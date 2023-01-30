// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWPOSTDEFINITIONCONTAINER_HPP_
#define MW_MWPOSTDEFINITIONCONTAINER_HPP_
//#############################################################################
#include "mwPostDefinition.hpp"
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostDefinitionContainer
	{
	public:
		//#############################################################################
		typedef misc::mwstring id;
		typedef std::vector<id> idVector;
		//#############################################################################
		mwPostDefinitionContainer(){};
		//#############################################################################
		mwPostDefinitionContainer(const mwPostDefinitionPtrVect& defs);
		//#############################################################################
		mwPostDefinitionContainer(const mwPostDefinitionPtr& def);
		//#############################################################################
		mwPostDefinitionContainer(const mwPostDefinitionContainer &toCopy);
		//#############################################################################
		const mwPostDefinitionContainer& operator = (const mwPostDefinitionContainer& toCopy);
		//#############################################################################
		const bool operator == (const mwPostDefinitionContainer& toCompare) const;
		//#############################################################################
		const bool operator != (const mwPostDefinitionContainer& toCompare) const;
		//#############################################################################
		const mwPostDefinitionPtr& GetPostDefinition(const id& _id) const;
		//#############################################################################
		mwPostDefinitionPtr& GetPostDefinition(const id& _id);
		//#############################################################################
		void AddPostDefinition(const mwPostDefinitionPtr& postDef);
		//#############################################################################
		void RemovePostDefinition(const id& _id);
		//#############################################################################
		void RemoveAllPostDefinitions();
		//#############################################################################
		void ChangePostDefinition(const id& _id, const mwPostDefinitionPtr& postDef);
		//#############################################################################
		const mwPostDefinitionPtrVect& GetAllPostDefinitions() const;
		//#############################################################################
		mwPostDefinitionPtrVect& GetAllPostDefinitions();
		//#############################################################################
		void SetAllPostDefinitions(const mwPostDefinitionPtrVect& defs);
		//#############################################################################
		const idVector GetAvailablePostDefinitionsIDs() const;
		//#############################################################################
		const size_t GetSize() const;
		//#############################################################################
	private:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################
		mwPostDefinitionPtrVect m_postDefs;
		//#############################################################################
		void Copy(const mwPostDefinitionContainer &toCopy);
		//#############################################################################
#pragma warning(pop)
	};
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTDEFINITIONCONTAINER_HPP_
