// (C) 2006-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILEIOSTREAM_HPP_
#define MW_MWFILEIOSTREAM_HPP_
#define __CAN_USE_MW_FILE_IO_STREAM__

#include "mwDllImpExpDef.hpp"
#include "mwPresetIOStream.hpp"
#include "mwString.hpp"

#include <fstream>

namespace misc
{
class MW_5AXUTIL_API mwFileIOStream : public mwPresetIOStream
{
public:
	//! Create a file io stream
	/*!
		\param fileName filename of the file associated to the stream
	*/
	mwFileIOStream(const misc::mwstring& fileName, const bool in);

	//! Destructor
	virtual ~mwFileIOStream();

	//! Get data size
	/*!
		\returns length of the data
	*/
	virtual const uint64_t GetDataLength() const;


	//! Read data from the stream
	/*!
		\param data buffer to store the read data
		\param dataLen size of the buffer
	*/
	virtual void Read(void* data, uint64_t& dataLen);

	//! Writes data to the stream
	/*!
		\param data buffer with data
		\param dataLen length of the buffer
	*/
	virtual void Write(const void* data, const uint64_t& dataLen);

	//! Rewind
	/*!Sets the position of the internal pointer to the specified position.
		\param pos offset to set the pointer
	*/
	virtual void Rewind(const uint64_t& pos = 0);

	virtual void Flush();

	mwFileIOStream(const uint64_t&);

protected:
private:
#pragma warning(push)
#pragma warning(disable : 4251)

	mwFileIOStream(mwFileIOStream&);
	mwFileIOStream& operator=(mwFileIOStream&);
	typedef std::basic_fstream<char, std::char_traits<char>> MW_FILEIOSTREAM_TYPE;
	MW_FILEIOSTREAM_TYPE m_fstream;

#pragma warning(pop)
};
};  // namespace misc
#endif  //	MW_MWFILEIOSTREAM_HPP_
