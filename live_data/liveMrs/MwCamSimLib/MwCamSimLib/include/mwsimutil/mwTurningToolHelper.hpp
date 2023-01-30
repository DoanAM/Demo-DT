// (C) 2014-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTURNINGTOOLHELPER_HPP_
#define MW_MWTURNINGTOOLHELPER_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwGrooveTurningTool.hpp"
#include "mwMiscFwdDecl.hpp"
#include "mwPrimeTurningSolidDefinition.hpp"
#include "mwTurningToolsFwdDecl.hpp"

namespace cadcam
{
class mwGenericExtrudedTool;
}  // namespace cadcam

namespace cadcam
{
namespace mwTurningToolHelper
{
bool IsCornerRadiusValid(const double cornerRadius, const double inscribedCircleDiameter);

bool IsCornerRadiusValid(
	const double cornerRadius,
	const double formAngleInDegrees,
	const double width,
	const double length);

bool IsCornerRadiusValid(
	const double cornerRadius,
	const cadcam::mwGrooveTurningTool::Type type,
	const double a,
	const double b,
	const double c,
	const double d,
	const double eInDegrees);

bool IsGrooveTool(const mwTypedExtrudedTool& tool);

bool IsContourTurningTool(const mwTypedExtrudedTool& tool);

MW_5AXUTIL_API double GetCornerRadius(const mwTypedExtrudedTool& tool);

MW_5AXUTIL_API double GetMinCornerRadius(const mwTypedExtrudedTool& tool);

MW_5AXUTIL_API mwTPoint2d<double> GetReferencePointTipTangent(
	const mwTypedExtrudedTool& tool,
	const double tiltAngleInDeg,
	const bool isSpindleRotationClockwise);

enum ReferencePoint
{
	RP_TIP_TANGENT,
	RP_TIP_CENTER,
	RP_CUSTOM_DEFINED
};

MW_5AXUTIL_API mwTPoint3d<double> GetReferencePoint(
	const mwTypedExtrudedTool::Ptr& tool,
	const ReferencePoint rp,
	const mwTPoint3d<double>& customReference,
	const double tiltAngleInDeg,
	const bool isSpindleRotationClockwise);

MW_5AXUTIL_API double GetToolLengthRefTipCenter(const mwTypedExtrudedTool& tool);

MW_5AXUTIL_API double GetToolLengthRefTipTangent(const mwTypedExtrudedTool& tool);

MW_5AXUTIL_API double GetToolLengthRefCustomDef(
	const mwTypedExtrudedTool& tool, const mwPoint2d& customRefPoint);

const mwTypedExtrudedSolidDefinition<double>& GetTypedExtrudedSolidDefinition(
	const mwSolidDefinition<double>& solid);

const mwTurningSolidDefinition<double> GetHolderSolidDefinition(const mwTypedExtrudedTool& tool);

const mwContourTurningSolidDefinition<double> GetContourTurningSolidDefinition(
	const mwTypedExtrudedTool& tool);

const mwPrimeTurningSolidDefinition<double> GetPrimeTurningSolidDefinition(
	const mwTypedExtrudedTool& tool);

template <typename T>
MW_5AXUTIL_API misc::mwstring GetCodeNumber(
	const typename mwPrimeTurningSolidDefinition<T>::CodeNumber codeNumber);

double GetCuttingPartLength(const mwTypedExtrudedTool& tool);

class MW_5AXUTIL_API ContourTurningToolGetter: public cadcam::mwToolVisitor
{
public:
	ContourTurningToolGetter();

	void Visit(const cadcam::mwContourTurningTool& toVisit);

	const cadcam::mwContourTurningTool* GetResult() const;

	bool IsContourTurningTool() const;

	void Default();

private:
	const cadcam::mwContourTurningTool* m_res;
	bool m_isContourTurningTool;
};

class MW_5AXUTIL_API PrimeTurningToolGetter : public cadcam::mwToolVisitor
{
public:
	PrimeTurningToolGetter();

	void Visit(const cadcam::mwPrimeTurningTool& toVisit);

	const cadcam::mwPrimeTurningTool* GetResult() const;

	bool IsPrimeTurningTool() const;

	void Default();

private:
	const cadcam::mwPrimeTurningTool* m_res;
	bool m_isPrimeTurningTool;
};

misc::mwAutoPointer<mwGenericExtrudedTool> Convert(
	const mwExtrudedTool& tool, const double profileTolerance);

misc::mwAutoPointer<mwGenericExtrudedTool> Convert(
	const mwTypedExtrudedTool& tool, const double profileTolerance);

mw3dBoundingBox<double> GetToolPartBoundingBox(
	const mwTypedExtrudedTool& tool, const mwTypedExtrudedTool::ToolPartFlags selection);

}  // namespace mwTurningToolHelper
}  // namespace cadcam
#endif  //	MW_MWTURNINGTOOLHELPER_HPP_
