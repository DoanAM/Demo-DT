// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINREGORCUSTOMPARAMSTORAGE_HPP_
#define MW_MWWINREGORCUSTOMPARAMSTORAGE_HPP_
#if !defined(UNDER_CE)

#include "mwString.hpp"
#include "mwParamStorage.hpp"
#include "mwBasicTypes.hpp"

namespace misc
{
	/*This class uses either a mwWinRegParamStorage (default, if customer didn't setup a custom storage) 
	OR a custom storage class (if customer has setup one).
	!!! IMPORTANT : Please use this class instead of plain misc::mwWinRegParamStorage because there are 
	customers which prohibits registry access and therefore they pass a custom storage class.
	*/
	class MW_5AXUTIL_API mwWinRegOrCustomParamStorage : public mwParamStorage
	{
	public:


		//!Constructor
		mwWinRegOrCustomParamStorage(const misc::mwstring& companyName, 
									 const misc::mwstring& applicationName, 
									 const misc::mwstring& sectionName);

		//!Destructor
		~mwWinRegOrCustomParamStorage();

		//!Checks if Window registry storage class is used
		/*
			\return true if Windows registry storage class is used
					false if custom storage class is used
		*/
		const bool UseWinRegStorage()  const;
		const bool UseEnvStorage()  const;
		const bool UseCustomStorage()  const;


		

		virtual void WriteParamBool( const misc::mwstring &paramName, const bool paramValue );

		virtual const bool GetParamBool( const misc::mwstring &paramName, const bool defaultValue );

		virtual const bool GetParamBool( const misc::mwstring &paramName );

		virtual void WriteParamFloat( const misc::mwstring &paramName, const float paramValue );

		virtual const float GetParamFloat( const misc::mwstring &paramName, const float defaultValue );

		virtual const float GetParamFloat( const misc::mwstring &paramName );

		virtual void WriteParamDouble( const misc::mwstring &paramName, const double paramValue );

		virtual const double GetParamDouble( const misc::mwstring &paramName, const double defaultValue );

		virtual const double GetParamDouble( const misc::mwstring &paramName );

		virtual void WriteParamString( const misc::mwstring &paramName, const misc::mwstring &paramValue );

		virtual const misc::mwstring GetParamString( const misc::mwstring &paramName, const misc::mwstring &defaultValue );

		virtual const misc::mwstring GetParamString( const misc::mwstring &paramName );

		virtual void WriteParamInt( const misc::mwstring &paramName, const int paramValue );

		virtual const int GetParamInt( const misc::mwstring &paramName, const int defaultValue );

		virtual const int GetParamInt( const misc::mwstring &paramName );

		virtual void WriteParamUInt( const misc::mwstring &paramName, const unsigned int paramValue );

		virtual const unsigned int GetParamUInt( const misc::mwstring &paramName, const unsigned int defaultValue );

		virtual const unsigned int GetParamUInt( const misc::mwstring &paramName );

		virtual void WriteParamInt64( const misc::mwstring &paramName, const int64_t paramValue );

		virtual const int64_t GetParamInt64( const misc::mwstring &paramName, const int64_t defaultValue );

		virtual const int64_t GetParamInt64( const misc::mwstring &paramName );

		virtual void WriteParamUInt64( const misc::mwstring &paramName, const uint64_t paramValue );

		virtual const uint64_t GetParamUInt64( const misc::mwstring &paramName, const uint64_t defaultValue );

		virtual const uint64_t GetParamUInt64( const misc::mwstring &paramName );

		virtual void WriteParamLong( const misc::mwstring &paramName, const long paramValue );

		virtual const long GetParamLong( const misc::mwstring &paramName, const long defaultValue );

		virtual const long GetParamLong( const misc::mwstring &paramName );

		virtual void WriteParamULong( const misc::mwstring &paramName, const unsigned long paramValue );

		virtual const unsigned long GetParamULong( const misc::mwstring &paramName, const unsigned long defaultValue );

		virtual const unsigned long GetParamULong( const misc::mwstring &paramName );

		virtual void WriteParamShort( const misc::mwstring &paramName, const short paramValue );

		virtual const short GetParamShort( const misc::mwstring &paramName, const short defaultValue );

		virtual const short GetParamShort( const misc::mwstring &paramName );

		virtual void WriteParamUShort( const misc::mwstring &paramName, const unsigned short paramValue );

		virtual const unsigned short GetParamUShort( const misc::mwstring &paramName, const unsigned short defaultValue );

		virtual const unsigned short GetParamUShort( const misc::mwstring &paramName );

		virtual void WriteParamChar( const misc::mwstring &paramName, const char paramValue );

		virtual const char GetParamChar( const misc::mwstring &paramName, const char defaultValue );

		virtual const char GetParamChar( const misc::mwstring &paramName );

		virtual void WriteParamUChar( const misc::mwstring &paramName, const unsigned char paramValue );

		virtual const unsigned char GetParamUChar( const misc::mwstring &paramName, const unsigned char defaultValue );

		virtual const unsigned char GetParamUChar( const misc::mwstring &paramName );

		virtual valueList EnumerateSubsections() const;

		virtual valueList EnumerateValues() const;

		virtual void DeleteSubsection( const misc::mwstring &toDelete );

		virtual void DeleteParameter( const misc::mwstring & toDelete );

		virtual unsigned long GetParamBinary( const misc::mwstring &paramName, char **data );

		virtual void WriteParamBinary( const misc::mwstring &paramName, const char *data, const unsigned long dataLength );

		virtual const bool CanHoldLargeData() const;

	protected:

	private:
		mwWinRegOrCustomParamStorage& operator=(const mwWinRegOrCustomParamStorage&); // = delete

		misc::mwParamStorage* m_storagePtr;
		const bool m_isCustomStorage;
		const bool m_isEnvStorage;
	};//class
};//namespace

#endif
#endif	//	MW_MWWINREGORCUSTOMPARAMSTORAGE_HPP_
