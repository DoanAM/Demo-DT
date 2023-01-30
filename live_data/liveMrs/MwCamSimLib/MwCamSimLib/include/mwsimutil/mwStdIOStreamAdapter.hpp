// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTDIOSTREAMADAPTER_HPP_
#define MW_MWSTDIOSTREAMADAPTER_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY

#include "mwBinIOStream.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwWarningPragmas.hpp"

#include <iostream>
#include <memory>

namespace misc
{
class mwStdIOStreamAdapterImpl;

/// Adapter to convert a mwBinIOStream or mwPresetIOStream into a std::iostream
/// If an mwPresetIOStream is given, it also supports seeking
///
/// Sample usage:
/// void SaveAndLoad(std::iostream& s);
/// void SaveAndLoad(mwBinIOStream& s)
/// {
///    SaveAndLoad(misc::mwStdIOStreamAdapter(s).get());
/// }
class MW_5AXUTIL_API mwStdIOStreamAdapter
{
public:

	/// Constructs the adapter class and attaches it to the given mwBinIOStream
	/// Does not take the ownership of stream
	explicit mwStdIOStreamAdapter(misc::mwBinIOStream& stream);
	~mwStdIOStreamAdapter();

	std::iostream& get();

private:
	MW_WARNING_SUPPRESS_DLLINTERFACE
	std::unique_ptr<mwStdIOStreamAdapterImpl> m_pImpl;
};

}  // namespace misc

#endif // MW_USE_VS2008_COMPATIBILITY

#endif  // MW_MWSTDIOSTREAMADAPTER_HPP_