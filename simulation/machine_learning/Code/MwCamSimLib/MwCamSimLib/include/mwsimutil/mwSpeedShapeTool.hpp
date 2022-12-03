// (C) 2016-2020 by ModuleWorks GmbH
// Owner: 5Axis Application

#ifndef MW_MWSPEEDSHAPETOOL_HPP_
#define MW_MWSPEEDSHAPETOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTool.hpp"


namespace cadcam
{
/// Class for a non rotating tool definition used in machining optical surfaces
class MW_5AXUTIL_API mwSpeedShapeTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwSpeedShapeTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;

	explicit mwSpeedShapeTool(const Units units = Units::METRIC);

	virtual ~mwSpeedShapeTool();

	/// Constructor
	/// @param holder holder for this tool
	/// @param arbor arbor for this tool
	/// @param units metric/inches system to be used for this tool
	mwSpeedShapeTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const double width,
		const double length,
		const double cornerRadius,
		const double conicLength,
		const double conicAngle,  // degree
		const double rampAngle,  // degree
		const double arcRadius,
		const double depth,
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


	double GetWidth() const;
	double GetLength() const;
	double GetCornerRadius() const;
	double GetDepth() const;

	double GetConicLength() const;
	double GetConicAngle() const;
	double GetRampAngle() const;
	double GetArcRadius() const;

	void SetWidth(double newWidth);
	void SetLength(double newLength);
	void SetCornerRadius(double newCornerRadius);
	void SetDepth(double newDepth);

	void SetConicLength(double newConicLength);
	void SetConicAngle(double newConicAngle);
	void SetRampAngle(double newRampAngle);
	void SetArcRadius(double newArcRadius);


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
	bool operator==(const mwSpeedShapeTool& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwSpeedShapeTool& toCompare);


protected:
	/// Scale the tool to new metric system
	/// @param units the new metric system to be used
	/// @param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);

	/// Class members
	HolderDefinition m_holder;
	ArborDefinition m_arbor;
	double m_width;
	double m_length;
	double m_cornerRadius;
	double m_conicLength;
	double m_conicAngle;  // degree angle
	double m_rampAngle;  // degree
	double m_arcRadius;
	double m_depth;


private:
	/// Copies data from another mwSpeedShape object to this one (member by member)
	///
	/// @param rToCopy is object to copy data from
	void Copy(const mwSpeedShapeTool& rToCopy);
};

}  // namespace cadcam
#endif  //	MW_MWSPEEDSHAPETOOL_HPP_
