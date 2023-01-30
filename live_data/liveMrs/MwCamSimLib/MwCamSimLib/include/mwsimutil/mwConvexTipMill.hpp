// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCONVEXTIPMILL_HPP_
#define MW_MWCONVEXTIPMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwConvexTipMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwConvexTipMill& toDump);

namespace cadcam
{
/// This class represents a convex tip mill tool.
class MW_5AXUTIL_API mwConvexTipMill: public mwTypedRevolvedTool
{
	/// Serialize the class data
	/// @param os stream to serialize to
	/// @param toDump object of this class
	/// @return the resulting stream
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwConvexTipMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	/// Default constructor
	///
	/// Constructs a convex tip mill tool using default values for the tool parts.
	explicit mwConvexTipMill(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwConvexTipMill();

	/// Constructor
	///
	/// Constructs a convex tip mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the tool holder.
	/// @param newShoulderLen is the length of the tool shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the tool arbor.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newConvexTipRadius is the convex tip radius of the constructed tool.
	///	    @param flatnessRadius is the flatness radius of the tool.
	/// @param units are the measurement units.
	mwConvexTipMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const double& flatnessRadius,
		const Units units);

	/// Constructor
	///
	/// Constructs a convex tip mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the tool holder.
	/// @param newShoulderLen is the length of the tool shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the tool arbor.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newConvexTipRadius is the convex tip radius of the constructed tool.
	///	    @param flatnessRadius is the flatness radius of the tool.
	/// @param newShoulderDef is the new shoulder definition of the constructed tool.
	/// @param units are the measurement units.
	mwConvexTipMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const double& flatnessRadius,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs an end mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwConvexTipMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const double& flatnessRadius,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool.
	/// @param toCopy is the tool to be copied.
	mwConvexTipMill(const mwConvexTipMill& toCopy);


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


	/// Gets the flatness radius of the tool.
	///
	/// @returns The flatness radius of the tool.
	const double GetFlatnessRadius() const;
	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	/// @param toCopy is the tool from which the information is copied.
	/// @returns The current tool with the copied information.
	const mwConvexTipMill& operator=(const mwConvexTipMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwConvexTipMill& toCompare) const;


	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise.
	bool operator!=(const mwConvexTipMill& toCompare);

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
	/// Copies the data from mwConvexTipMill
	void Copy(const mwConvexTipMill& rToCopy);

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
	///	@param flatnessRadius is the flatness radius for the tool.
	void InternalConstructor(
		const double& newDiameter,
		const double& newCornerRadius,
		const double& newConvexTipRadius,
		const double& flatnessRadius);

	/// Checks the validity of constraints that must be kept by the tool radii.
	///
	/// Triggers error if \f$ toolRadius-cornerRadius <= flatRadius \f$ or 
	/// \f$ convexTipRadius < toolRadius-flatRadius  \f$
	///	@param diameter is the tool diameter.
	///	@param convexTipRadius is the convex tip radius of the tool.
	///	@param cornerRadius is the corner radius of the tool.
	///	@param flatnessRadius is the flatness radius of the tool.
	void ValidateRadiiContraints(
		const double& diameter,
		const double& convexTipRadius,
		const double& cornerRadius,
		const double& flatnessRadius) const;

	/// Checks the validity of the flatness radius. A valid flatness radius is greater than or equal
	/// to zero.
	///
	///	@param toValidate is the flatness radius to be validated.
	///	@throws mwException if the flatness radius is not valid.
	void ValidateFlatnessRadius(const double& toValidate) const;


	double m_cornerRadius;
	double m_convexTipRadius;
	double m_flatnessRadius;
};
}  // namespace cadcam
#endif  //	MW_MWCONVEXTIPMILL_HPP_
