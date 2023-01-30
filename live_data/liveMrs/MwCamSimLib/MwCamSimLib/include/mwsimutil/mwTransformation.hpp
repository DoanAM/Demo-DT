// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///                  this module describes the
/// mwTransformation class

//#############################################################################

#ifndef MW_MWTRANSFORMATION_HPP_
#define MW_MWTRANSFORMATION_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwMachDef.hpp"
#include <mwTPoint3d.hpp>
#include "mwMatrix.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwTransformation  
	{
	public:
		//#############################################################################
		typedef cadcam::mwMatrix<double, 4, 4>   mwMatrix4d;
		typedef misc::mwAutoPointer<mwMatrix4d>  mwMatrix4dPtr;
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw3axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,		  //!< part origin in machine coordinate system			
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition);	      //!< part position	    			
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle defines rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw4axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,		  //!< part origin in machine coordinate system			
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	      //!< part position
			const double& rotAngle);                      //!< angle in Degree	
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
		*/
			static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw5axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,		  //!< part origin in machine coordinate system			
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	      //!< part position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the absolute machine position from relative position
			/*!
			\param machDef defines 5+1 machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
			*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw6axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,		  //!< part origin in machine coordinate system			
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	      //!< part position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines 6axis contour machine definition
			\param partOrigin defines 3d translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param rotAngle2 defines third rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
			\Rotation axis order should be: 3rd under 2nd and 2nd under 1st; 3rd is fixed on machine and 1st rotate the tool or the workpiece;
			\Sample 1: for Head-Head-Table, 3rd on head, 2nd on head under 3rd, 1st rotate the table and fixed on machine;
			\Sample 2: for Head-Head-Head, 3rd rotate the tool, 2nd under 3rd, 1st under 2nd and fixed on machine;
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw6axCSMachDef& machDef,                //!< machine definition
			const cadcam::mwVector3d& partOrigin,		  //!< part origin in machine coordinate system			
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	      //!< part position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1,                      //!< angle in Degree
			const double& rotAngle2);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw3axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,                  //!< part position	    			
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle defines rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw4axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	                //!< part position
			const double& rotAngle,                                 //!< angle in Degree	
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw5axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	                //!< part position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines 5+1 machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw6axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	                //!< part position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the absolute machine position from relative position
		/*!
			\param machDef defines 6axis contour machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param partPosition defines part position in workpiece coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param rotAngle2 defines third rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
			\Rotation axis order should be: 3rd under 2nd and 2nd under 1st; 3rd is fixed on machine and 1st rotate the tool or the workpiece;
			\Sample 1: for Head-Head-Table, 3rd on head, 2nd on head under 3rd, 1st rotate the table and fixed on machine;
			\Sample 2: for Head-Head-Head, 3rd rotate the tool, 2nd under 3rd, 1st under 2nd and fixed on machine;
		*/
		static const cadcam::mwPoint3d CalcAbsMachPos(
			const mw6axCSMachDef& machDef,                          //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& partPosition,	                //!< part position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
			const double& rotAngle2,                                //!< angle in Degree
		    const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw3axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,	      //!< part origin in machine coordinate system					
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition);	      //!< absolute machine position
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle defines rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw4axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,	      //!< part origin in machine coordinate system					
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	      //!< absolute machine position
			const double& rotAngle);					  //!< angle in Degree
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw5axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,	      //!< part origin in machine coordinate system					
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	      //!< absolute machine position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw6axMachDef& machDef,                  //!< machine definition
			const cadcam::mwVector3d& partOrigin,	      //!< part origin in machine coordinate system					
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	      //!< absolute machine position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines 6axis contour machine definition
			\param partOrigin defines 3D translation used in workpiece coordinate system
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param rotAngle2 defines third rotary axis value in degree
			\returns absolute coordinate in machine coordinate system
			\Rotation axis order should be: 3rd under 2nd and 2nd under 1st; 3rd is fixed on machine and 1st rotate the tool or the workpiece;
			\Sample 1: for Head-Head-Table, 3rd on head, 2nd on head under 3rd, 1st rotate the table and fixed on machine;
			\Sample 2: for Head-Head-Head, 3rd rotate the tool, 2nd under 3rd, 1st under 2nd and fixed on machine;
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw6axCSMachDef& machDef,                //!< machine definition
			const cadcam::mwVector3d& partOrigin,	      //!< part origin in machine coordinate system					
			const double& toolLengthCompensationValue,	  //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	      //!< absolute machine position
			const double& rotAngle0,					  //!< angle in Degree
			const double& rotAngle1,                      //!< angle in Degree
			const double& rotAngle2);                     //!< angle in Degree
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw3axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	                //!< absolute machine position
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle defines rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw4axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	                //!< absolute machine position
			const double& rotAngle,					                //!< angle in Degree
		    const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw5axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	                //!< absolute machine position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
		    const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw6axMachDef& machDef,                            //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	                //!< absolute machine position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
			const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Calculates the relative position (in workpiece coordinate system) from absolute position (in machine coordinate system)
		/*!
			\param machDef defines 6axis contour machine definition
			\param toolLengthCompensationValue defines tool length compensation (TLC)
			\param absPosition defines absolute position in machine coordinate system
			\param rotAngle0 defines first rotary axis value in degree
			\param rotAngle1 defines second rotary axis value in degree
			\param rotAngle2 defines third rotary axis value in degree
			\param transformationMatrix defines a 4x4 transformation matrix used (in workpiece coordinate system)
			\returns absolute coordinate in machine coordinate system
			\Rotation axis order should be: 3rd under 2nd and 2nd under 1st; 3rd is fixed on machine and 1st rotate the tool or the workpiece;
			\Sample 1: for Head-Head-Table, 3rd on head, 2nd on head under 3rd, 1st rotate the table and fixed on machine;
			\Sample 2: for Head-Head-Head, 3rd rotate the tool, 2nd under 3rd, 1st under 2nd and fixed on machine;
		*/
		static const cadcam::mwPoint3d CalRelMachPos(
			const mw6axCSMachDef& machDef,                          //!< machine definition
			const double& toolLengthCompensationValue,	            //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d& absPosition,	                //!< absolute machine position
			const double& rotAngle0,					            //!< angle in Degree
			const double& rotAngle1,                                //!< angle in Degree
			const double& rotAngle2,                                //!< angle in Degree
		    const mwMatrix4dPtr& transformationMatrix = MW_NULL);	//!< transformation matrix (rotation + translation)	
		//#############################################################################
		//! Compute tool direction vector
		/*!
			\param machDef contains machine definition
			\returns tool direction vector
		*/
		static const cadcam::mwVector3d CalcOrient(
			const mw3axMachDef& machDef);                 //!< machine definition
		//#############################################################################
		//! Compute tool direction vector
		/*!
			\param machDef contains machine definition
			\param rotAngle defines rotary axis value in radians
			\returns tool direction vector
		*/
		static const cadcam::mwVector3d CalcOrient(
			const mw4axMachDef& machDef,                  //!< machine definition
			const double& rotAngle);					  //!< angle in Radians
		//#############################################################################
		//! Compute tool direction vector
		/*!
			\param machDef contains machine definition
			\param rotAngle0 defines first rotary axis value in radians
			\param rotAngle1 defines second rotary axis value in radians
			\returns tool direction vector
		*/
		static const cadcam::mwVector3d CalcOrient(
			const mw5axMachDef& machDef,                  //!< machine definition
			const double& rotAngle0,					  //!< angle in Radians
			const double& rotAngle1);    				  //!< angle in Radians
		//#############################################################################
		//! Compute tool direction vector
		/*!
			\param machDef contains machine definition
			\param rotAngle0 defines first rotary axis value in radians
			\param rotAngle1 defines second rotary axis value in radians
			\param rotAngle2 defines third rotary axis value in radians
			\returns tool direction vector
		*/
		static const cadcam::mwVector3d CalcOrient(
			const mw6axCSMachDef& machDef,                  //!< machine definition
			const double& rotAngle0,					  //!< angle in Radians
			const double& rotAngle1,                      //!< angle in Radians
			const double& rotAngle2);    				  //!< angle in Radians
		//#############################################################################
		//! Compute tool contour cutting direction vector
		/*!
			\param machDef contains 6axis contour machine definition
			\param rotAngle0 defines first rotary axis value in radians
			\param rotAngle1 defines second rotary axis value in radians
			\param rotAngle2 defines third rotary axis value in radians
			\returns  tool contour cutting direction vector
		*/
		static const cadcam::mwVector3d CalcSaw(
			const mw6axCSMachDef& machDef,                  //!< machine definition
			const double& rotAngle0,					  //!< angle in Radians
			const double& rotAngle1,                      //!< angle in Radians
			const double& rotAngle2);    				  //!< angle in Radians
		//#############################################################################
		//! Invert rotary axis direction if is mounting on HEAD
		static void SetRotAxisDir(
			const mw4axMachDef& machDef,                  //!< machine definition
			cadcam::mwVector3d& rotAxisDir);              //!< rotational axis (vector)
		//#############################################################################
		//! Invert rotary axis direction if is mounting on HEAD
		static void SetRotAxisDir(
			const mw5axMachDef& machDef,                  //!< machine definition
			cadcam::mwVector3d& rotAxisDir0,              //!< first rotational axis (vector)
			cadcam::mwVector3d& rotAxisDir1);             //!< second rotational axis (vector)
		//#############################################################################
		//! Invert rotary axis direction if is mounting on HEAD
		static void SetRotAxisDir(
			const mw6axMachDef& machDef,                  //!< machine definition
			cadcam::mwVector3d& rotAxisDir0,              //!< first rotational axis (vector)
			cadcam::mwVector3d& rotAxisDir1);             //!< second rotational axis (vector)
		//#############################################################################
		//! Invert rotary axis direction if is mounting on HEAD
		static void SetRotAxisDir(
			const mw6axCSMachDef& machDef,                  //!< machine definition
			cadcam::mwVector3d& rotAxisDir0,              //!< first rotational axis (vector)
			cadcam::mwVector3d& rotAxisDir1,              //!< second rotational axis (vector)
			cadcam::mwVector3d& rotAxisDir2);             //!< second rotational axis (vector)
		//#############################################################################
		//! The RotatePoint function
		/*! This function rotates a given point P, around vector a, at base point S an angle of alpha in radians the result is returned
			\param P Given point to rotate
			\param a vector 
			\param S base point
			\param  alpha an angle of alpha in radians 
			\return the result
		*/
		static const cadcam::mwPoint3d RotatePoint( 
			const cadcam::mwPoint3d& P,		
			const cadcam::mwVector3d& a,
			const cadcam::mwPoint3d& S,
			const double alpha,
			bool noTolerance = false);
		//#############################################################################
	private:
		//#############################################################################
		/*! Private method
		*/
		mwTransformation(){};
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 3 axis machine 
		/*! Given is the desired surface position on the part as X,Y,Z and 
			\return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordFor3axMach( 
			const cadcam::mwPoint3d& partPos,		      //!< position on the part
			const cadcam::mwPoint3d& partOrigin,		  //!< part origin in machine coordinate system
			const cadcam::mwVector3d& spindle,	   	      //!< spindle direction vector
			const double& toolLen,	                      //!< length of tool up to the position of rotation axis
			const cadcam::mwPoint3d&);	                  //!< holder transformation (for turning machine) 		                  
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 4 axis machine 
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordTableFor4axMach( 
			const cadcam::mwPoint3d& partPos,		      //!< position on the part
			const cadcam::mwPoint3d& partOrigin,		  //!< part origin in machine coordinate system
			const cadcam::mwVector3d& spindle,	   	      //!< spindle direction vector
			const cadcam::mwVector3d& rotAxisVector,	  //!< rotational axis (vector)
			const cadcam::mwPoint3d& basePointDis,	      //!< rotation base point 
			const double& toolLen,				          //!< length of tool up to the position of rotation axis
			const double& angle,		                  //!< Angle in Radians 
			const cadcam::mwPoint3d&);	                  //!< holder transformation (for turning machine) 		                  
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 4 axis machine 
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordHeadFor4axMach( 
			const cadcam::mwPoint3d& partPos,		      //!< position on the part
			const cadcam::mwPoint3d& partOrigin,		  //!< part origin in machine coordinate system
			const cadcam::mwVector3d& spindle,	   	      //!< spindle direction vector
			const cadcam::mwVector3d& rotAxisVector,	  //!< rotational axis (vector)
			const cadcam::mwPoint3d& basePointDis,	      //!< rotation base point 
			const double& toolLen,				          //!< length of tool up to the position of rotation axis
			const double& angle,		                  //!< Angle in Radians 
			const cadcam::mwPoint3d&);	                  //!< holder transformation (for turning machine) 		                  
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 5 axis machine with both axis in head
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordBothAxisInHeadFor5axMach( 
			const cadcam::mwPoint3d&,		              //!< position on the part
			const cadcam::mwPoint3d&,		              //!< part origin in machine coordinate system
			const cadcam::mwVector3d&,		              //!< spindle direction vector
			const cadcam::mwVector3d&,	                  //!< first rotational axis (vector)
			const cadcam::mwVector3d&,	                  //!< second rotational axis (vector)
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the first axis
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the second axis 
			const double&,				                  //!< length of tool up to the position of rotation axis
			const double&,		                          //!< Angle in Radians (Rotation axis 1) crot		
			const double&,                                //!< Angle in Radians (Rotation axis 2) brot	
			const cadcam::mwPoint3d&,                     //!< holder transformation (for turning machine) 		                   
			bool noTolerance);	                 
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 5 axis machine with both axis in table legacy
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordBothAxisInTableLegacyFor5axMach( 
			const cadcam::mwPoint3d&,		              //!< position on the part
			const cadcam::mwPoint3d&,		              //!< part origin in machine coordinate system
			const cadcam::mwVector3d&,		              //!< spindle direction vector
			const cadcam::mwVector3d&,	                  //!< first rotational axis (vector)
			const cadcam::mwVector3d&,	                  //!< second rotational axis (vector)
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the first axis
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the second axis 
			const double&,				                  //!< length of tool up to the position of rotation axis
			const double&,		                          //!< Angle in Radians (Rotation axis 1) crot		
			const double&,                                //!< Angle in Radians (Rotation axis 2) brot	
			const cadcam::mwPoint3d&,                     //!< holder transformation (for turning machine)
			bool noTolerance);         
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 5 axis machine with both axis in table new
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordBothAxisInTableNewFor5axMach( 
			const cadcam::mwPoint3d&,		              //!< position on the part
			const cadcam::mwPoint3d&,		              //!< part origin in machine coordinate system
			const cadcam::mwVector3d&,	   	              //!< spindle direction vector
			const cadcam::mwVector3d&,	                  //!< first rotational axis (vector)
			const cadcam::mwVector3d&,	                  //!< second rotational axis (vector)
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the first axis
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the second axis 
			const double&,				                  //!< length of tool up to the position of rotation axis
			const double&,		                          //!< Angle in Radians (Rotation axis 1) crot		
			const double&,                                //!< Angle in Radians (Rotation axis 2) brot
			const cadcam::mwPoint3d&,                     //!< holder transformation (for turning machine)                    
			bool noTolerance);		              
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 5 axis machine with both axis in table
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordBothAxisInTableCommonFor5axMach( 
			const cadcam::mwPoint3d&,		              //!< position on the part
			const cadcam::mwPoint3d&,		              //!< part origin in machine coordinate system
			const cadcam::mwVector3d&,		              //!< spindle direction vector
			const cadcam::mwVector3d&,	                  //!< first rotational axis (vector)
			const cadcam::mwVector3d&,	                  //!< second rotational axis (vector)
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the first axis
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the second axis 
			const double&,				                  //!< length of tool up to the position of rotation axis
			const double&,		                          //!< Angle in Radians (Rotation axis 1) crot		
			const double&,                                //!< Angle in Radians (Rotation axis 2) brot		
			const cadcam::mwPoint3d&,                     //!< holder transformation (for turning machine)                    	                  
			bool noTolerance);	                  
		//#############################################################################
		//! Private method, this function calculates the absolute position X,Y,Z of a 5 axis machine with one rotary axis at head and the other in table
		/*! Given is the desired surface position on the part as X,Y,Z and 
			@return absolute machine position
		*/
		static const cadcam::mwPoint3d CalcAbsCoordHeadTableFor5axMach( 
			const cadcam::mwPoint3d&,		              //!< position on the part
			const cadcam::mwPoint3d&,		              //!< part origin in machine coordinate system
			const cadcam::mwVector3d&,		              //!< spindle direction vector
			const cadcam::mwVector3d&,	                  //!< first rotational axis (vector)
			const cadcam::mwVector3d&,	                  //!< second rotational axis (vector)
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the first axis
			const cadcam::mwPoint3d&,	                  //!< rotation base point of the second axis 
			const double&,				                  //!< length of tool up to the position of rotation axis
			const double&,		                          //!< Angle in Radians (Rotation axis 1) crot		
			const double&,                                //!< Angle in Radians (Rotation axis 2) brot
			const cadcam::mwPoint3d&,                     //!< holder transformation (for turning machine)                    	                                   
			bool noTolerance);                    
		//#############################################################################
		/*! Private method
		*/
		static const cadcam::mwPoint3d GetToolTranf(const mwMachDef& machDef);
		//#############################################################################
	};
	//#############################################################################
};
#endif	//	MW_MWTRANSFORMATION_HPP_
