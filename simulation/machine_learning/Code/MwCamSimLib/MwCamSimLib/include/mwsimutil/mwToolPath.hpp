// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATH_HPP_
#define MW_MWTOOLPATH_HPP_
#include "mwAutoPointer.hpp"
#include "mwCNCMoveHelpers.hpp"
#include "mwCollectionOfContainers.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"
#include "mwMovesAccessor.hpp"
#include "mwTPPass.hpp"
#include "mwcadcamException.hpp"

#include <list>
#include <map>
#include <utility>


namespace cadcam
{
class mwMoveReportsToolPathMapper;
/// This class implements a toolpath.
///
/// The toolpath is made from a list of toolpath passes, which are a list of toolpath slices,
///	which are a list of toolpath sections. Each toolpath section can be a toolpath contour or a
///toolpath link, but both are lists of moves. 	This class can be also be understood as a continuous
///list of moves which is actually the result of concatenating all the moves from all passes. 	If you
///try to add a move in a toolpath when no pass is available, the class creates a default one for
///you.
class MW_5AXUTIL_API mwToolPath
	: public mwMovesAccessor<
		  misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPPass>>>>,
	  public measures::mwMeasurable
{
public:
	typedef misc::mwAutoPointer<mwToolPath> Ptr;
	typedef mwTPPass TPPass;
	typedef misc::mwAutoPointer<TPPass> TPPassPtr;
	typedef std::list<TPPassPtr> TPPasses;
	typedef mwMovesAccessor<misc::mwCollectionOfContainers<TPPasses>> Super;
	typedef TPPasses::iterator OverTPPassesIterator;
	typedef TPPasses::const_iterator ConstOverTPPassesIterator;
	typedef mwCNCMove moveType;
	typedef measures::mwMeasurable::Units Units;
	typedef misc::mwAutoPointer<mwCNCMove> CNCMovePtr;
	typedef std::pair<CNCMovePtr, mwMoveGenericMarkers> mwMarkedMove;
	typedef std::list<mwMarkedMove> mwMarkedMoves;
	typedef std::map<double, mwMoveGenericMarkers> OrderedMarkersMap;
	typedef Super::const_iterator const_iterator;

	explicit mwToolPath(measures::mwMeasurable::Units tpUnits);

	~mwToolPath();

	OverTPPassesIterator GetPassesBegin() { return m_Collection.begin(); }
	ConstOverTPPassesIterator GetPassesBegin() const { return m_Collection.begin(); }
	OverTPPassesIterator GetPassesEnd() { return m_Collection.end(); }
	ConstOverTPPassesIterator GetPassesEnd() const { return m_Collection.end(); }
	/// Get the last pass
	misc::mwAutoPointer<cadcam::mwTPPass>& GetBack() { return m_Collection.back(); }
	/// Get the section the move belongs to
	const mwTPSection& GetMoveSection(const ConstOverMovesIterator& move) const
	{
		return (*GetContainer(move))->GetMoveSection(GetValue(move));
	}
	unsigned int GetPassesCount() const { return (unsigned int)m_Collection.size(); }
	void PushBack(TPPassPtr pass) { m_Collection.push_back(pass); }
	void PushFront(TPPassPtr pass) { m_Collection.push_front(pass); }
	/// Insert a pass at a given position.
	///
	///	@param insertionPoint is the iterator after which the pass is inserted.
	///	@param pass is the pass to insert.
	OverTPPassesIterator Insert(OverTPPassesIterator insertionPoint, const TPPassPtr& pass)
	{
		return m_Collection.insert(insertionPoint, pass);
	}
	/// Clear the toolpath
	void Clear() { m_Collection.clear(); }
	/// Erase the range of passes.
	OverTPPassesIterator ErasePasses(OverTPPassesIterator first, OverTPPassesIterator last)
	{
		return m_Collection.erase(first, last);
	}
	/// Inserts a toolpath slice at the end of the sequence.
	///
	/// If there is no pass available in the sequence, a new one is created
	///	@param slice is the slice to be added.
	void PushBack(TPPass::TPSlicePtr slice)
	{
		AssureAtLeastOnePass();
		(*(--m_Collection.end()))->PushBack(slice);
	}
	/// Inserts a toolpath section at the end of the sequence.
	///
	/// If there is no pass available in the sequence, a new one is created.
	///	@param section is the section to be added
	void PushBack(TPPass::TPSlice::TPSectionPtr section)
	{
		AssureAtLeastOnePass();
		(*(--m_Collection.end()))->PushBack(section);
	}

	/// Check whether the move is part of a link.
	/// @param move is the iterator to the move to be checked.
	/// @returns True if the move is part of a link, false if it is part of a contour.

	const bool IsPartOfALink(const ConstOverMovesIterator& move) const;
	/// Check whether the section is a link.
	/// @param section is the section to be checked.
	/// @returns True if the move is part of a link, false if it is part of a contour.
	static const bool IsALink(const mwTPSection& section);
	/// Check whether the section fit is a PolyLineFit.
	/// @param sectionFit is the section fit to be checked.
	/// @returns True if the sectionFit is a polyLine fit type, otherwise false.
	static const bool IsAPolyLineFit(const mwTPSectionFit& sectionFit);
	/// Returns the type of link to which the move belongs.
	/// If the move is not part of a link, the function throws an exception.
	/// @param move is the iterator to the move in the link section.
	/// @returns The type of link to which the move belongs.
	const mwTPLink::Types GetLinkType(const ConstOverMovesIterator& move) const;

	/// Check if 2 toolpaths have the same structure and equal moves.
	const bool operator==(const mwToolPath& toCompare) const;
	const bool operator!=(const mwToolPath& toCompare) const;
	/// Deep-copy a given toolpath into this object.
	void DeepCopy(const mwToolPath& toCopy);

	/// Copy-operator
	const mwToolPath& operator=(const mwToolPath& toCopy);

	// Copy-constructor
	mwToolPath(const mwToolPath& toCopy);

	///	Tests whether 2 toolpaths have the same structure and equivalent moves.
	///
	/// It also checks whether the distance between the positions of the moves is within the
	/// tolerance,
	///	and whether the tool orientation vectors differ more than minCos.
	///		@param toCompare is the toolpath to be compared.
	///		@param delta is the tolerance.
	///		@param minCos is the minimal cosine of the angle between moves.
	bool ExactCompareTolerance(const mwToolPath& toCompare, double delta, double minCos) const;
	///	Tests whether 2 toolpaths have the same structure and equivalent moves.
	///
	/// It also tests whether the distance between the positions of the moves is within the
	/// tolerance, and whether the tool orientation vectors differ more than minCos. The function
	/// adds markers to
	///	moves that do not satisfy these two conditions.
	///	@param toCompare is the toolpath to be compared.
	///	@param delta is the tolerance.
	///	@param minCos is the minimal cosine of the angle between moves.
	/// @param maxNbDifferences upper limit of a number of tracked differences
	bool ExactCompareToleranceMark(
		const mwToolPath& toCompare, double delta, double minCos, const int maxNbDifferences = 0);

	void RealCompareMark(
		mwToolPath& toCompare,
		double delta,
		double delta1,
		double toolLength,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0);

#ifndef MW_USE_VS2008_COMPATIBILITY
	void VisualCompareMark(
		mwToolPath& toCompare,
		double delta,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0,
		const bool compareLinksFlg = false);
#endif
	
	///	Tests whether 2 toolpaths are within tolerance.
	///
	/// Whenever it detects that a move from one toolpath is not within tolerance relative to the
	/// other toolpath with regard to the position, a cadcam::mwToolPathDifferentPositionMarker
	/// corresponding to that move is added. Also, whenever it detects that a move from one toolpath
	/// is not within tolerance relative to the other toolpath with regard to the position shifted
	/// with the tool length in that move's orientation, a cadcam::mwToolPathDifferentOrientationMarker 
	/// corresponding to that move is added.
	/// 
	/// @param toCompare is the toolpath to be compared.
	/// @param delta is the tolerance used to compare positions.
	/// @param delta1 is the tolerance used to compare positions shifted with toolLength.
	/// @param toolLength is the length of the tool
	/// @param uhePtr update handler
	/// @param maxNbDifferences maximum number of tracked differences
	void TypeOfDifferenceCompareMark(
		mwToolPath& toCompare,
		double delta,
		double delta1,
		double toolLength,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0);

	/// Attach a list of markers to the last move from the toolpath.
	/// @param moveMarkerList represents the list of mwGenericMoveMarker.
	void AttachMarkers(const mwMoveGenericMarkers& moveMarkerList);
	/// Attach a list of markers to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move to which the list will be attached.
	/// @param moveMarkerList represents the list of mwGenericMoveMarker.
	void AttachMarkers(
		const ConstOverMovesIterator& moveIt, const mwMoveGenericMarkers& moveMarkerList);
	/// Attach one marker to the last move of the toolpath.
	/// @param moveMarker represents the marker that will be added.
	void AttachMarker(const mwMoveGenericMarker::Ptr& moveMarker);
	/// Attach one marker to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move to which the marker will be added.
	/// @param moveMarker represents the marker that will be added.
	void AttachMarker(
		const ConstOverMovesIterator& moveIt, const mwMoveGenericMarker::Ptr& moveMarker);
	/// Check whether the move associated with the specified iterator has markers attached.
	/// @param moveIt is the iterator that points to the move.
	/// @returns True if the move has markers attached, otherwise false.
	bool HasMarkers(const ConstOverMovesIterator& moveIt) const;
	/// Check whether the move associated with the specified autopointer of the move has markers
	/// attached.
	/// @param move is the autopointer that points to the move to be checked.
	/// @returns True if the move has markers attached, otherwise false.
	bool HasMarkers(const misc::mwAutoPointer<mwCNCMove>& move) const;
	/// Remove the markers attached to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move from which the markers will be
	/// removed.
	void RemoveMarkers(const ConstOverMovesIterator& moveIt);
	/// Obtain the markers attached to the move associated with the specified iterator.
	/// @param moveIt is the iterator that points to the move from which the markers will be
	/// obtained.
	/// @returns A list of associated generic move markers.
	const mwMoveGenericMarkers& GetMarkers(const ConstOverMovesIterator& moveIt) const;
	/// Obtain the markers attached to the specified move.
	/// @param move is the autopointer that points to the move from which the markers will be
	/// obtained.
	/// @returns the list of associated generic move markers.
	const mwMoveGenericMarkers& GetMarkers(const misc::mwAutoPointer<mwCNCMove>& move) const;
	/// Obtain a sorted list (pair representing parametrization and move marker list) with all
	/// markers from all moves.
	/// @returns A sorted list with all markers from all moves.
	mwMarkedMoves GetMarkedMoves() const;
	/// Removes all markers from all moves.
	void RemoveAllMarkers();

	/// Gets mapper between move reports and associated moves from this toolpath
	///
	///	@return non-const move reports mapper
	mwMoveReportsToolPathMapper& GetMoveReportsMapper();

	/// Gets mapper between move reports and associated moves from this toolpath
	///
	///	@return const move reports mapper
	const mwMoveReportsToolPathMapper& GetMoveReportsMapper() const;

protected:
	/// Create ordered markers map from generic map.
	///
	///	@param markersMap is the source markers map.
	///	@returns An ordered markers map.
	OrderedMarkersMap CreateOrderedMarkersMap(const GenericMarkersMap& markersMap) const;
	/// Compare two marker maps.
	/// @param originalMarkersMap is a marker map.
	/// @param finalMarkersMap is a marker map.
	/// @returns True if they are the same.
	const bool CompareMoveMarkers(
		OrderedMarkersMap& originalMarkersMap, OrderedMarkersMap& finalMarkersMap) const;
	/// Compare two marker maps (ordered by parametrization).
	/// @param markers is a marker.
	/// @param markersToCompare is a marker.
	/// @return true if equal
	const bool CompareGenericMarkers(
		mwMoveGenericMarkers& markers, mwMoveGenericMarkers& markersToCompare) const;
	/// Create one pass in case the toolpath is empty.
	virtual void AssureSpace4Move() { AssureAtLeastOnePass(); }
	/// Scale the toolpath with the given factor.
	/// @param Units are reserved and are unused at the moment.
	/// @param scaleFactor is the scale applied to the toolpath.
	void Scale(const Units, const double& scaleFactor);
	std::map<mwMarkerKeyWrapper, mwMoveGenericMarkers> m_markerMaps;
	mwMoveReportsToolPathMapper* m_moveReportsMapper;

private:
	/// Assure that there is at least one pass in the toolpath. If there is none, a default pass is
	/// added.
	void AssureAtLeastOnePass();

	/// Performs a deep-copy of markers from a toolpath into this object.
	void DeepCopyMarkers(const mwToolPath& toCopy);

	/// Get the deep copy of a list of markers.
	/// @param toCopy is the list of markers which will be deep-copied.
	/// @return A new list of markers that contains the deep-copy of the input markers.
	const mwMoveGenericMarkers GetDeepCopyMarkers(const mwMoveGenericMarkers& toCopy);

	/// Compare move reports from 2 input toolpaths
	///
	///	@param firstTp is first tp whose move report will be compared
	///	@param secondTp is second tp whose move report will be compared
	///	@return true if both move reports are equal
	///			false otherwise
	const bool CompareMoveReports(const mwToolPath& firstTp, const mwToolPath& secondTp) const;

	/// Performs a copy of move reports from a given toolpath into this object.
	///
	///	@param toCopy is input toolpath whose move reports
	///	will be deep copied into move reports of this toolpath
	///	@param deepCopyFlg is flag which tells if a deep or shallow copy will
	///	be performed
	///		true if deep copy is performed
	///		false if shallow copy is performed
	void CopyMoveReports(const mwToolPath& toCopy, const bool& deepCopyFlg);


	/// Copy members of input toolpath into this object
	void Copy(const mwToolPath& toCopy);
};

inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwToolPath& toDump)
{
	os << _T("class cadcam::mwToolPath\n");
	// public properties from cadcam::mwToolPath class.
	os << _T("GetPassesCount        = ") << toDump.GetPassesCount() << _T("\n");
	os << _T("GetMovesCount         = ") << toDump.GetMovesCount() << _T("\n");
	os << _T("IsEmpty               = ") << toDump.IsEmpty() << _T("\n");
	os << _T("Collide               = ") << toDump.Collide() << _T("\n");
	os << _T("CountCollisions       = ") << toDump.CountCollisions() << _T("\n");
	return os;
}

typedef mwToolPath toolpath;

/// This class copies CNC moves.
///
/// DEPRECATED class. Use class mwMoveDeepCopy from mwCNCMoveUtils.hpp instead
class MW_5AXUTIL_API mwMoveCopy: public cadcam::mwCNCMoveVisitor
{
public:
	mwMoveCopy(): m_copyMove(MW_NULL) {}
	void Visit(const cadcam::mwCNCMove& mw)
	{
		misc::mwAutoPointer<cadcam::mwCNCMove> newMoveElem(new cadcam::mwCNCMove(mw));
		m_copyMove = newMoveElem;
	}
	void Visit(const cadcam::mw3axMove& mw)
	{
		misc::mwAutoPointer<cadcam::mw3axMove> newMoveElem(new cadcam::mw3axMove(mw));
		m_copyMove = newMoveElem;
	}
	void Visit(const cadcam::mw5axMove& mw)
	{
		misc::mwAutoPointer<cadcam::mw5axMove> newMoveElem(new cadcam::mw5axMove(mw));
		m_copyMove = newMoveElem;
	}
	void Visit(const cadcam::mw5axMarkedMove& mw)
	{
		misc::mwAutoPointer<cadcam::mw5axMarkedMove> newMoveElem(new cadcam::mw5axMarkedMove(mw));
		m_copyMove = newMoveElem;
	}
	void Visit(const cadcam::mw6axMove& mw)
	{
		misc::mwAutoPointer<cadcam::mw6axMove> newMoveElem(new cadcam::mw6axMove(mw));
		m_copyMove = newMoveElem;
	}
	mwToolPath::Move m_copyMove;
};
}  //  namespace cadcam
#endif  //	MW_MWTOOLPATH_HPP_
