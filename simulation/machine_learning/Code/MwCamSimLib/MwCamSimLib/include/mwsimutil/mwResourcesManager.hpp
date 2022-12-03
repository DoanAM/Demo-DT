// (C) 2016-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWRESOURCESMANAGER_HPP_
#define MW_MWRESOURCESMANAGER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwMemoryIOStream.hpp"

#include <list>
#include <map>

namespace misc
{
	class MW_5AXUTIL_API mwResourcesManager
	{
	public:
#if defined (_WIN32) && !defined(UNDER_CE)

	
		/* !Writes resource to dll
			\param resourceFileName is the name of the resource we want to write in the dll
			\param resourceTypeName is the type of the resource we want to write
			\param dllName is the name of the dll in which we want to insert the resource
		*/
		static bool WriteResourcesToDll(const mwstring& resourceFileName, const mwstring& resourceTypeName, const mwstring& dllName);

	
		/* !Writes all resources from specified directory to dll
		\param resourcesDirectoryName is the name of the directory which contains the resource we want to write to dll
		\param resourceTypeName is the type of the resource we want to write
		\param dllName is the name of the dll in which we want to insert the resources
		*/
		static bool WriteResourcesFromDirectoryToDll(const mwstring& resourcesDirectoryName, const mwstring& resourceTypeName, const mwstring& dllFileName, const mwstring& fileFilterPattern = _T("*"));

		
		/* !Read all resources of given type from dll and write it on disk, in a new created file

		\param dllFileName is the name of the dll from which it extracts the resource
		\param resourceTypeName is the type of resource we want to extract
		
		*/

		static void ReadResourcesOfSameTypeFromDll(const mwstring& resourceTypeName, const mwstring& dllFileName, const mwstring& directoryNameToExtractTo = mwstring());

		/* !Read resource from dll and write it on disk, in a new created file

			\param dllFileName is the name of the dll from which it extracts the resource
			\param resourceTypeName is the type of resource we want to extract
			\param resourceFileName is the name of the resource we want to extract
			\param filename is the name of the file that will be created on disk, where the extracted resource will be written
		*/
		static void ReadResourceFromDll(const mwstring& resourceTypeName, 
										const mwstring& resourceFileName, 
										const mwstring& extractedResourceName, 
										const mwstring& dllFileName);

		static misc::mwMemoryIOStream ReadResourceFromDllToMemoryStream(const mwstring& resourceTypeName,
																								 const mwstring& resourceFileName,
																								 const mwstring& dllFileName);

		/* !Deletes resource from dll
		\param resourceFileName is the name of the resource we want to write in the dll
		\param resourceTypeName is the type of the resource we want to write
		\param dllName is the name of the dll in which we want to insert the resource
		*/
		static bool DeleteResourceFromDll(const mwstring& resourceFileName, const mwstring& resourceTypeName, const mwstring& dllFileName);

		static const std::list<misc::mwstring> GetListOfSameTypeFromDll(const mwstring& resourceTypeName, const mwstring& dllFileName);

		typedef unsigned int MsgNumT;
		typedef unsigned short LANGID;

		/// Updates the String Table inside the dll file found at \p pathToDll with the new
		///  strings given through \p stringResourcesMap.
		/// The updated dll file will be named as \p pathToUpdatedDll.
		/// By default, it uses the langID given by GetUserDefaultLangID()
		static void UpdateStringResourcesInDll(
			const std::map<MsgNumT, mwstring>& stringResourcesMap,
			const mwstring& pathToDll,
			const mwstring& pathToUpdatedDll);

		/// Updates the String Table inside the dll file found at \p pathToDll with the new
		///  strings given through \p stringResourcesMap.
		/// The updated dll file will be named as \p pathToUpdatedDll.
		/// You can also specify which String Table should be updated through the \p langID parameter.
		/// Use langID = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US) to select a different String Table to be updated
		static void UpdateStringResourcesInDll(
			const std::map<MsgNumT, mwstring>& stringResourcesMap,
			const mwstring& pathToDll,
			const mwstring& pathToUpdatedDll,
			const LANGID langID);

#endif
	};
}; //namespace
#endif	//	MW_MWRESOURCESMANAGER_HPP_
