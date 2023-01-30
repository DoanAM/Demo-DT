// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINREGPARAMSTORAGE_HPP_
#define MW_MWWINREGPARAMSTORAGE_HPP_
#if defined (_WIN32) && !defined (UNDER_CE)

#include <mwParamStorage.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winreg.h>

#include "mwDllImpExpDef.hpp"


namespace misc
{
	//!MW_5AXUTIL_API class
	/*!This class represents a MW_5AXUTIL_API*/
	class MW_5AXUTIL_API mwWinRegParamStorage : public mwParamStorage
	{
	public:
		//!Construct a parameter storage object
		/*!
			\param companyName Company name or other top level id
			\param applicationName Name of the application or other application ID
			\param sectionName name of the section
		*/

		mwWinRegParamStorage( const string &companyName, const string &applicationName, const string &sectionName );
		
		//!Destructor
		virtual ~mwWinRegParamStorage();


		//!Set company id
		/*!
			\param companyName name of the company or other top level identifier
		*/
		virtual void SetCompanyName( const string &companyName );

		//!Set application name
		/*!
			\param applicationName name of the application
		*/
		virtual void SetApplicationName( const string &applicationName );

		//!Set section name
		/*!
			\param sectionName name of the section
		*/
		virtual void SetSectionName( const string &sectionName );



		//!Write a boolean parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamBool( const string &paramName, const bool paramValue );

		//!Get a boolean parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage or 
			a failure occurred
		*/
		virtual const bool GetParamBool( const string &paramName, const bool defaultValue );

		//!Get a boolean parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const bool GetParamBool( const string &paramName );


		
		//!Write a float parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamFloat( const string &paramName, const float paramValue ) ;

		//!Get a float parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const float GetParamFloat( const string &paramName, const float defaultValue );

		//!Get a double parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const float GetParamFloat( const string &paramName );
		


		//!Write a double parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamDouble( const string &paramName, const double paramValue );

		//!Get a double parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const double GetParamDouble( const string &paramName, const double defaultValue );

		//!Get a double parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const double GetParamDouble( const string &paramName );



		//!Write a string parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamString( const string &paramName, const string &paramValue );

		//!Get a string parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const string GetParamString( const string &paramName, const string &defaultValue );

		//!Get a string parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const string GetParamString( const string &paramName );



		//!Write an int parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamInt( const string &paramName, const int paramValue );

		//!Get an int parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with 
			the given name couldn't be found in the parameter storage or a 
			failure occurred
		*/
		virtual const int GetParamInt( const string &paramName, const int defaultValue );

		//!Get an int parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const int GetParamInt( const string &paramName );



		//!Write an unsigned int parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUInt( const string &paramName, const unsigned int paramValue );

		//!Get an unsigned int parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const unsigned int GetParamUInt( const string &paramName, const unsigned int defaultValue );

		//!Get an unsigned int parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const unsigned int GetParamUInt( const string &paramName );



		//!Write an int64 parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamInt64( const string &paramName, const int64_t paramValue );

		//!Get an int64 parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with
			the given name couldn't be found in the parameter storage or a 
			failure occurred
		*/
		virtual const int64_t GetParamInt64( const string &paramName, const int64_t defaultValue );

		//!Get an int64 parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const int64_t GetParamInt64( const string &paramName );



		//!Write an unsigned int64parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUInt64( const string &paramName, const uint64_t paramValue );

		//!Get an unsigned int64 parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const uint64_t GetParamUInt64( const string &paramName,	const uint64_t defaultValue );

		//!Get an unsigned int64 parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const uint64_t GetParamUInt64( const string &paramName );



		//!Write a long parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamLong( const string &paramName, const long paramValue );

		//!Get a long parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const long GetParamLong( const string &paramName, const long defaultValue );

		//!Get a long parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const long GetParamLong( const string &paramName );
	


		//!Write an unsigned long parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamULong( const string &paramName, const unsigned long paramValue );

		//!Get an unsigned long parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const unsigned long GetParamULong( const string &paramName, const unsigned long defaultValue );

		//!Get an unsigned long parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const unsigned long GetParamULong( const string &paramName );



		//!Write a short parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamShort( const string &paramName, const short paramValue );

		//!Get a short parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with 
			the given name couldn't be found in the parameter storage or a 
			failure occurred
		*/
		virtual const short GetParamShort( const string &paramName, const short defaultValue );

		//!Get a short parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const short GetParamShort( const string &paramName );



		//!Write an unsigned short parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUShort( const string &paramName, const unsigned short paramValue );

		//!Get an unsigned short parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const unsigned short GetParamUShort( const string &paramName, const unsigned short defaultValue );

		//!Get an unsigned short parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const unsigned short GetParamUShort( const string &paramName );
		


		//!Write a char parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamChar( const string &paramName, const char paramValue );

		//!Get a char parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const char GetParamChar( const string &paramName, const char defaultValue );

		//!Get a char parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const char GetParamChar( const string &paramName );



		//!Write an unsigned char parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUChar( const string &paramName, const unsigned char paramValue );

		//!Get an unsigned char parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter 
			with the given name couldn't be found in the parameter storage 
			or a failure occurred
		*/
		virtual const unsigned char GetParamUChar( const string &paramName, const unsigned char defaultValue );

		//!Get an unsigned char parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to 
			GetParam* is that if the parameter is not in the storage an 
			exception is raised
		*/
		virtual const unsigned char GetParamUChar( const string &paramName );



		//!Enumerate subsections of the current section
		/*!
			Get a list of subsections for the given section
		*/
		virtual valueList EnumerateSubsections() const;

		//!Enumerate values
		/*!
			Get the list of parameters in the current cross section
		*/
		virtual valueList EnumerateValues() const;

		//!Delete subsection of the current section
		/*!
			Delete a subsection with the given name
		*/
		virtual void DeleteSubsection( const string &toDelete );

		//!Delete a parameter
		/*!
			Delete a parameter with the given name in the current section
		*/
		virtual void DeleteParameter( const string & toDelete );



		virtual unsigned long GetParamBinary( const string &paramName, char **data );
		
		//!Write binary data to the param storage
		virtual void WriteParamBinary( const string &paramName, const char *data, const unsigned long dataLength );



		//CanHoldLargeData
		/*!Asks whether the preset stream can hold large data (memory-oriented
			cannot, while disk-oriented should be able to do so
			\returns if preset stream is supposed to hold large quantities or not
		*/
		virtual const bool CanHoldLargeData() const;

		
	protected:
	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	
		template <typename T>
		void WriteParam( const string &paramName, const T paramValue );

		template <typename T>
		T GetParam( const string &paramName);

		template <typename T>
		T GetParam( const string &paramName, const T defaultValue );

		mwWinRegParamStorage& operator = (mwWinRegParamStorage&);
		mwWinRegParamStorage(const mwWinRegParamStorage&);

		//gets error message for a system error and formats it nice
		const string GetFormatedSystemError(const string &errorDescription, const string& paramName, const LONG errorNo )const;
		HKEY mRegKey;

		void OpenRegistry( );

		const unsigned long MaxRegistryBinarySize;
		const DWORD TempFileMarker;
		const string TempFileExtension;
	
	#pragma warning(pop)
	};
};

#endif
#endif	//	MW_MWWINREGPARAMSTORAGE_HPP_
