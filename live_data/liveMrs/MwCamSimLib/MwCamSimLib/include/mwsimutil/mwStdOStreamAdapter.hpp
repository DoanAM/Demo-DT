// (C) 2022-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTDOSTREAMADAPTER_HPP_
#define MW_MWSTDOSTREAMADAPTER_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY


#include "mwBinOutputStream.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwWarningPragmas.hpp"

#include <iostream>
#include <memory>

namespace misc
{
class mwStdOStreamAdapterImpl;

/// Adapter to convert a mwBinOutputStream into a std::ostream
///
/// Sample usage:
/// void Save(std::ostream& s);
/// void Save(mwBinOutputStream& s)
/// {
///    Save(misc::mwStdOStreamAdapter(s).get());
/// }
class MW_5AXUTIL_API mwStdOStreamAdapter
{
public:

	/// Constructs the adapter class and attaches it to the given mwBinOutputStream
	/// Does not take the ownership of stream
	explicit mwStdOStreamAdapter(misc::mwBinOutputStream& stream);
	~mwStdOStreamAdapter();

	std::ostream& get();

private:
	MW_WARNING_SUPPRESS_DLLINTERFACE
	std::unique_ptr<mwStdOStreamAdapterImpl> m_pImpl;
};

}  // namespace misc

#endif // MW_USE_VS2008_COMPATIBILITY

#endif  // MW_MWSTDOSTREAMADAPTER_HPP_