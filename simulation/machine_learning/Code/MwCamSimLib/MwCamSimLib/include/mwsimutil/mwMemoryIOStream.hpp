// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYIOSTREAM_HPP_
#define MW_MWMEMORYIOSTREAM_HPP_
#include "mwPresetIOStream.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwBasicTypes.hpp"

namespace misc
{
/**
This class implements the \ref mwPresetIOStream interface using a in memory buffer.
By default, it uses a resizable internal buffer where the user can read and write from.
Furthermore, it allows to attach to a fixed-sized external buffer. 
In this case, reading and writing is limited to buffer size of the external buffer.
*/
class MW_5AXUTIL_API mwMemoryIOStream : public mwPresetIOStream
{
public:
	typedef ::misc::uint64_t uint64_t;

	//! Create a memory stream
	/*!The default amount of memory allocated = initialCapacity.
		\param initialCapacity amount of memory to be initially allocated
		\note increaseStep will also be set to \p initialCapacity
	*/
	mwMemoryIOStream(const uint64_t& initialCapacity);

	//! Creates a memory stream that attaches to an external buffer
	/*!
	\param data Pointer to the external buffer
	\param dataLen Length of the provided buffer
	\see \ref mwMemoryIOStream::Attach
	*/
	mwMemoryIOStream(const void* data, const uint64_t& dataLen);

	mwMemoryIOStream();
	//! Destructor
	virtual ~mwMemoryIOStream();
	//! copy constructor
	/**
	The copy operator copies all data from the stream to copy from to a new internal buffer.
	This also happens if a stream attached to an external buffer is provided.
	Furthermore, the new stream will be rewound such that \ref GetDataPosition() returns 0.
	\param rhs The memory stream to copy from
	*/
	mwMemoryIOStream(const mwMemoryIOStream& rhs);

	//! =  operator
	/**
	The assignment operator copies all data from the stream to copy from to a new internal buffer.
	This also happens of a stream attached to an external buffer is provided.
	Furthermore, the operator rewinds the stream such that \ref GetDataPosition() returns 0
	afterwards. \param rhs The memory stream to copy from \note if &rhs == this the assignment
	operator does nothing
	*/
	mwMemoryIOStream& operator=(const mwMemoryIOStream& rhs);

	//! Set increaseStep.
	/*!Sets increase step. Doesn't reallocate the buffer.
		\param newIncreaseStep new value of increase step
	*/
	void SetIncreaseStep(const uint64_t& newIncreaseStep);

	//! Get data
	/*!
		\returns pointer to the buffer with data
	*/
	virtual const void* GetBuffer() const;

	//! Get data size
	/*!
		\returns length of the data
	*/
	virtual const uint64_t GetDataLength() const;

	//! Read data from the stream
	/*!Reads data from the internal buffer number of bytes actually read is stored in dataLen.
		The internal pointer is moved forward by the number of bytes read.
		\param data buffer to store the read data
		\param dataLen size of the buffer
	*/
	virtual void Read(void* data, uint64_t& dataLen);

	//! Writes data to the stream
	/*!Writes data to the internal buffer. Reallocates the internal buffer automatically if needed.
		\param data buffer with data
		\param dataLen length of the buffer
		\throws mwMemoryException if memory reallocation fails
	*/
	virtual void Write(const void* data, const uint64_t& dataLen);

	//! Rewind
	/*!Sets the stream's offset to/from where to write/read
		\param newOffset offset from the beginning of the stream in number of bytes
		\throws mwIdxRangeException if the specified offset is outside the limits of the stream
	*/
	virtual void Rewind(const uint64_t& newOffset = 0);

	//! Get data position
	/*!
		\returns Gets the position of the internal pointer relative to the data
	*/
	virtual const uint64_t GetDataPosition() const;

	//! Attaches the memory to an external buffer
	/*!
	\param data Pointer to the external buffer
	\param dataLen Length of the provided buffer
	\note Given an external fixed-sized buffer reading and writing operations are limited to
		boundaries of the fixed sized buffer
	*/
	void Attach(const void* data, const uint64_t& dataLen);

	/**
	\brief Detaches from an external buffer
	After detaching, the class automatically switches to an internal buffer on the next write
	operation \note This function does nothing when an internal buffer is used
	*/
	void Detach();

	
	//! Clears memory stream content
	/*!Deallocate all allocated memory for the stream and reset all member variables.
	*/
	void Clear();
	

protected:
private:
#pragma warning(push)
#pragma warning(disable : 4251)

	void Copy(const mwMemoryIOStream& toCopy);
	void Resize(const uint64_t newSize);

	uint64_t m_increaseStep;
	uint64_t m_dataSize;	// amount of memory that is actually used
	uint64_t m_capacity;	// the buffer' size
	char* m_dataPtr;	// pointer to all the data in the stream
	uint64_t m_offset;	// offset to/from where to write/read
	bool m_isAttached;	// true if the m_dataPtr points to an external buffer

	size_t m_resizesCount;	// number of times Resize has been called
	static const size_t NR_OF_RESIZES_BEFORE_REALLOCATION_STRATEGY_CHANGES = 20;
	static const size_t DEFAULT_INCREASE_STEP = 2048;
#pragma warning(pop)
};

}	// namespace misc
#endif	//	MW_MWMEMORYIOSTREAM_HPP_
