// (C) 2003-2017 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWARBORDEFINITION_HPP_
#define MW_MWARBORDEFINITION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwToolPartDefinition.hpp"

namespace cadcam
{
/// @class mwArborDefinition
/// Class template defining the arbor as a solid body
template <class T>
class MW_5AXUTIL_API mwArborDefinition: public mwToolPartDefinition<T>
{
public:
	typedef misc::mwAutoPointer<mwArborDefinition<T>> Ptr;
	typedef measures::mwMeasurable::Units Units;
	typedef typename mwToolPartDefinition<T>::Solid Solid;

	/// Creates an empty arbor definition
	///
	/// The arbor will be defined as an empty revolved solid
	///	@param units metric or inch
	explicit mwArborDefinition(const Units units);

	/// Creates an arbor from a solid definition
	///
	///	@param toCopy Solid to create arbor from
	explicit mwArborDefinition(const Solid& toCopy);

	const bool operator==(const mwArborDefinition& toCompare) const;
	/// Implements the visitor pattern
	void virtual AcceptVisitor(mwToolPartDefinitionVisitor<T>& virtualVisitor) const;

protected:
};
}  //  namespace cadcam
#endif  //	MW_MWARBORDEFINITION_HPP_
