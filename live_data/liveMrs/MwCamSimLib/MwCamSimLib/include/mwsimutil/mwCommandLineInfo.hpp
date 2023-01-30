// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOMMANDLINEINFO_HPP_
#define MW_MWCOMMANDLINEINFO_HPP_
#include "mwStringConversions.hpp"
#include <list>
#include <map>
#include <exception>
#include "mwDllImpExpDef.hpp"

namespace misc
{
	//!This class represents a set of operations for command line
	/*!This class provides an easy to use interface to parse command line 
		options and create command lines
	*/
	class MW_5AXUTIL_API mwCommandLineInfo
	{
	public:

		/*! \var typedef std::list<misc::mwstring>      argList
		    \brief A type redefinition for
			    std::list<misc::mwstring>     				as argList
		*/
		typedef std::list<misc::mwstring>		argList;

		/*! \var typedef std::list<misc::mwstring>      optList
		    \brief A type redefinition for
			    std::list<misc::mwstring>     				as optList
		*/
		typedef std::list<misc::mwstring>		optList;

		/*! \var typedef std::map<misc::mwstring, misc::mwstring> optMap
		    \brief A type redefinition for
			    std::map<misc::mwstring, misc::mwstring>				as optMap
		*/
		typedef std::map<misc::mwstring, misc::mwstring> optMap;

		/*! \var typedef argList::const_iterator     constArgIterator
		    \brief A type redefinition for
			    argList::const_iterator    				as constArgIterator
		*/
		typedef argList::const_iterator		constArgIterator;

		/*! \var typedef optList::const_iterator     constOptIterator
		    \brief A type redefinition for
			    optList::const_iterator    				as constOptIterator
		*/
		typedef optList::const_iterator		constOptIterator;

	public:


		//!Default constructor
		mwCommandLineInfo();

		//!Construct a command line info from a string
		/*!Construct a command line info from a string like 
			used in functions WinExec etc.
			\param cmdLine command line to parse
		*/
		explicit mwCommandLineInfo( const misc::mwstring &cmdLine );

		//!Construct a command line info from C-Style arguments
		/*!Construct a command line info object from argc and argv
			\param argc number of arguments
			\param argv array of null terminated strings representing the 
			arguments
		*/
		mwCommandLineInfo( const int argc, char *argv[] );
		mwCommandLineInfo( const int argc, wchar_t *argv[] );

		//!Copy constructor
		/*!
			\param cliIn command line info to create a copy of
		 */
		mwCommandLineInfo( const mwCommandLineInfo &cliIn );

		//!Destructor
		~mwCommandLineInfo();

	public:


		//!Get number of arguments
		/*!Returns count of arguments (and options)
			\param all <b>true</b> to return count of arguments and options
					   <b>false</b> to return only count of arguments
			\returns Count of arguments (and options)
		 */
		const size_t GetArgumentCount( bool all = false ) const;

		//!Get first argument
		constArgIterator GetArgBegin() const;

		//!Get the end of the argument list
		constArgIterator GetArgEnd() const;

		//!Get first option in the list
		constOptIterator GetOptionBegin() const;

		//!Get the end of the options list
		constOptIterator GetOptionEnd() const;

		//!Is option present in the command line?
		/*!Is option present in the command line?
			\param option name of the option to check
			\returns <b>true</b> if option is present
					 <b>false</b> else
		 */
		bool IsOptionPresent( const misc::mwstring &option ) const;

		//!Returns a value of an option if present
		/*!
			\param option name of the option to return a value for
			\returns value of the requested option
		 */
		const misc::mwstring &GetOptionValue( const misc::mwstring &option ) const
			;
		
		//!Set executable path
		/*!Set the path of executable file. Can be absolute or relative
			\param exePath path of the executable to set
		 */
		void SetExecutablePath( const misc::mwstring &exePath );

		//!Add argument to the command line
		/*!Add argument to the argument list
			\param argument argument to add to the command line
		 */
		void AddArgument( const misc::mwstring &argument );

		//!Add option with a value
		/*! Add option with a value
			\param option option to add to the command line
			\param value value of the given option
		 */
		void AddOption( const misc::mwstring &option, const misc::mwstring &value );

	public:


		//!Convert to a string
		operator misc::mwstring ();
		
		//!Assignment operator
		/*!
			\param info command line info to create a copy of
		 */
		const mwCommandLineInfo &operator=( const mwCommandLineInfo &info );

	protected:
	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	
		argList		m_lstArguments;
		optList		m_lstOptions;

		optMap		m_mapOptValues;


		//! ParseArgument function
		/*!
			\param argument of type const misc::mwstring &
			\returns ParseArgument of type void
		*/
		void ParseArgument( const misc::mwstring &argument );
	
	#pragma warning(pop)
	};
};
#endif	//	MW_MWCOMMANDLINEINFO_HPP_
