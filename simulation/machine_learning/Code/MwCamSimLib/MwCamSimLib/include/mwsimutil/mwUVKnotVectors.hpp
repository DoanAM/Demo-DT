// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWUVKNOTVECTORS_HPP_
#define MW_MWUVKNOTVECTORS_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc

namespace cadcam
{
/// This class represents a UV knot vector.
#pragma CACHING_INTERNAL_BEGIN
class MW_5AXUTIL_API mwUVKnotVectors
{
public:
	/// Constructor
	///
	/// Constructs a UV knot vector with given number of uKnots and vKnots
	///	If number of uKnots or vKnots < 1 an exception will be thrown
	///	@param uKnots const number of uKnots in the new UV knot vector
	///	@param vKnots const number of vKnots in the new UV knot vector
	mwUVKnotVectors(const size_t uKnots, const size_t vKnots);

	/// Resize UV knot vector
	///	@param uKnots const number of uKnots in the UV knot vector
	///	@param vKnots const number of vKnots in the UV knot vector
	void ResizeVectors(const size_t uKnots, const size_t vKnots);

	/// Get number of uKnots
	///	@returns const number of uKnots
	const size_t UKnots() const;

	/// Get number of vKnots
	///	@returns const number of uKnots
	const size_t VKnots() const;

	/// Get UKnot
	///
	/// Get UKnot from the vector with a given index
	///	If number of uKnots <= index  an exception will be thrown
	///	@param index const index of the UKnot
	///	@returns UKnot
	const double GetUKnot(const size_t index) const;

	/// Get VKnot
	///
	/// Get VKnot from the vector with a given index
	///	If number of vKnots <= index  an exception will be thrown
	///	@param index const index of the VKnot
	///	@returns VKnot
	const double GetVKnot(const size_t index) const;

	/// Set UKnot
	///
	/// Set UKnot with a given index
	///	If number of uKnots <= index  an exception will be thrown
	///	@param index position to set the UKnot in
	///	@param value UKnot value
	void SetUKnot(const size_t index, double value);

	/// Set VKnot
	///
	/// Set VKnot with a given index
	///	If number of vKnots <= index  an exception will be thrown
	///	@param index position to set the VKnot in
	///	@param value VKnot value
	void SetVKnot(const size_t index, double value);

	/// Get UKnot vector
	///	@returns UKnot vector
	const std::vector<double> GetUKnotVector() const;

	/// Get VKnot vector
	///	@returns VKnot vector
	const std::vector<double> GetVKnotVector() const;

private:
	std::vector<double> uKnot;
	std::vector<double> vKnot;
};
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MWUVKNOTVECTORS_HPP_
