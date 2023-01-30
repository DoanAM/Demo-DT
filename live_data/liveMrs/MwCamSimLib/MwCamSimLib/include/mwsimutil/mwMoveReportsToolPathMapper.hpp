// (C) 2003-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVEREPORTSTOOLPATHMAPPER_HPP_
#define MW_MWMOVEREPORTSTOOLPATHMAPPER_HPP_
#include "mwMoveReport.hpp"
#include "mwToolPath.hpp"


namespace cadcam
{
/// This class is used for allowing mapping between moves from a toolpath and move reports
///
/// Stores association of move reports with toopath moves and provides methods for interaction
/// with this association (get,add,remove,change,etc)
class MW_5AXUTIL_API mwMoveReportsToolPathMapper
{
public:
	typedef mwToolPath::ConstOverMovesIterator ConstOverMovesIterator;

	/// Constructor
	///
	///	@param tp is toolpath whose moves will be associated with move reports
	mwMoveReportsToolPathMapper(const mwToolPath& tp);

	/// Attach report to the last move from toolpath
	///
	///	@param report is report to be attached
	void AttachReport(const mwMoveReport& report);

	/// Attach report to toolpath move associated with given iterator
	///
	///	@param moveIt is iterator to toolpath move which will be associated with the report
	///	@param report is report to be attached
	void AttachReport(const ConstOverMovesIterator& moveIt, const mwMoveReport& report);

	/// Attach report to the move associated with the specified auto-pointer
	///
	///	@param move is the autopointer that points to the move where report will be attached.
	///	@param report is report to be attached
	void AttachReport(const misc::mwAutoPointer<mwCNCMove>& move, const mwMoveReport& report);

	/// Check whether the move associated with the specified iterator has report attached.
	/// @param moveIt is the iterator that points to the move.
	/// @returns true if the move has report attached, otherwise false.
	const bool HasReport(const ConstOverMovesIterator& moveIt) const;

	/// Check whether the move associated with the specified autopointer of the move has report
	/// attached.
	/// @param move is the autopointer that points to the move to be checked.
	/// @returns true if the move has report attached, otherwise false.
	const bool HasReport(const misc::mwAutoPointer<mwCNCMove>& move) const;

	/// Remove the report attached to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move from which the report will be removed.
	void RemoveReport(const ConstOverMovesIterator& moveIt);

	/// Remove the report attached to the move associated with the specified auto-pointer.
	/// @param move is the autopointer that points to the move whose report will be removed.
	void RemoveReport(const misc::mwAutoPointer<mwCNCMove>& move);

	/// Obtain the report attached to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move from which the report will be
	/// obtained.
	/// @returns report associated with toolpath move.
	const mwMoveReport& GetReport(const ConstOverMovesIterator& moveIt) const;

	/// Obtain the report attached to the specified move.
	/// @param move is the autopointer that points to the move from which the report will be
	/// obtained.
	/// @returns report associated with given toolpath move.
	const mwMoveReport& GetReport(const misc::mwAutoPointer<mwCNCMove>& move) const;

	/// Removes all reports associated with toolpath moves
	void RemoveAllReports();

	/// Check if there is no mapping between move reports and toolpath moves
	///
	///	@return true if if there is no mapping between move reports and toolpath moves
	///			false if at least one mapping exists
	const bool Empty() const;

	/// Gets size of the mapping (how many associations are made)
	///
	///	@return size of associations between move reports and toolpath moves
	const size_t Size() const;

private:
	mwMoveReportsToolPathMapper& operator=(const mwMoveReportsToolPathMapper&);

	const mwToolPath& m_tp;

	typedef std::map<mwMarkerKeyWrapper, mwMoveReport> ReportsMap;
#pragma warning(suppress : 4251)
	ReportsMap m_reportsMap;
};
};  // namespace cadcam
#endif  //	MW_MWMOVEREPORTSTOOLPATHMAPPER_HPP_
