// (C) 2007-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DCURVE_HPP_
#define MW_MW2DCURVE_HPP_
#include "mw2dBoundingBox.hpp"
#include "mw2dGeometry.hpp"
#include "mw2dPoint.hpp"
#include "mwMathConstants.hpp"

#include <cmath>
#include <vector>

#define MW2DCURVE_DEFAULT_POINT_REQUESTED 50

namespace cadcam
{
template <typename T>
class mw2dCurveVisitor;

/// Implements a 2D generic curve
///
/// Here is just the interface, the implementation is in WMAdapters
template <class T>
class MW_5AXUTIL_API mw2dCurve: public mw2dGeometry<T>
{
public:
	// Linux specific
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	// Linux specific

	typedef mwTPoint2d<T> TPoint;
	typedef cadcam::mw2dPoint<T> CurveControlPoint;
	typedef std::vector<CurveControlPoint> CurveControlPointsVec;
	typedef cadcam::mw2dPolyLine<T> Polyline2d;
	typedef std::vector<Polyline2d> Polyline2dVec;

	mw2dCurve() {}

	/// Get curve length
	virtual T GetLength() const = 0;
	/// Get curve area
	virtual T GetArea() const = 0;
	/// Get curve degree
	virtual int GetDegree() const = 0;
	/// Set curve degree
	virtual void SetDegree(int iDegree) = 0;
	/// Get curve control points
	virtual void GetControlPoints(CurveControlPointsVec& mkCtrlPoints) const = 0;
	/// Set curve control points
	virtual void SetControlPoints(const CurveControlPointsVec& mwCtrlPoints) = 0;
	/// Setup curve
	///
	/// Setup curve post creation
	///	@param iDegree Curve degree
	///	@param mwCtrlPoints the list of control points
	virtual void SetupCurve(int iDegree, const CurveControlPointsVec& mwCtrlPoints) = 0;
	using mw2dGeometry<T>::AcceptVisitor; // import overloads from baseclass
	virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }
	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw2dCurveVisitor<T>& visitor) = 0;
	virtual void AcceptVisitor(const mw2dCurveVisitor<T>& visitor) const = 0;
	/// Get curve start point
	virtual const TPoint& GetStartPoint() const = 0;
	/// Get curve end point
	virtual const TPoint& GetEndPoint() const = 0;
	/// Is curve continuous?
	virtual bool IsContinuous(const T tolerance = 0) const = 0;
	static size_t GetDefaultOutputPointCount() { return MW2DCURVE_DEFAULT_POINT_REQUESTED; }
	// transient methods
	virtual void ComputeCurvePoints(
		size_t outputPointCount, CurveControlPointsVec& mwCtrlPoint) const = 0;
	virtual void ComputeCurvePoints(size_t outputPointCount, Polyline2d& polyline) const = 0;
	virtual void GetTangentsList(Polyline2dVec& mkPolyLines) const = 0;

protected:
	/// CalculateBoundingBox method calculates the bounding box
	virtual inline void CalculateBoundingBox() = 0;
};
}  // namespace cadcam
#endif  //	MW_MW2DCURVE_HPP_
