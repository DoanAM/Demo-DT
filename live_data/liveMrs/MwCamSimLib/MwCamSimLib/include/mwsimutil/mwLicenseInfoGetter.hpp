// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWLICENSEINFOGETTER_HPP_
#define MW_MWLICENSEINFOGETTER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwAutoPointer.hpp"
#if defined (_WIN32) && !defined(MW_NO_LICENSE_CHECK)
#include "mwLicenseTypes.hpp"
#else
namespace mwLicenseAPI
{
	enum
	{
		MAX_ARRAY_SIZE = 255
	};
	enum LicenseType
	{
		LAST_TYPE_USED_FOR_VALIDATIONS
	};
}
#endif
#include "mwDeprecated.hpp"

namespace misc
{	
	class mwPresetIOStream;
}

namespace misc
{
	//!This class gets various information about license file
	class MW_5AXUTIL_API mwLicenseInfoGetter
	{
		public:		
			typedef std::vector <int>	LicensedTypes;	 //contains types of licenses currently available for checked product
			typedef std::pair <mwLicenseAPI::LicenseType,misc::mwstring> LicenseTypeAndName;//keeps license ID and name
	//#############################################################################
			//!Constructor
			/*
				\param licenseFileFullName is full path and name to the license file to get info from
				e.g. "d:\\license\\mwSupport.dll"
				An exception is thrown if license file is not found or cannot be read (due to old format,etc)
			*/
			MW_DEPRECATED("Deprecated 2016_04 , the path to the mwSupport does not need to be set.")
				mwLicenseInfoGetter(const misc::mwstring& licenseFileFullName);
	//#############################################################################
			//!Constructor
			/*
				\param strm is a stream from where license info will be read
				\exception mwmiscException
				An exception is thrown if license file is not found or cannot be read (due to old format,etc)
			*/
			mwLicenseInfoGetter(misc::mwPresetIOStream& strm, const bool silent = true);
	//#############################################################################
			mwLicenseInfoGetter();
			//!Destructor
			~mwLicenseInfoGetter();
	//#############################################################################
			//!Set new license stream to use
			/*
				\param the reference to the stream to be used 
				\exception mwmiscException
			*/		
			void SetLicenseStream(misc::mwPresetIOStream& strm, const bool silent = true);
	//#############################################################################
			//!Check if module specified is licensed in the current license 
			/*
				\param the  index of a module found in 	mwLicenseAPI::LicenseType
				\return bool true if the specified module has that license 
				\exception mwmiscException
			*/
			bool IsLicensed(const mwLicenseAPI::LicenseType checkedLicense, const bool silent = true) const;
	//#############################################################################
			//!Check if module specified is licensed in the current license 
			/*
				\return bool true if the watermark should be displayed 	   				
			*/
			bool IsWaterMarkImposed() const;
	//#############################################################################
			//!Return vendor name from license
			/*
				\return vendor name
			*/
			const misc::mwstring GetVendorName() const;
	//#############################################################################
			//!Return build version which has been used to generate the license
			/*
				\return a string containing build version information in our format,
				like for example: 2012.08.30.0
			*/
			const misc::mwstring GetBuildVersion() const;
	//#############################################################################
			//!Test if build version which has been used to generate the license was an Official Release build
			/*
				\return true if license has been generated with an OfficialRelease build
						false if license has been generated with a Daily build
			*/
			const bool IsOfficialReleaseBuild() const;
	//#############################################################################
			//!Test if license is evaluation or full
			/*
				\return true if it is an evaluation license
						false if it is a full license
			*/
			const bool IsEvaluation(mwLicenseAPI::LicenseType checkedLicense = mwLicenseAPI::LAST_TYPE_USED_FOR_VALIDATIONS) const;
	//#############################################################################
			//!Gets evaluation expire date for an evaluation license
			/* User should ask first IsEvaluation() function and if it returns true
			  then call this function to get license expire date
			   \ return license expire date as a string in format yyyy/mm/dd
			*/
			
			const misc::mwstring GetEvaluationExpireDate(mwLicenseAPI::LicenseType checkedLicense = mwLicenseAPI::LAST_TYPE_USED_FOR_VALIDATIONS) const;
	//#############################################################################
			//!Get types currently licensed for the given licensed product type
			/*
				\param licProducts is licensed product types to be checked.
			*/
			const LicensedTypes GetLicensedTypes() const; 
	//#############################################################################
			//!Utility function,gets info about all public licenses currently implemented by MW
			/*
				\return a vector containing pairs (license type,license name) for all 
				public licenses currently implemented by MW
			*/
			static std::vector <LicenseTypeAndName> GetAllLicensesTypesAndNames();
		
			//!Utility function,gets name of a license as string from license type
			/*
				\param licenseType is license type to get the name from
				\return license name as string for the input license type
			*/
			static misc::mwstring GetLicenseNameFromType(
				const mwLicenseAPI::LicenseType& licenseType);

			//!Checks if hardware key is attached to this license
			/*
				\return true a hardware key is attached  to this license
						false if no hardware key is attached to this license
			*/
			bool HasHardwareKey() const;

			//!Checks if hardware key attached to this license is valid
			/*
				\return true if a hardware key is attached to license and it is valid
					false if a hardware key is attached to license and it is not valid
					or if no hardware key is attached.
			*/
			bool IsHardwareKeyValid() const;
	};
};//namespace
#endif	//	MW_MWLICENSEINFOGETTER_HPP_
