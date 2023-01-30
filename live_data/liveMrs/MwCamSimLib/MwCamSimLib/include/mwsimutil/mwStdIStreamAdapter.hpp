// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTDISTREAMADAPTER_HPP_
#define MW_MWSTDISTREAMADAPTER_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY

#include "mwBinInputStream.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwWarningPragmas.hpp"

#include <iostream>
#include <memory>

namespace misc
{
class mwStdIStreamAdapterImpl;

/// Adapter to convert a mwBinInputStream into a std::istream
///
/// Sample usage:
/// void Load(std::istream& s);
/// void Load(mwBinInputStream& s)
/// {
///    Load(misc::mwStdIStreamAdapter(s).get());
/// }
class MW_5AXUTIL_API mwStdIStreamAdapter
{
public:
	/// Constructs the adapter class and attaches it to the given mwBinInputStream
	/// Does not take the ownership of stream
	explicit mwStdIStreamAdapter(misc::mwBinInputStream& stream);
	~mwStdIStreamAdapter();

	std::istream& get();

private:
	MW_WARNING_SUPPRESS_DLLINTERFACE
	std::unique_ptr<mwStdIStreamAdapterImpl> m_pImpl;
};

}  // namespace misc

#endif  // !MW_USE_VS2008_COMPATIBILITY

#endif  // MW_MWSTDISTREAMADAPTER_HPP_