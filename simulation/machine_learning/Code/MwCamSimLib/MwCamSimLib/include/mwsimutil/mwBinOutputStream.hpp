// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBINOUTPUTSTREAM_HPP_
#define MW_MWBINOUTPUTSTREAM_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwBasicTypes.hpp"
#include "mwBinStream.hpp"

namespace misc
{
	//!This class provides a generic interface to a binary output stream
	class MW_5AXUTIL_API mwBinOutputStream : virtual public mwBinStream
	{
	public:

		typedef	::misc::uint64_t mwsize_t;

		//!This function writes to the output stream
		/*!
			\param data pointer to the buffer with data
			\param dataLen size of the buffer/number of bytes to write
		*/
		virtual void Write( const void *data, const mwsize_t &dataLen ) = 0;

		virtual ~mwBinOutputStream(){};
		template<typename T>
		inline mwBinOutputStream& operator <<(const T& val)
		{
			static const mwsize_t size=sizeof(T);
			Write(&val,size);
			return (*this);
		}

		//! Write the stream content to the targeted storage.
		/*! This is to make sure no data is lost, if the application crashes later on.
		Or to actually see the written data in another application, for example a log file. */
		inline virtual void Flush() {};

	protected:
	private:
	};
}
#endif	//	MW_MWBINOUTPUTSTREAM_HPP_
