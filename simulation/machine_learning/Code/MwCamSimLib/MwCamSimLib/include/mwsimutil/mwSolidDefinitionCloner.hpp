// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSOLIDDEFINITIONCLONER_HPP_
#define MW_MWSOLIDDEFINITIONCLONER_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwSolidDefinition.hpp"


namespace cadcam
{
/// This class clones a solid definition derived from a mwSolidDefinition object
template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionCloner: public cadcam::mwSolidDefinitionVisitorGetter<T>
{
public:
	/// Class constructor
	///
	/// @param solidDest reference to an existing auto-pointer to an mwSolidDefinition object
	mwSolidDefinitionCloner(typename mwSolidDefinition<T>::Ptr& solidDest);


	/// Class destructor
	virtual ~mwSolidDefinitionCloner() {}


	/// Visit method for a mwSolidDefinition object
	///
	/// @param visitor a reference to a mwSolidDefinition object
	/// @throws an exception, since mwSolidDefinition is an abstract class
	virtual void Visit(const mwSolidDefinition<T>& visitor);


	/// Visit method for a mwRevolvedSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwRevolvedSolidDefinition, and makes it an exact copy of the
	/// passed object
	/// @param visitor a const reference to an existing mwRevolvedSolidDefinition object that will
	/// be cloned
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);


	/// Visit method for a mwExtrudedSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwExtrudedSolidDefinition, and makes it an exact copy of the
	/// passed object
	/// @param visitor a const reference to an existing mwExtrudedSolidDefinition object that will
	/// be cloned
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);


	/// Visit method for a mwMeshSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwMeshSolidDefinition, and makes it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwMeshSolidDefinition object that will be
	/// cloned
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);


	/// Visit method for a mwTurningSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwTurningSolidDefinition, and makes it an exact copy of the
	/// passed object
	/// @param visitor a const reference to an existing mwTurningSolidDefinition object that will be
	/// cloned
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);

	/// Visit method for a mwContourTurningSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwContourTurningSolidDefinition, and makes it an exact copy of
	/// the passed object
	/// @param visitor a const reference to an existing mwContourTurningSolidDefinition object that
	/// will be cloned
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);


	/// Visit method for a mwWireSolidDefinition objects, which are concrete solids
	///
	/// Creates a new object of type mwWireSolidDefinition, and makes it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwWireSolidDefinition object that will be
	/// cloned
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

#ifndef MW_USE_VS2008_COMPATIBILITY
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);
#endif

private:
	mwSolidDefinitionCloner& operator=(mwSolidDefinitionCloner&);  // avoid warning C4512
	/// Reference to an existing auto-pointer to a mwSolidDefinition derived object.
	/// After calling the Visit method for a concrete solid definition, this auto-pointer will
	/// contain the address of the newly created and cloned solid, obtained from the solid passed on
	/// Visit method
	typename mwSolidDefinition<T>::Ptr& ptrToSolid;
};
}  // namespace cadcam
#endif  //	MW_MWSOLIDDEFINITIONCLONER_HPP_
