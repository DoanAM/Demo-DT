// (C) 2004-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DLINECUTTER_HPP_
#define MW_MW3DLINECUTTER_HPP_
#include "mw3dLine.hpp"
#include "mwAutoPointer.hpp"
#include "mwException.hpp"
#include "mwMathConstants.hpp"

#include <list>


namespace cadcam
{
#define MW_3DLINECUTTER_EPSILON 0.000000001

template <typename T>
class MW_5AXUTIL_API mw3dLineCutter
{
public:
	typedef mw3dLine<T> Line;
	typedef typename Line::Ptr LinePtr;
	typedef typename Line::Point Point;
	typedef typename Line::PointPtr PointPtr;

	mw3dLineCutter(const Line& target): _Target(target) {}
	virtual ~mw3dLineCutter() {}

	const Line& GetTarget() const { return this->_Target; }
	LinePtr GetResult1() { return this->_Result1; }
	LinePtr GetResult2() { return this->_Result2; }

#if defined(_WIN32) && defined(ACCURACY)
	/// Cuts this line by the given sphere.
	/// @param center the center of the sphere.
	/// @param radius the radius of the sphere.
	/// @param l1 ref pointer to the first  result of cutting. Null if not exist.
	/// @param l2 ref pointer to the second result of cutting. Null if not exist.
	void CutSphere(PointPtr center, T radius)
	{
		ResetResult();
		Point a = *(GetTarget().GetStartPoint()) - *center;
		Point b = *(GetTarget().GetEndPoint()) - *(GetTarget().GetStartPoint());

		T a2 = a * a;
		T b2 = b * b;
		T ab = a * b;
		if (b2 < ACCURACY)
		{
			if (a2 > radius * radius)
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			return;
		}
		T d = ab * ab - b2 * (a2 - radius * radius);
		if (d <= 0.0)
		{
			SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			return;
		}
		T d2 = sqrt(d);
		T t1 = (-ab - d2) / b2;
		T t2 = (-ab + d2) / b2;
		if (t1 < 0.0)
		{
			if (t2 > 0.0)
			{
				if (t2 < 1.0)
					SetResult1(
						new Point(*(GetTarget().GetStartPoint()) + b * t2),
						GetTarget().GetEndPoint());
			}
			else
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
		}
		else
		{
			if (t1 >= 1.0)
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			else
			{
				if (t2 >= 1.0)
					SetResult1(
						GetTarget().GetStartPoint(),
						new Point(*(GetTarget().GetStartPoint()) + b * t1));
				else
				{
					SetResult1(
						GetTarget().GetStartPoint(),
						new Point(*(GetTarget().GetStartPoint()) + b * t1));
					SetResult2(
						new Point(*(GetTarget().GetStartPoint()) + b * t2),
						GetTarget().GetEndPoint());
				}
			}
		}
	}
#endif

	/// Cuts this line by the given cylinder.
	/// @param axle the axle of the cylinder.
	/// @param radius the radius of the cylinder.
	void CutCylinder(const mw3dLine<T>& axle, T radius)
	{
		ResetResult();
		T r = radius;
		T r2 = r * r;
		Point A = *axle.GetEndPoint() - *axle.GetStartPoint();
		T a2 = A * A;
		if (a2 < MW_3DLINECUTTER_EPSILON)
		{
			// TODO: intersection with disk.
			SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			return;
		}
		Point B = *(GetTarget().GetEndPoint()) - *(GetTarget().GetStartPoint());
		T b2 = B * B;
		Point S = *(GetTarget().GetStartPoint()) - *axle.GetStartPoint();

		// check the distance from line to axis
		Point AxB = A % B;
		T ab2 = AxB * AxB;
		if (ab2 < MW_3DLINECUTTER_EPSILON)
		{
			Point v = S % A;
			T d = (v * v) / a2;
			if (d > r2)
			{
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
				return;
			}
		}
		else
		{
			T v = S * AxB;
			T d = v * v / ab2;
			if (d > r2)
			{
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
				return;
			}
		}

		Point E = *(GetTarget().GetEndPoint()) - *axle.GetStartPoint();
		Point AxS = A % S;
		Point AxE = A % E;
		T axs2 = AxS * AxS;
		T axe2 = AxE * AxE;
		T sa = S * A;
		T ea = E * A;
		if (b2 < MW_3DLINECUTTER_EPSILON)
		{
			if ((axs2 <= r2 || axe2 <= r2) && (sa >= 0.0 || ea >= 0.0) &&
				(sa * sa < a2 * a2 || ea * ea < a2 * a2))
				return;
			SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			return;
		}
		// Full cutting case.
		if (sa >= 0.0 && sa <= a2 && ea >= 0.0 && ea <= a2 && axs2 <= r2 && axe2 <= r2)
			return;
		// Lets x = s + b * t
		//~(x - a*[(a*x)/a2]) = r; =>
		//(x - a*[(a*x)/a2])^2 - r2 = 0;
		// x^2 - (a*x)^2/a2 - r2 = 0;
		//(s+b*t)^2-((a*s)+(a*b)*t)^2/a2 - r2 = 0;
		//[a2*b2-(a*b)^2] [a2*s*b-(a*s)*(a*b)] [ a2*(s*s-r2)-(a*s)^2 ]
		T ts1, ts2;
		T ab = A * B;
		T k1 = a2 * b2 - ab * ab;
		if (k1 < MW_3DLINECUTTER_EPSILON)
		{
			if (ab >= MW_3DLINECUTTER_EPSILON)
			{
				T t1 = (a2 - sa) / ab;
				T t2 = -sa / ab;
				if (t1 < t2)
				{
					ts1 = t1;
					ts2 = t2;
				}
				else
				{
					ts1 = t2;
					ts2 = t1;
				}
			}
			else
			{
				// throw misc::mwException( 0, _T("CutCylinder unexpected case") );
				// TODO : unexpected case.
				return;
			}
		}
		else
		{
			T k2 = a2 * (S * B) - sa * ab;
			T k3 = a2 * (S * S - r2) - sa * sa;
			T d = k2 * k2 - k1 * k3;
			if (d < 0)
			{
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
				return;
			}
			if (d == 0.0)
			{
				// TODO: Touch case.
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
				return;
			}
			T d2 = sqrt(d);
			T t1 = (-k2 - d2) / k1;
			T t2 = (-k2 + d2) / k1;
			if ((t1 <= 0.0 && t2 <= 0.0) || (t1 >= 1.0 && t2 >= 1.0))
			{
				SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
				return;
			}
			if (t1 < t2)
			{
				ts1 = t1;
				ts2 = t2;
			}
			else
			{
				ts1 = t2;
				ts2 = t1;
			}
			if (ab >= MW_3DLINECUTTER_EPSILON)
			{
				T t3 = (a2 - sa) / ab;
				T t4 = -sa / ab;
				T ts3, ts4;
				if (t3 < t4)
				{
					ts3 = t3;
					ts4 = t4;
				}
				else
				{
					ts3 = t4;
					ts4 = t3;
				}
				if (ts1 < ts3)
					ts1 = ts3;
				if (ts2 > ts4)
					ts2 = ts4;
			}
		}
		if (ts2 <= 0.0 || ts1 >= 1.0)
		{
			SetResult1(GetTarget().GetStartPoint(), GetTarget().GetEndPoint());
			return;
		}
		if (ts1 > 0.0)
		{
			if (ts2 < 1.0)
			{
				SetResult1(
					GetTarget().GetStartPoint(),
					new Point(*(GetTarget().GetStartPoint()) + B * ts1));
				SetResult2(
					new Point(*(GetTarget().GetStartPoint()) + B * ts2), GetTarget().GetEndPoint());
			}
			else
			{
				SetResult1(
					GetTarget().GetStartPoint(),
					new Point(*(GetTarget().GetStartPoint()) + B * ts1));
			}
		}
		else
		{
			if (ts2 < 1.0)
			{
				SetResult1(
					new Point(*(GetTarget().GetStartPoint()) + B * ts2), GetTarget().GetEndPoint());
			}
		}
	}

	/// cut current line by cuboid (infinite)
	///
	/// cut current line by infinite cuboid
	///	@param axle the axle of rectangle which defines the cuboid
	///	@param radius the _T("radius") of rectangle
	void CutCuboid(const mw3dLine<T>& axle, T radius)
	{
		ResetResult();
		PointPtr ps = axle.GetStartPoint(), pe = axle.GetEndPoint();
		LinePtr flax = new Line(new Point(*ps), new Point(*pe));  // flat axle
		flax->GetStartPoint().z(0.);
		flax->GetEndPoint().z(0.);

		ps = _Target.GetStartPoint();
		pe = _Target.GetEndPoint();
		LinePtr fltg = new Line(new Point(*ps), new Point(*pe));  // flat _T("target") line
		fltg->GetStartPoint().z(0.);
		fltg->GetEndPoint().z(0.);


		Point dir = (*flax->GetEndPoint() - *flax->GetStartPoint()).Normalized();
		Point a_nrm(dir.y(), -dir.x(), 0.);  // RIGHT normal
		a_nrm = a_nrm * radius;

		T CB_t0 = 0., CB_t1 = 1., r;


		Point dxdy_full = *_Target.GetEndPoint() - *_Target.GetStartPoint();
		Point dxdy(dxdy_full);
		dxdy.z(0.);
		T tan_phi = dxdy_full.z() / ~dxdy;
		bool vis = 1;
		Point p1 = (*flax->GetStartPoint() + a_nrm);
		Point p2 = (*flax->GetEndPoint() + a_nrm);
		Point Q, tmp, N;
		for (int ii = 0; ii < 4; ++ii)
		{
			switch (ii)
			{
			case 1:
				p1 = p2;
				p2 = *flax->GetEndPoint() - a_nrm;
				break;
			case 2:
				p1 = p2;
				p2 = *flax->GetStartPoint() - a_nrm;
				break;
			case 3:
				p1 = p2;
				p2 = *flax->GetStartPoint() + a_nrm;
				break;
			}

			Q = *fltg->GetStartPoint() - p1;
			tmp = (p2 - p1);
			N.x(-tmp.y());
			N.y(tmp.x());  // LEFT normal
			N.z(0);

			T Pn = dxdy * N;
			T Qn = Q * N;

			if (mathdef::is_eq(Pn, 0.))
			{
				if (Qn < 0.)
				{
					vis = 0;
					break;
				}
			}
			else
			{
				r = -Qn / Pn;
				if (Pn < 0.)
				{
					if (r < CB_t0)
					{
						vis = 0;
						break;
					}
					if (r < CB_t1)
						CB_t1 = r;
				}
				else
				{
					if (r > CB_t1)
					{
						vis = 0;
						break;
					}
					if (r > CB_t0)
						CB_t0 = r;
				}
			}
		}
		if (vis)
		{
			Point v1 = *_Target.GetStartPoint(), v2 = *_Target.GetEndPoint();
			if (CB_t0 > CB_t1)
				vis = 0;
			else
			{
				Point z_corr_t1(0., 0., ~dxdy * CB_t1 * tan_phi),
					z_corr_t0(0., 0., ~dxdy * CB_t0 * tan_phi);  // compute applicates corrections

				if (mathdef::is_eq(CB_t0, CB_t1) && CB_t1 < 1. && CB_t0 > 0.)
				{
					SetResult1(new Point(v1 + CB_t1 * dxdy + z_corr_t1), new Point(v2));
				}
				else
				{
					if (CB_t1 < 1.)
						SetResult1(new Point(v1 + CB_t1 * dxdy + z_corr_t1), new Point(v2));
					if (CB_t0 > 0.)
						SetResult2(new Point(v1), new Point(v1 + CB_t0 * dxdy + z_corr_t0));
				}
			}
		}
		if (!vis)
			_Result1 = new Line(_Target);
	}

	/// get tangent of angle between current line and XOY plane
	///
	///	@returns line-plane intersection angle tangent
	T GetXOYPlaneTangent()
	{
		Point dir = *_Target.GetEndPoint() - *_Target.GetStartPoint();
		Point dxdy(dir);
		dxdy.z(0);  // get projection
		return (dir.z() / ~dxdy);
	}


	/// cut current line by cylinder (w. infinite axis length)
	///
	/// cut current line by infinite cylinder
	///	@param center some point on the cylinder's axis to assume as a center
	///	@param radius of the cylinder
	void CutInfCylinder(const mw3dPoint<T>& center, T radius)
	{
		ResetResult();

		Point p1 = *_Target.GetStartPoint();
		Point p2 = *_Target.GetEndPoint();
		Point p3 = center;
		p1.z(0);
		p2.z(0);
		p3.z(0);

		T r = radius;

		T p1_dist = ~(p3 - p1);
		T p2_dist = ~(p3 - p2);
		Point lv = p2 - p1;

		if (p1_dist < r && p2_dist < r)
			return;  // line lies entirely inside arc circle

		T a = lv * lv;
		T b = 2. * (lv * (p1 - p3));
		T c = p3 * p3 + p1 * p1 - 2. * (p3 * p1) - r * r;

		T delta = b * b - 4. * a * c;

		if (delta <= 0.)
		{
			SetResult1(new Point(*_Target.GetStartPoint()), new Point(*_Target.GetEndPoint()));
			return;  // no intersection or tangent
		}

		T t1 = (-b - sqrt(delta)) / 2. / a;
		T t2 = (-b + sqrt(delta)) / 2. / a;

		T pre1 = ~lv * GetXOYPlaneTangent();

		Point z_corr_t1(0., 0., t1 * pre1),
			z_corr_t2(0., 0., t2 * pre1);  // compute applicates corrections


		p1 = *_Target.GetStartPoint();
		p2 = *_Target.GetEndPoint();
		if (t1 <= 0.0)
		{
			if (t2 > 0.0 && t2 < 1.0)
				SetResult1(new Point(p1 + lv * t2 + z_corr_t2), new Point(p2));
			else
				SetResult1(new Point(p1), new Point(p2));
		}
		else
		{
			if (t1 >= 1.0)
				SetResult1(new Point(p1), new Point(p2));
			else
			{
				if (t2 >= 1.0 || t2 <= 0)
					SetResult1(new Point(p1), new Point(p1 + lv * t1 + z_corr_t1));
				else
				{
					SetResult1(new Point(p1), new Point(p1 + lv * t1 + z_corr_t1));
					SetResult2(new Point(p1 + lv * t2 + z_corr_t2), new Point(p2));
				}
			}
		}
	}

private:
	mw3dLineCutter& operator=(mw3dLineCutter&);  // avoid warning C4512

	void ResetResult()
	{
		_Result1 = 0;
		_Result2 = 0;
	}

	/// SetResult1 function
	///
	///	@param start of type PointPtr
	///	@param end of type PointPtr
	///	@returns SetResult1 of type void
	void SetResult1(PointPtr start, PointPtr end)
	{
		if (~(*start - *end) < MW_3DLINECUTTER_EPSILON)
			return;
		_Result1 = new Line(start, end);
	}

	/// SetResult2 function
	///
	///	@param start of type PointPtr
	///	@param end of type PointPtr
	///	@returns SetResult2 of type void
	void SetResult2(PointPtr start, PointPtr end)
	{
		if (~(*start - *end) < MW_3DLINECUTTER_EPSILON)
			return;
		_Result2 = new Line(start, end);
	}

	const Line& _Target;

	LinePtr _Result1;
	LinePtr _Result2;
};

typedef mw3dLineCutter<float> mw3dfLineCutter;
typedef mw3dLineCutter<double> mw3ddLineCutter;

#undef MW_3DLINECUTTER_EPSILON
}  // namespace cadcam
#endif  //	MW_MW3DLINECUTTER_HPP_
