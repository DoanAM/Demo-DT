// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPARAMSTORAGE_HPP_
#define MW_MWPARAMSTORAGE_HPP_
#include <list>
#include "mwStringConversions.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwNameValue.h"
#include "mwBasicTypes.hpp"



namespace misc
{
	class mwParamStorageException;

	class MW_5AXUTIL_API mwParamStorage
	{
	public:

		/*! \var typedef misc::mwstring             string
		    \brief A type redefinition for
			    misc::mwstring            				as string
		*/
		typedef misc::mwstring				string;

		/*! \var typedef std::list< string >     valueList
		    \brief A type redefinition for
			    std::list< string >    				as valueList
		*/

		typedef std::list< mwPresetNames >		valueList;

		//!Construct a parameter storage object
		/*!
			\param companyName Company name or other top level id
			\param applicationName Name of the application or other application ID
			\param sectionName name of the section
		*/

		mwParamStorage( const string &companyName, const string &applicationName, const string &sectionName );
		
		//!Destructor
		virtual ~mwParamStorage();



		//!Set company id
		/*!
			\param companyName name of the company or other top level identifier
		*/
		virtual void SetCompanyName( const string &companyName );

		//!Get company id
		/*!
			\returns currently set id of the company
		*/
		virtual const string &GetCompanyName() const;

		//!Set application name
		/*!
			\param applicationName name of the application
		*/
		virtual void SetApplicationName( const string &applicationName );

		//!Get application name
		/*!
			\returns application name
		*/
		virtual const string &GetApplicationName() const;

		//!Set section name
		/*!
			\param sectionName name of the section
		*/
		virtual void SetSectionName( const string &sectionName );

		//!Get current section name
		/*!
			\returns name of the section the parameters are currently occurred to
		*/
		virtual const string &GetSectionName() const;



		//!Write a boolean parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamBool( const string &paramName, const bool paramValue ) = 0;

		//!Get a boolean parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const bool GetParamBool( const string &paramName, const bool defaultValue ) = 0;

		//!Get a boolean parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const bool GetParamBool( const string &paramName ) = 0;


		
		//!Write a float parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamFloat( const string &paramName, const float paramValue ) = 0;

		//!Get a float parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const float GetParamFloat( const string &paramName, const float defaultValue ) = 0;

		//!Get a double parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const float GetParamFloat( const string &paramName ) = 0;
		


		//!Write a double parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamDouble( const string &paramName, const double paramValue ) = 0;

		//!Get a double parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const double GetParamDouble( const string &paramName, const double defaultValue ) = 0;

		//!Get a double parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const double GetParamDouble( const string &paramName ) = 0;


		//!Write a string parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamString( const string &paramName, const string &paramValue ) = 0;

		//!Get a string parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const string GetParamString( const string &paramName, const string &defaultValue ) = 0;

		//!Get a string parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const string GetParamString( const string &paramName ) = 0;


		//!Write an int parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamInt( const string &paramName, const int paramValue ) = 0;

		//!Get an int parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const int GetParamInt( const string &paramName, const int defaultValue ) = 0;

		//!Get an int parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const int GetParamInt( const string &paramName ) = 0;


		//!Write an unsigned int parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUInt( const string &paramName, const unsigned int paramValue ) = 0;

		//!Get an unsigned int parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const unsigned int GetParamUInt( const string &paramName, const unsigned int defaultValue ) = 0;

		//!Get an unsigned int parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const unsigned int GetParamUInt( const string &paramName ) = 0;

		
		//!Write an int64 parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/
		virtual void WriteParamInt64( const string &paramName, const ::misc::int64_t paramValue ) = 0;


		//!Get an int64 parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const ::misc::int64_t GetParamInt64( const string &paramName, const ::misc::int64_t defaultValue ) = 0;
		//!Get an int64 parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const ::misc::int64_t GetParamInt64( const string &paramName ) = 0;

		//!Write an unsigned int64parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUInt64( const string &paramName, const ::misc::uint64_t paramValue )= 0;

		//!Get an unsigned int64 parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const ::misc::uint64_t GetParamUInt64( const string &paramName, const ::misc::uint64_t defaultValue ) = 0;
		//!Get an unsigned int64 parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const ::misc::uint64_t GetParamUInt64( const string &paramName ) = 0;


		//!Write a long parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamLong( const string &paramName, const long paramValue ) = 0;

		//!Get a long parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const long GetParamLong( const string &paramName, const long defaultValue ) = 0;

		//!Get a long parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const long GetParamLong( const string &paramName ) = 0;
	

		//!Write an unsigned long parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamULong( const string &paramName, const unsigned long paramValue ) = 0;

		//!Get an unsigned long parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const unsigned long GetParamULong( const string &paramName, const unsigned long defaultValue ) = 0;

		//!Get an unsigned long parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const unsigned long GetParamULong( const string &paramName ) = 0;


		//!Write a short parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamShort( const string &paramName, const short paramValue ) = 0;

		//!Get a short parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const short GetParamShort( const string &paramName, const short defaultValue ) = 0;

		//!Get a short parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const short GetParamShort( const string &paramName ) = 0;


		//!Write an unsigned short parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUShort( const string &paramName, const unsigned short paramValue ) = 0;

		//!Get an unsigned short parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const unsigned short GetParamUShort( const string &paramName, const unsigned short defaultValue ) = 0;

		//!Get an unsigned short parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const unsigned short GetParamUShort( const string &paramName ) = 0;
		

		//!Write a char parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamChar( const string &paramName, const char paramValue ) = 0;

		//!Get a char parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const char GetParamChar( const string &paramName, const char defaultValue ) = 0;

		//!Get a char parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const char GetParamChar( const string &paramName ) = 0;


		//!Write an unsigned char parameter to the parameter storage
		/*!
			\param paramName name of the parameter
			\param paramValue value to be stored
			\remark throws an exception if the parameter couldn't be written
		*/	
		virtual void WriteParamUChar( const string &paramName, const unsigned char paramValue ) = 0;

		//!Get an unsigned char parameter with a given name
		/*!
			\param paramName name of the parameter to get the value of
			\param defaultValue default value. Will be set if a parameter with the given name
			couldn't be found in the parameter storage or a failure occurred
		*/
		virtual const unsigned char GetParamUChar( const string &paramName, const unsigned char defaultValue ) = 0;

		//!Get an unsigned char parameter with the given name
		/*!
			Get a parameter with the given name. The only difference to GetParam* is that 
			if the parameter is not in the storage an exception is raised
		*/
		virtual const unsigned char GetParamUChar( const string &paramName ) = 0;
		
		
		//!Enumerate subsections of the current section
		/*!
			Get a list of subsections for the given section
		*/
		virtual valueList EnumerateSubsections() const = 0;

		//!Enumerate values
		/*!
			Get the list of parameters in the current cross section
		*/
		virtual valueList EnumerateValues() const = 0;

		//!Delete subsection of the current section
		/*!
			Delete a subsection with the given name
		*/
		virtual void DeleteSubsection( const string &toDelete ) = 0;


		//!Delete a parameter
		/*!
			Delete a parameter with the given name in the current section
		*/
		virtual void DeleteParameter( const string & toDelete ) = 0;
		

		//!Get binary data from param storage
		/*!
			Returns pointer to the dynamically allocated buffer that contains
			the binary data of the parameter
			@returns number of bytes in the data
		*/
		virtual unsigned long GetParamBinary( const string &paramName, char **data ) = 0;
		
		//!Write binary data to the param storage
		virtual void WriteParamBinary( const string &paramName, const char *data, const unsigned long dataLength ) = 0;

		//CanHoldLargeData
		/*!Asks whether the storage can hold large data (memory-oriented
			cannot, while disk-oriented should be able to do so
			\returns if storage is supposed to hold large quantities or not
		*/
		virtual const bool CanHoldLargeData() const = 0;
		
		

	protected:
	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	

		misc::mwstring mCompanyID;
		misc::mwstring mApplicationID;
		misc::mwstring mSectionID;
	
	#pragma warning(pop)
	};
};
#endif	//	MW_MWPARAMSTORAGE_HPP_
