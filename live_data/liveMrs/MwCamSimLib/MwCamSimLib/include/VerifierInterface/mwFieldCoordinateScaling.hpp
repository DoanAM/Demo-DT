// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWFIELDCOORDINATESCALING_HPP_
#define MW_MWFIELDCOORDINATESCALING_HPP_
#include <mwException.hpp>
#include <mwMathConstants.hpp>
#include <mwStringConversions.hpp>

#ifndef MW_GENERATE_DOCUMENTATION
#ifndef MW_FORCEINLINE
#ifdef _WIN32
#define MW_FORCEINLINE __forceinline
#else
#define MW_FORCEINLINE inline
#endif
#endif
#endif

namespace VerifierUtil
{
/// Used to transform between discrete coordinates (indices of nails/rays) and world-coordinates.
///
/// The dots in the following picture represent nails/rays. This class is for one dimension, for
/// example X or Y in a field, where Z is the direction of the nails/rays.
///
/// @image html "../../Verifier/dox/scaling.png"
///
class mwFieldCoordinateScaling
{
public:
	/// @hidden
	inline mwFieldCoordinateScaling();
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateEmpty();
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateWithExactSizeWorld(
		const float fieldOriginWorld, const float sizeWorld, const float scaling);
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateWithExactScaling(
		const float fieldOriginWorld, const float sizeWorld, const float scaling);
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateWithExactScalingAndCount(
		const float fieldOriginWorld, const float scaling, const int indexCount);
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateSnapToBorder(
		const float fieldOriginWorld, const float sizeWorld, const float scaling);
	/// @hidden
	inline static const mwFieldCoordinateScaling CreateUnsafe(
		const int indexCount,
		const float fieldOriginWorld,
		const float sizeWorld,
		const float scaling);
	inline static const int ComputeNumberOfNails(const float sizeWorld, const float scaling);

	/// Transform from world coordinates to discrete indices, use floor to round to the nearest
	/// index.
	inline const int WorldToIndexFloor(const float world) const;
	/// Transform from world coordinates to discrete indices, use ceil to round to the nearest
	/// index.
	inline const int WorldToIndexCeil(const float world) const;
	/// Transform from world coordinates to discrete indices, rounded to the nearest index.
	inline const int WorldToIndex(const float world) const;
	/// Transform from discrete indices to world coordinates.
	///
	/// This is equivalent to world=GetOrigin()+index*GetScaling().
	inline const float IndexToWorld(const int index) const;
	/// Check if index is in the range, that is in [0..GetIndexCount()).
	inline const bool IndexIsInRange(const int index) const;
	/// Return size of space occupied by all indices/nails.
	inline const float GetWorldSize() const;
	/// Return number of indices/nails.
	inline const int GetIndexCount() const;
	/// Return distance between two indices/nails.
	MW_FORCEINLINE const float GetScaling() const;
	MW_FORCEINLINE const double GetScalingWithDoublePrecision() const;
	MW_FORCEINLINE const double GetScalingReciprocalWithDoublePrecision() const;
	/// Return position of first index, which is also origin of the local coordinate system.
	MW_FORCEINLINE const float GetOrigin() const;

	inline bool operator==(const mwFieldCoordinateScaling& other) const;
	inline bool operator!=(const mwFieldCoordinateScaling& other) const;

	/// @hidden
	template <class Archive>
	void serialize(Archive& ar, const unsigned int /*file_version*/)
	{
		ar& m_IndexCount;
		ar& m_Scaling;
		ar& m_SizeWorld;
		ar& m_OriginWorld;
	}

private:
	int m_IndexCount;
	float m_Scaling;
	float m_SizeWorld;
	float m_OriginWorld;
};

inline mwFieldCoordinateScaling::mwFieldCoordinateScaling()
	: m_IndexCount(0), m_Scaling(1), m_SizeWorld(0), m_OriginWorld(0)
{
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateEmpty()
{
	return mwFieldCoordinateScaling();
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateWithExactSizeWorld(
	const float fieldOriginWorld, const float sizeWorld, const float scaling)
{
	mwFieldCoordinateScaling s;
	s.m_IndexCount = ComputeNumberOfNails(sizeWorld, scaling);
	s.m_Scaling = sizeWorld / (s.m_IndexCount - 1);  // -1 because last nails are on the border
	s.m_SizeWorld = sizeWorld;
	s.m_OriginWorld = fieldOriginWorld;
	return s;
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateWithExactScaling(
	const float fieldOriginWorld, const float sizeWorld, const float scaling)
{
	mwFieldCoordinateScaling s;
	s.m_IndexCount = ComputeNumberOfNails(sizeWorld, scaling);
	s.m_Scaling = scaling;
	s.m_SizeWorld = scaling * (s.m_IndexCount - 1);  // -1 because last nails are on the border
	s.m_OriginWorld = fieldOriginWorld;
	return s;
}

inline const int mwFieldCoordinateScaling::ComputeNumberOfNails(
	const float sizeWorld, const float scaling)
{
	if (scaling <= 0.0f)
		return 2;

	const int numberOfNails = int(floor(sizeWorld / scaling)) + 1;
	if (numberOfNails > mathdef::MW_MAX_INT)
	{
		throw misc::mwException(
			0,
			_T("Impossible to create: ") + misc::from_value(numberOfNails) +
				_T(" nails. Please reduce precision.\n") + _T("Maximum number of nails: ") +
				misc::from_value(mathdef::MW_MAX_INT));
	}

	return mathdef::mw_max(2, static_cast<int>(numberOfNails));
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateWithExactScalingAndCount(
	const float fieldOriginWorld, const float scaling, const int indexCount)
{
	mwFieldCoordinateScaling s;
	s.m_IndexCount = indexCount;
	s.m_Scaling = scaling;
	s.m_OriginWorld = fieldOriginWorld;
	s.m_SizeWorld = scaling * (s.m_IndexCount - 1);  // -1 because last nails are on the border
	return s;
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateSnapToBorder(
	const float fieldOriginWorld, const float sizeWorld, const float scaling)
{
	const float shrinkValue = 1e-6f;

	const int indexCount = ComputeNumberOfNails(sizeWorld, scaling);
	const float adjustedSizeWorld = sizeWorld - 2.f * shrinkValue;
	float adjustedScaling =
		adjustedSizeWorld / (indexCount - 1);  // -1 because last nails are on the border
	int tries = 0;

	// loop is needed to overcome numerical issues;
	while (tries < 10)
	{
		const float adjustedFieldOriginWorld = fieldOriginWorld + shrinkValue - adjustedScaling;
		mwFieldCoordinateScaling s = CreateWithExactScalingAndCount(
			adjustedFieldOriginWorld, adjustedScaling, indexCount + 2);

		if (s.m_OriginWorld > fieldOriginWorld)
			throw misc::mwException(0, _T("Unable to snap nail board to borders"));

		if (s.m_OriginWorld + s.m_SizeWorld < fieldOriginWorld + sizeWorld)
			throw misc::mwException(0, _T("Unable to snap nail board to borders"));

		if (s.m_OriginWorld + (s.m_IndexCount - 2) * s.m_Scaling < fieldOriginWorld + sizeWorld)
			return s;

		adjustedScaling -= 5e-7f;
		++tries;
	}

	throw misc::mwException(0, _T("Unable to snap nail board to borders"));
}

inline const mwFieldCoordinateScaling mwFieldCoordinateScaling::CreateUnsafe(
	const int indexCount, const float fieldOriginWorld, const float sizeWorld, const float scaling)
{
	mwFieldCoordinateScaling s;
	s.m_IndexCount = indexCount;
	s.m_Scaling = scaling;
	s.m_SizeWorld = sizeWorld;
	s.m_OriginWorld = fieldOriginWorld;
	return s;
}

inline const int mwFieldCoordinateScaling::WorldToIndexFloor(const float world) const
{
	const float relWorld = world - m_OriginWorld;
	const float scaledRelWorld = relWorld / m_Scaling;

	// fast floor function
	int index = static_cast<int>(scaledRelWorld);
	if (index > scaledRelWorld)
		index--;
	return index;
}

inline const int mwFieldCoordinateScaling::WorldToIndexCeil(const float world) const
{
	const float relWorld = world - m_OriginWorld;
	const float scaledRelWorld = relWorld / m_Scaling;

	// fast ceil function
	int index = static_cast<int>(scaledRelWorld);
	if (index < scaledRelWorld)
		index++;
	return index;
}

inline const int mwFieldCoordinateScaling::WorldToIndex(const float world) const
{
	return WorldToIndexFloor(world + (m_Scaling * 0.5f));
}

inline const float mwFieldCoordinateScaling::IndexToWorld(const int index) const
{
	const float world = m_Scaling * index + m_OriginWorld;
	return world;
}

inline const bool mwFieldCoordinateScaling::IndexIsInRange(const int index) const
{
	return ((index >= 0) && (index < m_IndexCount));
}

inline const float mwFieldCoordinateScaling::GetWorldSize() const
{
	return m_SizeWorld;
}

inline const int mwFieldCoordinateScaling::GetIndexCount() const
{
	return m_IndexCount;
}

MW_FORCEINLINE const float mwFieldCoordinateScaling::GetScaling() const
{
	return m_Scaling;
}

MW_FORCEINLINE const double mwFieldCoordinateScaling::GetScalingWithDoublePrecision() const
{
	return double(GetWorldSize()) / double(GetIndexCount() - 1);
}

MW_FORCEINLINE const double mwFieldCoordinateScaling::GetScalingReciprocalWithDoublePrecision()
	const
{
	return double(GetIndexCount() - 1) / double(GetWorldSize());
}

MW_FORCEINLINE const float mwFieldCoordinateScaling::GetOrigin() const
{
	return m_OriginWorld;
}

inline bool mwFieldCoordinateScaling::operator==(const mwFieldCoordinateScaling& other) const
{
	return (m_IndexCount == other.m_IndexCount) && (m_Scaling == other.m_Scaling) &&
		(m_SizeWorld == other.m_SizeWorld) && (m_OriginWorld == other.m_OriginWorld);
}

inline bool mwFieldCoordinateScaling::operator!=(const mwFieldCoordinateScaling& other) const
{
	return !(*this == other);
}
};  // namespace VerifierUtil
#endif  //	MW_MWFIELDCOORDINATESCALING_HPP_
