// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELADVANCEDMILL_HPP_
#define MW_MWBARRELADVANCEDMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include <iosfwd>

namespace cadcam
{
class mwBarrelAdvancedMill;
class mwBarrelMill;
}  // namespace cadcam
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelAdvancedMill&);

namespace cadcam
{
/// This class represents an advanced barrel mill tool
class MW_5AXUTIL_API mwBarrelAdvancedMill: public mwTypedRevolvedTool
{
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelAdvancedMill&);
public:
	using mwRevolvedTool::AcceptVirtual;

	/// Definition of FluteHeight for advanced BarrelMill
	class MW_5AXUTIL_API FluteHeightDefinition: public measures::mwMeasurable
	{
	public:
		enum DefinedBy
		{
			FH_DEF_BY_UPPER_DIAMETER,
			FH_DEF_BY_LENGTH
		};
		FluteHeightDefinition(const Units units = Units::METRIC);
		const DefinedBy GetDefinedBy() const;
		void SetDefinedBy(const DefinedBy& toSet);
		const double GetValue() const;
		void SetValue(const double& toSet);
		const bool operator==(const FluteHeightDefinition& toCompare) const;

	protected:
		virtual void Scale(const Units units, const double& scaleFactor);

	private:
		void SetDefaults();
		DefinedBy m_definedBy;
		double m_value;
	};
	/// Definition of AxialPosition (OY) of center point (M) of barrel tool profile circle
	class MW_5AXUTIL_API AxialPositionDefinition: public measures::mwMeasurable
	{
	public:
		enum DefinedBy
		{
			AP_DEF_BY_DISTANCE,
			AP_DEF_BY_REFERENCE_DIAMETER
		};
		AxialPositionDefinition(const Units units = Units::METRIC);
		const DefinedBy GetDefinedBy() const;
		void SetDefinedBy(const DefinedBy& toSet);
		const double GetValue() const;
		void SetValue(const double& toSet);
		const bool operator==(const AxialPositionDefinition& toCompare) const;

	protected:
		virtual void Scale(const Units units, const double& scaleFactor);

	private:
		void SetDefaults();
		DefinedBy m_definedBy;
		double m_value;
	};
	/// Definition of RadialPosition (OX) of center point (M) of barrel tool profile circle
	class MW_5AXUTIL_API RadialPositionDefinition: public measures::mwMeasurable
	{
	public:
		enum DefinedBy
		{
			RP_DEF_BY_DISTANCE,
			RP_DEF_BY_MAX_DIAMETER
		};
		RadialPositionDefinition(const Units units = Units::METRIC);
		const DefinedBy GetDefinedBy() const;
		void SetDefinedBy(const DefinedBy& toSet);
		const double GetValue() const;
		void SetValue(const double& toSet);
		const bool operator==(const RadialPositionDefinition& toCompare) const;

	protected:
		virtual void Scale(const Units units, const double& scaleFactor);

	private:
		void SetDefaults();
		DefinedBy m_definedBy;
		double m_value;
	};

	explicit mwBarrelAdvancedMill(const Units units = Units::METRIC);

	/// Constructor with parameters and default shoulder definition extender
	mwBarrelAdvancedMill(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const cornerRadiusType& cornerRadType,
		const double& cornerRadius,
		const double& shoulderLen,
		const double& profileRadius,
		const HolderDefinition& holderDef,
		const ArborDefinition& arborDef,
		const Units units);

	/// Constructor with parameters and user given shoulder definition extender
	mwBarrelAdvancedMill(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const cornerRadiusType& cornerRadType,
		const double& cornerRadius,
		const double& shoulderLen,
		const double& profileRadius,
		const HolderDefinition& holderDef,
		const ArborDefinition& arborDef,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructor with parameters and user given shoulder definition extender as profile
	mwBarrelAdvancedMill(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const cornerRadiusType& cornerRadType,
		const double& cornerRadius,
		const double& profileRadius,
		const HolderDefinition& newHolder,
		const ArborDefinition& newArbor,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	virtual ~mwBarrelAdvancedMill();

	/// Creates a exact copy of a given tool
	/// @param toCopy tool to create a copy of
	mwBarrelAdvancedMill(const mwBarrelAdvancedMill& toCopy);

	/// Get corner radius
	///
	/// Returns corner radius of the tool
	///		@returns corner radius of the tool
	const double& GetCornerRadius() const;
	/// Get corner radius type
	///
	/// Returns corner radius type
	///	@returns corner radius type
	const cornerRadiusType& GetCornerRadiusType() const;
	/// Get upper diameter of the tool
	///
	///	@return tool upper diameter
	const double& GetUpperDiameter() const;
	/// Get profile radius of the tool
	///
	///	@return profile radius of the tool
	const double& GetProfileRadius() const;
	/// Gets flute length definition of the tool
	///
	///	@return flute length definition
	const FluteHeightDefinition& GetFluteHeightDefinition() const;
	/// Gets definition of axial position of tool profile
	///
	/// This is the way how axial (OY) position of center point (M) of tool profile circle is
	/// defined
	///	@return definition of axial position of tool profile
	const AxialPositionDefinition& GetAxialPositionDefinition() const;
	/// Gets definition of radial position of tool profile
	///
	/// This is the way how radial (OX) position of center point (M) of tool profile circle is
	/// defined
	///	@return definition of radial position of tool profile
	const RadialPositionDefinition& GetRadialPositionDefinition() const;
	/// Gets axial distance (OY distance) of center point (M) of tool profile circle
	///
	///	@return axial distance of profile center point (M)
	const double& GetAxialDistance() const;
	/// Gets radial distance (OX distance) of center point (M) of tool profile circle
	///
	///	@return radial distance of profile center point (M)
	const double& GetRadialDistance() const;
	/// Gets reference diameter of the tool
	///
	/// This is the diameter ar the tip of the tool
	///	@return reference diameter
	const double& GetReferenceDiameter() const;
	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	///	the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;
	/// Attempt to convert an object of this class to a mwBarrelMill object
	///
	/// In some situations, depending on parameters settings, conversion may not work
	///	and an exception is thrown
	///	@param toConvert is object to be converted
	///	@return autopointer to a new constructed mwBarrelMill object if conversion succeeds
	///	@throws exception if conversion fails
	static const misc::mwAutoPointer<mwBarrelMill> Convert(const mwBarrelAdvancedMill& toConvert);
	/// Assignment operator
	const mwBarrelAdvancedMill& operator=(const mwBarrelAdvancedMill& toCopy);
	/// Equality operator
	bool operator==(const mwBarrelAdvancedMill& toCompare) const;
	/// Inequality operator
	bool operator!=(const mwBarrelAdvancedMill& toCompare);
	/// implements the visitor pattern
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	const double ComputeCornerRadius() const;

	static const double ComputeFluteLength(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const double& profileRadius);

protected:
	/// Scale this tool according with measurement units
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copy data members from given tool to current tool
	///
	///	@param toCopy is barrel to be copied into this object
	void Copy(const mwBarrelAdvancedMill& toCopy);
	/// Validates the upper diameter
	///
	/// Validates the upper diameter of the tool
	///	@param newUpperDiameter the new upper diameter
	///	@throws mwException if the upper diameter is not valid
	void ValidateUpperDiameter(const double& newUpperDiameter);
	/// Validates the corner radius
	///
	/// Validates if the corner radius is greater or equal zero
	/// @param newCornerRad corner radius
	/// @throws mwException if the corner radius is negative
	void ValidateCornerRadius(const double& newCornerRadius);
	/// Validates the profile radius
	///
	/// Validates the profile radius of the tool
	///	@param newProfileRadius the new profile radius
	///	@throws mwException if the profile radius is not valid
	void ValidateProfileRadius(const double& newProfileRadius);
	/// Internal constructor
	///
	/// Performs params validations and initialize all params based on user input
	///	@param fluteHeightDef is user given definition for flute height
	///	@param axialPositionDef is user given definition for axial position
	///	@param radialPositionDef is user given definition for radial position
	///	@param shoulderLen is should length
	///	@param cornerRadType is corner radius type
	///	@param cornerRadius is corner radius
	///	@param profileRadius is profile radius
	void InternalConstructor(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const cornerRadiusType& cornerRadType,
		const double& cornerRadius,
		const double& profileRadius);
	/// Compute corner radius
	///
	/// Compute tool's corner radius based on given params
	///	@param cornerRadType is corner radius type
	///	@param cornerRadius is corner radius value
	///	@param profileRadius is profile radius
	///	@param axialDistance is axial distance of profile center point (M)
	///	@param radialDistance is radial distance of profile center point (M)
	///	@return computed corner radius
	const double ComputeCornerRadius(
		const cornerRadiusType& cornerRadType,
		const double& cornerRadius,
		const double& profileRadius,
		const double& axialDistance,
		const double& radialDistance) const;
	/// Validates reference diameter
	///
	/// Validates  reference diameter of the tool
	///	@param referenceDiameter is reference diameter to be validated
	///	@throws exception is parameter to be validated is not valid
	void ValidateReferenceDiameter(const double& referenceDiameter) const;
	/// Validate individual params
	///
	///	@param upperDiameter is upper diameter to be validated
	///	@param maximumDiameter is maximum diameter to be validated
	///	@param cornerRadius is corner radius to be validated
	///	@param profileRadius is profileRadius to be validated
	///	@param referenceDiameter  is referenceDiameter to be validated
	void IndividualParamsValidations(
		const double& upperDiameter,
		const double& maximumDiameter,
		const double& cornerRadius,
		const double& profileRadius,
		const double& referenceDiameter);
	/// Validated dependencies between parameters
	///
	///	@param fluteLen is flute length to be validated
	///	@param upperDiameter is upper diameter to be validated
	///	@param maximumDiameter is maximum diameter to be validated
	///	@param cornerRadius is corner radius to be validated
	///	@param profileRadius is profileRadius to be validated
	///	@param referenceDiameter  is referenceDiameter to be validated
	///	@param axialDistance is axial distance to be validated
	///	@param radialDistance is radial distance to be validated
	void DependenciesParamsValidations(
		const double& fluteLen,
		const double& upperDiameter,
		const double& maximumDiameter,
		const double& cornerRadius,
		const double& profileRadius,
		const double& referenceDiameter,
		const double& axialDistance,
		const double& radialDistance);
	/// Compute full corner radius based on other tool parameters
	///
	///	@param profileRadius is profile radius
	///	@param axialDistance is axial distance of profile
	///	@param radialDistance is radial distance of profile
	const double ComputeFullCornerRadius(
		const double& profileRadius,
		const double& axialDistance,
		const double& radialDistance) const;
	/// @struct BarrelComputedParams
	/// Params to be computed from user given definitions
	struct BarrelComputedParams
	{
		double m_fluteLen;
		double m_upperDiameter;
		double m_maxDiameter;
		double m_referenceDiameter;
		double m_axialDistance;
		double m_radialDistance;
	};
	/// Compute some barrel parameter from user given definitions
	///
	///	@param fluteHeightDef is user given definition for flute height
	///	@param axialPositionDef is user given definition for axial position
	///	@param radialPositionDef is user given definition for radial position
	///	@param profileRadius is user given profile radius
	///	@return computed params based on input definitions
	const BarrelComputedParams ComputeBarrelParamsFromDefinitions(
		const FluteHeightDefinition& fluteHeightDef,
		const AxialPositionDefinition& axialPositionDef,
		const RadialPositionDefinition& radialPositionDef,
		const double& profileRadius);

	double m_profileRadius;
	double m_cornerRadius;
	double m_referenceDiameter;
	double m_upperDiameter;
	cornerRadiusType m_cornerRadiusType;
	double m_axialDistance;
	double m_radialDistance;

	FluteHeightDefinition m_fluteHeightDefinition;
	AxialPositionDefinition m_axialPositionDefinition;
	RadialPositionDefinition m_radialPositionDefinition;
};  //  class mwBarrelAdvancedMill
}  //  namespace cadcam
#endif  //	MW_MWBARRELADVANCEDMILL_HPP_
