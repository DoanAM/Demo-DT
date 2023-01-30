// (C) 2010-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWBINSTREAMERTOOLPATH_HPP_
#define MW_MWBINSTREAMERTOOLPATH_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY
#include "mwBILostData.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
class mwBinInputStream;
class mwBinOutputStream;
class mwException;
}  // namespace misc

namespace cadcam
{
class mwToolPath;
}

const unsigned int MW5TP_BINARY_MARKER = 0x5461532D;

namespace cadcam
{
class MW_5AXUTIL_API mwBinStreamerToolPath
{
public:
	/// Loads a mwToolPath object using an input stream
	///
	///	@param rInputStream the stream from where to read the data
	///	@param retTp the place where to put the read data (toolpath object)
	///	@param ignoreBinFileVersion special flag for mwPatch.exe application
	///	@throws mwException if any read value is invalid
	static void LoadToolPath(
		misc::mwBinInputStream& rInputStream,
		cadcam::mwToolPath& retTp,
		const bool ignoreBinFileVersion = false);


	/// Saves a mwToolPath object using an output stream
	///
	///	@param rOutputStream the stream where to write the data
	///	@param rToSave the date to be written
	///	@throws mwException if it's not able to write data though the provided stream
	static void SaveToolPath(
		misc::mwBinOutputStream& rOutputStream, const cadcam::mwToolPath& rToSave);

private:
	/// Constructor not allowed since it's a static class
	mwBinStreamerToolPath();
};
}  // namespace cadcam
#endif  //	MW_MWBINSTREAMERTOOLPATH_HPP_
#endif  // MW_USE_VS2008_COMPATIBILITY
