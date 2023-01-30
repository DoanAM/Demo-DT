// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILESTREAM_HPP_
#define MW_MWFILESTREAM_HPP_

#include "mwAutoPointer.hpp"
#include "mwStream.hpp"
#include "mwFileStreamImpl.hpp"

	//! define unicode/asci output file stream
	/*! There are wide versions of the usual stream classes
		and it is easy to define t-style macros to manage them:

		@code{.cpp}
		#ifdef _UNICODE
			#define tofstream wofstream
			#define tstringstream wstringstream
			// etc...
		#else
			#define tofstream ofstream
			#define tstringstream stringstream
			// etc...
		#endif // _UNICODE
		@endcode

		And you would use them like this:

		@code{.cpp}
		tofstream testFile( "test.txt" ) ;
		testFile << _T("ABC") ;
		@endcode

		Now, you would expect the above code to produce a 3-byte file when compiled using
		single-byte characters and a 6-byte file when using double-byte. Except you don't.
		You get a 3-byte file for both. WTH is going on?!

		It turns out that the C++ standard dictates that wide-streams are required to convert
		double-byte characters to single-byte when writing to a file.
		So in the example above, the wide string L"ABC" (which is 6 bytes long) gets converted
		to a narrow string (3 bytes) before it is written to the file.
		And if that wasn't bad enough, how this conversion is done is implementation-dependent.

		The solution: write a new codecvt-derived class that converts wchar_ts to wchar_ts
		(i.e. do nothing) and attach it to the wofstream object.
		When the wofstream tried to convert the data it was writing out, it would invoke my new
		codecvt object that did nothing and the data would be written out unchanged.

		The only thing left to do is instantiate one of these and connect it to the wofstream object.
		Using MSVC, you are supposed to use the (non-standard) _ADDFAC() macro to imbue objects with
		a locale, but it didn't want to work with my new NullCodecvt class so I ripped out the guts
		of the macro and wrote a function that did this.

		All of this are done on the constructor of the stream class so in order to use this class all you have to do is:

		@code{.cpp}
		misc::mwOFStream testFile( _T("test.txt") , std::ios::out | std::ios::binary );
		testFile << _T("ABC") ;
		@endcode
	*/
namespace misc
{
	//!This class represents an output file stream
#pragma warning(push)
#pragma warning(disable : 4251) // because basic_ofstream_ex is not dll exported
	class MW_5AXUTIL_API mwOFStream : public basic_ofstream_ex<wchar_t >
	{
#pragma warning(pop)
	public:
		//! available encodes
		enum mw_encoding
		{
			ASCII_ENC,
			UNICODE_ENC
		};
		
		//! Constructor
		/*! same as std::ofstream/std::wofstream constructor
			see STL documentation for details
		*/
		mwOFStream();
		
		//! Constructor
		/*! same as std::ofstream/std::wofstream constructor
			see STL documentation for details
			\param s file to be opend
			\param mode specifyes the mode in wich to be open(read,write etc)
			\param encoding ascii or unicode
		*/
		mwOFStream( const mwstring &s,std::ios_base::openmode mode = std::ios_base::out | std::ios_base::trunc, const mw_encoding encoding =UNICODE_ENC);
		
		//! opens a specified file
		/*! same as std::ofstream/std::wofstream open function
			see STL documentation for details
			\param s file to be opend
			\param mode specifyes the mode in wich to be open(read,write etc)
			\param encoding ascii or unicode
		*/
		void open(const mwstring &s, std::ios_base::openmode mode = std::ios_base::out | std::ios_base::trunc, const mw_encoding encoding =UNICODE_ENC );

		


		

		//! confirms if is open or not
		bool operator!()
		{return !is_open();}
	private:
		
		//! attaches to the stream the specified codec
		/*!
			\param codecIndex the codec to be attached
		*/
		void AttachCodec (const size_t& codecIndex);
		//! writes in the stream a code specifying the codec used
		/*!
			\param rStream the stream where to write
			\param rCodec the codec having the header to be write
		*/
		void WriteCodingHeader(std::basic_ostream<wchar_t,std::char_traits<wchar_t> >& rStream,
							   const mwCodecvt& rCodec);
		//! opens a specified file
		/*! same as std::ofstream/std::wofstream open function
			see STL documentation for details
			\param s file to be open
			\param mode specifies the mode in wich to be open(read,write etc)
		*/
		void Open(const mwstring &s, std::ios_base::openmode mode);


	};


	//!This class represents an input stream
#pragma warning(push)
#pragma warning(disable : 4251) // because basic_ifstream_ex is not dll exported
	class MW_5AXUTIL_API mwIFStream : public basic_ifstream_ex<wchar_t, std::char_traits<wchar_t> >
	{
#pragma warning(pop)
	public:
		
		//! Constructor
		/*! same as std::ofstream/std::wofstream constructor
			see STL documentation for details
		*/

		mwIFStream();


		
		//! Constructor
		/*! same as std::ofstream/std::wofstream constructor see STL documentation for details
		\param s file to be opend
		\param mode specifyes the mode in wich to be open(read,write etc)
		*/
		mwIFStream( const mwstring &s,std::ios_base::openmode mode = std::ios_base::in);
		
		//! opens a specified file
		/*! same as std::ofstream/std::wofstream open function
			see STL documentation for details
			\param s file to be opend
			\param mode specifyes the mode in wich to be open(read,write etc)
		*/
		void open(const mwstring &s, std::ios_base::openmode mode = std::ios_base::in);
		//! confirms if it's open or not
		inline const bool operator!()
		{return !is_open();}
		
	private:
		
		//! attaches to the stream the specified codec
		/*!
			\param codecIndex the codec to be attached
		*/
		void AttachCodec (const size_t& codecIndex);
		//! reads from the stream the codec header
		/*!
			\param rStream the stream from where to read
			\param rCodec the codec having the header to be read
		*/
		void RemoveCodingHeader(std::basic_istream<wchar_t,std::char_traits<wchar_t> >& rStream,const mwCodecvt& rCodec);
		//! opens a specified file
		/*! same as std::ofstream/std::wofstream open function
			see STL documentation for details
			\param s file to be open
			\param mode specifies the mode in wich to be open(read,write etc)
		*/
		void Open(const mwstring &s, std::ios_base::openmode mode);
		//! reads from the stream the codec header and detecs based on  it the codec
		/*!
			\param rStream the stream from where to read
			\return the index of the detected codec
		*/
		const size_t GetAppropiateCodecIndex(
			std::basic_istream<char, std::char_traits<char> >& rStream);
	};


	class MW_5AXUTIL_API mwBaseFStream
	{
	public:
		//! allows attaching a codec to a basic file stream
		static void AttachCodec (const size_t& codecIndex,
			w_basic_filebuf<wchar_t, std::char_traits<wchar_t> > &rdbuf );
	private:
		//! Constructor not allowed since it's a static class
		mwBaseFStream();
	};

	typedef std::fstream mwAFStream;
}

#endif	//	MW_MWFILESTREAM_HPP_
