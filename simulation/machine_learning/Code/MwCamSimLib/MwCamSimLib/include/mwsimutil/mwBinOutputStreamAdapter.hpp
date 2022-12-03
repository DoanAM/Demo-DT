// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBINOUTPUTSTREAMADAPTER_HPP
#define MW_MWBINOUTPUTSTREAMADAPTER_HPP

#include "mwAutoPointer.hpp"
#include "mwBinOutputStream.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"  // MW_5AXUTIL_API


namespace misc
{
class mwFileName;

/// mwBinOutputStream implementation for std::ostreams (and files (deprecated!))
class MW_5AXUTIL_API mwBinOutputStreamAdapter : public mwBinOutputStream
{
public:
	/// Constructs a new mwBinOutputStream and attaches it to the given ostream
	/// Does not take the ownership of the stream!
	mwBinOutputStreamAdapter(std::ostream& out);

	/// Constructs a new mwBinOutputStream and attaches it to the given ostream
	/// Does take the ownership of the stream!
	mwBinOutputStreamAdapter(const misc::mwAutoPointer<std::ostream>& out);

	/// Constructs a new mwBinOutputStream by opening a file
	/// @param fileName path to the file
	MW_DEPRECATED(
		"Deprecated since 2022.04, please use the first constructor passing an std::ofstream or "
		"use misc::mwFileIOStream or misc::mwOFStream.")
	mwBinOutputStreamAdapter(const mwstring& fileName);

	/// Constructs a new mwBinOutputStream by opening a file
	/// @param fileName path to the file
	MW_DEPRECATED(
		"Deprecated since 2022.04, please use the first constructor passing an std::ofstream or "
		"use misc::mwFileIOStream or misc::mwOFStream.")
	mwBinOutputStreamAdapter(const misc::mwFileName& fileName);

	virtual void Write(const void* data, const mwsize_t& dataLen);
	virtual void Flush();
	virtual const void* GetBuffer() const;
	virtual const uint64_t GetDataLength() const;

protected:
private:
	mwAutoPointer<std::ostream> m_out;
};
}  // namespace misc
#endif  //	MW_MWBINOUTPUTSTREAMADAPTER_HPP
