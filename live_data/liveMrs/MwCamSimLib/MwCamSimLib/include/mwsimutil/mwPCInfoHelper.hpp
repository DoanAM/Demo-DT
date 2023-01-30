// (C) 2017-2021 by ModuleWorks GmbH
// Owner: MC Integration

/// \file
/// \brief Helper class for getting hardware/software serial numbers from the machine
///      user for MAC, HDD serial number, CPU hash, PC Name

#ifndef MW_MWPCINFOHELPER_HPP_
#define MW_MWPCINFOHELPER_HPP_

#if defined (_WIN32)

#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"

namespace misc
{
	///Extracts hardware information from local PC
	class MW_5AXUTIL_API mwPCInfoHelper
	{
	public:
		
		static const int HARDWARE_KEY_VERSION;
		static const misc::mwstring HARDWARE_KEY_MARKER;
		


	
		typedef misc::mwAutoPointer<mwPCInfoHelper> Ptr;
		
		///Get singleton instance of this class
		static Ptr GetInstance(); 
		

		/*! GetComputerIdentificationString
		* \brief Get a string intended  to uniquely identify this computer based on its hardware 
		*		components
		* \return identification string
		*/
		const misc::mwstring& GetComputerIdentificationString() const;
		
		/*! GetCPUHash
		* \return CPU Hash of this machine
		*/
		const misc::mwstring& GetCPUHash() const;
		
		/*! GetMACAddress
		* \return GetFirstMACAddress of this machine
		*/
		const misc::mwstring& GetMACAddress() const;
		
		/*! GetHardDriveSerialNumber
		* \return serial number of first physical hard drive of this machine
		*/
		const misc::mwstring& GetHardDriveSerialNumber() const;
		
		/*! GetPCName
		* \return PC name of this machine
		*/
		const misc::mwstring& GetPCName() const;
		

		//!Get serial number of the motherboard from this PC
		/*
			\return motherboard serial number
		*/
		const misc::mwstring& GetMotherboardSerialNumber() const;
		

		//!Checks if computer ID string contains hardware key version
		/*
			\return true if computer ID string contains hardware key version
					false otherwise
		*/
		const bool HasHardwareKeyVersion(const misc::mwstring& computerIDString) const;
		
		//!Gets hardware key version from computer identification string
		/*Throws exception if computer identification string doesn't contain hardware version
			\return hardware key version
		*/
		const int GetHardwareKeyVersion(const misc::mwstring& computerIDString) const;
		
	
	
	private:
	
		static const misc::mwstring DEFAULT_MAC_ADDRESS;
		static const misc::mwstring DEFAULT_HARD_DRIVE_SERIAL_NUMBER;
		static const misc::mwstring DEFAULT_PC_NAME;
		static const misc::mwstring DEFAULT_MOTHERBOARD_SERIAL_NUMBER;
		static const misc::mwstring FIELDS_SEPARATOR;
		
		/*! default constructor
		 */
		mwPCInfoHelper();
		
		//!Calculate serial number for hard drive and motherboard
		/*
			\param hardDriveSerialNo will return drive serial number
			\param motherboardSerialNo will return motherboard serial number
		*/
		void CalculateHardDriveAndMotherboardSerialNumbers(misc::mwstring& hardDriveSerialNo, 
														   misc::mwstring& motherboardSerialNo) const;
		
		/*! Initialize WMI related DB
		 * should be called only once otherwise it seems to through error
		 */
		void InitializeWMI() const;
		
		/*! GetPCName
		* \return the name of this PC
		*/
		const misc::mwstring CalculatePCName() const;
		
		/*! GetFirstMacAddress
		* \brief Get physical MAC address of the first Ethernet board
		* \return mac address
		*/
		const misc::mwstring CalculateFirstMACAddress() const;
		
		/*! GetCpuHash
		* \brief Get a cpu number obtained from cpu information representing the model; not unique; to
		* be used in combination with other information
		* \return cpu hash
		*/
		const misc::mwstring CalculateCPUHash() const;
		
		
		
		const misc::mwstring CalculateComputerIdentificationString() const;
		
		/*! Uninitialize WMI related DB
		 * should be called only once otherwise it seems to through error
		 */
		void UninitializeWMI() const;
	
		static Ptr m_instance;
		misc::mwstring m_PCName;
		misc::mwstring m_computerIdentificationString;
		misc::mwstring m_MACAddress;
		misc::mwstring m_hardDriveSerialNumber;
		misc::mwstring m_CPUHash;
		misc::mwstring m_motherboardSerialNumber;
	};
};//namespace misc
#endif
#endif //MW_MWPCINFOHELPER_HPP_