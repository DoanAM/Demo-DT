// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBININPUTSTREAM_HPP_
#define MW_MWBININPUTSTREAM_HPP_
#include "mwDllImpExpDef.hpp"
#include <istream>
#include "mwBinStream.hpp"

namespace misc
{
	//!The mwBinInputStream class
	/*!
		This class provides generic interface to the binary input stream
	*/
	class MW_5AXUTIL_API mwBinInputStream : virtual public mwBinStream
	{
	public:
		typedef	misc::uint64_t						mwsize_t;

		//!This function reads from the input stream 
		/*!
			\param data buffer to write the data to 
			\param dataLen this parameter has two meanings. First it is the maximum length of the buffer into which we read.
			Second, after reading, it stores the amount of data actually read.
		*/
		virtual void Read( void *data, mwsize_t &dataLen )= 0; 
		virtual void read( void *data, std::streamsize &dataLen )
		{
			mwsize_t mwDataLen=(mwsize_t)dataLen;
			Read(data,mwDataLen);
			dataLen=(std::streamsize)mwDataLen;
		}; 
		template<typename T>
		inline mwBinInputStream& operator >>(T& val)
		{
			mwsize_t size=sizeof(T);
			Read(reinterpret_cast<void *>(&val),size);
			return (*this);
		}

		virtual ~mwBinInputStream(){};

	protected:
	private:
	};
}
#endif	//	MW_MWBININPUTSTREAM_HPP_
