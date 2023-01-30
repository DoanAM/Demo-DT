// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPHELIXFIT_HPP_
#define MW_MWTPHELIXFIT_HPP_
#include "mwDeprecated.hpp"
#include "mwHelixMovesCompMethods.hpp"
#include "mwTArcCircleFactory.hpp"
#include "mwTPSectionFit.hpp"
#include "mwTPoint3d.hpp"

#include <list>

namespace cadcam
{
/// Class mwTPHelixFit stores a toolpath helix fit. A toolpath helix fit is made of two components:
///  - parameters for a 3d helix geometry
///  - a list of moves which fit the helix geometry within a specific tolerance
class MW_5AXUTIL_API mwTPHelixFit: public mwTPSectionFit
{
public:
	typedef misc::mwAutoPointer<mwTPHelixFit> Ptr;
	typedef std::list<movePtr>::const_iterator ListMovesIterator;
	typedef mwCNCMove::point3d Point3d;
	typedef geoDef::mwTHelix<double, geoDef::CS3dd> Helix;
	typedef misc::mwAutoPointer<Helix> HelixPtr;
	typedef geoDef::ArcCircledIn3ddFactory::Geo ArcCircle;

	/// Constructs an mwTPHelixFit using the parameters given:
	/// @param startMove CNC move for the start of the helix, the start must be in the same plane as
	/// the arc
	/// @param endMove CNC move for the end of the helix
	/// @param arcCircle a 3d arc which is in the same plane as start move
	/// @param tolerance the maximum tolerance allowed for position of two consecutive moves
	/// @param maxAngleDev the maximum angle deviation (in degrees) between two consecutive moves
	/// @param interpolateDirectly <b>true</b> to create polygonization in constructor
	mwTPHelixFit(
		const movePtr& startMove,
		const movePtr& endMove,
		const ArcCircle& arcCircle,
		const double tolerance,
		const double maxAngleDev,
		const bool interpolateDirectly = false)
		: m_startMove(CloneMove(startMove)), m_deltaTolerance(tolerance), m_maxAngleDev(maxAngleDev)
	{
		// compute normal to arc plane and bulge factor
		m_helixPtr = CreateHelixGeo(startMove, endMove, arcCircle);
		mwHelixMoveCreator::MoveList moveList;
		if (interpolateDirectly)
		{
			mwHelixMoveCreator helixMoveCreator(*m_helixPtr, startMove, endMove);
			moveList = helixMoveCreator.CreateMoveList(m_deltaTolerance, m_maxAngleDev);
		}
		else
		{
			mwHelixOrientedMoveCreator helixMoveCreator(*m_helixPtr, startMove, endMove);
			moveList = helixMoveCreator.CreateMoveList(m_deltaTolerance, m_maxAngleDev);
		}
		assign(moveList.begin(), moveList.end());
	}
	/// Constructs an mwTPHelixFit using the parameters given:
	/// @param startMove CNC move for the start of the helix, the start must be in the same plane as
	/// the arc
	/// @param arcCirle a 3d arc which is in the same plane as start move
	/// @param tolerance the maximum tolerance allowed for position of two consecutive moves
	/// @param maxAngleDev the maximum angle deviation ( in degrees ) between two consecutive moves
	/// @param startIt iterator pointing the beginning of the helix fit moves
	/// @param endIt iterator pointing the ending of the helix fit moves
	mwTPHelixFit(
		const movePtr& startMove,
		const ArcCircle& arcCirle,
		const double tolerance,
		const double maxAngleDev,
		const ListMovesIterator& startIt,
		const ListMovesIterator& endIt)
		: m_startMove(CloneMove(startMove)), m_deltaTolerance(tolerance), m_maxAngleDev(maxAngleDev)
	{
		if (startIt == endIt)
			MW_EXCEPTION("Invalid helix fit parameters, empty list of points is not allowed");

		ListMovesIterator lastMoveIt = endIt;
		--lastMoveIt;

		// compute normal to arc plane and bulge factor
		m_helixPtr = CreateHelixGeo(startMove, *lastMoveIt, arcCirle);

		mwHelixMovesCompMethods helixMovesComp(
			*m_helixPtr, startMove, *lastMoveIt, m_deltaTolerance, m_maxAngleDev);

		if (!helixMovesComp.AreMovesValid(startIt, endIt))
			throw misc::mwException(0, _T("Moves do not approximate the helix parameters"));

		this->assign(startIt, endIt);
	}

	/// Constructs an mwTPHelixFit using the parameters given:
	/// @param startMove CNC move for the start of the helix, the start must be in the same plane as
	/// the arc
	/// @param helixPtr pointer to mwTHelix object
	/// @param tolerance the maximum tolerance allowed for position of two consecutive moves
	/// @param maxAngleDev the maximum angle deviation ( in degrees ) between two consecutive moves
	/// @param startIt iterator pointing the beginning of the helix fit moves
	/// @param endIt iterator pointing the ending of the helix fit moves
	mwTPHelixFit(
		const movePtr& startMove,
		const HelixPtr& helixPtr,
		const double tolerance,
		const double maxAngleDev,
		const ListMovesIterator& startIt,
		const ListMovesIterator& endIt)
		: m_startMove(CloneMove(startMove)),
		  m_helixPtr(helixPtr),
		  m_deltaTolerance(tolerance),
		  m_maxAngleDev(maxAngleDev)
	{
		if (startIt == endIt)
			MW_EXCEPTION("Invalid helix fit parameters, empty list of points is not allowed");

		ListMovesIterator lastMoveIt = endIt;
		--lastMoveIt;

		this->assign(startIt, endIt);
	}
	/// implement the visitor pattern
	virtual void AcceptVisitor(mwTPSFitVisitor& visitor) const { visitor.Visit(*this); }
	/// inserts a move at the end of the sequence, but before the last move
	virtual void PushBackMove(const Move& move)
	{
		OverMovesIterator prevMove(end());
		--prevMove;
		InsertMove(prevMove, move);
	}
	/// inserts a move at the begin of the sequence, but after the first move
	virtual void PushFrontMove(const Move& move)
	{
		OverMovesIterator nextMove(begin());
		++nextMove;
		InsertMove(nextMove, move);
	}
	/// inserts a move just before specified position
	OverMovesIterator InsertMove(OverMovesIterator& insertionPoint, const Move& move)
	{
		OverMovesIterator prevMoveIt(insertionPoint);
		if (prevMoveIt == begin())
			MW_EXCEPTION("Moves can not be inserted before the first move of the helix");

		--prevMoveIt;
		OverMovesIterator nextMoveIt(insertionPoint);

		mwHelixMovesCompMethods helixMovesComp(
			*m_helixPtr, m_startMove, back(), m_deltaTolerance, m_maxAngleDev);

		if (!helixMovesComp.IsMoveValid(move, *prevMoveIt, *nextMoveIt))
			MW_EXCEPTION("Move insertion does not approximate anymore to the helix parameters");

		return insert(insertionPoint, move);
	}
	/// Removes the moves from the sequence in the range [first, last)
	/// first and last move are not allowed to be removed
	OverMovesIterator EraseMoves(OverMovesIterator first, OverMovesIterator last)
	{
		return erase(first, last);
	}
	///	It tests that 2 contours has the same structure and equal moves
	const bool operator==(const mwTPHelixFit& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return mathdef::is_eq(m_deltaTolerance, toCompare.m_deltaTolerance) &&
			mathdef::is_eq(m_maxAngleDev, toCompare.m_maxAngleDev) &&
			*m_startMove == *toCompare.m_startMove && *m_helixPtr == *toCompare.GetHelix() &&
			mwTPSectionFit::operator==(toCompare);
	}
	///	It tests 2 contours for inequality
	const bool operator!=(const mwTPHelixFit& toCompare) const { return !((*this) == toCompare); }

	///	It tests that 2 contours has the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos
	///		@param toCompare the slice to be compared with.
	///		@param delta given tolerance factor.
	///		@param minCos given minimal cosine of angle between moves orientations.
	const bool ExactCompareTolerance(
		const mwTPHelixFit& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		return mathdef::is_eq(m_deltaTolerance, toCompare.m_deltaTolerance) &&
			mathdef::is_eq(m_maxAngleDev, toCompare.m_maxAngleDev) &&
			*m_startMove == *toCompare.m_startMove &&
			m_helixPtr->ExactCompareTolerance(*toCompare.GetHelix(), delta, minCos) &&
			mwTPSectionFit::ExactCompareTolerance(toCompare, delta, minCos);
	}
	/// Return the start move of the helix (move with the position from which the helix starts),
	/// may point to the last move of the previous fit and may not be equal to the current fit beginning move
	const movePtr& GetStartMove() const { return m_startMove; }
	/// Return the helix geometry
	const HelixPtr& GetHelix() const
	{
		if (empty())
			MW_EXCEPTION("Invalid helix fit parameters, empty list of points is not allowed");
		return m_helixPtr;
	}
	/// Return the delta tolerance used for approximation the helix
	const double GetDeltaTolerance() const { return m_deltaTolerance; }
	/// Return the maximum angle deviation ( in degrees ) allowed for the helix approximation
	const double GetMaxAngleDev() const { return m_maxAngleDev; }
	const Point3d GetNormalToArcPlane() const
	{
		geoDef::mwTCSijkGetter<double> csg;
		m_helixPtr->GetCoordSystem().AcceptVisitor(csg);
		return mwVector3d(csg.Getk().x(), csg.Getk().y(), csg.Getk().z());
	}
	/// Deep-copy a given tp helix fit into this object
	void DeepCopy(const mwTPHelixFit& toCopy)
	{
		// deep copy start move
		m_startMove = CloneMove(toCopy.m_startMove);

		// deep copy helix geometry
		m_helixPtr = new Helix(*toCopy.m_helixPtr);

		m_deltaTolerance = toCopy.m_deltaTolerance;
		m_maxAngleDev = toCopy.m_maxAngleDev;
		// base class deep copy for the helix moves
		mwTPSectionFit::DeepCopy(toCopy);
	}

protected:
	mwTPHelixFit(
		const movePtr& startMove,
		const Point3d& normalToArcPlane,
		const double bulgeFactor,
		const double tolerance,
		const double maxAngleDev,
		const ListMovesIterator& startIt,
		const ListMovesIterator& endIt);

	static double GetHelixStep(
		const Point3d& startPoint,
		const Point3d& endPoint,
		const double sw,
		const Point3d& normalToArcPlane)
	{
		const Point3d endPointInPlane = mwVectorUtils<double>::ProjectPointToPlane(
			endPoint, normalToArcPlane, normalToArcPlane * startPoint);

		double stepSign = mathdef::Sign(normalToArcPlane * (endPoint - startPoint));
		return stepSign * (~(endPoint - endPointInPlane)) / sw;
	}

	HelixPtr CreateHelixGeo(
		const movePtr& startMove, const movePtr& endMove, const ArcCircle& arcCircle)
	{
		geoDef::mwTCSijkGetter<double> csijkGetter;
		arcCircle.GetCoordSystem().AcceptVisitor(csijkGetter);
		const Point3d normalToArcPlane =
			to_cadcam(csijkGetter.Getk());  // store normal to arc plane

		double helixStep = GetHelixStep(
			startMove->GetPosition(),
			endMove->GetPosition(),
			arcCircle.GetBase().GetSweepAngle(),
			normalToArcPlane);

		return new geoDef::HelixdIn3ddFactory::Geo(
			geoDef::HelixdIn3ddFactory::Create(arcCircle, helixStep));
	}

	HelixPtr CreateHelixGeo(
		const movePtr& startMove,
		const Point3d& normalToArcPlane,
		const movePtr& endMove,
		const double bulgeFactor) const
	{
		const Point3d& startPoint = startMove->GetPosition();  // in arc plane
		Point3d endPoint = mwVectorUtils<double>::ProjectPointToPlane(
			endMove->GetPosition(), normalToArcPlane, normalToArcPlane * startPoint);

		geoDef::ArcCircledIn3ddFactory::Geo arcCircle = geoDef::ArcCircledIn3ddFactory::Create(
			from_cadcam(startPoint),
			from_cadcam(endPoint),
			from_cadcam(normalToArcPlane),
			bulgeFactor);

		double helixStep = GetHelixStep(
			startPoint,
			endMove->GetPosition(),
			arcCircle.GetBase().GetSweepAngle(),
			normalToArcPlane);

		return new geoDef::HelixdIn3ddFactory::Geo(
			geoDef::HelixdIn3ddFactory::Create(arcCircle, helixStep));
	}

	movePtr CloneMove(const movePtr& toClone)
	{
		movePtr retMove = MW_NULL;
		mwMoveDeepCopy moveDeepCopy(retMove);
		toClone->AcceptVisitor(moveDeepCopy);
		return retMove;
	}
	movePtr m_startMove;
	HelixPtr m_helixPtr;
	double m_deltaTolerance;
	double m_maxAngleDev;
	friend class mwBICadcamTypes2;
	friend class mwBOCadcamTypes;
};  // end class mwTPHelixFit

class MW_5AXUTIL_API mwHelixFitInfoGetter
{
public:
	explicit mwHelixFitInfoGetter(const mwTPSectionFit& sectionFit);
	~mwHelixFitInfoGetter();
	/// Helix normal
	mwPoint3d GetCenterPointOrientation() const;
	/// Helix start point
	mwPoint3d GetStartPoint() const;
	/// Helix end point
	mwPoint3d GetEndPoint() const;
	/// Helix origin (center) point
	mwPoint3d GetCenterPoint() const;
	
	/// Helix orientation. Always returns false (CCW)
	///
	/// Orientation is defined when looking along helix normal, see
	/// <a href="http://en.wikipedia.org/wiki/Helix">article</a>.
	/// Normal can be used for helix orientation reversal.
	/// ![](doc/Developer_guide/Toolpath_calculation/Description_of_the_resulting_toolpath/images/image1007.gif)
	MW_DEPRECATED("Deprecated in 2014.12")
	bool IsClockWise() const;
	/// Helix sweep angle in radians
	double GetArcSweep() const;
	/// Helix height along the normal
	double GetHelixHeight() const;

	/// Tool axis at helix start position
	mwPoint3d GetStartPointOrientation() const;
	/// Tool axis at helix end position
	mwPoint3d GetEndPointOrientation() const;

private:
	class HelixFitInfoGetter;
	HelixFitInfoGetter* m_helixInfoGetter;
};
}  // namespace cadcam
#endif  //	MW_MWTPHELIXFIT_HPP_
