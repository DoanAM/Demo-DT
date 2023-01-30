// (C) 2011-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOMPATIBILITYCHECKER_HPP_
#define MW_MWCOMPATIBILITYCHECKER_HPP_
#include <exception>
#include <string>
#include <vector>

#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwVersionInfoHelper.hpp"

#ifdef UNDER_CE
#include "mwException.hpp"
#endif

#ifdef _MSC_VER
#if _MSC_VER == 1600
#include <crtversion.h>

#define _MWDEFTOSTR(x) #x
#define _MWCONCATDEFSTR(a, b, c, d, e, f, g) _MWDEFTOSTR(a) ## _MWDEFTOSTR(b) ## _MWDEFTOSTR(c) ## _MWDEFTOSTR(d) ## _MWDEFTOSTR(e) ## _MWDEFTOSTR(f) ## _MWDEFTOSTR(g)
#endif
#endif


namespace misc
{
	class MW_5AXUTIL_API mwCompatibilityChecker
	{
	public:
		friend class mwForcedCompatibilityCheck;

		mwCompatibilityChecker();

		virtual ~mwCompatibilityChecker();
#ifdef _WIN32
		void CheckCompatibility(bool showMessageBox = true)
#else
		void CheckCompatibility()
#endif
		{
#if defined (_WIN32)
			
			/*Starting VS2010, _SECURE_SCL is ignored if we are in Debug and _ITERATOR_DEBUG_LEVEL ==2 (Default value for Debug builds)
			  For this scenario it seems that we are binary compatible with default settings of an integrator, this is why we skip SCL validation
			  and not show the warning with SCL settings are different, since SCL settings doesn't have influence for this context.
			*/
			const bool ignoreSCLSettings = GetVSVersion() >= 1600 
										   && IsDebugBuild()
										   && GetIDLSetting() == 2;
			
			if(
				GetIDLSetting() != compiled_ITERATOR_DEBUG_LEVEL ||
				(!ignoreSCLSettings && GetSCLSetting() != compiled_SECURE_SCL) ||
				GetDebugSetting() != compiledDebug ||
				!AreVSVersionsCompatible(GetVSVersion(), compiledVSVersion) ||
				GetIteratorSetting() != compiledIteratorDebugging ||
				GetVectorSize() != compiledVectorSize ||
				GetIteratorSize() != compiledIteratorSize ||
				GetStringSize() != compiledStringSize ||
				!IsSameCRTVersion())
			{
				char buffer[4*1024] = "Unknown Error";

				GetConfigurationMessage(buffer, sizeof(buffer), true);

				bool throwException = true;
				if(showMessageBox)
				{
					if(ShowMessageBox(buffer) != 2 /*cancel*/)
					{
						throwException = false;
					}
				}

				if(throwException)
				{
#ifdef UNDER_CE
					throw misc::mwException(0, misc::mwstring(buffer));
#else
					throw std::runtime_error(buffer);
#endif
				}
			}
#endif
		}

		void ShowSettings()
		{
			char buffer[4*1024] = {0};
			int bufferSize = sizeof(buffer);

			GetConfigurationMessage(buffer, bufferSize, false);

			ShowMessageBox(buffer, false);
		}

		static bool AreVSVersionsCompatible(const int version1, const int version2)
		{
			if (version1 == version2)
				return true;

			/*Looks like VS2015 and VS2017 are binary compatible so if customer uses VS2017 with
			our VS2015 libraries we skip VS version validation. That includes also subversions*/

			return IsVSVersionPartOfMajorVersion(version1, 1900) &&
				   IsVSVersionPartOfMajorVersion(version2, 1900);
		}


	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	

		int ShowMessageBox(const char* error, bool isError = true);
		
#ifdef _WIN32
		void GetConfigurationMessage(char* buffer, int bufferSize, bool isErrorMessage = true)
#else
		void GetConfigurationMessage(char*, int, bool)
#endif
		{
#if defined (_WIN32)
			int written = 0;

			const char *header = (isErrorMessage) ? "Mismatch!" : "Configuration";
			
			if(!IsSameCRTVersion() || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "C++ Runtime Version (CRT) %s\nYour setting: %s, ModuleWorks compiled with: %s\n\n", header, GetCRTVersion(), compiledCRTVersion);
			}
			if(GetVSVersion() != compiledVSVersion || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Visual Studio Version %s\nYour compiler: %s, ModuleWorks compiled with: %s\n\n", header, GetVSVersionString(GetVSVersion()), GetVSVersionString(compiledVSVersion));
			}
			if(GetDebugSetting() != compiledDebug || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "DEBUG / RELEASE %s\nYour configuration is: %s, ModuleWorks compiled as: %s\n\n", header, (GetDebugSetting() == 1 ? "DEBUG" : "RELEASE") , (compiledDebug == 1 ? "DEBUG" : "RELEASE"));
			}
			if (GetIDLSetting() != compiled_ITERATOR_DEBUG_LEVEL || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "_ITERATOR_DEBUG_LEVEL %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetIDLSetting(), compiled_ITERATOR_DEBUG_LEVEL);
			}
			if (GetSCLSetting() != compiled_SECURE_SCL || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "_SECURE_SCL %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetSCLSetting(), compiled_SECURE_SCL);
			}
			if(GetIteratorSetting() != compiledIteratorDebugging || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "_HAS_ITERATOR_DEBUGGING %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetIteratorSetting(), compiledIteratorDebugging);
			}
			if(GetStringSize() != compiledStringSize || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Size of string %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetStringSize(), compiledStringSize);
			}
			if(GetVectorSize() != compiledVectorSize || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Size of vector<double> %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetVectorSize(), compiledVectorSize);
			}
			if(GetIteratorSize() != compiledIteratorSize || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Size of vector<double>::iterator %s\nYour setting: %d, ModuleWorks compiled value: %d\n\n", header, GetIteratorSize(), compiledIteratorSize);
			}
			if(GetRevision() != compiledRevision || !isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Revision of ModuleWorks-Library %s (Not critical)\nExpected: %d, ModuleWorks compiled with: %d\n\n", header, mwVersionInfoHelper::GetRevision(), compiledRevision);
			}

			if(isErrorMessage)
			{
				written += sprintf_s(buffer + written, bufferSize - written, "Make sure you are not mixing debug and release DLLs or Assemblies.\nPlease contact ModuleWorks Support if you need advice on how to resolve the incompatibilities, thank you!");
			}
#endif
			
		}

		static int GetVSVersion()
		{
			int ret = -1;

#ifdef _MSC_VER
			ret = _MSC_VER;
#endif

			return ret;
		}

		static const char* GetVSVersionString(int version)
		{
			const char* ret = "Unknown Version";
			switch(version)
			{
				case 1200:
					ret = "Visual Studio 6.0";
					break;
				case 1300:
					ret = "Visual Studio 7.0";
					break;
				case 1310:
					ret = "Visual Studio 7.1";
					break;
				case 1400:
					ret = "Visual Studio 8.0 (VS 2005)";
					break;
				case 1500:
					ret = "Visual Studio 9.0 (VS 2008)";
					break;
				case 1600:
					ret = "Visual Studio 10.0 (VS 2010)";
					break;
				case 1700:
					ret = "Visual Studio 11.0 (VS 2012)";
					break;
				case 1800:
					ret = "Visual Studio 12.0 (VS 2013)";
					break;
				case 1900:
					ret = "Visual Studio 14.0 (VS 2015)";
					break;
				case 1910://VS2017 Release
				case 1911://VS2017 Update3
					ret = "Visual Studio 15.0 (VS 2017)";
					break;
			};

			return ret;
		}

		static int GetSCLSetting()
		{
			int ret = 0;
#ifdef _SECURE_SCL
			ret = _SECURE_SCL;
			//#else ifdef SECURE_SCL
			//		ret = SECURE_SCL;
#endif
			return ret;
		}

		static int GetDebugSetting()
		{
			int ret = 0;
#ifdef _DEBUG
			ret = _DEBUG;
#endif
			return ret;
		}

		static int GetIteratorSetting()
		{
			int ret = 0;
#ifdef _HAS_ITERATOR_DEBUGGING
			ret = _HAS_ITERATOR_DEBUGGING;
#endif
			return ret;
		}

		static int GetStringSize()
		{
			int ret = sizeof(std::string);

			return ret;
		}

		static int GetVectorSize()
		{
			int ret = sizeof(std::vector<double>);

			return ret;
		}

		static int GetRevision()
		{
			return mwVersionInfoHelper::GetRevision();
		}

		static int GetIteratorSize()
		{
			int ret = sizeof(std::vector<double>::iterator);

			return ret;
		}

		static const char *GetCRTVersion()
		{
			const char *ret = "Unknown Version";

#ifdef _CRT_ASSEMBLY_VERSION
			ret = _CRT_ASSEMBLY_VERSION;
#else
#ifdef _MWCONCATDEFSTR
			ret =  _MWCONCATDEFSTR(_VC_CRT_MAJOR_VERSION, ., _VC_CRT_MINOR_VERSION, ., _VC_CRT_BUILD_VERSION, ., _VC_CRT_RBUILD_VERSION);
#endif
#endif
			return ret;
		}

		bool IsSameCRTVersion()
		{
			return true;
		}

		static bool IsDebugBuild()
		{
			#ifdef _DEBUG
				return true;	
			#else
				return false;
			#endif
		}

		static int GetIDLSetting()
		{
			int ret = 0;
			
			#ifdef _ITERATOR_DEBUG_LEVEL
				ret = _ITERATOR_DEBUG_LEVEL;
			#endif
			
			return ret;
		}
		//!Check if a given VS version is part of a VS Major version
		/*e.g 1900,19010,1911 are subversions of 1900 major version
		*/
		static const bool IsVSVersionPartOfMajorVersion(const int vsVersion,const int vsMajorVersion)
		{
			const int subVersion = vsVersion % vsMajorVersion;
			return subVersion >= 0 && subVersion <= 99;
		}

		int compiled_ITERATOR_DEBUG_LEVEL;
		int compiled_SECURE_SCL;
		int compiledDebug;
		int compiledVSVersion;
		int compiledIteratorDebugging;
		int compiledStringSize;
		int compiledVectorSize;
		int compiledIteratorSize;
		const char *compiledCRTVersion;
		int compiledRevision;
		bool showErrorOnlyOnce;
		//static int instanceCount;
	
	#pragma warning(pop)
	};


#if !defined(SUPPRESSCOMPATIBILITYCHECK) && defined(_WIN32)
	
	class mwForcedCompatibilityCheck
	{
	public:
		mwForcedCompatibilityCheck()
		{
			static int __mwCOMPCHECKERINSTANCECOUNT = 0;

			if(__mwCOMPCHECKERINSTANCECOUNT == 0)
			{
				++__mwCOMPCHECKERINSTANCECOUNT;
				mwCompatibilityChecker c;
				c.showErrorOnlyOnce = true;
				c.CheckCompatibility();
				
			}
		}
	private:
	};

	static const mwForcedCompatibilityCheck __mwCOMPCHECKER;
#endif
}
#endif	//	MW_MWCOMPATIBILITYCHECKER_HPP_
