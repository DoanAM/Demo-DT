// (C) 2007-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DMULTIPLECLOSEDPOLYLINE_HPP_
#define MW_MW2DMULTIPLECLOSEDPOLYLINE_HPP_
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMathConstants.hpp"

#include <list>
#include <utility>
#include <vector>


namespace cadcam
{
// serialize
template <typename T>
class MW_5AXUTIL_API mw2dMultipleClosedPolyLine;

template <class Archive, typename T>
void serialize(Archive& archive, mw2dMultipleClosedPolyLine<T>& mcp, unsigned int);
// end serialize

/// Class template implementing multiple polygon
/// (i.e. common boundary which includes holes/inner polygons)
template <typename T>
class MW_5AXUTIL_API mw2dMultipleClosedPolyLine
{
	// serialize
	template <class Archive, typename T2>
	friend void serialize(Archive& archive, mw2dMultipleClosedPolyLine<T2>& mcp, unsigned int);
	// end serialize

public:
	typedef mw2dPolyLine<T> Contour;
	typedef std::vector<Contour> ContourVec;
	typedef mw2dMultipleClosedPolyLine<T> MultiContour;
	typedef std::vector<MultiContour> MultiContourVec;
	typedef T ValueType;
	typedef mw2dBoundingBox<T> BoundingBox;


	typedef mw2dPolyLine<T> Polygon;  // Deprecated
	typedef std::vector<Polygon> PolygonVec;  // Deprecated
	typedef mw2dMultipleClosedPolyLine<T> MultiPolygon;  // Deprecated
	typedef std::vector<MultiPolygon> MultiPolygonVec;  // Deprecated


	mw2dMultipleClosedPolyLine();
	explicit mw2dMultipleClosedPolyLine(const Polygon& src);
	mw2dMultipleClosedPolyLine(const PolygonVec& src, const std::vector<size_t>& inclusionNumbers);

	void AddContour(const Contour& src);
	void RemoveContour(const size_t idx);
	void CalculateInclusionNumbers();
	void OrientContours(const bool isOuterClockWise = true);

	const Contour& GetContour(const size_t idx) const;
	const Contour& GetOuter() const;
	const ContourVec GetInners() const;
	const ContourVec GetHoles() const;
	const ContourVec& GetContours() const;

	const size_t GetContoursCount() const;
	const size_t GetInclusionNumber(const size_t idx) const;
	const size_t GetMaxInclusionNumber() const;


	void AddPolygon(const Polygon& src);  // Deprecated
	void RemovePolygon(const size_t idx);  // Deprecated
	void CalcHoleFlags();  // Deprecated
	const Polygon& GetPolygon(const size_t idx) const;  // Deprecated
	const Polygon& GetBoundary() const;  // Deprecated
	const PolygonVec& GetPolys() const;  // Deprecated
	const size_t GetPolyCount() const;  // Deprecated


	const bool IsInclusionNumbersCalculated() const;
	const bool IsOriented() const;
	const bool IsHole(const size_t idx) const;
	const bool IsEmpty() const;

	const bool operator==(const mw2dMultipleClosedPolyLine<T>& rhs) const;
	const bool operator!=(const mw2dMultipleClosedPolyLine<T>& rhs) const;

	const mw2dBoundingBox<T> GetBoundingBox() const;

private:
	PolygonVec m_contours;
	size_t m_outerContourIdx;
	std::vector<size_t> m_inclusionNumbers;
	bool m_isInclusionNumbersCalculated;
	bool m_isOriented;
};

/// Class template implementing multi-polyline builder
template <typename T>
class MW_5AXUTIL_API mw2dMultipleClosedPolyLineHelper
{
public:
	typedef mw2dPolyLine<T> Contour;
	typedef std::vector<Contour> ContourVec;
	typedef mw2dMultipleClosedPolyLine<T> MultiContour;
	typedef std::vector<MultiContour> MultiContourVec;


	typedef mw2dPolyLine<T> Polyline2d;  // Deprecated
	typedef std::vector<Polyline2d> PolylineVec;  // Deprecated
	typedef mw2dPolyLine<T> Polygon;  // Deprecated
	typedef std::vector<Polygon> PolygonVec;  // Deprecated
	typedef mw2dMultipleClosedPolyLine<T> MultiPolygon;  // Deprecated
	typedef std::vector<MultiPolygon> MultiPolygonVec;  // Deprecated


	class ReducePolyLine
	{
	public:
		explicit ReducePolyLine(T tol): m_tol(tol) {}

		void operator()(Polyline2d& src);

	private:
		T m_tol;
	};

	class ResolveIntersections
	{
	public:
		explicit ResolveIntersections(const T tolerance): m_tolerance(tolerance) {}

		void operator()(Polyline2d& src);

	private:
		T m_tolerance;
	};

	static void FilterAreaBased(MultiPolygonVec& src, const T cutTolerance);

	/// GetComplexPolygons
	///
	/// Extract multiple polygon set from the set of simple polygons
	///	@param[in] src simple polygon set
	/// @param[in] maxInclusionNum maximum depth of holes to be included into single element in result
	/// @param[in] validateInput check that input loops do not overlap with themselves and each other
	///	@return vector of multiple polygons
	static MultiPolygonVec GetComplexPolygons(
		const PolylineVec& src, const size_t maxInclusionNum = 0, const bool validateInput = false);

	/// Convert multiple polygons to limit inclusion number
	///
	///	@param[in,out] src polygon set to process
	///	@param[in] inclusionNum inclusion degree
	///	@note Inclusion number of 1 means getting set of polygons with
	///	only outer boundaries, 2 means boundaries with holes and no polygons
	///	inside these holes
	static void ConvertUsingMaxInclusionNumber(MultiContourVec& src, const size_t inclusionNum);

	/// Convert set of multiple polygons to set of polylines
	///
	///	@param[in] region of multiple polygons
	///	@return vector of polygons
	static ContourVec ConvertToPolylines(const MultiContourVec& region);

	/// Check if polygons are equal disregarding the order
	///
	/// Checks if polygons have equal vertices. Doesn't take
	///	polygons order and orientation into consideration
	///	@param src1 polygon #1 to compare
	///	@param src2 polygon #2 to compare
	///	@return bool true if polygons are equal
	static bool IsEqualNoOrder(const MultiContour& src1, const MultiContour& src2);

	static void CalculateInclusionNumbers(MultiContourVec& src);
	static void OrientContours(MultiContourVec& src);

private:
	mw2dMultipleClosedPolyLineHelper();
};
}  // namespace cadcam
#endif  //	MW_MW2DMULTIPLECLOSEDPOLYLINE_HPP_
