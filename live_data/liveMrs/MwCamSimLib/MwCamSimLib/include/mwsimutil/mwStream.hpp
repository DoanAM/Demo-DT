// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTREAM_HPP_
#define MW_MWSTREAM_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwStringConversions.hpp"
#include <iostream>
#include <ostream>
#include <istream>

	

namespace misc
{
	
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

	The solution: write a new codecvt-derivemd class that converts wchar_ts to wchar_ts 
	(i.e. do nothing) and attach it to the wofstream object.
	When the wofstream tried to convert the data it was writing out, it would invoke my new 
	codecvt object that did nothing and the data would be written out unchanged.

	The only thing left to do is instantiate one of these and connect it to the wofstream object.
	Using MSVC, you are supposed to use the (non-standard) _ADDFAC() macro to imbue objects with 
	a locale, but it didn't want to work with my new NullCodecvt class so I ripped out the guts 
	of the macro and wrote a function that did this.

	All of this are done on the constructor of the stream class so in order to use this class all you have to do is:

	@code{.cpp}
	misc::mwOStream testFile( _T("test.txt") , std::ios::out | std::ios::binary ); 
	testFile << _T("ABC") ;
	@endcode{.cpp}
	*/
	typedef std::wostream mwOStream;

	typedef std::wistream mwIStream;
	typedef std::iostream mwAStream;

	static mwOStream& mwCout = std::wcout;
}
#endif	//	MW_MWSTREAM_HPP_
