// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// helper (static) functions to help mwToolApproximation

#ifndef MW_MWTOOLAPPROXIMATIONHELPER_HPP_
#define MW_MWTOOLAPPROXIMATIONHELPER_HPP_
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedSolidDefinition.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwMesh.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwRevolvedTool.hpp"
#include "mwDeprecated.hpp"
#include "mwDefines.hpp"

namespace cadcam
{
//! Helper (static) functions to help mwToolApproximation
template <typename T>
class MW_5AXUTIL_API mwToolApproximationHelper
{
public:
	typedef mwTPoint2d<T>			TPoint2d;
	typedef	mw2dContour<T>			Contour2d;
	typedef mw2dPolyLine<T>			PolyLine2d;

	//! Splitting a tool profile in cutting and non cutting part
	/*!
		\param src the tool profile
		\param splitHeight the height at which to perform splitting
		\param cuttingPart resulting cutting part (output)
		\param nonCuttingPart resulting non cutting part (output)
	*/
	static void ExtractToolProfileParts(
				const Contour2d& src,
				const T& splitHeight,
				Contour2d& cuttingPart,
				Contour2d& nonCuttingPart);

	//! Splitting a tool profile in holder, arbor, cutting and non cutting part
	/*!
		\param src the tool profile
		\param arborCutHeight the height at which to perform splitting the Arbor
		\param nonCuttingCutHeight the height at which to perform splitting Non Cutting Part
		\param cuttingCutHeight the height at which to perform splitting Cutting Part (Flute)
		\param holderPart resulting holder part (output)
		\param arborPart resulting non arbor part (output)
		\param cuttingPart resulting cutting part (output)
		\param nonCuttingPart resulting non cutting part (output)
	*/
	static void ExtractToolProfileParts(
											const Contour2d& src,
											const T& cuttingCutHeight,
											const T& nonCuttingCutHeight,
											const T& arborCutHeight,
											Contour2d& cuttingPart,
											Contour2d& nonCuttingPart,
											Contour2d& arborPart,
											Contour2d& holderPart);

	//! Splitting a tool profile in arbor, cutting and non cutting part
	/*!
	\param src the tool profile
	\param nonCuttingCutHeight the height at which to perform splitting Non Cutting Part
	\param cuttingCutHeight the height at which to perform splitting Cutting Part (Flute)
	\param arborPart resulting non arbor part (output)
	\param cuttingPart resulting cutting part (output)
	\param nonCuttingPart resulting non cutting part (output)
	*/
	static void ExtractToolProfileParts(
		const Contour2d& src,
		const T& cuttingCutHeight,
		const T& nonCuttingCutHeight,
		Contour2d& cuttingPart,
		Contour2d& nonCuttingPart,
		Contour2d& arborPart);

	//! Translate the contour on Y Axis
	/*!Works with a 2d contour object
		\param src the contour to be shifted
		\param deltaY the offset with which the contour will be shifted
		\returns the translated contour
	*/
	static Contour2d ShiftContourOnY(const Contour2d& src, const T& deltaY);

	//! Translate the contour on Y Axis
	/*!Works with a 2d polyline object
		\param src the contour to be shifted
		\param deltaY the offset with which the contour will be shifted
		\returns the translated contour
	*/
	static PolyLine2d ShiftContourOnY(const PolyLine2d& src, const T& deltaY);

	//! Traslate the contour on X Axis
	/*!
		\param src the contour to be shifted
		\param deltaX the offset with which the contour will be shifted
		\returns the translated contour
	*/
	static Contour2d ShiftContourOnX(const Contour2d& src, const T& deltaX);

	//! Scale the contour 
	/*!
		\param src the contour to be scaled
		\param scaleFactor the scale factor to be used for scaling
		\returns the scaled contour
	*/
	static Contour2d ScaleContour(const Contour2d& src, const T& scaleFactor);

	//! Mirror the 2d contour at x or y axis
	/*!
		\param src the contour to be mirrored
		\param bAtXaxis if true, then mirror at x-axis, otherwise y-axis
		\returns the scaled contour
	*/
	static Contour2d MirrorContour(const Contour2d& src, bool bAtXaxis);

	//! Rotates the 2d contour
	/*!
		\param src the contour to be rotated
		\param angle 
		\returns the rotated contour
	*/
	static Contour2d RotateContour(const Contour2d& src, T angle = 0.0);

	// check the validation that is done in void mwToolPartProfileValidation::Check(const Profile& src),
	// this function tryes to prevent those errors to happen
	static void	RemoveFirstOrLastLineIfNotCorrect(Contour2d& src);

#ifndef MW_USE_VS2008_COMPATIBILITY
	//! Creates a GenericRevolvedTool object
	/*!
		\param cuttingPart - mesh pointer
		\param nonCuttingPart - mesh pointer
		\param arbor - mesh pointer
		\param holder - mesh pointer
		\param units This parameter is used to create an empty solid definition when solidMeshPtr is NULL, otherwise it is not used
		\returns a pointer to the new object
	*/
	static mwGenericRevolvedTool::Ptr CreateGenericRevolvedTool(
		misc::mwAutoPointer<mwTMesh<T>> cuttingPart,
		misc::mwAutoPointer<mwTMesh<T>> nonCuttingPart,
		misc::mwAutoPointer<mwTMesh<T>> arbor,
		misc::mwAutoPointer<mwTMesh<T>> holder,
		measures::mwUnitsFactory::Units units, 
		const T& tolerance = GetDefaultTolerance());

	//Helper function to be used together with CreateRevolvedSolidDefinition
	static T GetDefaultTolerance() {
		return mathdef::mw_maxvalue(T());
	}

	//! Creates an infinite interval, which will not effect the solid mesh, if used together with
	//! CreateRevolvedSolidDefinition
	static std::pair<T, T> CreateUnboundedInterval()
	{
		return std::make_pair(
			-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
	}

	//! Creates a left bounded interval, which will cut the solid mesh at bottom of the mesh, if
	//! used together with CreateRevolvedSolidDefinition
	static std::pair<T, T> CreateLowerBoundedInterval(const T& lower)
	{
		return std::make_pair(lower, std::numeric_limits<T>::infinity());
	}

	//! Creates a right bounded interval, which will cut the solid mesh at top of the mesh, if used
	//! together with CreateRevolvedSolidDefinition
	static std::pair<T, T> CreateUpperBoundedInterval(const T& upper)
	{
		return std::make_pair(-std::numeric_limits<T>::infinity(), upper);
	}

	//! Creates an on both sides bounded interval, which will cut the solid mesh at bottom and top
	//! of the mesh, if used together with CreateRevolvedSolidDefinition
	static std::pair<T, T> CreateBoundedInterval(const T& lower, const T& upper)
	{
		return (lower < upper) ? std::make_pair(lower, upper) : std::make_pair(upper, lower);
	}

	//! Creates a mwRevolvedSolidDefinition object
	/*!
	\param solidMesh - mesh
	\param interval - the interval in which the mesh is used for revolved solid creation
	\param useTopPolylineAlgorithm - Top polyline algorithm is faster and numerically more stable, but fills undercuts
	\returns a pointer to the new object
	*/
	static typename mwRevolvedSolidDefinition<T>::Ptr CreateRevolvedSolidDefinition(
		const mwTMesh<T>& solidMesh,
		const std::pair<T, T>& interval = mwToolApproximationHelper<T>::CreateUnboundedInterval(),
		const T& tolerance = GetDefaultTolerance(),
		const bool useTopPolylineAlgorithm = false,
		const bool forceSolidInOrigin = false);

	//! Creates a mwRevolvedSolidDefinition object
	/*!
	\see CreateRevolvedSolidDefinition
	\param units This parameter is used to create an empty solid definition when solidMeshPtr is NULL, otherwise it is not used
	\note Function returns RevolvedSolidDefinition(units), when solidMeshPtr is NULL
	*/
	MW_DEPRECATED("Deprecated since 2018.12, please use CreateRevolvedSolidDefinition(...) without units")
	static typename mwRevolvedSolidDefinition<T>::Ptr CreateRevolvedSolidDefinition(
		misc::mwAutoPointer<mwTMesh<T>> solidMeshPtr,
		measures::mwUnitsFactory::Units units,
		const std::pair<T, T>& interval = mwToolApproximationHelper<T>::CreateUnboundedInterval(),
		const T& tolerance = GetDefaultTolerance())
	{
		if (solidMeshPtr.IsNull()) {
			return new mwRevolvedSolidDefinition<T>(units);
		} else {
			return CreateRevolvedSolidDefinition(*solidMeshPtr, interval, tolerance);
		}
	}
#endif

private:
	//!Shift a generic contour geometry on Y
	/*
		\param src is input contour geometry to be shifted
		\param deltaY is amount used to shift on Y
		\return shifted contour geometry
	*/
	template <class ContourGeo>
	static ContourGeo GenericShiftContourOnY(const ContourGeo& src, const T& deltaY);

	//! Constructor not allowed since it's a static class
	mwToolApproximationHelper();
};

} // cadcam namespace
#endif	//	MW_MWTOOLAPPROXIMATIONHELPER_HPP_
