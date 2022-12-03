// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMOTIONS_HPP_
#define MW_MWMOTIONS_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierNestedClasses.hpp"

#include <mwDefines.hpp>
#include <mwLanguageFeatures.hpp>
#include <mwMathUtilitiesDefinitions.hpp>
#include <mwTPoint3d.hpp>
#include <vector>

namespace boost
{
namespace serialization
{
class access;
}
}  // namespace boost

namespace VerifierUtil
{
/// Describes a motion by a finite non empty time equidistant ordered discrete set of frames.
class MW_VERIFIER_API mwMotion
{
public:
	typedef ::cadcam::mwTPoint3d<float> float3d;
	mwMotion() : m_isRapid(false) {}

	template <typename Iter>
	mwMotion(Iter begin, Iter end);
	template <typename Iter>
	mwMotion(Iter begin, Iter end, bool isRapid);

	void AddPosition(const Frame& frame);
	const Frame& GetPosition(const size_t timeIdx) const;
	const Frame& GetLastPosition() const;
	size_t GetNumOfTimeSteps() const;
	void RemoveTimeStepsAfter(size_t firstStepToRemove);
	bool IsRapid() const { return m_isRapid; };
	void SetIsRapid(const bool isRapid) { m_isRapid = isRapid; };
	void Reserve(const size_t n) { m_frames.reserve(n); }
	size_t GetCapacity() const { return m_frames.capacity(); }
	void Clear() { m_frames.clear(); }

#ifndef MW_USE_VS2008_COMPATIBILITY
	// explicitly specify move constructor, as VS2013 and below doesn't auto-generate it
	mwMotion(const mwMotion& other) : m_frames(other.m_frames), m_isRapid(other.m_isRapid) {}
	mwMotion(mwMotion&& other) MW_NOEXCEPT : m_frames(std::move(other.m_frames)),
											 m_isRapid(other.m_isRapid)
	{
	}

	mwMotion& operator=(const mwMotion& other)
	{
		m_frames = other.m_frames;
		m_isRapid = other.m_isRapid;
		return *this;
	}
	mwMotion& operator=(mwMotion&& other) MW_NOEXCEPT
	{
		m_frames = std::move(other.m_frames);
		m_isRapid = other.m_isRapid;
		return *this;
	}
#endif

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template <class Archive>
	void save(Archive& ar, const unsigned int version) const;
	template <class Archive>
	void load(Archive& ar, const unsigned int version);
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<Frame> m_frames;
	bool m_isRapid;
};

/// Collection of motions for one object
///
///	For all motions in it is assumed that they describe	the same
///	period with the same equidistant time stepping.	From this
///	follows that each Motion includes the same number of Frames.
class MW_VERIFIER_API mwMotionMap
{
public:
	void SetMotion(const int id, const mwMotion& motion);
#ifndef MW_USE_VS2008_COMPATIBILITY
	void SetMotion(const int id, mwMotion&& motion);
#endif
	void AddPosition(const int id, const Frame& position);
	void SetMotionType(const int id, const bool isRapid);
	void GetIds(std::vector<int>& ids) const;
	const mwMotion& GetMotion(const int id) const;
	mwMotion& GetOrCreateMotionRef(const int id) { return m_idToMotion[id]; }
	bool HasMotion(const int id) const;
	size_t GetNumOfTimeSteps() const;
	void RemoveTimeStepsAfter(const size_t firstStepToRemove);
	void RemoveMotion(const int id);
	void Clear();

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);
	typedef std::map<int, mwMotion> Container;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Container m_idToMotion;
};

/// Collection of motions for tools and meshes
class MW_VERIFIER_API mwMotions
{
public:
	/// The motions of tools in current tool - array.
	///	The key of this map is used as index in current tool - array.
	///	See @sa mwMachSimVerifier::SetTools()
	///	and @sa mwMachSimVerifier::SetCurrentCutTool *
	const mwMotionMap& GetToolMotions() const;
	mwMotionMap& GetToolMotionsRef();
	/// The motions of previously added collision meshes.
	///	The key of this map is used as CollisionMesh id.
	///	See @sa mwMachSimVerifier::AddCollisionMesh()
	const mwMotionMap& GetMeshMotions() const;
	mwMotionMap& GetMeshMotionsRef();
	size_t GetNumOfTimeSteps() const;
	void Clear();
	/// @param firstStepToRemove (first step is 0)
	void RemoveTimeStepsAfter(const size_t firstStepToRemove);

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);
	mwMotionMap m_toolMotions;
	mwMotionMap m_meshMotions;
};

/// Controls for mwMachSimVerifier::SimulateMotion
class MW_VERIFIER_API mwSimulateMotionOptions
{
public:
	mwSimulateMotionOptions();
	bool GetStopOnCollision() const;
	void SetStopOnCollision(const bool value);

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);
	bool m_stopOnCollision;
};

/// Results of mwMachSimVerifier::SimulateMotion
class MW_VERIFIER_API mwSimulateMotionResults
{
public:
	mwSimulateMotionResults();

	bool HasCollidingTools() const;
	bool WasMaterialRemoved() const;
	bool HasCollidingMeshes() const;
	/// @param For each given tool motion a VerificationResult is created. See @sa
	/// SimulateBufferedCuts
	const VerificationResultVector& GetAllVerificationResults() const;
	/// For each given collision mesh motion, which ends up in safety distances violation,
	///	a MeshCollisionReport with the smallest violated safety distance is created.
	///	See @sa GetCollidingMeshes(std::vector<MeshCollisionReport>& meshIds)
	const std::vector<MeshCollisionReport>& GetAllMeshCollisionReports() const;
	/// The index of the last simulated frame in given motions.
	///	If the full motion is simulated the index is
	///	(number of Frames) - 1. If the simulation should stop on the first
	///	collision the index is the index of the first frame, which ends up in
	///	collision.From this follows lastSimulatedFrameIdx is always >= 0;
	int GetLastSimulatedFrameIndex() const;

	void AddVerificationResult(const VerificationResult& result);
	void AddMeshCollisionReport(const MeshCollisionReport& report);
	void SetLastSimulatedFrameIdx(const int idx);
	void Reset();

private:
	bool m_hasCollidingTools;
	bool m_wasMaterialRemoved;
	bool m_hasCollidingMeshes;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	VerificationResultVector m_results;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<MeshCollisionReport> m_reports;
	int m_lastSimulatedFrameIdx;
};

template <typename Iter>
mwMotion::mwMotion(Iter begin, Iter end) : m_frames(begin, end), m_isRapid(false)
{
}

template <typename Iter>
mwMotion::mwMotion(Iter begin, Iter end, bool isRapid) : m_frames(begin, end), m_isRapid(isRapid)
{
}

}  // namespace VerifierUtil
#endif  //	MW_MWMOTIONS_HPP_
