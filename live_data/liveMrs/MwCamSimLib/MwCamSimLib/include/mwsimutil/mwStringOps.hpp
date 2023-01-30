// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTRINGOPS_HPP_
#define MW_MWSTRINGOPS_HPP_
#include <functional>
#include "mwStringConversions.hpp"
#include	"mwDllImpExpDef.hpp"
#include <locale>
#if defined(__linux__) || defined(__APPLE__)
#include "mwTChar.hpp"
#endif

namespace misc
{
	//!Transform the string to lower chars.
	/*!Transform the string to lower chars.
		\param toTransform reference to a string to be transformed
	*/
	inline void string_down( misc::mwstring &toTransform )
	{
		for (size_t i = 0; i < toTransform.size(); i++)
		{
			toTransform[i] = std::tolower(toTransform[i], std::locale());
		}
	};
	inline mwstring to_string_down(const mwstring &toTransform)
	{
		mwstring result = toTransform;
		string_down(result);
		return result;
	};

	//!Transform the string to upper chars.
	/*!Transform the string to upper chars.
		\param toTransform reference to a string to be transformed
	*/
	inline void string_up( misc::mwstring &toTransform )
	{
		for (size_t i = 0; i < toTransform.size(); i++)
		{
			toTransform[i] = std::toupper(toTransform[i], std::locale());
		}
	};
	inline mwstring to_string_up(const mwstring &toTransform)
	{
		mwstring result = toTransform;
		string_up(result);
		return result;
	};

	//!trims leading specified characters from the string
	/*!trims leading specified characters from the string
		\param rToTransform reference to a string to be transformed
		\param rTarget specifies the target characters to be trimmed (default is white space)
	*/
	inline void trim_left ( misc::mwstring & rToTransform , const misc::mwstring &rTarget = _T(" ") )
	{
		rToTransform.erase ( 0 , rToTransform.find_first_not_of ( rTarget ) );
	}

	//!trims trailing specified characters from the string
	/*!trims trailing specified characters from the string
		\param rToTransform reference to a string to be transformed
		\param rTarget specifies the target characters to be trimmed (default is white space)
	*/
	inline void trim_right ( misc::mwstring & rToTransform , const misc::mwstring &rTarget = _T(" ") )
	{
		rToTransform.erase ( rToTransform.find_last_not_of ( rTarget ) + 1 ) ;
	}

	//!trims leading and trailing specified characters from the string
	/*!trims leading and trailing specified characters from the string
		\param rToTransform reference to a string to be transformed
		\param rTarget specifies the target characters to be trimmed (default is white space)
	*/
	inline void trim ( misc::mwstring & rToTransform , const misc::mwstring &rTarget = _T(" ") )
	{
		trim_left ( rToTransform , rTarget );
		trim_right ( rToTransform , rTarget );
	}

	// returns the tailing numeric substring (ex : "stock123" -> "123" )
	inline const misc::mwstring ExtractNumericSuffix(const misc::mwstring& src)
	{
		const misc::mwstring digits(_T("0123456789"));
		const size_t n = src.size();
		size_t counter = 0;
		for(size_t i = 0; i < n; ++i)
		{
			const size_t j = n - i - 1;
			if(digits.find(src[j]) == digits.npos)
				break;
			counter++;
		}
		return src.substr(src.size() - counter , counter);
	}

	inline const misc::mwstring AddNonBreakingAreaMarker(
		const misc::mwstring& src,
		const misc::mwstring &delimiterThatRequiresNonBreakingAreaMarking = _T(" "), 
		const misc::mwstring &nonBreakingAreaMarker = _T("\""))
	{
		if(src.find(delimiterThatRequiresNonBreakingAreaMarking) == src.npos)
			return src;
		
		return nonBreakingAreaMarker + src + nonBreakingAreaMarker;
	}
	
	//!Predicate class used for removing some not allowed chars from a file name
	class IsNotAllowedChar
	{
	public:
		IsNotAllowedChar () 
			: m_notAllowedChars(L"\\/:?\"<>|;',*")
		{
		};

		bool operator()(const wchar_t& crtChar) const 	
		{
			mwstring::const_iterator It;
			mwstring::const_iterator ItEnd = m_notAllowedChars.end();

			for (It = m_notAllowedChars.begin() ; It != ItEnd ; ++ It )
			{
				if (crtChar == *It)
					return true;
			}
			return false;
		}
	private:
		IsNotAllowedChar& operator=(const IsNotAllowedChar&); // = delete
		const mwstring m_notAllowedChars;
	};
};
#endif	//	MW_MWSTRINGOPS_HPP_
