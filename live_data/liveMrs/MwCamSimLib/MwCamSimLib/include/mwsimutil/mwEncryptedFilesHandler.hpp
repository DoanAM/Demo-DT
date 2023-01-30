// (C) 2007-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWENCRYPTEDFILESHANDLER_HPP_
#define MW_MWENCRYPTEDFILESHANDLER_HPP_
#include "mwDllImpExpDef.hpp"
#include <string>
#include "mwBasicTypes.hpp"
#include <cstddef>


#ifdef _WIN32
	#define MW_STDCALL __stdcall
#else
	#define MW_STDCALL
#endif


namespace misc
{
	class mwFileName;

	namespace mwEncryptedFilesHandler
	{
		//this functions allow you to write and read encrypted files
		//using a MW default AES key
		//we know to read such encrypted files in different applications
		//for now we know to read encrypted CL files, but probably more will follow
	
	//#############################################################################
		//C API
		//following section is design for easy access from any language so is wrote as "WinApi C style" on purpose
		//functions from this section will never throw
		
		//! encode and write pass data to specify file
		/*! returns 0 for success or one of the MW_Crypting_Error_Codes
			if the data is actually text data you need to let us know if the format is ASCII or UNICODE
			such as we know how to read it back 
		*/
		extern "C" MW_5AXUTIL_API 
			int MW_STDCALL Write(const char* outputFile,	
			const char* data, const std::uint64_t& dataLen, const bool isUnicode = false );
		//! read,decode and flush all in data buffer 
		/*! it allocates need memory with new operator, caller should handle the delete
			returns 0 for success or one of the MW_Crypting_Error_Codes
			we let you know if the saved data in the file was marked as unicode or not
		*/
		extern "C" MW_5AXUTIL_API
			int MW_STDCALL Read( const char* inputFile,
			char*& data, std::uint64_t& dataLen, bool& isUnicode  );

		//errors that we may return on upper functions calls
		enum MW_Crypting_Error_Codes
		{
			MW_CEC_NO_ERROR = 0,
			MW_CEC_UNKNOWN_ERROR ,
			MW_CEC_BAD_ALLOCATION,
			MW_CEC_FILE_ACCESS_FAIL,
			MW_CEC_UNKNOWN_FILE_FORMAT
		};
	
	//#############################################################################
		//C++ API
		// back to c++ style, please note, following function may throw 
		
		//! check for special markers inside the file
		MW_5AXUTIL_API bool IsmwEncryptedFile(const mwFileName& inputFile);
		
		//! read, decode and flush all in data buffer, overwrite what ever is there
		/*! we let you know if the saved data in the file was marked as unicode or not
		*/
		MW_5AXUTIL_API void Read( const mwFileName& inputFile, std::string& data, bool& isUnicode );

		//! read, decode and flush partially the file
		/*! reads the file from the beging upTo number of bytes asked for
			if the file is shorter then false is return 
			still data string is fill in with what found until eof reached
			we let you know if the saved data in the file was marked as unicode or not
		*/
		MW_5AXUTIL_API bool PartialRead(const mwFileName &inputFile,const std::size_t upTo, std::string& data, bool& isUnicode );
	} // mwEncryptedFilesHandler

} // misc
#endif	//	MW_MWENCRYPTEDFILESHANDLER_HPP_
