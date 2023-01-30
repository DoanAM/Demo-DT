// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef mwvUtilityHelper_h__
#define mwvUtilityHelper_h__

#include "mwVerifierDllDefinition.hpp"
#include "mwvUtilDefines.hpp"

namespace VerifierUtil
{
namespace OpenGL
{
class CameraState;
class ContextBackup;
}  // namespace OpenGL

#ifndef MW_CHECK_GL_ERROR
#define MW_CHECK_GL_ERROR() VerifierUtil::mwvUtilityHelper::CheckOpenGl(__FILE__, __LINE__);
#endif

#ifndef MW_CHECK_GL_ERROR_MEMORY
#define MW_CHECK_GL_ERROR_MEMORY() \
	VerifierUtil::mwvUtilityHelper::CheckOpenGlOutOfMemory(__FILE__, __LINE__);
#endif

class MW_VERIFIER_API mwvUtilityHelper
{
public:
	/// Save previous OpenGL state. Restore when object is out of scope.
	struct GlStateSaver
	{
		/// calls glPushAttrib(GL_ALL_ATTRIB_BITS)
		GlStateSaver();

		/// calls glPopAttrib()
		~GlStateSaver();
	};

	/// Gets 3d OpenGL coordinates using last stored scene
	///
	/// In contrast to GetOGLPos(), this function uses the view
	/// and matrices, that were stored during last Draw() call
	/// via SaveLastStockOpenGlState().
	static bool GetPos(int x, int y, float3d& dest, float& error);

	/// Gets openGL coordinates
	///
	/// Gets the openGL coordinates of the passed window position.
	/// @param win  the window position you want to translate
	/// @returns the translated openGL coordinates
	static float3d GetOGLPos(const float3d& win);
	static void GetOGLPos(const float3d& win, float3d& scene);

	/// Gets window coordinates
	///
	/// Gets the window coordinates of the passed openGL position.
	/// @param scene  the openGL position you want to translate
	/// @returns the translated window coordinates
	static float3d GetWinPos(const float3d& scene);
	static void GetWinPos(const float3d& scene, float3d& win);

	/// Gets world from screen coordinates
	///
	/// Gets world coordinates from screen coordinates and an approximated error of the position
	/// @param [in]  x     the x part of the screen coordinates
	/// @param [in]  y     the y part of the screen coordinates
	/// @param [out] pos   the calculated 3d position
	/// @param [out] error the approximated error as a distance
	/// @returns TRUE if the calculation was successful
	static bool GetWorldPositionFromScreen(int x, int y, float3d& pos, float& error);

	static bool WindowPosToScenePos(int x, int y, int2d& dest);

	static void GetEndPosInScreenDist(
		float3d& point, float length, float3d& vPinEndPos, float startPointOffset);

	/// Throws an mwException if a glError is detected
	static void CheckOpenGl(const char* file, const unsigned int line);

	/// Throws an mwException if GL_OUT_OF_MEMORY is detected. Other errors are ignored.
	static void CheckOpenGlOutOfMemory(const char* file, const unsigned int line);

	static void SaveLastStockOpenGlState();

	static double* GetModelViewMatrix();

	static double* GetProjectionMatrix();
	static bool StockWasDrawn();
	static bool IsFSAAenabled();
	static void readPixelDepth(int winX, int winY, int width, int height, float* winZ);
};
}  // namespace VerifierUtil

#endif  // mwvUtilityHelper_h__
