// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVERIFIERNESTEDCLASSES_HPP_
#define MW_MWVERIFIERNESTEDCLASSES_HPP_

#include "mwCuttingResultEntry.hpp"
#include "mwFieldCoordinateScaling.hpp"
#include "mwSetCustomToolParameters.hpp"
#include "mwSetToolParameters.hpp"
#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierNestedEnums.hpp"
#include "mwvMeasureForward.hpp"
#include "mwvToolBehavior.hpp"

#include <cassert>
#include <map>
#include <mw3dBoundingBox.hpp>
#include <mw3dPolyLine.hpp>
#include <mwDefines.hpp>
#include <mwDeprecated.hpp>
#include <mwException.hpp>
#include <mwMathConstants.hpp>
#include <mwMathUtilitiesDefinitions.hpp>
#include <mwMesh.hpp>
#include <mwOverrideFinal.hpp>
#include <mwString.hpp>
#include <mwStringConversions.hpp>
#include <mwTPoint3d.hpp>
#include <mwWarningPragmas.hpp>

#ifdef NONE
#undef NONE
#endif

namespace misc
{
template <class T>
class mwAutoPointer;
};

namespace cadcam
{
class mwTool;
typedef ::misc::mwAutoPointer<const mwTool> mwConstToolPtr;
template <typename T>
class mwTMesh;
};  // namespace cadcam

class mwMachSimVerifier;
namespace Verifier
{
struct AdditionalChunkDataInternal;
}

namespace VerifierUtil
{
struct ChunkMovability;
struct ChunkMovabilityAlongMainAxisDirections;
class StaticSimulationData;

/// @deprecated Not used
struct MW_DEPRECATED("Not used") mwWirePlanesDefinition
{
	float m_plane1;
	float m_plane2;
	cadcam::mwTPoint3d<float> m_normal;
};
struct mwvChunkDetectionHandler
{
	virtual void OnChunksChanged(mwMachSimVerifier& verifier, size_t before, size_t after) = 0;
	inline virtual void OnChunksChanged(
		mwMachSimVerifier& verifier,
		const int chunksBefore,
		const int chunksNow,
		const int chunksCreated,
		const int chunksRemoved);

	virtual ~mwvChunkDetectionHandler() {}
};
inline void mwvChunkDetectionHandler::OnChunksChanged(
	mwMachSimVerifier&, const int, const int, const int, const int)
{
}
//---------------------------------------------------------------------------------------
struct mwvChunkDetectionKeepHandler : public mwvChunkDetectionHandler
{
	typedef ::cadcam::mwTPoint3d<float> float3d;

	/// For a description of parameters see mwMachSimVerifier::DeleteChunksNotTouching()
	mwvChunkDetectionKeepHandler(
		const std::vector<float3d>& fixturePoints, const float equalTolerance)
		: m_fixturePoints(fixturePoints), m_equalTolerance(equalTolerance)
	{
	}
	void OnChunksChanged(mwMachSimVerifier& verifier, size_t, size_t) MW_OVERRIDE;

protected:
	std::vector<float3d> m_fixturePoints;
	float m_equalTolerance;
};
//---------------------------------------------------------------------------------------
class mwvCollisionColorMode
{
public:
	/// Enable or disable red (default-color) for collisions on the stock surface
	///
	/// WARNING: Disabling the collision color is considered dangerous, as real collisions are no
	/// longer highlighted on the material!
	inline void SetCollisionColoringEnabled(const bool enabled)
	{
		m_collisionColoringEnabled = enabled;
	}
	/// @sa SetCollisionColoringEnabled()
	inline bool GetCollisionColoringEnabled() const { return m_collisionColoringEnabled; }
	/// Enable or disable projection of collision color, when a collision-marked surface is cut
	/// again.
	inline void SetCollisionColorProjectionEnabled(const bool enabled)
	{
		m_collisionColorProjectionEnabled = enabled;
	}
	/// @sa SetCollisionColorProjectionEnabled()
	inline bool GetCollisionColorProjectionEnabled() const
	{
		return m_collisionColorProjectionEnabled;
	}
	/// Set, if on a collision tool vs stock, only the colliding tool-element will mark the
	/// stock-surface with red (default-color).
	inline void SetMarkCollidingToolElementOnly(const bool enabled)
	{
		m_markCollidingToolElementOnly = enabled;
	}
	/// @sa SetMarkCollidingToolElementOnly()
	inline bool GetMarkCollidingToolElementOnly() const { return m_markCollidingToolElementOnly; }
	/// Constructor with default-settings of all members, @sa SetCollisionColoringEnabled(), @sa
	/// SetCollisionColorProjectionEnabled(), @sa SetMarkCollidingToolElementOnly()
	inline mwvCollisionColorMode(
		const bool collisionColoringEnabled = true,
		const bool collisionColorProjectionEnabled = false,
		const bool markCollidingToolElementOnly = false)
		: m_collisionColoringEnabled(collisionColoringEnabled),
		  m_collisionColorProjectionEnabled(collisionColorProjectionEnabled),
		  m_markCollidingToolElementOnly(markCollidingToolElementOnly)
	{
	}
	inline bool operator==(const mwvCollisionColorMode& c) const
	{
		return m_collisionColoringEnabled == c.m_collisionColoringEnabled &&
			m_collisionColorProjectionEnabled == c.m_collisionColorProjectionEnabled &&
			m_markCollidingToolElementOnly == c.m_markCollidingToolElementOnly;
	}

	inline bool operator!=(const mwvCollisionColorMode& c) const { return !(*this == c); }

private:
	bool m_collisionColoringEnabled;
	bool m_collisionColorProjectionEnabled;
	bool m_markCollidingToolElementOnly;
};
//---------------------------------------------------------------------------------------
typedef MATH::Frame<float> Frame;
//---------------------------------------------------------------------------------------
class mwvExperimentalSettings
{
public:
	/// Size of space partition for triangulation.
	///
	/// The sub-volume size for the simulation. The sub-volume size specifies the partition of the
	/// workpiece in sub-volumes and is used during the simulation to ensure that only changed parts
	/// of the workpiece are updated. The value of the sub-volume size is set to 32 by default and
	/// must always be a number of 2^x. Decreasing this value can increase performance of your
	/// simulation. Please do only change this value after close checking if this is really needed
	/// for your purpose.
	int m_subVolumeSize;

	/// 5 axis SolidStampingMaxAngle
	float m_solidStampingMaxAngle5x;
	float m_solidStampingMaxError;

	bool m_disable2dHoleOptimization;

	/// Decimation quality for abstract renderer
	float m_decimationQuality;

	/// Stop targets from being changed from outside
	bool m_targetsFinal;

	/// use fast mesh decimation on GetMesh
	bool m_fastMeshDecimation;

	/// Increases number of parallel nails in the turning mode
	int m_refineFactorParallelNails;

	/// Disables retriangulation when changing the color scheme. This method can be used if you know
	/// that your changes to mwMachSimVerifierColorScheme don't affect the next Draw() or Render()
	/// result.
	/// @warning This flag should only be enabled temporarily, if at all!
	bool m_suppressRedrawOnWorkpieceDrawModeChange;

	/// Check if the sweep distance should be used for normal calculation
	bool m_useSweepDist;

	/// range of moves for sweep distance
	int m_sweepDistMoveRange;

	bool m_correctStampingRotation;

	/// If true, will always use mesh cutting for 5x tool paths with revolved tools.
	bool m_useMeshToolsFor5x;

	/// decide whether to use sharp edge interpolation for contour extraction
	bool m_contourPointsMustLieOnWorkpieceGrid;

	bool m_disableParallelTriangulation;

	bool m_enableSharpEdges;

	bool m_useTurningToolOctree;

	bool m_treatBooleanAsToolOperation;

	float m_meshCuttingMaxStepAngle;

	bool m_disableParallelCutting;

	/// supernail triangulation creates very few triangles, but may lead to T-vertices in the mesh.
	bool m_enableSupernailTriangulation;

	bool m_unsignedGougeExcess;

	bool m_precomputeOnAddCollisionMesh;

	/// use kd-tree (instead of octree) subdivision to create less triangles
	bool m_useNewSubdivision;

	/// use turning triangulation for rotationally symmetric stock parts
	bool m_turningTriangulationForMilling;

	/// tune CSB playback for performance, by limiting the amount of information in output messages
	bool m_fastCSBPlayback;

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	/// construct with default values
	mwvExperimentalSettings()
		: m_subVolumeSize(32),
		  m_solidStampingMaxAngle5x(1.0f),
		  m_solidStampingMaxError(3e38f),
		  m_disable2dHoleOptimization(false),
		  m_decimationQuality(0.0f),
		  m_targetsFinal(false),
		  m_fastMeshDecimation(true),
		  m_refineFactorParallelNails(1),
		  m_suppressRedrawOnWorkpieceDrawModeChange(false),
		  m_useSweepDist(true),
		  m_sweepDistMoveRange(0),
		  m_correctStampingRotation(false),
		  m_useMeshToolsFor5x(false),
		  m_contourPointsMustLieOnWorkpieceGrid(false),
		  m_disableParallelTriangulation(false),
		  m_enableSharpEdges(true),
		  m_useTurningToolOctree(false),
		  m_treatBooleanAsToolOperation(false),
		  m_meshCuttingMaxStepAngle(mathdef::MW_MAX_FLOAT),
		  m_disableParallelCutting(false),
		  m_enableSupernailTriangulation(true),
		  m_unsignedGougeExcess(false),
		  m_precomputeOnAddCollisionMesh(false),
		  m_useNewSubdivision(false),
		  m_turningTriangulationForMilling(true),
		  m_fastCSBPlayback(false){};
	MW_WARNING_POP

	bool operator==(const mwvExperimentalSettings& that) const
	{
		return m_subVolumeSize == that.m_subVolumeSize &&
			m_solidStampingMaxAngle5x == that.m_solidStampingMaxAngle5x &&
			m_disable2dHoleOptimization == that.m_disable2dHoleOptimization &&
			m_decimationQuality == that.m_decimationQuality &&
			m_solidStampingMaxError == that.m_solidStampingMaxError &&
			m_targetsFinal == that.m_targetsFinal &&
			m_fastMeshDecimation == that.m_fastMeshDecimation &&
			m_refineFactorParallelNails == that.m_refineFactorParallelNails &&
			m_suppressRedrawOnWorkpieceDrawModeChange ==
			that.m_suppressRedrawOnWorkpieceDrawModeChange &&
			m_useSweepDist == that.m_useSweepDist &&
			m_sweepDistMoveRange == that.m_sweepDistMoveRange &&
			m_correctStampingRotation == that.m_correctStampingRotation &&
			m_useMeshToolsFor5x == that.m_useMeshToolsFor5x &&
			m_contourPointsMustLieOnWorkpieceGrid == that.m_contourPointsMustLieOnWorkpieceGrid &&
			m_disableParallelTriangulation == that.m_disableParallelTriangulation &&
			m_enableSharpEdges == that.m_enableSharpEdges &&
			m_useTurningToolOctree == that.m_useTurningToolOctree &&
			m_treatBooleanAsToolOperation == that.m_treatBooleanAsToolOperation &&
			m_meshCuttingMaxStepAngle == that.m_meshCuttingMaxStepAngle &&
			m_disableParallelCutting == that.m_disableParallelCutting &&
			m_enableSupernailTriangulation == that.m_enableSupernailTriangulation &&
			m_unsignedGougeExcess == that.m_unsignedGougeExcess &&
			m_precomputeOnAddCollisionMesh == that.m_precomputeOnAddCollisionMesh &&
			m_useNewSubdivision == that.m_useNewSubdivision &&
			m_turningTriangulationForMilling == that.m_turningTriangulationForMilling &&
			m_fastCSBPlayback == that.m_fastCSBPlayback;
	}
};
/// Experimental, don't use in production code yet!
namespace mwRawNailAccess
{
class NailPoint
{
private:
	float m_height;
	cadcam::mwTPoint3d<float> m_normal;
	int m_moveNumber;
	int m_toolNumber;
	// TODO: extended data like color-id, collision
public:
	inline float GetHeight() const { return m_height; }
	inline cadcam::mwTPoint3d<float> GetNormal() const { return m_normal; }
	inline int GetMoveNumber() const { return m_moveNumber; }
	inline int GetToolNumber() const { return m_toolNumber; }
	inline NailPoint(
		const float height,
		const cadcam::mwTPoint3d<float>& normal,
		const int moveNumber,
		const int toolNumber)
		: m_height(height), m_normal(normal), m_moveNumber(moveNumber), m_toolNumber(toolNumber)
	{
	}
};

class Nail
{
public:
	// getters
	inline unsigned int GetX() const { return m_x; }
	inline unsigned int GetY() const { return m_y; }
	inline const NailPoint* GetPointArray() const { return m_pointArray; }
	/// make sure that index < GetPointCount()!
	inline const NailPoint& GetPointAt(const size_t index) const { return m_pointArray[index]; }
	inline size_t GetPointCount() const { return m_pointCount; }
	// construction
	inline Nail(const unsigned int x, const unsigned int y)
		: m_x(x), m_y(y), m_pointArray(0), m_pointCount(0)
	{
	}
	inline void SetPoints(const NailPoint* begin, const size_t count)
	{
		m_pointArray = begin;
		m_pointCount = count;
	}

private:
	unsigned int m_x;
	unsigned int m_y;
	const NailPoint* m_pointArray;
	size_t m_pointCount;
};
struct Callback
{
	virtual void OnNailsChanged(const Nail* nails, const size_t numOfNails) = 0;
	virtual void OnNailsClear() = 0;
	inline virtual ~Callback(){};
};
};  // namespace mwRawNailAccess

struct ChunkInfo
{
	inline ChunkInfo()
		: numSurfacePoints(0),
		  volumeUpperBound(0),
		  volume(mathdef::MW_FLOAT_NAN),
		  isValidChunk(false)
	{
	}

	inline ChunkInfo(
		const size_t numSurfacePoints,
		const cadcam::mwTPoint3d<float>& bboxLower,
		const cadcam::mwTPoint3d<float>& bboxUpper,
		const float volumeUpperBound,
		const float volume = mathdef::MW_FLOAT_NAN)
		: numSurfacePoints(numSurfacePoints),
		  bboxLower(bboxLower),
		  bboxUpper(bboxUpper),
		  volumeUpperBound(volumeUpperBound),
		  volume(volume),
		  isValidChunk(true)
	{
	}

	inline ~ChunkInfo() {}

	inline size_t GetNumberOfSurfacePoints() const { return numSurfacePoints; }
	inline void GetBoundingBox(
		cadcam::mwTPoint3d<float>& lowerLeftNearCorner,
		cadcam::mwTPoint3d<float>& upperRightFarCorner) const
	{
		lowerLeftNearCorner = bboxLower;
		upperRightFarCorner = bboxUpper;
	}
	inline float GetUpperBoundForVolume() const { return volumeUpperBound; }
	inline bool HasVolume() const { return !mathdef::is_nan(volume); }
	inline float GetVolume() const { return volume; }
	inline bool IsValidChunk() const { return isValidChunk; }

private:
	size_t numSurfacePoints;
	cadcam::mwTPoint3d<float> bboxLower;
	cadcam::mwTPoint3d<float> bboxUpper;
	float volumeUpperBound;
	float volume;
	bool isValidChunk;
};

namespace Commands
{
struct Command;
typedef misc::mwAutoPointer<Command> CommandPtr;
}  // namespace Commands

class PrecomputeToolCondition
{
public:
	/// Precompute only the given tool (default: precompute all currently set tools)
	PrecomputeToolCondition& SetToolIdx(const int idx)
	{
		toolIdx = idx;
		return *this;
	}
	int GetToolIdx() const { return toolIdx; }

	/// Precompute tool model for collision checking (default true)
	PrecomputeToolCondition& ForCollisionCheck(bool use)
	{
		collisionCheck = use;
		return *this;
	}
	bool GetCollisionCheck() const { return collisionCheck; }

	/// Precompute tool model for rapid moves (default: true)
	PrecomputeToolCondition& ForRapidCheck(bool use)
	{
		rapidCheck = use;
		return *this;
	}
	bool GetRapidCheck() const { return rapidCheck; }

	/// Precompute tool model for cutting (default: true)
	PrecomputeToolCondition& ForCutting(bool use)
	{
		cutting = use;
		return *this;
	}
	bool GetCutting() const { return cutting; }

	/// Precompute tool model for given safety distances (default: none)
#ifndef MW_USE_VS2008_COMPATIBILITY
	PrecomputeToolCondition& ForSafetyDistances(std::vector<float> distances)
	{
		safetyDistances = std::move(distances);
		return *this;
	}
#else
	PrecomputeToolCondition& ForSafetyDistances(const std::vector<float>& distances)
	{
		safetyDistances = distances;
		return *this;
	}
#endif
	const std::vector<float>& GetSafetyDistances() const { return safetyDistances; }

	/// Precompute for turning mode (default: true)
	PrecomputeToolCondition& ForTurning(bool use)
	{
		turning = use;
		return *this;
	}
	bool GetTurning() const { return turning; }

	/// Precompute for milling mode (default: true)
	PrecomputeToolCondition& ForMilling(bool use)
	{
		milling = use;
		return *this;
	}
	bool GetMilling() const { return milling; }

	enum ElementType
	{
		CUTTING = 1,
		NON_CUTTING = 2,
		ARBOR = 4,
		HOLDER = 8
	};
	/// Precompute only for selected set of tool elements (default: all)
	///
	/// @param mask  OR-concatenation of ElementType
	PrecomputeToolCondition& ForToolParts(int mask)
	{
		toolParts = mask;
		return *this;
	}
	int GetToolParts() const { return toolParts; }

	PrecomputeToolCondition()
		: toolIdx(-1),
		  collisionCheck(true),
		  rapidCheck(true),
		  cutting(true),
		  turning(true),
		  milling(true),
		  toolParts(CUTTING | NON_CUTTING | ARBOR | HOLDER){};

private:
	int toolIdx;
	bool collisionCheck;
	bool rapidCheck;
	bool cutting;
	std::vector<float> safetyDistances;
	bool turning;
	bool milling;
	int toolParts;
};

struct mwExperimentalMethods
{
	/// Register callback-objects for direct nail-access
	///
	/// Callbacks are called, when nails change and include some selected data from the nails to
	/// display them.
	/// * @param xyPlane Callback for nails on xyPlane. Use 0 to unregister. Make sure object lives
	/// until it is unregistered or cutsim is freed.
	/// * @param yzPlane Callback for nails on yzPlane. Use 0 to unregister. Make sure object lives
	/// until it is unregistered or cutsim is freed.
	/// * @param zxPlane Callback for nails on zxPlane. Use 0 to unregister. Make sure object lives
	/// until it is unregistered or cutsim is freed.
	/// * @param updateLimit Upper limit for number of nails in mwvNailCallback::OnNailsChanged().
	/// Use a small value to keep memory overhead small.
	///
	virtual void SetNailCallbacks(
		mwRawNailAccess::Callback* xyPlane,
		mwRawNailAccess::Callback* yzPlane,
		mwRawNailAccess::Callback* zxPlane,
		const size_t updateLimit = mathdef::mw_maxvalue(size_t())) = 0;
	/// Puts all nails into currently registered callback, @sa SetNailCallbacks
	virtual void GetAllNails() = 0;

	/// Returns information regarding requested chunk
	//
	// Includes:
	// - GetVolume()
	// - GetBoundingBox()
	//
	// Note if the chunk requested does not exist, this method will return an empty chunkInfo. You
	// can check for this by calling chunkInfo.IsValidChunk(). This was introduced because splinter
	// removal can currently happen unexpectedly to the user, leading to empty chunks.
	//
	// For now, volume can only be calculated for the 5axis nail model. For turning- and 3axis model
	// we only provide the upper bound.
	virtual ChunkInfo GetChunkInfo(int chunkId) = 0;
	virtual void SetChunkVisibility(int chunkId, bool visible) = 0;
	virtual bool IsChunkVisible(int chunkId) const = 0;

	/// Returns the volume of a chunk
	// This is currently only a shorthand for GetChunkInfo(chunk).GetVolume(), and will likely be
	// removed
	virtual float GetChunkVolume(int chunk) = 0;

	/// Returns the distance all chunks in stock travel in any one of the six main axis directions
	/// before they hit another chunk
	//
	// The vector contains one entry for each chunk in the stock: how far can that chunk travel in
	// each main axis direction? The individual entry contains accessor methods to help get the data
	// for the requested direction.
	//
	// Implementation note: See GetChunkMovabilityInDirection
	virtual std::vector<VerifierUtil::ChunkMovabilityAlongMainAxisDirections>
	GetChunkMovabilityAlongAllMainAxes() = 0;

	/// Returns the distance the given chunk can travel in the given direction before it hits
	/// another chunk
	//
	// The permitted directions are restricted to the three main axes:
	// (1, 0, 0), (0, 1, 0), (0, 0, 1),
	// (-1, 0, 0), (0, -1, 0), (0, 0, -1)
	//
	// Implementation note: the movability is currently calculated for all axes simultaneously and
	// cached, with this method reading the formerly calculated data for the requested axis. So
	// there is currently no performance benefit in calling this method over the
	// GetChunkMovabilityAlongAllMainAxes method.
	// Cached data is returned unless the stock changes (by cutting, deleting or splitting off
	// chunks...), which triggers a recalculation.
	virtual VerifierUtil::ChunkMovability GetChunkMovabilityInDirection(
		const int chunkId, const cadcam::mwTPoint3d<float>& direction) = 0;

	/// Returns the silhouette of the current tool
	///
	/// If no tool is set or there wasn't any cut so far an empty contour is returned.
	///
	// 		virtual cadcam::mw2dContour<double > GetCurrentToolSilhouette() const = 0;

	/// Mesh type definition
	typedef cadcam::mwTMesh<float> Mesh;
	/// Mesh pointer type definition
	typedef misc::mwAutoPointer<Mesh> MeshPtr;

	/// Calculate a mesh from the cutting results (if they are enabled)
	///
	/// This method returns current geometry of the cutting results (if they are enabled) as a mesh
	/// of triangles. the method can be used in two ways depending of your intended usage. /item
	/// First the result mesh can be retrieved as a point to a mwTMesh object. To do this the
	/// parameter filename needs to be MW_NULL. /item  Second the result mesh can be streamed
	/// directly to hard disk ( STL format binary) using the file name given in the parameters. If
	/// used in this way the return value will allways be MW_NULL.
	///
	/// Both usages have advantages and disadvantages. Writing to disc is inefficient when the
	/// result mesh needs to be used in the application afterwards and again reloaded from disk. The
	/// advantage of this method is that the mesh can be retrieved from very big (high detail) stock
	/// models. The number of triangles can easily reach one million and more. On the other hand
	/// copying the result triangles directly into a mwTMesh object may lead to very big mwtMesh
	/// objects which will use up the free memory and if this happens make the whole application
	/// hard to control. But if the mesh is needed in the calling application as one single mwTMesh
	/// objects this is the best way to call this method. The mesh will be decimated according to
	/// the decimation tolerance, if no tolerance is set a non-decimated mesh will be exported.
	/// @param [in] filename the name of the file in STL format to which the triangles will be
	/// streamed. @param [in] tolerance decimation tolerance (if 0 old GetMesh()-method is applied)
	/// @return pointer to the polygonal geometry object. @sa Description of the stl file format
	/// http://en.wikipedia.org/wiki/STL_%28file_format%29 .
	virtual MeshPtr GetCuttingResultMesh(
		misc::mwstring* filename = MW_NULL, float tolerance = 0, bool decimate = true) = 0;

	virtual int GetNumberOfNailDefects() = 0;
	virtual void InvertStock() = 0;

	virtual void SetToolRefineFactor(const int toolId, const int refineFactor) = 0;
	virtual void ResetToolRefineFactors() = 0;

	struct SimpleToolBehavior
	{
#if defined(_MSC_VER) && _MSC_VER <= 1600  // VS2008 and before
		typedef unsigned __int32 uint32_t;
		typedef unsigned __int8 uint8_t;
#endif
		struct Element
		{
			Element(bool isSimulated, bool isCollisionChecked)
			{
				m_data = (uint8_t)isSimulated | ((uint8_t)isCollisionChecked << 1);
			}
			Element(uint8_t privateData) : m_data(privateData) {}
			bool IsSimulated() { return (m_data & 1) != 0; }
			bool IsCollisionChecked() { return (m_data & 2) != 0; }

			uint8_t m_data;
		};
		SimpleToolBehavior(Element flute, Element shaft, Element arbor, Element holder)
		{
			m_data =
				flute.m_data | (shaft.m_data << 2) | (arbor.m_data << 4) | (holder.m_data << 6);
		}
		SimpleToolBehavior(uint32_t privateData = 0) : m_data(privateData) {}

		Element GetFlute() { return Element(uint8_t(m_data)); }
		Element GetShaft() { return Element(uint8_t(m_data >> 2)); }
		Element GetArbor() { return Element(uint8_t(m_data >> 4)); }
		Element GetHolder() { return Element(uint8_t(m_data >> 6)); }

		uint32_t m_data;
	};
	struct SimpleMove
	{
		Frame start;
		Frame end;
		int tool;
		float startDistance;
		SimpleToolBehavior toolBehavior;
	};
	struct SimpleTool
	{
		float radius;
		float height;
		cadcam::mw2dContour<double>::Ptr profile[4];
	};
	virtual bool GetToolsAndMoves(
		std::map<int, SimpleTool>& tools, std::map<int, SimpleMove>& moves) = 0;
	virtual void GetMoveIdsIntersectingBox(
		const cadcam::mw3dBoundingBox<float>& box, std::vector<int>& moves) = 0;
	virtual void GetMoveIdsInRendererGroup(
		const int triangleGroupId, std::vector<int>& moveIds) = 0;
	virtual const std::vector<cadcam::mwfMesh::Ptr>& GetInitialStockMeshes() = 0;
	virtual void GetTriangleIdsInRendererGroups(
		std::vector<std::vector<int>>& idsPerGroup, int& groupOffset) = 0;
	virtual bool GetIsInTurningMode() = 0;

	/// Forget about the current renderer. The next Render() call will return all triangles, and not
	/// delete any rendered subvolumes.
	virtual void ForgetRenderer() = 0;

	/// Get a list of all previously set tool ids, in their original order of being set
	//
	// Ids can legally occur several times in the list, for instance if the user called SetTool() to
	// set the current cutting tool to some tool he had set before, and reuses the old id.
	//
	// e.g. [0,1,2,0,3] is a valid sequence
	//
	virtual void GetAllCustomToolIds(std::vector<int>& toolIds) const = 0;

	/// Reassign new tool-ids, replacing previously set tool ids
	//
	// To be used together with companion method GetAllCustomToolIds().
	// The size must match that returned by GetAllCustomToolIds().
	//
	virtual void SetAllCustomToolIds(const std::vector<int>& toolIds) = 0;

	virtual void EnableStopOnCollision(bool enabled = true) = 0;
	virtual bool IsStopOnCollisionEnabled() const = 0;

	/// return the raw "removed volume" values, i.e. non-tracked moves will have -1 as values. The
	/// second vector will be filled with the assigned move ids.
	virtual void GetAllRemovedVolumes(
		std::vector<float>& volumePerMove, std::vector<float>& moveIds) const = 0;

	virtual std::vector<std::vector<cadcam::mw3dfPolyLine>> GetEngagementContoursOnStock() = 0;
	virtual std::vector<std::vector<cadcam::mw2dfPolyLine>> GetEngagementContoursOnTool() = 0;
	virtual std::vector<float> GetEngagementMoveLengthEstimate() const = 0;

	/// Get the engagement transformations for all previous cuts.
	/// - An engagement-system is the tool-system at the end position of the move, additionally
	/// rotated around the tool-axis in order to get X-axis looking into the feed-direction.
	/// - Only works with new tracking, see EnableEngagementTracking.
	/// @param transforms Gets a transformation per move from the engagement-system into the
	/// world-system.
	virtual void GetEngagementTransforms(std::vector<Frame>& transforms) = 0;

	/// Precomputes some structures needed for cutting, which are usually initialized on first use.
	///
	/// This may improve response times during the simulation.
	///
	///	The structures initialized here depend on:
	///	  * current collision tolerance
	///	  * current stock
	///	  * current tool behavior (SimulateHoles)
	///
	///	When the tools are changed the precomputation is discarded.
	///	The cache survives changing tolerances or safety distances, but it won't be
	///	automatically filled for the new distances.
	///
	///	This API currently expects a 5axis stock to be present (MWV_FM_DEXELBLOCK). If the
	///	preconditions are not met an exception may be thrown.
	virtual void PrecomputeTool(const PrecomputeToolCondition& condition) = 0;

	/// Converts the internal data representation. If this function is not called after changing the
	/// stock spindle mode, then the conversion is delayed until it is needed (during cutting or
	/// drawing).
	virtual void ApplyStockSpindleMode() = 0;

	/// @name Painting
	/// @{
	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	virtual void SetPaintDirection(const cadcam::mwPoint3df& direction) = 0;
	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	virtual void SetPaintOcclusionDirection(const cadcam::mwPoint3df& direction) = 0;

	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	virtual void SetPaintDirectionForCurrentTool(const cadcam::mwPoint3df& direction) = 0;
	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	virtual void SetOcclusionDirectionForCurrentTool(const cadcam::mwPoint3df& direction) = 0;

	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	static void ApplyPaintDirection(
		mwvToolBehavior& toolBehavior, const cadcam::mwPoint3df& direction)
	{
		toolBehavior.SetPaintDirection(direction);
	}
	// MW_DEPRECATED("Use mwvToolBehavior::SetPaintDirection() instead")
	static void ApplyPaintOcclusionDirection(
		mwvToolBehavior& toolBehavior, const cadcam::mwPoint3df& direction)
	{
		ApplyPaintDirection(toolBehavior, -direction);
	}

	// MW_DEPRECATED("Use mwvToolBehavior::GetPaintDirection() instead")
	static inline const cadcam::mwPoint3df& GetPaintDirection(const mwvToolBehavior& toolBehavior)
	{
		return toolBehavior.GetPaintDirection();
	}
	// MW_DEPRECATED("Use mwvToolBehavior::GetPaintDirection() instead")
	static cadcam::mwPoint3df GetPaintOcclusionDirection(const mwvToolBehavior& toolBehavior)
	{
		return -GetPaintDirection(toolBehavior);
	}
	/// @}

	/// @name Simulation State Management
	///	The following methods allow you to store the simulation state at some point and then be
	/// able to restore it back.
	/// @{
	MW_DEPRECATED("Moved to Verifier API")
	virtual std::pair<misc::mwstring, bool> CreateRestorePoint() = 0;

	MW_DEPRECATED("Moved to Verifier API")
	virtual void Restore(const misc::mwstring& id) = 0;

	MW_DEPRECATED("Moved to Verifier API")
	virtual void RemoveRestorePoint(const misc::mwstring& id) = 0;

	MW_DEPRECATED("Moved to Verifier API")
	virtual void RemoveAllRestorePoints() = 0;
	/// @}

	/// Reads command from currently open player into command struct
	//
	// This is a complementary function to PlayNextStep(), in that it reads a command from a players
	// file or stream, but does not execute it. This allows to manipulate it before execution or
	// skip it altogether.
	//
	// This feature is currently only implemented for a very limited number of verifier commands.
	// If reading is not implemented for a given command, an empty auto-pointer is returned.
	//
	// * @see mwMachSimVerifier::PlayNextStep()
	// * @see mwMachSimVerifier::IsPlaying()
	//
	// * You can switch between using ReadNextStep and PlayNextStep at will
	// * If an empty auto-pointer is returned, this can mean one of the following:
	//   (a) Reading the current command is not implemented: you then MUST call PlayNextStep next
	//   (b) There is no command left to read: you can stop playing
	// * You can find out which of these two is the case by calling IsPlaying()
	// * Implement the CommandVisitor or the DefaultCommandVisitor to manipulate commands
	virtual Commands::CommandPtr ReadNextStep() = 0;

	/// Will create a string describing the command and its parameters
	virtual misc::mwstring DescribeCommand(Commands::Command& command) = 0;

	/// Will run the given command and return it's description
	virtual void RunCommand(Commands::Command& command) = 0;

	virtual void RaiseCustomWarning(
		VerifierUtil::NotificationCode code, const misc::mwstring& message) = 0;

	/// Add stock to current stock
	///
	/// Stock and current stock must have exactly the same world position, size and precision.
	/// Only supported for the 5-axis model.
	/// Warning: Undefined behavior for refine, internal vertex attributes are not cleared!
	/// @return true if current stock has been changed, false otherwise.
	virtual bool BooleanUnify(mwMachSimVerifier& stock) = 0;

	/// Subtract stock from current stock
	///
	/// Stock and current stock must have exactly the same world position, size and precision.
	/// Only supported for the 5-axis model.
	/// Warning: Undefined behavior for refine, internal vertex attributes are not cleared!
	/// @return true if current stock has been changed, false otherwise.
	virtual bool BooleanSubtract(mwMachSimVerifier& stock) = 0;

	/// Intersect current stock with stock
	///
	/// Stock and current stock must have exactly the same world position, size and precision.
	/// Only supported for the 5-axis model.
	/// Warning: Undefined behavior for refine, internal vertex attributes are not cleared!
	/// @return true if current stock has been changed, false otherwise.
	virtual bool BooleanIntersect(mwMachSimVerifier& stock) = 0;

	/// Value of internal counter of stock changes.
	/// Used in order to track changes of the stocks model.
	/// @return non-zero value
	virtual unsigned GetStockChangeNum() const = 0;

	/// Value of internal counter of performed triangulations.
	/// Used in order to track changes of the stocks mesh.
	/// @return non-zero value
	virtual unsigned GetTriangulationNum() const = 0;

	/// Like @ref mwMachSimVerifier::SaveStock() but avoids to undo zooming or
	/// other internal states.
	virtual void SaveStockForTest(const misc::mwstring& filename) const = 0;

	/// With the experimental draw mode WDM_LAST_CUT, only export the triangles from last cut.
	virtual void SetTriangulateOnlyLastCut(const bool enabled) = 0;
	/// @sa SetTriangulateOnlyLastCut()
	virtual bool GetTriangulateOnlyLastCut() = 0;
	/// With the experimental draw mode WDM_LAST_CUT, compute the center of the last cut triangles.
	virtual cadcam::mwPoint3df GetCenterOfLastCut() = 0;

	/// Returns the number of buffered cuts that were not simulated yet.
	virtual size_t GetBufferedCutCount() const = 0;

	struct BenchmarkEntry
	{
		std::string name;
		double totalTime;
		double maxTime;
		size_t callCount;
	};
	/// Returns internal benchmarks
	virtual std::vector<BenchmarkEntry> GetBenchmarks() const = 0;
	/// Reset internal benchmarks.
	///
	/// Will have an effect on all currently living verifier instances. This call is recorded in
	/// csbs and can be used to created testfiles to profile specific API calls.
	virtual void ResetBenchmarks() = 0;

	virtual float GetTriangulationTolerance() const = 0;

	virtual void OverrideDebugIniSetting(
		const misc::mwstring& name, const misc::mwstring& value) = 0;

	virtual void LoadStockWithSimulationList(
		const misc::mwstring& pathName, const StaticSimulationData* externalData = MW_NULL) = 0;

	virtual cadcam::mw3dfBoundingBox GetSubvolumeBox(const cadcam::mwPoint3di& idx) const = 0;

	/// @returns the internally used zero tolerance for the incoming tool path.
	///
	/// Tool paths shorter than this tolerance are likely to be changed, maybe even being snapped to
	/// a zero length move. For example for engagement calculations it may be important to either
	/// avoid shorter moves, or ignore the engagement results of e.g. @ref
	/// mwMachSimVerifier::GetEngagementAngles().
	///
	/// The tolerance depends on the stock size, so this getter will throw an exception, if no stock
	/// was set yet.
	virtual float GetToolPathTolerance() const = 0;
};
//---------------------------------------------------------------------------------------
struct MW_VERIFIER_API RenderOptions
{
public:
	/// @sa RequestAttributes()
	enum AttributeFlags
	{
		NONE = 0,
		DEVIATION = 1 << 0,
		OPERATION_ID = 1 << 1,
		COLLISION = 1 << 2,
		CHUNK_ID = 1 << 3,
		TOOL_ID = 1 << 4,
		MOVE_ID = 1 << 5,
		ALL = (1 << 6) - 1
	};
	RenderOptions()
		: m_visualizeAttribute(NONE),
		  m_showEdges(true),
		  m_showColorEdges(true),
		  m_watertight(true),
		  m_requestedAttributes(0),
		  m_measureID(0){};

	bool operator==(const RenderOptions& rhs) const;
	bool operator!=(const RenderOptions& rhs) const;

	/// Enable edges (sharpened features)
	void SetShowEdges(bool showEdges) { m_showEdges = showEdges; };
	/// @sa SetShowEdges
	const bool GetShowEdges() const { return m_showEdges; };

	/// @note Requires SetShowEdges() to be set to `true`.
	///
	/// Disabling color edges allows triangles to have inconsistent colors and attributes across the
	/// triangle area, and thus results in fewer triangles.
	void SetShowColorEdges(bool showColorEdges) { m_showColorEdges = showColorEdges; };
	/// @sa SetShowColorEdges
	const bool GetShowColorEdges() const { return m_showColorEdges; };

	/// When set to `false`, disables watertight triangulation. Use with caution if absolutely
	/// necessary for performance reasons. Disabling watertightness can cause artifacts such as
	/// gaps and sparkles.
	///
	/// @image html "../dox/watertightness.png" width=100%
	///
	/// top: non-watertight, bottom: watertight
	void SetWatertight(bool watertight) { m_watertight = watertight; };
	/// @sa SetWatertight
	const bool GetWatertight() const { return m_watertight; };

	/// Specify requested vertex attributes. Multiple attributes can be requested at once by
	/// connecting their @ref AttributeFlags with OR.
	///
	/// To get better performance request as few attributes as possible. This allows us to skip
	/// computing them, and, more importantly, results in fewer triangles.
	///
	/// Output triangles will be split if the color or selected attribute vary across their area.
	/// This is the reason why the "deviation" attribute especially results in an high number of
	/// triangles. If you don't want that behavior you can disable "color edges" using
	/// SetShowColorEdges().
	void RequestAttributes(int attributes, bool request)
	{
		assert(attributes <= ALL);
		m_requestedAttributes = (m_requestedAttributes & (~attributes)) | (attributes * request);
	};
	bool IsAttributeRequested(int attributes) const
	{
		assert(attributes <= ALL);
		return (m_requestedAttributes & attributes) == attributes;
	};
	int GetRequestedAttributes() const { return m_requestedAttributes; }

	void ResetMeasureID() { m_measureID = 0; }
	/// Set ID of measured object for internal verifier drawing.
	/// If an ID is set, verifier writes automatically data into the stencil-buffer (required for
	/// Smart-Measure feature). The value is recommended to be set only when Measure-feature needs
	/// to be updated and calls @ref VerifierUtil::Measure::WindowCallbacks::RenderToStencil().
	void SetMeasureID(Measure::MeasuredObjectID id) { m_measureID = id; }
	Measure::MeasuredObjectID GetMeasureID() const { return m_measureID; }

	AttributeFlags m_visualizeAttribute;

private:
	bool m_showEdges;

	bool m_showColorEdges;

	bool m_watertight;

	int m_requestedAttributes;

	Measure::MeasuredObjectID m_measureID;
};

/// Options provided to mwMachSimVerifier::ExportStockMesh().
struct ExportStockMeshOptions
{
	ExportStockMeshOptions() : m_decimationTolerance(0), m_exportColor(false) {}

	/// Tolerances greater than zero enable an additional decimation step. The tolerance describes
	/// the maximum allowed (absolute) distance between decimated and non-decimated mesh.
	///
	/// Decimation leads to fewer triangles, but it also requires some additional processing time.
	///
	/// Please note that we currently can't provide vertex normals when decimation is enabled.
	/// Decimation is not applied when the stock spindle is enabled. Both may change in the future.
	ExportStockMeshOptions& SetDecimationTolerance(const float tolerance)
	{
		m_decimationTolerance = tolerance;
		return *this;
	}
	/// @sa SetDecimationTolerance()
	float GetDecimationTolerance() const { return m_decimationTolerance; }

	/// Enable color export
	///
	/// Color is provided as an additional attribute in the output mesh (mwvStockMesh), or as a
	/// triangle attribute in the STL file.
	///
	/// For STL files the color is provided in the "Materialise Magic" format, which stores it in
	/// the 16 bits allocated to triangle attributes, with 5 bits per color: "(b << 10) | (g << 5) |
	/// r"
	///
	/// Please note that vertex color is not available when using the legacy data model
	/// (MWV_FM_FIELD).
	ExportStockMeshOptions& SetShouldExportColor(const bool color)
	{
		m_exportColor = color;
		return *this;
	}
	/// @sa SetShouldExportColor()
	bool ShouldExportColor() const { return m_exportColor; }

private:
	float m_decimationTolerance;
	bool m_exportColor;
};

struct EngagementOptions
{
	/// See SetAlgorithm()
	enum Algorithm
	{
		QuadBased = 0,
		ContourBased = 1
	};

	EngagementOptions() : m_boxesHeight(0), m_algorithm(QuadBased){};

	/// Maximum size of the profile segments in the GetEngagementBoxes() API
	void SetBoxesHeight(const float boxesHeight) { m_boxesHeight = boxesHeight; }
	float GetBoxesHeight() const { return m_boxesHeight; }

	/// Chose the internal algorithm.
	/// QuadBased:
	/// - rough accuracy about the size of stock precision
	/// - fast but not parallelized
	///
	/// ContourBased:
	/// - usually much better accuracy than nail precision
	/// - less jittering/flickering
	/// - supports GetEngagementBoxes()
	/// - may be slower than QuadBased
	/// - does not support mwMachSimVerifier::SetNoCutHistory(true) yet.
	void SetAlgorithm(const Algorithm algo) { m_algorithm = algo; }
	Algorithm GetAlgorithm() const { return m_algorithm; }

	bool operator==(const EngagementOptions& options) const
	{
		return m_boxesHeight == options.m_boxesHeight && m_algorithm == options.m_algorithm;
	}
	bool operator!=(const EngagementOptions& options) const { return !(*this == options); }


private:
	float m_boxesHeight;
	Algorithm m_algorithm;
};

/// Additional information assigned to each move/cut in the API.
class MoveParameters
{
public:
	/// The id of the move set by mwMachSimVerifier::SetMoveId().
	float GetMoveId() { return m_moveId; }
	/// The id of the tool set by mwMachSimVerifier::SetTool() and similar methods.
	int GetToolId() { return m_toolId; };
	/// The operation id set by mwMachSimVerifier::SetOperationId().
	int GetOperationId() { return m_operationId; }
	/// The custom text description set by mwMachSimVerifier::SetMoveDescription().
	const misc::mwstring& GetMoveDescription() { return m_description; }

	MoveParameters(
		float moveId = -1,
		int toolId = -1,
		int operationId = -1,
		const misc::mwstring& moveDescription = misc::mwstring())
		: m_moveId(moveId),
		  m_toolId(toolId),
		  m_operationId(operationId),
		  m_description(moveDescription)
	{
	}

private:
	float m_moveId;
	int m_toolId;
	int m_operationId;
	misc::mwstring m_description;
};

/// Information about a gouge or excess.
///
/// For each local minimum or maximum in the deviation field we create one of these structures.
struct GougeReport
{
	/// Distance from the target. This is negative for gouges, and positive for excess material.
	float gougeSize;

	/// Position in world coordinates
	::cadcam::mwTPoint3d<float> position;

	/// The move ID, as set via @ref mwMachSimVerifier::SetMoveID(), rounded to an integer. "-1" if
	/// the material was not cut at this position.
	///
	/// If the [cut&nbsp;history](@ref mwMachSimVerifier::SetNoCutHistory) was disabled, then this
	/// value is the _index_ of the move instead.
	unsigned int blockNumber;

	/// The move description, as set via @ref mwMachSimVerifier::SetMoveDescription().
	misc::mwstring blockDesc;

	/// The tool ID, as set via @ref mwMachSimVerifier::SetTool().
	int toolNumber;

	/// The target index, i.e. the position in the vector passed to @ref
	/// mwMachSimVerifier::SetTargets().
	int targetID;

	/// The move ID, as set via @ref mwMachSimVerifier::SetMoveID(). Undefined if the material was
	/// not cut at this position, or if the move history was disabled.
	float moveId;

	bool operator<(const GougeReport& rhs) const { return gougeSize < rhs.gougeSize; }
};

/// Holds transformation objects for all three coordinate axes.
/// Those objects describe the grid of internal sampling points for a 5axis stock model.
struct CuttingResult_TransformationInfo
{
	mwFieldCoordinateScaling ScalingX;
	mwFieldCoordinateScaling ScalingY;
	mwFieldCoordinateScaling ScalingZ;
};
//---------------------------------------------------------------------------------------
typedef std::vector<int> ChunkIdVector;
//---------------------------------------------------------------------------------------
/// Lists of chunk-ids for each tool-element. If a chunk's id is e.g. in FluteCollisions, the flute
/// collided with this chunk. See GetCollidingChunks().
struct ToolChunkCollisions
{
	ChunkIdVector FluteCollisions;
	ChunkIdVector ShaftCollisions;
	ChunkIdVector ArborCollisions;
	ChunkIdVector HolderCollisions;
};
//---------------------------------------------------------------------------------------
typedef std::pair<float, float> EngagementAngle;
typedef std::vector<EngagementAngle> EngagementAngleList;
typedef std::vector<EngagementAngleList> EngagementAngleListList;

/// Transformations that help to switch between engagement coordinate systems.
///
/// - Can be used to transform the engagement angles and boxes into 3d world space. See
/// mwMachSimVerifier::GetEngagementAngles(), mwMachSimVerifier::GetEngagementBoxes().
/// - The engagement-system is the tool-system at the end position of the move, additionally
/// rotated around the tool-axis in order to get X-axis looking into the feed-direction.
/// - Only works with new tracking, see mwMachSimVerifier::EnableEngagementTracking(). *
class EngagementTransformations
{
public:
	/// Only rotate from feed direction system into tool system (tool at move end position).
	///
	/// The transformation might be the identity, if it is for a move that did not hit
	/// the stock.
	Frame::Quaternion GetEngagementToToolTransform() const { return m_engagementToToolTransform; }
	/// Transfrom from feed direction system into world system.
	///
	/// The transformation might be the identity, if it is for a move that did not hit
	/// the stock.
	Frame GetEngagementToWorldTransform() const { return m_engagementToWorldTransform; }

	EngagementTransformations(
		const Frame::Quaternion& engagementToTool = Frame::Quaternion(),
		const Frame& engagementToWorld = Frame())
		: m_engagementToToolTransform(engagementToTool),
		  m_engagementToWorldTransform(engagementToWorld)
	{
	}

private:
	Frame::Quaternion m_engagementToToolTransform;
	Frame m_engagementToWorldTransform;
};

//---------------------------------------------------------------------------------------
/// Structure which contains a the texts masks for the labels allowing them do customize or
/// localize. Used in SetLabelTextMask()
struct MW_VERIFIER_API mwLabelTextMask
{
	/// a descriptive text for the gouge labels shown at first line of a label
	misc::mwstring m_GougeDescription;
	/// a descriptive text for the material excess labels shown at first line of a label
	misc::mwstring m_ExcessDescription;
	/// a descriptive text for the point description labels shown at first line of a label
	misc::mwstring m_PointDescription;
	/// a descriptive text for the position line in a label. Three float arguments in boost::format
	/// need to be placed in the label, like "Position%|15t|(%0.2f/%0.2f/%0.2f)"
	misc::mwstring m_Position;
	/// a descriptive text line for the deviation to the target in a label, when no offset is active
	/// i.e. =0 . One float argument in boost::format needs to be placed in the label, like
	/// "Deviation %|15t|(%0.4f)"
	misc::mwstring m_Deviation;
	/// a descriptive text line for the deviation absolute to the target in a label. One float
	/// argument in boost::format needs to be placed in the label, like "Deviation
	/// abs.%|15t|(%0.4f)"
	misc::mwstring m_AbsoluteDeviation;
	/// a descriptive text line for the deviation relative to the target offset in a label. One
	/// float argument in boost::format needs to be placed in the label, like "Deviation
	/// rel.%|15t|(%0.4f)"
	misc::mwstring m_RelativeDeviation;
	/// a descriptive text line for target id. One float argument in boost::format needs to be
	/// placed in the label, like "Target ID  (%0.4f)"
	misc::mwstring m_TargetID;
	/// a descriptive text line for the number of the part chunk the labeled surface point belongs
	/// to. One float argument in boost::format needs to be placed in the label, like "Part
	/// number%|15t|(%d)"
	misc::mwstring m_ChunkNumber;
	///  a descriptive text line for the number of move block which formed the surface point. One
	///  float argument in boost::format needs to be placed in the label, like "Move
	///  number%|15t|(%d)"
	misc::mwstring m_BlockNumber;
	/// a descriptive text line for the number of the active tool which formed the surface point.
	/// One float argument in boost::format needs to be placed in the label, like "Tool
	/// number%|15t|(%d)"
	misc::mwstring m_ToolNumber;
	/// a descriptive text line for the number of operation where the move block which formed the
	/// surface point belonged. One float argument in boost::format needs to be placed in the label,
	/// like "Operation number%|15t|(%d)"
	misc::mwstring m_OperationNumber;
	/// a descriptive text line if the surface point was in collision with a part of the tool.
	misc::mwstring m_CollisionWarning;
	/// a descriptive text line for distace label. One float argument in boost::format needs to be
	/// placed in the label, like "Distance  (%0.4f)"
	misc::mwstring m_Distance;

	mwLabelTextMask();
};

struct RefineBox
{
	/// box of the refinement area
	cadcam::mw3dBoundingBox<float> box;
	/// factor of the refinement
	///
	/// - have to be power of 2
	///	- 0 for the feature detection
	///	- non-positive value for the limited feature detection, for example -4 means that the
	///   refinement factor will be not bigger than 4
	int factor;
	/// refinement step
	///
	/// - each step ends with stock redraw
	int step;

	RefineBox(const cadcam::mw3dBoundingBox<float>& box, int factor = 0, int step = 0)
		: box(box), factor(factor), step(step){};
};

typedef std::vector<RefineBox> RefineLayout;

class RedrawNotifier
{
public:
	virtual ~RedrawNotifier() {}

	/// Callback; signals that a draw on integration side is needed.
	///
	/// Important: This method is called from an internal thread, it is not safe to draw inside of
	/// this callback. Instead, you should notify your main- or drawing-thread to perform the
	/// redraw.
	///
	/// As an example, on Windows the invalidation could look like:
	/// ```
	/// ::RedrawWindow(window, 0, 0, RDW_INVALIDATE);
	/// ```
	virtual void OnRedrawNeeded() = 0;
};

class RefineNotifier : public RedrawNotifier
{
public:
	/// Called when a refinement process starts.
	///
	/// Important: This method can be called from another thread, an implementation have to be
	/// thread-safe!
	virtual void OnRefineStarted(const bool manual) = 0;

	/// Called when a refinement process completed.
	///
	/// Important: This method can be called from another thread, an implementation have to be
	/// thread-safe!
	virtual void OnRefineCompleted() = 0;

	/// Called when a refinement process was aborted.
	///
	/// Important: This method can be called from another thread, an implementation have to be
	/// thread-safe!
	virtual void OnRefineAborted(misc::mwException::Ptr /*exception*/) /*= 0*/
	{
		OnRefineAborted();
	}
	// MW_DEPRECATED("Use OnRefineAborted(misc::mwException::Ptr)")
	virtual void OnRefineAborted() /*= 0*/ {}

	/// Called when new progress is available (from 0...1 meaning 0%...100%)
	///
	/// Important: This method can be called from another thread, an implementation has to be
	/// thread-safe!
	///
	/// Sample:
	/// ```
	/// if ((frontSide >= 1) && (backSide < 1))
	/// {
	///	text = "Refining backside (%i)" % (int)(backSide * 100);
	/// }
	/// else if ((frontSide < 1) && (backSide < 1))
	/// {
	///	// appears only in multipass refinement under low memory condition
	///	text = "Refining entire stock (%i)" % (int)(common * 100);
	/// }
	/// else
	/// {
	///	// front side, or when refinement is completed
	///	text = "Refining (%i)" % (int)(frontSide * 100);
	/// }
	/// ```
	virtual void OnProgressUpdate(
		const float common, const float frontSide, const float /*backSide*/) /*= 0*/
	{
		OnProgressUpdate(common, frontSide);
	}

	// deprecated
	virtual void OnProgressUpdate(const float /*progress*/) /*= 0*/ {}

	// deprecated
	virtual void OnProgressUpdate(const float common, const float /*frontSide*/) /*= 0*/
	{
		OnProgressUpdate(common);
	}
};

//---------------------------------------------------------------------------------------
/// Contains data of a target definition
struct TargetData
{
	typedef misc::mwAutoPointer<cadcam::mwTMesh<float>> MeshPtr;
	TargetData() {}
	TargetData(
		MeshPtr pMesh,
		float fGougeThreshold,
		float fExcessThreshold,
		float cRed = 1,
		float cGreen = 0.5f,
		float cBlue = 0.5f,
		float cAlpha = 1)
		: m_pMesh(pMesh),
		  m_fGougeThreshold(fGougeThreshold),
		  m_fExcessThreshold(fExcessThreshold),
		  m_cRed(cRed),
		  m_cGreen(cGreen),
		  m_cBlue(cBlue),
		  m_cAlpha(cAlpha){};

	/// pointer to the polygonal geometry object
	MeshPtr m_pMesh;
	/// value of the gouge threshold specific for this target
	float m_fGougeThreshold;
	/// value of the excess threshold specific for this target
	float m_fExcessThreshold;
	/// red light of the target color. value between 0.0 and 1.0
	float m_cRed;
	/// green light of the target color. value between 0.0 and 1.0
	float m_cGreen;
	/// blue light of the target color. value between 0.0 and 1.0
	float m_cBlue;
	/// transparency of the target color. value between 0.0(transparent) and 1.0(opaque)
	float m_cAlpha;
};

/// Used in VerificationResult
struct CollisionInfo
{
	enum ToolElementType
	{
		CUTTING,
		NON_CUTTING,
		ARBOR,
		HOLDER
	};
	enum CollisionType
	{
		COLLISION,
		SAFETY_CHECK
	};

	CollisionInfo(
		ToolElementType toolElementType,
		CollisionType collisionType,
		cadcam::mwTPoint3d<float> pointInWorld)
		: toolElementType(toolElementType), collisionType(collisionType), pointInWorld(pointInWorld)
	{
	}

	ToolElementType toolElementType;

	CollisionType collisionType;

	cadcam::mwTPoint3d<float> pointInWorld;
};

struct VerificationResult
{
	/// The tool's index in the vector passed to SetTools().
	///
	/// If SetTool() is used this index will always be zero.
	size_t RelativeToolIdx;

	/// Identifies collisions.
	///
	/// `Code` is a bitwise OR of symbols in mwMachSimVerifier::VerificationCodes.
	unsigned int Code;

	/// Custom move id as set via SetMoveId(float)
	float MoveID;

	/// The tool's id as set via @ref mwMachSimVerifier::SetTool() or mwMachSimVerifier::SetTools()
	int ToolId;

	/// True, if the cut removed material.
	///
	/// Note that this value might be false, even though some material should have been
	/// removed. In that case "UnreliableMaterialChangeFlag" will be true. This is due to
	/// internal optimizations.
	///
	/// If you prefer this flag to be correct at the cost of performance you can call
	/// `mwvMachSimVerifier::ForceCorrectMaterialRemovalFlag(true)`.
	bool DidRemoveMaterial;

	/// True, if material has been added (additive manufacturing mode)
	bool DidAddMaterial;

	/// True, if material has been painted
	bool DidPaintMaterial;

	/// This vector contains more information about collisions that occurred.
	///
	/// It is only filled if collisions occurred, and if collision points were requested via @ref
	/// mwMachSimVerifier::SetCollisionPointOptions().
	///
	/// @note Current Limitations (this behavior may change in the future):
	/// - Currently we can't always generate a correct collision point in cases where the
	///   stock spindle is enabled, since the internal calculation happens in 2d. The real collision
	///   point may have a different rotation around the axis, compared to the returned one. The
	///   returned point will still have the correct height and radius on the axis though. If this
	///   is important for you please contact us.
	///
	/// - The resulting collision points are not guaranteed to be stable, if multi-threaded
	///   simulation is enabled (see @ref mwMachSimVerifier::LimitThreadCount()). Since the number of potential
	///   collision points can be greater than one, and the processing order is currently not
	///   deterministic, you may receive any of the potential candidates.
	std::vector<CollisionInfo> CollisionInfoVec;

	/// True, if the results are unreliable
	///
	/// Move delaying can cause verification results to be assigned to later moves. This means
	/// the following values are unreliable:
	/// - DidRemoveMaterial
	/// - DidAddMaterial
	/// - Code
	///
	/// A move can be delayed if a tool element is collision checked _and_ cutting. This is to
	/// prevent it from cutting away material that a later move should collide with. Due to this
	/// technique the collision may be assigned to a later move, but it will not be missed
	/// completely.
	///
	/// A move can also be delayed for speed reasons. To get accurate reports (for the cost of a
	/// slower simulation), you can call mwvMachSimVerifier::ForceCorrectMaterialRemovalFlag(true).
	///
	bool UnreliableMaterialChangeFlag;

	/// @copydoc UnreliableMaterialChangeFlag
	bool UnreliableCollisionReport;

	/// Constructor with default values that describe a non-simulated cut.
	/// See struct members for an explanation of the parameters.
	inline VerificationResult(
		const bool didRemoveMaterial = false,
		const int code = VC_NO_ERROR,
		const float moveID = -1,
		const int toolId = MW_MIN_INT,
		const size_t relativeToolIdx = 0,
		const bool didAddMaterial = false,
		const bool didPaintMaterial = false)
		: RelativeToolIdx(relativeToolIdx),
		  Code(code),
		  MoveID(moveID),
		  ToolId(toolId),
		  DidRemoveMaterial(didRemoveMaterial),
		  DidAddMaterial(didAddMaterial),
		  DidPaintMaterial(didPaintMaterial),
		  UnreliableMaterialChangeFlag(false),
		  UnreliableCollisionReport(false)
	{
	}

	static const int MW_MIN_INT = (-2147483647 - 1);
};
typedef std::vector<VerificationResult> VerificationResultVector;
typedef mwSetToolParameters SetToolParameters;
typedef std::vector<SetToolParameters> SetToolsParameters;
typedef mwSetCustomToolParameters SetCustomToolParameters;
typedef std::vector<SetCustomToolParameters> SetCustomToolsParameters;

/// This should not be used in any integration, it is used by ModuleWorks internally only.
struct DebugCompareStockSettings
{
	float NailHeightRelativeTolerance;
	float NormalAngleTolerance;
	bool IgnoreMoveNumbers;
	bool IgnoreMoveCollisionStatus;
	bool IgnoreAdditionalValue;
	bool PrintToConsole;

	inline DebugCompareStockSettings(
		const float nailHeightRelativeTolerance,
		const float normalAngleTolerance,
		const bool ignoreMoveNumbers,
		const bool ignoreMoveCollisionStatus,
		const bool ignoreAdditionalValue,
		const bool printToConsole)
		: NailHeightRelativeTolerance(nailHeightRelativeTolerance),
		  NormalAngleTolerance(normalAngleTolerance),
		  IgnoreMoveNumbers(ignoreMoveNumbers),
		  IgnoreMoveCollisionStatus(ignoreMoveCollisionStatus),
		  IgnoreAdditionalValue(ignoreAdditionalValue),
		  PrintToConsole(printToConsole)
	{
	}
};
/// This should not be used in any integration, it is used by ModuleWorks internally only.
class DebugCompareStockResult
{
public:
	enum ResultCode
	{
		IS_EQUAL,
		IS_IN_TOLERANCE,
		IS_DIFFERENT
	};
	inline DebugCompareStockResult(
		const ResultCode code, const misc::mwstring& differentExplanation = misc::mwstring())
		: m_code(code), m_differentExplanation(differentExplanation)
	{
	}
	inline ResultCode GetCode() const { return m_code; }
	inline misc::mwstring GetDifferentExplanation() const { return m_differentExplanation; }

private:
	ResultCode m_code;
	misc::mwstring m_differentExplanation;
};
//---------------------------------------------------------------------------------------
/// Structure for holding an RGBA color value as a `float` between `0.0f` and `1.0f` for each
/// channel.
///
/// To work with colors as 8-bit integers for each channel, see VerifierUtil::mwvColor.
struct Color
{
	float r;
	float g;
	float b;
	float a;

	/// Sets the color to opaque black, i.e., the RGBA value `(0.0f, 0.0f, 0.0f, 1.0f)`.
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
	Color(float ar, float ag, float ab, float aa = 1.0f) : r(ar), g(ag), b(ab), a(aa) {}
	bool operator==(const Color& other) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool operator!=(const Color& other) const { return !(*this == other); }
};
//---------------------------------------------------------------------------------------
/// Structure which contains the data to define the appearance of a label.
struct mwLabelAppearance
{
	/// True if a shadow shall be drawn with the label
	bool m_bUseShadow;
	/// TRue if the label shall be drawn transparent
	bool m_bUseTransparency;
	/// defines the distance between label and the point which is labeled.
	float m_PinLength;
	/// defines the size of the pin point
	float m_fPinPointSize;
	/// defines the width of the shadow id active through m_bUseShadow.
	float m_fShadowWidth;
	/// defines the corner and border width between text and label edge.
	float m_fCornerSize;

	/// LabelAppearance
	///
	/// default constructor sets to a transparent label with shadow a pin
	///	length of 30 a Point size of 6 and a shadow width and corner size of 8.
	mwLabelAppearance()
		: m_bUseShadow(true),
		  m_bUseTransparency(true),
		  m_PinLength(30),
		  m_fPinPointSize(6),
		  m_fShadowWidth(8),
		  m_fCornerSize(8){};

	mwLabelAppearance(
		bool bUseShadow,
		bool bUseTransparency,
		float fPinLength,
		float fPinPointSize,
		float fShadowWidth,
		float fCornerSize)
		: m_bUseShadow(bUseShadow),
		  m_bUseTransparency(bUseTransparency),
		  m_PinLength(fPinLength),
		  m_fPinPointSize(fPinPointSize),
		  m_fShadowWidth(fShadowWidth),
		  m_fCornerSize(fCornerSize){};
};
//---------------------------------------------------------------------------------------
struct MeshCollisionReport
{
	typedef ::cadcam::mwTPoint3d<float> float3d;
	inline MeshCollisionReport()
		: m_meshId(-1), m_violatedSafetyDistance(-1), m_safetyDistanceidx(-1), m_chunkId(-1)
	{
	}
	inline MeshCollisionReport(
		const int id,
		const float safetyDist,
		const int safteyDistIdx,
		const float3d& collPoint,
		const int chunkId = -1)
		: m_meshId(id),
		  m_violatedSafetyDistance(safetyDist),
		  m_safetyDistanceidx(safteyDistIdx),
		  m_collisionPoint(collPoint),
		  m_chunkId(chunkId)
	{
	}
	/// The id of the colliding mesh, see return value of mwMachSimVerifier::AddCollisionMesh()
	inline int GetMeshId() const { return m_meshId; }

	/// The safety distance for which the collision occurred, see
	/// mwMachSimVerifier::AddCollisionMesh()
	inline float GetViolatedSafetyDistance() const { return m_violatedSafetyDistance; }

	/// The index of the distance for which the collision occurred
	///
	/// The index is referring to the vector of safety distances in
	/// mwMachSimVerifier::AddCollisionMesh().
	inline int GetSafetyDistanceIdx() const { return m_safetyDistanceidx; }

	/// Returns one collision point on the stock.
	///
	/// If a safety distance of 0 was used, the point is also on the mesh.
	/// For safety distances > 0, it can be outside of the mesh.
	inline float3d GetCollisionPoint() const { return m_collisionPoint; }

	/// Returns the chunk id of one colliding stock part.
	///
	/// - The chunk id is only available if mwMachSimVerifier::GetCollidingChunks(true) was called.
	/// - You get one report per mesh-chunk combination if chunk id reporting is enabled.
	/// - Computing the colliding chunks will decrease performance.
	inline int GetChunkId() const { return m_chunkId; }

#ifndef MW_GENERATE_DOCUMENTATION
	/// @deprecated Direct access to members is deprecated, please use Getters!
	int m_meshId;
	float m_violatedSafetyDistance;
	int m_safetyDistanceidx;
	float3d m_collisionPoint;
#endif
private:
	int m_chunkId;
};

struct ChunkMovability
{
	ChunkMovability() : distance(mathdef::MW_FLOAT_NAN), obstructedByChunk(-1) {}
	ChunkMovability(int obstructedByChunk, float distance)
		: distance(distance), obstructedByChunk(obstructedByChunk)
	{
	}
	bool operator==(const ChunkMovability& other) const
	{
		return other.obstructedByChunk == obstructedByChunk && other.distance == distance;
	}

	float distance;  // the distance the chunk can travel
	int obstructedByChunk;  // the opposing chunk that is hit after distance
};
struct ChunkMovabilityAlongMainAxisDirections
{
	ChunkMovabilityAlongMainAxisDirections(const int chunkId = -1) : chunkId(chunkId)
	{
		for (int direction = 0; direction < 6; ++direction)
			inDirection[direction] = ChunkMovability();
	}
	int chunkId;
	ChunkMovability inDirection[6];  // +x, +y, +z, -x, -y, -z
	const ChunkMovability& GetChunkMovabilityInDirection(const cadcam::mwPoint3df& direction)
	{
		int chosenAxis = 0;
		for (int axis = 0; axis < 3; ++axis)
		{
			if (direction[axis] != 0.0f)
			{
				chosenAxis = axis;
				if (direction[axis] < 0)
					chosenAxis += 3;
				break;
			}
		}
		return inDirection[chosenAxis];
	}
};

typedef cadcam::mw3dPolyLine<float> PolyLine3df;
typedef std::vector<PolyLine3df> PolyLine3dVector;
typedef misc::mwAutoPointer<PolyLine3dVector> PolyLine3dVectorPtr;

struct mwPolyLine3dTreeNode;
/// A tree of polylines, used in @ref mwMachSimVerifier::GetIntersectionPlanesStock(): All polylines
/// are on a single plane, they are non-intersecting and closed. With the sorting relation 'x lies
/// inside y', x would be a child of y.
///
/// The information whether a given node contains an outer boundary (the
/// stock is inside the contour) or an inner boundary (island, the stock is outside of the contour)
/// is implicitly given by the tree depth. The topmost contours usually are outer boundaries. If the
/// contours are oriented (counterclockwise for outer, clockwise for inner boundaries), all tests
/// whether a given point is inside the stock do not need tree depth information. For @ref
/// mwMachSimVerifier::GetIntersectionPlanesStock(), this is the case.
typedef std::vector<mwPolyLine3dTreeNode> mwPolyLine3dTree;

/// A node for a @ref mwPolyLine3dTree holds a polyline and all children of this polyline. Usually,
/// the polylines are sorted by a relation (e.g. 'x lies inside y'), such that all children are
/// 'below' the actual polyline.
struct mwPolyLine3dTreeNode
{
	mwPolyLine3dTreeNode(const PolyLine3df& iPolyLine) : polyLine(iPolyLine){};

	PolyLine3df polyLine;
	/// the tree of polylines that are sorted below the current polyline (could be empty).
	mwPolyLine3dTree childPolyLines;
};

/// a vector of polyline trees, for the intersection of several planes with the stock as in  @ref
/// mwMachSimVerifier::GetIntersectionPlanesStock().
typedef std::vector<mwPolyLine3dTree> mwPolyLine3dTreeVector;
/// @sa mwPolyLine3dTreeVector
typedef misc::mwAutoPointer<mwPolyLine3dTreeVector> mwPolyLine3dTreeVectorPtr;

class MW_VERIFIER_API StaticSimulationData
{
	typedef cadcam::mwTMesh<float> Mesh;
	typedef misc::mwAutoPointer<Mesh> MeshPtr;

public:
	StaticSimulationData();

	/// get mesh used as initial stock volume
	const MeshPtr& GetInitialMesh(std::size_t idx) const;
	std::size_t GetInitialMeshCount() const;

	/// get mesh used as target volume
	const MeshPtr& GetTargetMesh(std::size_t idx) const;
	std::size_t GetTargetMeshCount() const;

	void SetInitialMeshes(const std::vector<MeshPtr>& meshes);  // for internal use
	void SetTargetMeshes(const std::vector<MeshPtr>& meshes);  // for internal use

private:
	typedef std::vector<MeshPtr> InitialMeshes;
	typedef std::vector<MeshPtr> TargetMeshes;
	InitialMeshes m_initialMeshes;
	TargetMeshes m_targetMeshes;
};

/// Used as callback in mwMachSimVerifier::SetNotificationHandler()
class NotificationHandler
{
public:
	virtual ~NotificationHandler() {}

	/// Called by a warning.
	///
	/// Important: This method can be called from another thread, an implementation has to be
	/// thread-safe! @param [in] code resource id of the message string or 0 for custom messages
	/// @param [in] text english message for the specified code
	virtual void OnWarning(const NotificationCode code, const misc::mwstring& text) = 0;
};

/// Used in mwMachSimVerifier::SetCollisionPointOptions().
struct CollisionPointOptions
{
	CollisionPointOptions() : enabled(false) {}

	/// Enable collision point tracking. This fills the CollisionInfo in
	/// mwMachSimVerifier::VerificationResult.
	CollisionPointOptions& SetEnabled(const bool b)
	{
		enabled = b;
		return *this;
	}
	bool IsEnabled() const { return enabled; }

private:
	bool enabled;
};

/// Used in @ref mwMachSimVerifier::TraceEdge().
struct MW_VERIFIER_API TracedEdge
{
	cadcam::mw2dfContourPtr contour;
	cadcam::mwHomogenousMatrix transform;

	cadcam::mw3dfPolyLinePtr trace;  ///< optional

	TracedEdge() {}

	explicit TracedEdge(
		const cadcam::mw2dfContourPtr& contour,
		const cadcam::mwHomogenousMatrix& transform,
		const cadcam::mw3dfPolyLinePtr& trace = NULL);
};

};  // namespace VerifierUtil
#endif  //	MW_MWVERIFIERNESTEDCLASSES_HPP_
