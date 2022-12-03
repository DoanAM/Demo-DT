// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
/// this module describe the mwPosted5axTPTimeCalc class

#ifndef MW_MWPOSTED5AXTPTIMECALC_HPP_
#define MW_MWPOSTED5AXTPTIMECALC_HPP_
//#############################################################################
#include "mwUnitsFactory.hpp"
#include <list>
#include "mwAutoPointer.hpp"
#include "mwPosted3axMove.hpp"
#include "mwPosted4axMove.hpp"
#include "mwPosted5axMove.hpp"
#include "mwPosted6axMove.hpp"
#include "mwPostCommonDefinitions.hpp"
#include "mwMachDynamics.hpp"
#include "mwMachDef.hpp"
#include <set>
//#############################################################################
//! allows mwPosted5axTPTimeCalc of
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPosted5axTPTimeCalc
	{
	public:
		//#############################################################################
		static void Compute(posted3axListPtr& posted3axTP, const post::mwMachDynamics& machDynamics,
			const mwMachDefPtr& machineDef, const double TLC,
			const std::set<size_t>& reports = std::set<size_t>(/*NOT USED*/), const bool postStreaming = false,
			const post::mwPostedMovePtr& previousChunkLastMove = MW_NULL);
		//#############################################################################
		static void Compute(posted4axListPtr& posted4axTP, const post::mwMachDynamics& machDynamics,
			const mwMachDefPtr& machineDef, const double TLC,
			const std::set<size_t>& reports = std::set<size_t>(/*NOT USED*/), const bool postStreaming = false,
			const post::mwPostedMovePtr& previousChunkLastMove = MW_NULL);
		//#############################################################################
		static void Compute(posted5axListPtr& posted5axTP, const post::mwMachDynamics& machDynamics,
			const mwMachDefPtr& machineDef, const double TLC,
			const std::set<size_t>& reports = std::set<size_t>(/*NOT USED*/), const bool postStreaming = false,
			const post::mwPostedMovePtr& previousChunkLastMove = MW_NULL);
		//#############################################################################
		static void Compute(posted6axListPtr& posted6axTP, const post::mwMachDynamics& machDynamics,
			const mwMachDefPtr& machineDef, const double TLC,
			const std::set<size_t>& reports = std::set<size_t>(/*NOT USED*/), const bool postStreaming = false,
			const post::mwPostedMovePtr& previousChunkLastMove = MW_NULL);
		//#############################################################################
		static void SetTime(mwPostedMove& curr, const mwPostedMove& prev, const post::mwMachDynamics& machDynamics,
			const mwMachDefPtr& machineDef, const double TLC);
	private:
		//#############################################################################
		//! Constructor not allowed since it's a static class
		mwPosted5axTPTimeCalc();
		//#############################################################################
		static const double ComputeDist(const mwMachDefPtr& machineDef, const mwPostedMove& curr, const mwPostedMove& prev, const double TLC);
		//#############################################################################
		static const double ComputeDist2(const mwMachDefPtr& machineDef, const mwPostedMove& curr, const mwPostedMove& prev, const double TLC, const short axis);
		//#############################################################################
		static const double FakeDist(const mwMachDefPtr& machineDef, const mwPostedMove& curr, const mwPostedMove& prev, const double TLC);
		//#############################################################################
		static void AddReport(mwPostedMove& move, const std::set<size_t>& reports);
		//#############################################################################
		static void SetFirstMove(mwPostedMove& move, const post::mwMachDynamics& machDynamics);
		//#############################################################################
		static const double GetMaxAngleChange(const mwMachDefPtr& machineDef, const mwPostedMove& curr, const mwPostedMove& prev);
		//#############################################################################
	};
	//#############################################################################
}
//#############################################################################
#endif	//	MW_MWPOSTED5AXTPTIMECALC_HPP_