// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBINIOSTREAM_HPP_
#define MW_MWBINIOSTREAM_HPP_
#include "mwBinInputStream.hpp"
#include "mwBinOutputStream.hpp"

namespace misc
{
	//!This class represents an interface to an IO stream
	class MW_5AXUTIL_API mwBinIOStream : public mwBinInputStream, public mwBinOutputStream
	{
	public:
		virtual ~mwBinIOStream(){};

	protected:
	private:
	};
}
#endif	//	MW_MWBINIOSTREAM_HPP_
