// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWLOLMILL_HPP_
#define MW_MWLOLMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwLolMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwLolMill& toDump);

namespace cadcam
{
/// This class represents a lolipop mill tool.
class MW_5AXUTIL_API mwLolMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwLolMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwLolMill(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwLolMill();

	/// Constructor - deprecated - left for backwards compatibility. It has been replaced by
	/// constructors that contain the OutsideDiameter parameter.
	///
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param units are the units.
	/// @note This constructor is deprecated and instead should be used the  constructors  that
	/// have OutsideDiameter as parameter
	mwLolMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);

	/// Constructor
	///
	/// Constructs a lolipop mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newOutsideDiameter is the outside diameter of the tool.
	/// @param units are the units.
	mwLolMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newOutsideDiameter,
		const Units units);

	/// Constructor
	///
	/// Constructs a lolipop mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newOutsideDiameter is the new outside diameter of the tool.
	/// @param units are the units.
	mwLolMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newOutsideDiameter,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs an Lollipop mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newOutsideDiameter is the new outside diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwLolMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newOutsideDiameter,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	/// @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets corner radius type.
	///
	/// @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################
	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwLolMill& toCompare) const;

	/// Inequality operator.
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise
	bool operator!=(const mwLolMill& toCompare);


	const mwLolMill operator=(const mwLolMill& toCopy);

	/// Implements the visitor pattern.
	///
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;

	/// Gets the outside diameter of the tool.
	///
	/// @returns The outside diameter of the tool.
	const double GetOutsideDiameter() const;

protected:
	/// Scales this object (its measurable components)
	///
	/// @param units are the measurement units.
	/// @param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	void Copy(const mwLolMill& rToCopy);

	/// Gets the first diameter of an arbor.
	///
	/// @param arbor is the arbor from which the diameter is taken.
	/// @return The arbor's first diameter.
	double GetArborFirstDiameter(const ArborDefinition& arbor) const;

	/// Internal constructor to set member variables and perform validations.
	///
	/// @param newDiameter is the diameter of the tool.
	/// @param newOutsideDiameter is the new outside diameter of the tool.
	void InternalConstructor(const double& newDiameter, const double& newOutsideDiameter);

	/// Validates the diameter against the outside diameter.
	///
	/// Triggers exception if \f$ newOutsideDia > newDia \f$
	///	@param newDia is the new diameter.
	///	@param newOutsideDia is the new outside diameter.
	void ValidateDiameterVSOutsideDiameter(const double newDia, const double newOutsideDia) const;

	/// Check the validity of the tool's outside diameter.
	///
	/// Triggers exception if \f$ toValidate <= 0 \f$
	///	@param toValidate is the outside diameter to be validated.
	void ValidateOutsideDiameter(const double toValidate);

	/// Validates the tool's outside diameter against the shoulder diameter.
	///
	/// Triggers exception if \f$ shoulderDiameter <= outsideDiameter \f$
	///	@param outsideDiameter is outside diameter to be validated
	void ValidateOutsideDiameterVSShoulderDiameter(const double outsideDiameter) const;

	/// Checks the validity of the tool's flute length.
	///
	/// @param toolDiameter is the tool diameter used to validate the flute length.
	void ValidateFluteLength(const double& toolDiameter) const;

	/// Validates the tool's outside diameter against the zero value.
	///
	/// @param outsideDiameter is the tool diameter used for the validation.
	void ValidateOutsideDiameterAgainstZero(const double& outsideDiameter);

	double m_outsideDiameter;

	/// Visitor used for getting the first diameter from an arbor.
	class ArborFirstDiameterGetter: public mwRevolvedTool::SolidDefinitionVisitorGetter
	{
	public:
		/// Constructor
		///
		/// @param firstRadius returns the arbor's first radius.
		ArborFirstDiameterGetter();

		/// Return The arbor's first radius.
		double GetDiameter() const;

		virtual void Visit(const mwRevolvedTool::SolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::RevolvedSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ExtrudedSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::MeshSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::TurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::WireSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ContourTurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::PrimeTurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ThreadTapSolidDefinition& visitor);

	private:
		double m_diameter;
	};
};
}  // namespace cadcam
#endif  //	MW_MWLOLMILL_HPP_
