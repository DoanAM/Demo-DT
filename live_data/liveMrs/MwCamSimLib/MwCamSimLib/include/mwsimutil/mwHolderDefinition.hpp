// (C) 2003-2017 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWHOLDERDEFINITION_HPP_
#define MW_MWHOLDERDEFINITION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwSolidDefinition.hpp"
#include "mwToolPartDefinition.hpp"

namespace cadcam
{
/// @class mwHolderDefinition
/// Class template defining the holder as a solid body
template <class T>
class MW_5AXUTIL_API mwHolderDefinition: public mwToolPartDefinition<T>
{
public:
	typedef misc::mwAutoPointer<mwHolderDefinition<T>> Ptr;
	typedef measures::mwMeasurable::Units Units;
	typedef typename mwToolPartDefinition<T>::Solid Solid;
	/// Creates an empty holder definition
	///
	/// The holder will be defined as an empty revolved solid
	///	@param units metric or inch
	explicit mwHolderDefinition(const Units units);
	/// Creates an holder from a solid definition
	///
	///	@param toCopy Solid to create holder from
	explicit mwHolderDefinition(const Solid& toCopy);
	const bool operator==(const mwHolderDefinition& toCompare) const;
	/// implements the visitor pattern
	void virtual AcceptVisitor(mwToolPartDefinitionVisitor<T>& virtualVisitor) const;

	MW_DEPRECATED("Deprecated since 2017.12. Use GetSolid().GetBoundingBox3d().GetSizeZ()")
	const T GetHolderMaxHeight() const;

protected:
};
}  // namespace cadcam
#endif  //	MW_MWHOLDERDEFINITION_HPP_
