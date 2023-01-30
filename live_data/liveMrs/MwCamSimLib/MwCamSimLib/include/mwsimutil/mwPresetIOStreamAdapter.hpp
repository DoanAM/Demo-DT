// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPRESETIOSTREAMADAPTER_HPP
#define MW_MWPRESETIOSTREAMADAPTER_HPP

#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"  // MW_5AXUTIL_API
#include "mwPresetIOStream.hpp"

namespace misc
{

/// mwPresetIOStream implementation for std::iostreams
class MW_5AXUTIL_API mwPresetIOStreamAdapter : public mwPresetIOStream
{
public:
	/// Constructs a new mwPresetIOStream and attaches it to the given iostream
	/// Does not take the ownership of the stream!
	explicit mwPresetIOStreamAdapter(std::iostream& iostream);

	/// Constructs a new mwPresetIOStream and attaches it to the given iostream
	/// Does take the ownership of the stream!
	explicit mwPresetIOStreamAdapter(const misc::mwAutoPointer<std::iostream>& iostream);

	// Inherited from the base interface (mwPresetIOStream)

	virtual void Read(void* data, mwBinInputStream::mwsize_t& dataLen);
	virtual void Write(const void* data, const mwBinOutputStream::mwsize_t& dataLen);
	virtual void Flush();
	virtual void Rewind(const uint64_t& pos);
	virtual const void* GetBuffer() const;
	virtual const uint64_t GetDataLength() const;

protected:
private:
	misc::mwAutoPointer<std::iostream> m_iostream;
};
}  // namespace misc
#endif  //	MW_MWPRESETIOSTREAMADAPTER_HPP
