// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBINIOSTREAMADAPTER_HPP
#define MW_MWBINIOSTREAMADAPTER_HPP

#include "mwAutoPointer.hpp"
#include "mwBinIOStream.hpp"
#include "mwDllImpExpDef.hpp"  // MW_5AXUTIL_API

namespace misc
{

/// mwBinIOStream implementation for std::iostreams
class MW_5AXUTIL_API mwBinIOStreamAdapter : public mwBinIOStream
{
public:
	/// Constructs a new mwBinIOStream and attaches it to the given iostream
	/// Does not take the ownership of the stream!
	explicit mwBinIOStreamAdapter(std::iostream& iostream);

	/// Constructs a new mwBinIOStream and attaches it to the given iostream
	/// Does take the ownership of the stream!
	explicit mwBinIOStreamAdapter(const misc::mwAutoPointer<std::iostream>& iostream);

	// Inherited from the base interface (mwBinIOStream)

	virtual void Read(void* data, mwBinInputStream::mwsize_t& dataLen);
	virtual void Write(const void* data, const mwBinOutputStream::mwsize_t& dataLen);
	virtual void Flush();
	virtual const void* GetBuffer() const;
	virtual const uint64_t GetDataLength() const;

protected:
private:
	misc::mwAutoPointer<std::iostream> m_iostream;
};
}  // namespace misc
#endif  //	MW_MWBINIOSTREAMADAPTER_HPP
