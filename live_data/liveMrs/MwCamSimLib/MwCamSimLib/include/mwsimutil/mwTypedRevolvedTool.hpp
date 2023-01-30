// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWTYPEDREVOLVEDTOOL_HPP_
#define MW_MWTYPEDREVOLVEDTOOL_HPP_
namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc

#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwRevolvedTool.hpp"
#include "mwToolHelper.hpp"


namespace cadcam
{
// serialize
class mwTypedRevolvedTool;
//
template <class Archive>
void serialize(Archive& archive, mwTypedRevolvedTool& tool, unsigned int);
// end serialize

/// Definition of a class for tool definition
///
/// This class defines a basis class for all tools
///   used in cam operations
class MW_5AXUTIL_API mwTypedRevolvedTool: public mwRevolvedTool
{
public:
	using mwRevolvedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwTypedRevolvedTool> Ptr;

	template <class Archive>
	friend void serialize(Archive& archive, mwTypedRevolvedTool& tool, unsigned int);
	//###################### Enums and Typedefs      ##############################
	enum cornerRadiusType
	{
		none,
		corner,
		full
	};

	MW_DEPRECATED("cornerRaduisType is deprecated since 2021.04. Please use cornerRadiusType.")
	typedef cornerRadiusType cornerRaduisType;


	enum toolPartDefinitionType
	{
		profile,
		mesh
	};

	enum shaftType
	{
		cylindrical,
		cylindricalCone,
		shaftProfile
	};


	/// Extends tool shoulder definition
	///
	/// This allows user to add a shoulder base and diameter to tools
	/// to be able to specify a tool shaft of cylindrical shape (as before/default) or as trochoidal
	/// shape
	class MW_5AXUTIL_API mwShoulderDefinitionExtender: public measures::mwMeasurable
	{
	public:
		/// Constructor
		///
		///	@param diameter is tool shaft diameter
		///	@param length is tool shaft length measured from the tip of the tool up to bottom of the
		///cylinder 		(where conical part ends)
		mwShoulderDefinitionExtender(
			const double& diameter, const double& length, const Units& units);

		/// Constructor
		///
		///	@param diameter is tool shaft diameter
		///	@param length is tool shaft length measured from the tip of the tool up to bottom of the
		/// cylinder 
		/// @param cylinderBase is the cylinder height (where conical part ends)
		mwShoulderDefinitionExtender(
			const double& diameter,
			const double& length,
			const double& cylinderBase,
			const Units& units);

		/// Get shaft diameter
		///
		///	@return tool shaft diameter
		inline double GetDiameter() const { return m_diameter; }

		/// Set shaft diameter
		///
		///	@param toSet is the new shaft diameter to be set
		void SetDiameter(const double& toSet);

		/// Get shaft length
		///
		///	@return tool shaft length
		inline double GetBaseLength() const { return m_baseLength; }

		/// Set shaft base length
		///
		///	@param toSet is the new shaft base length to be set
		void SetBaseLength(const double& toSet);

		/// Get cylinder base
		///
		///	@return tool shoulder base
		inline double GetCylinderBase() const { return m_cylinderBase; }

		/// Set cylinder base
		///
		///	@param toSet is the new cylinder base to be set
		void SetCylinderBase(const double& toSet);


	protected:
		explicit mwShoulderDefinitionExtender(const Units& units);
		virtual void Scale(const Units units, const double& scaleFactor);

	private:
		/// Validate shaft elements

		/// Validate shaft's diameter
		///
		///	@param toValidate is shaft's diameter to be validated
		void ValidateDiameter(const double& toValidate);

		/// Validate shaft's base length
		///
		///	@param toValidate is shaft's base length to be validated
		void ValidateBaseLenght(const double& toValidate);

		/// Validate shaft's base height
		///
		///	@param toValidate is shaft's cylinder base to be validated
		void ValidateCylinderBase(const double& toValidate);


		double m_diameter;
		double m_baseLength;
		double m_cylinderBase;
		friend class mwTypedRevolvedTool;
	};
	typedef mwShoulderDefinitionExtender ShoulderDefinitionExtender;
	typedef misc::mwAutoPointer<ShoulderDefinitionExtender> ShoulderDefinitionExtenderPtr;


	/// Destructor
	virtual ~mwTypedRevolvedTool(){};

	/// Constructor
	///	@param diameter tool diameter
	///	@param holder tool holder
	///	@param fluteLength  tool flute length
	///	@param arbor tool arbor
	///	@param shoulderLength tool shoulder length
	///	@param units the metric system to be used for this tool
	mwTypedRevolvedTool(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const double& shoulderLength,
		const Units units);

	/// Constructor with tool shaft definition
	///
	/// Constructor
	/// @param diameter tool diameter
	/// @param holder tool holder
	/// @param fluteLength  tool flute length
	/// @param arbor tool arbor
	/// @param shoulderLength tool shoulder length
	/// @param shaftDefinition tool shaft definition
	/// @param units the metric system to be used for this tool
	mwTypedRevolvedTool(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const double& shoulderLength,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);


	/// Constructor with user defined shaft definition as profile
	///
	/// Constructor
	/// @param diameter tool diameter
	/// @param holder tool holder
	/// @param fluteLength  tool flute length
	/// @param arbor tool arbor
	/// @param shoulderLength tool shoulder length
	/// @param shaftDefinition tool shaft definition
	/// @param units the metric system to be used for this tool
	mwTypedRevolvedTool(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const NonCutPartDefinition& shaftDefinition,
		const Units units);

	/// Copy Constructor
	///	@param toCopy the tool to be copied
	mwTypedRevolvedTool(const mwTypedRevolvedTool& toCopy);

	//#########################  Gets  ############################################

	/// Get tool diameter
	///
	/// This function returns the diameter of the tool
	/// @returns current tool diameter
	const double GetToolDiameter() const;

	/// Get tool shaft definition
	///
	/// This function returns the definition of tool shaft
	///	@return tool shaft definition
	const mwShoulderDefinitionExtender& GetShoulderDefinition() const;

	/// Get tool shaft definition
	///
	/// This function returns the definition of tool shaft
	/// @return tool shaft definition
	/// Valid only for shaftType == shaftProfile
	/// Please note that no automatic conversion is done between ShoulderDefinition and ShaftProfile
	const NonCuttingPartDefinition& GetShaftProfile() const;

	/// Get tool shaft type
	///
	/// This function returns the type of tool shaft
	///	@return tool shaft type
	const shaftType& GetShaftType() const;

	/// Test if this tool has advanced shoulder definition
	///
	/// Advanced shoulder definition means that shoulder part of this tool can have the following
	/// shapes:
	///		1. a truncated cone and a cylinder. truncated cone starts at "flute length" and ends at shoulder base.
	/// cylinder starts at "shoulder base" with diameter "shoulder diameter" (not equal tool diameter) 	and ends at shaft length.
	///		2. a single cylinder starting at "flute length" with diameter "shoulder diameter" (not equal
	/// tool diameter) and ends at shaft length.
	///
	/// @return true if this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;


	//#################### Visitor scheme ########################################

	/// This function is used in the visitor scheme
	/// void virtual AcceptVirtual( const mwToolVisitor &virtualVisitor )
	///	const = 0;

	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;


	/// Function to set the base length of the tool
	/// @param toSet the new value of the base length
	void SetBaseLength(const double& toSet);

protected:
	/// Calculate bbox of tool's cutting part
	/// @returns current tool's cutting part bbox
	virtual mw3dBoundingBox<double> GetCuttingPartBoundingBox() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another
	/// @param toCopy tool to copy the information from
	/// @returns current tool with copied information
	const mwTypedRevolvedTool& operator=(const mwTypedRevolvedTool& toCopy);

	/// Equality operator
	///
	/// Are given tools equal?
	/// @param toCompare tool to compare the current tool with
	/// @returns <b>true</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwTypedRevolvedTool& toCompare) const;

	/// Scale the tool to new metric system
	///	@param units the new metric system to be used
	///	@param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);

	/// ComputeCornerRadiusType
	///
	///	Computes corner radius type based on an input corner radius type
	///	and also on corner radius value
	///	@param crType is corner radius type passed as input
	///	@param cornerRadius is the value of corner radius
	///	@return type of corner radius computed based on input corner radius type and
	///		the value of corner radius
	const cornerRadiusType ComputeCornerRadiusType(
		const cornerRadiusType& crType, const double& cornerRadius) const;

	/// ValidateToolDiameterNotZero function
	///
	///	@param newDiameter of type const double
	virtual void ValidateToolDiameterNotZero(const double newDiameter);
	void ValidateDiameterVersusCornerRadius(
		const double& newCornerRadius, const double& newDiameter);


	/// Tool diameter
	double mDiameter;
	/// Tool flute length
	double mFluteLength;
	/// Tool shoulder length
	double mShoulderLength;
	/// Tool shaft definition
	mwShoulderDefinitionExtender m_shoulderDefinition;
	/// Tool shaft type
	shaftType m_shaftType;
	/// Shaft part of the tool
	NonCutPartDefinition m_shaftProfile;

private:
	/// Internal constructor for this object
	///
	/// Construct an object of this type, set member variables and makes additional validations
	///	@param diameter tool diameter
	///	@param fluteLength is tool flute length
	///	@param shoulderLength is tool shoulder length
	void InternalConstructor(
		const double& diameter, const double& fluteLength, const double& shoulderLength);

	/// Copys data
	void Copy(const mwTypedRevolvedTool& rToCopy);

	/// ValidateToolDiameter function
	///
	///	@param newDiameter of type const double
	virtual void ValidateToolDiameter(const double newDiameter);

	/// ValidateFluteLength function
	///
	///	@param newLength of type const double
	virtual void ValidateFluteLength(const double newLength);

	/// ValidateShoulderLength function
	///
	///	@param newLength of type const double
	virtual void ValidateShoulderLength(const double newLength);

	void ValidateShoulderDefinition();

	void ValidateShaftDefinition();
};

typedef misc::mwAutoPointer<mwTypedRevolvedTool> mwTypedRevolvedToolPtr;
}  // namespace cadcam
#endif  //	MW_MWTYPEDREVOLVEDTOOL_HPP_
