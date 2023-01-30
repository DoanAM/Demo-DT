// (C) 2013-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTYPEDEXTRUDEDTOOL_HPP_
#define MW_MWTYPEDEXTRUDEDTOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedTool.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTurningToolsFwdDecl.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwTypedExtrudedTool: public mwExtrudedTool
{
public:
	typedef misc::mwAutoPointer<mwTypedExtrudedTool> Ptr;

	explicit mwTypedExtrudedTool(const Units units = measures::mwUnitsFactory::METRIC);

	mwTypedExtrudedTool(const HolderDefinition& holder, const Units units);

	mwTypedExtrudedTool(
		const HolderDefinition& holder, const double insertThickness, const Units units);

	mwTypedExtrudedTool(const mwTypedExtrudedTool& toCopy);

	/// Get insert thickness
	double GetThickness() const;

	virtual ~mwTypedExtrudedTool();

protected:
	/// Assignment operator
	const mwTypedExtrudedTool& operator=(const mwTypedExtrudedTool& toCopy);

	/// Equality operator
	bool operator==(const mwTypedExtrudedTool& toCompare) const;

	/// Scale the tool to new metric system
	virtual void Scale(const Units units, const double& scaleFactor);

	/// Validates holder insert type compatibility
	void ValidateHolderDefinition(const TurningSolidDefinition::Insert insert) const;

	/// Validates insert corner radius
	void ValidateCornerRadius(const double cornerRadius) const;

	/// Validates insert corner radius
	void ValidateCornerRadius(
		const double cornerRadius, const double inscribedCircleDiameter) const;

	/// Validates insert inscribed circle diameter
	void ValidateInscribedCircleDiameter(const double circleDiameter) const;

	/// Validates insert form angle
	void ValidateFormAngle(const double formAngle) const;

	/// Validates insert width
	void ValidateWidth(const double width) const;

	/// Validates insert cutting edge distance
	void ValidateLength(const double cuttingEdgeDistance) const;
	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

private:
	virtual void DoScale(const Units units, const double scaleFactor) = 0;

	double m_insertThickness;

	/// Copies data from another mwTypedExtrudedTool object to this one (member by member)
	void Copy(const mwTypedExtrudedTool& rToCopy);

	/// Validates insert thickness for the tool
	void ValidateThickness(const double insertThickness) const;
};

}  // namespace cadcam
#endif  //	MW_MWTYPEDEXTRUDEDTOOL_HPP_
