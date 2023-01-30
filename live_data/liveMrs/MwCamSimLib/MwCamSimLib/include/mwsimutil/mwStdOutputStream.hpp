// (C) 2003-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTDOUTPUTSTREAM_HPP_
#define MW_MWSTDOUTPUTSTREAM_HPP_
#include "mwAutoPointer.hpp"
#include "mwBinOutputStream.hpp"
#include "mwBinOutputStreamAdapter.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwFileName.hpp"
#include "mwStream.hpp"


namespace misc
{
//! STD stream implementation
/*!This class provides an mwBinOutputStream implementation for
	std:: streams and files
*/
#ifdef _WIN32

class
#if defined(_MSC_VER) && _MSC_VER > 1900  // VS2015 generates deprecation warnings/ errors on each
	// destructor call, which is not wanted
	MW_DEPRECATED("Deprecated since 2022.04, please use misc::mwBinOutputStreamAdapter.")
#endif
		MW_5AXUTIL_API mwStdOutputStream : public mwBinOutputStream
{
public:
	//! Default constructor
	/*!Construct an object an attaches it to the given std::ostream
		\param out stream to attach the new object to
	*/
	mwStdOutputStream(mwOStream& out);

	//! Default constructor
	/*!Constructs a stream object and attaches it to a file
		\param fileName name of the file to write the data to
	*/
	mwStdOutputStream(const mwstring& fileName);

	//! Write data to the stream
	/*!Writes given data to the stream
		\param data data to be written to the stream
		\param dataLen length of data
	*/
	virtual void Write(const void* data, const mwsize_t& dataLen);

	virtual void Flush();

	//! Get data
	/*!
		\returns pointer to the buffer with data
	*/
	virtual const void* GetBuffer() const;

	//! Get data size
	/*!
		\returns length of the data
	*/
	virtual const uint64_t GetDataLength() const;

protected:
private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	mwAutoPointer<mwOStream> m_out;
};
#else
MW_DEPRECATED("Deprecated since 2022.04, please use misc::mwBinOutputStreamAdapter.")
typedef mwBinOutputStreamAdapter mwStdOutputStream;
#pragma deprecated(mwStdOutputStream)  // For MSVC < 2017
#endif

MW_DEPRECATED("Deprecated since 2022.04, please use misc::mwBinOutputStreamAdapter.")
typedef mwBinOutputStreamAdapter mwStdBinaryStream;
#pragma deprecated(mwStdBinaryStream)  // For MSVC < 2017

}  // namespace misc
#endif  //	MW_MWSTDOUTPUTSTREAM_HPP_
