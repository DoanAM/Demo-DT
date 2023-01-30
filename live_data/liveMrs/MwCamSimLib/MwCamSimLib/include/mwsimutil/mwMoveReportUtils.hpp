// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef __mwMoveReportUtils_hpp__
#define __mwMoveReportUtils_hpp__

#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
class mwMoveReportsToolPathMapper;
/// Namespace grouping utilities for cadcam::mwMoveReport objects
namespace mwMoveReportUtils
{
// Contains parameters used by utility functions from this namespace
class MW_5AXUTIL_API mwMoveReportParams
{
public:
	typedef misc::mwAutoPointer<mwMoveReportParams> Ptr;
	/// Default constructor
	mwMoveReportParams();
	/// GetInterpolateWeldingReportsFlg
	///
	/// Gets flag which tells if welding reports should be interpolate by
	/// mwMoveReportUtils::InterpolateReports  function
	/// By default, welding reports are not interpolated
	///	@return value of the flag
	bool GetInterpolateWeldingReportsFlg() const;
	/// SetInterpolateWeldingReportsFlg
	///
	/// Sets flag which tells if welding reports should be interpolate by
	/// mwMoveReportUtils::InterpolateReports  function.
	/// By default, welding reports are not interpolated
	///	@param toSet is flag value to be set
	void SetInterpolateWeldingReportsFlg(const bool toSet);

private:
	bool m_interpolateWeldingReportsFlg;
};

/// InterpolateReports
///
/// Interpolates reports of two input moves and may create and attach an interpolated
/// report to destination move.
/// Depending if the input moves have or not reports, and also depending of type of reports,
/// a report may be created or not for destination move.
///	@param t is interpolation factor in [0,1]
///	@param srcMove1 is source move 1 (may contain report or not)
///	@param srcMove2 is source move 2 (may contain report or not)
///	@param destMove is destination move where a report may be attached
///	@param moveReportsMapper is mapper which contains the reports and where
///	 may be added the new interpolated report for destMove
MW_5AXUTIL_API void InterpolateReports(
	const double t,
	const mwCNCMove::Ptr& srcMove1,
	const mwCNCMove::Ptr& srcMove2,
	mwCNCMove::Ptr& destMove,
	mwMoveReportsToolPathMapper& moveReportsMapper);

/// InterpolateReports
///
/// Interpolates reports of two input moves and may create and attach an interpolated
/// report to destination move.
/// Depending if the input moves have or not reports, and also depending of type of reports,
/// a report may be created or not for destination move.
///	@param t is interpolation factor in [0,1]
///	@param srcMove1 is source move 1 (may contain report or not)
///	@param srcMove2 is source move 2 (may contain report or not)
///	@param destMove is destination move where a report may be attached
///	@param moveReportsMapper is mapper which contains the reports and where
///	 may be added the new interpolated report for destMove
///	@param reportParams are report parameters
MW_5AXUTIL_API void InterpolateReports(
	const double t,
	const mwCNCMove::Ptr& srcMove1,
	const mwCNCMove::Ptr& srcMove2,
	mwCNCMove::Ptr& destMove,
	mwMoveReportsToolPathMapper& moveReportsMapper,
	const mwMoveReportParams::Ptr reportParams);

/// HasMandatoryReport
/// Check if a given move contains a mandatory report.
/// A mandatory report must stay in the report mapper and must not be deleted.
/// @param move is move to be checked
/// @param moveReportsMapper is mapper which contains the reports
/// @return true if the move contains a mandatory report
/// 		false otherwise
MW_5AXUTIL_API const bool HasMandatoryReport(
	const mwCNCMove::Ptr& move, const mwMoveReportsToolPathMapper& moveReportsMapper);

};  // namespace mwMoveReportUtils
};  // namespace cadcam

#endif  //__mwMoveReportUtils_hpp__