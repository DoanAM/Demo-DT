// (C) 2016-2020 by ModuleWorks GmbH
// Owner: 5Axis Application

#ifndef MW_MWCHISELINGTOOL_HPP_
#define MW_MWCHISELINGTOOL_HPP_
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
class MW_5AXUTIL_API mwChiselingTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwChiselingTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;

	/// Constructor with default values
	explicit mwChiselingTool(const Units units =  Units::METRIC);

	virtual ~mwChiselingTool();

	/// Constructor that requires all tool parameters
	///
	/// @param holder holder for this tool
	/// @param arbor arbor for this tool
	/// @param length length of tool shaft (cylinder)
	/// @param radius radius of the clearance geometry (cylinder)
	/// @param cuttingAngle
	/// @param cuttingWidth
	/// @param units metric/inches system to be used for this tool
	mwChiselingTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const double length,
		const double radius,
		const double tipAngle,
		const double tipDepth,
		const double flankAngle,
		const double cuttingWidth,
		const Units units);

	virtual const HolderDefinition& GetHolder() const;
	virtual const ArborDefinition& GetArbor() const;

	double GetLength() const;
	double GetRadius() const;
	double GetTipAngle() const;
	double GetTipDepth() const;
	double GetFlankAngle() const;
	double GetCuttingWidth() const;

	bool IsTipFlat() const;
	double GetTipHeight() const;
	double GetCuttingLength() const;

	//#################### Visitor scheme ########################################
	/// Visitor pattern
	/// @param visitor the visitor
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;

	/// Visitor pattern
	/// @param visitor the visitor
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

	/// Are given tools equal?
	/// @param toCompare tool to compare the current tool with
	/// @returns <b>true</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwChiselingTool& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwChiselingTool& toCompare);


protected:
	/// Scale the tool to new metric system
	/// @param units the new metric system to be used
	/// @param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);


	HolderDefinition m_holder;
	ArborDefinition m_arbor;

	double m_length;  ///< total length
	double m_radius;  ///< radius of the clearance geometry
	double m_tipAngle;  ///< opening angle of tip
	double m_tipDepth;  ///< height of blunt tip part
	double m_flankAngle;  ///< opening angle of flank above tip
	double m_cuttingWidth;  ///< width of tip part

private:
	/// Copies data from another mwSawingTool object to this one (member by member)
	///
	/// @param rToCopy is object to copy data from
	void Copy(const mwChiselingTool& rToCopy);
};

}  // namespace cadcam
#endif  //	MW_MWCHISELINGTOOL_HPP_
