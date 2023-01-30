// (C) 2004-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWREVOLVEPROFILESRV_HPP_
#define MW_MWREVOLVEPROFILESRV_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwMeasurableAxis.hpp"

#include <list>

// includes below are not necessary
// kept for API compatibility reasons only
#include "mw2dPolyLine.hpp"
#include "mw3dPolyLine.hpp"
#include "mw3dShapeList.hpp"
#include "mwAutoPointer.hpp"
#include "mwCylinder.hpp"
#include "mwMesh.hpp"
#include "mwStringConversions.hpp"
#include "mwTPoint3d.hpp"
#include "mwTruncatedCone.hpp"

namespace cadcam
{
template <class T>
class mw3dShapeList;
template <typename T>
class MW_5AXUTIL_API mwRevolveProfileSrv
{
public:
	typedef mwTPoint3d<T> Point;
	typedef mwTMesh<T> Mesh;
	typedef misc::mwAutoPointer<Mesh> MeshPtr;
	typedef mw3dPolyLine<T> Profile;
	typedef mwTruncatedCone<T> TruncatedCone;
	typedef mwCylinder<T> Cylinder;
	typedef misc::mwAutoPointer<Profile> ProfilePtr;
	typedef std::list<ProfilePtr> Profiles;
	typedef mw3dShapeList<T> ShapeList;
	typedef typename Profiles::iterator ProfileIt;
	typedef typename Profiles::const_iterator ProfileCIt;
	typedef typename std::vector<Point>::const_iterator ProfilePointCIt;

	mwRevolveProfileSrv(const T& profileTolerance);
	virtual ~mwRevolveProfileSrv();
	/// Creates a 3D profile list from a polyline by rotating the polyline around OZ axis
	void Revolve(
		const ProfilePtr& profile,
		Profiles& profiles,
		const bool returnOnlyValidProfiles = false,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		bool profileInXZplane = true);
	/// Create a list of truncated cones from a 2dProfiles
	void CreateTruncatedConesOZ(const ProfilePtr& profile, ShapeList& shapeList);
	/// Print mesh to file
	void PrintMesh(const Mesh& mesh, const misc::mwstring& fileName) const;
	/// Print profile to file
	static void PrintProfile(const Profile& profile, const misc::mwstring& fileName);
	/// Calculate the number of steps
	const int CalculateNumberOfSteps(
		const ProfilePtr& profile,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);
	static const ProfilePtr ConvertFrom2dXYto3dXY(const mw2dPolyLine<T>& src);

protected:
	T m_collDetTol;
	/// profile tolerance
	T m_profileTol;

private:
	// To revolve the profiles
	static ProfilePtr RevolveProfile(
		const Profile& profile,
		const T& rAngle,
		const typename mwMeasurableAxis<T>::axis& axis,
		bool profileInXZplane);
	// To get the maximum radius of the profile points
	T GetMaxRadius(
		const ProfilePtr& profile,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);
};
}  // namespace cadcam
#endif  //	MW_MWREVOLVEPROFILESRV_HPP_
