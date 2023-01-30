// (C) 2019-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMESSAGEBOXWRAPPER_HPP_
#define MW_MWMESSAGEBOXWRAPPER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"

#if !defined(__linux__) && !defined(__APPLE__)
namespace misc 
{
	namespace detail 
	{

#define MB_OK 0x00000000L

			int MW_5AXUTIL_API mwMessageBox(const misc::mwstring& text, const misc::mwstring& caption, const unsigned int type = MB_OK);

		}
	}
#endif
#endif	//	MW_MWMESSAGEBOXWRAPPER_HPP_
