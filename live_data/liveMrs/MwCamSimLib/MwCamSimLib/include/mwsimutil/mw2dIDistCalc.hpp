// (C) 2005-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DIDISTCALC_HPP_
#define MW_MW2DIDISTCALC_HPP_
#include "mw2dGeometry.hpp"
#include "mwMathConstants.hpp"
#include "mwMinSquaredDistance.hpp"

namespace cadcam
{
/// Abstract interface for distance calculators in 2d
template <typename T>
class MW_5AXUTIL_API mw2dIDistCalc
{
public:
	typedef mw2dGeometry<T> Geometry;
	/// Get first object involved in distance calculation
	virtual const Geometry& GetGeometry1() const = 0;
	/// Get second object involved in distance calculation
	virtual const Geometry& GetGeometry2() const = 0;
	/// Get distance between point and polyline
	virtual T GetDistance() const = 0;
	virtual ~mw2dIDistCalc() {}

protected:
private:
};

/// Interface class for Point-Polyline distance calculator in 2d
template <typename T>
class MW_5AXUTIL_API mw2dIDistCalcPointPolyline: public mw2dIDistCalc<T>
{
public:
	typedef typename mw2dIDistCalc<T>::Geometry Geometry;
	typedef mw2dPolyLine<T> PolyLine;
	typedef mwTPoint2d<T> Point;
	typedef typename misc::mwAutoPointer<mw2dIDistCalcPointPolyline<T>> Ptr;

	/// Get point object involved in distance calculation
	virtual const Geometry& GetGeometry1() const = 0;
	/// Get polyline object involved in distance calculation
	virtual const Geometry& GetGeometry2() const = 0;
	/// Get distance between point and polyline
	virtual T GetDistance() const = 0;
	/// Get witness point
	///
	/// Get closest point on the polyline to specified point
	///	@param dstPoint point on the polyline closest to specified point
	virtual void GetWitnessPoint(typename Point::Ptr& dstPoint) const = 0;
	virtual ~mw2dIDistCalcPointPolyline() {}

protected:
private:
};

/// Concrete class for Point-Polyline distance calculator in 2d
///
/// Object of this class should not be created directly
template <typename T>
class MW_5AXUTIL_API mw2dDistCalcPointPolyline: public mw2dIDistCalcPointPolyline<T>
{
public:
	typedef typename mw2dIDistCalcPointPolyline<T>::Point Point;
	typedef typename mw2dIDistCalcPointPolyline<T>::PolyLine PolyLine;
	typedef typename mw2dIDistCalcPointPolyline<T>::Geometry Geometry;
	mw2dDistCalcPointPolyline(const Point& pt, const PolyLine& pl)
	{
		m_pt = pt;
		m_pl = pl;
	}

	/// Get distance between point and polyline
	virtual T GetDistance() const
	{
		return (
			static_cast<T>(sqrt(cadcam::mwMinSquaredDistance::Calculate(m_pt.getTPoint(), m_pl))));
	}

	/// Get witness point
	///
	/// Get closest point on the polyline to specified point
	///	@param dst ptr to point on the polyline closest to specified point
	virtual void GetWitnessPoint(typename Point::Ptr& dst) const
	{
		dst = MW_NULL;
		if (m_pl.GetPointCount() < 2)
			return;

		typename PolyLine::PointListConstIt itC, itN, end = m_pl.GetPointEnd();
		itC = itN = m_pl.GetPointBegin();
		Point ret;
		T sqrDist = mathdef::mw_maxvalue(T(0));

		for (++itN; itN != end; ++itN, ++itC)
		{
			Point testPt(GetSegmentWitnessPoint((*itC)->getTPoint(), (*itN)->getTPoint()));
			Point distPt(testPt - m_pt.getTPoint());
			T testSqrDist = distPt * distPt;
			if (testSqrDist < sqrDist)
			{
				ret = testPt;
				sqrDist = testSqrDist;
			}
		}
		dst = new Point(ret);
		return;
	}

	/// Get mw2dPoint object involved in distance calculation
	virtual const Geometry& GetGeometry1() const { return m_pt; }

	/// Get mw2dPolyLine object involved in distance calculation
	virtual const Geometry& GetGeometry2() const { return m_pl; }

protected:
private:
	/// Get witness point on single line segment
	///	@param ps ptr to start point of line segment
	///	@param pe ptr to end point of line segment
	///	@returns witness point
	inline Point GetSegmentWitnessPoint(const Point& ps, const Point& pe) const
	{
		Point a = ps - m_pt.getTPoint();
		Point d = pe - ps;
		T t = -((a * d) / (d * d));
		if (t < 0.0)
			return ps;
		if (t > 1.0)
			return pe;
		return Point(ps + d * t);
	}

	PolyLine m_pl;
	mw2dPoint<T> m_pt;
};

/// Concrete class for oriented Point-Polyline distance calculator in 2d
///
/// Object of this class should not be created directly
template <typename T>
class MW_5AXUTIL_API mw2dOrientedDistCalcPointPolyline: public mw2dIDistCalcPointPolyline<T>
{
public:
	typedef typename mw2dIDistCalcPointPolyline<T>::PolyLine PolyLine;
	typedef typename mw2dIDistCalcPointPolyline<T>::Point Point;
	typedef typename mw2dIDistCalcPointPolyline<T>::Geometry Geometry;
	mw2dOrientedDistCalcPointPolyline(const mw2dPoint<T>& pt, const PolyLine& pl, const Point& dir)
		: m_pt(pt), m_pl(pl), m_dir(dir)
	{
	}

	/// Get distance between point and polyline
	virtual T GetDistance() const
	{
		return (
			static_cast<T>(sqrt(cadcam::mwMinSquaredDistance::Calculate(m_pt.getTPoint(), m_pl))));
	}

	/// Get witness point
	///
	/// Get closest point on the polyline to specified point
	///	@param dst ptr to point on the polyline closest to specified point
	virtual void GetWitnessPoint(typename Point::Ptr& dst) const
	{
		dst = MW_NULL;
		if (m_pl.GetPointCount() < 2)
			return;

		typename PolyLine::PointListConstIt itC, itN, end = m_pl.GetPointEnd();
		itC = itN = m_pl.GetPointBegin();
		Point ret;
		T sqrDist = mathdef::mw_maxvalue(T(0));

		for (++itN; itN != end; ++itN, ++itC)
		{
			Point testPt(getSegmentWitnessPoint(*itC, *itN));
			Point distPt(testPt - m_pt.getTPoint());
			T testSqrDist = distPt * distPt;

			if (testSqrDist < sqrDist && distPt * m_dir > 0.)
			{
				ret = testPt;
				sqrDist = testSqrDist;
			}
		}
		dst = new Point(ret);
		return;
	}

	/// Get mw2dPoint object involved in distance calculation
	virtual const Geometry& GetGeometry1() const { return m_pt; }

	/// Get mw2dPolyLine object involved in distance calculation
	virtual const Geometry& GetGeometry2() const { return m_pl; }

protected:
private:
	/// Get witness point on single line segment
	///	@param ps ptr to start point of line segment
	///	@param pe ptr to end point of line segment
	///	@returns witness point
	inline Point getSegmentWitnessPoint(const Point& ps, const Point& pe) const
	{
		Point a = ps - m_pt.getTPoint();
		Point d = pe - ps;
		T t = -((a * d) / (d * d));
		if (t < 0.0)
			return ps;
		if (t > 1.0)
			return pe;
		return Point(ps + d * t);
	}

	const PolyLine m_pl;
	const mw2dPoint<T> m_pt;
	const Point m_dir;
};

/// Factory for 2d distance calculators
template <typename T>
class MW_5AXUTIL_API mw2dDistCalcFactory
{
public:
	/// Create point-polyline distance calculator
	///
	/// Point-polyline distance calculator creation method
	///	@param g1 ref to 2d point to calculate distance to
	///	@param g2 ref to 2d polyline to calculate distance from
	///	@returns ptr to distance calculator interface
	virtual typename mw2dIDistCalcPointPolyline<T>::Ptr Create(
		const mwTPoint2d<T>& g1, const mw2dPolyLine<T>& g2) const
	{
		return new mw2dDistCalcPointPolyline<T>(g1, g2);
	}
};

/// Any distance calculator to PolyLine objects.
template <typename T>
class MW_5AXUTIL_API mw2dIDistCalcPolyLine
{
public:
	/// type name for PolyLine class.
	typedef mw2dPolyLine<T> PolyLine;
	/// type name for point class.
	typedef mwTPoint2d<T> Point;

	/// returns the PolyLine object.
	virtual const PolyLine& GetPolyLine() const = 0;

	///  returns the witness point the distance between two objects,
	/// the tValue and the segment index of the witness point of the polyline.
	virtual T GetDistance(
		const Point&, Point& witnessPoint, T& tValue, size_t& idxSegment) const = 0;

	/// virtual destructor.
	virtual ~mw2dIDistCalcPolyLine() {}
};

/// Abstract class to realize mw2dIDistCalcPolyLine.
template <typename T>
class MW_5AXUTIL_API mw2dDistCalcPolyLineBase: public mw2dIDistCalcPolyLine<T>
{
public:
	/// Store the const reference to the PolyLine object.
	typedef typename mw2dIDistCalcPolyLine<T>::PolyLine PolyLine;

	/// Constructor
	mw2dDistCalcPolyLineBase(const PolyLine& PolyLine): _PolyLine(PolyLine) {}

	/// returns the PolyLine object.
	virtual const PolyLine& GetPolyLine() const { return _PolyLine; }

	/// virtual destructor.
	virtual ~mw2dDistCalcPolyLineBase() {}

private:
	const PolyLine& _PolyLine;
	mw2dDistCalcPolyLineBase& operator=(mw2dDistCalcPolyLineBase&);  // avoid warning C4512
};

/// Any distance calculator to ClosedPolyLine objects.
template <typename T>
class MW_5AXUTIL_API mw2dIDistCalcClosedPolyLine
{
public:
	/// type name for ClosedPolyLine class.
	typedef mw2dPolyLine<T> ClosedPolyLine;
	/// type name for point class.
	typedef mwTPoint2d<T> Point;

	/// returns the ClosedPolyLine object.
	virtual const ClosedPolyLine& GetClosedPolyLine() const = 0;

	///  returns the witness point the distance between two objects,
	/// the tValue and the segment index of the witness point of the polyline.
	virtual T GetDistance(
		const Point&, Point& witnessPoint, T& tValue, size_t& idxSegment) const = 0;

	/// virtual destructor.
	virtual ~mw2dIDistCalcClosedPolyLine() {}
};

/// Abstract class to realize mw2dIDistCalcClosedPolyLine.
template <typename T>
class MW_5AXUTIL_API mw2dDistCalcClosedPolyLineBase: public mw2dIDistCalcClosedPolyLine<T>
{
public:
	typedef typename mw2dIDistCalcClosedPolyLine<T>::ClosedPolyLine ClosedPolyLine;
	/// Constructor
	mw2dDistCalcClosedPolyLineBase(const ClosedPolyLine& ClosedPolyLine)
		: _ClosedPolyLine(ClosedPolyLine)
	{
	}

	/// returns the ClosedPolyLine object.
	virtual const ClosedPolyLine& GetClosedPolyLine() const { return _ClosedPolyLine; }

	/// virtual destructor.
	virtual ~mw2dDistCalcClosedPolyLineBase() {}

private:
	/// Store the const reference to the ClosedPolyLine object.
	const ClosedPolyLine& _ClosedPolyLine;
	mw2dDistCalcClosedPolyLineBase& operator=(
		mw2dDistCalcClosedPolyLineBase&);  // avoid warning C4512
};
}  // namespace cadcam
#endif  // MW_MW2DIDISTCALC_HPP_
