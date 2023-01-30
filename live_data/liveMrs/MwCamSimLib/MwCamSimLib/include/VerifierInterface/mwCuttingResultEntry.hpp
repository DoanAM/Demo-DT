// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWCUTTINGRESULTENTRY_HPP_
#define MW_MWCUTTINGRESULTENTRY_HPP_
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
/// One height-change of a nail at given 2d-coordinates (contains 2 sampling points describing an
/// interval on a ray).
struct mwCuttingResultEntry
{
	/// First index of nail-/ray-position in the 2d-grid. For example X for Z-parallel-nails.
	int Coord1;
	/// Second index of nail-/ray-position in the 2d-grid. For example Y for Z-parallel-nails.
	int Coord2;
	/// Number of the move/cut, from which this sampling points come from.
	///
	/// It's an internal enumeration, that is it starts at 0 for the first call to Cut(),
	/// BufferedCut(), CircularCut(), etc. It does not match the value from SetMoveID().
	int MoveNumber;
	/// Custom ID of move, which is set by mwMachSimVerifier::SetMoveId().
	float MoveId;

	typedef ::cadcam::mwTPoint3d<float> float3d;
	float3d n1;
	float3d n2;

	enum HeightValueDistributionType
	{
		FIRST_IS_INITIAL_SECOND_IS_CUT = 0,
		FIRST_IS_CUT_SECOND_IS_INITIAL,
		BOTH_ARE_INITIAL,
		BOTH_ARE_CUT,
		FIRST_IS_INSIDE_SECOND_IS_OUTSIDE,
		FIRST_IS_OUTSIDE_SECOND_IS_INSIDE,
		BOTH_ARE_INSIDE,
		BOTH_ARE_OUTSIDE
	};

	/// 3rd coordinate of the first sampling point (lower limit of the nail-interval). For example Z
	/// for Z-parallel nails.
	float Height1;
	/// 3rd coordinate of the second sampling point (upper limit of the nail-interval). For example
	/// Z for Z-parallel nails.
	float Height2;
	/// Defines, how to interpret Height1, and Height2.
	///
	/// If a height-value is in the initial field, it defines a point of the material, before the
	/// cutting was done. If it is in the cut field, it defines a point after the material was cut.
	/// One or both points are 'inside' or 'outside', if the tool does not remove material, see
	/// SetToolBehavior().
	HeightValueDistributionType HeightValueDistribution;

	inline static bool IsCutting(const HeightValueDistributionType distribution)
	{
		return (
			distribution == FIRST_IS_INITIAL_SECOND_IS_CUT ||
			distribution == FIRST_IS_CUT_SECOND_IS_INITIAL || distribution == BOTH_ARE_INITIAL ||
			distribution == BOTH_ARE_CUT);
	}

	inline static bool IsIntersectionOnly(const HeightValueDistributionType distribution)
	{
		return (
			distribution == FIRST_IS_INSIDE_SECOND_IS_OUTSIDE ||
			distribution == FIRST_IS_OUTSIDE_SECOND_IS_INSIDE || distribution == BOTH_ARE_INSIDE ||
			distribution == BOTH_ARE_OUTSIDE);
	}

	/// Absolute amount of removed material.
	inline const float GetCutHeight() const
	{
		float val = Height1 - Height2;
		if (val < 0)
		{
			val = -val;
		}
		return val;
	}

	/// Constructor initializing all member, see member for description. See
	/// CuttingResultEntry::Coord1, CuttingResultEntry::Coord2.
	mwCuttingResultEntry(
		const int coord1,
		const int coord2,
		const float height1,
		const float height2,
		const HeightValueDistributionType valueDistribution,
		const int moveNumber)
		: Coord1(coord1),
		  Coord2(coord2),
		  MoveNumber(moveNumber),
		  MoveId(-1),
		  Height1(height1),
		  Height2(height2),
		  HeightValueDistribution(valueDistribution)
	{
	}
};
typedef std::vector<mwCuttingResultEntry, std::allocator<mwCuttingResultEntry>>
	mwCuttingResultVector;
typedef mwCuttingResultVector* mwCuttingResultVectorPtr;
};  // namespace VerifierUtil
#endif  //	MW_MWCUTTINGRESULTENTRY_HPP_
