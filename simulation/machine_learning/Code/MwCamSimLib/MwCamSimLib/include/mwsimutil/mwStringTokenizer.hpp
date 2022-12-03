// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTRINGTOKENIZER_HPP_
#define MW_MWSTRINGTOKENIZER_HPP_
#include "mwStringConversions.hpp"
#include <vector>
#include "mwDllImpExpDef.hpp"


namespace misc
{
	
	//!This class provides function for parsing strings
	class MW_5AXUTIL_API mwStringTokenizer
	{
	public:
		typedef std::vector<misc::mwstring>		tokenList;
		typedef tokenList::const_iterator	tokenListIterator;

	public:
		//!Default constructor
		/*!Constructs a string tokenizer with defines delimiter list and
			list of non-break delimiters
			\param delimiters Character set, that should be used for token delimiters.
			\param nbSigns Set of characters, to mark a non-breaking area
			\param useCharDelimiters select char/string delimiter
		 */
		explicit mwStringTokenizer( 
			const misc::mwstring &delimiters = _T(" "), 
			const misc::mwstring &nbSigns = _T("\""),
			const bool useCharDelimiters = true);
		
		//!Copy constructor
		mwStringTokenizer( const mwStringTokenizer &inST );

		//!Destructor
		~mwStringTokenizer();

	public:

		//!Parse a string
		/*!This function parses a given string and creates a list of tokens
			\param inString String to parse
		*/
		void Parse( const misc::mwstring& inString );
		
		//!Assign a string tokenizer to another one
		/*!
			\param inST string tokenizer to create a copy of
			\returns *this
		*/
		const mwStringTokenizer &operator=( const mwStringTokenizer &inST );

		//!Reset the string tokenizer
		/*!Reset the string tokenizer and empty the token list
		*/
		void Reset();
		
		//! Get number of tokens from string tokenizer
		const size_t GetSize() const;
	
		//!Set char delimiter list
		/*
			If you call both functions (SetCharDelimiters and SetStringDelimiter), the last will be used as delimiter
		*/
		void SetCharDelimiters( const misc::mwstring &delimiters );
		
		//!Set all string as delimiter 
		/*
			If you call both functions (SetCharDelimiters and SetStringDelimiter), the last will be used as delimiter
		*/
		void SetStringDelimiter( const misc::mwstring &delimiter );
		

		//!Set nbline list
		void SetNBSigns( const misc::mwstring &nbsigns );

		//!Get first token from a list
		tokenListIterator GetTokenBegin() const;

		//!Get last token from a list
		tokenListIterator GetTokenEnd() const;

		//!Get list of all tokens
		const tokenList &GetTokens() const;
		
		//! &operator[]
		/*!
			\param index of type unsigned long
			\returns &operator[] of type const misc::mwstring
		*/
		const misc::mwstring &operator[]( size_t index ) const;

	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	

		misc::mwstring m_charDelimiters;
		misc::mwstring m_stringDelimiter;
		bool           m_useCharDel;
		misc::mwstring m_sNbSigns;

		tokenList m_lstTokens;

		void ParseWithString( misc::mwstring inString );
		void ParseWithChar( const misc::mwstring& inString );
	
	#pragma warning(pop)
	};

};
#endif	//	MW_MWSTRINGTOKENIZER_HPP_
