// (C) 2011-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMESHOFFSETER_HPP_
#define MW_MWMESHOFFSETER_HPP_
#include "mw3dBoundingBox.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"

#include <vector>

class mwMachSimVerifierProgressHandler;  // forward declaration

namespace Verifier
{
//! Functionality for calculating mesh offsets
/*!
	\tparam T scalar type of the mesh
*/
template <class T>
class MW_5AXUTIL_API mwMeshOffseter
{
public:
	typedef cadcam::mwTMesh<T> Mesh;
	typedef typename misc::mwAutoPointer<Mesh> MeshAptr;
	typedef std::vector<MeshAptr> MeshArray;

	//! Structure used to bind mesh AutoPointer, it`s offset and color value
	struct MeshDataStructure
	{
		MeshAptr mesh;  //!< mesh pointer
		T offset;  //!< offset value

		MeshDataStructure(): mesh(NULL), offset(0) {}

		MeshDataStructure(const MeshDataStructure& mtc): mesh(mtc.mesh), offset(mtc.offset) {}
	};
	typedef std::vector<MeshDataStructure> MeshesVector;

	//! Structure used to contain offsetted meshes by their directions
	struct MeshDirectionalStructure
	{
		MeshAptr innerMesh;  //!< offset part, obtained by offsetting inside(AutoPointer to mesh)
		MeshAptr outerMesh;  //!< offset part, obtained by offsetting outside(AutoPointer to mesh)
		MeshAptr rolloverMesh;  //!< offset part, obtained by offsetting between inside and outside.
		MeshDirectionalStructure(): innerMesh(NULL), outerMesh(NULL), rolloverMesh(NULL) {}
	};

	//! Offset mesh(simple offset of single mesh)
	/*!
		\param inputMesh mesh to offset
		\param offsetValue offset Value
		\param precision precision of dexel field, used during offsetting
		\param forceNoSharpening
		\param progressHandler handler for receiving progress updates
		\return AutoPointer to offsetted mesh
	*/
	static MeshAptr OffsetMesh(
		const Mesh& inputMesh,
		const T offsetValue,
		const T precision,
		const bool forceNoSharpening = false,
		mwMachSimVerifierProgressHandler* progressHandler = NULL);

	//! Offset meshes(offset of multiply meshes with different offset values)
	/*!
		\param inputMeshes vector of input meshes to offset(offset value is in a vector)
		\param precision precision of dexel field, used during offsetting
		\param progressHandler handler for receiving progress updates
		\return AutoPointer to offsetted mesh
	*/
	static MeshAptr OffsetMeshes(
		const MeshesVector& inputMeshes,
		const T precision,
		mwMachSimVerifierProgressHandler* progressHandler = NULL);

	//! Directional meshes offset(offset of multiply meshes with different offset value)
	/*!
		Result divide to internal/external offset and rollover.
					in/out direction detected by triangles normals.
		\param inputMeshes vector of input meshes to offset(offset value is in a vector structure)
		\param precision precision used during offsetting
		\param glueTolerance tol value used to glue gaps in mesh
		\param correctEdgesFlag filter result mesh edges to disable "jagged style"
		\param disableRolloverFlag divide only for inner and outer parts. No rollover detected.
		\return in/out/rollover structure that contains pointers to meshes.
	*/
	static MeshDirectionalStructure OffsetDirectionalMeshes(
		const MeshesVector& inputMeshes,
		const T precision,
		const T glueTolerance = T(0.000001),
		const bool correctEdgesFlag = false,
		const bool disableRolloverFlag = false);

	//! Split mesh to inner/outer meshes
	/*!
		\param originMesh original mesh to split
		\param innerMesh reference to internal mesh(result)
		\param outerMesh reference to external mesh(result)
	*/
	static void SplitMeshToInnerOuter(const Mesh& originMesh, Mesh& innerMesh, Mesh& outerMesh);

	//! Split mesh to inner/outer meshes
	/*!
		\param originMeshes original meshes to split
		\param innerMesh reference to internal mesh(result)
		\param outerMesh reference to external mesh(result)
	*/
	static void SplitMeshesToInnerOuter(
		const std::vector<MeshAptr>& originMeshes, Mesh& innerMesh, Mesh& outerMesh);

	//! Estimate comfort(optimal) mesh offseter precision
	/*!
		\param meshBoundingBox bounding box of mesh to offset
		\param offsetValue offset value
		\param nailsNumber optimal number of nails(may not be specified)
		\return precision value
	*/
	static T EstimateMeshOffseterComfortMinimalPrecision(
		const cadcam::mw3dBoundingBox<T>& meshBoundingBox,
		const T offsetValue,
		const T nailsNumber = static_cast<T>(50000));
};
}  // namespace Verifier
#endif  //	MW_MWMESHOFFSETER_HPP_
