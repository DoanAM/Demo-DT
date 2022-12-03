// (C) 2008-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWPOSTEDUTILS_HPP_
#define MW_MWPOSTEDUTILS_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwPostedMove.hpp"
#include "mwEnrichedPostedTP.hpp"
#include "mwMatrix.hpp"
#include "mwPostedTP.hpp"
#include "mwMemoryPoolList.hpp"
#include "mwMachDef.hpp"
#include "mwPostCommonDefinitions.hpp"
#include "mwPostUpdateHandler.hpp"
#include "mwMachDefUtils.hpp"
#include "mwArcAttribute.hpp"
#include "mwTurningToolHelper.hpp"
#include "mwCoordinateSystem.hpp"
#include "mwTurningPostUtils.hpp"
#include "mwResourceIntf.hpp"

class mwEnrichedPostedMove;
namespace cadcam
{
	class mwTool;
}

namespace post
{
	class mwMXPParam;
	class MW_5AXUTIL_API mwPostedUtils
	{
	public:
		
		typedef cadcam::mwMatrix<double, 4, 4>   mwMatrix4d;
		typedef misc::mwAutoPointer<mwMatrix4d>  mwMatrix4dPtr;
		typedef cadcam::mwMatrix<double, 3, 3>   mwMatrix3d;
		typedef misc::mwAutoPointer<mwMatrix3d>  mwMatrix3dPtr;
		typedef std::vector<size_t>              indexPositions;
		typedef std::list< std::pair< int, misc::mwstring > > ListIntString;// The functions using the int-string pairs are deprecated. Please use the string-string variant.
		typedef std::list< std::pair< misc::mwstring, misc::mwstring > > ListStringString;

		class ThreadAttributeExtractor : public mwExtendedMoveAttributeVisitor
		{
		public:
			ThreadAttributeExtractor(const mwExtendedMoveAttributePtr extendedMoveAttribute);
			ThreadAttributeExtractor(const mwExtendedMoveAttributeList extendedMoveAttributes);
			misc::mwAutoPointer<mwThreadAttribute> GetThreadAttribute() const;
		private:
			virtual void Visit(const mwExtendedMoveAttribute& toVisit);
			virtual void Visit(const mwKeepPartsAttribute& toVisit);
			virtual void Visit(const mwAdditionalInfoAttribute &toVisit);
			virtual void Visit(const mwChuckJawsStateChangeAttribute &toVisit);
			virtual void Visit(const mwThreadAttribute& toVisit);
			virtual void Visit(const mwArcAttribute& toVisit);
		private:
			misc::mwAutoPointer<mwThreadAttribute>	m_threadAttribute;
		};
		
		enum CoordinateType
		{
			POSTEDMOVE_WITH_ABS_POS = 0,
			POSTEDMOVE_WITH_REL_POS,
			POSTEDMOVE_WITH_BOTH_POS
		};
		
		enum DisplayCoordinate
		{
			DISPLAY_ABSOLUTE_WITHOUT_TLC = 0,// "Absolute Machine Axis Values"      
			DISPLAY_ABSOLUTE_WITH_TLC = 1,// "Absolute Machine Axis Values (at Tool Tip)"
			DISPLAY_RELATVIE = 2,// "Relative to Workpiece Position Values (at Tool Tip)"
			DISPLAY_ONLY_BLK = 3,
			DISPLAY_BLK_AND_COMMENT = 4,
			DISPLAY_RELATVIE_WITH_TLC = 5,// "Relative to Workpiece Position Values"
			DISPLAY_GEOMETRY_AXIS_VALUE_RTCP_OFF = 6, // "Values of Tool Tip in Workpiece Coordinate System"
			DISPLAY_CONTACT_POINT_FOR_WORK_OFFSET = 7 // "Reference Point Offset in Tool Coordinates"
		};

		enum PostMessages
		{
			EXCEEDED_LIMITS_OF_MACHINE_FOR = 1,
			IF_CONTINUE_SOME_SETTINGS_WILL_BE_IGNORED = 2,
			ACTUAL_VAL_AND_MIN_CIRC_LIMIT_VAL = 3,
			AXIS_EQUALS_AND_MIN_VAL = 4,
			AXIS_EQUALS_AND_MAX_VAL = 5
		};

		struct AditionalPostedMoveInfo
		{
			bool addedOnPost;
			size_t originalMoveId;
		};

		struct Quaternion
		{
			Quaternion() 
			{
				x = 0;
				y = 0;
				z = 0;
				w = 1;
			}

			double x;
			double y;
			double z;
			double w;
		};
		
		static void GetArcNormalAndCenterInWorldCoordinateSystem(
			const post::mwMachDefPtr& machDef,
			const post::mwTranslationPos firstTrAxis,
			const post::mwTranslationPos secondTrAxis,
			const post::mwTranslationPos thirdTrAxis,
			const cadcam::mwPoint3d partOrigin,
			const post::mwPostedMove& move,
			cadcam::mwPoint3d& center,
			cadcam::mwVector3d& normal,
			const bool usePassedCenter = false);
		
		template <typename T>
		static const cadcam::mwTPoint3d<T> ComputeArcCenter(
			const cadcam::mwTPoint3d<T>& startPosition,
			const cadcam::mwTPoint3d<T>& endProj,
			const cadcam::mwTPoint3d<T>& normal,
			const T radius)
		{
			const T dist2 = ~(startPosition - endProj) / 2.0;
			const cadcam::mwTPoint3d<T> u = (endProj - startPosition).Normalized();
			const cadcam::mwTPoint3d<T> P = startPosition + u * (dist2);
			if (mathdef::is_eq(std::abs(radius), std::abs(dist2)))
				return P;
			const cadcam::mwTPoint3d<T> v = radius < 0 ? (u % normal).Normalized() : (normal % u).Normalized();
			const T h = sqrt(radius * radius - dist2 * dist2);
			return (P + v * h);
		}
		
		static mwEnrichedPostedMove PostedMoveToEnrichedMove(
			const mwPostedMovePtr &postedMove,
			const misc::mwstring &comment = _T(""),
			const bool isPhantom = false,
			const mwExtendedMoveAttributeList& extendedAttributes = mwExtendedMoveAttributeList(),
			const post::AdditionalFixedAxesPtr& additionalFixedAxesPtr = MW_NULL);
		
		static mwEnrichedPostedMove PostedMoveToEnrichedMove(
			const mwPostedMove &postedMove,
			const misc::mwstring &comment = _T(""),
			const bool isPhantom = false,
			const mwExtendedMoveAttributeList& extendedAttributes = mwExtendedMoveAttributeList(),
			const post::AdditionalFixedAxesPtr& additionalFixedAxesPtr = MW_NULL);
		
		static const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP> PostedTPToEnrichedTP(
			const mwPostedTP& postdTP);
	
		template <typename TPostedMoveType>
		static const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP> GetEnrichedTPFromPostedMoveList(
			const misc::mwAutoPointer< misc::mwMemoryPoolList<TPostedMoveType> >& listPtr);

		template <typename TPostedMoveType>
		static const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP> GetEnrichedTPFromMoveList(
			const misc::mwAutoPointer< misc::mwMemoryPoolList<TPostedMoveType> >& listPtr,
			const DisplayCoordinate displayCoordinate = DISPLAY_ABSOLUTE_WITHOUT_TLC,
			const mwMachDefPtr& machineDef = MW_NULL,
			const double TLC = 0);
		
		template <typename TPostedMoveType>
		static const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP> GetEnrichedTPFromMoveList(
			misc::mwAutoPointer< misc::mwMemoryPoolList<TPostedMoveType> >& listPtr,
			const DisplayCoordinate displayCoordinate = DISPLAY_ABSOLUTE_WITHOUT_TLC,
			bool clearList = false,
			const mwMachDefPtr& machineDef = MW_NULL,
			const double TLC = 0,
			const ListIntString& commentBlk = ListIntString(),
			const std::list<mwExtendedMoveAttributeList>& extendedAttributes = std::list<mwExtendedMoveAttributeList>(),
			const cadcam::mwPoint3d partOrigin = cadcam::mwPoint3d(0, 0, 0),
			const post::mwTranslationPos firstTrAxis = post::HEAD,
			const post::mwTranslationPos secondTrAxis = post::HEAD,
			const post::mwTranslationPos thirdTrAxis = post::HEAD,
			misc::mwAutoPointer<std::list<AditionalPostedMoveInfo> > additionalInfo = MW_NULL,
			const bool includeMoveIdx = true,
			const post::AdditionalFixedAxesPtr&  additionalFixedAxesPtr = MW_NULL,
			const cadcam::mwPoint3d& contactPointForWorkOffset = cadcam::mwPoint3d(0, 0, 0));
		
		template <typename TPostedMoveType>
		static const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP> GetEnrichedTPFromMoveList(
			misc::mwAutoPointer< misc::mwMemoryPoolList<TPostedMoveType> >& listPtr,
			const DisplayCoordinate displayCoordinate = DISPLAY_ABSOLUTE_WITHOUT_TLC,
			bool clearList = false,
			const mwMachDefPtr& machineDef = MW_NULL,
			const double TLC = 0,
			const ListStringString& commentList = ListStringString(),
			const std::list<mwExtendedMoveAttributeList>& extendedAttributes = std::list<mwExtendedMoveAttributeList>(),
			const cadcam::mwPoint3d partOrigin = cadcam::mwPoint3d(0, 0, 0),
			const post::mwTranslationPos firstTrAxis = post::HEAD,
			const post::mwTranslationPos secondTrAxis = post::HEAD,
			const post::mwTranslationPos thirdTrAxis = post::HEAD,
			misc::mwAutoPointer<std::list<AditionalPostedMoveInfo> > additionalInfo = MW_NULL,
			const bool includeMoveIdx = true,
			const post::AdditionalFixedAxesPtr&  additionalFixedAxesPtr = MW_NULL,
			const cadcam::mwPoint3d& contactPointForWorkOffset = cadcam::mwPoint3d(0, 0, 0));
		
		template <typename TPostedMoveType>
		static void FilterPostedArcMoves(
			misc::mwAutoPointer< misc::mwMemoryPoolList<TPostedMoveType> >& listPtr,
			const double maxSweepAngle = mathdef::MW_MAX_DOUBLE,
			const bool filterHelices = true,
			const bool filterArcs = true,
			const bool maxSplitSweepAngle = false,
			const bool useArcPlanes = false,
			const std::vector<cadcam::mwPoint3d>& arcPlaneNormals = std::vector<cadcam::mwPoint3d>());
		
		template<typename TMachineDef, typename TPostedMoveType>
		static const TPostedMoveType GetPostedMoveRetracted(
			const TMachineDef& machine,
			const TPostedMoveType& move,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			bool computeOrientation = false,
			const CoordinateType ct = POSTEDMOVE_WITH_BOTH_POS,
			const double minusOffset = 0/*don't use a negative value*/,
			const double rate = 0);
		
		static const double GetAngleBetweenTwoValues(
			double angle,
			const double min,
			const double max);
		
		static const double InterpolateAngles(const double s, const double e, const double k, const double nk);
		
		static const cadcam::mwPoint3d InterpolateDistance(
			const cadcam::mwPoint3d& A,
			const cadcam::mwPoint3d& B,
			const double k,
			const double nk);
		
		//!
			/*InterpolateByThresholdAngle
			If the difference between two consecutive rotation axis values differs by
			more than the /threshold amount, linear interpolation is done for all of the axes,
			inserting all of the needed intermediary moves into the source toolpath
			\param toolPath the source toolpath
			\param threshold rotation axis values differences over this value will trigger interpolation
			\param rotAxesPos define a vector with positions in axes names, eg: [3][4][5]
		*/
		static void InterpolateByThresholdAngle(
			cadcam::mwEnrichedPostedTP& toolPath,
			const float threshold,
			const indexPositions& rotAxesPos);
		
		//!
			/*FormatWorkpieceBasedCoordsAsString
			Return a string containing formatted workpiece based coordinates  for a posted move
			(used when choosed to display in machine simulator 'workpiece based' coordinates
			instead of absolute machine axis values
			\param crtIndex the index of current posted move
			\param postedMove the posted move to extract workpiece based coordinates from
			\return a formatted string containing workpiece based coordinates for a move
		*/
		static const misc::mwstring FormatWorkpieceBasedCoordsAsString(
			const int crtMoveIndex,
			const mwPostedMove& postedMove,
			const bool includeMoveIdx = true);
		
		//!
			/*FormatWorkpieceWithTLCBasedCoordsAsString
			Return a string containing formatted workpiece based coordinates with TLC (tool length compensation)  for a posted move
			(used when choosed to display in machine simulator 'workpiece based' coordinates
			instead of absolute machine axis values
			\param crtIndex the index of current posted move
			\param postedMove the posted move to extract workpiece based coordinates from
			\param tlc is the length of the tool
			\return a formatted string containing workpiece based coordinates for a move
		*/
		static const misc::mwstring FormatWorkpieceWithTLCBasedCoordsAsString(
			const int crtMoveIndex,
			const mwPostedMove& postedMove,
			const double tlc,
			const bool includeMoveIdx = true);
		
		//!
			/*FormatAbsoluteWithTLCBasedCoordsAsString
			Return a string containing formatted absolute with Tool Length Compensation based coordinates for a posted move
			\param crtIndex the index of current posted move
			\param postedMove the posted move to extract absolute based coordinates from
			\param partOrigin the translation of the toolpath from 0,0,0 machine position
			\param machineSystem the transformation from orthogonal system to machine system base on translation axis. See also OrthogonalSystem2MachineSystem
			\
			\return a formatted string containing workpiece based coordinates for a move
		*/
		static const misc::mwstring FormatAbsoluteWithTLCBasedCoordsAsString(
			const int crtMoveIndex,
			const mwPostedMove& postedMove,
			const mwMachDefPtr& machineDef,
			const double TLC,
			const bool includeMoveIdx = true);

		//!
			/*FormatToolTipFixedWorkpieceCoordsAsString
			Return a string containing Values of Tool Tip in Fixed Workpiece Coordinate System
			\param crtIndex the index of current posted move
			\param postedMove the posted move to extract absolute based coordinates from
			\param partOrigin the translation of the toolpath from 0,0,0 machine position
			\
			\return a formatted string containing fixed workpiece based coordinates for a move
		*/
		static const misc::mwstring FormatToolTipFixedWorkpieceCoordsAsString(
			const int crtMoveIndex,
			const mwPostedMove& postedMove,
			const mwMachDefPtr& machineDef,
			const cadcam::mwPoint3d partOrigin,
			const bool includeMoveIdx = true);
		
		static const misc::mwstring FormatContactPointForWorkOffsetAsString(
			const int crtMoveIndex,
			const mwPostedMove& postedMove,
			const bool includeMoveIdx,
			const cadcam::mwPoint3d& uvw,
			const mwMachDefPtr& machineDef,
			const double TLC,
			const cadcam::mwPoint3d partOrigin);
		
		static const misc::mwstring FormatPostedMoveRotaryAxis(
			const mwPostedMove& postedMove,
			const unsigned short precision4MoveCoord);
		
		const mwMachDef::mwMatrix4dPtr OrthogonalSystem2MachineSystem(
			cadcam::mwPoint3d x,
			cadcam::mwPoint3d y,
			cadcam::mwPoint3d z,
			mwTranslationPos xAxisPos,
			mwTranslationPos yAxisPos,
			mwTranslationPos zAxisPos);
		
		static unsigned int GetNumberOfAxes(const mwPostedMove& postedMove);
		
		static const mwMatrix4d CreateHolderTranformation(
			const mwMachDef& machineDef,
			const double toolLengthCompensation);
		
		static const cadcam::mwPoint3d AbsolutePosWithoutTLC2AbsolutePosWithTLC(
			const mwPostedMove& postedMove,
			const mwMachDefPtr& machineDef,
			const double TLC);
		
		static const cadcam::mwVector3d GetCurrentSpindleDirection(
			const mwPostedMove& postedMove,
			const mwMachDefPtr& machineDef);
		
		static bool ComputeMachPosComponent(mwPosted5axMove& move,
			const mwMachDefPtr& machineDefinition,
			const cadcam::mwTPoint3d< double >& partOrigin,
			const double& toolLengthCompensation,
			const cadcam::mwHomogenousMatrixd& alignMatrix,
			const bool isLeadingToolLathe = false,
			const bool yFake = false);

		static bool ComputeMachPosComponent(mwPosted6axMove& move,
			const mwMachDefPtr& machineDefinition,
			const cadcam::mwTPoint3d< double >& partOrigin,
			const double& toolLengthCompensation,
			const cadcam::mwHomogenousMatrixd& alignMatrix,
			const bool isLeadingToolLathe,
			const bool yFake);

		//! FormatString
			/*Formats a real value as a string, giving a certain precision and
			number of digits to be displayed in string
			\param value the real value to be formatted as string
			\param nrDigits number of digits to be displayed
			\param precision the number of digits after decimal point to be displayed
		*/
		static const misc::mwstring FormatString(
			const double value,
			const int nrDigits,
			const unsigned short precision);

		//! returns the tool length compensation 
			/* it use the following conventions:
			- for wire tools it returns 0
			- for lathe tools and tools having cutting part as mesh, it returns the length of the tool without cutting part
			- for the other tools it returns full length of the tool
		*/
		static const double GetToolLengthCompensationInMWConvention(const cadcam::mwTool& tool,
			const double notused = 0.);

		static const double SyncRoboticPostMachine(const cadcam::mwTool& tool,
			const double notused = 0.);

		static void ApplyTrOnMove(
			mwPosted5axMove& move,
			const mwMachDef::mwMatrix4dPtr& matrixPtr,
			const mwMachDefPtr& machDef,
			const double previousAngle0,
			const double previousAngle1);

		static void ApplyTrOnMove(
			mwPosted6axMove& move,
			const mwMachDef::mwMatrix4dPtr& matrixPtr,
			const mwMachDefPtr& machDef,
			const double previousAngle0,
			const double previousAngle1,
			const double previousAngle2);

		static const double DistPointLine(const cadcam::mwPoint3d& x0, const cadcam::mwPoint3d& x1, const cadcam::mwPoint3d& x2);
		
		static void ComputeEulerAngles(
			const cadcam::mwVector3d& u,
			const cadcam::mwVector3d& v,
			double& spa,
			double& spb,
			double& spc,
			bool toDegree = true);
		
		static void ComputeEulerAngles(
			const cadcam::mwMatrix<double, 3, 3>& rot3Matrix,
			double& spa,
			double& spb,
			double& spc,
			bool toDegree = true);

		static void EliminateMachineShifts(mwMachDefPtr& machDef);
		
		static void EliminateMachineShifts(mwMachDef& machDef);
		
		static const mwPosted3axMove GetMultipleRetractsMove(
			const mw3axMachDef& machDef,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwPosted3axMove& move,
			const double retractDistance,
			const bool additionalRetractToolAtMax,
			const double additionalRetractDistance,
			const cadcam::mwPoint3d& additionalRetractDirection,
			const double rate = 0);
		
		static const mwPosted4axMove GetMultipleRetractsMove(
			const mw4axMachDef& machDef,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwPosted4axMove& move,
			const double retractDistance,
			const bool additionalRetractToolAtMax,
			const double additionalRetractDistance,
			const cadcam::mwPoint3d& additionalRetractDirection,
			const double rate = 0);
		
		static const mwPosted5axMove GetMultipleRetractsMove(
			const mw5axMachDef& machDef,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwPosted5axMove& move,
			const double retractDistance,
			const bool additionalRetractToolAtMax,
			const double additionalRetractDistance,
			const cadcam::mwPoint3d& additionalRetractDirection,
			const double rate = 0);
		
		static const mwPosted6axMove GetMultipleRetractsMove(
			const mw6axCSMachDef& machDef,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwPosted6axMove& move,
			const double retractDistance,
			const bool additionalRetractToolAtMax,
			const double additionalRetractDistance,
			const cadcam::mwPoint3d& additionalRetractDirection,
			const double rate = 0);
		
		static const post::mw5axMachDef Extract5axMachDefFrom5plus1MachDef(const post::mw6axMachDef& machDef);
		
		static const post::mwMachDef::mwMatrix4d ExtractTableTransformationMatrixFrom5plus1MachDef(
			const post::mw6axMachDef& machDef,
			const cadcam::mwPoint3d& partOrigin = cadcam::mwPoint3d(0, 0, 0));
		
		static const bool CheckLicense(mwMXPParam& params);
	
		static const mwMatrix4d ConvertSpindleDirAndCuttingDirToHolderTranformation(const mwMachDef& machineDef);
		static const mwMatrix4d ConvertSpindleDirAndCuttingDirToHolderTranformation(const mwSpindle& spindle);
		static const mwMatrix4dMap ConvetSpindlesToMatrixMap(const mwSpindles& spindles);

		static const bool CheckGimbalLock(const post::mwMatrix4d& matrix);

		static void SetProcess(
			mwPostUpdateHandler* updateHandler,
			const mwPostUpdateHandler::ProgressDescription::postTPCreatorID& processType,
			unsigned int& prevProgressValue,
			const unsigned int intervalPos,
			const size_t intervalSize);

		static const post::mwPosted5axMove::anglesState ConvertAngleState(const mwPosted6axMove& moveAngleToConvert);
		static const post::mwPosted6axMove::anglesState ConvertAngleState(const mwPosted5axMove& moveAngleToConvert);

		static void VisualizePostMachinePossibleToolDirections(const mwMachDefPtr& machDef, const double angleTol = 1.0);

		MW_DEPRECATED("Deprecated in 2021.04, please use ShiftToolReferencePoint")
		static cadcam::mwPoint3d GetContactPointForWorkOffset(
			const post::mwPostedMove& move,
			const cadcam::mwPoint3d& uvw,
			const mwMachDefPtr& machineDef,
			const double TLC = 0,
			const cadcam::mwPoint3d partOrigin = cadcam::mwPoint3d(0, 0, 0),
			const bool isOrientationInMCS = true,
			const bool isSideOrientationInMCS = true);

		static cadcam::mwPoint3d ShiftToolReferencePoint(
			const post::mwPostedMove& move,
			const cadcam::mwPoint3d& shift,
			const mwMachDefPtr& machineDef,
			const double TLC = 0,
			const cadcam::mwPoint3d partOrigin = cadcam::mwPoint3d(0, 0, 0),
			const bool isOrientationInMCS = true,
			const bool isSideOrientationInMCS = true);

		static const cadcam::mwPoint3d GetToolTipFixedWorkCoord(
			const post::mwPostedMove& move,
			const mwMachDefPtr& machineDef,
			const cadcam::mwPoint3d partOrigin = cadcam::mwPoint3d(0.0f, 0.0f, 0.0f));

		static const std::vector<size_t> ComputeOptimalStreamingChunkSizes(const cadcam::mwToolPath& toolp, const size_t desiredSize);

		static void AddThreadingInfosToEnrichedTP(const misc::mwAutoPointer<cadcam::mwEnrichedPostedTP>& enrichedTP,
			const mwMachDefPtr& machineDefPtr,
			const size_t noOfThreads,
			const double pitch,
			const bool incrementalPitch,
			const double pitchIncrement);

		static mwMatrix4d CreateTurningHolderTransform(
			const misc::mwAutoPointer <cadcam::mwTool>& toolInfoPtr,
			const bool isSpindleRotationClockwise,
			const cadcam::mwTurningToolHelper::ReferencePoint& referencePoint,
			const cadcam::mwPoint3d& customReferencePoint,
			const double toolTiltAngle,
			const cadcam::mwCoordinateSystem& workingCoordSystem,
			const post::mwMachDefPtr& postMachDefPtr,
			double toolLengthCompensation,
			bool enablePostTipPointTranslation = false,
			const cadcam::mwVector3d& toolpathDirectionVector = cadcam::mwVector3d(0,0,1));

		static mwMatrix4d ConvertWorkingCoordSystemToAlignMatrix(const cadcam::mwCoordinateSystem& workingCoordSystem);

		static cadcam::mwVector3d GetToolpathDirectionVectorForTurningPosting(
			const post::mwMachDefPtr& machDefPtr,
			const cadcam::toolpath& toolp,
			const mwMatrix4dPtr& alignMatrix);

		static bool IsOrientationCompatibleWithMachine(
			const cadcam::mwVector3d& orientation, 
			const mwMachDefPtr& machDefPtr,
			const double poleAngleDetectToolInDeg,            
			const double toolpathTol,
			const mwMatrix4dPtr alignMatrixPtr = MW_NULL,
			const cadcam::mwVector3d& sixAxCuttingDirection = cadcam::mwVector3d(1,0,0));

		static Quaternion EulerToQuaternion(const vector3d& value, post::mwPostedNaxMove::EulerAngleType type);

		static const misc::mwstring GetExceedLimitMsg(
			const post::mwPostLimitType& limitType,
			const post::mwMachDef& machDef,
			const std::vector<misc::mwstring>& axisNames,
			const bool addQuestion = false,
			const misc::mwstring& message = _T(""),
			const misc::mwResourceIntf* resource = MW_NULL);

		static const misc::mwstring ConvertPostMessageIdToText(const PostMessages& messageId);

	private:	
		
		mwPostedUtils() {}; //  ALLOW ONLY STATIC FUNCTIONS
	
	};//end class mwPostedUtils
}// end namespace post

#endif