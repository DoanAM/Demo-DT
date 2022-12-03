// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWNEUTRALRESOURCEDLL_HPP_
#define MW_MWNEUTRALRESOURCEDLL_HPP_
#if defined (_WIN32)

#include "mwStringConversions.hpp"
#include "mwDllImpExpDef.hpp"
#if defined (_WIN32)
#include <windows.h>
#endif

namespace misc
{
	/*!This class is used for interacting with a resource dll containing only 
	 neutral resources (like images). The dll has no resource used for internationalization (like string tables) */
	class MW_5AXUTIL_API  mwNeutralResourceDll
	{

	public:

		//!Default constructor
		mwNeutralResourceDll();

		//Constructor
		/*
			\Load a resource dll from a specified file
			\param fileName name of the resource dll file
		*/
		mwNeutralResourceDll(const misc::mwstring& fileName);

		//!Destructor
		~mwNeutralResourceDll();

		//!Gets the handler of resource dll library
		/*
			\returns HINSTANCE - handler of the resource dll library  
		*/
#if defined (_WIN32)
		inline const HINSTANCE GetResourceDllHandler() const
		{
			return m_hResourceDllInstance;
		}
#endif

		//!Set the name of the resource dll file to get resources from
		/*!Reads resources from the library file with a given name
			\param fileName name of the resource dll file
		*/
		void SetFile( const misc::mwstring& fileName );

		//!Gets the name of the resource dll file
		/*
			\returns the name of resource dll library 
		*/
		const misc::mwstring& GetFile() const;

		
		//!Unloads a resource dll file
		void UnloadResourceDll();

	protected:

	private:
		

		//!Loads a resource dll file
		void LoadResourceDll();

	
		misc::mwstring m_fileName;
#if defined (_WIN32)
		HINSTANCE m_hResourceDllInstance;
#endif
	};

};

#endif
#endif	//	MW_MWNEUTRALRESOURCEDLL_HPP_
