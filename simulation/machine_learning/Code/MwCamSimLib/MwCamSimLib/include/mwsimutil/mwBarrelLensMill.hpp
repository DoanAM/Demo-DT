// (C) 2017-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELLENSMILL_HPP_
#define MW_MWBARRELLENSMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwBarrelLensMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelLensMill& toDump);

namespace cadcam
{
/// This class represents a barrel lens mill tool.
class MW_5AXUTIL_API mwBarrelLensMill: public mwTypedRevolvedTool
{
	/// @param os stream to serialize to
	/// @param toDump object of this class
	/// @return the resulting stream
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelLensMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;


	/// Default constructor
	///
	/// Constructs a barrel lens mill tool using default values for the tool parts.
	explicit mwBarrelLensMill(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwBarrelLensMill();

	/// Constructor
	///
	/// Constructs a barrel lens mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the tool holder.
	/// @param newShoulderLen is the length of the tool shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the tool arbor.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newConvexTipRadius is the convex tip radius of the constructed tool.
	/// @param units are the measurement units.
	mwBarrelLensMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const Units units);

	/// Constructor
	///
	/// Constructs a barrel lens mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the tool holder.
	/// @param newShoulderLen is the length of the tool shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the tool arbor.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newConvexTipRadius is the convex tip radius of the constructed tool.
	/// @param newShoulderDef is the new shoulder definition of the constructed tool.
	/// @param units are the measurement units.
	mwBarrelLensMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs a barrel lens mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newConvexTipRadius is the convex tip radius of the constructed tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwBarrelLensMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool.
	/// @param toCopy is the tool to be copied.
	mwBarrelLensMill(const mwBarrelLensMill& toCopy);


	//#########################  Gets  ############################################
	/// Gets the corner radius.
	///
	/// @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets the corner radius type.
	///
	/// @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Gets the convex tip radius of the tool.
	///
	/// @returns The convex tip radius of the tool.
	const double GetConvexTipRadius() const;
	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	/// @param toCopy is the tool from which the information is copied.
	/// @returns The current tool with the copied information.
	const mwBarrelLensMill& operator=(const mwBarrelLensMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwBarrelLensMill& toCompare) const;


	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise.
	bool operator!=(const mwBarrelLensMill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
	/// Scales this object (its measurable components)
	///
	/// @param units are the measurement units of this object.
	/// @param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data from mwBarrelLensMill
	void Copy(const mwBarrelLensMill& rToCopy);

	/// Checks the validity of the corner radius. A valid corner radius is greater than or equal to
	/// zero.
	///
	///	@param newCornerRad is the corner radius.
	///	@throws mwException if the corner radius is negative.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newDiameter is the tool's diameter.
	///	@param newCornerRadius is the tool's corner radius.
	///	@param newCovexTipRadius is the tool'S convex tip radius.
	void InternalConstructor(
		const double& newDiameter, const double& newCornerRadius, const double& newConvexTipRadius);

	/// Checks the validity of constraints that must be kept by the tool radii.
	///
	/// Triggers error if \f$ toolRadius-cornerRadius <= 0\f$ or \f$ convexTipRadius < toolRadius\f$
	///	@param diameter is the tool diameter.
	///	@param convexTipRadius is the convex tip radius of the tool.
	///	@param cornerRadius is the corner radius of the tool.
	void ValidateRadiiContraints(
		const double& diameter, const double& convexTipRadius, const double& cornerRadius) const;


	double m_cornerRadius;
	double m_convexTipRadius;
};
}  // namespace cadcam
#endif  //	MW_MWBARRELLENSMILL_HPP_
