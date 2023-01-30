// (C) 2006-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPRESETIOSTREAM_HPP_
#define MW_MWPRESETIOSTREAM_HPP_
#include "mwBinIOStream.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
	class MW_5AXUTIL_API  mwPresetIOStream : public mwBinIOStream
	{
	public:

		//!Rewind
		/*!Sets the position of the internal pointer to the specified position.
			\param pos offset to set the pointer
			\throws mwIdxRangeException if specified position is out of range
		*/
		virtual void Rewind( const uint64_t &pos = 0 ) = 0;


	protected:
	private:
	};
}
#endif	//	MW_MWPRESETIOSTREAM_HPP_
