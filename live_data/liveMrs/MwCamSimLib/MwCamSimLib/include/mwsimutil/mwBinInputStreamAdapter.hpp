// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBININPUTSTREAMADAPTER_HPP_
#define MW_MWBININPUTSTREAMADAPTER_HPP_

#include "mwAutoPointer.hpp"
#include "mwBinInputStream.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"  // MW_5AXUTIL_API
#include "mwWarningPragmas.hpp"

namespace misc
{

/// mwBinInputStream implementation for std::istreams (and files (deprecated!))
class MW_5AXUTIL_API mwBinInputStreamAdapter : public mwBinInputStream
{
public:
	MW_DEPRECATED("Deprecated since 2022.04, please just use (std::)uint64_t.")
	typedef ::misc::uint64_t uint64_t;

	/// Constructs a new mwBinInputStream and attaches it to the given istream
	/// Does not take the ownership of the stream!
	explicit mwBinInputStreamAdapter(std::istream& stream);

	/// Constructs a new mwBinInputStream and attaches it to the given istream
	/// Does take the ownership of the stream!
	explicit mwBinInputStreamAdapter(const misc::mwAutoPointer<std::istream>& stream);

	/// Constructs a new mwBinInputStream by opening a file
	/// @param fileName path to the file
	MW_DEPRECATED(
		"Deprecated since 2022.04, please call the first constructor using an std::ifstream or use "
		"misc::mwFileIOStream or misc::mwIFStream.")
	explicit mwBinInputStreamAdapter(const mwstring& fileName);

	virtual ~mwBinInputStreamAdapter();

	// Inherited from the base interface (mwBinInputStream)

	virtual void Read(void* data, mwsize_t& dataLen);
	virtual const void* GetBuffer() const;
	virtual const ::misc::uint64_t GetDataLength() const;

	MW_DEPRECATED(
		"Deprecated since 2022.04, as this method is not part of the base interface "
		"mwBinInputStream")
	void Rewind(const ::misc::uint64_t& pos = 0);

protected:
private:
	MW_WARNING_SUPPRESS_DLLINTERFACE
	mwAutoPointer<std::istream> m_in;
};
}  // namespace misc
#endif  //	MW_MWBININPUTSTREAMADAPTER_HPP_
