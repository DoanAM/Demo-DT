// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWMXPPARAM_HPP_
#define MW_MWMXPPARAM_HPP_
//#############################################################################
/*
	MultiXPost post processor uses Post Parameters in order to generate posted - toolpath.
	The corresponding API for all parameters is post::mwMXPParam class, exported by MultiXPost.dll.
	There is an user interface(UI) available in MPSEditor.exe and Sampleintegration.exe which corresponds to Post Parameters.
*/
#include <vector>
#include <mwTPoint3d.hpp>
#include "mwUnitsFactory.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"
#include "mwTPoint3d.hpp"
#include "mwRobMXPParams.hpp"
//#############################################################################
namespace post
{
	class MW_5AXUTIL_API mwMXPParam : public measures::mwMeasurable
	{
	public:
		//#############################################################################
		typedef enum measures::mwUnitsFactory::Units	Units;
		//#############################################################################
		typedef misc::mwAutoPointer<mwRobMXPParams> mwRoboticMXPParamPtr;
		enum StartAngleType
		{
			ANGTYPE_SEL_BETW_TWO_SOLUTIONS = 0,
			ANGTYPE_USE_FIRST_ROT_ANGLE,
			ANGTYPE_USE_SECOND_ROT_ANGLE,
			TRANSTYPE_PROVIDE_AXIS,
			ANGTYPE_USE_THIRD_ROT_ANGLE
		};
		//#############################################################################
		enum SolutionForStartTranslation
		{
			SST_USE_FIRST_POSITIVE = 0,
			SST_USE_FIRST_NEGATIVE,
			SST_USE_SECOND_POSITIVE,
			SST_USE_SECOND_NEGATIVE,
			SST_USE_THIRD_POSITIVE,
			SST_USE_THIRD_NEGATIVE,
			SST_USE_CUSTOM
		};
		//#############################################################################
		enum MachineLimits 
		{
			NO_LIMITS = 0, // No limit
			TRANSLATIONAL_LIMITS, // Translation limits
			ROTATIONAL_LIMITS, // Rotation limits
			ALL_LIMITS // Translation + Rotation limits
		};
		//#############################################################################
		enum SolutionForStartAngle
		{
			SSA_USE_FIRST_SOLUTION = 0,
			SSA_USE_OTHER_SOLUTION

		};
		//#############################################################################
		enum PoleHandling
		{
			FREEZE_ANGLE_AROUND_POLE = 0,//"Freeze angle around pole" (old behaivour) 
			USE_ROTATION_ANGLE_AROUND_POLE,//"Use rotation angle around pole to stay within linear axis limits" (avoid limits using rotation) 
			LINEAR_INTERPOLATION,//"Linear interpolation of rotation angle around pole" (linear blend) 
			SMOOTH_INTERPOLATION,//"Smooth interpolation of rotation angle around pole" (cubic blend).
			FORCE_HEAD_AND_TABLE_ROTATION,//Force Head and Table rotation.
			FIND_HEAD_OR_TABLE_FIX_POSITION // Find Head or Table fix position to stay in machine limits
		};
		//#############################################################################
		enum Interpolation
		{
			INTERPOLATION_VECTORS = 0, 
			INTERPOLATION_ANGLES, //// RTCP ON
			INTERPOLATION_AXIS_VALUES //// RTCP OFF
		};
		//#############################################################################
		//! Constructor 
		/*  will set post parameter to default settings:
			SetAngleSelectAutoFrom2Pairs(true);
			SetAngleSelectOtherPair(false);

			SetAngleChangeLimit( 120. );

			SetInterpolationStep( 3. );
			SetRapidRateInterpolationStep( 10. );
			SetInterpolationDist( GetUnits() == measures::mwUnitsFactory::METRIC ? 2.5 : 0.1);
			SetRapidRateInterpolationDist( GetUnits() == measures::mwUnitsFactory::METRIC ? 2.5 : 0.1);

			SetInterpolationDistFlag( true );//for distance
			SetRapidRateInterpolationDistFlag( true );
			SetInterpolationStepFlag( true );//for angle
			SetRapidRateInterpolationStepFlag( false );

			SetPoleAngleTolInDeg( 0.01 );
			SetAngleTolInDegForUsingMachLimits( 0.0001 );
			SetMachineLimits(NO_LIMITS);

			SetStartAngleType(mwMXPParam::ANGTYPE_SEL_BETW_TWO_SOLUTIONS);
			SetSolutionForStartAngle(mwMXPParam::SSA_USE_FIRST_SOLUTION);
			SetPreferredStartAngleValInDeg(0.0);
			SetStartRotationAngle(false);
			SetSolutionChangeForMinRetractsAndRewinds(false);

			SetPoleHandling(mwMXPParam::SMOOTH_INTERPOLATION);

			SetToolpathAlignment(false);

			SetInterpolation(INTERPOLATION_VECTORS);


			SetToolpathTolerance(1e-10);

			SetFirstSolutionCloserTo0Degree(true);

			SetFilterDuplicateMoves(true);

			SetSolutionForStartTranslation(mwMXPParam::SST_USE_FIRST_POSITIVE);

			SetLimitLinearAxisTravel(true);
			SetAvoidRotationAxisDirectionChange(false);

			SetCustomTransAxisDirValues(cadcam::mwPoint3d(1.0, 0.0, 0.0));

			SetRetractAndRewindFlag(true);
			SetRetractToolAtMax(false);
			SetAdditionalRetractFlag(false);
			SetAdditionalRetractToolAtMax(true);
			SetRetractAndRewindAngleFlag(true);
			SetRetractDistForLargeAngChange(GetUnits() == measures::mwUnitsFactory::METRIC ? 100 : 4);
			SetAdditionalRetractDistForLargeAngChange(GetUnits() == measures::mwUnitsFactory::METRIC ? 100 : 4);
			SetRetractAndRewindAngleStep(10.0);
			SetAdditionalRetractDirection(cadcam::mwPoint3d(1.0, 0.0, 0.0));

			EnableFilterArcsAndHelices(false);
			SetFilterMaxSweepAngle(mathdef::MW_MAX_DOUBLE);
			SetFilterHelices(true);
			SetFilterArcs(true);
			SetFilterWithMaxSplitSweepAngle(false);
			SetFilterUsingArcPlanes(false);
			SetFilterArcPlaneNormals(std::vector<cadcam::mwPoint3d>());

			SetSmoothLeadOutAndIn(false);
			SetRapidExitDist(10);
			SetFeedEntryDist(10);

		*/
		mwMXPParam(const Units units);
		//#############################################################################
		//! Copy constructor
		mwMXPParam(const mwMXPParam& toCopy);
		//#############################################################################
		//! Copy operator
		const mwMXPParam& operator = (const mwMXPParam &toCopy);
		//#############################################################################
		//! Comparison operator
		/* Compares two objects
			\return true it the compared objects are equal member by member,
			\false otherwise
		*/
		const bool operator == (const mwMXPParam& toCompare) const;
		//#############################################################################
		//! Set all parameters to default settings, as constructor does
		void Default();
		//#############################################################################
		//! Gets Auto Angle Pair
		/*!
			This parameter is the auto angle pair selection flag of the post processor. 
			A 5-axis vector can be mapped into two different angle pairs. 
			If this flag is ON, post processor should determine automatically which pair of angle to use. 
			In this case, the post processor will select the angle pair that will not create a very large angle change from previous posted position 
			(if both solutions are in machine limits or post processor will not use machine limits). 
			Some machines can only use one of the angle pairs due to mechanical limitations: in such case, this flag must be ON and post processor will select a solutions that are in machine limits.
			If Auto Angle Pair is turned ON, then, selection of the very first angle pair is based on Solution for start angle parameter and/or First solution closer to 0 degree parameter and/or Preferred start angle type paremeter and/or Machine limits parameter as you can see next. After the first move, all subsequent angle pair selections will be performed by the auto selection. 
			This parameter si used only after first move.
		*/
		const bool GetAngleSelectAutoFrom2Pairs() const;
		//#############################################################################
		//! Sets Auto Angle Pair
		/*!
			This parameter is the auto angle pair selection flag of the post processor.
			A 5-axis vector can be mapped into two different angle pairs.
			If this flag is ON, post processor should determine automatically which pair of angle to use.
			In this case, the post processor will select the angle pair that will not create a very large angle change from previous posted position
			(if both solutions are in machine limits or post processor will not use machine limits).
			Some machines can only use one of the angle pairs due to mechanical limitations: in such case, this flag must be ON and post processor will select a solutions that are in machine limits.
			If Auto Angle Pair is turned ON, then, selection of the very first angle pair is based on Solution for start angle parameter and/or First solution closer to 0 degree parameter and/or Preferred start angle type paremeter and/or Machine limits parameter as you can see next. After the first move, all subsequent angle pair selections will be performed by the auto selection.
			This parameter si used only after first move.
		*/
		void SetAngleSelectAutoFrom2Pairs(const bool angleSelAutoFrom2Pairs);
		//#############################################################################
		//! Gets First solution closer to 0 degree
		/*!
			This parameter allows the selection of one of the two solutions by 5-axis posting depending on the angles variation for first move (only). 
			In more general terms this parameter marks Solution 1 as being solution closest to 0 and Solution 2 solution that is not closest to 0. 
			This parameter is used together with Solution for start angle parameter, who enable selection of one or the other solution (Solution 1 or Solution 2). 
			It is available only when Auto Angle Pair parameter is ON.
			This parameter has effect only for 5-axis posting, when there are two possible solution to choose. 
			When this parameter is OFF there is no explanation for the user what the Solution 1 and Solution 2 means.
			It's easier to understand how it works if we follow an example:
			Let's assume there are two distinct solutions: 
			Solution A (first angle=20 degree and second angle=-15 degree) and Solution B (first angle=30 and second angle=10); 
			when First solution closer to 0 degree is ON Solution closest to 0 (or Solution 1) is Solution A, because: |20-0| + |-15-0| = 35 degree, which is smaller than |30-0| + |10-0| = 40 degree, and Solution that is not closest to 0 (or Solution 2) is Solution B.
		*/
		const bool IsFirstSolutionCloserTo0Degree() const;
		//#############################################################################
		//! Sets First solution closer to 0 degree
		/*!
			This parameter allows the selection of one of the two solutions by 5-axis posting depending on the angles variation for first move (only).
			In more general terms this parameter marks Solution 1 as being solution closest to 0 and Solution 2 solution that is not closest to 0.
			This parameter is used together with Solution for start angle parameter, who enable selection of one or the other solution (Solution 1 or Solution 2).
			It is available only when Auto Angle Pair parameter is ON.
			This parameter has effect only for 5-axis posting, when there are two possible solution to choose.
			When this parameter is OFF there is no explanation for the user what the Solution 1 and Solution 2 means.
			It's easier to understand how it works if we follow an example:
			Let's assume there are two distinct solutions:
			Solution A (first angle=20 degree and second angle=-15 degree) and Solution B (first angle=30 and second angle=10);
			when First solution closer to 0 degree is ON Solution closest to 0 (or Solution 1) is Solution A, because: |20-0| + |-15-0| = 35 degree, which is smaller than |30-0| + |10-0| = 40 degree, and Solution that is not closest to 0 (or Solution 2) is Solution B.
		*/
		void SetFirstSolutionCloserTo0Degree(const bool firstSolution0);
		//#############################################################################
		//! Gets Preferred start angle type
		/*
			This parameter has multiple roles (used by 4-axis/ 5-axis/ 6-axis post processors): to select a solution and set his value for first move (only).
			A 5-axis tool axis orientations (I,J,K) can be mapped to two solutions on a 5-axis machine tool, but not always, some times there can be an UNDETERMINED solution (first angle can be UNDETERMINED or second angle can be UNDETERMINED).
			There are 5 possible options for this parameter:
			-ANGTYPE_SEL_BETW_TWO_SOLUTIONS: is used by 5-axis processor in combination with Solution for start angle parameter enable selection of one solution.
			-ANGTYPE_USE_FIRST_ROT_ANGLE: is used by 5-axis post processor and 6-axis post processor in combination with Preferred rotation angle parameter.
			If there are two distinct solution then a solution is selected base on distance from Preferred rotation angle parameter value and first rotation angle of two solutions; the closest solution will be chosen.
			If there is first rotation angle UNDETERMINED then first rotation angle value for first move is set to Preferred rotation angle parameter value.
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
			-ANGTYPE_USE_SECOND_ROT_ANGLE: is used by 5-axis post processor and 6-axis post processor in combination with Preferred rotation angle parameter.
			If there are two distinct solution then a solution is selected base on distance from Preferred rotation angle parameter value and second rotation angle of two solutions; the closest solution will be chosen.
			If there is second rotation angle UNDETERMINED then second rotation angle value for first move is set to Preferred rotation angle parameter value.
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
			-ANGTYPE_USE_THIRD_ROT_ANGLE: is used by 6-axis post processor in combination with Preferred rotation angle parameter.
			If there are two distinct solutions then a solution is selected base on distance from Preferred rotation angle parameter value and third rotation angle of two solutions; the closest solution will be chosen.
			Third rotation angle UNDETERMINED it is not supported by post processor at this time, and third rotation angle value cannot be set with Preferred rotation angle parameter value.
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
-			ANGTYPE_USE_THIRD_ROT_ANGLE:  is is used by 4-axis, 5-axis and 6-axis Force Head or Table rotation algorithm of post processor. For more information read Pole Handling parameter.
		*/
		const StartAngleType& GetStartAngleType() const;
		//#############################################################################
		//! Sets Preferred start angle type
		/*
			This parameter has multiple roles (used by 4-axis/ 5-axis/ 6-axis post processors): to select a solution and set his value for first move (only). 
			A 5-axis tool axis orientations (I,J,K) can be mapped to two solutions on a 5-axis machine tool, but not always, some times there can be an UNDETERMINED solution (first angle can be UNDETERMINED or second angle can be UNDETERMINED).
			There are 5 possible options for this parameter:
			-ANGTYPE_SEL_BETW_TWO_SOLUTIONS: is used by 5-axis processor in combination with Solution for start angle parameter enable selection of one solution.
			-ANGTYPE_USE_FIRST_ROT_ANGLE: is used by 5-axis post processor and 6-axis post processor in combination with Preferred rotation angle parameter. 
			If there are two distinct solution then a solution is selected base on distance from Preferred rotation angle parameter value and first rotation angle of two solutions; the closest solution will be chosen. 
			If there is first rotation angle UNDETERMINED then first rotation angle value for first move is set to Preferred rotation angle parameter value. 
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
			-ANGTYPE_USE_SECOND_ROT_ANGLE: is used by 5-axis post processor and 6-axis post processor in combination with Preferred rotation angle parameter. 
			If there are two distinct solution then a solution is selected base on distance from Preferred rotation angle parameter value and second rotation angle of two solutions; the closest solution will be chosen. 
			If there is second rotation angle UNDETERMINED then second rotation angle value for first move is set to Preferred rotation angle parameter value. 
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
			-ANGTYPE_USE_THIRD_ROT_ANGLE: is used by 6-axis post processor in combination with Preferred rotation angle parameter. 
			If there are two distinct solutions then a solution is selected base on distance from Preferred rotation angle parameter value and third rotation angle of two solutions; the closest solution will be chosen. 
			Third rotation angle UNDETERMINED it is not supported by post processor at this time, and third rotation angle value cannot be set with Preferred rotation angle parameter value. 
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
-			ANGTYPE_USE_THIRD_ROT_ANGLE:  is is used by 4-axis, 5-axis and 6-axis Force Head or Table rotation algorithm of post processor. For more information read Pole Handling parameter.
		*/
		void SetStartAngleType(const  StartAngleType& startAngleType);
		//#############################################################################
		//! Gets Other Angle Pair
		/*!
			This parameter is used by 5-axis post processor. 
			It si used only when Auto Angle Pair parameter is OFF and enable selection of one solution or the other solution (Solution 1/Solution 2) for all moves,
			but if post processor uses machine limits and solution selected is out of machine limits then the other solution is used. 
			When Auto Angle Pair parameter is OFF there is no explanation for the user what the first (Solution 1) and other solution (Solution 2) means, both solutions should be tried and chosen the most appropriate; 
			to eliminate trial-and-error there is available First solution closer to 0 degree parameter.
			Other angle pair parameter  enable selection of first solution (Solution 1) when it is OFF and selection of second solution (Solution 2) when it is ON.
		*/
		const bool GetAngleSelectOtherPair() const;
		//#############################################################################
		//! Sets Other Angle Pair
		/*!
			This parameter is used by 5-axis post processor.
			It si used only when Auto Angle Pair parameter is OFF and enable selection of one solution or the other solution (Solution 1/Solution 2) for all moves,
			but if post processor uses machine limits and solution selected is out of machine limits then the other solution is used.
			When Auto Angle Pair parameter is OFF there is no explanation for the user what the first (Solution 1) and other solution (Solution 2) means, both solutions should be tried and chosen the most appropriate;
			to eliminate trial-and-error there is available First solution closer to 0 degree parameter.
			Other angle pair parameter  enable selection of first solution (Solution 1) when it is OFF and selection of second solution (Solution 2) when it is ON.
		*/
		void SetAngleSelectOtherPair(const bool angleSelOtherPair);
		//#############################################################################
		//! Gets Solution for start angle
		/*
			Used by 5-axis post processor to select a solution for first move only when Auto Angle Pair parameter is ON and Preferred start angle type parameter is ANGTYPE_SEL_BETW_TWO_SOLUTIONS. 
			The user has the possibility to specify the solution for start angle among two (mathematical) possible solutions (the two solutions are called Solution 1 and Solution 2). 
			Due to machine limits, both solutions might not be available at all, then the user will not be able to select among two possible start angles. 
			This parameter lets the users to decide what solution to be used for first move (only). 
			If First solution closer to 0 degree parameter is OFF and Preferred start angle type parameter is ANGTYPE_SEL_BETW_TWO_SOLUTIONS, then there is no explanation for the user what the first and other solution means, 
			values returned by post processor are base on machine specific kinematics and move orientation, selection between them is hard-coded in post processor. 
			To get the appropriate solution that the user wishes, both solutions should be tried. 
			To avoid try and fail use Preferred start angle type parameter or First solution closer to 0 degree parameter.
			SSA_USE_FIRST_SOLUTION corresponds to  Solution 1 and SSA_USE_OTHER_SOLUTION corresponds to Solution 2.
		*/
		const SolutionForStartAngle& GetSolutionForStartAngle() const;
		//#############################################################################
		//! Sets Solution for start angle
		/*
			Used by 5-axis post processor to select a solution for first move only when Auto Angle Pair parameter is ON and Preferred start angle type parameter is ANGTYPE_SEL_BETW_TWO_SOLUTIONS.
			The user has the possibility to specify the solution for start angle among two (mathematical) possible solutions (the two solutions are called Solution 1 and Solution 2).
			Due to machine limits, both solutions might not be available at all, then the user will not be able to select among two possible start angles.
			This parameter lets the users to decide what solution to be used for first move (only).
			If First solution closer to 0 degree parameter is OFF and Preferred start angle type parameter is ANGTYPE_SEL_BETW_TWO_SOLUTIONS, then there is no explanation for the user what the first and other solution means,
			values returned by post processor are base on machine specific kinematics and move orientation, selection between them is hard-coded in post processor.
			To get the appropriate solution that the user wishes, both solutions should be tried.
			To avoid try and fail use Preferred start angle type parameter or First solution closer to 0 degree parameter.
			SSA_USE_FIRST_SOLUTION corresponds to  Solution 1 and SSA_USE_OTHER_SOLUTION corresponds to Solution 2.
		*/
		void SetSolutionForStartAngle(const SolutionForStartAngle& solution);
		//#############################################################################
		//! Gets Preferred rotation angle
		/*
			As described for preferred start angle type, the user can specify the desired start angle by different methods. 
			The user can set the preferred start angle type, for e.g. with ANGTYPE_USE_FIRST_ROT_ANGLE and then provide with rotation angle value like 90 degree. 
			This means post processor will take from two possible solutions the closest solution 
			(for e.g. assume C rotation axis solutions are -80 and 80, if user set as input 90 degree, then, solution 80 is selected because 80 is closer to 90, in unit circle).
			Any value positive or negative is accepted; note that the closest angle in unit circle is used. E.g. 
			if user specifies -270 here (in angle in unit circle -270 = 90 - 360), and possible solutions are -80 and 80, then, post processor will take 80 since -270 is closer to 80 in unit circle.
			In case all moves in the toolpath contains UNDETERMINED angles, value used as input will change all angles for all moves; 
			if there are two distinct solutions (DETERMINED) this parameter is used to select a solution base on angle variation; 
			if there is one move DETERMINED then all previous UNDTERMINED angles will be equal with first DETERMINED angle value.
		*/
		const double GetPreferredStartAngleValInDeg() const;
		//#############################################################################
		//! Sets Preferred rotation angle
		/*
			As described for preferred start angle type, the user can specify the desired start angle by different methods.
			The user can set the preferred start angle type, for e.g. with ANGTYPE_USE_FIRST_ROT_ANGLE and then provide with rotation angle value like 90 degree.
			This means post processor will take from two possible solutions the closest solution
			(for e.g. assume C rotation axis solutions are -80 and 80, if user set as input 90 degree, then, solution 80 is selected because 80 is closer to 90, in unit circle).
			Any value positive or negative is accepted; note that the closest angle in unit circle is used. E.g.
			if user specifies -270 here (in angle in unit circle -270 = 90 - 360), and possible solutions are -80 and 80, then, post processor will take 80 since -270 is closer to 80 in unit circle.
			In case all moves in the toolpath contains UNDETERMINED angles, value used as input will change all angles for all moves;
			if there are two distinct solutions (DETERMINED) this parameter is used to select a solution base on angle variation;
			if there is one move DETERMINED then all previous UNDTERMINED angles will be equal with first DETERMINED angle value.
		*/
		void SetPreferredStartAngleValInDeg(const double angleValue);
		//#############################################################################
		//! Gets Start Rotation Angle
		/*!
			This parameter is available only for 4-axis post processor. 
			It work in combination with Preferred rotation angle parameter. 
			In cases when angle is UNDETERMINED, for e.g. when the Tool is parallel with move orientation, this parameter it makes it possible for a value to be set for angle in combination with Preferred rotation angle parameter value. 
			Force Head and Table rotation algorithm also uses Preferred rotation angle parameter and Start Rotation Angle parameter. 
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
		*/
		const bool GetStartRotationAngle() const;
		//#############################################################################
		//! Sets Start Rotation Angle
		/*!
			This parameter is available only for 4-axis post processor.
			It work in combination with Preferred rotation angle parameter.
			In cases when angle is UNDETERMINED, for e.g. when the Tool is parallel with move orientation, this parameter it makes it possible for a value to be set for angle in combination with Preferred rotation angle parameter value.
			Force Head and Table rotation algorithm also uses Preferred rotation angle parameter and Start Rotation Angle parameter.
			When angle is not UNDETERMINED a rewind can be applied to the angle (for e.g. if the angle is 1.0 degree and Preferred rotation angle parameter value is 512.0 degree, then, the angle will be changed to 361.0, a plus 360.0 degree rewind is applied).
		*/
		void SetStartRotationAngle(const bool provideRotationAngle);
		//#############################################################################
		//! Gets Solution for start translation axis
		/*!
			This parameter is used by 4-axis/ 5-axis/ 6-axis post processor - Force Head and Table rotation algorithm in order choose a translation solution from the 6 possible solutions (1st Linear Axis positive, 1st Linear Axis negative, 2nd Linear Axis positive, 2nd Linear Axis negative, 3rd Linear Axis positive and 3rd Linear Axis negative). 
			These 6 cases are translation axes returned by post processor and not to axis directions or axis names (e.g. first translation axis can be (0,-1,0) and named "Z").  
			If the solution selected can not be used (due to machine limits etc.), then other solution is used: this is done automatically, it is hard-coded in post processor.
			This parameter block a translation axis when Force Head and Table rotation algorithm is used. 
			Force Head and Table rotation algorithm uses rotation of the Table axis or rotation of the Head axis and block one translation axis when there is a case of UNDETERMINED angle and any possible value for that angle will not change Tool direction
		*/
		const SolutionForStartTranslation& GetSolutionForStartTranslation() const;
		//#############################################################################
		//! Sets Solution for start translation axis
		/*!
			This parameter is used by 4-axis/ 5-axis/ 6-axis post processor - Force Head and Table rotation algorithm in order choose a translation solution from the 6 possible solutions (1st Linear Axis positive, 1st Linear Axis negative, 2nd Linear Axis positive, 2nd Linear Axis negative, 3rd Linear Axis positive and 3rd Linear Axis negative).
			These 6 cases are translation axes returned by post processor and not to axis directions or axis names (e.g. first translation axis can be (0,-1,0) and named "Z").
			If the solution selected can not be used (due to machine limits etc.), then other solution is used: this is done automatically, it is hard-coded in post processor.
			This parameter block a translation axis when Force Head and Table rotation algorithm is used.
			Force Head and Table rotation algorithm uses rotation of the Table axis or rotation of the Head axis and block one translation axis when there is a case of UNDETERMINED angle and any possible value for that angle will not change Tool direction
		*/
		void SetSolutionForStartTranslation(const SolutionForStartTranslation solutionForStartTranslation);
		//#############################################################################
		//! Gets Interpolation 
		/*!
			Post processor supports 3 types of Interpolation: base on vector, base on machine angle (RTCP) and base on axis values (non-RTCP). 
			Interpolation algorithm is used by post processor to add (interpolate) additional moves in output posted-toolpath. 
			Interpolation algorithm will generate an exception if there are two consecutive moves with opposite orientations. 
			The number of extra moves (to be added) is set with additional parameters for distances and angles. 
		*/
		const Interpolation GetInterpolation() const;
		//#############################################################################
		//! Sets Interpolation 
		/*!
			Post processor supports 3 types of Interpolation: base on vector, base on machine angle (RTCP) and base on axis values (non-RTCP).
			Interpolation algorithm is used by post processor to add (interpolate) additional moves in output posted-toolpath.
			Interpolation algorithm will generate an exception if there are two consecutive moves with opposite orientations.
			The number of extra moves (to be added) is set with additional parameters for distances and angles.
		*/
		void SetInterpolation(const Interpolation interpolation);
		//#############################################################################
		//! Gets Feed Interpolation for angle value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			This parameter represents the minimum angle that must be found between two consecutive Feed moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Feed Interpolation for angle flag parameter is ON.
		*/
		const double GetInterpolationStep() const;
		//#############################################################################
		//! Sets Feed Interpolation for angle value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			This parameter represents the minimum angle that must be found between two consecutive Feed moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Feed Interpolation for angle flag parameter is ON.
		*/
		void SetInterpolationStep(const double);
		//#############################################################################
		//! Gets Rapid-Rate Interpolation for angle value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			This parameter represents the minimum distance that must be found between two consecutive Rapid-Rate moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Rapid-Rate Interpolation for angle flag parameter is ON.
		*/
		const double GetRapidRateInterpolationStep() const;
		//#############################################################################
		//! Sets Rapid-Rate Interpolation for angle value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			This parameter represents the minimum distance that must be found between two consecutive Rapid-Rate moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Rapid-Rate Interpolation for angle flag parameter is ON.
		*/
		void SetRapidRateInterpolationStep(const double);
		//#############################################################################
		//! Gets Feed Interpolation for angle flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			When this parameter is ON Interpolation algorithm will enable interpolation for angle for Feed moves. 
			The number of extra moves is set with additional parameters for distances and angles. 
		*/
		const bool GetInterpolationStepFlag() const;
		//#############################################################################
		//! Sets Feed Interpolation for angle flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			When this parameter is ON Interpolation algorithm will enable interpolation for angle for Feed moves.
			The number of extra moves is set with additional parameters for distances and angles.
		*/
		void SetInterpolationStepFlag(const bool);
		//#############################################################################
		//! Gets Rapid-Rate Interpolation for angle flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			When this parameter is ON Interpolation algorithm will enable interpolation for angle for Rapid-Rate moves. 
			The number of extra moves is set with additional parameters for distances and angles. 
		*/
		const bool GetRapidRateInterpolationStepFlag() const;
		//#############################################################################
		//! Sets Rapid-Rate Interpolation for angle flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			When this parameter is ON Interpolation algorithm will enable interpolation for angle for Rapid-Rate moves.
			The number of extra moves is set with additional parameters for distances and angles.
		*/
		void SetRapidRateInterpolationStepFlag(const bool);
		//#############################################################################
		//! Gets Feed Interpolation for distance value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			This parameter represents the minimum distance that must be found between two consecutive Feed moves in output posted-toolpath generated by post processor.
			This parameter is used only if Feed Interpolation for distance flag parameter is ON.
		*/
		const double GetInterpolationDist() const;
		//#############################################################################
		//! Sets Feed Interpolation for distance value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			This parameter represents the minimum distance that must be found between two consecutive Feed moves in output posted-toolpath generated by post processor.
			This parameter is used only if Feed Interpolation for distance flag parameter is ON.
		*/
		void SetInterpolationDist(const double);
		//#############################################################################
		//! Gets Rapid-Rate Interpolation for distance value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			This parameter represents the minimum distance that must be found between two consecutive Rapid-Rate moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Rapid-Rate Interpolation for distance flag parameter is ON.
		*/
		const double GetRapidRateInterpolationDist() const;
		//#############################################################################
		//! Sets Rapid-Rate Interpolation for distance value
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			This parameter represents the minimum distance that must be found between two consecutive Rapid-Rate moves in output posted-toolpath generated by post processor.
			Note: This parameter is used only if Rapid-Rate Interpolation for distance flag parameter is ON.
		*/
		void SetRapidRateInterpolationDist(const double);
		//#############################################################################
		//! Gets Feed Interpolation for distance flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			When this parameter is ON Interpolation algorithm will enable interpolation for distance for Feed moves. 
			The number of extra moves is set with additional parameters for distances and angles. 
		*/
		const bool GetInterpolationDistFlag() const;
		//#############################################################################
		//! Sets Feed Interpolation for distance flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			When this parameter is ON Interpolation algorithm will enable interpolation for distance for Feed moves.
			The number of extra moves is set with additional parameters for distances and angles.
		*/
		void SetInterpolationDistFlag(const bool);
		//#############################################################################
		//! Gets Rapid Rate Interpolation for distance flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves. 
			When this parameter is ON Interpolation algorithm will enable interpolation for distance for Rapid-Rate moves. 
			The number of extra moves is set with additional parameters for distances and angles. 
		*/
		const bool GetRapidRateInterpolationDistFlag() const;
		//#############################################################################
		//! Sets Rapid Rate Interpolation for distance flag
		/*!
			This parameter is used by post processor Interpolation algorithm to add (interpolate) additional moves between two consecutive moves.
			When this parameter is ON Interpolation algorithm will enable interpolation for distance for Rapid-Rate moves.
			The number of extra moves is set with additional parameters for distances and angles.
		*/
		void SetRapidRateInterpolationDistFlag(const bool);
		//#############################################################################
		//! Gets Retract distance
		/*!
			 This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter. 
			 When Retract to machine axis limits is OFF all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are controlled by Retract distance parameter (the Tool is retracted with distance Retract distance parameter value).
		*/
		const double GetRetractDistForLargeAngChange() const;
		//#############################################################################
		//! Sets Retract distance
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter.
			 When Retract to machine axis limits is OFF all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are controlled by Retract distance parameter (the Tool is retracted with distance Retract distance parameter value).
		*/
		void SetRetractDistForLargeAngChange(const double retractDist);
		//#############################################################################
		//! Gets Retract Tool at Machine Limits
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter. 
			When Retract to machine axis limits is ON all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are at the machine limits (the Tool is retracted until a machine limit is exedeed); 
			and when Retract to machine axis limits is OFF all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are controlled by Retract distance parameter (the Tool is retracted with distance Retract distance parameter value). 
		*/
		const bool GetRetractToolAtMax() const;
		//#############################################################################
		//! Sets Retract to machine axis limits
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter.
			When Retract to machine axis limits is ON all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are at the machine limits (the Tool is retracted until a machine limit is exedeed);
			and when Retract to machine axis limits is OFF all moves added by post processor for Rewind algorithm and Angle Change Limits parameter are controlled by Retract distance parameter (the Tool is retracted with distance Retract distance parameter value).
		*/
		void SetRetractToolAtMax(const bool retractToolAtMax);
		//#############################################################################
		//! Gets Pole Handling
		/*!
			It is important to understand that mapping a 5 axis tool orientation (described by I, J, K) to a 5 axis machine tool kinematics with two rotational axis creates in general two solutions.
			If there is only one solution, that solution is UNDETERMINED.
			This parameter is used to handle UNDETERMINED angle case. An example of UNDETERMINED angle soluion is when there is a 5-axis machine definition with spindle equal with (0,0,1) and move orientation is also equal with (0,0,1);
			in this case first rotation angle is UNDETERMINED: this means that any value for first rotation angle can be used without changing the direction of the Tool.
			When an angle axis of a move is UNDETERMINED is called Pole area (aka the north pole of the earth).
			Post processor takes advantage of the Pole area and changes angle values.
			There are 5 options supported.
		*/
		const PoleHandling& GetPoleHandling() const;
		//#############################################################################
		//! Sets Pole Handling
		/*!
			It is important to understand that mapping a 5 axis tool orientation (described by I, J, K) to a 5 axis machine tool kinematics with two rotational axis creates in general two solutions. 
			If there is only one solution, that solution is UNDETERMINED. 
			This parameter is used to handle UNDETERMINED angle case. An example of UNDETERMINED angle soluion is when there is a 5-axis machine definition with spindle equal with (0,0,1) and move orientation is also equal with (0,0,1); 
			in this case first rotation angle is UNDETERMINED: this means that any value for first rotation angle can be used without changing the direction of the Tool. 
			When an angle axis of a move is UNDETERMINED is called Pole area (aka the north pole of the earth). 
			Post processor takes advantage of the Pole area and changes angle values. 
			There are 5 options supported.
		*/
		void SetPoleHandling(const PoleHandling& poleHandling);
		//#############################################################################
		//! Gets Trigger Angle Tolerance
		/*!
			A 5-axis tool orientation (I,J,K) can be represented in general by two sets of values for the rotary axis (two possible solutions). 
			One exceptional case is when e.g. a axis rotating around the Z axis is present and the tool orientation is almost parallel to Z axis, 
			then any axis value will satisfy the conversion of the tool orientation vector to rotational values, this is called UNDETERMINED angle. 
			So only e.g. the second rotation axis value is important, first rotation axis can be arbitrary, since is UNDETERMINED. Such tool axis orientations are referred as "singularity" or "pole". 
			Post processor has a special handling for pole areas and in general the arbitrary axis value, e.g. first rotation axis (UNDETERMINED) is "frozen" for the time when the tool axis orientation is almost parallel to Z axis. 
			The Trigger Angle Tolerance parameter value is the angle limit between tool axis orientation and spindle direction vector ( spindle direction vector is direction of the Tool when all axis are 0 ). 
			Making this value smaller, for e.g. 0.01 degrees, is recommended in order to avoid machining errors. 
			On the other hand, small values might generate a lot of rotation axis motions by just little changes of tool axis orientation. 
			Note, that Z axis is here just a sample, such poles can happen with any spindle main direction. 
		*/
		const double GetPoleAngleTolInDeg() const;
		//#############################################################################
		//! Sets Trigger Angle Tolerance
		/*!
			A 5-axis tool orientation (I,J,K) can be represented in general by two sets of values for the rotary axis (two possible solutions).
			One exceptional case is when e.g. a axis rotating around the Z axis is present and the tool orientation is almost parallel to Z axis,
			then any axis value will satisfy the conversion of the tool orientation vector to rotational values, this is called UNDETERMINED angle.
			So only e.g. the second rotation axis value is important, first rotation axis can be arbitrary, since is UNDETERMINED. Such tool axis orientations are referred as "singularity" or "pole".
			Post processor has a special handling for pole areas and in general the arbitrary axis value, e.g. first rotation axis (UNDETERMINED) is "frozen" for the time when the tool axis orientation is almost parallel to Z axis.
			The Trigger Angle Tolerance parameter value is the angle limit between tool axis orientation and spindle direction vector ( spindle direction vector is direction of the Tool when all axis are 0 ).
			Making this value smaller, for e.g. 0.01 degrees, is recommended in order to avoid machining errors.
			On the other hand, small values might generate a lot of rotation axis motions by just little changes of tool axis orientation.
			Note, that Z axis is here just a sample, such poles can happen with any spindle main direction.
		*/
		void SetPoleAngleTolInDeg(const double poleAngleTolInDeg);
		//#############################################################################
		//! Gets Limits
		/*!
			This parameter sets machine limit type in post processor. 
			There can be 4 type of settings: no limits (post::mwMXPParam::NO_LIMITS), all limits (post::mwMXPParam::ALL_LIMITS), rotation only (post::mwMXPParam::ROTATIONAL_LIMITS), and translation only (post::mwMXPParam::TRANSLATIONAL_LIMITS). 
			If machine limits are used (rotations/translations) and a axis value is out of machine limits (and there is no solution available to be used) then an exception is thrown. 
			When there are two possible solutions (5-axis/6-axis post processors) this parameter may result in selection of one solution, if a solution is out of machine limits.
		*/
		const MachineLimits& GetMachineLimits() const;
		//#############################################################################
		//! Sets Limits
		/*!
			This parameter sets machine limit type in post processor.
			There can be 4 type of settings: no limits (post::mwMXPParam::NO_LIMITS), all limits (post::mwMXPParam::ALL_LIMITS), rotation only (post::mwMXPParam::ROTATIONAL_LIMITS), and translation only (post::mwMXPParam::TRANSLATIONAL_LIMITS).
			If machine limits are used (rotations/translations) and a axis value is out of machine limits (and there is no solution available to be used) then an exception is thrown.
			When there are two possible solutions (5-axis/6-axis post processors) this parameter may result in selection of one solution, if a solution is out of machine limits.
		*/
		void SetMachineLimits(const MachineLimits& machineLimits);
		//#############################################################################
		//! Gets Angle Tolerance for Using Machine Limits
		/*!
			This parameter defines tolerance used by post processor to check if a rotation axis values is in machine limits. 
			It is used only if Limits parameter is set to ALL_LIMITS or ROTATIONAL_LIMITS.
			A rotation axis value is considered out of limits if is larger/smaller then machine limits +/- Angle Tolerance for Using Machine Limits value.
			For translation axes the tolerance used by post processor is hard-coded with the value 1e-12.
		*/
		const double GetAngleTolInDegForUsingMachLimits() const;
		//#############################################################################
		//! Sets Angle Tolerance for Using Machine Limits
		/*!
			This parameter defines tolerance used by post processor to check if a rotation axis values is in machine limits.
			It is used only if Limits parameter is set to ALL_LIMITS or ROTATIONAL_LIMITS.
			A rotation axis value is considered out of limits if is larger/smaller then machine limits +/- Angle Tolerance for Using Machine Limits value.
			For translation axes the tolerance used by post processor is hard-coded with the value 1e-12.
		*/
		void SetAngleTolInDegForUsingMachLimits(const double angleTolInDegForUsingMachLimits);
		//#############################################################################
		//! Gets Angle Change Limits
		/*!
			This parameter sets a maximum angle difference between two consecutive Feed moves. 
			If there is an angle change, in circle unit, larger, then additional retract moves are added by post processor.
			This is a safety measure to avoid sudden movement of the Tool on the contour. 
			E.g. if this limit is 120 degree and a rotation axis is moving from 10 degree to 170 degree, then, such a move will be considered as a large angle change and a retract motion is applied. 
			The retract distance is controlled by the parameters Retract to machine axis limits parameter, Retract distance parameter, Additional retract parameter, Additional retract direction parameter, Additional retract to Machine Axis Limits parameter and Additional retract distance parameter.
		*/
		const double GetAngleChangeLimit() const;
		//#############################################################################
		//! Sets Angle Change Limits
		/*!
			This parameter sets a maximum angle difference between two consecutive Feed moves.
			If there is an angle change, in circle unit, larger, then additional retract moves are added by post processor.
			This is a safety measure to avoid sudden movement of the Tool on the contour.
			E.g. if this limit is 120 degree and a rotation axis is moving from 10 degree to 170 degree, then, such a move will be considered as a large angle change and a retract motion is applied.
			The retract distance is controlled by the parameters: Retract to machine axis limits parameter, Retract distance parameter, Additional retract parameter, Additional retract direction parameter, Additional retract to Machine Axis Limits parameter and Additional retract distance parameter.
		*/
		void SetAngleChangeLimit(const double angleChangeLimit);
		//#############################################################################
		//! Gets Toolpath Alignment 
		/*!
			 When this parameter is ON, 3-axis post processor and 4-axis post processor will try to rotate the toolpath in order to be aligned with the machine. 
			 For e.g. if a pure 3-axis toolpath is used with all move orientations equal with (1,0,0) and a 3-axis post processor with a machine spindle equal with (0,0,1), 
			 if Toolpath Alignment parameter is ON, then internally, a rotation is applied to the toolpath from (1,0,0) to (0,0,1). 
			 The same behavior is happening for 4-axis post processor.
		*/
		const bool GetToolpathAlignment() const;
		//#############################################################################
		//! Sets Toolpath Alignment 
		/*!
			 When this parameter is ON, 3-axis post processor and 4-axis post processor will try to rotate the toolpath in order to be aligned with the machine.
			 For e.g. if a pure 3-axis toolpath is used with all move orientations equal with (1,0,0) and a 3-axis post processor with a machine spindle equal with (0,0,1),
			 if Toolpath Alignment parameter is ON, then internally, a rotation is applied to the toolpath from (1,0,0) to (0,0,1).
			 The same behavior is happening for 4-axis post processor.
		*/
		void SetToolpathAlignment(const bool toolpathAlignment);
		//#############################################################################
		//! Gets Toolpath Tolerance
		/*!
			3-axis post processor and 4-axis post processor use this parameter to check if the toolpath can be posted; 
			if 3-axis machine definition or 4-axis machine definition can rotate the Tool in all move orientations. 
			This check uses a tolerance set by this parameter. 
			In case of 3-axis posting the orientation of every move in the toolpath must be equal with machine spindle (move orientation vs machine spindle), otherwise post processor will throw an exception. 
			In case of 4-axis post processor the test is slightly more complicated, but in a similar way, post processor will check if all orientations are can be accomplished by machine Tool (scalar product between the spindle and rotation angle vs scalar product between move orientation and rotation angle). 
		*/
		const double GetToolpathTolerance() const;
		//#############################################################################
		//! Sets Toolpath Tolerance
		/*!
			3-axis post processor and 4-axis post processor use this parameter to check if the toolpath can be posted;
			if 3-axis machine definition or 4-axis machine definition can rotate the Tool in all move orientations.
			This check uses a tolerance set by this parameter.
			In case of 3-axis posting the orientation of every move in the toolpath must be equal with machine spindle (move orientation vs machine spindle), otherwise post processor will throw an exception.
			In case of 4-axis post processor the test is slightly more complicated, but in a similar way, post processor will check if all orientations are can be accomplished by machine Tool (scalar product between the spindle and rotation angle vs scalar product between move orientation and rotation angle).
		*/
		void SetToolpathTolerance(const double toolpathTolerance);
		//#############################################################################
		//! Gets Retract and Rewind activation
		/*! 
			In some cases rotation angles exceed machine limits. The rewind algorithm can solve this problem. To do this the tool is retracted, the angle that is over the machine limits is twisted back, and the tool return back to contour.
			Rewind algorithm can be enable or disable. By default rewind algorithm is enable.
		*/
		const bool GetRetractAndRewindFlag() const;
		//#############################################################################
		//! Sets Retract and Rewind activation
		/*!
			In some cases rotation angles exceed machine limits. The rewind algorithm can solve this problem. To do this the tool is retracted, the angle that is over the machine limits is twisted back, and the tool return back to contour.
			Rewind algorithm can be enable or disable. By default rewind algorithm is enable.
		*/
		void SetRetractAndRewindFlag(const bool retractAndRewindFlag);
		//#############################################################################
		//! Gets Rewind in one angle step
		/*!
			This parameter is used by Rewind algorithm. 
			When this parameter is ON, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back in only one step. 
			Retract distance is controlled by Retract to machine axis limits parameter and Retract distance parameter. 
			When this parameter is OFF, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back; 
			the number of moves added by Rewind algorithm is controlled by Rewind max angle interpolation parameter. 
			Rewind max angle interpolation defines how many moves to be added; for e.g. if a rewind of 360 degree is created and Rewind max angle interpolation is 10 then 36 moves are added (360/10). 
			An additional retract can be applied if Additional retract parameter is ON.
			Note: when Rewind in one angle step parameter is ON API function SetRetractAndRewindAngleFlag is set to false.
		*/
		const bool GetRetractAndRewindAngleFlag() const;
		//#############################################################################
		//! Sets Rewind in one angle step
		/*!
			This parameter is used by Rewind algorithm.
			When this parameter is ON, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back in only one step.
			Retract distance is controlled by Retract to machine axis limits parameter and Retract distance parameter.
			When this parameter is OFF, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back;
			the number of moves added by Rewind algorithm is controlled by Rewind max angle interpolation parameter.
			Rewind max angle interpolation defines how many moves to be added; for e.g. if a rewind of 360 degree is created and Rewind max angle interpolation is 10 then 36 moves are added (360/10).
			An additional retract can be applied if Additional retract parameter is ON.
			Note: when Rewind in one angle step parameter is ON API function SetRetractAndRewindAngleFlag is set to false.
		*/
		void SetRetractAndRewindAngleFlag(const bool retractAndRewindAngleFlag);
		//#############################################################################
		//! Gets Rewind max angle interpolation
		/*!
			This parameter is used by Rewind algorithm. 
			When a rotation axis is exceeded, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back. 
			Retract distance is controlled by Retract to machine axis limits parameter and Retract distance parameter. 
			The number of moves added by Rewind algorithm is controlled by Rewind in one angle step parameter and Rewind max angle interpolation parameter. 
			Rewind max angle interpolation defines how many moves to be added; for e.g. if a rewind of 360 degree is created and Rewind max angle interpolation is 10 then 36 moves are added (360/10). 
			This parameter has an effect only if  Rewind in one angle step parameter is OFF. 
			An additional retract can be applied if Additional retract parameter is ON.
		*/
		const double GetRetractAndRewindAngleStep() const;
		//#############################################################################
		//! Sets Rewind max angle interpolation
		/*!
			This parameter is used by Rewind algorithm.
			When a rotation axis is exceeded, and Retract and rewind parameter is ON, Rewind algorithm will retract the Tool and rewind the rotation axis back.
			Retract distance is controlled by Retract to machine axis limits parameter and Retract distance parameter.
			The number of moves added by Rewind algorithm is controlled by Rewind in one angle step parameter and Rewind max angle interpolation parameter.
			Rewind max angle interpolation defines how many moves to be added; for e.g. if a rewind of 360 degree is created and Rewind max angle interpolation is 10 then 36 moves are added (360/10).
			This parameter has an effect only if  Rewind in one angle step parameter is OFF.
			An additional retract can be applied if Additional retract parameter is ON.
		*/
		void SetRetractAndRewindAngleStep(const double retractAndRewindAngeStep);
		//#############################################################################
		//! Gets Additional Retract
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, 
			is bigger then angle change limit set with Angle Change Limits parameter, 
			in order to enable the addition of an extra retract.
		*/
		const bool GetAdditionalRetractFlag() const;
		//#############################################################################
		//! Sets Additional Retract
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves,
			is bigger then angle change limit set with Angle Change Limits parameter,
			in order to enable the addition of an extra retract.
		*/
		void SetAdditionalRetractFlag(const bool additionalRetractFlag);
		//#############################################################################
		//! Gets Additional retract to Machine Axis Limits
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, 
			between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter. 
			When this parameter is ON, and Additional retract parameter is ON, an additional retract will be added to Machine Axis Limits. 
			When this parameter is OFF, and Additional retract parameter is ON, an additional retract will be added at a specified distance ( this distance is specified with Additional retract distance parameter ). 
		*/
		const bool GetAdditionalRetractToolAtMax() const;
		//#############################################################################
		//! Sets Additional retract to Machine Axis Limits
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle,
			between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter.
			When this parameter is ON, and Additional retract parameter is ON, an additional retract will be added to Machine Axis Limits.
			When this parameter is OFF, and Additional retract parameter is ON, an additional retract will be added at a specified distance ( this distance is specified with Additional retract distance parameter ).
		*/
		void SetAdditionalRetractToolAtMax(const bool additionalRetractToolAtMax);
		//#############################################################################
		//! Gets Additional retract distance
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, 
			between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter, 
			in order to define a distance used for additional retract. 
			This value is used only if Additional retract to Machine Axis Limits parameter is OFF.
		*/
		const double GetAdditionalRetractDistForLargeAngChange() const;
		//#############################################################################
		//! Sets Additional retract distance
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle,
			between two consecutive Feed moves, is bigger then angle change limit set with Angle Change Limits parameter,
			in order to define a distance used for additional retract.
			This value is used only if Additional retract to Machine Axis Limits parameter is OFF.
		*/
		void SetAdditionalRetractDistForLargeAngChange(const double additionalRetractDist);
		//#############################################################################
		//! Gets Additional retract direction
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves, 
			is bigger then angle change limit set with Angle Change Limits parameter, 
			in order to define a 3D vector used for additional retract. 
			The vector is defined in workpiece coordinate system (toolpath coordinate system). 
			This value is used only if Additional retract parameter is ON.
		*/
		const cadcam::mwPoint3d& GetAdditionalRetractDirection() const;
		//#############################################################################
		//! Sets Additional retract direction
		/*!
			This parameter is used by post processor for Rewind algorithm, and when the difference of the angle, between two consecutive Feed moves,
			is bigger then angle change limit set with Angle Change Limits parameter,
			in order to define a 3D vector used for additional retract.
			The vector is defined in workpiece coordinate system (toolpath coordinate system).
			This value is used only if Additional retract parameter is ON.
		*/
		void SetAdditionalRetractDirection(const cadcam::mwPoint3d& additionalRetractDirection);
		//#############################################################################
		//! Gets Filter Duplicate Moves
		/*!
			When this parameter is ON post processor will filter (delete) consecutive posted-moves which have the same values for all axes. 
			Filter uses a hard-coded tolerance of 1e-12.
		*/
		const bool ShouldFilterDuplicateMoves() const;
		//#############################################################################
		//! Sets Filter Duplicate Moves
		/*!
			When this parameter is ON post processor will filter (delete) consecutive posted-moves which have the same values for all axes.
			Filter uses a hard-coded tolerance of 1e-12.
		*/
		void SetFilterDuplicateMoves(const bool shouldFilter);
		//#############################################################################
		//! Gets Geometry Axis Value RTCP OFF
		/*!
			Enable special posting. 
			When this parameter is ON post processor will ignore rotary axis base positions, machine holder transformation, machine workpiece transformation, and tool length compensation (TLC) is 0.
		*/
		const bool GetGeometryAxisValuesRTCPOFF() const;
		//#############################################################################
		//! Sets Geometry Axis Value RTCP OFF
		/*!
			Enable special posting.
			When this parameter is ON post processor will ignore rotary axis base positions, machine holder transformation, machine workpiece transformation, and tool length compensation (TLC) is 0.
		*/
		void SetGeometryAxisValuesRTCPOFF(const bool valuesOfToolTipInFixedWorkpieceCS);
		//#############################################################################
		//! Gets Limit the travel of linear axis
		/*!
			This parameter is used by Force Head and Table rotation algorithm to handle UNDETERMINED angle case when translation axis changes from plus to minus or vice versa. 
			if parameters can not be respected, then, any possible solution is used by Force Head and Table rotation algorithm (this behavior is hard-coded in post processor).
			Force Head and Table rotation algorithm will block one translation axis and use a UNDETERMINED rotation axis instead; 
			the translation axis that is not fixed may change its direction from plus to minus or vice versa: this will not happen if Limit the travel of linear axis parameter is ON, 
			but a big jump rotation may be created.
		*/
		const bool GetLimitLinearAxisTravel() const;
		//#############################################################################
		//! Sets Limit the travel of linear axis
		/*!
			This parameter is used by Force Head and Table rotation algorithm to handle UNDETERMINED angle case when translation axis changes from plus to minus or vice versa.
			if parameters can not be respected, then, any possible solution is used by Force Head and Table rotation algorithm (this behavior is hard-coded in post processor).
			Force Head and Table rotation algorithm will block one translation axis and use a UNDETERMINED rotation axis instead;
			the translation axis that is not fixed may change its direction from plus to minus or vice versa: this will not happen if Limit the travel of linear axis parameter is ON,
			but a big jump rotation may be created.
		*/
		void SetLimitLinearAxisTravel(const bool limitLinearAxisTravel);
		//#############################################################################
		//! Gets Custom axis direction vector
		/*!
			This parameter is used by the Force Head and Table rotation algorithm of the 4-axis, 5-axis and 6-axis post processors.
			When Force Head or Table rotation instead of Linear Axis moves is used, the axis values will be calculated in such a way that all rotation axis will be left in initial positions (usually 0).
			When an option such as Select between the two solutions for startup: by providing Translation Axis direction (or similar) is used, that changes the starting position to another position, the machine will start in the desired position, but during posting, will slowly transition to the natural starting position (which is similar to not using the startup position change setting) by moving translational axis while also rotating the table/head.
			By using this option, the posting will try on a best-effort basis to maintain the translational axes (linear axes) in a similar position (side) to the selected starting position.
		*/
		const cadcam::mwPoint3d& GetCustomTransAxisDirValues() const;
		//#############################################################################
		//! Sets Custom axis direction vector
		/*!
			This parameter is used by the Force Head and Table rotation algorithm of the 4-axis, 5-axis and 6-axis post processors.
			When Force Head or Table rotation instead of Linear Axis moves is used, the axis values will be calculated in such a way that all rotation axis will be left in initial positions (usually 0).
			When an option such as Select between the two solutions for startup: by providing Translation Axis direction (or similar) is used, that changes the starting position to another position, the machine will start in the desired position, but during posting, will slowly transition to the natural starting position (which is similar to not using the startup position change setting) by moving translational axis while also rotating the table/head.
			By using this option, the posting will try on a best-effort basis to maintain the translational axes (linear axes) in a similar position (side) to the selected starting position.
		*/
		void SetCustomTransAxisDirValues(const cadcam::mwPoint3d& customTransAxisDirValues);
		//#############################################################################
		//! Gets Solution Change For Minimum Retracts & Rewinds
		/*!
			This parameter is used by post processor for 5 axis machines
			and 5+1 axis machines. When this parameter is ON the chosen solution (Solution 1 / Solution 2) can be changed.
			Solution that generates fewer retractions is selected when this parameter is ON.
		*/
		const bool GetSolutionChangeForMinRetractsAndRewinds() const;
		//#############################################################################
		//! Sets Solution Change For Minimum Retracts & Rewinds
		/*!
			This parameter is used by post processor for 5 axis machines
			and 5+1 axis machines. When this parameter is ON the chosen solution (Solution 1 / Solution 2) can be changed.
			Solution that generates fewer retractions is selected when this parameter is ON.
		*/
		void SetSolutionChangeForMinRetractsAndRewinds(const bool solutionChangeForMinRetractsAndRewinds);
		//#############################################################################
		//! Gets Filter Arc/Helix
		/*!
			Use this parameter to enable filters for arcs/helices. 
			When this parameter is ON, the post processor deletes intermediate moves (marked with post::mwPostedArcMove::ARC_POINT) from the
			posted toolpath.
			Filters are defined with additional parameters. If you use a filter to removes moves, the last move
			in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		const bool IsEnableFilterArcsAndHelices() const;
		//#############################################################################
		//! Sets Filter Arc/Helix
		/*!
			Use this parameter to enable filters for arcs/helices.
			When this parameter is ON, the post processor deletes intermediate moves (marked with
		   post::mwPostedArcMove::ARC_POINT) from the posted toolpath. Filters are defined with
		   additional parameters. If you use a filter to removes moves, the last move in the arc
		   (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		void EnableFilterArcsAndHelices(const bool enableFilterArcsAndHelices);
		//#############################################################################
		//! Gets Filter Max Sweep Angle Value
		/*!
			This parameter is used by the arcs/helices filter.
			If an arc/helix has a sweep angle (in degrees) greater than this value, it is divided into smaller
			arcs/helices with a sweep angle equal to this value.
		*/
		const double GetFilterMaxSweepAngle() const;
		//#############################################################################
		//! Sets Filter Max Sweep Angle Value
		/*!
			This parameter is used by the arcs/helices filter.
			If an arc/helix has a sweep angle (in degrees) greater than this value, it is divided into smaller
			arcs/helices with a sweep angle equal to this value.
		*/
		void SetFilterMaxSweepAngle(const double filterMaxSweepAngle);
		//#############################################################################
		//! Gets Filter Arcs
		/*!
			Use this parameter to enable filters for helices. When this parameter is ON, the post processor deletes intermediary moves 
			(marked with post::mwPostedArcMove::ARC_POINT) from posted toolpaths that are part of a helix.
            The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
			The difference between an arc and a helix is determined by the height.
		*/
		const bool IsFilterHelices() const;
		//#############################################################################
		//! Sets Filter Arcs
		/*!
			Use this parameter to enable filters for helices. When this parameter is ON, the post processor deletes intermediary moves 
			(marked with post::mwPostedArcMove::ARC_POINT) from posted toolpaths that are part of a helix. 
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated. 
			The difference between an arc and a helix is determined by the height.
		*/
		void SetFilterHelices(const bool filterHelices);
		//#############################################################################
		//! Gets Filter Helices
		/*!
			Use this parameter to enable filters for helices. When this parameter is ON, the post
			processor deletes intermediary moves (marked with post::mwPostedArcMove::ARC_POINT) from posted
			toolpaths that are part of a helix.
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
			The difference between an arc and a helix is determined by the height.
		*/
		const bool IsFilterArcs() const;
		//#############################################################################
		//! Sets Filter Helices
		/*!
			Use this parameter to enable filters for arcs. When this parameter is ON, the post
			processor deletes intermediary moves (marked with post::mwPostedArcMove::ARC_POINT) from posted toolpaths that are part of an arc.
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
			The difference between an arc and a helix is determined by the height.
		*/
		void SetFilterArcs(const bool filterArcs);
		//#############################################################################
		//! Gets Filter Max Sweep Angle 
		/*!
			This parameter is used by the arcs/helices filters.
			If the sweep angle (in degrees) of an arc/helix is greater than the Filter Max Sweep Angle Value parameter, 
			it is divided into smaller arcs/helices with a sweep angle equal to the Max Sweep Angle Value.
		*/
		const bool IsFilterWithMaxSplitSweepAngle() const;
		//#############################################################################
		//! Sets Filter Max Sweep Angle 
		/*!
			This parameter is used by the arcs/helices filters.
			If the sweep angle (in degrees) of an arc/helix is greater than the Filter Max Sweep Angle Value parameter, 
			it is divided into smaller arcs/helices with a sweep angle equal to the Max Sweep Angle Value.
		*/
		void SetFilterWithMaxSplitSweepAngle(const bool filterWithMaxSplitSweepAngle);
		//#############################################################################
		//! Gets Filter Arcs/Helices based on normal direction
		/*!
			This parameter is used by the Arc/Helix filter algorithm.
			The post processor applies a filters to arcs/helices whose normals are parallel to one value defined by this parameter.
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		const bool IsFilterUsingArcPlanes() const;
		//#############################################################################
		//! Sets Filter Arcs/Helices based on normal direction
		/*!
			This parameter is used by the Arc/Helix filter algorithm.
			The post processor applies a filters to arcs/helices whose normals are parallel to one value defined by this parameter. 
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		void SetFilterUsingArcPlanes(const bool filterUsingArcPlanes);
		//#############################################################################
		//! Gets Filter Arcs/Helices normal directions
		/*!
			This parameter is used by the Arc/Helix filter algorithm.
			The post processor will apply a filter for arcs/helices having normals parallel with one value defined by this parameter.
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		const std::vector<cadcam::mwPoint3d>& GetFilterArcPlaneNormals() const;
		//#############################################################################
		//! Sets Filter Arcs/Helices normal directions
		/*!
			This parameter is used by the Arc/Helix filter algorithm.
			The post processor will apply a filter for arcs/helices having normals parallel with one value defined by this parameter. 
			The last move in the arc (marked with post::mwPostedArcMove::ARC_END) is never eliminated.
		*/
		void SetFilterArcPlaneNormals(const std::vector<cadcam::mwPoint3d>& filterArcPlaneNormals);
		//#############################################################################
		//! Gets Smooth lead-out and lead-in for Retract and Approach
		/*!
			This parameter is used by the post processor Rewind algorithm and when the difference in the angle between two consecutive feed moves is bigger 
			than the angle change limit set via the Angle Change Limits parameter. 
			When a retract is added by post processor, if this parameter is true additional moves are added to smooth the entry/exit motion. 
			The distance from original moves are defined by Rapid motion for exit distance and Rapid motion for entry distance parameters.
		*/
		const bool IsSmoothLeadOutAndIn() const;
		//#############################################################################
		//! Sets Smooth lead-out and lead-in for Retract and Approach
		/*!
			This parameter is used by the post processor Rewind algorithm and when the difference in the angle between two consecutive feed moves is bigger 
			than the angle change limit set via the Angle Change Limits parameter. 
			When a retract is added by post processor, if this parameter is true additional moves are added to smooth the entry/exit motion.
			The distance from original moves are defined by Rapid motion for exit distance and Rapid motion for entry distance parameters.
		*/
		void SetSmoothLeadOutAndIn(const bool smoothLeadOutAndIn);
		//#############################################################################
		//! Gets Rapid motion for exit distance
		/*!
			This parameter is used by the post processor for Smooth lead-out and lead-in for Retract and Approach parameter. 
			When a retract is added by post processor, value defined by this parameter is used to set retract distance for exit. 
			Using this parameter a motion can be added to smooth the retract.
		*/
		const double GetRapidExitDist() const;
		//#############################################################################
		//! Sets Rapid motion for exit distance
		/*!
			This parameter is used by the post processor for Smooth lead-out and lead-in for Retract and Approach parameter. 
			When a retract is added by post processor, value defined by this parameter is used to set retract distance for exit. 
			Using this parameter a motion can be added to smooth the retract.
		*/
		void SetRapidExitDist(const double rapidExitDist);
		//#############################################################################
		//! Gets Rapid motion for entry distance
		/*!
			This parameter is used by the post processor for Smooth lead-out and lead-in for Retract and Approach parameter. 
			When a retract is added by post processor, value defined by this parameter is used to set retract distance for entry.
			Using this parameter a motion can be added to smooth the retract.
		*/
		const double GetFeedEntryDist() const;
		//#############################################################################
		//! Sets Rapid motion for entry distance
		/*!
			This parameter is used by the post processor for Smooth lead-out and lead-in for Retract and Approach parameter. 
			When a retract is added by post processor, value defined by this parameter is used to set retract distance for entry. 
			Using this parameter a motion can be added to smooth the retract.
		*/

		void SetFeedEntryDist(const double feedEntryDist);
		//#############################################################################
		//! Sets move orientation in Machine Coordinate System
		/*!
			This parameter is used to compute move orientation in Machine Coordinate System (MCS).
			Orientation of the move defines tool direction for every move, and can be extracted from posted move using the API post::mwPostMove::GetOrientation().
			By default move orientation is defined in Workpiece Coordinate System (WCS).
		*/
		void SetOrientationInMCS(const bool orientationInMCS);
		//#############################################################################
		//! Gets if move orientation is defined in Machine Coordinate System
		/*!
			This parameter is used to compute move orientation in Machine Coordinate System (MCS)
			Orientation of the move defines tool direction for every move, and can be extracted from posted move using the API post::mwPostMove::GetOrientation().
			By default move orientation is defined in Workpiece Coordinate System (WCS).
		*/
		bool IsOrientationInMCS() const;
		//#############################################################################
		//! Sets potential surface contact point in Machine Coordinate System
		/*!
			This parameter is used to compute potential surface contact point, if present and valid, in Machine Coordinate System (MCS).
			Potential surface contact point is a 3D point that defines where tool touch the workpiece. This position can be found in initial toolpath used by post processor
			and can be extracted from posted moves using the API  post::mwPostedMove::GetPotentialSurfaceCP()
			By default move potential surface contact point is defined in Workpiece Coordinate System (WCS).
		*/
		void SetPotentialSurfaceCPInMCS(const bool potentialSurfaceCPInMCS);
		//#############################################################################
		//! Gets if potential surface contact point is defined in Machine Coordinate System
		/*!
			This parameter is used to compute potential surface contact point, if present and valid, in Machine Coordinate System (MCS).
			Potential surface contact point is a 3D point that defines where tool touch the workpiece. This position can be found in initial toolpath used by post processor
			and can be extracted from posted moves using the API post::mwPostedMove::GetPotentialSurfaceCP().
			By default move potential surface contact point is defined in Workpiece Coordinate System (WCS).
		*/
		bool IsPotentialSurfaceCPInMCS() const;
		//#############################################################################
		//! Sets potential surface contact point orientation in Machine Coordinate System
		/*!
			This parameter is used to compute potential surface contact point orientation, if present and valid, in Machine Coordinate System (MCS).
			Potential surface contact point orientation is a 3D vector perpendicular to workpiece in potential surface point.
			This vector can be found in initial toolpath used by post processor
			and can be extracted from posted moves using the API post::mwPostedMove::GetPotentialSurfaceCPOrient().
			By default move potential surface contact point orientation is defined in Workpiece Coordinate System (WCS).
		*/
		void SetPotentialSurfaceCPOrientInMCS(const bool potentialSurfaceCPOrientInMCS);
		//#############################################################################
		//! Gets if potential surface contact point orientation is defined in Machine Coordinate System
		/*!
			This parameter is used to compute potential surface contact point orientation, if present and valid, in Machine Coordinate System (MCS).
			Potential surface contact point orientation is a 3D vector perpendicular to workpiece in potential surface point.
			This vector can be found in initial toolpath used by post processor
			and can be extracted from posted moves using the API post::mwPostedMove::GetPotentialSurfaceCPOrient().
			By default move potential surface contact point orientation is defined in Workpiece Coordinate System (WCS).
		*/
		bool IsPotentialSurfaceCPOrientInMCS() const;
		//#############################################################################
		//! Sets 6-axis tool cutting direction, called also side orientation vector, in Machine Coordinate System
		/*!
			This parameter is used to compute tool side orientation (cutting direction) for 6-axis in Machine Coordinate System (MCS).
			Side orientation of the move defines tool cutting direction for every move for 6-axis post processor,
			and can be extracted from 6-axis posted moves using the API post::mwPosted6axMove::GetSawOrient().
			By default 6-axis move side orientation is defined in Workpiece Coordinate System (WCS).
		*/
		void SetSideOrientationInMCS(const bool sideOrientationInMCS);
		//#############################################################################
		//! Gets if 6-axis tool cutting direction, called also side orientation vector, is defined in Machine Coordinate System
		/*!
			This parameter is used to compute tool side orientation (cutting direction) for 6-axis in Machine Coordinate System (MCS).
			Side orientation of the move defines tool cutting direction for every move for 6-axis post processor,
			and can be extracted from 6-axis posted moves using the API post::mwPosted6axMove::GetSawOrient().
			By default 6-axis move side orientation is defined in Workpiece Coordinate System (WCS).
		*/
		bool IsSideOrientationInMCS() const;
		//#############################################################################
		//! Sets Avoid Rotation Axis direction change 
		/*!
			This parameter is used by the **Force Head and Table rotation** algorithm of the 4-axis, 5-axis post processors to keep table rotation in one direction.
			When this is enabled, post processor will try to find a solution that rotates the table instead of using the linear axis, but the table always rotated in the same direction. Example:
			if at the beginning the table starts to rotate clockwise, the table rotate the clockwise for the entire toolpath;
			if at the beginning the table starts to rotate counter-clockwise, the table rotate counter-clockwise for the entire toolpath.
			At each moment if the table tries to rotate in the opposite direction compared to previous moves, the posting will use only X,Y,Z (linear axis) and freeze the table rotation.
			The algorithm can resume the table rotation, but only if this is happening in the same direction as it started at the beginning.
		*/
		void SetAvoidRotationAxisDirectionChange(const bool avoidRotationAxisDirectionChange);
		//#############################################################################
		//! Gets Avoid Rotation Axis direction change 
		/*!
			This parameter is used by the **Force Head and Table rotation** algorithm of the 4-axis, 5-axis post processors to keep table rotation in one direction.
			When this is enabled, post processor will try to find a solution that rotates the table instead of using the linear axis, but the table always rotated in the same direction. Example:
			if at the beginning the table starts to rotate clockwise, the table rotate the clockwise for the entire toolpath;
			if at the beginning the table starts to rotate counter-clockwise, the table rotate counter-clockwise for the entire toolpath.
			At each moment if the table tries to rotate in the opposite direction compared to previous moves, the posting will use only X,Y,Z (linear axis) and freeze the table rotation.
			The algorithm can resume the table rotation, but only if this is happening in the same direction as it started at the beginning.
		*/
		bool IsAvoidRotationAxisDirectionChange() const;
		//#############################################################################

		mwRoboticMXPParamPtr& GetRobParamPtr();

		const mwRoboticMXPParamPtr& GetRobParamPtr() const;

		void SetRobParamPtr(const mwRoboticMXPParamPtr& robParam);

protected:
		//#############################################################################
		//! Scaled all measurable data of the machine definition by the given scale factor
		/*!
			\param units not used here
			\param scaleFactor  the machine definition is scaled by the scale factor
		*/
		void Scale(const Units,const double& scaleFactor);
		//#############################################################################
private:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################	
		bool						   m_angleSelAutoFrom2Pairs;
		bool						   m_angleSelOtherPair;
		double						   m_angChangLim;
		double						   m_feedRateInterAngStep;
		double						   m_rapidRateInterAngStep;
		double						   m_feedRateInterDist;
		double						   m_rapidRateInterDist;
		bool						   m_rapidRateInterDistFlag;
		bool						   m_feedRateInterDistFlag;
		bool						   m_rapidRateInterAngleFlag;
		bool						   m_feedRateInterAngleFlag;
		double						   m_poleAngleTolInDeg;
		MachineLimits				   m_machineLimits;
		double						   m_angleTolInDegForUsingMachLimits;
		StartAngleType				   m_startAngleType;
		SolutionForStartAngle		   m_solutionForStartAngle;
		double						   m_preferredStartAngleValDeg;
		PoleHandling                   m_poleHandling;
		bool                           m_toolpathAlignment;
		Interpolation                  m_interpolation;
		double                         m_toolpathTolerance;
		bool                           m_provideStartRotationAngle;
		bool                           m_firstSolution0;
		bool						   m_filterDuplicateMoves;
		SolutionForStartTranslation    m_solutionForStartTranslation;
		bool                           m_valuesOfToolTipInFixedWorkpieceCS;
		bool                           m_limitLinearAxisTravel;
		cadcam::mwPoint3d              m_customTransAxisDirValues;
		bool                           m_retractAndRewindFlag;
		bool                           m_retractToolAtMax;
		bool                           m_additionalRetractFlag;
		bool                           m_additionalRetractToolAtMax;
		bool                           m_retractAndRewindAngeFlag;
		double						   m_retractDist;
		double                         m_additionalRetractDist;
		double                         m_retractAndRewindAngeStep;
		cadcam::mwPoint3d              m_additionalRetractDirection;
		bool						   m_solutionChangeForMinRetractsAndRewinds;
		bool                           m_enableFilterArcsAndHelices;
		double                         m_filterMaxSweepAngle;
		bool                           m_filterHelices;
		bool                           m_filterArcs;
		bool                           m_filterWithMaxSplitSweepAngle;
		bool                           m_filterUsingArcPlanes;
		std::vector<cadcam::mwPoint3d> m_filterArcPlaneNormals;
		bool						   m_smoothLeadOutAndInFlag;
		double						   m_rapidExitDist;
		double						   m_feedEntryDist;
		bool                           m_orientationInMCS;
		bool                           m_potentialSurfaceCPInMCS;
		bool                           m_potentialSurfaceCPOrientInMCS;
		bool                           m_sideOrientationInMCS;
		bool                           m_avoidRotationAxisDirectionChange;

		mwRoboticMXPParamPtr		   m_robParamPtr;
		//#############################################################################
		void Copy(const mwMXPParam &toCopy);
		//#############################################################################
#pragma warning(pop)
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwMXPParam> mwMXPParamPtr;
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWMXPPARAM_HPP_
