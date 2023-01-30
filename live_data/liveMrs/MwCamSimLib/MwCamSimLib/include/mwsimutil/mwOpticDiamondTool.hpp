// (C) 2016-2020 by ModuleWorks GmbH
// Owner: 5Axis UP & Additive

#ifndef MW_MWOPTICDIAMONDTOOL_HPP_
#define MW_MWOPTICDIAMONDTOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTool.hpp"


namespace cadcam
{
/// Class for a non rotating tool definition used in machining optical surfaces
///
/// This tool is similar to a turning tool but with a very specific cutting curve
/// that is defined by a clearance geometry cut by a rake plane. The clearance
/// is either achieved by a cone with a specified clearance angle or a cylinder that
/// is rotated by the clearance angle. The cutting curve is the defined by an
/// intersection with a rake plane that is defined by a rake angle. This results in
/// a possible elliptical cutting edge. Additionally this tool can be flattened so
/// that only on half of the tool remains.
class MW_5AXUTIL_API mwOpticDiamondTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwOpticDiamondTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;

	/// Possible clearance types
	enum ClearanceType
	{
		CT_CONICAL,  ///< based on a cone with opening angle = 2 times clearance angle
		CT_CYLINDRICAL,  ///< based on a cylinder rotated by the clearance angle
	};

	/// Possible radius types
	enum RadiusType
	{
		RT_FULL,  ///< full cutting curve on both sides
		RT_LEFT,  ///< only left side of the tool
		RT_RIGHT,  ///< only right side of the tool
	};

	/// Constructor with default values
	explicit mwOpticDiamondTool(const Units units = Units::METRIC);

	virtual ~mwOpticDiamondTool();

	/// Constructor that requires all tool parameters
	///
	/// @param holder holder for this tool
	/// @param arbor arbor for this tool
	/// @param radius radius of the clearance geometry(cone/cylinder)
	/// @param includedAngle included angle at the cutting curve
	/// @param clearanceType type of clearance geometry
	/// @param clearanceAngle clearance angle
	/// @param rakeAngle rake angle
	/// @param radiusType radius type
	/// @param length total length of the tool
	/// @param width width of the tool
	/// @param thickness total thickness of the tool
	/// @param units metric/inches system to be used for this tool
	mwOpticDiamondTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const double radius,
		const double includedAngle,
		const ClearanceType clearanceType,
		const double clearanceAngle,
		const double rakeAngle,
		const RadiusType radiusType,
		const double length,
		const double width,
		const double thickness,
		const Units units);

	/// Get holder
	///
	/// This function returns the holder of the tool
	/// @returns current holder
	virtual const HolderDefinition& GetHolder() const;

	/// Get arbor definition
	///
	/// This function returns the arbor definition of the tool
	/// @returns current arbor definition
	virtual const ArborDefinition& GetArbor() const;

	/// Get thickness of the tool
	///
	/// @return thickness of the tool
	double GetThickness() const;

	/// Get width of the tool
	///
	/// @return width of the tool
	double GetWidth() const;

	/// Get length of the tool
	///
	/// @return length of the tool
	double GetLength() const;

	/// Get radius type of the tool
	///
	/// @return radius type of the tool
	RadiusType GetRadiusType() const;

	/// Get rake angle of the tool
	///
	/// @return rake angle of the tool
	double GetRakeAngle() const;

	/// Get clearance angle of the tool
	///
	/// @return clearance angle of the tool
	double GetClearanceAngle() const;

	/// Get clearance type of the tool
	///
	/// @return clearance type of the tool
	ClearanceType GetClearanceType() const;

	/// Get included angle of the tool
	///
	/// @return included angle of the tool
	double GetIncludedAngle() const;

	/// Get radius of the tool
	///
	/// @return radius of the tool
	double GetRadius() const;

	//#################### Visitor scheme ########################################
	/// Visitor pattern
	/// @param visitor the visitor
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;

	/// Visitor pattern
	/// @param visitor the visitor
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

	//########################## Operators ########################################
	/// Equality operator
	///
	/// Are given tools equal?
	/// @param toCompare tool to compare the current tool with
	/// @returns <b>true</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwOpticDiamondTool& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwOpticDiamondTool& toCompare);


protected:
	/// Scale the tool to new metric system
	/// @param units the new metric system to be used
	/// @param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);

	HolderDefinition m_holder;  ///< tool holder
	ArborDefinition m_arbor;  ///< tool arbor
	double m_radius;  ///< radius of the clearance geometry
	double m_includedAngle;  ///< included angle of the cutting curve
	ClearanceType m_clearanceType;  ///< clearance type
	double m_clearanceAngle;  ///< clearance angle
	double m_rakeAngle;  ///< rake angle
	RadiusType m_radiusType;  ///< radius type
	double m_length;  ///< total length
	double m_width;  ///< total width
	double m_thickness;  ///< total thickness

private:
	/// Copies data from another mwSawingTool object to this one (member by member)
	///
	/// @param rToCopy is object to copy data from
	void Copy(const mwOpticDiamondTool& rToCopy);
};

}  // namespace cadcam
#endif  //	MW_MWOPTICDIAMONDTOOL_HPP_
