// (C) 2007-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCNCMOVEUTILS_HPP_
#define MW_MWCNCMOVEUTILS_HPP_
#include "mw3axMove.hpp"
#include "mw5axMarkedMove.hpp"
#include "mw5axMove.hpp"
#include "mw6axMove.hpp"
#include "mwCNCMove.hpp"
#include "mwCadcamMathConvs.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTHelixHelper.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwMoveTypeVisitor: public mwCNCMoveVisitor
{
public:
	enum moveType
	{
		UNDEFINED,
		MOVE_CNC,
		MOVE_3AX,
		MOVE_5AX,
		MOVE_6AX,
		MOVE_5AX_MARKED
	};

	mwMoveTypeVisitor();

	virtual ~mwMoveTypeVisitor();

	virtual void Visit(const mwCNCMove&);

	virtual void Visit(const mw3axMove&);

	virtual void Visit(const mw5axMove&);

	virtual void Visit(const mw5axMarkedMove&);

	virtual void Visit(const mw6axMove&);

	const moveType GetMoveType() const;

protected:
	moveType m_moveType;
};

class MW_5AXUTIL_API mwMoveTypeAndDataVisitor: public mwMoveTypeVisitor
{
public:
	mwMoveTypeAndDataVisitor();

	virtual void Visit(const mwCNCMove& move);

	virtual void Visit(const mw3axMove& move);

	virtual void Visit(const mw5axMove& move);

	virtual void Visit(const mw6axMove& move);

	virtual void Visit(const mw5axMarkedMove& move);

	const mwCNCMove& GetCNCMove() const;

	const mw3axMove& Get3axMove() const;

	const mw5axMove& Get5axMove() const;

	const mw6axMove& Get6axMove() const;

	const mw5axMarkedMove& Get5axMarkedMove() const;

private:
	mwCNCMove m_CNCMove;
	mw3axMove m_3axMove;
	mw5axMove m_5axMove;
	mw6axMove m_6axMove;
	mw5axMarkedMove m_5axMarkedMove;
};

class MW_5AXUTIL_API mwMoveLinCmb
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> movePtr;

	mwMoveLinCmb(movePtr move1, movePtr move2);

	movePtr CreatePoint(const double k1, const double k2) const;

	const movePtr& GetMove1() const;

	const movePtr& GetMove2() const;

protected:
	movePtr m_move1;
	movePtr m_move2;
};

class MW_5AXUTIL_API mwHelixMoveCreator
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> movePtr;
	typedef std::list<movePtr> MoveList;
	typedef geoDef::HelixdIn3ddHelper::HelixGeo Helix;
	typedef geoDef::HelixdIn3ddHelper::PointAnglePair PointAnglePair;
	typedef geoDef::HelixdIn3ddHelper::PointAnglePairList PointAnglePairList;
	typedef mwCNCMove::point3d point3d;

	mwHelixMoveCreator(const Helix& helix, const movePtr& startMove, const movePtr& endMove);

	const MoveList CreateMoveList(const double deltaTolerance, const double maxAngleDev) const;

	static movePtr CreateMoveLinCmb(
		const double curTheta, const double sweepAngle, const mwMoveLinCmb& moveLinCmb);

protected:
	const Helix& m_helix;
	const movePtr m_startMove;
	const movePtr m_endMove;

	class CNCMoveCreator
	{
	public:
		typedef mwMoveLinCmb::movePtr movePtr;
		typedef mwCNCMove::point3d point3d;

		CNCMoveCreator(
			const mwMoveLinCmb& moveLinCmb, MoveList& helixMoveList, const double sweepAngle)
			: m_helixMoveList(helixMoveList), m_moveLinCmb(moveLinCmb), m_sweepAngle(sweepAngle)
		{
			m_startPoint = m_moveLinCmb.GetMove1()->GetPosition();
			m_endPoint = m_moveLinCmb.GetMove2()->GetPosition();
		}
		void operator()(const PointAnglePair& curPoint)
		{
			movePtr toAdd(
				mwHelixMoveCreator::CreateMoveLinCmb(curPoint.first, m_sweepAngle, m_moveLinCmb));

			toAdd->SetPosition(to_cadcam(curPoint.second));
			m_helixMoveList.push_back(toAdd);
		}

	protected:
		MoveList& m_helixMoveList;
		const mwMoveLinCmb& m_moveLinCmb;
		point3d m_startPoint;
		point3d m_endPoint;
		const double m_sweepAngle;

	private:
		CNCMoveCreator& operator=(const CNCMoveCreator);  // = delete
	};

	double GetMaxAngleAllowed4DeltaTol(const double deltaTolerance, const Helix& helixGeo) const;

	double GetMaxAngleAllowed4AngleDev(
		const double maxAngleDev,
		const Helix& helixGeo,
		const point3d& o1,
		const point3d& o2) const;

	PointAnglePairList CreateArcPointsInTolerance(
		const double deltaTolerance,
		const double maxAngleDev,
		Helix helixGeo,
		const point3d& o1,
		const point3d& o2) const;

private:
	mwHelixMoveCreator& operator=(mwHelixMoveCreator&);  // = delete
};

/// Performs a deep copy (clone) of a visited move
class MW_5AXUTIL_API mwMoveDeepCopy: public mwCNCMoveVisitor
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> movePtr;

	/// Constructor
	///
	///	@param retDeepCopy will return the new created clone of the visited move
	mwMoveDeepCopy(movePtr& retDeepCopy);

	virtual ~mwMoveDeepCopy();

	virtual void Visit(const mwCNCMove& move);

	virtual void Visit(const mw3axMove& move);

	virtual void Visit(const mw5axMove& move);

	virtual void Visit(const mw5axMarkedMove& move);

	virtual void Visit(const mw6axMove& move);

private:
	mwMoveDeepCopy& operator=(mwMoveDeepCopy&);  // = delete
	movePtr& m_retDeepCopy;  // will return deep copy of the visited object
};


class MW_5AXUTIL_API mwHelixOrientedMoveCreator
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> movePtr;
	typedef std::list<movePtr> MoveList;
	typedef geoDef::HelixdIn3ddHelper::HelixGeo Helix;
	typedef geoDef::HelixdIn3ddHelper::PointAnglePairList PointAnglePairList;

	mwHelixOrientedMoveCreator(
		const Helix& helix, const movePtr& startMove, const movePtr& endMove);

	const MoveList CreateMoveList(const double deltaTolerance, const double maxAngleDev) const;

private:
	mwHelixOrientedMoveCreator& operator=(const mwHelixOrientedMoveCreator&);  // = delete
	const Helix& m_helix;
	const movePtr m_startMove;
	const movePtr m_endMove;
};
}  // namespace cadcam
#endif  //	MW_MWCNCMOVEUTILS_HPP_
