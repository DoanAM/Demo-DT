// (C) 2004-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWOPENGLSCENEHELPER_HPP_
#define MW_MWOPENGLSCENEHELPER_HPP_
#if defined (_WIN32) && !defined (NO_GL)
//#############################################################################
#include "mwDllImpExpDef.hpp"
// cadcam includes
#include "mwMatrix.hpp"
#include "mwTPoint3d.hpp"

namespace mmedia
{
	template<typename T>
	class MW_5AXUTIL_API mwOpenGLSceneHelper
	{
	public:
		
		//! MatrixHomogenousToOpenGL function
		/*!
		\param source of type const cadcam::mwMatrix<T,4,4> &
		\param matrix[] of type T
		*/
		static void MatrixHomogenousToOpenGL(			
			const cadcam::mwMatrix<T,4,4>& source, T matrix[] );
	
		//! MatrixOpenGLToHomogenous function
		/*!
		\param source[] of type const T
		\param matrix of type cadcam::mwMatrix<T,4,4> &
		*/
		static void MatrixOpenGLToHomogenous( 			
			const T source[], cadcam::mwMatrix<T,4,4>& matrix );

		static cadcam::mwTPoint3d<T>  RotateAroundVec( 			
			const cadcam::mwTPoint3d<T>& p, cadcam::mwTPoint3d<T> d, const T a);

		static T GetScaleFactorForOrthoView();
	};

	
} // mmedia namespace
#endif
#endif	//	MW_MWOPENGLSCENEHELPER_HPP_
