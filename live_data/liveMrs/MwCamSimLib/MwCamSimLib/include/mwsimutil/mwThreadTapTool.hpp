// (C) 2019-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_mwThreadTapTool_HPP_
#define MW_mwThreadTapTool_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include <iostream>


namespace cadcam
{
class mwThreadTapTool;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwThreadTapTool& toDump);

namespace cadcam
{
/// @class mwThreadTapTool
/// This class represents an Thread Tap tool.
class MW_5AXUTIL_API mwThreadTapTool: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwThreadTapTool& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	enum ThreadType  // Type of how threads are defined
	{
		TT_PITCH,  // use thread pitch distance
		TT_TPI  // use number of threads per inch
	};

	enum ThreadDirection  // Thread direction
	{
		TD_LEFT_HANDED,
		TD_RIGHT_HANDED
	};

	enum CoreDiameterType  // Core diameter type
	{
		CDT_AUTOMATIC,  // value computed automatically based on other tool elements
		CDT_USER_DEFINED  // user defined value
	};
	/// Default constructor
	explicit mwThreadTapTool(const Units units = Units::METRIC);

	/// Constructs an Thread Tap tool using the given parameters.
	/// @param diameter is the diameter of the constructed tool.
	/// @param holder is the holder.
	/// @param shoulderLen is the shoulder length.
	/// @param fluteLen is the flute length.
	/// @param arbor is the arbor diameter of the tool.
	/// @param threadType is type of threads (pitch/TPI)
	/// @param pitch is distance between 2 neighbor crests of threads
	/// @param TPI is number of threads per inch
	/// @param threadDirection is thread direction of the tool
	/// @param units are the units.
	mwThreadTapTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLen,
		const double fluteLen,
		const ArborDefinition& arbor,
		const ThreadType threadType,
		const double pitch,
		const double TPI,
		const ThreadDirection threadDirection,
		const Units units);

	/// Constructs an Thread Tap tool using the given parameters.
	/// @param diameter is the diameter of the constructed tool.
	/// @param holder is the holder.
	/// @param shoulderLen is the shoulder length.
	/// @param fluteLen is the flute length.
	/// @param arbor is the arbor diameter of the tool.
	/// @param shoulderDefinition is the shoulder definition of the tool.
	/// @param threadType is type of threads (pitch/TPI)
	/// @param pitch is distance between 2 neighbor crests of threads
	/// @param TPI is number of threads per inch
	/// @param threadDirection is thread direction of the tool
	/// @param units are the units.
	mwThreadTapTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLen,
		const double fluteLen,
		const ArborDefinition& arbor,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const ThreadType threadType,
		const double pitch,
		const double TPI,
		const ThreadDirection threadDirection,
		const Units units);

	/// Constructs an Thread Tap tool using the given parameters.
	/// @param diameter is the diameter of the constructed tool.
	/// @param holder is the holder.
	/// @param shoulderLen is the shoulder length.
	/// @param fluteLen is the flute length.
	/// @param arbor is the arbor diameter of the tool.
	/// @param threadType is type of threads (pitch/TPI)
	/// @param pitch is distance between 2 neighbor crests of threads
	/// @param TPI is number of threads per inch
	/// @param threadDirection is thread direction of the tool
	/// @param coreDiameterType is type of core diameter
	/// @param coreDiameter is value of core diameter
	/// 	If coreDiameterType is CDT_AUTOMATIC,passed coreDiameter is ignored and automatically
	/// computed based on other tool elements 	Calculation formula in automatic mode: 	    In case of
	/// thread type Pitch : Core Diameter = Diameter - pitch 		In case of thread type TPI :   Core
	/// Diameter = Diameter - (25.4/TPI) 	If coreDiameterType is CDT_USER_DEFINED,passed coreDiameter
	/// is used as the value for core diameter element
	/// @param units are the units.
	mwThreadTapTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLen,
		const double fluteLen,
		const ArborDefinition& arbor,
		const ThreadType threadType,
		const double pitch,
		const double TPI,
		const ThreadDirection threadDirection,
		const CoreDiameterType coreDiameterType,
		const double coreDiameter,
		const Units units);

	/// Constructs an Thread Tap tool using the given parameters.
	/// @param diameter is the diameter of the constructed tool.
	/// @param holder is the holder.
	/// @param shoulderLen is the shoulder length.
	/// @param fluteLen is the flute length.
	/// @param arbor is the arbor diameter of the tool.
	/// @param shoulderDefinition is the shoulder definition of the tool.
	/// @param threadType is type of threads (pitch/TPI)
	/// @param pitch is distance between 2 neighbor crests of threads
	/// @param TPI is number of threads per inch
	/// @param threadDirection is thread direction of the tool
	/// @param coreDiameterType is type of core diameter
	/// @param coreDiameter is value of core diameter
	/// 	If coreDiameterType is CDT_AUTOMATIC,passed coreDiameter is ignored and automatically
	/// computed based on other tool elements 	Calculation formula in automatic mode: 	    In case of
	/// thread type Pitch : Core Diameter = Diameter - pitch 		In case of thread type TPI :   Core
	/// Diameter = Diameter - (25.4/TPI) 	If coreDiameterType is CDT_USER_DEFINED,passed coreDiameter
	/// is used as the value for core diameter element
	/// @param units are the units.
	mwThreadTapTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLen,
		const double fluteLen,
		const ArborDefinition& arbor,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const ThreadType threadType,
		const double pitch,
		const double TPI,
		const ThreadDirection threadDirection,
		const CoreDiameterType coreDiameterType,
		const double coreDiameter,
		const Units units);

	~mwThreadTapTool();

	/// Creates an exact copy of the tool.
	/// @param toCopy is the tool that you want to copy.
	mwThreadTapTool(const mwThreadTapTool& toCopy);


	/// Gets type of tool's thread ( pitch or TPI)
	///
	///	@return type of tool's threads
	ThreadType GetThreadType() const;

	/// Get thread pitch
	///
	/// Get distance between two neighbor crests of the thread in current measurement units
	///	 @returns thread pitch
	double GetPitch() const;

	/// Get TPI (threads per inch)
	///
	/// Get how many threads exists along one inch length of the tool
	///	 @returns threads per inch
	double GetTPI() const;

	/// Get thread direction
	///
	///	@returns thread direction
	ThreadDirection GetThreadDirection() const;

	/// Assigns one tool object to another.
	/// @param toCopy is the tool from which the information will be to copied.
	/// @returns The current tool with the copied information.

	/// Gets type of core diameter (auto,custom)
	///
	///	@return type of tool's core diameter
	CoreDiameterType GetCoreDiameterType() const;

	/// Get value or core (inner) diameter of the tool
	///
	/// This is the diameter of tool without threads
	///	 @returns core diameter
	double GetCoreDiameter() const;

	const mwThreadTapTool& operator=(const mwThreadTapTool& toCopy);

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwThreadTapTool& toCompare) const;

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise.
	bool operator!=(const mwThreadTapTool& toCompare);

	/// Implements the visitor pattern
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
	/// Scale the tool.
	/// @param units are the units.
	/// @param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data from another mwThreadTapTool
	/// @param toCopy source tool from which the data will be copied into this object
	void Copy(const mwThreadTapTool& toCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param diameter is the diameter of the constructed tool.
	///	@param threadType is type of threads (pitch/TPI)
	///	@param pitch is distance between 2 neighbor crests of threads
	///	@param TPI is number of threads per inch
	///	@param threadDirection is thread direction of the tool
	void InternalConstructor(
		const double diameter,
		const ThreadType threadType,
		const double pitch,
		const double TPI,
		const ThreadDirection threadDirection,
		const CoreDiameterType coreDiameterType,
		const double coreDiameter);

	/// Validates thread type
	///
	///	@param toValidate is thread type to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidateThreadType(const ThreadType toValidate) const;

	/// Validates thread pitch
	///
	///	@param toValidate is thread pitch to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidatePitch(const double toValidate) const;

	/// Validates TPI (threads per inch)
	///
	///	@param toValidate is TPI to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidateTPI(const double toValidate) const;
	/// Validates thread direction
	///
	///	@param toValidate is parameter to be validated
	///	throws exception if parameter to be validated is not valid
	void ValidateThreadDirection(const ThreadDirection toValidate) const;

	/// Compute core diameter based on other tool information
	///
	///	@param diameter is tool diameter
	///	@param threadType is thread type (pitch,TPI)
	///	@param pitch is thread pitch value
	///	@param TPI is thread TPI value
	///	throws exception if a valid core diameter cannot be computed
	double ComputeCoreDiameter(
		const double diameter,
		const ThreadType threadType,
		const double pitch,
		const double TPI) const;

	/// Validates core (inner) diameter
	///
	///	@param toValidate is core diameter to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidateCoreDiameter(const double toValidate) const;


	/// Checks whether the relationship between core diameter and tool diameter is valid.
	///
	///	@param coreDiameter is tool core diameter
	///	@param diameter is tool diameter
	///	@throws exception if relationship between elements to be validated doesn't hold.
	void ValidateCoreDiameterVSDiameter(const double coreDiameter, const double diameter) const;

	/// Checks whether the relationship between thread pitch and tool diameter is valid.
	///
	///	@param pitch is thread pitch value
	///	@param diameter is tool diameter
	///	@throws exception if relationship between elements to be validated doesn't hold.
	void ValidatePitchVSDiameter(const double pitch, const double diameter) const;

	/// Validates core diameter type
	///
	///	@param toValidate is parameter to be validated
	///	throws exception if parameter to be validated is not valid
	void ValidateCoreDiameterType(const CoreDiameterType toValidate) const;

	/// Members
	ThreadType m_threadType;
	double m_pitch;
	double m_TPI;
	ThreadDirection m_threadDirection;
	CoreDiameterType m_coreDiameterType;
	double m_coreDiameter;
};
}  // namespace cadcam
#endif  //	MW_mwThreadTapTool_HPP_
