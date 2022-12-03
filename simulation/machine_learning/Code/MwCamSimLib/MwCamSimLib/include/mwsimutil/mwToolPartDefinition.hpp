// (C) 2003-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPARTDEFINITION_HPP_
#define MW_MWTOOLPARTDEFINITION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwMeasurable.hpp"
#include "mwSolidDefinition.hpp"
#include "mwSolidDefinitionCloner.hpp"
#include "mwSolidDefinitionComparer.hpp"


namespace cadcam
{
template <typename T>
class mw2dPolyLine;
}

namespace cadcam
{
//=========== Templates declarations.=============

template <class T>
class MW_5AXUTIL_API mwToolPartDefinition;
template <class T>
class MW_5AXUTIL_API mwCuttingPartDefinition;
template <class T>
class MW_5AXUTIL_API mwNonCuttingPartDefinition;
template <class T>
class MW_5AXUTIL_API mwArborDefinition;
template <class T>
class MW_5AXUTIL_API mwHolderDefinition;
template <class T>
class MW_5AXUTIL_API mwToolPartDefinitionVisitor;

//=========== Classes declarations.=============
// float tool parts
typedef mwToolPartDefinition<float> mwfToolPartDefinition;
typedef mwCuttingPartDefinition<float> mwfCuttingPartDefinition;
typedef mwNonCuttingPartDefinition<float> mwfNonCuttingPartDefinition;
typedef mwArborDefinition<float> mwfArborDefinition;
typedef mwHolderDefinition<float> mwfHolderDefinition;
typedef mwToolPartDefinitionVisitor<float> mwfToolPartDefinitionVisitor;


// double tool parts
typedef mwToolPartDefinition<double> mwdToolPartDefinition;
typedef mwCuttingPartDefinition<double> mwdCuttingPartDefinition;
typedef mwNonCuttingPartDefinition<double> mwdNonCuttingPartDefinition;
typedef mwArborDefinition<double> mwdArborDefinition;
typedef mwHolderDefinition<double> mwdHolderDefinition;
typedef mwToolPartDefinitionVisitor<double> mwdToolPartDefinitionVisitor;

/// @class mwToolPartDefinitionVisitor
/// Use this class to implement additional virtual functions in the mwToolPartDefinition class.
/// It is designed for the 'visitor' scheme.
template <class T>
class MW_5AXUTIL_API mwToolPartDefinitionVisitor
{
public:
	virtual ~mwToolPartDefinitionVisitor() {}
	virtual void Visit(const mwToolPartDefinition<T>& visitor) = 0;
	virtual void Visit(const mwCuttingPartDefinition<T>& visitor) = 0;
	virtual void Visit(const mwNonCuttingPartDefinition<T>& visitor) = 0;
	virtual void Visit(const mwArborDefinition<T>& visitor) = 0;
	virtual void Visit(const mwHolderDefinition<T>& visitor) = 0;
};

/// @class mwToolPartDefinition
/// This is used to define the parts of the tool
/// Parts vary based on their function: holder, arbor, non-cutting, cutting, etc
template <typename T>
class MW_5AXUTIL_API mwToolPartDefinition: public measures::mwMeasurable
{
public:
	typedef misc::mwAutoPointer<mwToolPartDefinition<T>> Ptr;
	typedef mwSolidDefinition<T> Solid;
	/// Creates an empty tool part definition.
	///
	/// The tool part is defined as an empty revolved solid.
	///	@param units are the measurement units (Metric or British Imperial).
	explicit mwToolPartDefinition(const Units units);
	explicit mwToolPartDefinition(const Solid& rToCopy);
	mwToolPartDefinition(const mwToolPartDefinition& rToCopy);
	virtual ~mwToolPartDefinition() {}
	const mwToolPartDefinition& operator=(const mwToolPartDefinition& rToCopy);
	/// Sets the solid definition.
	/// @param toSet definition to be set.
	void SetSolid(const Solid& toSet);
	/// Gets the solid definition.
	/// @returns the solid definition.
	const Solid& GetSolid() const { return *m_solidDefinition; }
	const bool operator==(const mwToolPartDefinition& rToCompare) const;

	/// This function is used in the visitor scheme.
	void virtual AcceptVisitor(mwToolPartDefinitionVisitor<T>& virtualVisitor) const = 0;

protected:
	/// Scales the solid by the given scale factor.
	/// @param units are the measurement units.
	/// @param scaleFactor is the factor by which the solid is scaled.
	void Scale(const Units units, const double& scaleFactor)
	{
		PropagateUnitsChange(*m_solidDefinition, units, scaleFactor);
	}
	typedef misc::mwAutoPointer<Solid> SolidPtr;
	SolidPtr m_solidDefinition;

private:
	void CloneSolid(const Solid& rToCopy);
};

template <typename T>
mwToolPartDefinition<T>::mwToolPartDefinition(const Units units): mwMeasurable(units)
{
	m_solidDefinition = new mwRevolvedSolidDefinition<T>(units);
}
template <typename T>
mwToolPartDefinition<T>::mwToolPartDefinition(const Solid& rToCopy)
	: mwMeasurable(rToCopy.GetUnits())
{
	CloneSolid(rToCopy);
}
template <typename T>
mwToolPartDefinition<T>::mwToolPartDefinition(const mwToolPartDefinition& rToCopy)
	: mwMeasurable(rToCopy.GetUnits())
{
	CloneSolid(*rToCopy.m_solidDefinition);
}
template <typename T>
const mwToolPartDefinition<T>& mwToolPartDefinition<T>::operator=(
	const mwToolPartDefinition& rToCopy)
{
	if (&rToCopy == this)
		return *this;

	mwMeasurable::operator=(rToCopy);

	CloneSolid(*rToCopy.m_solidDefinition);

	return *this;
}
template <typename T>
const bool mwToolPartDefinition<T>::operator==(const mwToolPartDefinition<T>& rToCompare) const
{
	if (!(mwMeasurable::operator==(rToCompare)))
	{
		return false;
	}
	mwSolidDefinitionComparer<T> comparer(m_solidDefinition);
	rToCompare.m_solidDefinition->AcceptVisitor(comparer);
	return comparer.Equal();
}
template <typename T>
void mwToolPartDefinition<T>::SetSolid(const Solid& toSet)
{
	SetUnits(toSet.GetUnits());
	CloneSolid(toSet);
}
template <typename T>
void mwToolPartDefinition<T>::CloneSolid(const Solid& rToCopy)
{
	mwSolidDefinitionCloner<T> cloner(m_solidDefinition);
	rToCopy.AcceptVisitor(cloner);
}
}  // namespace cadcam
#endif  //	MW_MWTOOLPARTDEFINITION_HPP_
