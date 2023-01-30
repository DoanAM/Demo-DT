// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWTHREADMILLSINGLEFORMTOOL_HPP_
#define MW_MWTHREADMILLSINGLEFORMTOOL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include <iostream>


namespace cadcam
{
class mwThreadMillSingleFormTool;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwThreadMillSingleFormTool& toDump);

namespace cadcam
{
/// @class mwThreadMillSingleFormTool
/// This class represents a thread mill single form tool (used for HoleMaking/ThreadMilling cycles).
/// Tool contains a single cutting thread
class MW_5AXUTIL_API mwThreadMillSingleFormTool: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwThreadMillSingleFormTool& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	
	/// Default constructor
	///Constructs a thread mill single form tool with default parameters for Metric measurement units
	mwThreadMillSingleFormTool();

	/// Constructs a thread mill single form tool with default parameters for given measurement units
	/// @param units area measurement units of tool
	explicit mwThreadMillSingleFormTool(const Units units);

	/// Destructor
	virtual ~mwThreadMillSingleFormTool();

	/// Constructs a thread mill single form tool using the given parameters.
	/// @param diameter is outer (maximal) diameter of cutting part (includes cutting thread)
	/// @param holder is tool holder definition
	/// @param shoulderLength is tool should length
	/// @param fluteLength is tool flute length
	/// @param arbor is tool arbor definition
	/// @param coreDiameter is inner diameter of cutting part (not including cutting thread)
	/// @param threadAngle is angle in degree for the tooth of cutting part
	/// @param units are the units.
	mwThreadMillSingleFormTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLength,
		const double fluteLength,
		const ArborDefinition& arbor,
		const double coreDiameter,
		const double threadAngle,
		const Units units);
	
	/// Constructs a thread mill single form tool using the given parameters.
	/// Creates a tool with shaft either as cylindrical (default) or as cylindrical+conical
	/// using shoulderDefinition parameter
	/// @param diameter is outer (maximal) diameter of cutting part (includes cutting thread)
	/// @param holder is tool holder definition
	/// @param shoulderLength is tool should length
	/// @param fluteLength is tool flute length
	/// @param arbor is tool arbor definition
	/// @param coreDiameter is inner diameter of cutting part (not including cutting thread)
	/// @param threadAngle is angle in degree for the tooth of cutting part
	/// @param shoulderDefinition is tool shoulder definition
	/// @param units are the units.
	mwThreadMillSingleFormTool(
		const double diameter,
		const HolderDefinition& holder,
		const double shoulderLength,
		const double fluteLength,
		const ArborDefinition& arbor,
		const double coreDiameter,
		const double threadAngle,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs a thread mill single form tool using the given parameters.
	/// Creates a tool with a custom definition of non-cutting part (shaft)
	/// @param diameter is outer (maximal) diameter of cutting part (includes cutting thread)
	/// @param holder is tool holder definition
	/// @param fluteLength is tool flute length
	/// @param arbor is tool arbor definition
	/// @param coreDiameter is inner diameter of cutting part (not including cutting thread)
	/// @param threadAngle is angle in degree for the tooth of cutting part
	/// @param shaftDefinition is tool shaft definition
	/// @param units are the units.
	mwThreadMillSingleFormTool(
		const double diameter,
		const HolderDefinition& holder,
		const double fluteLength,
		const ArborDefinition& arbor,
		const double coreDiameter,
		const double threadAngle,
		const NonCutPartDefinition& shaftDefinition,
		const Units units);

	/// Get value of tool's core diameter
	/// This is inner diameter of cutting part (not including cutting thread)
	/// 
	/// @returns core diameter
	double GetCoreDiameter() const;

	/// Get angle in degrees of cutting thread profile
	/// @returns thread angle in degrees
	double GetThreadAngle() const;

	/// Creates an exact copy of the tool.
	/// @param toCopy is the tool that you want to copy.
	mwThreadMillSingleFormTool(const mwThreadMillSingleFormTool& toCopy);

	/// Assigns one tool object to another.
	/// @param toCopy is the tool from which the information will be to copied.
	/// @returns The current tool with the copied information.
	const mwThreadMillSingleFormTool& operator=(const mwThreadMillSingleFormTool& toCopy);

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwThreadMillSingleFormTool& toCompare) const;

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise.
	bool operator!=(const mwThreadMillSingleFormTool& toCompare);

	/// Implements the visitor pattern
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Customize test for an advanced shoulder definition for this tool
	/// Overrides base class mwTypedRevolvedTool check since this tool has another test
	///	@return <b>True</b> is this tool has an advanced shoulder definition
	///			<b>false</b> otherwise
	virtual const bool HasAdvancedShoulderDefinition() const;

protected:
	/// Scale the tool.
	/// @param units are the units.
	/// @param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);
private:
	/// Copies the data from another mwThreadMillSingleFormTool to this object
	/// @param src is source tool from which the data will be copied.
	void Copy(const mwThreadMillSingleFormTool& src);

	/// Internal constructor to set member variables and perform validations.
	///
	/// @param diameter is outer (maximal) diameter of cutting part (includes cutting tooth)
	/// @param fluteLength is tool flute length
	/// @param coreDiameter is inner diameter of cutting part (not including cutting tooth)
	/// @param threadAngle is angle in degree for the tooth of cutting part
	///	@throws exception if passed parameters don't define a valid tool
	void InternalConstructor(
		const double diameter,
		const double fluteLength,
		const double coreDiameter,
		const double threadAngle);

	/// Validates core (inner) diameter of tool
	///
	///	@param toValidate is core diameter to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidateCoreDiameter(const double toValidate) const;

	/// Validates thread angle of tool
	///
	///	@param toValidate is thread angle to be validated
	///	@throws exception if parameter to be validated is not valid
	void ValidateThreadAngle(const double toValidate) const;

	/// Validates dependencies between parameters
	/// @param diameter is tool diameter
	/// @param fluteLength is tool flute length
	/// @param coreDiameter is core diameter
	/// @param threadAngle is tool's thread angle
	///	@throws exception if dependencies between parameters don't keep
	void ValidateParamDependencies(
		const double diameter,
		const double fluteLength,
		const double coreDiameter,
		const double threadAngle) const;

	/// Adjusts m_shaftType parameter in base class mwTypedRevolvedTool 
	/// based on HasAdvancedShoulderDefinition function of this class which overrides base class condition
	void AjustShaftType();

	/// Members
	double m_coreDiameter;
	double m_threadAngle;
};
}  //  namespace cadcam
#endif  //	MW_MWTHREADMILLSINGLEFORMTOOL_HPP_
