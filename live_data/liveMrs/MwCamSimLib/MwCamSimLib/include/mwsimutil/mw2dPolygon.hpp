// (C) 2004-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYGON_HPP_
#define MW_MW2DPOLYGON_HPP_
#include "mw2dBoundingBox.hpp"
#include "mwAutoPointer.hpp"
#include "mwException.hpp"
#include "mwTPoint2d.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <cmath>
#include <utility>
#include <vector>


namespace cadcam
{
class mw2dPolygon;


/// Polygon class
class MW_5AXUTIL_API mw2dPolygon
{
	/// Polygon point
	typedef mwTPoint2d<double> Point;
	/// Point array
	typedef std::vector<Point> PointArray;
	/// Point list
	typedef std::list<Point> PointList;
	/// Point list iterator
	typedef PointList::iterator PointIter;

	/// Contour axis-aligned bounding box
	typedef mw2dBoundingBox<double> Bound;
	/// Bound pointer.
	typedef Bound* BoundPtr;
	/// Bound list
	typedef std::vector<BoundPtr> BoundList;
	/// Bound list iterator
	typedef BoundList::iterator BoundIter;

	/// Represents the contour of simple polygon: array of points of the contour and pass-tracing.
	typedef std::pair<PointArray, bool> Contour;
	/// Represents the list of the simple contours.
	typedef std::vector<Contour> Contours;
	/// The geometry information about contour of this polygon.
	Contours contours;

public:
	/// Constructor
	mw2dPolygon() {}

	/// Destructor
	~mw2dPolygon() {}

	/// size function
	///
	///	@returns size of type size_t
	size_t size() const { return contours.size(); }

	/// clear function
	void clear() { contours.clear(); }

	/// getContour function
	///
	///	@param index of type size_t
	///	@returns getContour of type PointArray&
	PointArray& getContour(const size_t index) { return contours[index].first; }

	/// getContour function
	///
	/// @param index of type size_t
	/// @returns getContour of type const PointArray&
	const PointArray& getContour(const size_t index) const { return contours[index].first; }


	/// setContour function
	///
	///	@param index of type size_t
	///	@param value of type PointArray&
	void setContour(const size_t index, PointArray& value)
	{
		getContour(index).clear();
		getContour(index).resize(value.size(), Point());
		std::copy(value.begin(), value.end(), getContour(index).begin());
	}

	/// getIsHole function
	///
	///	@param index of type size_t
	///	@returns getIsHole of type bool
	bool getIsHole(const size_t index) { return contours[index].second; }

	/// setIsHole function
	///
	///	@param index of type size_t
	///	@param value of type bool
	///	@returns setIsHole of type void
	void setIsHole(const size_t index, bool value) { contours[index].second = value; }

	/// Read function
	///
	///	@param is of type std::istream &
	///	@param read_hole_flags of type bool
	///	@returns Read of type void
	void Read(std::istream& is, const bool read_hole_flags = false)
	{
		if (!is)
			throw int(0);
		size_t s;
		is >> s;
		for (size_t c = 0; c < s; c++)
		{
			this->AddContour();
			size_t _size;
			is >> _size;
			this->getContour(c).reserve(_size);
			for (size_t v = 0; v < _size; ++v)
			{
				double x, y;
				is >> x >> y;
				this->getContour(c).push_back(Point(x, y));
			}

			if (read_hole_flags)
			{
				is >> this->contours[c].second;
			}
			else
			{
				this->setIsHole(c, false);
			}
		}
	}

	/// Write function
	///
	///	@param os of type std::ostream&
	///	@param write_hole_flags of type bool
	///	@returns Write of type void
	void Write(std::ostream& os, const bool write_hole_flags = false)
	{
		if (!os)
			throw int(0);
		os << this->size() << std::endl;
		for (size_t c = 0; c < this->size(); ++c)
		{
			os << this->getContour(c).size() << std::endl;
			if (write_hole_flags)
				os << this->getIsHole(c) << std::endl;
			for (size_t v = 0; v < this->getContour(c).size(); v++)
			{
				os << this->getContour(c)[v].x() << _T(" ") << this->getContour(c)[v].y()
				   << std::endl;
			}
		}
	}

	/// Write AddContour
	///
	///	@param hole of type bool default value false
	void AddContour(bool hole = false) { contours.push_back(Contour(PointArray(), hole)); }

	/// CreateContourBound function
	///
	///	@returns CreateContourBound of type Bound
	Bound CreateContourBound() const
	{
		Bound box;
		if (!size())
			return box;
		box.SetCorners(getContour(0)[0], getContour(0)[0]);

		for (size_t c = 0; c < size(); ++c)
		{
			for (size_t j = 0; j < getContour(c).size(); ++j)
			{
				box.EnlargeForPoint(getContour(c)[j]);
			}
		}
		return box;
	}
};
}  // namespace cadcam
#endif  //	MW_MW2DPOLYGON_HPP_
