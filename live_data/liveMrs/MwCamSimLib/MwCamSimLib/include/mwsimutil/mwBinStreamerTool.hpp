// (C) 2010-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWBINSTREAMERTOOL_HPP_
#define MW_MWBINSTREAMERTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwBILostData.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace misc
{
class mwBinInputStream;
class mwBinOutputStream;
class mwException;
}  // namespace misc

namespace cadcam
{
class mwTool;
}

const unsigned long MW5TL_BINARY_MARKER = 0x4C543557;

namespace cadcam
{
class MW_5AXUTIL_API mwBinStreamerTool
{
public:
	/// Loads a mwTool object using an input stream
	///
	///	@param rInputStream the stream from where to read the data
	///	@param retTl the place where to put the read data (reference to an auto pointer to a tool
	///object)
	///	@returns information about lost data during older tools conversion
	///	@throws mwException if any read value is invalid
	static const std::vector<misc::mwBILostData> LoadTool(
		misc::mwBinInputStream& rInputStream, misc::mwAutoPointer<cadcam::mwTool>& retTl);


	/// Saves a mwTool object using an output stream
	///
	///	@param rOutputStream the stream where to write the data
	///	@param rToSave the date to be written (tool object)
	///	@throws mwException if it's not able to write data though the provided stream

	static void SaveTool(misc::mwBinOutputStream& rOutputStream, const cadcam::mwTool& rToSave);

private:
	/// Constructor not allowed since it's a static class
	mwBinStreamerTool();
};
}  // namespace cadcam
#endif  //	MW_MWBINSTREAMERTOOL_HPP_
