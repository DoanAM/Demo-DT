// (C) 2011-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Mesh offseter with support of legacy interface

#ifndef MW_MWMESHOFFSETERLEGACYINTERFACE_HPP_
#define MW_MWMESHOFFSETERLEGACYINTERFACE_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"

class mwMachSimVerifierProgressHandler;  // forward declaration

namespace Verifier
{
//! Compute offset meshes
template <class T>
class MW_5AXUTIL_API mwMeshOffseterLegacyInterface
{
private:
	//		bool    m_meshMustBeUpdated;
	T m_offset;
	T m_resolution;
	bool m_resolutionDefined;
	bool m_sharpening;  // produces sharpened/unsharpened offset meshes

public:
	//! constructor
	mwMeshOffseterLegacyInterface()
		: m_offset(0), m_resolution(T(1)), m_resolutionDefined(false), m_sharpening(true)
	{
	}

	//! destructor
	virtual ~mwMeshOffseterLegacyInterface() {}

	//! Set offset value
	void SetOffset(const T newValue);

	//! Set sharpening
	void SetSharpening(const bool newValue);

	//! For compatibility
	void UseDefinedResolution(const bool useDefined, const T resolution);

	//! Get offseted mesh
	/*!
	\param inputMesh mesh to offset
	\param offsetedMesh output parameter for resulting offset
	\param bUseRemeshing unused
	\param factor
	\param progressHandler handler to receive updates of calculation progress
	*/
	void GetOffsetedMesh(
		const cadcam::mwTMesh<T>& inputMesh,
		cadcam::mwTMesh<T>& offsetedMesh,
		bool bUseRemeshing,
		T factor,
		mwMachSimVerifierProgressHandler* progressHandler = NULL);

	//! Get resolution from input parameters
	/*!
	\param inputMesh input mesh
	\param offset offset value
	\param factor
	\return the resolution value
	*/
	static T GetResolution(const cadcam::mwTMesh<T>& inputMesh, const T offset, const T factor);
};
}  // namespace Verifier
#endif  //	MW_MWMESHOFFSETERLEGACYINTERFACE_HPP_
