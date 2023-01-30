// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILEFINDER_HPP_
#define MW_MWFILEFINDER_HPP_
#include "mwStringConversions.hpp"
#include <list>
#include <map>
#include "mwDllImpExpDef.hpp"

namespace misc
{

	//!This class provides functionality for recursive search
	/*!Files with names that match the pattern will be 
		collected in a list
	*/
	class MW_5AXUTIL_API mwFileFinder
	{
	public:
		enum FILES_ORDER
		{
			MW_ORDERED_BY_NAME=1,
			MW_ORDERED_BY_SIZE,
			MW_ORDERED_BY_CREATION_DATE
		};
		/*
		 * Defines
		 */
		typedef std::list< misc::mwstring >		filelist;
		typedef filelist::const_iterator		const_iterator;

		//!Default constructor
		mwFileFinder();
		
		//!Construct a file finder object with a root directory and pattern
		/*!File finder with a root directory and pattern
			\param rootDir Initial directory for the filesearch
			\param pattern Shell pattern for the files
		 */
		mwFileFinder( const misc::mwstring &rootDir, const misc::mwstring &pattern );
		mwFileFinder( const misc::mwstring &rootDir );
		
		//!Destructor
		virtual ~mwFileFinder();

		//!Set root directory
		/*!
			\param rootDirectory Initial directory
		 */
		void SetRootDirectory( const misc::mwstring &rootDirectory );

		//!Set pattern
		/*!
			\param shellPattern Shell pattern for the files
		 */
		void AddShellPattern( const misc::mwstring &shellPattern );
		
		//!Start a query
		/*!If results of the last query aren't reset
			via Reset() the results of the new query are
			appended to the file fist
			\param recursive true for recursive search
			\returns true if query contains any results
		 */
		bool QueryFile( bool recursive = true , FILES_ORDER sortBy = MW_ORDERED_BY_NAME);
		bool QueryFile( misc::mwstring fileName);

		//!Start a query
		/*!If results of the last query aren't reset
			via Reset() the results of the new query are
			appended to the file fist
			\param recursive true for recursive search
			\returns true if query contains any results
		 */
		bool QueryDirectory( bool recursive = false );

		//!Reset
		/*!Deletes the results of the last query
			Root directory and patterns are still valid
		 */
		void Reset();

		//!Get root directory
		const misc::mwstring &GetRootDirectory() const;

		//!Get results
		/*!
			\returns a list with file names
		*/
		const filelist &GetFileList() const;

		void CheckDuplicates() const;

		const_iterator GetFileListBegin() const
		{
			return m_lResults.begin();
		}

		const_iterator GetFileListEnd() const
		{
			return m_lResults.end();
		}

		//!Get results 
		/*!
			\returns a list with directory names
		*/
		const filelist &GetDirList() const;

		//!Get begin of the directories list
		const_iterator GetDirListBegin() const;

		//!Get end of the directories list
		const_iterator GetDirListEnd() const;

		virtual bool MatchPattern( const misc::mwstring &fileName );

	private:
#pragma warning(push)
#pragma warning(disable : 4251)

		misc::mwstring		m_sRootDir;
		filelist		m_lPattern;
		filelist		m_lResults;
		filelist		m_lDirs;
		std::map<misc::mwstring, unsigned long long> m_sizeCache;

		bool Match( const misc::mwstring &data, const misc::mwstring &pattern );

		enum fileType
		{
			MW_FT_DIRECTORY,
			MW_FT_REGULAR,
			MW_FT_IGNORED
		};

		fileType AddFile( const misc::mwstring &fileName, unsigned long fileAttribs );
		void FindDirectoriesRecursive( const misc::mwstring &dirName );
		
		//! confirm if left file creation date is strictly less as right file creation date
		/*! 
			\param leftFileName the leftFileName
			\param rightFileName the rightFileName
			\returns true if leftFileName creation date < rightFileName creation date as size on hdd
		*/
		static const bool LessAsCreationDate(
			const misc::mwstring& leftFileName,
			const misc::mwstring& rightFileName
			);
		
		void SortFiles(
			FILES_ORDER sortBy
		);
		void MergeFiles(filelist& src, FILES_ORDER sortBy );
#pragma warning(pop)
	};
};
#endif	//	MW_MWFILEFINDER_HPP_
