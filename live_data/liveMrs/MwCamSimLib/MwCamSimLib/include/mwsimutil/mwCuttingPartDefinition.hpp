// (C) 2010-2017 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCUTTINGPARTDEFINITION_HPP_
#define MW_MWCUTTINGPARTDEFINITION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwToolPartDefinition.hpp"


namespace cadcam
{
/// @class mwCuttingPartDefinition
/// Class containing tool cutting part definition
template <class T>
class MW_5AXUTIL_API mwCuttingPartDefinition: public mwToolPartDefinition<T>
{
public:
	typedef misc::mwAutoPointer<mwCuttingPartDefinition<T>> Ptr;
	typedef measures::mwMeasurable::Units Units;
	typedef typename mwToolPartDefinition<T>::Solid Solid;

	/// Creates an empty cutting part definition.
	///
	/// The cutting part is defined as an empty revolved solid.
	///	@param units are the measurement units (Metric or British Imperial).
	explicit mwCuttingPartDefinition(const Units units);

	explicit mwCuttingPartDefinition(const Solid& toCopy);

	const bool operator==(const mwCuttingPartDefinition& toCompare) const;

	/// Implements the visitor pattern
	///
	///	@param virtualVisitor is the visitor to be accepted.
	void virtual AcceptVisitor(mwToolPartDefinitionVisitor<T>& virtualVisitor) const;

protected:
};
}  // namespace cadcam
#endif  //	MW_MWCUTTINGPARTDEFINITION_HPP_
