// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MC Integration

#ifndef MW_MWHARDWARELICENSEREQUESTUTILS_HPP_
#define MW_MWHARDWARELICENSEREQUESTUTILS_HPP_

#if defined (_WIN32)

#include "mwBasicTypes.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHardwareLicenseRequest.hpp"

namespace misc
{
	class mwMemoryIOStream;
	class mwCompilerBIBasicTypes;
	class mwCompilerBOBasicTypes;
	
	///Utility for a mwHardwareLicenseRequest object
	class MW_5AXUTIL_API mwHardwareLicenseRequestUtils
	{
	public:
		
		enum FileWriteFormat
		{
			FWF_BINARY,
			FWF_JSON
		};
		static const unsigned int REQUEST_VERSION;
		
		
		static void ReadRequestFromFile(
			const misc::mwstring& fileName, 
			mwHardwareLicenseRequest& requestData);

		static void  WriteRequestToFile(
			const misc::mwstring& fileName, 
			const mwHardwareLicenseRequest& requestData,
			const FileWriteFormat writeFormat= FWF_BINARY);
		
	private:
	
		
		static void ReadRequestFromMemoryStream(
			const misc::mwMemoryIOStream& memStream,
			mwHardwareLicenseRequest& requestData);

		static void  WriteRequestToMemoryStream(
			misc::mwMemoryIOStream& memStream, 
			const mwHardwareLicenseRequest& requestData);

		static void ReadRequestedProducts(
			const unsigned int requestVersion,
			misc::mwCompilerBIBasicTypes& streamReader, 
			mwHardwareLicenseRequest::RequestedProducts& productInfos);

		static void WriteRequestedProducts(
			const mwHardwareLicenseRequest::RequestedProducts& productInfos,
			misc::mwCompilerBOBasicTypes& streamWriter);

		static void WriteRequestToFileInBinaryFormat(
			const misc::mwstring& fileName, 
			const mwHardwareLicenseRequest& requestData);

		static void WriteRequestToFileInJSONFormat(
			const misc::mwstring& fileName, 
			const mwHardwareLicenseRequest& requestData);

		static void ReadRequestFromFileInBinaryFormat(
			const misc::mwstring& fileName, 
			mwHardwareLicenseRequest& requestData);

		static void ReadRequestFromFileInJSONFormat(
			const misc::mwstring& fileName, 
			mwHardwareLicenseRequest& requestData);

		//!Class members
		static const unsigned int FILE_MARKER;

		static const uint64_t  MEMORY_STREAM_SIZE_IN_BYTES;
	};
};//namespace
#endif
#endif //MW_MWHARDWARELICENSEREQUESTUTILS_HPP_