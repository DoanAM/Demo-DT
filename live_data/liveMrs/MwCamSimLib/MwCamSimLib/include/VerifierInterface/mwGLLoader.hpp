// (C) 2016-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWGLLOADER_HPP_
#define MW_MWGLLOADER_HPP_
#include "mwVerifierDllDefinition.hpp"

#ifndef MW_UNDER_CE

namespace VerifierUtil
{
namespace mwShaderRenderer
{
typedef void* (*LoadGLProc)(const char* name);

/// Initialize GL functions.
MW_VERIFIER_API int LoadGL(void);

/// Initialize GL functions by having a loader function (for example glfw).
/*  For example using glfw:
 *  @code{.cpp}
 *  if (!LoadGL((LoadGLProc)glfwGetProcAddress))
 *      fprintf(stderr, "Failed to initialize OpenGL context");
 *  \endcode
 */
MW_VERIFIER_API int LoadGL(LoadGLProc proc);

}  // namespace mwShaderRenderer
}  // namespace VerifierUtil
#endif

#endif  //	MW_MWGLLOADER_HPP_