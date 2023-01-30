// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMESHOFFSETTEREXTINF_HPP_
#define MW_MWMESHOFFSETTEREXTINF_HPP_
#ifdef _WIN32
#define MWMSV_API __stdcall
#else
#define MWMSV_API
#endif

#include "mwMesh.hpp"

class mwMachSimVerifierProgressHandler;

template <typename T>
class MW_5AXUTIL_API mwMeshOffsetterExtInf
{
public:
	// types
	typedef misc::mwAutoPointer<mwMeshOffsetterExtInf<T>> Ptr;
	typedef typename cadcam::mwTMesh<T> Mesh;
	typedef typename misc::mwAutoPointer<Mesh> MeshPtr;
	typedef typename cadcam::mwTPoint3d<T> TPoint;

	//! Experimental flags
	enum Experimental
	{
		/*	It will use only verifier offset (edge sharpening on).
			No Open Mesh refinement.
		*/
		EXP_OM_NO_ADDITIONAL_REFINEMENT = 0,
		/* With Open Mesh refinement. */
		EXP_OM_OFFSETTER = 1,
		/* With rerastering. Use with caution! Unstable and slow atm. */
		EXP_OMRERASTER_OFFSETTER
	};

	//! constructor
	mwMeshOffsetterExtInf(){};

	//! destructor
	virtual ~mwMeshOffsetterExtInf(){};

	//! Set input mesh for offsetting.
	virtual void MWMSV_API SetTargetMesh(const MeshPtr& inputMesh) = 0;

	//! Set the offset value.
	virtual void MWMSV_API SetOffset(T offset) = 0;

	//! Set the precision. It is the nail distance in verifier base offset.
	virtual void MWMSV_API SetPrecision(T precision) = 0;

	//! Set the tolerance (only used if if SetExperimental(EXP_OM_OFFSETTER) or
	//! EXP_OMRERASTER_OFFSETTER)
	/*	During edge refinement, if an edge is at a distance > tolerance it will be refined.
	 */
	virtual void MWMSV_API SetTolerance(T tolerance) = 0;

	//! Enables a lower tolerance value for sharp edges.
	virtual void MWMSV_API SetLowTolEdge(bool enableLowTolEdge) = 0;

	//! It replaces the calls to SetPrecision and SetTolerance with limited number of nails.
	virtual T MWMSV_API SetAutoPrecision(T numNails = 480000.0f, T precTolRatio = 20.0f) = 0;

	//! Set the offsetting progress handler.
	virtual void MWMSV_API
	SetProgressHandler(mwMachSimVerifierProgressHandler* progressHandler) = 0;

	//! Set bit mask experimental params
	virtual void MWMSV_API SetExperimental(int params) = 0;

	//! Calculates and returns the offset mesh.
	virtual MeshPtr MWMSV_API OffsetMesh(void) = 0;

	//! Returns the distance from point to target.
	virtual T MWMSV_API GetDistanceToTarget(
		const TPoint& point, const TPoint& normal, TPoint& witness, TPoint& witnessNormal) = 0;
};

#endif  //	MW_MWMESHOFFSETTEREXTINF_HPP_
