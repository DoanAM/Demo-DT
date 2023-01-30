// (C) 2014-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWEXTRUDEDTOOL_HPP_
#define MW_MWEXTRUDEDTOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTool.hpp"
#include "mwTurningSolidDefinition.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwExtrudedTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwExtrudedTool> Ptr;

	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;

	typedef mwSolidDefinition<double> SolidDefinition;
	typedef mwRevolvedSolidDefinition<double> RevolvedSolidDefinition;
	typedef mwExtrudedSolidDefinition<double> ExtrudedSolidDefinition;
	typedef mwMeshSolidDefinition<double> MeshSolidDefinition;
	typedef mwTurningSolidDefinition<double> TurningSolidDefinition;
	typedef mwSolidDefinitionVisitorGetter<double> SolidDefinitionVisitorGetter;

	explicit mwExtrudedTool(const Units units = measures::mwUnitsFactory::METRIC);

	mwExtrudedTool(const HolderDefinition& holder, const ArborDefinition& arbor, const Units units);

	mwExtrudedTool(const mwExtrudedTool& toCopy);

	const mwExtrudedTool& operator=(const mwExtrudedTool& toCopy);

	bool operator==(const mwExtrudedTool& toCompare) const;

	virtual const HolderDefinition& GetHolder() const;

	virtual const ArborDefinition& GetArbor() const;

	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

	virtual ~mwExtrudedTool();

	virtual void Scale(const Units units, const double& scaleFactor);

private:
#pragma warning(push)
#pragma warning(disable : 4251)
	ArborDefinition m_arbor;
	HolderDefinition m_holder;
#pragma warning(pop)

	void Copy(const mwExtrudedTool& rToCopy);

	/// This class represents a tool's holder validator
	struct HolderValidator: public SolidDefinitionVisitorGetter
	{
		/// Visit const SolidDefinition
		virtual void Visit(const SolidDefinition& visitor);
		/// Visit const RevolvedSolidDefinition
		virtual void Visit(const RevolvedSolidDefinition& visitor);
		/// Visit const ExtrudedSolidDefinition
		virtual void Visit(const ExtrudedSolidDefinition& visitor);
		/// Visit const MeshSolidDefinition
		virtual void Visit(const MeshSolidDefinition& visitor);
	};

	/// This class represents a tool's arbor validator
	struct ArborValidator: public SolidDefinitionVisitorGetter
	{
		/// Visit const SolidDefinition
		virtual void Visit(const SolidDefinition& visitor);
		/// Visit const RevolvedSolidDefinition
		virtual void Visit(const RevolvedSolidDefinition& visitor);
		/// Visit const ExtrudedSolidDefinition
		virtual void Visit(const ExtrudedSolidDefinition& visitor);
		/// Visit const MeshSolidDefinition
		virtual void Visit(const MeshSolidDefinition& visitor);
	};
};

typedef misc::mwAutoPointer<mwExtrudedTool> mwExtrudedToolPtr;
}  // namespace cadcam
#endif  //	MW_MWEXTRUDEDTOOL_HPP_
