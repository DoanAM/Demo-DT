// (C) 2014-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWCUTTERCOMPENSATION_HPP_
#define MW_MWCUTTERCOMPENSATION_HPP_
#include "mwCrcSegment.hpp"
#include "mwAutoPointer.hpp"
#include "mwToolPath.hpp"

/*
	-This class implements the API for cutter radius compensation
	-Cutter compensation algorithm can compensate a 3D toolpath if all orientations are equal 
	and turning operations (with lathe tools) if all moves and orientations are contained in one plane, 
	and this plane also contains machine spindle direction and table rotation direction.
	-Avoid having a compensation value greater than half of the smallest segment of the tool path to be compensated. 
	This is not the use case for which this algorithm is designed and the output may not be correct.
*/

class MW_5AXUTIL_API mwCutterCompensation
{
public:
	// defines direction of compensation: LEFT or RIGHT
	enum CutterCompensationDirection
	{
		CC_LEFT = 0,
		CC_RIGHT = 1
	};

	enum CutterCompensationEdgeType
	{
		ROUND = 0,
		SHARP
	};

	enum CutterCompensationLookAheadType
	{
		GLOBAL = 0,
		LOCAL
	};

	// defines Marker Area to start/stop compensation - solution (1) to define a compensation area
	struct AreaMarker
	{
		AreaMarker(
			size_t passNumber,
			size_t sliceNumber,
			size_t sectionNumber,
			size_t sectionFitNumber,
			size_t moveNumber)
				: m_passNumber(passNumber)
				, m_sliceNumber(sliceNumber)
				, m_sectionNumber(sectionNumber)
				, m_sectionFitNumber(sectionFitNumber)
				, m_moveNumber(moveNumber)
		{
		};

		size_t m_passNumber;
		size_t m_sliceNumber;
		size_t m_sectionNumber;
		size_t m_sectionFitNumber;
		size_t m_moveNumber;  // move number in current section fit
	};

	// defines a single Marker Area to be compensated, 
	// start is where the compensation area starts and stop is where compensation area stops
	struct CompensationMarkersArea
	{
		CompensationMarkersArea(
			AreaMarker start,
			AreaMarker stop,
			double distance,
			CutterCompensationDirection direction)
			: m_start(start)
			, m_stop(stop)
			, m_distance(distance)
			, m_direction(direction)
		{
		};

		AreaMarker m_start;
		AreaMarker m_stop;
		double m_distance;
		CutterCompensationDirection m_direction;
	};

	// defines a vector of compensation Marker Area
	typedef std::vector<CompensationMarkersArea> CompensationMarkersAreaVector;

	// defines a single Move Area to be compensated - solution (2) to define a compensation area
	typedef cadcam::mwCNCMove                     mwCNCMove;
	typedef cadcam::movePtr 			          movePtr;
	// start is where the compensation area starts and stop is where compensation area stops
	struct CompensationMovesArea
	{
		CompensationMovesArea(
			movePtr start,
			movePtr stop,
			double distance,
			CutterCompensationDirection direction)
			: m_start(start)
			, m_stop(stop)
			, m_distance(distance)
			, m_direction(direction)
		{
		};

		movePtr m_start;
		movePtr m_stop;
		double m_distance;
		CutterCompensationDirection m_direction;
	};

	// defines a vector of compensation Move Area
	typedef std::vector<CompensationMovesArea>  CompensationMovesAreaVector;

	typedef misc::mwAutoPointer<std::vector<mwCrcMarker> > CrcMarkerVectorPtr;
	typedef std::vector<size_t> ReferenceVector;
	typedef std::vector<misc::mwAutoPointer<cadcam::mwTPSectionFit> > TPSectionFitPtrVector;


	//! Constructor
	/*!
		\param tp :	contain toolpath to be compensated
		\param precision :	defines precision
	*/
	mwCutterCompensation(
		cadcam::toolpath& tp, 
		const double precision,
		const CutterCompensationEdgeType edgesType = ROUND,
		const CutterCompensationLookAheadType filterType = GLOBAL,
		bool usingFilter = true);

	//! Virtual destructor
	virtual ~mwCutterCompensation();

	//! Call this function to apply compensation on current toolpath
	/*!
		\param operationNumber : defines operation number
		\param latheTool : activate compensation for turning operations: (with lathe tools) if all moves and orientations must be contained in one plane,
			and this plane also contain machine spindle direction and table rotation direction, otherwise an exception will be thrown
	*/
	void Process(const long operationNumber = 1, const bool latheTool = false);

	//! Call this function to start compensation for next move that will be added to toolpath
	/*! Solution (3) to define a compensation area
		\param distance : defines distance of compensation, this must be positive.
		\param direction : defines direction of compensation (LEFT of RIGHT).
		\param operationNumber : defines current operation number
		Note: Can be used CompensationMarkersAreaVector or CompensationMovesAreaVector or MakeNextMoveCompensated/MakeNextMoveUnCompensated but not all of them
	*/
	void MakeNextMoveCompensated(const double distance, const CutterCompensationDirection direction, const long operationNumber = 1);

	//! Call this function to end compensation for next move that will be added to toolpath.
	/*! Solution (3) to define a compensation area
	*/
	void MakeNextMoveUnCompensated();

	// Only one compensation area definition type can be used 
	// (1) CompensationMarkersAreaVector or 
	// (2) CompensationMovesAreaVector or 
	// (3) MakeNextMoveCompensated/MakeNextMoveUnCompensated
	void SetCompensationArea(const CompensationMarkersAreaVector& compensationMarkersAreaVector);
	// Only one compensation area definition type can be used 
	// (1) CompensationMarkersAreaVector or 
	// (2) CompensationMovesAreaVector or 
	// (3) MakeNextMoveCompensated/MakeNextMoveUnCompensated
	void SetCompensationArea(const CompensationMovesAreaVector& compensationMovesAreaVector);

	//! Get precision used
	/*
		\return double representing the precision
	*/
	const double GetPrecision() const;

	//! Get the section fits found within pass, slice and section described by the sent parameters
	/*!
		\param passNumber : the number of the pass
		\param sliceNumber : the number of the slice
		\param sectionNumber : the number of the section
		\return an autopointer to a vector containing all the section fits corresponding to the sent parameters
	*/
	TPSectionFitPtrVector GetSectionFits(const size_t passNumber = 0, const size_t sliceNumber = 0, const size_t sectionNumer = 0) const;

	//! Get the markers
	/*
		\return an autopointer to a vector of markers
	*/
	const CrcMarkerVectorPtr& GetMarkerVectorPtr() const;
	
	//! Get a vector with markers' reference move indexes
	/*
		\return a vector containing all markers' reference move indexes
	*/
	const ReferenceVector GetReferenceVector() const;

	//! Get the toolpath
	/*
		\return the toolpath used by the cutter compensation, the toolpath that is passed on constructor
	*/
	cadcam::toolpath& GetToolpath();

	//!
	/*
		\return CutterCompensationEdgeType: ROUND/SHARP
	*/
	const CutterCompensationEdgeType GetEdgesType() const;

	//!
	/*
		\return CutterCompensationLookAheadType: GLOBAL/LOCAL
	*/
	const CutterCompensationLookAheadType GetLookAheadType() const;

	//!
	/*
		\return FILTER status: ON/OFF
	*/
	const bool GetIsUsingFilter() const;

protected:

	enum CompensationAreaType
	{
		NOT_DEFINED = -1,
		DEFAULT_COMPENSATION_TYPE = 0,
		MARKERS_COMPENSATION_TYPE = 1,
		MOVES_COMPENSATION_TYPE = 2
	};

	typedef std::vector<mwCrcSegment> CrcSegmentVector;

	const mwCrcMarker GetToolPathPosition(const cadcam::toolpath& tp) const;

	void ConvertFromMarkersToDefaultType();
	void ConvertFromMovesToDefaultType();

	mwCrcMarker GetMarkerUsingMove(const movePtr& move);

	bool AreMarkersOrdered(const mwCrcMarker& firstMarker, const mwCrcMarker& secondMarker);

#pragma warning(push)
#pragma warning(disable:4251)
	cadcam::toolpath& m_tp;
	double m_precision;

	CrcSegmentVector m_segmentVector;

	CrcMarkerVectorPtr m_markerPtr;

	bool m_isCutterCompensationActive;

	CompensationAreaType m_compensationAreaType;

	CompensationMarkersAreaVector m_compensationMarkersAreaVector;
	CompensationMovesAreaVector m_compensationMovesAreaVector;

	CutterCompensationEdgeType m_edgesType;
	CutterCompensationLookAheadType m_filterType;
	bool m_usingFilter;

#pragma warning(pop)

private:
	mwCutterCompensation& operator = (const mwCutterCompensation&) { return *this; }// avoid warning c4512
};

typedef misc::mwAutoPointer<mwCutterCompensation> mwCutterCompensationPtr;
#endif	//	MW_MWCUTTERCOMPENSATION_HPP_
