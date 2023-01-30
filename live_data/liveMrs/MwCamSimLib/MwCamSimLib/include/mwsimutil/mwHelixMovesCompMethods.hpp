// (C) 2003-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWHELIXMOVESCOMPMETHODS_HPP_
#define MW_MWHELIXMOVESCOMPMETHODS_HPP_

#include "mwCNCMove.hpp"
#include "mwCNCMoveUtils.hpp"
#include "mwCadcamMathConvs.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTCSijkGetter.hpp"
#include "mwTHelixFactory.hpp"


namespace cadcam
{
/// provides 2 different methods to compare if 2 Helix Moves are the same
class MW_5AXUTIL_API mwHelixMovesCompMethods
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> movePtr;
	typedef geoDef::mwTHelix<double, geoDef::CS3dd> Helix;
	typedef std::list<movePtr>::const_iterator ListMovesIterator;
	typedef mwCNCMove::point3d point3d;

	mwHelixMovesCompMethods(
		const Helix& helix,
		const movePtr& startMove,
		const movePtr& endMove,
		const double deltaTolerance,
		const double maxAngleDev);

	bool IsMoveValid(const movePtr& moveToCheck, const movePtr& refMove) const;

	bool IsMoveValid(
		const movePtr& moveToCheck, const movePtr& moveBefore, const movePtr& moveNext);

	bool AreMovesValid(const ListMovesIterator& startIt, const ListMovesIterator& endIt) const;

private:
	bool IsMoveValid(const movePtr& moveToCheck) const;

	mwHelixMovesCompMethods& operator=(const mwHelixMovesCompMethods&);  // = delete

	const Helix& m_helix;
	const movePtr m_startMove;
	const movePtr m_endMove;
	const double m_deltaTolerance;
	const double m_minCosDev;
};
}  // namespace cadcam
#endif  //	MW_MWHELIXMOVESCOMPMETHODS_HPP_
