// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILESYSTEM_HPP_
#define MW_MWFILESYSTEM_HPP_
#include "mwDefines.hpp"
#include "mwStringConversions.hpp"
#include "mwDllImpExpDef.hpp"
#include <vector>

namespace misc
{
class MW_5AXUTIL_API mwFileSystem
{
public:
	/// Returns the parent of the given file or directory name. Passing a root directory like "C:\\"
	/// into this function leads to non-specified results.
	///
	/// @note This only works on paths which use the platform-specific path separator ('\' on
	/// windows, '/' on linux).
	///
	/// Examples (on windows):
	/// - GetDirectoryName("C:\\Users\\file.txt") == "C:\\Users"
	/// - GetDirectoryName("C:\\Users") == "C:\\"
	/// - not specified: GetDirectoryName("C:\\").
	static misc::mwstring GetDirectoryName(const misc::mwstring& file);

#if defined(_WIN32)
	static const _TCHAR pathDelimiter = _T('\\');
	static const _TCHAR wrongPathDelimiter = _T('/');
#elif defined(__linux__) || defined(__APPLE__)
	static const _TCHAR pathDelimiter = _T('/');
	static const _TCHAR wrongPathDelimiter = _T('\\');
#endif

	/// Returns the platform-specific path delimiter ('\' on windows, '/' on linux).
	inline static const _TCHAR GetPathDelimiter()
	{
		return pathDelimiter;
	}

	/// Returns the linux path delimiter on windows, and the windows path delimiter on linux.
	inline static const _TCHAR GetWrongPathDelimiter()
	{
		return wrongPathDelimiter;
	}

	/// Normalizes the given path (to a certain degree):
	/// - On windows the path is converted to lower-case (by default)
	/// - all path delimiters are replaced by the platform default ('\' on windows, '/' on linux)
	/// - a path delimiter is inserted at the end, if missing.
	///
	/// @note If you also want to resolve symlinks, remove dots and dot-dot elements, then use @ref
	/// Canonical().
#ifdef _WIN32
	static void NormalizeDir(misc::mwstring& dirName, bool convertToLowerCase = true);
#else
	static void NormalizeDir(misc::mwstring& dirName, bool convertToLowerCase = false);
#endif

	/// Normalizes the given path (to a certain degree):
	/// - on windows the path is converted to lower-case (by default)
	/// - all path delimiters are replaced by the platform default ('\' on windows, '/' on linux)
	///
	/// @note If you also want to resolve symlinks, remove dots and dot-dot elements, then use @ref
	/// Canonical().
#ifdef _WIN32
	static void NormalizeFile(misc::mwstring& fileName, bool convertToLowerCase = true);
#else
	static void NormalizeFile(misc::mwstring& fileName, bool convertToLowerCase = false);
#endif

	/// Returns true if the given path points to a regular file
	static bool FileExists(const misc::mwstring& fileName);

	/// Returns true if the given path points to a directory
	static bool DirectoryExists(const misc::mwstring& dirName);

	/// Alias for @ref DirectoryExists.
	static bool IsDirectory(const misc::mwstring& fileName)
	{
		return DirectoryExists(fileName);
	}

	/// Recursively creates the given directory.
	///
	/// Passing a path to an existing file results in a failure. If the path points to an existing
	/// directory this function does nothing and returns "true".
	///
	/// @note on windows the path is converted to lower-case by default.
	///
	/// @returns true on success, false on failure
#ifdef _WIN32
	static bool MakeDirectory(const misc::mwstring& dirName, bool convertToLowerCase = true);
#else
	static bool MakeDirectory(const misc::mwstring& dirName, bool convertToLowerCase = false);
#endif

	/// Deletes the given directory and all it's contents.
	///
	/// Returns "false" if the given path is not a directory, or if some files could not be deleted.
	static bool DeleteDirectory(const misc::mwstring& dirName);

	/// Deletes the given file. Returns "true" on success.
	static bool FileDelete(const misc::mwstring& dirName);

	/// Recursively copies the given directory to a new location.
	///
	/// By default the destination directory is deleted if it exists. If you don't want that you can
	/// set @p failExists to "true".
	///
	/// @note This is not an atomic operation: if some of the file operations fail then you may
	/// end up with a partial copy of the directory.
	///
	/// @returns "true" if the copy operation was successful.
	static bool CopyDirectory(
		const misc::mwstring& sourceDir,
		const misc::mwstring& destDir,
		const bool failExists = false);

	/// Copies the file to a new location. If @p failExists is "false", then any existing file (but
	/// not directory) is overwritten.
	///
	/// @returns "true" on success.
	static bool FileCopy(
		const misc::mwstring& sourceFile,
		const misc::mwstring& destFile,
		const bool failExists = false);

	/// Renames the given file.
	///
	/// @returns "true" on success.
	static bool FileRename(const misc::mwstring& sourceFile, const misc::mwstring& destFile);

	/// Copies the given file to the new location, and deletes the old version.
	///
	/// Any existing destination file is deleted iff @p failExists is false.
	static bool FileMove(
		const misc::mwstring& sourceFile,
		const misc::mwstring& destFile,
		const bool failExists = false);

	/// Returns the size of the given file.
	///
	/// @throws misc::mwException if the given file can not be accessed.
	static int64_t GetFileSize(const misc::mwstring& fileName);

	/// @name Temp Filename Creation
	/// These functions return reasonably-unique file names, by including a high-precision time
	/// stamp and the process- and thread id. They also make sure that the file name doesn't exist
	/// when they return.
	/// @{

	/// Returns a unique file name in the temp directory of the user
	static misc::mwstring CreateTempFileName();

	/// Returns the path of the system temp folder
	///
	/// On Windows this is the result of GetTempPathW (usually C:\\TEMP)
	static misc::mwstring GetTempFolder(const bool bConvertToLowerCase = false);

	/// Returns a unique file name with the specified extension
	static misc::mwstring CreateTempFileName(const misc::mwstring& fileExt);

	/// Create a unique file name with the specified extension and inside the given folder
	static misc::mwstring CreateTempFileName(
		const misc::mwstring& parentFolder,
		const misc::mwstring& fileExtension,
		const misc::mwstring& filePrefix = _T(""));

	/// Like @ref CreateTempFileName(const misc::mwstring&, const misc::mwstring&, const misc::mwstring&), but also
	/// creates an empty file with that name.
	static misc::mwstring CreateTempFile(
		const misc::mwstring& parentFolder,
		const misc::mwstring& fileExtension,
		const misc::mwstring& filePrefix = _T(""));

	/// Like @ref CreateTempFileName(const misc::mwstring&), but also creates an empty file with
	/// that name.
	static misc::mwstring CreateTempFile(const misc::mwstring& fileExt);

	/// Like @ref CreateTempFileName(), but also creates an empty file with that name.
	static misc::mwstring CreateTempFile();
	// @}

	static time_t GetFileLastModificationTime(const misc::mwstring& fileName);

	static time_t GetFileLastAccessedTime(const misc::mwstring& fileName);

	static time_t GetFileCreationTime(const misc::mwstring& fileName);

	static bool IsReadable(const misc::mwstring& fileName);

	static bool IsWritable(const misc::mwstring& fileName);

	static bool IsFileOpenedByAnotherProcess(const misc::mwstring& fileName);

	static bool IsFileFreeToWrite(const misc::mwstring& fileName);

	static bool IsPathAbsolute(const misc::mwstring& fileName);

	static bool IsPathRelativeToCurrentDir(const misc::mwstring& fileName);

	static bool AreTextFilesEqual(
		const misc::mwstring& firstFileName, const misc::mwstring& secondFileName);

	/// Concatenates the given paths. If path2 contains an absolute path, then this method returns
	/// path2.
	static misc::mwstring CombinePath(const misc::mwstring& path1, const misc::mwstring& path2);
#ifndef UNDER_CE
#ifdef _WIN32
	static misc::mwstring GetCurrentPath(bool convertToLowerCase = true);

	/// - resolves symlinks
	/// - removes ./ and ../ elements
	/// - changes all path separator to the platform default ('\' on windows, '/' on linux)
	/// - converts the path to lower-case if @p convertToLowerCase is enabled
	static misc::mwstring Canonical(const misc::mwstring& path, bool convertToLowerCase = true);
#else
	static misc::mwstring GetCurrentPath(bool convertToLowerCase = false);
	static misc::mwstring Canonical(const misc::mwstring& path, bool convertToLowerCase = false);
#endif
#endif

	/// If you're using this function via 5axutil.dll or mwsimutil.dll, then this returns the path
	/// of the DLL. Otherwise, if it's statically linked this function returns the name of the
	/// current executable.
	static misc::mwstring GetCurrentExePath();

protected:
private:
	//! Constructor not allowed since it's a static class
	mwFileSystem();
};
}		// namespace misc
#endif	//	MW_MWFILESYSTEM_HPP_
