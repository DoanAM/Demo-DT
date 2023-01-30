// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLHELPER_HPP_
#define MW_MWTOOLHELPER_HPP_
#include "mwArborDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwTool.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwToolHelper
{
public:
	typedef typename measures::mwUnitsFactory::Units Units;
	typedef mwTPoint2d<T> Point2d;

	/// Creates a holder from a cylinder.
	///
	/// @param diameter is the diameter of the cylinder.
	/// @param height is the height of the cylinder.
	/// @param units units to be used
	static mwHolderDefinition<T> CreateHolderAsCylinder(
		const T& diameter, const T& height, const Units units);

	/// Creates an arbor from a cylinder.
	///
	/// @param diameter is the diameter of the cylinder.
	/// @param height is the height of the cylinder.
	/// @param units units to be used
	static mwArborDefinition<T> CreateArborAsCylinder(
		const T& diameter, const T& height, const Units units);

	/// Creates a profile from a cylinder.
	///
	/// @param diameter is the diameter of the cylinder.
	/// @param height is the height of the cylinder.
	static typename mwRevolvedSolidDefinition<T>::PolyLine CreateProfileAsCylinder(
		const T& diameter, const T& height);

	/// Creates a holder from a truncated cone.
	///
	/// @param lowerDiameter is the lower diameter of the truncated cone.
	/// @param upperDiameter is the upper diameter of the truncated cone.
	/// @param height is the height of the truncated cone.
	/// @param units units to be used
	static mwHolderDefinition<T> CreateHolderAsTruncatedCone(
		const T& lowerDiameter, const T& upperDiameter, const T& height, const Units units);

	/// Creates an arbor from a truncated cone.
	///
	/// @param lowerDiameter is the lower diameter of the truncated cone.
	/// @param upperDiameter is the upper diameter of the truncated cone.
	/// @param height is the height of the truncated cone.
	/// @param units units to be used
	static mwArborDefinition<T> CreateArborAsTruncatedCone(
		const T& lowerDiameter, const T& upperDiameter, const T& height, const Units units);

	/// Creates a profile from a truncated cone.
	///
	/// @param lowerDiameter is the lower diameter of the truncated cone.
	/// @param upperDiameter is the upper diameter of the truncated cone.
	/// @param height is the height of the truncated cone.
	static typename mwRevolvedSolidDefinition<T>::PolyLine CreateProfileAsTruncatedCone(
		const T& lowerDiameter, const T& upperDiameter, const T& height);

	/// Creates a holder from a list of 2D points.
	///
	///	@param pointList is the list containing the points.
	///	@param pListSize is the size of the list containing the points.
	///	@param units are the measurement units for the new holder.
	///	@return The new HolderDefinition.
	static mwHolderDefinition<T> CreateHolderFromPoints(
		const Point2d pointList[], const int pListSize, const Units units);

	/// Creates an arbor from a list of 2D points.
	///
	///	@param pointList is the list containing the points.
	///	@param pListSize is the size of the list containing the points.
	///	@param units are the measurement units for the new arbor.
	///	@return the new ArborDefinition.
	static mwArborDefinition<T> CreateArborFromPoints(
		const Point2d pointList[], const int pListSize, const Units units);

	/// Creates an shaft from a list of 2D points.
	///
	///	@param pointList is the list containing the points.
	///	@param pListSize is the size of the list containing the points.
	///	@param units are the measurement units for the new shaft.
	///	@return the new ShaftDefinition.
	static mwNonCuttingPartDefinition<T> CreateShaftFromPoints(
		const Point2d pointList[], const int pListSize, const Units units);

	/// Check whether mwTool::GetHolder can be called for a given tool.
	///
	///	@param tool is the mwTool that should be inspected.
	///	@return true if GetHolder would return a holder (that might be empty).
	static bool HasHolder(const mwTool& tool);

	/// Check whether mwTool::GetArbor can be called for a given tool.
	///
	///	@param tool is the mwTool that should be inspected.
	///	@return true iff GetArbor would return an arbor (that might be empty).
	static bool HasArbor(const mwTool& tool);

private:
	/// Create a revolved solid definition from a given list of points.
	///
	///	@param pointList is the list containing the points.
	///	@param pListSize is the size of the list containing the points.
	///	@param units are the measurement units for the new profile.
	///	@return the new solid definition.
	static mwRevolvedSolidDefinition<T> CreateRevolvedSolidFromPoints(
		const Point2d pointList[], const int pListSize, const Units units);

	/// Constructor is not allowed because it is a static class.
	mwToolHelper();
};

typedef cadcam::mwToolHelper<double> ToolHelper;
}  // namespace cadcam
#endif  //	MW_MWTOOLHELPER_HPP_
