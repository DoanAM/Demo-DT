// (C) 2006-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// Small helper file for common definitions

#ifndef MW_MWVUTILDEFINES_HPP_
#define MW_MWVUTILDEFINES_HPP_
#include <mwAvoid_Warnings.hpp>
#include <mwMathUtilities.hpp>
#include <mwMesh.hpp>
#include <mwTPoint2d.hpp>
#include <mwTPoint3d.hpp>
// for quicker debugging
#include <iostream>
#include <mwStream.hpp>
#include <sstream>
#include <string>

#if defined(_WIN32) && !defined(UNDER_CE)
extern "C"
{
	__declspec(dllimport) void __stdcall OutputDebugStringW(const wchar_t* lpOutputString);
};
#endif

namespace VerifierUtil
{
// 	#if defined(_DEBUG) && defined (_WIN32)
// 	static int DISABLE_MEMORY_LEAK_DUMPS = _CrtSetDbgFlag(0);
// 	#endif

/// Returns the file name given a Windows file path string.
inline std::string GetFilenameUtil(const char* f)
{
	std::string sf(f);
	const size_t pos = sf.find_last_of('\\');
	if (pos != std::string::npos)
	{
		return sf.substr(pos + 1);
	}
	else
	{
		return sf;
	}
}
#if defined(UNDER_CE)
#define DEBUG_WIN_UTIL(text)                                                                      \
	{                                                                                             \
		std::cout << "MWVUtil: " << __FILE__ << " (" << __LINE__ << "):\t " << text << std::endl; \
	}
#elif defined(_WIN32)
#define DEBUG_WIN_UTIL(text)                                                            \
	{                                                                                   \
		std::wostringstream ost;                                                        \
		ost << "MWVUtil: " << ::VerifierUtil::GetFilenameUtil(__FILE__).c_str() << " (" \
			<< __LINE__ << "):\t " << text << "\n";                                     \
		OutputDebugStringW(ost.str().c_str());                                          \
	}
#elif defined(__linux__) || defined(__APPLE__)
#define DEBUG_WIN_UTIL(text)                                                                      \
	{                                                                                             \
		std::wcout << L"MWVUtil: " << __FILE__ << L" (" << __LINE__ << L"):\t " << text << L"\n"; \
	}
#endif
}  // namespace VerifierUtil

// general Type definitions
////////////////////////////////////////////////////////////////////////////////
/// Mesh type definition
typedef cadcam::mwTMesh<float> Mesh;
/// Mesh pointer type definition
typedef misc::mwAutoPointer<Mesh> MeshPtr;
/// float 2d vertex type definition
typedef cadcam::mwTPoint2d<float> float2d;
typedef cadcam::mwTPoint2d<double> double2d;
/// float 3d vertex type definition
typedef cadcam::mwTPoint3d<float> float3d;
/// double 3d vertex type definition
typedef cadcam::mwTPoint3d<double> double3d;
/// integer 3d vertex type definition
typedef cadcam::mwTPoint3d<int> int3d;
/// integer 2d vertex type definition
typedef cadcam::mwTPoint2d<int> int2d;

/// defines position and orientation
typedef MATH::Frame<float> Frame;
/// defines position and orientation
typedef MATH::Frame<double> DFrame;

/// float 3d bounding box type definition
typedef cadcam::mw3dBoundingBox<float> BoundingBox3d;

#ifndef CUTSIM_BINARY_MARKER_UTIL
#define CUTSIM_BINARY_MARKER_UTIL
/// in/out stream marker
static const unsigned int CUTSIM_BINARY_MARKER =
	(unsigned int)0x5543574D;  // hex value for MWCU text
#endif
#endif  //	MW_MWVUTILDEFINES_HPP_
