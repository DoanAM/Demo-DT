// (C) 2003-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILENAME_HPP_
#define MW_MWFILENAME_HPP_
#include "mwStringConversions.hpp"
#include "mwDllImpExpDef.hpp"


namespace misc
{

//!This class represents a file name
/*!Class for operations on the file name in a 
hierarchical file system
*/
class MW_5AXUTIL_API mwFileName
{
public:

	//!Default constructor
	mwFileName();

	//!Construct a file name object from a string
	explicit mwFileName(const misc::mwstring &name, bool _case = false);

	//!Construct a file name from dir, title, ext
	/*!Construct a file name object from directory,
	file name and file extension
	\param dir Directory
	\param title File name without extension
	\param ext Extension
	\param _case define if normalize string(s) or not, true to normalize... this will not work on Japanese code pages
	*/
	mwFileName(
		const misc::mwstring &dir, 
		const misc::mwstring &title, 
		const misc::mwstring &ext,
		bool _case = false);


	//!Copy constructor
	mwFileName( const mwFileName &other );

	//!Set directory of the file
	/*!
	\param dir Directory to set
	*/
	void SetFileDirectory( const misc::mwstring &dir );

	//!Append directory 
	/*!Add a part to the directory
	\param dir Part to append
	*/
	void AppendFileDirectory( const misc::mwstring &dir );

	//!Prepend directory
	/*!Add current string at the begin of the directory string
	\param dir Part to prepend
	*/
	void PrependFileDirectory( const misc::mwstring &dir );

	//!Get directory
	/*!
	\returns Directory of the file
	*/
	const misc::mwstring &GetFileDirectory() const;

	//!Skip root
	/*!Delete a part of the directory
	\param root Part of the dir name to skip
	\returns false if given root is not a root
	of this file name
	*/
	bool SkipRoot( const misc::mwstring &root );

	//!Set file name ( without extension )
	/*!
	\param name Name to set
	*/
	void SetFileCoreName( const misc::mwstring &name );

	//!Set file name ( name + extension )
	/*!
	\param name Name +ext to set
	*/
	void SetFileName( const misc::mwstring &name );

	//!Append name
	/*!
	\param name Name part to append
	*/
	void AppendFileCoreName( const misc::mwstring &name );

	//!Prepend name
	/*!
	\param name Name part to prepend
	*/
	void PrependFileCoreName( const misc::mwstring &name );

	//!Get file title ( without extension )
	/*!
	\returns File title
	*/
	const misc::mwstring &GetFileCoreName() const;

	//!Set file extension
	/*!
	\param ext Extension to set
	*/
	void SetFileExtention( const misc::mwstring &ext );

	//!Append file extension
	/*!
	\param ext Extension part to append
	*/
	void AppendFileExtention( const misc::mwstring &ext );

	//!Prepend file extension
	/*!
	\param ext extension part to prepend
	*/
	void PrependFileExtention( const misc::mwstring &ext );

	//!Get file extension
	/*!
	\returns File extension
	*/
	const misc::mwstring &GetFileExtention() const;

	//!Get file name ( title + . + extension )
	misc::mwstring GetFileName() const;

	//!Get complete file path ( dir+ title + . + extension )
	misc::mwstring GetFilePath() const;

	//!Convert to a string
	operator misc::mwstring() const;

	//!Equality operator
	bool operator==( const mwFileName &other ) const;

	//!Inequality operator
	bool operator!=( const mwFileName &other ) const;

	//!Assignment operator
	mwFileName &operator=( const mwFileName &other );

	//!Assignment operator
	mwFileName &operator=( const misc::mwstring &fileName );

	void SetNormalize(bool _case);

	bool GetNormalize() const;

	bool IsRelativePath() const;

private:
	misc::mwstring		m_sDirectory;
	misc::mwstring		m_sTitle;
	misc::mwstring		m_sExtention;

	bool m_case;

	//! Parse function
	/*!
	\param fileName of type const misc::mwstring &
	\returns Parse of type void
	*/
	void Parse( const misc::mwstring &fileName );
};
}
#endif	//	MW_MWFILENAME_HPP_
