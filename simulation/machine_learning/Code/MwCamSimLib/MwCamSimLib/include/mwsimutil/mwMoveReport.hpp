// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVEREPORT_HPP_
#define MW_MWMOVEREPORT_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

#include <bitset>

namespace cadcam
{
class mwMoveSwarfReport;
class mwMoveGeodesicReport;
class mwMoveGrindingReport;
class mwMoveExtrusionReport;
class mwMoveEngagementReport;
class mwMoveDrillingReport;
class mwMoveWeldingReport;
class mwMoveLayerTimeReport;
class mwMoveAdaptiveRoughReport;
class mwCutterRadiusCompensationReport;
class mwMoveHoleMakingReport;
class mwMoveAdditiveFdmReport;
class mwLinkInterpolationReport;

// This class contains all possible reports which can be attached to a move after a toolpath
// calculation
class MW_5AXUTIL_API mwMoveReport
{
public:
	typedef misc::mwAutoPointer<mwMoveReport> Ptr;

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///	false otherwise
	const bool operator==(const mwMoveReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///	false otherwise
	const bool operator!=(const mwMoveReport& toCompare) const;

	/// Deep-copy a given report into this object
	///
	///	@param toCopy is input report which will  be deep-copied in this object
	void DeepCopy(const mwMoveReport& toCopy);

	/// Gets Swarf report
	///
	///	@return auto-pointer to Swarf report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveSwarfReport>& GetSwarfReport() const;

	/// Sets Swarf report
	///
	///	@param toSet auto-pointer to Swarf report to be set, can be NULL if such report doesn't
	///exist
	void SetSwarfReport(const misc::mwAutoPointer<mwMoveSwarfReport>& toSet);

	/// Gets Geodesic report
	///
	///	@return auto-pointer to Geodesic report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveGeodesicReport>& GetGeodesicReport() const;

	/// Sets Geodesic report
	///
	///	@param toSet auto-pointer to Geodesic report to be set, can be NULL if such report doesn't
	///exist
	void SetGeodesicReport(const misc::mwAutoPointer<mwMoveGeodesicReport>& toSet);
	/// Gets Adaptive Roughing report
	///
	///	@return auto-pointer to Adaptive Roughing report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveAdaptiveRoughReport>& GetAdaptiveRoughingReport() const;
	/// Sets Adaptive Roughing report
	///
	///	@param toSet auto-pointer to Adaptive Roughing report to be set, can be NULL if such report
	///doesn't exist
	void SetAdaptiveRoughingReport(const misc::mwAutoPointer<mwMoveAdaptiveRoughReport>& toSet);
	/// Gets Grinding report
	///
	///	@return auto-pointer to Grinding report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveGrindingReport>& GetGrindingReport() const;

	/// Sets Grinding report
	///
	///	@param toSet auto-pointer to Grinding report to be set, can be NULL if such report doesn't
	///exist
	void SetGrindingReport(const misc::mwAutoPointer<mwMoveGrindingReport>& toSet);

	/// Gets Extrusion report
	///
	///	@return auto-pointer to Extrusion report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveExtrusionReport>& GetExtrusionReport() const;

	/// Sets Extrusion report
	///
	///	@param toSet auto-pointer to Extrusion report to be set, can be NULL if such report doesn't
	///exist
	void SetExtrusionReport(const misc::mwAutoPointer<mwMoveExtrusionReport>& toSet);

	void SetEngagementReport(const misc::mwAutoPointer<mwMoveEngagementReport>& toSet);
	const misc::mwAutoPointer<mwMoveEngagementReport>& GetEngagementReport() const;

	void SetLayerTimeReport(const misc::mwAutoPointer<mwMoveLayerTimeReport>& toSet);
	const misc::mwAutoPointer<mwMoveLayerTimeReport>& GetLayerTimeReport() const;

	/// Gets Drilling report
	///
	///	@return auto-pointer to Drilling report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveDrillingReport>& GetDrillingReport() const;

	/// Sets Drilling report
	///
	///	@param toSet auto-pointer to Drilling report to be set, can be NULL if such report doesn't
	///exist
	void SetDrillingReport(const misc::mwAutoPointer<mwMoveDrillingReport>& toSet);

	/// Gets Welding report report
	///
	///	@return auto-pointer to Welding report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveWeldingReport>& GetWeldingReport() const;

	/// Sets Welding report
	///
	///	@param toSet auto-pointer to Welding report to be set, can be NULL if such report doesn't
	///exist
	void SetWeldingReport(const misc::mwAutoPointer<mwMoveWeldingReport>& toSet);

	/// Gets Link move report report
	///
	///	@return auto-pointer to Link move report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwCutterRadiusCompensationReport>& GetCutterRadiusCompensationReport()
		const;

	/// Sets Link move report
	///
	///	@param toSet auto-pointer to Link move report to be set, can be NULL if such report doesn't
	///exist
	void SetCutterRadiusCompensationReport(
		const misc::mwAutoPointer<mwCutterRadiusCompensationReport>& toSet);

	/// Gets HoleMaking report
	///
	///	@return auto-pointer to HoleMaking report, can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveHoleMakingReport>& GetHoleMakingReport() const;

	/// Sets HoleMaking report
	///
	///	@param toSet auto-pointer to HoleMaking move report to be set
	void SetHoleMakingReport(const misc::mwAutoPointer<mwMoveHoleMakingReport>& toSet);

	/// Gets additive fdm report
	///
	///	@return auto-pointer to  additive fdm report
	///		can be NULL if such report doesn't exist
	const misc::mwAutoPointer<mwMoveAdditiveFdmReport>& GetAdditiveFdmReport() const;

	/// Sets  additive fdm report
	///
	///	@param additiveFdmReport auto-pointer to a additive fdm report to be set
	void SetAdditiveFdmReport(
		const misc::mwAutoPointer<mwMoveAdditiveFdmReport>& additiveFdmReport);

	void SetLinkInterpolationReport(const misc::mwAutoPointer<mwLinkInterpolationReport>& toSet);
	const misc::mwAutoPointer<mwLinkInterpolationReport>& GetLinkInterpolationReport() const;

private:
#pragma warning(push)
#pragma warning(disable : 4251)
	misc::mwAutoPointer<mwMoveSwarfReport> m_swarfReport;
	misc::mwAutoPointer<mwMoveGeodesicReport> m_geodesicReport;
	misc::mwAutoPointer<mwMoveGrindingReport> m_grindingReport;
	misc::mwAutoPointer<mwMoveExtrusionReport> m_extrusionReport;
	misc::mwAutoPointer<mwMoveEngagementReport> m_engagementReport;
	misc::mwAutoPointer<mwMoveDrillingReport> m_drillingReport;
	misc::mwAutoPointer<mwMoveWeldingReport> m_weldingReport;
	misc::mwAutoPointer<mwMoveLayerTimeReport> m_layerTimeReport;
	misc::mwAutoPointer<mwMoveAdaptiveRoughReport> m_adaptiveRoughingReport;
	misc::mwAutoPointer<mwCutterRadiusCompensationReport> m_cutterRadiusCompensationReport;
	misc::mwAutoPointer<mwMoveHoleMakingReport> m_holeMakingReport;
	misc::mwAutoPointer<mwMoveAdditiveFdmReport> m_additiveFdmReport;
	misc::mwAutoPointer<mwLinkInterpolationReport> m_linkInterpolationReport;
#pragma warning(pop)
};

/// SwarfMilling calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveSwarfReport
{
public:
	typedef misc::mwAutoPointer<mwMoveSwarfReport> Ptr;
	mwMoveSwarfReport();

	/// Constructor with arguments
	///
	///	@param contactLineLength is contact line length
	///	@param residualMaterial is residual material at the tool position
	///	@param undercut is undercut at the tool position
	mwMoveSwarfReport(
		const double& contactLineLength, const double& residualMaterial, const double& undercut);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveSwarfReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveSwarfReport& toCompare) const;

	/// Get contact line length
	///
	///	@return contact line length
	const double& GetContactLineLength() const;

	/// Set contact line length
	///
	///	@param toSet is contact line length to be set
	void SetContactLineLength(const double& toSet);

	/// Get residual material
	///
	///	@return residual material
	const double& GetResidualMaterial() const;

	/// Set residual material
	///
	///	@param toSet is residual material to be set
	void SetResidualMaterial(const double& toSet);

	/// Get undercut
	///
	///	@return undercut
	const double& GetUndercut() const;

	/// Set undercut
	///
	///	@param toSet is undercut to be set
	void SetUndercut(const double& toSet);

private:
	double m_contactLineLength;
	double m_residualMaterial;
	double m_undercut;
};

/// Geodesic calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveGeodesicReport
{
public:
	typedef misc::mwAutoPointer<mwMoveGeodesicReport> Ptr;

	/// Default constructor
	mwMoveGeodesicReport();

	/// Constructor with arguments
	///
	///	@param focusWidthLeftSide is focus width for left side
	///	@param focusWidthRightSide is focus width for right side
	mwMoveGeodesicReport(const double& focusWidthLeftSide, const double& focusWidthRightSide);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveGeodesicReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveGeodesicReport& toCompare) const;

	/// Get focus width for left side
	///
	///	@return focus width for left side
	const double& GetFocusWidthLeftSide() const;

	/// Set focus width for left side
	///
	///	@param toSet is  focus width for left side to be set
	void SetFocusWidthLeftSide(const double& toSet);

	/// Get focus width for right side
	///
	///	@return focus width for right side
	const double& GetFocusWidthRightSide() const;

	/// Set focus width for right side
	///
	///	@param toSet is  focus width for right side to be set
	void SetFocusWidthRightSide(const double& toSet);

private:
	double m_focusWidthLeftSide;
	double m_focusWidthRightSide;
};

/// Adaptive roughing calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveAdaptiveRoughReport
{
public:
	enum Direction
	{
		CLIMB,
		CONVENTIONAL
	};
	typedef misc::mwAutoPointer<mwMoveAdaptiveRoughReport> Ptr;

	/// Default constructor
	mwMoveAdaptiveRoughReport();

	/// Constructor with arguments
	///
	///	@param dir is climb or conventional direction
	mwMoveAdaptiveRoughReport(const Direction& dir);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveAdaptiveRoughReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveAdaptiveRoughReport& toCompare) const;

	/// Get climb or conventional direction
	///
	///	@return climb or conventional direction
	const Direction& GetDirection() const;

	/// Set direction
	///
	///	@param toSet is  climb or conventional direction to be set
	void SetDirection(const Direction& toSet);

private:
	Direction m_dir;
};

/// Grinding calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveGrindingReport
{
public:
	typedef misc::mwAutoPointer<mwMoveGrindingReport> Ptr;

	/// Default constructor
	mwMoveGrindingReport();

	/// Constructor with arguments
	///
	///	@param excessMaterial is excess material
	mwMoveGrindingReport(const double& excessMaterial);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveGrindingReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveGrindingReport& toCompare) const;

	/// Get excess material
	///
	///	@return excess material
	const double& GetExcessMaterial() const;

	/// Set excess material
	///
	///	@param toSet is excess material to be set
	void SetExcessMaterial(const double& toSet);

private:
	double m_excessMaterial;
};

/// Extrusion calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveExtrusionReport
{
public:
	typedef misc::mwAutoPointer<mwMoveExtrusionReport> Ptr;

	/// Default constructor
	mwMoveExtrusionReport();

	/// Parameterized constructor
	mwMoveExtrusionReport(const double& extrusionVolume);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveExtrusionReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveExtrusionReport& toCompare) const;

	/// Get extrusion volume
	///
	///	@return extrusion volume
	const double& GetExtrusionVolume() const;

	/// Set extrusion volume
	///
	///	@param toSet is extrusion volume to be set
	void SetExtrusionVolume(const double& toSet);

private:
	double m_extrusionVolume;
};

/// Extrusion calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwMoveAdditiveFdmReport
{
public:
	typedef misc::mwAutoPointer<mwMoveAdditiveFdmReport> Ptr;

	mwMoveAdditiveFdmReport();

	mwMoveAdditiveFdmReport(const mwMoveAdditiveFdmReport&);

	mwMoveAdditiveFdmReport& operator=(const mwMoveAdditiveFdmReport&);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	bool operator==(const mwMoveAdditiveFdmReport&) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	bool operator!=(const mwMoveAdditiveFdmReport&) const;

	/// The extrusion volume along the move
	///
	///	@return extrusion volume
	double GetExtrusionVolume() const;

	/// The extrusion volume along the move
	///
	///	@param extrusionVolume extrusion volume
	void SetExtrusionVolume(double extrusionVolume);

	/// This flag defines, if the position of the move is within a region of a corner.
	///
	///	@return corner mode flag
	bool GetCornerModeFlg() const;

	/// This flag defines, if the position of the move is within a region of a corner.
	///
	///	@param cornerMode corner mode flag
	void SetCornerModeFlg(bool cornerMode);

	/// This flag defines, if the position is at a corner.
	///
	///	@return corner flag
	bool GetCornerFlg() const;

	/// This flag defines, if the position is at a corner.
	///
	///	@param corner corner flag
	void SetCornerFlg(bool corner);

private:
	enum
	{
		CORNER_MODE = 0,
		CORNER = 1
	} Flags;
	double m_extrusionVolume;
	std::bitset<2> m_flags;
};

class MW_5AXUTIL_API mwMoveEngagementReport
{
public:
	typedef misc::mwAutoPointer<mwMoveEngagementReport> Ptr;

	mwMoveEngagementReport();
	mwMoveEngagementReport(double);
	const double GetEngagement() const;
	void SetEngagement(double);
	const bool operator==(const mwMoveEngagementReport& toCompare) const;
	const bool operator!=(const mwMoveEngagementReport& toCompare) const;

private:
	double m_engagement;
};

class MW_5AXUTIL_API mwMoveLayerTimeReport
{
public:
	typedef misc::mwAutoPointer<mwMoveLayerTimeReport> Ptr;
	mwMoveLayerTimeReport();
	mwMoveLayerTimeReport(const bool);
	const bool IsLessThanXSecondsBeforeLayerEnd() const;
	void SetBeforeFlag(const bool);
	const bool operator==(const mwMoveLayerTimeReport& toCompare) const;
	const bool operator!=(const mwMoveLayerTimeReport& toCompare) const;

private:
	bool m_isBefore;
};

/// Drilling calculation report attached to a move after a drilling toolpath calculation
class MW_5AXUTIL_API mwMoveDrillingReport
{
public:
	typedef misc::mwAutoPointer<mwMoveDrillingReport> Ptr;

	/// Default constructor
	mwMoveDrillingReport();

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveDrillingReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveDrillingReport& toCompare) const;

	/// Gets flag which tells if move associated with this report is drilling start point
	///
	///	@return flag if this is drilling start point (first point of hole to be drilled)
	const bool& GetDrillStartFlg() const;

	/// Sets flag which tells if move associated with this report is drilling start point
	///
	///	@param toSet is flag to be set
	void SetDrillStartFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is drilling end point
	///
	///	@return flag if this is drilling end point (last point of the drilled hole)
	const bool& GetDrillEndFlg() const;

	/// Sets flag which tells if move associated with this report is drilling end point
	///
	///	@param toSet is flag to be set
	void SetDrillEndFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is drill hole bottom point
	///
	///	@return flag if this is drill hole bottom point
	const bool& GetHoleBottomFlg() const;

	/// Sets flag which tells if move associated with this report is drill hole bottom point
	///
	///	@param toSet is flag to be set
	void SetHoleBottomFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is peck drill retraction point
	///
	///	@return flag if this is peck drill retraction point
	const bool& GetPeckRetractFlg() const;

	/// Sets flag which tells if move associated with this report is peck drill retraction point
	///
	///	@param toSet is flag to be set
	void SetPeckRetractFlg(const bool& toSet);

private:
	bool m_drillStartFlg;
	bool m_drillEndFlg;
	bool m_holeBottomFlg;
	bool m_peckRetractFlg;
};

/// Welding calculation report attached to a move after toolpath calculation for welding strategy
class MW_5AXUTIL_API mwMoveWeldingReport
{
public:
	typedef misc::mwAutoPointer<mwMoveWeldingReport> Ptr;  // auto-pointer to this class

	/// Default constructor
	mwMoveWeldingReport();

	/// Constructor with parameters
	mwMoveWeldingReport(
		const int layerIndex,
		const bool layerStartFlg,
		const bool layerEndFlg,
		const bool sliceStartFlg,
		const bool sliceEndFlg,
		const bool infillBoundaryStartFlg,
		const bool infillBoundaryEndFlg,
		const bool infillStartFlg,
		const bool infillEndFlg,
		const bool edgePointFlg,
		const double distanceToPreviousLayer,
		const double distanceToNextLayer,
		const int regionIndex,
		const bool regionStartFlg,
		const bool regionEndFlg);

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveWeldingReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveWeldingReport& toCompare) const;

	// !Gets 0-based layer index of the move associated with this report
	const int GetLayerIndex() const;

	/// Sets 0-based layer index of the move associated with this report
	void SetLayerIndex(const int& toSet);

	/// Gets flag which tells if move associated with this report is first move from a layer
	const bool GetLayerStartFlg() const;

	/// Sets flag which tells if move associated with this report is first move from a layer
	void SetLayerStartFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is last move from a layer
	const bool GetLayerEndFlg() const;

	/// Sets flag which tells if move associated with this report is last move from a layer
	void SetLayerEndFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is first move from a slice
	const bool GetSliceStartFlg() const;

	/// Sets flag which tells if move associated with this report is first move from a slice
	void SetSliceStartFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is last move from a slice
	const bool GetSliceEndFlg() const;

	/// Sets flag which tells if move associated with this report is last move from a slice
	void SetSliceEndFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is infill boundary start move
	const bool GetInfillBoundaryStartFlg() const;

	/// Sets flag which tells if move associated with this report is infill boundary start move
	void SetInfillBoundaryStartFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is infill boundary end move
	const bool GetInfillBoundaryEndFlg() const;

	/// Sets flag which tells if move associated with this report is infill boundary end move
	void SetInfillBoundaryEndFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is infill start move
	const bool GetInfillStartFlg() const;

	/// Sets flag which tells if move associated with this report is infill start move
	void SetInfillStartFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this report is infill end move
	const bool GetInfillEndFlg() const;

	/// Sets flag which tells if move associated with this report is infill end move
	void SetInfillEndFlg(const bool& toSet);

	/// Gets flag which tells if move associated with this point is at the edge (start/end) of a
	/// toolpath section
	bool GetEdgePointFlg() const;

	/// Sets flag which tells if move associated with this point is at the edge (start/end) of a
	/// toolpath section
	void SetEdgePointFlg(const bool toSet);

	/// Get distance to previous layer for move associated with this report
	double GetDistanceToPreviousLayer() const;

	/// Set distance to previous layer for move associated with this report
	void SetDistanceToPreviousLayer(const double toSet);

	/// Get distance to previous layer for move associated with this report
	double GetDistanceToNextLayer() const;

	/// Set distance to next layer for move associated with this report
	void SetDistanceToNextLayer(const double toSet);

	/// Gets 0-based region index where this point belongs to
	int GetRegionIndex() const;

	/// Sets 0-based region index where this point belongs to
	void SetRegionIndex(const int toSet);

	/// Gets flag which tells if this point is first point from a region
	bool GetRegionStartFlg() const;

	/// Sets flag which tells if this point is first point from a region
	void SetRegionStartFlg(const bool toSet);

	/// Gets flag which tells if this point is last point from a region
	bool GetRegionEndFlg() const;

	/// Sets flag which tells if this point is last point from a region
	void SetRegionEndFlg(const bool toSet);

private:
	// layer info
	int m_layerIndex;
	bool m_layerStartFlg;
	bool m_layerEndFlg;
	bool m_sliceStartFlg;
	bool m_sliceEndFlg;
	bool m_infillBoundaryStartFlg;
	bool m_infillBoundaryEndFlg;
	bool m_infillStartFlg;
	bool m_infillEndFlg;
	bool m_edgePointFlg;
	double m_distanceToPreviousLayer;
	double m_distanceToNextLayer;
	int m_regionIndex;
	bool m_regionStartFlg;
	bool m_regionEndFlg;
};

/// Link calculation report attached to a move after toolpath calculation for 5Axis links
class MW_5AXUTIL_API mwCutterRadiusCompensationReport
{
public:
	enum CutterRadiusCompensationMarkerType
	{
		CRC_LEFT = 0,
		CRC_RIGHT = 1,
		CRC_OFF = 2
	};
	typedef misc::mwAutoPointer<mwCutterRadiusCompensationReport> Ptr;

	/// Default constructor
	mwCutterRadiusCompensationReport();

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwCutterRadiusCompensationReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwCutterRadiusCompensationReport& toCompare) const;

	// !Gets cutter radius compensation marker type of the move associated with this report
	const CutterRadiusCompensationMarkerType GetCutterRadiusCompensationMarker() const;

	/// Sets cutter radius compensation marker type of the move associated with this report
	void SetCutterRadiusCompensationMarker(const CutterRadiusCompensationMarkerType& toSet);

private:
	CutterRadiusCompensationMarkerType m_cutterRadiusCompensationMarker;
};

/// Calculation report attached to a move after a HoleMaking calculation
class MW_5AXUTIL_API mwMoveHoleMakingReport
{
public:
	enum Strategy
	{
		HMS_DRILLING,
		HMS_THREAD_TAPPING,
		HMS_REAMING,
		HMS_THREAD_MILLING
	};

	enum SpindleDirection
	{
		SD_CLOCKWISE,
		SD_COUNTER_CLOCKWISE
	};

	enum CuttingDirection
	{
		CD_CLIMB,
		CD_CONVENTIONAL
	};

	typedef misc::mwAutoPointer<mwMoveHoleMakingReport> Ptr;

	/// Default constructor
	mwMoveHoleMakingReport();

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	const bool operator==(const mwMoveHoleMakingReport& toCompare) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	const bool operator!=(const mwMoveHoleMakingReport& toCompare) const;

	/// Get hole making strategy for the move associated with this report
	///
	///	@return hole making strategy
	Strategy GetStrategy() const;

	/// Set hole making strategy to the move associated with this report
	///
	///	@param toSet is hole making strategy to be set
	void SetStrategy(const Strategy toSet);

	/// GetHoleStartFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	start point where tool touches the material on the approach move to hole bottom
	/// From this point the tools moves inside the material till it reaches the hole bottom
	///	@return flag if this is start point of the hole
	bool GetHoleStartFlg() const;

	/// SetHoleStartFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	start point where tool touches the material on the approach move to hole bottom
	/// From this point the tools moves inside the material till it reaches the hole bottom
	///	@param toSet is hole start flag to be set
	void SetHoleStartFlg(const bool toSet);


	/// GetHoleEndFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	end point where tool touches the material on the retract move from hole bottom
	/// This point is reached when tool retracts from hole bottom to hole top
	///	@return flag if this is end point of the hole
	bool GetHoleEndFlg() const;

	/// SetHoleEndFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	end point where tool touches the material on the retract move from hole bottom
	/// This point is reached when tool retracts from hole bottom to hole top
	///	@param toSet is hole end flag to be set
	void SetHoleEndFlg(const bool toSet);

	/// GetHoleBottomFlg
	///
	/// Gets flag which tells if move associated with this report is hole bottom point
	/// This is the point inside the material at the drill depth distance from hole start and end
	/// points
	///	@return flag if this is bottom point of the hole
	bool GetHoleBottomFlg() const;

	/// SetHoleBottomFlg
	///
	/// Sets flag which tells if move associated with this report is hole bottom point
	/// This is the point inside the material at the drill depth distance from hole start and end
	/// points
	///	@param toSet is hole bottom flag to be set
	void SetHoleBottomFlg(const bool toSet);

	/// GetSafetyDistanceApproachFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	 an approach point in the air located at 'SafetyDistance' from hole start point
	/// From this point the tool starts the machining process approaching the part
	///	@return flag if this is approach point at safety distance
	bool GetSafetyDistanceApproachFlg() const;

	/// SetSafetyDistanceApproachFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	an approach point in the air located at 'SafetyDistance' from hole start point
	/// From this point the tool starts the machining process approaching the part
	///	@param toSet is safety distance approach flag to be set
	void SetSafetyDistanceApproachFlg(const bool toSet);

	/// GetSafetyDistanceRetractFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	 a retract point in the air located at 'SafetyDistance' from hole end point
	/// In this point the tool ends the machining process on retraction move from part
	///	@return flag if this is retract point at safety distance
	bool GetSafetyDistanceRetractFlg() const;

	/// SetSafetyDistanceRetractFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	a retract point in the air located at 'SafetyDistance' from hole end point
	/// In this point the tool ends the machining process on retraction move from part
	///	@param toSet is safety distance retract flag to be set
	void SetSafetyDistanceRetractFlg(const bool toSet);

	/// Gets flag which tells if move associated with this report is peck drill retraction point
	///This point marks a retraction position after finishing a major peck
	///	@return flag if this is peck drill retraction point
	bool GetPeckDrillRetractFlg() const;

	/// Sets flag which tells if move associated with this report is peck drill retraction point
	///This point marks a retraction position after finishing a major peck
	///	@param toSet is flag to be set
	void SetPeckDrillRetractFlg(const bool toSet);

	/// Gets tool spindle direction for the move associated with this report
	///
	/// Depending on strategy, spindle direction for a move can be different
	///  from spindle direction for other move
	///	@return tool spindle direction
	SpindleDirection GetSpindleDirection() const;

	/// Sets tool spindle direction for the move associated with this report
	///
	/// Depending on strategy, spindle direction in one point can be different
	///  from spindle direction in other point
	///	@param toSet is tool spindle direction to be set
	void SetSpindleDirection(const SpindleDirection toSet);

	/// Gets flag which tells if move associated with this report is a breakthrough point
	///
	/// Breakthrough function adds additional cutting depth with plunge feed rate
	///	@return flag if this is breakthrough point
	bool GetBreakthroughFlg() const;

	/// Sets flag which tells if move associated with this report is a breakthrough point
	///
	/// Breakthrough function adds additional cutting depth with plunge feed rate
	///	@param toSet is flag to be set for breakthrough point
	void SetBreakthroughFlg(const bool toSet);

	/// GetStartDistanceFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	an approach point in the air located at 'Start/End' distance from hole start point
	/// From this point the tool  approaches safe distance with rapid feed rate
	///	@return flag if this is approach point at 'start/end' distance
	bool GetStartDistanceFlg() const;

	/// SetStartDistanceFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	an approach point in the air located at 'Start/End' distance from hole start point
	/// From this point the tool approaches to safe distance with rapid feed rate
	///	@param toSet is flag for approach point at 'Start/End' distance to be set
	void SetStartDistanceFlg(const bool toSet);

	/// GetEndDistanceFlg
	///
	/// Gets flag which tells if move associated with this report is
	///	a retract point in the air located at 'Start/End' distance from hole end point
	/// From  safe distance,the tool  retracts to this point with rapid feed rate
	///	@return flag if this is end point at 'start/end' distance
	bool GetEndDistanceFlg() const;

	/// SetEndDistanceFlg
	///
	/// Sets flag which tells if move associated with this report is
	///	a retract point in the air located at 'Start/End' distance from hole end point
	/// From  safe distance,the tool  retracts to this point with rapid feed rate
	///	@param toSet is flag for retract point at 'Start/End' distance to be set
	void SetEndDistanceFlg(const bool toSet);

	/// Gets cutting direction for the move associated with this report
	///
	///Applies for some strategies like ThreadMilling where cutting direction 
	///decides the machining direction of spiral cuts
	///	@return cutting direction
	CuttingDirection GetCuttingDirection() const;

	///Sets cutting direction for the move associated with this report
	///
	///Applies for some strategies like ThreadMilling where cutting direction 
	///decides the machining direction of spiral cuts
	///	@param toSet is tool spindle direction to be set
	void SetCuttingDirection(const CuttingDirection toSet);

	///Gets flag which tells if this point is an approach point in order to drill next major peck
	///Used for HoleMaking-Drilling with pecks strategy
	///Tool approaches this position with plunge/custom feed rate in order to drill next major peck
	///Position is at min. retract distance above next major peck to be drilled
	///Applied starting second major peck if full retract is activated
	///	@return flag if this is peck drill approach point for drilling next major peck
	bool GetPeckDrillApproachFlg() const;
	

	///Sets flag which tells if this point is an approach point in order to drill next major peck
	///Used for HoleMaking-Drilling with pecks strategy
	///Tool approaches this position with plunge/custom feed rate in order to drill next major peck
	///Position is at min. retract distance above next major peck to be drilled
	///Applied starting second major peck if full retract is activated
	///@param toSet is flag for peck drill approach point for drilling next major peck to be set
	void SetPeckDrillApproachFlg(const bool toSet);
	

	///Gets flag which tells if move associated with this report is peck drill break peck retraction point
	///This point marks a retraction position after finishing a break peck inside a major peck.
	///Not applied after finishing last break peck of a major peck, in this case retraction is marked with PeckDrillRetractFlg 
	///Position is at min. retract distance above next break beck to be drilled
	///	@return flag if this is peck drill break peck retraction point
	bool GetPeckDrillBreakPeckRetractFlg() const;
	
	///Sets flag which tells if move associated with this report is peck drill break peck retraction point
	///This point marks a retraction position after finishing a break peck inside a major peck.
	///Not applied after finishing last break peck of a major peck, in this case retraction is marked with PeckDrillRetractFlg 
	///Position is at min. retract distance above next break beck to be drilled
	///	@param toSet is flag for peck drill break peck retraction point to be set
	void SetPeckDrillBreakPeckRetractFlg(const bool toSet);
	

private:
	Strategy m_strategy;
	bool m_holeStartFlg;
	bool m_holeEndFlg;
	bool m_holeBottomFlg;
	bool m_safetyDistanceApproachFlg;
	bool m_safetyDistanceRetractFlg;
	bool m_peckDrillRetractFlg;
	SpindleDirection m_spindleDirection;
	bool m_breakthroughFlg;
	bool m_startDistanceFlg;
	bool m_endDistanceFlg;
	CuttingDirection m_cuttingDirection;
	bool m_peckDrillApproachFlg;
	bool m_peckDrillBreakPeckRetractFlg;
};


/// Extrusion calculation report attached to a move after toolpath calculation
class MW_5AXUTIL_API mwLinkInterpolationReport
{
public:
	typedef misc::mwAutoPointer<mwLinkInterpolationReport> Ptr;
	enum LinkSegmentInterpolationMarkerType
	{
		INTERPOLATION_START = 0,
		INTERPOLATION_END = 1,
		NO_MARK = 2
	};
	mwLinkInterpolationReport();

	/// Equality operator
	///
	/// Compares two objects of this class for equality
	///	@return true if objects are equal
	///		false otherwise
	bool operator==(const mwLinkInterpolationReport&) const;

	/// Inequality operator
	///
	/// Compares two objects of this class for inequality
	///	@return true if objects are not equal
	///		false otherwise
	bool operator!=(const mwLinkInterpolationReport&) const;

	/// Gets link segment interpolation marker type of the move associated with this report
	const mwLinkInterpolationReport::LinkSegmentInterpolationMarkerType GetLinkSegmentMarkerType()
		const;

	/// Sets link segment interpolation marker type of the move associated with this report
	void SetLinkSegmentMarkerType(
		const mwLinkInterpolationReport::LinkSegmentInterpolationMarkerType& toSet);

private:
	LinkSegmentInterpolationMarkerType m_linkSegmentMarkerType;
};


}  // namespace cadcam
#endif  //	MW_MWMOVEREPORT_HPP_
