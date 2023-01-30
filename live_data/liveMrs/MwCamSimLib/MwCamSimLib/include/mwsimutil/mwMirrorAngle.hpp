// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwMirrorAngle class

//#############################################################################

#ifndef MW_MWMIRRORANGLE_HPP_
#define MW_MWMIRRORANGLE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"
#include "mwPosted5axMove.hpp"
#include "mwPosted6axMove.hpp"
#include <list>
//#############################################################################
namespace post
{
	//#############################################################################
	struct mwMirrorAngle;
	//#############################################################################
	//! 5 axes posted-toolpah :
	typedef std::pair<mwPosted5axMove, mwMirrorAngle>	posted5axMoveMirror;
	typedef misc::mwAutoPointer<posted5axMoveMirror>    posted5axMoveMirrorPtr;
	typedef std::pair<mwPosted5axMove, mwPosted5axMove>	posted5axMovePair;
	typedef misc::mwAutoPointer<posted5axMovePair>      posted5axMovePairPtr;
	typedef std::list<posted5axMoveMirror>				posted5axMoveMirrorList;
	//! 6 axes posted-toolpah :
	typedef std::pair<mwPosted6axMove, mwMirrorAngle>	posted6axMoveMirror;
	typedef misc::mwAutoPointer<posted6axMoveMirror>    posted6axMoveMirrorPtr;
	typedef std::pair<mwPosted6axMove, mwPosted6axMove>	posted6axMovePair;
	typedef misc::mwAutoPointer<posted6axMovePair>      posted6axMovePairPtr;
	typedef std::list<posted6axMoveMirror>				posted6axMoveMirrorList;
	//flag used intarnally to detect some tolerance issues...
	const size_t MW_ANGLE_INTERPOLATION_FLAG = 999999999; // one billion
	//#############################################################################
	struct MW_5AXUTIL_API mwMirrorAngle
	{
		//#############################################################################
		double m_second_angle0;
		double m_second_angle1;
		double m_second_angle2;
		cadcam::mwTPoint3d<double> m_secondAbsMachPos;
		//#############################################################################
		mwMirrorAngle()
		{
			m_second_angle0 = m_second_angle1 = m_second_angle2 = 0;
		}
		//#############################################################################
		mwMirrorAngle(
			double second_angle0,
			double second_angle1,
			cadcam::mwTPoint3d<double> secondAbsMachPos)
		{
			m_second_angle0 = second_angle0;
			m_second_angle1 = second_angle1;
			m_secondAbsMachPos = secondAbsMachPos;

			m_second_angle2 = mathdef::MW_MAX_DOUBLE;
		}
		mwMirrorAngle(
			double second_angle0,
			double second_angle1,
			double second_angle2,
			cadcam::mwTPoint3d<double> secondAbsMachPos)
		{
			m_second_angle0 = second_angle0;
			m_second_angle1 = second_angle1;
			m_second_angle2 = second_angle2;
			m_secondAbsMachPos = secondAbsMachPos;
		}
		//#############################################################################
		mwMirrorAngle(const mwMirrorAngle& toCopy)
			: m_second_angle0(toCopy.m_second_angle0)
			, m_second_angle1(toCopy.m_second_angle1)
			, m_second_angle2(toCopy.m_second_angle2)
			, m_secondAbsMachPos(toCopy.m_secondAbsMachPos)
		{

		}
		//#############################################################################
		static mwPosted5axMove GetFirst(const posted5axMoveMirror& mw)
		{
			return mw.first;
		}
		//#############################################################################
		static mwPosted5axMove& GetFirst(posted5axMoveMirror& mw)
		{
			return mw.first;
		}
		//#############################################################################
		static mwPosted5axMove GetSecond(const posted5axMoveMirror& mw)
		{
			mwPosted5axMove second(mw.first);
			second.SetAbsMachPos(mw.second.m_secondAbsMachPos);
			second.SetRotVal(mw.second.m_second_angle0, 0);
			second.SetRotVal(mw.second.m_second_angle1, 1);
			return second;
		}
		//#############################################################################
		static posted5axMoveMirror PairToMirror(const posted5axMovePair& pair)
		{
			posted5axMoveMirror mirror;
			mirror.first = pair.first;
			mirror.second.m_secondAbsMachPos = pair.second.GetAbsMachPos();
			mirror.second.m_second_angle0 = pair.second.GetRotVal(0);
			mirror.second.m_second_angle1 = pair.second.GetRotVal(1);
			return mirror;
		}
		//#############################################################################
		static mwPosted6axMove GetFirst(const posted6axMoveMirror& mw)
		{
			return mw.first;
		}
		//#############################################################################
		static mwPosted6axMove& GetFirst(posted6axMoveMirror& mw)
		{
			return mw.first;
		}
		//#############################################################################
		static mwPosted6axMove GetSecond(const posted6axMoveMirror& mw)
		{
			mwPosted6axMove second(mw.first);
			second.SetAbsMachPos(mw.second.m_secondAbsMachPos);
			second.SetRotVal(mw.second.m_second_angle0, 0);
			second.SetRotVal(mw.second.m_second_angle1, 1);
			second.SetRotVal(mw.second.m_second_angle2, 2);
			return second;
		}
		//#############################################################################
		static posted6axMoveMirror PairToMirror(const posted6axMovePair& pair)
		{
			posted6axMoveMirror mirror;
			mirror.first = pair.first;
			mirror.second.m_secondAbsMachPos = pair.second.GetAbsMachPos();
			mirror.second.m_second_angle0 = pair.second.GetRotVal(0);
			mirror.second.m_second_angle1 = pair.second.GetRotVal(1);
			mirror.second.m_second_angle2 = pair.second.GetRotVal(2);
			return mirror;
		}
		//#############################################################################
	};// end struct mwMirrorAngle
	//#############################################################################
	typedef misc::mwAutoPointer<mwMirrorAngle>            mirrorAnglePtr;
	typedef std::pair<mwPostedMovePtr, mirrorAnglePtr>	  postedMoveMirror;
	typedef std::pair<mwPostedMovePtr, mwPostedMovePtr>	  postedMovePtrPair;
	typedef misc::mwAutoPointer<mwPosted3axMove>          posted3axMovePtr;
	typedef misc::mwAutoPointer<mwPosted4axMove>          posted4axMovePtr;
	typedef misc::mwAutoPointer<mwPosted5axMove>          posted5axMovePtr;
	typedef misc::mwAutoPointer<mwPosted6axMove>          posted6axMovePtr;
	typedef std::pair<posted3axMovePtr, posted3axMovePtr> posted3axMovePtrPair;
	typedef std::pair<posted4axMovePtr, posted4axMovePtr> posted4axMovePtrPair;
	typedef std::pair<posted5axMovePtr, posted5axMovePtr> posted5axMovePtrPair;
	typedef std::pair<posted6axMovePtr, posted6axMovePtr> posted6axMovePtrPair;
	//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWMIRRORANGLE_HPP_
