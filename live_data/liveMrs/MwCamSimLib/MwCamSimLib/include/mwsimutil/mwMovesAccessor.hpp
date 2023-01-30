// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVESACCESSOR_HPP_
#define MW_MWMOVESACCESSOR_HPP_

#include "mw3axMove.hpp"
#include "mw3dPolyLineComparer.hpp"
#include "mw5axMarkedMove.hpp"
#include "mw5axMove.hpp"
#include "mw6axMove.hpp"
#include "mwMinSquaredDistance.hpp"
#include "mwMoveGenericMarker.hpp"
#include "mwMovesCompMethods.hpp"
#include "mwTPointUtils.hpp"
#include "mwToolPathDifferenceMarker.hpp"
#include "mwUpdateMarkedMoveVisitor.hpp"

#include <list>
#include <map>


namespace cadcam
{
/// this class allows conversion of a sequence of moves in 2 polylines
///
/// First polyline is an approximation based on position only,
/// Second one is an approximation based on position, orientation and tool length.
class MW_5AXUTIL_API mwRealComparePolyLines: public mwCNCMoveVisitor
{
public:
	/// Constructor
	///
	///	@param length tool length to be used in aproximation
	inline mwRealComparePolyLines(double length): m_Length(length){};
	/// addes a cnc move to aproximation
	///
	///	@param mw move to extract info
	inline virtual void Visit(const mwCNCMove& mw) { GetPoints(mw); };
	/// addes a 3ax move to aproximation
	///
	///	@param mw move to extract info
	inline virtual void Visit(const mw3axMove& mw) { GetPoints(mw); };
	/// addes a 5ax move to aproximation
	///
	///	@param mw move to extract info
	inline virtual void Visit(const mw5axMove& mw) { GetPoints(mw); };
	/// addes a 5ax marked move to aproximation
	///
	/// @param mw move to extract info
	inline virtual void Visit(const mw5axMarkedMove& mw) { GetPoints(mw); };
	/// addes a 6ax move to aproximation
	///
	///	@param mw move to extract info
	inline virtual void Visit(const mw6axMove& mw) { GetPoints(mw); };

	/// Get current position point added
	const mwCNCMove::point3d& GetCurrentRough() { return m_tmpRough; }
	/// Get current position point added
	const mwCNCMove::point3d& GetCurrentFine() { return m_tmpFine; }

private:
	/// addes a cnc move to aproximation
	///
	/// @param mw move to be added
	void GetPoints(const mwCNCMove& mw)
	{
		m_tmpRough = mw.GetPosition();
		m_tmpFine = mw.GetPosition() + mw.GetOrientation() * m_Length;
	}
	/// tool length
	double m_Length;
	/// current point (rough)
	mwCNCMove::point3d m_tmpRough;
	/// current point (fine)
	mwCNCMove::point3d m_tmpFine;
};

class mwMarkerKeyWrapper
{
public:
	typedef misc::mwAutoPointer<cadcam::mwCNCMove> CNCMovePtr;

	explicit mwMarkerKeyWrapper(CNCMovePtr move): m_movePtr(move) {}
	const CNCMovePtr& GetMove() const { return m_movePtr; }
	bool operator<(const mwMarkerKeyWrapper& toCompare) const
	{
		return (&(*m_movePtr)) < (&(*toCompare.m_movePtr));
	}

protected:
	misc::mwAutoPointer<cadcam::mwCNCMove> m_movePtr;
};

/// implements the functions for accessing the moves from a moves holder (container)
///
/// the main scope of this class is to hide normal containers members as begin, end
///		, iterator which are too generics names and instead to expose to the clients
///		 more meaningful names as GetMovesBegin, GetMovesEnd, etc
///		 Also it's providing 3 different methods to compare if 2 MovesHolders are the same
///		 and allows checking for left collisions.
template <typename MovesHolder>
class MW_5AXUTIL_API mwMovesAccessor: protected MovesHolder
{
public:
	/// move
	typedef typename MovesHolder::value_type Move;
	/// move iterator
	typedef typename MovesHolder::iterator OverMovesIterator;
	/// const move iterator
	typedef typename MovesHolder::const_iterator ConstOverMovesIterator;
	typedef std::list<mwMoveGenericMarker::Ptr> mwMoveGenericMarkers;
	typedef std::pair<mwMarkerKeyWrapper, mwMoveGenericMarkers> PairIteratorMoveMarker;
	typedef std::map<mwMarkerKeyWrapper, mwMoveGenericMarkers> GenericMarkersMap;

	/// destructor
	virtual inline ~mwMovesAccessor(){};

	/// return a bidirectional iterator to the first move
	///
	/// return a bidirectional iterator that points at the first move
	///	available (or just beyond the end of the sequence if there is no move).
	inline OverMovesIterator GetMovesBegin() { return this->begin(); };

	/// const version of GetMovesBegin()
	ConstOverMovesIterator GetMovesBegin() const { return this->begin(); };


	/// return a bidirectional iterator that points just beyond the end of the sequence.
	OverMovesIterator GetMovesEnd() { return this->end(); };

	/// const version of GetMovesEnd()
	ConstOverMovesIterator GetMovesEnd() const { return this->end(); };

	/// return how many moves are in in the sequence
	unsigned int GetMovesCount() const { return (unsigned int)this->size(); }

	/// return true if the toolpath is empty
	const bool IsEmpty() const { return this->empty(); }


	/// inserts a move at the end of the sequence
	virtual void PushBackMove(const Move& move) { this->push_back(move); }

	/// inserts a move at the begin of the sequence
	virtual void PushFrontMove(const Move& move) { this->push_front(move); }

	/// inserts a move just before specified position
	OverMovesIterator InsertMove(const OverMovesIterator& insertionPoint, const Move& move)
	{
		return insert(insertionPoint, move);
	}

	/// It tests for equality by value each move from MovesHolder.
	///
	/// @param toCompare moves accessor to comp with
	/// @return true if all the moves has the same values.
	const bool operator==(const mwMovesAccessor<MovesHolder>& toCompare) const;

	/// It tests for inequality by value each move from MovesHolder.
	///
	/// @param toCompare moves accessor to comp with
	/// @return true if at least one move is different.
	inline const bool operator!=(const mwMovesAccessor<MovesHolder>& toCompare) const
	{
		return !((*this) == toCompare);
	};

	/// Compare if MovesHolder distances between positions are within tolerance and if the tool
	/// orientation vectors differ not more than minCos
	///
	///	@param toCompare the MovesHolder to be compared with.
	///	@param delta given tolerance factor.
	///	@param minCos given minimal cosinus of angle between moves orientations.
	const bool ExactCompareTolerance(
		const mwMovesAccessor<MovesHolder>& toCompare, double delta, double minCos) const;

	/// Compare if MovesHolder distances between positions are within tolerance and if the tool
	/// orientation vectors differ not more than minCos, marks if not
	///
	///	@param toCompare the MovesHolder to be compared with.
	///	@param delta given tolerance factor.
	///	@param minCos given minimal cosine of angle between moves orientations.
	/// @param markersMap markers map
	bool ExactCompareToleranceMark(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap) const;

	bool ExactCompareToleranceMark(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap,
		const int maxNbDifferences,
		int& nbDifferences) const;

	/// Compare two MovesHolder with given tolerance delta and given delta1.
	/// @param toCompare MovesHolder to be compared.
	/// @param delta given tolerance factor.
	/// @param delta1 given tolerance factor.
	/// @param toolLength the length of tool.
	/// @param minCos min cosine value
	const bool RealCompare(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		double minCos) const;

	// const
	void RealCompareMark(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& leftMarkersMap,
		GenericMarkersMap& rightMarkersMap,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0) const;

	template <class MarkerType>
	void RealCompareMark(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& leftMarkersMap,
		GenericMarkersMap& rightMarkersMap,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0) const;

	template <class MarkerType>
	void RealCompareMark(
		const mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& markersMap,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0) const;

	// non const
	void RealCompareMark(
		mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& leftMarkersMap,
		GenericMarkersMap& rightMarkersMap,
		const bool markMoves,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0);

	template <class MarkerType>
	void RealCompareMark(
		mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& leftMarkersMap,
		GenericMarkersMap& rightMarkersMap,
		const bool markMoves,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0);

	template <class MarkerType>
	void RealCompareMark(
		mwMovesAccessor<MovesHolder>& toCompare,
		double delta,
		double delta1,
		double toolLength,
		GenericMarkersMap& markersMap,
		const bool markMoves,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0);

	/// Confirms if the MovesHolder is colliding.
	/// if at least one move from MovesHolder has collision state equal with COLLISION_LEFT
	/// then this function is returning true. other way it's returning false
	/// @return true if the MovesHolder is colliding.
	const bool Collide() const;


	/// Counts how many moves from MovesHolder are in collision state.
	/// @return the number of moves having the collision state equal with COLLISION_LEFT.
	const unsigned int CountCollisions() const;

protected:
	/// overwriting base class inserter in order to be able to make space for coming move if needed
	OverMovesIterator insert(const ConstOverMovesIterator& insertionPoint, const Move& move)
	{
		AssureSpace4Move();
		return MovesHolder::insert(insertionPoint, move);
	}

	/// each derived class should be sure that it has where to insert a move
	virtual void AssureSpace4Move() = 0;

private:
	/// This class is a distance calculator (functor) for Snake compare algorithm
	class mwTpSnakeDistanceCalculator
	{
	public:
		void operator()(
			ConstOverMovesIterator& it1,
			ConstOverMovesIterator& it2,
			ConstOverMovesIterator& it2p,
			const double& toolLength,
			double& dis,
			double& disX)
		{
			mwRealComparePolyLines point(toolLength);
			mwRealComparePolyLines point0Segment(toolLength);
			mwRealComparePolyLines point1Segment(toolLength);


			(*it1)->AcceptVisitor(point);
			(*it2p)->AcceptVisitor(point0Segment);
			(*it2)->AcceptVisitor(point1Segment);


			dis = GetDistanceRough(point0Segment, point1Segment, point);
			disX = GetDistanceFine(point0Segment, point1Segment, point);
		}

		void operator()(
			ConstOverMovesIterator& it1,
			ConstOverMovesIterator& it2,
			const double& toolLength,
			double& dis,
			double& disX)
		{
			mwRealComparePolyLines point1(toolLength);
			mwRealComparePolyLines point2(toolLength);

			(*it1)->AcceptVisitor(point1);
			(*it2)->AcceptVisitor(point2);

			dis = ~(point1.GetCurrentRough() - point2.GetCurrentRough());
			disX = ~(point1.GetCurrentFine() - point2.GetCurrentFine());
		}

	private:
		/// Get distance point to segment (rough)
		const double GetDistanceRough(
			mwRealComparePolyLines& pt0Segment,
			mwRealComparePolyLines& pt1Segment,
			mwRealComparePolyLines& pt) const
		{
			return mathdef::mw_sqrt(mwMinSquaredDistance::CalculateToSegment(
				pt.GetCurrentRough(), pt0Segment.GetCurrentRough(), pt1Segment.GetCurrentRough()));
		}

		/// Get distance point to segment (Fine)
		double GetDistanceFine(
			mwRealComparePolyLines& pt0Segment,
			mwRealComparePolyLines& pt1Segment,
			mwRealComparePolyLines& pt) const
		{
			return mathdef::mw_sqrt(mwMinSquaredDistance::CalculateToSegment(
				pt.GetCurrentFine(), pt0Segment.GetCurrentFine(), pt1Segment.GetCurrentFine()));
		}
	};

	/// this class allows conversion of a sequence of moves in 2 polylines
	///
	///	First polyline is an approximation based on position only,
	///	Second one is an approximation based on position, orientation and tool length.
	class mwRealComparePolyLinesBuilder: public mwCNCMoveVisitor
	{
	public:
		/// Constructor
		///
		///	@param roughAprox where to store created aproximation
		///	@param fineAprox where to store created aproximation
		///	@param length tool length to be used in aproximation
		inline mwRealComparePolyLinesBuilder(
			mw3ddPolyLinePtr roughAprox, mw3ddPolyLinePtr fineAprox, double length)  //-V730
			: m_roughAprox(roughAprox), m_fineAprox(fineAprox), mLength(length){};
		/// addes a cnc move to aproximation
		///
		///	@param mw move to be added
		inline virtual void Visit(const mwCNCMove& mw) { AddPoints(mw); };
		/// addes a 3ax move to aproximation
		///
		/// @param mw move to be added
		inline virtual void Visit(const mw3axMove& mw) { AddPoints(mw); };
		/// addes a 5ax move to aproximation
		///
		/// @param mw move to be added
		inline virtual void Visit(const mw5axMove& mw) { AddPoints(mw); };
		/// addes a 5ax marked move to aproximation
		///
		/// @param mw move to be added
		inline virtual void Visit(const mw5axMarkedMove& mw) { AddPoints(mw); };
		/// addes a 6ax move to aproximation
		///
		/// @param mw move to be added
		inline virtual void Visit(const mw6axMove& mw) { AddPoints(mw); };

		/// confirms if they are equal or not
		///
		///	@return true if they are equal
		const bool Equals() const;
		/// Get current position point added
		const mwCNCMove::point3d& GetCurrentRough() { return m_tmpRough; }
		/// Get current position point added
		const mwCNCMove::point3d& GetCurrentFine() { return m_tmpFine; }

	private:
		/// addes a cnc move to aproximation
		///
		///	@param mw move to be added
		void AddPoints(const mwCNCMove& mw)
		{
			m_tmpRough = mw.GetPosition();
			m_roughAprox->AddPoint(m_tmpRough);
			m_tmpFine = mw.GetPosition() + mw.GetOrientation() * mLength;
			m_fineAprox->AddPoint(m_tmpFine);
		}
		/// rough approximation
		mutable mw3ddPolyLinePtr m_roughAprox;
		/// fine aproximation
		mutable mw3ddPolyLinePtr m_fineAprox;
		/// tool length
		double mLength;
		/// current point (rough)
		mwCNCMove::point3d m_tmpRough;
		/// current point (fine)
		mwCNCMove::point3d m_tmpFine;
	};


	/// this function converts a sequence of moves in 2 polylines
	///
	/// @param roughAprox a polyline approximation based on position only,
	/// @param fineAprox a polyline approximation based on position, orientation and tool length.
	/// @param moves sequence of moves to be approximated by polylines,
	/// @param toolLength used for construction of the second polilyne approximantion
	void Convert2PolyLines(
		mw3ddPolyLinePtr& roughAprox,
		mw3ddPolyLinePtr& fineAprox,
		const mwMovesAccessor<MovesHolder>& moves,
		const double toolLength) const;

	void InsertMarker(GenericMarkersMap& markersMap, mwMarkerKeyWrapper::CNCMovePtr move) const
	{
		InsertMarker<mwToolPathDifferenceMarker>(markersMap, move);
	}

	template <class MarkerType>
	void InsertMarker(GenericMarkersMap& markersMap, mwMarkerKeyWrapper::CNCMovePtr move) const
	{
		mwMoveGenericMarker::Ptr newMarker(new mwMoveGenericMarker(new MarkerType()));
		newMarker->SetStatus(mwMoveGenericMarker::MW_GENERATED);
		markersMap[mwMarkerKeyWrapper(move)].push_back(newMarker);
	}
};

/// It tests for equality by value each move from MovesHolder.
///
///	@param toCompare moves accessor to comp with
///	@return true if all the moves has the same values.
template <typename MovesHolder>
const bool mwMovesAccessor<MovesHolder>::operator==(
	const mwMovesAccessor<MovesHolder>& toCompare) const
{
	if (&toCompare == this)
		return true;

	if (toCompare.GetMovesCount() != GetMovesCount())
		return false;

	ConstOverMovesIterator ToCompareIt(toCompare.GetMovesBegin());

	ConstOverMovesIterator End(GetMovesEnd());

	for (ConstOverMovesIterator It = GetMovesBegin(); It != End; It++, ToCompareIt++)
	{
		if (!mwMovesCompMethods::NormalCompareMoves(*(*It), *(*ToCompareIt)))
			return false;
	}

	return true;
}

/// Compare if MovesHolder distances between positions are within tolerance and if the tool
/// orientation vectors differ not more than minCos
///
/// @param toCompare the MovesHolder to be compared with.
/// @param delta given tolerance factor.
/// @param minCos given minimal cosinus of angle between moves orientations.
template <typename MovesHolder>
const bool mwMovesAccessor<MovesHolder>::ExactCompareTolerance(
	const mwMovesAccessor<MovesHolder>& toCompare, double delta, double minCos) const
{
	if (&toCompare == this)
		return true;

	if (toCompare.GetMovesCount() != GetMovesCount())
		return false;

	ConstOverMovesIterator ToCompareIt(toCompare.GetMovesBegin());

	ConstOverMovesIterator End(GetMovesEnd());

	for (ConstOverMovesIterator It = GetMovesBegin(); It != End; It++, ToCompareIt++)
	{
		if (!mwMovesCompMethods::ExactCompareMoves(*(*It), *(*ToCompareIt), delta, minCos))
			return false;
	}
	return true;
}

template <typename MovesHolder>
bool mwMovesAccessor<MovesHolder>::ExactCompareToleranceMark(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double minCos,
	GenericMarkersMap& markersMap) const
{
	int nbDifferences = 0;
	return ExactCompareToleranceMark(toCompare, delta, minCos, markersMap, 0, nbDifferences);
}

template <typename MovesHolder>
bool mwMovesAccessor<MovesHolder>::ExactCompareToleranceMark(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double minCos,
	GenericMarkersMap& markersMap,
	const int maxNbDifferences,
	int& nbDifferences) const
{
	if (&toCompare == this)
		return true;

	if (toCompare.GetMovesCount() != GetMovesCount())
		return false;

	ConstOverMovesIterator ToCompareIt(toCompare.GetMovesBegin());
	ConstOverMovesIterator End(GetMovesEnd());
	bool result = true;

	for (ConstOverMovesIterator It = GetMovesBegin(); It != End; ++It, ++ToCompareIt)
	{
		if (!mwMovesCompMethods::ExactCompareMoves(*(*It), *(*ToCompareIt), delta, minCos))
		{
			InsertMarker(markersMap, *It);
			result = false;
			if (maxNbDifferences > 0 && ++nbDifferences >= maxNbDifferences)
			{
				return false;
			}
		}
	}
	return result;
}

template <typename MovesHolder>
const bool mwMovesAccessor<MovesHolder>::RealCompare(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	double /*minCos*/) const
{
	mwTpSnakeDistanceCalculator distanceCalculator;


	if (cadcam::mwPolyLineSnakeCompare::Compare(
			toCompare.GetMovesBegin(),
			toCompare.GetMovesEnd(),
			this->GetMovesBegin(),
			this->GetMovesEnd(),
			distanceCalculator,
			delta,
			delta1,
			toolLength) == false)
	{
		return false;
	}

	if (cadcam::mwPolyLineSnakeCompare::Compare(
			this->GetMovesBegin(),
			this->GetMovesEnd(),
			toCompare.GetMovesBegin(),
			toCompare.GetMovesEnd(),
			distanceCalculator,
			delta,
			delta1,
			toolLength) == false)
	{
		return false;
	}


	return true;
}

template <typename MovesHolder>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& leftMarkersMap,
	GenericMarkersMap& rightMarkersMap,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences) const
{
	RealCompareMark<mwToolPathDifferenceMarker>(
		toCompare,
		delta,
		delta1,
		toolLength,
		leftMarkersMap,
		rightMarkersMap,
		uhePtr,
		maxNbDifferences);
}

template <typename MovesHolder>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& leftMarkersMap,
	GenericMarkersMap& rightMarkersMap,
	const bool markMoves,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences)
{
	RealCompareMark<mwToolPathDifferenceMarker>(
		toCompare,
		delta,
		delta1,
		toolLength,
		leftMarkersMap,
		rightMarkersMap,
		markMoves,
		uhePtr,
		maxNbDifferences);
}

template <typename MovesHolder>
template <class MarkerType>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& leftMarkersMap,
	GenericMarkersMap& rightMarkersMap,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences) const
{
	RealCompareMark<MarkerType>(
		toCompare, delta, delta1, toolLength, leftMarkersMap, uhePtr, maxNbDifferences);
	toCompare.RealCompareMark<MarkerType>(
		*this, delta, delta1, toolLength, rightMarkersMap, uhePtr, maxNbDifferences);
}

template <typename MovesHolder>
template <class MarkerType>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& leftMarkersMap,
	GenericMarkersMap& rightMarkersMap,
	const bool markMoves,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences)
{
	RealCompareMark<MarkerType>(
		toCompare, delta, delta1, toolLength, leftMarkersMap, markMoves, uhePtr, maxNbDifferences);
	toCompare.RealCompareMark<MarkerType>(
		*this, delta, delta1, toolLength, rightMarkersMap, markMoves, uhePtr, maxNbDifferences);
}

template <typename MovesHolder>
template <class MarkerType>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	const mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& markersMap,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences) const
{
	mwTpSnakeDistanceCalculator distanceCalculator;

	cadcam::mwPolyLineSnakeCompare::MoveIndices differences =
		cadcam::mwPolyLineSnakeCompare::MarkDifferences(
			this->GetMovesBegin(),
			this->GetMovesEnd(),
			toCompare.GetMovesBegin(),
			toCompare.GetMovesEnd(),
			distanceCalculator,
			delta,
			delta1,
			toolLength,
			uhePtr,
			maxNbDifferences);

	ConstOverMovesIterator move = GetMovesBegin();
	size_t lastIndex = 0;
	for (cadcam::mwPolyLineSnakeCompare::MoveIndices::iterator i = differences.begin();
		 i != differences.end();
		 ++i)
	{
		mwPolyLineSnakeCompare::VerifyIfCanceledCompare(uhePtr);

		const size_t moveIndex = (*i).first;
		std::advance(move, moveIndex - lastIndex);
		lastIndex = moveIndex;
		InsertMarker<MarkerType>(markersMap, *move);
	}
}

template <typename MovesHolder>
template <class MarkerType>
void mwMovesAccessor<MovesHolder>::RealCompareMark(
	mwMovesAccessor<MovesHolder>& toCompare,
	double delta,
	double delta1,
	double toolLength,
	GenericMarkersMap& markersMap,
	const bool markMoves,
	interact::mwUpdateHandlerInterface::Ptr uhePtr,
	const int maxNbDifferences)
{
	mwTpSnakeDistanceCalculator distanceCalculator;

	cadcam::mwPolyLineSnakeCompare::MoveIndices differences =
		cadcam::mwPolyLineSnakeCompare::MarkDifferences(
			this->GetMovesBegin(),
			this->GetMovesEnd(),
			toCompare.GetMovesBegin(),
			toCompare.GetMovesEnd(),
			distanceCalculator,
			delta,
			delta1,
			toolLength,
			uhePtr,
			maxNbDifferences);

	OverMovesIterator move = GetMovesBegin();
	size_t lastIndex = 0;
	for (cadcam::mwPolyLineSnakeCompare::MoveIndices::iterator i = differences.begin();
		 i != differences.end();
		 ++i)
	{
		mwPolyLineSnakeCompare::VerifyIfCanceledCompare(uhePtr);

		const size_t moveIndex = (*i).first;
		std::advance(move, moveIndex - lastIndex);
		lastIndex = moveIndex;
		// Check if it is enough to mark the move. Otherwise, add marker.
		if (markMoves)
		{
			const mwPolyLineSnakeCompare::DifferenceType differenceType = (*i).second;
			mwUpdateMarkedMoveVisitor updateMarkedMoveVisitor(differenceType);
			(**move).AcceptVisitor(updateMarkedMoveVisitor);
			if (!updateMarkedMoveVisitor.GetUpdatedMove())
			{
				InsertMarker<MarkerType>(markersMap, *move);
			}
		}
		else
		{
			InsertMarker<MarkerType>(markersMap, *move);
		}
	}
}

/// Confirms if the MovesHolder is colliding.
/// if at least one move from MovesHolder has collision state equal with COLLISION_LEFT
/// then this function is returning true. other way it's returning false
/// @return true if the MovesHolder is colliding.
template <typename MovesHolder>
const bool mwMovesAccessor<MovesHolder>::Collide() const
{
	bool collide = false;
	for (ConstOverMovesIterator move = GetMovesBegin(); move != GetMovesEnd(); ++move)
	{
		if ((*move)->GetCollisionState() == mwCNCMove::COLLISION_LEFT)
		{
			collide = true;
			break;
		}
	}
	return collide;
}

/// Counts how many moves from MovesHolder are in collision state.
/// @return the number of moves having the collision state equal with COLLISION_LEFT.
template <typename MovesHolder>
const unsigned int mwMovesAccessor<MovesHolder>::CountCollisions() const
{
	unsigned int collisions = 0;
	for (ConstOverMovesIterator move = GetMovesBegin(); move != GetMovesEnd(); ++move)
	{
		if ((*move)->GetCollisionState() == mwCNCMove::COLLISION_LEFT)
		{
			collisions++;
		}
	}
	return collisions;
}

/// this function converts a sequence of moves in 2 polylines
///
/// @param roughAprox a polyline approximation based on position only,
/// @param fineAprox a polyline approximation based on position, orientation and tool length.
/// @param moves sequence of moves to be approximated by polylines,
/// @param toolLength used for construction of the second polilyne approximantion
template <typename MovesHolder>
void mwMovesAccessor<MovesHolder>::Convert2PolyLines(
	mw3ddPolyLinePtr& roughAprox,
	mw3ddPolyLinePtr& fineAprox,
	const mwMovesAccessor<MovesHolder>& moves,
	const double toolLength) const
{
	roughAprox = new mw3ddPolyLine();
	fineAprox = new mw3ddPolyLine();
	mwRealComparePolyLinesBuilder plb(roughAprox, fineAprox, toolLength);
	// build polylines
	ConstOverMovesIterator End(moves.GetMovesEnd());
	for (ConstOverMovesIterator It = moves.GetMovesBegin(); It != End; It++)
	{
		(*It)->AcceptVisitor(plb);
	}
}

}  // namespace cadcam
#endif  //	MW_MWMOVESACCESSOR_HPP_
