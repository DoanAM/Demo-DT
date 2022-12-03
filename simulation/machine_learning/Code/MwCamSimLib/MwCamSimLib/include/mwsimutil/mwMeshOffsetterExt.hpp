// (C) 2013-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMESHOFFSETTEREXT_HPP_
#define MW_MWMESHOFFSETTEREXT_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMeshOffsetterExtInf.hpp"
#include "mwMeshOffsetterSerializationOptions.hpp"

#include <vector>

class mwMachSimVerifierProgressHandler;

namespace cadcam
{
template <class T>
struct mwTPoint3d;
template <typename T>
class MW_5AXUTIL_API mwTMesh;
};  // namespace cadcam

namespace misc
{
class mwstring;
template <class T>
class mwAutoPointer;
};  // namespace misc

namespace Verifier
{
struct mwMeshoffsetterInputParams;

class mwMeshOffsetterInternalExt;

/// Allows offsetting a mesh
/** This class has to be provided with a mesh which is to be offset ("target mesh").
	Based on this, many functions allow the parametrization of the offset process.

	The most important calls are SetTargetMesh, SetOffset, SetPrecision and OffsetMesh. */
template <class T>
class MW_5AXUTIL_API mwMeshOffsetterExt: public mwMeshOffsetterExtInf<T>
{
public:
	typedef misc::mwAutoPointer<mwMeshOffsetterExt<T>> Ptr;
	typedef typename cadcam::mwTMesh<T> Mesh;
	typedef typename misc::mwAutoPointer<Mesh> MeshPtr;
	typedef typename cadcam::mwTPoint3d<T> TPoint;

	mwMeshOffsetterExt();
	~mwMeshOffsetterExt();

	//! Set the target mesh for offsetting.
	void MWMSV_API SetTargetMesh(const MeshPtr& inputMesh);
	//! Set the offset value.
	void MWMSV_API SetOffset(T offset);
	//! Set the precision.
	void MWMSV_API SetPrecision(T precision);

	/// Whether to enable curtains
	/** With curtains enabled, a base surface is created at the lowest Z coordinate found in the
	   mesh. Triangles are created that connect overhanging parts to this base surface. */
	void SetDoCurtains(bool generateCurtains);

	//! Set bounding boxes that define areas of interest
	/** Any refinement is restricted to the volume enclosed by these bounding boxes, but only if
		ConsiderBBoxes is enabled.
		\see SetConsiderBBoxes */
	void SetBBoxes(const std::vector<std::pair<TPoint, TPoint>>& bboxes);

	/// Restrict refinement to the bounding boxes defined in SetBBoxes.
	/** \see SetBBoxes */
	void SetConsiderBBoxes(bool considerBBox);

	/// Eliminate curtains that nearly coalign with the mesh
	/** \see SetDoCurtains */
	void SetEliminateNearCurtains(bool doEliminate);

	///  Standard is to output only 2 offset meshes and not more. To deactivate this, use false
	/** \see SetDoCurtains */
	void SetAllowOnlyTwoOffsetsToBeRefinded(bool allowOnlyTwoOffsets);

	//! Increase precision for sharp edges (>= 90 degrees)
	void MWMSV_API SetLowTolEdge(bool enableLowTolEdge);

	//! Enable generation of statistics
	void SetStatistics(bool enableStatistics = false);

	//! Write statistics info to std::stringstream
	void GetStatisticsInfo(
		std::stringstream& infoText,  //!< stream to write to
		bool CSVOutput = false  //!< if false, write in human readable form, if true, write as CSV
	);

	/// Derives a precision from the target mesh.
	/** \returns computed precision
		\see SetTolerance */
	T MWMSV_API SetAutoPrecision(
		T numNails = 480000.0f,  //!< Maximum number of nails to be used
		T precTolRatio = 20.0f  //!< Precision can never be greater than precTolRatio * tolerance
	);

	//! Highest deviation from real offsetted mesh that is allowed.
	void MWMSV_API SetTolerance(T precision);

	// don't use debug purposes
	// void FindUnreachable(void);

	//! Set a progress handler.
	void MWMSV_API SetProgressHandler(mwMachSimVerifierProgressHandler* progressHandler);

	//! Set experimental parameters.
	void MWMSV_API SetExperimental(int params);

	//! Set factor for allowed tolerance near sharp edges
	/** The factor is multiplied to the global allowed tolerance.
		To enable sharp edge refinement, see SetLowTolEdge. */
	void MWMSV_API SetSharpEdgeTolRefinementFactor(T factor);

	//! Limit the maximum distance from the real offset surface at sharp edges.
	void MWMSV_API SetSharpEdgeDistLimitFactor(T factor);

	//! deprecated
	void MWMSV_API EnableOldStypeSplitDir(bool enable);

	//! deprecated
	bool MWMSV_API IsOldStyleSplitDirEnabled(void);

	/// Decides whether to remove triangles with very short edges
	/** The edge length under which triangles are removed can be set
		with SetMinEdgeLengthMeter.
		\see SetMinEdgeLengthMeter */
	void MWMSV_API SetCollapseShortEdgeTriangles(bool enable);
	//! \copydoc SetCollapseShortEdgeTriangles
	bool MWMSV_API GetCollapseShortEdgeTriangles() const;

	/// Minimum edge length threshold for valid triangles.
	/** ignored if CollapseShortEdgeTriangles is disabled.
		\see SetCollapseShortEdgeTriangles */
	void MWMSV_API SetMinEdgeLengthMeter(double lengthMeter);
	//! \copydoc SetMinEdgeLengthMeter
	double MWMSV_API GetMinEdgeLengthMeter(void) const;

	/// Decides whether to do multiple runs of degenerate triangle removal.
	/** It may happen that during removal triangles are created that are also degenerate.
		These will be catched if this option is enabled. */
	void MWMSV_API SetMultipleDegenTriRemoval(bool doMultipleRemovals);
	//! \copydoc SetMultipleDegenTriRemoval
	bool MWMSV_API GetMultipleDegenTriRemoval(void) const;

	/// Number of runs of ZigZag removal that shall be performed.
	/** ZigZag means "wrinkles" on the mesh surface, i.e. strips with near-180 degree turns on both
	 * sides */
	void MWMSV_API SetNumMaxZigZagRemoval(int newMax);
	//! \copydoc SetNumMaxZigZagRemoval
	int MWMSV_API GetNumMaxZigZagRemoval(void) const;

	//! Calculates and returns the offset mesh.
	MeshPtr MWMSV_API OffsetMesh(void);

	/// Refines the given mesh
	/** - Subdivides very thin triangles.
	 *  - Flips edges to better conform to the requested target mesh distance */
	MeshPtr MWMSV_API RefineOffsetMesh(MeshPtr& offsettedMesh);

	/// Returns the distance from point to target.
	/** Only usable after offsetting. Second parameter is ignored. */
	T MWMSV_API
	GetDistanceToTarget(const TPoint& point, const TPoint&, TPoint& witness, TPoint& witnessNormal);

	//! Serializes the offsetting operation and its parameters into a file
	bool Serialize(
		const misc::mwstring& fileName,
		const mwMeshOffsetterSerializationOptions::type options =
			mwMeshOffsetterSerializationOptions::DEFAULT) const;
	//! Serializes the offsetting operation, its parameters and its outputs into a file
	bool Serialize(
		const misc::mwstring& fileName,
		const MeshPtr& result,
		const mwMeshOffsetterSerializationOptions::type options =
			mwMeshOffsetterSerializationOptions::DEFAULT) const;

private:
	//! Internal class used for mesh offsetting.
	mwMeshoffsetterInputParams* m_inputParams;
	mwMeshOffsetterInternalExt* m_offsetter;

private:
	//! non-copyable
	mwMeshOffsetterExt(const mwMeshOffsetterExt&);
	mwMeshOffsetterExt& operator=(const mwMeshOffsetterExt&);
};
}  // namespace Verifier
#endif  //	MW_MWMESHOFFSETTEREXT_HPP_
