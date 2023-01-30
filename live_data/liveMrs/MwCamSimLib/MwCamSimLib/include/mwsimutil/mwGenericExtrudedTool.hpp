// (C) 2013-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGENERICEXTRUDEDTOOL_HPP_
#define MW_MWGENERICEXTRUDEDTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwCuttingPartDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedTool.hpp"
#pragma warning(push)
#pragma warning(disable : 4996)

namespace cadcam
{
class MW_5AXUTIL_API mwGenericExtrudedTool: public mwExtrudedTool
{
public:
	typedef misc::mwAutoPointer<mwGenericExtrudedTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;
	typedef mwCuttingPartDefinition<double> ToolPartDefinition;

	explicit mwGenericExtrudedTool(const Units units = Units::METRIC);

	mwGenericExtrudedTool(
		const ToolPartDefinition& cuttingPart, const HolderDefinition& holder, const Units units);

	mwGenericExtrudedTool(const mwGenericExtrudedTool& toCopy);

	const mwGenericExtrudedTool& operator=(const mwGenericExtrudedTool& toCopy);

	bool operator==(const mwGenericExtrudedTool& toCompare) const;

	MW_DEPRECATED(
		"Deprecated since 2017.12. Use GetHolder().GetSizeY() - GetHolder().GetSizeZ() for the old "
		"behaivior. Note you will get negative length, it was bugy.Best whould be to use "
		"GetToolPartLength(TPF_ALL_EXCLUDING_HOLDER)")
	virtual const double GetOverallLength() const;

	const ToolPartDefinition& GetCuttingPart() const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

	virtual ~mwGenericExtrudedTool();
	/// Get specified tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

protected:
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// The generic extruded's cutting part, a ToolPartDefinition typed object
#pragma warning(suppress : 4251)
	ToolPartDefinition m_cuttingPart;

	void Copy(const mwGenericExtrudedTool& rToCopy);
};


typedef misc::mwAutoPointer<mwGenericExtrudedTool> mwGenericExtrudedToolPtr;
}  // namespace cadcam
#pragma warning(pop)
#endif  //	MW_MWGENERICEXTRUDEDTOOL_HPP_
