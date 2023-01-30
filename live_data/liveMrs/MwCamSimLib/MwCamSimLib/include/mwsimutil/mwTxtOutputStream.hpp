// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTXTOUTPUTSTREAM_HPP_
#define MW_MWTXTOUTPUTSTREAM_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"


namespace misc
{
	class mwWarningMessage;
	//!This class provides a generic interface to a text output stream
	class MW_5AXUTIL_API mwTxtOutputStream
	{
	public:

		//!This function writes a text to the output stream
		/*!
			\param txt text to be written
		*/
		virtual void Write( const misc::mwstring& txt ) = 0;

		virtual void Write( const mwWarningMessage& msg ) = 0;

		virtual ~mwTxtOutputStream(){};

	protected:
	private:
	};
}
#endif	//	MW_MWTXTOUTPUTSTREAM_HPP_
