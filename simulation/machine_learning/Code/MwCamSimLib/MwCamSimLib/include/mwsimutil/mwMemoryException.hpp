// (C) 2003-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYEXCEPTION_HPP_
#define MW_MWMEMORYEXCEPTION_HPP_

#include "mwBasicTypes.hpp"
#include "mwException.hpp"

namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//!This class represents a memory exception
class MW_5AXUTIL_API mwMemoryException : public mwException
{
public:
	//!Types of memory exceptions
	/*!Currently two types are available:
		- memory allocation error
		- memory deallocation error
	*/	
	enum memExceptionType
	{
		//!Error during memory allocation
		MEMORY_ALLOCATION,
		//!Error during memory deallocation
		MEMORY_DEALLOCATION
	};

	//!Memory allocation exception
	/*!Constructs a new memory exception
		\param dataLen length of the memory block, that couldn't be allocated
		\remark The exception type is automatically set to MEMORY_ALLOCATION
	*/
	explicit mwMemoryException( const uint64_t dataLen );

	//!Memory deallocation exception
	/*!Constructs a new memory exception
		\param dataAddress address of the data block that couldn't be freed
		\remark The exception type is set to MEMORY_DEALLOCATION
	*/
	explicit mwMemoryException( const void *dataAddress );

	//!Get exception type
	/*!
		\returns exception type (ALLOCATION, DEALLOCATION)
	*/
	const memExceptionType &GetExceptionType() const;

	//!Get address of the block
	/*!
		\returns address of the memory block that couldn't be freed.
		\remark This information is only valid if memExceptionType is MEMORY_DEALLOCATION.
		If exception type is memory allocation 0x00000000 is returned.
	*/
	const void *GetMemoryAddress() const;

	//!Get number of bytes
	/*!
		\returns amount of memory requested on the failure.
		\remark This information is only valid if exception type is MEMORY_ALLOCATION.
		If exception type is MEMORY_DEALLOCATION 0 is returned.
	*/
	const uint64_t &GetMemoryAmount() const;

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;

protected:
private:
	mwMemoryException& operator = (mwMemoryException&);
	memExceptionType			mExType;
	const void					*mDataAddress;
	const uint64_t		mDataLength;

};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
};
#endif	//	MW_MWMEMORYEXCEPTION_HPP_
