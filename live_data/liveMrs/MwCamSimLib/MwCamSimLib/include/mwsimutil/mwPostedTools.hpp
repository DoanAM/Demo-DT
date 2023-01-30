// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWPOSTEDTOOLS_HPP_
#define MW_MWPOSTEDTOOLS_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include <mwTPoint3d.hpp>
#include "mwPosted5axMove.hpp"
#include "mwPosted6axMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mw3axMachDef;
	class mw4axMachDef;
	class mw5axMachDef;
	class mw6axCSMachDef;
	class mwPosted3axMove;
	class mwPosted4axMove;
	//#############################################################################
	//! this class provides some posted tools
	class MW_5AXUTIL_API mwPostedTools
	{
	public:
		//#############################################################################
		//! Get the retracted move
		/*! Get the retracted move, from a given move, so that the distance is retractDistForLargeAngChange.
		*/
		static const mwPosted3axMove GetRetractedMove(
			const mw3axMachDef& machDef,                     //!< The machine definition
			const cadcam::mwVector3d& partOrigin,		     //!< part origin in machine coordinate system			
			const double toolLengthCompensationValue,	     //!< Length of tool up to the position of rotation axis
			const mwPosted3axMove& move, 
			const double retractDistForLargeAngChange,
			const double rate = 0);
		//#############################################################################
		//! Get the retracted move
		/*! Get the retracted move, from a given move, so that the distance is retractDistForLargeAngChange.
		*/
		static const mwPosted4axMove GetRetractedMove(
			const mw4axMachDef& machDef,                     //!< The machine definition
			const cadcam::mwVector3d& partOrigin,		     //!< part origin in machine coordinate system			
			const double toolLengthCompensationValue,	     //!< Length of tool up to the position of rotation axis
			const mwPosted4axMove& move, 
			const double retractDistForLargeAngChange,
			const double rate = 0);
		//#############################################################################
		//! Get the retracted move
		/*! Get the retracted move, from a given move, so that the distance is retractDistForLargeAngChange.
		*/
		static const mwPosted5axMove GetRetractedMove(
			const mw5axMachDef& machDef,                     //!< The machine definition
			const cadcam::mwVector3d& partOrigin,		     //!< part origin in machine coordinate system			
			const double toolLengthCompensationValue,	     //!< Length of tool up to the position of rotation axis
			const mwPosted5axMove& move, 
			const double retractDistForLargeAngChange,
			const double rate = 0);
		//#############################################################################
		static const mwPosted6axMove GetRetractedMove(
			const mw6axCSMachDef& machDef,             //!< The machine definition
			const cadcam::mwVector3d& partOrigin,		//!< part origin in machine coordinate system			
			const double toolLengthCompensationValue,	//!< Length of tool up to the position of rotation axis
			const mwPosted6axMove& move, 
			const double retractDistForLargeAngChange,
			const double rate = 0);
		//#############################################################################
		//! Calculates the angle
		static double AngleCalc(
		const mw4axMachDef& machDef,                      //!< The machine definition 
		const cadcam::mwVector3d& moveOrient,		      //!< The orientation of move
		const double toolpathTol);		      
		//#############################################################################
		//! Calculates the angle
		static void AngleCalc(
			const mw5axMachDef& machDef,                      //!< The machine definition 
			const cadcam::mwVector3d& moveOrient,		      //!< The orientation of move
			double& first_angle0,							  //!< Angle in degrees C2		(second angle tuple)
			double& first_angle1,							  //!< Angle in degrees B2		(second angle tuple)
			double& second_angle0,							  //!< Angle in degrees C1		(first angle tuple)
			double& second_angle1,							  //!< Angle in degrees B1		(first angle tuple)
			mwPosted5axMove::anglesState& angsState,          //!< State of angles
			const double poleAngleDetectToolInDeg,            //!< The pole angle tolerance in degrees	
			const double toolpathTol,
			const bool smartSelect = false);		  
		//#############################################################################
		static mwPosted5axMove::anglesState ComputeAngleState(
			const mw5axMachDef& machDef,                      //!< The machine definition 
			const cadcam::mwVector3d& moveOrient,		      //!< The orientation of move
			const double poleAngleDetectToolInDeg,            //!< The pole angle tolerance in degrees	
			const double toolpathTol);
		//#############################################################################
		static void SetAngleBetween0And360(double& angle);
		//#############################################################################
		static const double TransformToleranceToAngleInDeg(const double tolerance);
		//#############################################################################
		static const long double ExtraCubicK(const double k, const double angle);
		//#############################################################################
		//#############################################################################
		//! the mw_acos function
		/*! Calculates the acos of a given value, and if the value is less than -1 or greater than +1, the returned angle is considered to be 0
			\param value the given value
			\return the corresponding angle
		*/
		static const double mw_acos(const double value);
		static const double mw_acos2(const double value);
		//#############################################################################
		//! Calculates the angle
		static void AngleCalc(
			const cadcam::mwVector3d& spindle, 		          //!< Spindle direction vector
			const cadcam::mwVector3d& orientation,			  //!< Move orientation vector
			const cadcam::mwVector3d& firstAxisDir,		      //!< Machine first rotation axis direction (vector)
			const cadcam::mwVector3d& secondAxisDir,		  //!< Machine second rotation axis direction (vector)
			double &first_angle0,							  //!< Angle in radians C2		(second angle tuple)
			double &first_angle1,							  //!< Angle in radians B2		(second angle tuple)
			double &second_angle0,							  //!< Angle in radians C1		(first angle tuple)
			double &second_angle1,							  //!< Angle in radians B1		(first angle tuple)
			mwPosted5axMove::anglesState& angsState,          //!< State of angles
			const double poleAngleDetectToolInDeg,            //!< The pole angle tolerance in degrees
			const double toolpathTol,                         //!< The orientation tolerance 
			bool noTolerance = false);                        
		//#############################################################################
		static void AngleCalc(
			const mw6axCSMachDef& machDef,                   
			const cadcam::mwVector3d& moveOrient,
			const cadcam::mwVector3d& sawOrientation,
			double& solution1_angle0,
			double& solution1_angle1,
			double& solution1_angle2,
			double& solution2_angle0,
			double& solution2_angle1,
			double& solution2_angle2,
			mwPosted6axMove::anglesState& angsState,         
			const bool smartSelect,
			const double toolpathTol);
		//#############################################################################
	private:	
		//#############################################################################
		//! default constructor
		mwPostedTools(){}; // static class
		//! Calculates the angle
		static double AngleCalc(
			const cadcam::mwVector3d& spindle, 		          //!< Spindle direction vector
			const cadcam::mwVector3d& orinetation,			  //!< Move orientation vector
			const cadcam::mwVector3d& direction,			  //!< Machine rotation axis direction (vector)
			const double toolpathTol);          
		//#############################################################################
		static const bool AngleCalc(
			const mw6axCSMachDef& machDef,                   
			const cadcam::mwVector3d& axis0,
			const cadcam::mwVector3d& axis1, 
			const cadcam::mwVector3d& axis2, 
			const cadcam::mwVector3d& orientation,
			const cadcam::mwVector3d& saw, 
			double& angle0,
			double& angle1,
			double& angle2,
			const double toolpathTol);
		//#############################################################################
	};// end class mwPostedTools
	//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWPOSTEDTOOLS_HPP_
