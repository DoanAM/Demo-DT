// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWDATAINTEGRITYUTILS_HPP_
#define MW_MWDATAINTEGRITYUTILS_HPP_
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwStream.hpp"
#include "mwBasicTypes.hpp"

/*
This class is used for adding mechanism of controlling data integrity.
Example of controlling data integrity for a file:
When the file is written,an additional checksum calculated based on file content is added to the file.
When the same file is readed, a new checksum is calculated and compared with the existing one in the file.
If the two checksums are different, there is a data corruption.
*/
namespace misc
{
	class mwMemoryIOStream;

	class MW_5AXUTIL_API mwDataIntegrityUtils
	{
	
	public:

		//!Adds a checksum information to a file
		/*
			\param fileName is the name of the file to add checksum to
		*/
		static void AddChecksumToFile(const misc::mwstring& fileName);

		//!Verify if a checksum stored in a file is the same with the checksum calculated from file
		/*	It is assumed that the passed file contains a checksum calculated and stored inside
			If the two checksums are different, the file was modified
			\return true if the stored and calculated checksum are the same
					false otherwise
		*/

		static bool VerifyChecksumFromFile(const misc::mwstring& fileName);
		static bool VerifyChecksumFromFile(std::istream& fileStrm);		

		//!Adds a checksum to a memory stream
		/*
			\param strm the memory stream to add checksum
		*/
		static void AddChecksum(misc::mwMemoryIOStream& strm);

		//! Verify if a checksum stored in a memory stream is the same with the checksum calculated from stream
		/*
			\param strm the memory stream for which to test the checksum
			\if the memory stream doesn't contain a checksum, an exception is thrown
		*/
		static bool VerifyChecksum(misc::mwMemoryIOStream& strm);

		//!Test if a memory stream has a checksum inside
		/*
			\param strm the stream to test if contains a checksum
		*/

		static bool HasChecksum(misc::mwMemoryIOStream& strm);

		//!Return checksum for a file
		/*
			\param fileName is the path to file
		*/

		static std::string GetChecksum(const misc::mwstring& fileName);

		//!Return size of checksum block (in bytes) which is written to the stream 
		/*
			\return checksum block size in bytes
		*/
		static size_t GetChecksumBlockSize();
		static size_t GetMarkerSize();
		static unsigned long GetBinaryMarker();

	protected:

	private:

		//!Calculate a checksum for a file
		/*
			\param inFile file stream to calculate the checksum for
			\param fileUtilSize the dimension in bytes, starting from file begining, 
			 for which is calculated the checksum
			\return the checksum calculated from file
		*/
		static std::string CalculateFileChecksum(std::istream& inFile,
													const size_t fileUtilSize);

		//!Calculate a checksum for a memory stream
		/*
			\param strm the memory stream to calculate the checksum for
			\param streamUtilSize the dimension in bytes, starting from the beggining of the stream,
			for which is calculated the checksum
			\return the checksum calculated from memory stream
		*/
		typedef ::misc::uint64_t uint64_t;
		static std::string CalculateChecksum(misc::mwMemoryIOStream& strm,const uint64_t streamUtilSize);


		static const size_t m_checksumBlockSize;
		static const size_t m_markerSize;
		static const unsigned long MWCP_BINARY_MARKER;
		
	};

};
#endif	//	MW_MWDATAINTEGRITYUTILS_HPP_
