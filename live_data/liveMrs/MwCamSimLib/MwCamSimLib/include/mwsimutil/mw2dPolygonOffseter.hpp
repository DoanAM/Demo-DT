// (C) 2004-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYGONOFFSETER_HPP_
#define MW_MW2DPOLYGONOFFSETER_HPP_


#include "mw2dArc.hpp"
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwGeometryCopy.hpp"
#include "mwLength.hpp"

#include <list>
#include <vector>

namespace intersect
{
	template <class T> class mw2dGeometryInflatedCutter;
	template <class T> class mw2dCircleCutter;
	template <class T> class mw2dRectangleCutter;
	template <class T> class mw2dArcStripCutter;
	template <class T> class mw2dCutter;
}

namespace cadcam
{
#pragma warning(push)
#pragma warning(disable: 4512)

	template<class T>
	class mwOffsetGenerator
	{
	public:
		typedef std::vector<T>	PolyLineOffsets;

		mwOffsetGenerator(
			const T lowerOffset,
			const T upperOffset,
			const bool selectPozitiveOffsets = true)
				: m_lowerOffset(lowerOffset),
				m_upperOffset(upperOffset),
				m_selectPozitiveOffsets(selectPozitiveOffsets)
		{
		}

		const PolyLineOffsets operator()(const mw2dPolyLine< T > &src) const
		{
			typename mw2dPolyLine<T>::PointListConstIt it(src.GetPointBegin()), ite(src.GetPointEnd());
			T maxHeight = mathdef::mw_minvalue(T());
			T minHeight = mathdef::mw_maxvalue(T());
			for (; it != ite; ++it)
			{
				if (it->y() > maxHeight)
				{
					maxHeight = it->y();
				}
				if (it->y() < minHeight)
				{
					minHeight = it->y();
				}
			}
			PolyLineOffsets pozNegOffsets;
			it = src.GetPointBegin();
			for (; it != ite; ++it)
			{
				T curOffset = m_lowerOffset
					+ it->y() *(m_upperOffset - m_lowerOffset) / (maxHeight - minHeight);
				pozNegOffsets.push_back(curOffset);
			}

			return SelectPozitiveOffset(pozNegOffsets);
		}
	private:
		PolyLineOffsets SelectPozitiveOffset(const PolyLineOffsets& pozNegOffsets) const
		{
			PolyLineOffsets toReturn;
			typename PolyLineOffsets::const_iterator it(pozNegOffsets.begin()), ite(pozNegOffsets.end());
			for (; it != ite; ++it)
			{
				T curOffset = *it;
				if (m_selectPozitiveOffsets && curOffset < 0)
				{
					curOffset = 0;
				}
				if (!m_selectPozitiveOffsets && curOffset > 0)
				{
					curOffset = 0;
				}
				toReturn.push_back(std::fabs(curOffset));
			}
			return toReturn;
		}

		bool m_selectPozitiveOffsets;
		const T m_lowerOffset;
		const T m_upperOffset;
	};  // end class OffsetGenerator

#pragma warning(pop)
}

namespace cadcam
{
	/// Class for constructing offset curve from a polyline
	template <class T, class OffsetGenerator = mwOffsetGenerator<T> > class MW_5AXUTIL_API mw2dPolygonOffseter
	{
	public:

		enum OffsetDir
		{
			LEFT,
			RIGHT
		};

		enum CrossoverHandling
		{
			LINE,
			TARC
		};


		typedef CrossoverHandling					GapHandling;
		typedef mw2dContour< T >					Contour;
		typedef typename mw2dContour< T >::Ptr		ContourPtr;
		typedef mw2dPolyLine<T>						PolyLine2d;
		typedef std::vector<PolyLine2d>				PolyLine2dVec;
		typedef std::vector<T>						PolyLineOffsets;



		/// Constructor
		///
		///	mw2dPolygonOffseter inits offseter with direction and
		///	the way intersections/gaps are handled
		///	@param dir offset direction
		///	@param ch defines crossover handling in offsetting result. Now only TARC is supproted
		///	@param gh defines gap handling in offsetting result. Now only TARC is supproted
		MW_DEPRECATED("Deprecated in 2018.04, use mw2dTransitiveOffsetter instead.")
		mw2dPolygonOffseter(
			const OffsetDir dir,
		    const CrossoverHandling ch = TARC,
			const GapHandling gh = TARC)
			: m_dir(dir), m_crh(ch), m_gah(gh)
		{
		}

		/// Destructor
		virtual ~mw2dPolygonOffseter()
		{
		}

		/// Build polyline offset contour
		///
		///	Offset builds polyline offset contour
		///	@param src vector of polyline to work with
		///	@param dist distance to offset
		///	@return contour object with offset result
		const ContourPtr Offset(
			const std::vector< mw2dPolyLine< T > >  &src,
			T dist);


		/// Build polyline offset contour
		///
		///	Offset builds polyline offset contour
		///	@param src polyline to work with
		///	@param dist distance to offset
		///	@return contour object with offset result
		const ContourPtr Offset(
			const mw2dPolyLine<T> &src,
			T dist);


		const ContourPtr Offset(
			const mw2dPolyLine<T> &src,
			const OffsetGenerator &og);

protected:

		typedef mwTPoint2d<T>							        Point;
		typedef typename mw2dPoint< T >::Ptr					PointPtr;
		//
		typedef mw2dLine< T >							        Line;
		typedef typename mw2dLine< T >::Ptr						LinePtr;
		//
		typedef mw2dArc< T >							        Arc;
		typedef typename mw2dArc< T >::Ptr						ArcPtr;
		//
		typedef mw2dGeometry< T >						        Item;
		typedef typename misc::mwAutoPointer< Item >			ItemPtr;
		typedef typename std::list < ItemPtr >					ItemList;
		typedef typename ItemList::iterator						ItemListIt;
		typedef typename ItemList::const_iterator				ItemListConstIt;
		//
		typedef cadcam::mw2dPolyLine< T >						Profile;
		//
		typedef typename Profile::PointList						PointList;
		typedef typename PointList::iterator						PointListIt;
		typedef typename PointList::const_iterator				PointListConstIt;


		typename mw2dArc<T>::Ptr CreateArc(
			const Point &center,
			const Point &prevDir,
			const Point &curDir,
			const OffsetDir arcLocationSide,
			const T offsetVal) const;


		/// Offset each segment of polyline in specified direction without trimming
		///
		///	OffsetSegments offsets each segment of polyline
		///	@param src source polyline
		///	@param dist distance to offset
		///	@return contour object with offseted lines
		ContourPtr OffsetSegments(
			const mw2dPolyLine<T>  &src,
			T dist);

		ContourPtr OffsetSegments(
			const mw2dPolyLine<T> &src,
			const PolyLineOffsets &polyLineOffset);


		/// Set polygon orientation according to offset direction
		const PolyLine2dVec SetAppropriateDirection(
			const PolyLine2dVec &src,
			const typename mw2dPolygonOffseter<T, OffsetGenerator>::OffsetDir dir) const
		{
			PolyLine2dVec ret;
			for (typename PolyLine2dVec::const_iterator it = src.begin(); it != src.end(); ++it)
			{
				ret.push_back(*it);
				if (dir == mw2dPolygonOffseter<T>::LEFT)
				{
					ret.back().Reverse();
				}
			}
			return ret;
		}

		template <typename Geom>
		const Geom SetAppropriateDirection(
			const Geom &src,
			const typename mw2dPolygonOffseter<T, OffsetGenerator>::OffsetDir dir) const
		{
			Geom ret(mwGeometryCopy::Deep(src));
			if(!cadcam::mwLength::IsZero(ret) && dir == mw2dPolygonOffseter<T>::LEFT)
			{
				ret.Reverse();
			}
			return ret;
		}
		const PolyLine2d SetAppropriateDirection(
			const PolyLine2d &src,
			const typename mw2dPolygonOffseter<T, OffsetGenerator>::OffsetDir dir) const
		{
			PolyLine2d ret(src);
			if(!cadcam::mwLength::IsZero(ret) && dir == mw2dPolygonOffseter<T>::LEFT)
			{
				ret.Reverse();
			}
			return ret;
		}

	private:

		PolyLineOffsets CreateOffsets(
			const Profile &src,
			const double lowerOffset,
			const double upperOffset);

		const T CalculateEliminationTolerance(const PolyLine2dVec &src)
		{
			T minDiagLen(mathdef::mw_maxvalue(T()));
			for (typename PolyLine2dVec::const_iterator it = src.begin(); it != src.end(); ++it)
			{
				const T diagLen(it->GetBoundingBox().GetDiagonalLength());
				if(diagLen < minDiagLen)
					minDiagLen = diagLen;
			}
			return minDiagLen * static_cast<T>(1e-8);
		}


		void SetAppropriateOffsetOrder(
			PolyLineOffsets &src,
			const OffsetDir dir) const
		{
			if (dir == mw2dPolygonOffseter<T>::LEFT)
			{
				std::reverse(src.begin(), src.end());
			}
		}

		/// Convert polyline to contour
		const ContourPtr GetContour(const PolyLine2dVec &src);

		/// Detect if angle between two offseted successive line segments is obtuse/acute
		///
		///	IsGap detects if two lines have a gap between each other after offset
		///	@param l1 first line
		///	@param l2 second line
		///	@return true if lines offset resulted a gap; false otherwise
		const bool IsGap(
			const Line& l1,
			const Line& l2,
			const T radius);

		void CreateArcsAtEveryGap(
			ContourPtr& cont,
			const mw2dPolyLine<T> &poly,
			const T dist);

	protected:

		/// gap handling mode
		GapHandling m_gah;
		/// crossover handling mode
		CrossoverHandling m_crh;
		/// offset direction
		OffsetDir m_dir;

	};  // end class mw2dPolygonOffseter

}  // end namespace

#endif	//	MW_MW2DPOLYGONOFFSETER_HPP_
