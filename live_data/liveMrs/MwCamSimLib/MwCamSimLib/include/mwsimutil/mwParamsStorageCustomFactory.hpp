// (C) 2018 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef __mwParamsStorageCustomFactory_hpp__
#define __mwParamsStorageCustomFactory_hpp__

#include "mwParamStorage.hpp"

namespace misc
{
	//! mwParamsStorageCustomFactory
	/*! By default the calculation will use Windows registry for saving persistent
		settings. It will use multiple subkeys as for example:
		HKEY_CURRENT_USER\Software\MW\5axcore\Caching
		HKEY_CURRENT_USER\Software\MW\5axcore\OpenmpParams
		each with its own set of parameters.
		The user can implement this factory to save the parameters
		in a different location.
	*/
	class MW_5AXUTIL_API mwParamsStorageCustomFactory
	{
	public:
		//! Default constructor
		mwParamsStorageCustomFactory() {}
		
		//! Default destructor
		virtual ~mwParamsStorageCustomFactory() {}
		
		/*! Create the custom parameter storage
			\return a pointer to the user implemented storage
		*/
		virtual mwParamStorage* CreateParamStorage(	
			const misc::mwstring& companyName,
			const misc::mwstring& applicationName,
			const misc::mwstring& sectionName
			) = 0;

		/*! Release the custom parameter storage
			The user can free the memory associated with the storage
		*/
		virtual void FreeParamStorage(
			const misc::mwstring& companyName,
			const misc::mwstring& applicationName,
			const misc::mwstring& sectionName
			) = 0;
	};

};//namespace

#endif // __mwParamsStorageCustomFactory_hpp__
