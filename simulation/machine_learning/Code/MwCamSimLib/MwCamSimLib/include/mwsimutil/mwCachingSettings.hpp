// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCACHINGSETTINGS_HPP_
#define MW_MWCACHINGSETTINGS_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwWinRegOrCustomParamStorage.hpp"


/*!This class is used for managing settings for 
caching mechanism which is implemented at toolpath calculation level */

namespace misc
{

	class MW_5AXUTIL_API mwCachingSettings
	{
	public:

		enum CachingUsageFlags
		{
			SCU_LOW_LEVEL = 1 << 0,
			SCU_WHOLE_TOOLPATH = 1 << 1,
		};
 
		//!Check if caching mechanism is enabled
		/*By default caching mechanism is enabled
			\return value of flag which tells if caching mechanism is enabled
					true if any kind of caching is enabled. see enum CachingUsageFlags
					false if all kinds of caching are disabled
		*/
		static bool GetCachingUsageFlg();

		/*! Check if caching mechanism is enabled
			\return bitmask of caching usage flags, defined by "cachingUsageFlags" parameter.
			\param cachingUsageFlags - a bitmask of caching usage flags. see enum CachingUsageFlags
		*/
		static int GetCachingUsageFlg(int cachingUsageFlags);

		//!Turns ON/OFF caching mechanism
		/*
			\param useCaching flag for turning ON/OFF caching mechanism
				if true then caching will be turned ON, same as SetCachingUsageFlg(true, SCM_WHOLE_TOOLPATH|SCM_LOW_LEVEL)
				if false then caching will be turned OFF, same as SetCachingUsageFlg(false, SCM_WHOLE_TOOLPATH|SCM_LOW_LEVEL)
		*/
		static void SetCachingUsageFlg(const bool useCaching);

		/*! Sets one or more caching modes
			\param enable - enables/disables caching flags defined by "cachingUsageFlags" parameter. 
							does not change	other flags 
			\param cachingUsageFlags - a bitmask of caching modes flags. see enum CachingUsageFlags
		*/
		static void SetCachingUsageFlg(bool enable, int cachingUsageFlags);

	
		//!Gets the full path where the caching files will be generated
		/*By default, caching files will be generated in the temp folder of the current user
			\return caching full path
		*/
		static misc::mwstring GetCachingPath();
	
		//!Sets the full path where the caching files will be generated
		/*By default, caching files will be generated in the temp folder of the current user
		 If given path is not valid, no changes in current caching path will be made
			\param toSet is caching path to be set
		*/
		static void SetCachingPath(const misc::mwstring& toSet);

	
		//!Gets maximum size allowed for all cache files (in Megabytes)
		/*By default, maximum size for all cache file is set to 5% from free space of the drive where caching is generated
		If size of all cache files is greater that this maximum cache size, then the 
		  oldest cache files will be automatically deleted till cache size is reduced to ~ 50% from maximum allowed size
			\return maximum size that all cache files can reach
		*/
		static double GetCachingMaxSizeInMegaBytes();
	
		//!Sets maximum size allowed for all cache files (in Megabytes)
		/*By default, maximum size for all cache file is set to 5% from free space of the drive where caching is generated
		If size of all cache files is greater that this maximum cache size, then the 
		  oldest cache files will be automatically deleted till cache size is reduced to ~ 50% from maximum allowed size
			\param toSet is maximum cache size to be set
		*/
		static void SetCachingMaxSizeInMegaBytes(const double& toSet);
	
		//!Gets the interval at which caching cleaner is run (in seconds)
		/*First time a toolpath calculation is started for current process, the cache cleaner will 
		 be activated and will run in a thread.
		 This function gets the time interval (in seconds) at which the cache cleaner will check cache folder and will delete
		 cache files if their size is greater than maximum allowed size.
		 Default value for the check interval is 5 minutes.
		 \return cache cleaner run time in seconds
		*/
		static int GetCachingCleanerRunIntervalInSeconds();
	
		//!Sets the interval at which caching cleaner is run (in seconds)
		/*First time a toolpath calculation is started for current process, the cache cleaner will 
		 be activated and will run in a thread.
		 This function sets the time interval (in minutes) at which the cache cleaner will check cache folder and will delete
		 cache files if their size is greater than maximum allowed size.
		 Default value for the check interval is 5 minutes.
		 \param toSet is time interval in seconds to at which cache cleaner will run
		*/
		static void SetCachingCleanerRunIntervalInSeconds(const int& toSet);

	protected:

	private:
	
		//!Validates the path set by user for cache files
		/*
			\param toValidate is cache path to be validated
			throws exception if path is not valid (e.g specified folder doesn't exist)
		*/
		static void ValidateCachingPath(const misc::mwstring& toValidate);
	
		//!Validates maximum size of caching set by user
		/*
			\param toValidate is caching size to be validated
			throws exception if caching size is not valid
		*/
		static void ValidateCachingMaxSize(const double& toValidate);
	
		//!Get free space of the drive where caching is setup (in megabytes)
		/*
			\param cachePath is full path to cache files
			\return drive free space in megabytes for the drive where cache files are generated
		*/
		static double GetCachingDriveFreeSpaceInMegaBytes(const misc::mwstring& cachePath);
	
		//!Validates running interval for cache cleaner (in seconds)
		/*
			\param toValidate is running interval to be validated
			throws exception if running interval is not valid
		*/
		static void ValidateCachingCleanerRunInterval(const int& toValidate);
	
		//!Internal parameter, see internal class mwCachingInternalSettings for description
		static void SetInternalFlgIgnoreExistingCache(const bool& ignoreExisting );
	
		//Internal parameter, see internal class mwCachingInternalSettings for description
		static bool GetInternalFlgIgnoreExistingCache();
	
		//!Internal parameter, see internal class mwCachingInternalSettings for description
		static void SetInternalFlgDebugCache(const bool& debugCacheFlg);
	
		//!Internal parameter, see internal class mwCachingInternalSettings for description
		static bool GetInternalFlgDebugCache();
	
		//!Internal parameter, see internal class mwCachingInternalSettings for description
		static void SetInternalFlgUseCacheCleaner(const bool& flg);
	
		//!Internal parameter, see internal class mwCachingInternalSettings for description
		static bool GetInternalFlgUseCacheCleaner();
	

		//!Internal parameter, Gets flag to get error when cached value does not exist in second test turn
		static bool GetInternalFlgCachingReadOnly();
		//!Internal parameter, Sets flag to get error when cached value does not exist in second test turn
		static void SetInternalFlgCachingReadOnly(bool bCachingReadOnly);
		
		//!Sets flag for ignoring caching exceptions 
		/*By default, these exceptions are ignored and as fallback we compute
		the operation without caching
			\param flg is value of the flag for ignoring caching exceptions
		*/
		static void SetInternalFlgIgnoreCachingExceptions(const bool flg);
		
		//!Gets flag for ignoring caching exceptions 
		/*By default, these exceptions are ignored and as fallback we compute
		the operation without caching
			\return value of the flag for ignoring caching exceptions
		*/
		static bool GetInternalFlgIgnoreCachingExceptions();

		//!Constructor not allowed for static class
		mwCachingSettings();
	
		//!Helper struct for caching stored settings
		struct CachingStoredSettingsStaticData
		{
			CachingStoredSettingsStaticData();

			~CachingStoredSettingsStaticData();

			const misc::mwstring CSS_COMPANY_NAME;
			const misc::mwstring CSS_APP_NAME;
			const misc::mwstring CSS_SECTION_NAME;
			
			//caching main stored settings flags
			const misc::mwstring CSS_CACHING_ENABLED_FLG; //usage
			const misc::mwstring CSS_CACHING_PATH;//path
			const misc::mwstring CSS_CACHING_MAX_SIZE;//max. size
			const misc::mwstring CSS_CACHING_CLEANER_RUN_INTERVAL;//cache cleaner run interval
			const misc::mwstring CSS_CACHING_TOOLPATH_FLG;

			//"Cache usage" values
			const int CACHE_FLG_NOT_SET_VALUE;
			const int CACHE_FLG_ENABLED_VALUE;
			const int CACHE_FLG_DISABLED_VALUE;

			//"Cache path" values
			const misc::mwstring CACHE_PATH_NOT_SET_VALUE;
			const misc::mwstring CACHE_PATH_DEFAULT_VALUE;
			
			//"Cache size" values
			const double CACHE_MAX_SIZE_NOT_SET_VALUE;
			const double CACHE_MAX_SIZE_DEFAULT_VALUE;

			//"Cache cleaner" run interval
			const int CACHE_CLEANER_RUN_INTERVAL_NOT_SET_VALUE;
			const int CACHE_CLEANER_RUN_INTERVAL_DEFAULT_VALUE;

			//"Ignore existing cache(internal parameter)"
			const misc::mwstring CSS_INTERNAL_FLG_IGNORE_EXISTING_CACHE;//internal parameter
			const int INTERNAL_FLG_IGNORE_EXISTING_CACHE_NOT_SET_VALUE;
			const int INTERNAL_FLG_IGNORE_EXISTING_CACHE_ENABLED_VALUE;
			const int INTERNAL_FLG_IGNORE_EXISTING_CACHE_DISABLED_VALUE;

			//"readonly cache(internal parameter)"
			const misc::mwstring CSS_INTERNAL_FLG_CACHING_READONLY;
			const int INTERNAL_FLG_CACHING_READONLY_NOT_SET_VALUE;
			const int INTERNAL_FLG_CACHING_READONLY_ENABLED_VALUE;
			const int INTERNAL_FLG_CACHING_READONLY_DISABLED_VALUE;

			//"Debug cache(internal parameter)"
			const misc::mwstring CSS_INTERNAL_FLG_DEBUG_CACHE;//internal parameter
			const int INTERNAL_FLG_DEBUG_CACHE_NOT_SET_VALUE;
			const int INTERNAL_FLG_DEBUG_CACHE_ENABLED_VALUE;
			const int INTERNAL_FLG_DEBUG_CACHE_DISABLED_VALUE;
			//

			//use cache cleaner (internal parameter)
			const misc::mwstring CSS_INTERNAL_FLG_USE_CACHE_CLEANER;//internal parameter
			const int INTERNAL_FLG_USE_CACHE_CLEANER_NOT_SET_VALUE;
			const int INTERNAL_FLG_USE_CACHE_CLEANER_ENABLED_VALUE;
			const int INTERNAL_FLG_USE_CACHE_CLEANER_DISABLED_VALUE;

			//"Ignore caching exceptions (internal parameter)"
			const misc::mwstring CSS_INTERNAL_FLG_IGNORE_CACHING_EXCEPTIONS;//internal parameter
			const int INTERNAL_FLG_IGNORE_CACHING_EXCEPTIONS_NOT_SET_VALUE;
			const int INTERNAL_FLG_IGNORE_CACHING_EXCEPTIONS_ENABLED_VALUE;
			const int INTERNAL_FLG_IGNORE_CACHING_EXCEPTIONS_DISABLED_VALUE;
			//

			#if defined (_WIN32) && !defined(UNDER_CE)
				misc::mwWinRegOrCustomParamStorage  m_settingsStorage;
			#endif
		
			double GetCacheDefaultMaxSizeInMegaBytes(const misc::mwstring& cachePath) const;
			misc::mwstring GetCacheDefaultPath() const;
		private:
			CachingStoredSettingsStaticData& operator=(const CachingStoredSettingsStaticData&) { return *this; }// non copyable
		};//CachingStoredSettingsStaticData
	
		
		friend class mwCachingInternalSettings;
	};
};//namespace
#endif	//	MW_MWCACHINGSETTINGS_HPP_
