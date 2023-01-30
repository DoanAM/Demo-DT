// (C) 2010-2017 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWNONCUTTINGPARTDEFINITION_HPP_
#define MW_MWNONCUTTINGPARTDEFINITION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwToolPartDefinition.hpp"


namespace cadcam
{
/// @class mwNonCuttingPartDefinition
/// Defines non-cutting part shape of a tool
template <class T>
class MW_5AXUTIL_API mwNonCuttingPartDefinition: public mwToolPartDefinition<T>
{
public:
	typedef misc::mwAutoPointer<mwNonCuttingPartDefinition<T>> Ptr;
	typedef measures::mwMeasurable::Units Units;
	typedef typename mwToolPartDefinition<T>::Solid Solid;

	/// Creates an empty cutting part definition.
	///
	/// The cutting part is defined as an empty revolved solid.
	///	@param units are the measurement units (Metric or British Imperial).
	explicit mwNonCuttingPartDefinition(const Units units);

	explicit mwNonCuttingPartDefinition(const Solid& toCopy);

	const bool operator==(const mwNonCuttingPartDefinition& toCompare) const;

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	void virtual AcceptVisitor(mwToolPartDefinitionVisitor<T>& virtualVisitor) const;

protected:
};
}  // namespace cadcam
#endif  //	MW_MWNONCUTTINGPARTDEFINITION_HPP_
