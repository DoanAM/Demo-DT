// (C) 2017-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBINSTREAM_HPP_
#define MW_MWBINSTREAM_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwBasicTypes.hpp"

//! base class for any mwBinStream
class MW_5AXUTIL_API mwBinStream
{
public:
	//! Get data. If not overwritten will return 0.
	//! Implementers can override this, if possible, for performance benefits in some cases.
	//! Callers must implement a fallback for the case that this is not overridden and returns 0.
	/*!
	\returns pointer to the buffer with data
	*/
	virtual const void *GetBuffer() const 
	{
		return 0;
	}
	//! Get data size. If not overwritten will return 0.
	//! Implementers can override this, if possible, for performance benefits in some cases.
	//! Callers must implement a fallback for the case that this is not overridden and returns 0.
	/*!
		\returns current length of the data
	*/
	virtual const misc::uint64_t GetDataLength() const
	{
		return 0;
	}

	virtual ~mwBinStream(){};
protected:
	mwBinStream(){};//interface class, instantiation not allowed
};
#endif	//	MW_MWBINSTREAM_HPP_
