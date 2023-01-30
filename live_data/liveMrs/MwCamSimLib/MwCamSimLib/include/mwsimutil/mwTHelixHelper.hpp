// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTHelixHelper class

#ifndef MW_MWTHELIXHELPER_HPP_
#define MW_MWTHELIXHELPER_HPP_
#include "mwVectorUtils.hpp"
#include "mwTHelixBase.hpp"
#include "mwTHelix.hpp"
#include "mwTGeometryHelper.hpp"
#include "mwTVector3.hpp"
#include "mwCadcamFwdDecl.hpp"
#include "mw3dArc.hpp"
#include "mw3dHelix.hpp"
#include "mwTCSijkGetter.hpp"
#include "mwCadcamMathConvs.hpp"
#include "mwAngleUtils.hpp"
#include <utility>
#include <list>

#ifndef MW_USE_VS2008_COMPATIBILITY
#include <array>
#endif

namespace geoDef
{
	template <class T, class TCoordSystem>
	class mwTHelixHelper: public mwTGeometryHelper<mwTHelixBase<T>, TCoordSystem>
	{
	public:
		typedef mwTHelix<T, TCoordSystem> HelixGeo;

		typedef typename mwTGeometryHelper<mwTHelixBase<T>, TCoordSystem>::BaseGeo BaseGeo;
		typedef typename mwTGeometryHelper<mwTHelixBase<T>, TCoordSystem>::PositionVector PositionVector;

		typedef std::pair<T, PositionVector>		PointAnglePair;
		typedef std::list<PointAnglePair>				PointAnglePairList;
		// TODO: Move CreateArcPointsInTolerance function to cadcam library.
		// CreateArcPointsInTolerance function creates circular dependencies
		// because it's used in cadcam library only.
		static PointAnglePairList CreateArcPointsInTolerance(
			const HelixGeo& helixGeo, const T angleTolerance)
		{
			PointAnglePairList toReturn;

			int iLines = static_cast<int>(ceil(std::fabs(helixGeo.GetBase().GetSweepAngle() / angleTolerance)));
			if(iLines == 0)
			{
				iLines = 1;
			}

			const T sgn = static_cast<T>(helixGeo.GetBase().GetSweepAngle() < 0 ? -1 : 1);
			const T angDelta = sgn * helixGeo.GetBase().GetSweepAngle() / iLines;

			for(int i = 0; i <= iLines; i++)
			{
				const T alpha = i * angDelta;
				toReturn.push_back(PointAnglePair(alpha, helixGeo.GetVector(alpha)));
			}
			return toReturn;
		}
	private:
		//! Constructor - not allowed since it's a static class
		mwTHelixHelper();
	};

	template <class T>
	class mwTHelixHelper3d: public mwTHelixHelper<T, mwTAbstractCoordSystem3d<T> >
	{
	public:

		typedef typename mwTHelixHelper<T, mwTAbstractCoordSystem3d<T> >::HelixGeo HelixGeo;

		static T GetHelixHeight(const HelixGeo& helix)
		{
			return mathdef::Abs(helix.GetBase().GetSweepAngle() * helix.GetBase().GetStep());
		}

		static void SetHelixHeight(HelixGeo& helix, const T height)
		{
			const T step = helix.GetBase().GetStep();
			if(mathdef::is_not_zero(step))
			{
				typename HelixGeo::BaseGeo baseHelix = helix.GetBase();
				baseHelix.SetSweepAngle(height / step);
				helix.SetBase(baseHelix);
			}
		}

		static bool IsRightHandedBasis(const HelixGeo& sourceHelix)
		{
			mwTCSijkGetter<T> ijkCS3dGetter;
			sourceHelix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			cadcam::mwTPoint3d<T> iNormal = cadcam::to_cadcam(ijkCS3dGetter.Geti());
			cadcam::mwTPoint3d<T> jNormal = cadcam::to_cadcam(ijkCS3dGetter.Getj());
			cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());

			return cadcam::mwVectorUtils<T>::GetShortestAngInRad(
				kNormal, iNormal % jNormal) < mathdef::MW_PI_2;
		}

		static void ReverseHelix(HelixGeo& sourceHelix)
		{
			mwTCSijkGetter<T> ijkCS3dGetter;
			sourceHelix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			const T sweepAngle = sourceHelix.GetBase().GetSweepAngle();
			
			cadcam::mwTPoint3d<T> iNormal = cadcam::to_cadcam(ijkCS3dGetter.Geti());
			cadcam::mwTPoint3d<T> jNormal = cadcam::to_cadcam(ijkCS3dGetter.Getj());
			cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());
			cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());

			origin += kNormal * GetHelixHeight(sourceHelix);
			kNormal = -kNormal;
			jNormal = -jNormal;

			T sweepAngleInDeg = sweepAngle * 180 / static_cast<T>(mathdef::MW_PI);
			measures::mwAngleUtils<T>::MapAngleBetween0And360(sweepAngleInDeg);

			if(mathdef::is_not_zero(sweepAngleInDeg))
			{
				const T rotationAngle = IsRightHandedBasis(sourceHelix)
					? 360 - sweepAngleInDeg
					: sweepAngleInDeg - 360;

				const cadcam::mwMatrix<T, 4, 4> rotationMatrix =
					cadcam::mwMatrixTransformationsFactory<T>::Create3dRotation(
						kNormal, rotationAngle);

				iNormal.Transform(rotationMatrix);
				jNormal.Transform(rotationMatrix);
			}

			sourceHelix.SetCoordSystem(
				mwTijkCoordSystem3d<T>(
				cadcam::from_cadcam(origin),
				cadcam::from_cadcam(iNormal),
				cadcam::from_cadcam(jNormal),
				cadcam::from_cadcam(kNormal)));
		}

		static void RotateHelix(
			HelixGeo& sourceHelix, const cadcam::mwMatrix<T, 4, 4>& matrix)
		{
			mwTCSijkGetter<T> ijkCS3dGetter;
			sourceHelix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			cadcam::mwTPoint3d<T> iNormal = cadcam::to_cadcam(ijkCS3dGetter.Geti());
			cadcam::mwTPoint3d<T> jNormal = cadcam::to_cadcam(ijkCS3dGetter.Getj());
			cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());
			cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());

			iNormal.Transform(matrix);
			jNormal.Transform(matrix);
			kNormal.Transform(matrix);
			origin.Transform(matrix);

			sourceHelix.SetCoordSystem(
				mwTijkCoordSystem3d<T>(
				cadcam::from_cadcam(origin),
				cadcam::from_cadcam(iNormal),
				cadcam::from_cadcam(jNormal),
				cadcam::from_cadcam(kNormal)));
		}

		static void MoveHelix(
			HelixGeo& sourceHelix, const cadcam::mwMatrix<T, 4, 4>& matrix)
		{
			mwTCSijkGetter<T> ijkCS3dGetter;
			sourceHelix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);
			cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());

			origin.Transform(matrix);
			sourceHelix.SetCoordSystem(
				mwTijkCoordSystem3d<T>(
				cadcam::from_cadcam(origin),
				ijkCS3dGetter.Geti(),
				ijkCS3dGetter.Getj(),
				ijkCS3dGetter.Getk()));
		}

		static typename HelixGeo::Ptr GetHelixCopyWithPositiveSweepAngle(
			const typename HelixGeo::Ptr& src)
		{
			typename HelixGeo::Ptr arc = src.DeepCopy();
			typename HelixGeo::BaseGeo base = arc->GetBase();
			base.SetSweepAngle(mathdef::Abs(arc->GetBase().GetSweepAngle()));
			arc->SetBase(base);
			return arc;
		}

		static void RotateHelix(
			HelixGeo& sourceHelix,
			const cadcam::mwTPoint3d<T>& axis,
			const cadcam::mwTPoint3d<T>& axisBasePoint,
			const T angle)
		{
			const cadcam::mwMatrix<T, 4, 4> rotationMatrix =
				cadcam::mwMatrixTransformationsFactory<T>::Create3dRotation(
					axis,
					axisBasePoint,
					angle);
			RotateHelix(sourceHelix, rotationMatrix);
		}

		static cadcam::mw3dLine<T> GetHelixAxis(const HelixGeo& helix)
		{
			mwTCSijkGetter<T> ijkCS3dGetter;
			helix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			const cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());
			const cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());

			const cadcam::mwTPoint3d<T> helixAxisStart = origin + kNormal * GetHelixHeight(helix);

			cadcam::mw3dLine<T> result(helixAxisStart, origin);
			return result;
		}

		static const bool IsArc(const HelixGeo& src)
		{
			return mathdef::is_zero(
				src.GetBase().GetSweepAngle() * src.GetBase().GetStep());
		}

		static typename cadcam::mw3dArc<T>::Ptr GetArc(const HelixGeo& src)
		{
			if (!IsArc(src))
				MW_EXCEPTION("Can't convert non-planar helix");
			mwTCSijkGetter<T> cs;
			src.GetCoordSystem().AcceptVisitor(cs);
			const T sign = static_cast<T>(IsRightHandedBasis(src) ? 1 : -1);
			const cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(cs.GetOrigin());
			const cadcam::mwTPoint3d<T> axis = sign * cadcam::to_cadcam(cs.Getk());
			const cadcam::mwTPoint3d<T> startPoint = cadcam::to_cadcam(src.GetVector(0));
			const cadcam::mwTPoint3d<T> endPoint = cadcam::to_cadcam(src.GetVector(src.GetBase().GetSweepAngle()));
			return new cadcam::mw3dArc<T>(origin, startPoint-origin, endPoint-origin, axis);
		}

		static typename cadcam::mw3dHelix<T>::Ptr GetHelix(const HelixGeo& src)
		{
			mwTCSijkGetter<T> cs;
			src.GetCoordSystem().AcceptVisitor(cs);
			const T sign = static_cast<T>(IsRightHandedBasis(src) ? 1 : -1);
			const cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(cs.GetOrigin());
			const cadcam::mwTPoint3d<T> axis = sign * cadcam::to_cadcam(cs.Getk());
			const cadcam::mwTPoint3d<T> startPoint = cadcam::to_cadcam(src.GetVector(0));
			const double sweepAngle = src.GetBase().GetSweepAngle();
			return new cadcam::mw3dHelix<T>(
				origin,
				startPoint - origin,
				axis,
				sweepAngle * mathdef::MW_R2D,
				sign * src.GetBase().GetStep() * sweepAngle);
		}

		static typename cadcam::mw3dGeometry<T>::Ptr GetGeometry(const HelixGeo& src)
		{
			return IsArc(src)
				? static_cast<typename cadcam::mw3dGeometry<T>::Ptr>(GetArc(src))
				: static_cast<typename cadcam::mw3dGeometry<T>::Ptr>(GetHelix(src));
		}

		//! Get helix part between 0 and 360 degrees
		/*!
			\param[in] sourceHelix Base helix for the new one
			\param[in] startPoint Start point of the new helix given on plane of sourceHelix origin
			\param[in] endPoint End point of the new helix given on plane of sourceHelix origin
		*/
		static typename HelixGeo::Ptr CreatePartHelix(
			const typename HelixGeo::Ptr& sourceHelix,
			const cadcam::mwTPoint3d<T>& startPoint,
			const cadcam::mwTPoint3d<T>& endPoint)
		{
			geoDef::mwTCSijkGetter<T> ijkCS3dGetter;
			sourceHelix->GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			const cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());
			const cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());
			const cadcam::mwTPoint3d<T> iNormal = (startPoint - origin).NormalizedOrZero();
			const cadcam::mwTPoint3d<T> jNormal = IsRightHandedBasis(*sourceHelix)
				? kNormal % iNormal : iNormal % kNormal;

			const T shortestAngle =
				cadcam::mwVectorUtils<T>::GetShortestAngInRad(iNormal, endPoint - origin);
			const T sweepAngle = sourceHelix->GetBase().GetSweepAngle() < 0
				? -shortestAngle : shortestAngle;

			typename HelixGeo::BaseGeo helixBase = sourceHelix->GetBase();
			helixBase.SetSweepAngle(sweepAngle);

			typename HelixGeo::Ptr result = new HelixGeo(helixBase,
				geoDef::mwTijkCoordSystem3d<T>(
					cadcam::from_cadcam(origin),
					cadcam::from_cadcam(iNormal),
					cadcam::from_cadcam(jNormal),
					cadcam::from_cadcam(kNormal)));

			return result;
		}

		static cadcam::mwTPoint3d<T> GetHelixTangent(
			const HelixGeo& helix,
			const double t)
		{
			using namespace cadcam;
			typedef mwTPoint3d<T> Point;
			const Point start = to_cadcam(helix.GetVector(0));

			geoDef::mwTCSijkGetter<T> ijkCS3dGetter;
			helix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);
			const Point iNormal = to_cadcam(ijkCS3dGetter.Geti());
			const Point jNormal = to_cadcam(ijkCS3dGetter.Getj());
			const Point kNormal = to_cadcam(ijkCS3dGetter.Getk());
			Point axis = jNormal % iNormal;

			const Point origin = to_cadcam(ijkCS3dGetter.GetOrigin());
			const double step = helix.GetBase().GetStep(); 
			const double R = helix.GetBase().GetRadius();
			Point startVec = (start - origin).Normalized();
			if (mathdef::is_not_zero(t))
			{
				const mwHomogenousMatrixd rot =
					mwMatrixTransformationsFactory<T>::Create3dRotation(
					axis, - t * mathdef::MW_R2D);
				startVec.Transform(rot);
			}
			if (mathdef::is_not_zero(step))
			{
				const double angle = atan(step / R)*mathdef::NonZeroSign(kNormal * axis);
				const mwHomogenousMatrixd rot =
					mwMatrixTransformationsFactory<T>::Create3dRotation(
					startVec, -angle * mathdef::MW_R2D);
				axis.Transform(rot);
			}
			return (axis % startVec).Normalized();
		}

		static cadcam::mw3dBoundingBox<T> GetBBox(const HelixGeo& helix)
		{
			geoDef::mwTCSijkGetter<T> ijkCS3dGetter;
			helix.GetCoordSystem().AcceptVisitor(ijkCS3dGetter);

			const cadcam::mwTPoint3d<T> iNormal = cadcam::to_cadcam(ijkCS3dGetter.Geti());
			const cadcam::mwTPoint3d<T> jNormal = cadcam::to_cadcam(ijkCS3dGetter.Getj());
			const cadcam::mwTPoint3d<T> kNormal = cadcam::to_cadcam(ijkCS3dGetter.Getk());
			const cadcam::mwTPoint3d<T> origin = cadcam::to_cadcam(ijkCS3dGetter.GetOrigin());

			const T thetaMax = helix.GetBase().GetSweepAngle();
			const T radius = helix.GetBase().GetRadius();
			const T step = helix.GetBase().GetStep();

			cadcam::mwTPoint3d<T> minPt;
			cadcam::mwTPoint3d<T> maxPt;

#ifndef MW_USE_VS2008_COMPATIBILITY
			std::tie(minPt[0], maxPt[0]) = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.x(), jNormal.x(), kNormal.x()), radius, step, thetaMax);
			std::tie(minPt[1], maxPt[1]) = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.y(), jNormal.y(), kNormal.y()), radius, step, thetaMax);
			std::tie(minPt[2], maxPt[2]) = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.z(), jNormal.z(), kNormal.z()), radius, step, thetaMax);
#else
			std::pair<T, T> extremeX = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.x(), jNormal.x(), kNormal.x()), radius, step, thetaMax);
			std::pair<T, T> extremeY = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.y(), jNormal.y(), kNormal.y()), radius, step, thetaMax);
			std::pair<T, T> extremeZ = CalculateCoordinateExtremum(
				cadcam::mwTPoint3d<T>(iNormal.z(), jNormal.z(), kNormal.z()), radius, step, thetaMax);

			minPt = cadcam::mwTPoint3d<T>(extremeX.first, extremeY.first, extremeZ.first);
			maxPt = cadcam::mwTPoint3d<T>(extremeX.second, extremeY.second, extremeZ.second);
#endif	// MW_USE_VS2008_COMPATIBILITY

			return cadcam::mw3dBoundingBox<T>(minPt + origin, maxPt + origin);
		}

	private:
		static std::pair<T, T> CalculateCoordinateExtremum(
			const cadcam::mwTPoint3d<T>& vec, const T radius, const T step, const T tMax)
		{
			const T R = radius, R2 = R * R;
			const T S = step, S2 = S * S;
			const T i = vec.x(), i2 = i * i;
			const T j = vec.y(), j2 = j * j;
			const T k = vec.z(), k2 = k * k;

			// t is sweep angle parameter
			const std::pair<T, T> t12 = std::make_pair(
				-2 * std::atan((R * i + std::sqrt(R2 * i2 + R2 * j2 - S2 * k2)) / (R * j - S * k)),
				-2 * std::atan((R * i - std::sqrt(R2 * i2 + R2 * j2 - S2 * k2)) / (R * j - S * k)));

			const T t1Min = t12.first > 0 ? t12.first : t12.first + mathdef::MW_2PI;
			const T t2Min = t12.second > 0 ? t12.second : t12.second + mathdef::MW_2PI;

			const size_t CANDIDATES_SIZE = 6;
#ifndef MW_USE_VS2008_COMPATIBILITY
			std::array<T, CANDIDATES_SIZE> candidates;
#else
			T candidates[CANDIDATES_SIZE];
#endif // MW_USE_VS2008_COMPATIBILITY

			candidates[0] = 0;
			candidates[1] = mathdef::mw_limit(t1Min, (T)0, tMax);
			candidates[2] = mathdef::mw_limit(t2Min, (T)0, tMax);

			// n is the count of full rotations
			const int n = (tMax - (std::min)(t12.first, t12.second)) / mathdef::MW_2PI;

			T t1Max = t12.first + mathdef::MW_2PI * n;
			T t2Max = t12.second + mathdef::MW_2PI * n;
			t1Max = t1Max < tMax ? t1Max : t1Max - mathdef::MW_2PI;
			t2Max = t2Max < tMax ? t2Max : t2Max - mathdef::MW_2PI;

			candidates[3] = tMax;
			candidates[4] = mathdef::mw_limit(t1Max, (T)0, tMax);
			candidates[5] = mathdef::mw_limit(t2Max, (T)0, tMax);

			for (size_t idx = 0; idx < CANDIDATES_SIZE; ++idx)
			{
				candidates[idx] = R * i * std::cos(candidates[idx]) +
								  R * j * std::sin(candidates[idx]) +
								  S * k * candidates[idx];
			}

#ifndef MW_USE_VS2008_COMPATIBILITY
			return std::make_pair(
				*std::min_element(candidates.begin(), candidates.end()),
				*std::max_element(candidates.begin(), candidates.end()));
#else
			return std::make_pair(
				*std::min_element(candidates, candidates + CANDIDATES_SIZE),
				*std::max_element(candidates, candidates + CANDIDATES_SIZE));
#endif // MW_USE_VS2008_COMPATIBILITY
		}

	};

	typedef mwTHelixHelper3d<float> HelixfIn3dfHelper;
	typedef mwTHelixHelper3d<double> HelixdIn3ddHelper;
}
#endif	//	MW_MWTHELIXHELPER_HPP_
