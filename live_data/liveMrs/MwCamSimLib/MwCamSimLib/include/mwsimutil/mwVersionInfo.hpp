/* this file is generated by gen_version_info_hpp.py */
#ifndef MW_VERSIONINFO_HPP
#define MW_VERSIONINFO_HPP

 /* here follows version info */
#define VERSION_INFO_WORKING_COPY_URL          "https://svn.moduleworks.com/ModuleWorks/branches/release_5axis_2022_04_SPs/dev"
#define VERSION_INFO_RELEASE                   2022, 04, 7, 1
#define VERSION_INFO_DAY                       28
#define VERSION_INFO_MONTH                     3
#define VERSION_INFO_YEAR                      2022
#define VERSION_INFO_STRING                    (VERSION_INFO_WORKING_COPY_URL "@" "1539359" "")
#define VERSION_INFO_VERSION                   (VERSION_INFO_WORKING_COPY_URL "@" "1539359")
#define VERSION_INFO_BRANCH                    (VERSION_INFO_WORKING_COPY_URL)
#define VERSION_INFO_REV                       "1539359"
#define VERSION_INFO_REV_STRING                "Revision: 1539359, x64"
#define VERSION_INFO_BRANCH_REV_STRING         "Revision: 1539359, x64, release_5axis_2022_04_SPs"
#define VERSION_INFO_RELEASE_STRING            "2022, 04, 7, 1"
#define VERSION_INFO_RELEASE_YEAR_MONTH_STRING "2022.04"
#define VERSION_INFO_RELEASE_STRING_COMPLETE   "2022, 04, 7, 1"
#define VERSION_INFO_VERSION_TAG               ""
#define VERSION_INFO_VERSION_TAG_EXT           ""
#if defined(_DEBUG) && defined(NDEBUG)
    #error Both _DEBUG and NDEBUG are defined
#elif defined(_DEBUG)
    #define VERSION_INFO_CONFIGURATION             "DebugUnicode"
#else
    #define VERSION_INFO_CONFIGURATION             "ReleaseUnicode"
#endif
#define VERSION_INFO_PLATFORM                  "x64"
#define VERSION_INFO_YEAR_MONTH_VSVERSION_PLATFORM_REVISION "2022.04.VS2019.64.1539359"

/* PLEASE USE THIS FOR VERSION INFO: */
#define VERSION_INFO_FILE_VERSION_STRING       "2022.04.7.1"
#define VERSION_INFO_PRODUCT_VERSION_STRING    "2022.04.VS2019.64.1539359"
#define VERSION_INFO_COMPANY_NAME              "ModuleWorks GmbH"
#define VERSION_INFO_COPYRIGHT                 "Copyright © 2022 ModuleWorks GmbH. All rights reserved."

#ifdef _WIN32
#ifndef MW_DLL_FILE_DESCRIPTION
#define MW_DLL_FILE_DESCRIPTION VERSION_INFO_REV_STRING
#endif
#endif
#endif // MW_VERSIONINFO_HPP
