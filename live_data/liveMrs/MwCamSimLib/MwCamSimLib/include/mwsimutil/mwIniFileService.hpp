// (C) 2011-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWINIFILESERVICE_HPP_
#define MW_MWINIFILESERVICE_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include <cstddef>

namespace misc
{
	class MW_5AXUTIL_API mwIniFileService
	{
	public:
		static mwstring GetString(
			const mwstring& section,
			const mwstring& parameterName,
			const mwstring& defaultString,
			const mwstring& iniFileName,
			const std::size_t bufferSize = 255);

		static bool SetString(
			const mwstring& section,
			const mwstring& parameterName,
			const mwstring& value,
			const mwstring& iniFileName);

		static void RemoveString(
			const mwstring& section,
			const mwstring& parameterName,
			const mwstring& iniFileName);

		static int GetInt(
			const mwstring& section,
			const mwstring& parameterName,
			const int defaultValue,
			const mwstring& iniFileName);

		static void SetInt(
			const mwstring& section,
			const mwstring& parameterName, 
			const int value,
			const mwstring& iniFileName);

 		static bool GetBool(
			const mwstring& section,
			const mwstring& parameterName,
			const bool defaultValue,
			const mwstring& iniFileName);

		static void SetBool(
			const mwstring& section,
			const mwstring& parameterName,
			const bool value,
			const mwstring& iniFileName);

		static float GetFloat(
			const mwstring& section,
			const mwstring& parameterName, 
			const float defaultValue,
			const mwstring& iniFileName);

		static void SetFloat(
			const mwstring& section,
			const mwstring& parameterName, 
			const float value,
			const mwstring& iniFileName);

		static double GetDouble(
			const mwstring& section,
			const mwstring& parameterName, 
			const double defaultValue,
			const mwstring& iniFileName);

		static void SetDouble(
			const mwstring& section,
			const mwstring& parameterName, 
			const double value,
			const mwstring& iniFileName);

		typedef unsigned int subObptionsFlags;
		//! write in the ini file the parameter and a set of suboptions for it
		/*! it use the , to separate suboption index of it's value and ; to separate the suboptions themself
				ex: options=00000101 and allSubOptions=00011111 is wrote as
				PassParameterName = 1,1;2,0;3,1;4,0;5,0;
				ex: options=00000101 and allSubOptions=00000111 is wrote as
				PassParameterName = 1,1;2,0;3,1;
		*/
		static void SetSuboptionsAsFlags (
			const mwstring& section,
			const mwstring& parameterName,
			const subObptionsFlags& options,
			const subObptionsFlags& allSubOptions,
			const mwstring& iniFileName);
		//! get from the ini file a set of suboptions saved for the parameter 
		/*! it use the , to get suboption index and it's value and ; to separate the suboptions themself
			suboptions may miss from the list, will be considered 0
				ex: PassParameterName = 1,1;2,0;4,1;5,0; and allSubOptions=00011111 
				return 00001001 
				ex: PassParameterName = 1,1;2,0;4,1;5,0; and allSubOptions=00000111
				return 00000001 
			suboptions may be in aleatory order
				ex: PassParameterName = 4,1;2,0;1,1;5,0; and allSubOptions=00011111 
				return 00001001 
		*/
		static subObptionsFlags GetSuboptionsAsFlags (
			const mwstring& section,
			const mwstring& parameterName,
			const subObptionsFlags& defaultSubOptions,
			const subObptionsFlags& allSubOptions, 
			const mwstring& iniFileName);

	};
}
#endif	//	MW_MWINIFILESERVICE_HPP_
