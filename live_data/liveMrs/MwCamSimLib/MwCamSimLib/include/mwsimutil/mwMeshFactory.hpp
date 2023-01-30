// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMESHFACTORY_HPP_
#define MW_MWMESHFACTORY_HPP_

#include "mw3dBoundingBox.hpp"
#include "mw3dPolyLine.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"
#include "mwRevolveProfileSrv.hpp"
#include "mwTPoint3d.hpp"

namespace cadcam
{
template <typename T>
struct mwTPoint3d;
template <typename T>
class mw3dPoint;

/// Generate triangle mesh based on different geometries
template <typename T, typename TVertex = mwTPoint3d<T>, typename TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwMeshFactory
{
public:
	typedef mwContainerMesh<T, TVertex, TFaceNormal> Mesh;
	typedef misc::mwAutoPointer<Mesh> MeshPtr;  /// @hidden
	typedef T ValueType;  /// @hidden
	typedef mw3dBoundingBox<ValueType> BoundingBox;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::Profile Profile;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::ProfilePtr ProfilePtr;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::Profiles Profiles;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::ProfileIt ProfileIt;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::ProfileCIt ProfileCIt;  /// @hidden
	typedef typename mwRevolveProfileSrv<ValueType>::ProfilePointCIt ProfilePointCIt;  /// @hidden
	typedef typename Mesh::point3d point3d;  /// @hidden
	typedef typename Mesh::vector3d vector3d;  /// @hidden
	typedef std::vector<TVertex> Silhouette;  /// @hidden
	typedef misc::mwAutoPointer<Silhouette> SilhouettePtr;  /// @hidden
	typedef mw2dPolyLine<T> profile2d;

	/// Type of caps for revolved geometries
	enum mwHasTop
	{
		HAS_TOP_NONE = 0,  ///< open at start and end
		HAS_TOP_START = 1,  ///< closed at the start
		HAS_TOP_END = 2,  ///< closed at the end
		HAS_TOP_BOTH = 3  ///< closed at start and end
	};

	enum mwHasBack
	{
		HAS_BACK_CONNECT_CENTER,
		HAS_BACK_CONNECT_DIRECT,
	};

	/// Compute bounding box for several meshes
	///
	///	@param meshes The meshes to compute the bounding box from
	///	@return the overall bounding box
	static mw3dBoundingBox<T> GetBoundingBox(const std::vector<typename mwTMesh<T>::Ptr>& meshes);

	/// Create a mesh from a mw3dBoundingBox object
	///
	///	@param boundingBox the bounding box to be "triangulated"
	///	@param units output mesh units
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateBox(
		const mw3dBoundingBox<T>& boundingBox, measures::mwMeasurable::Units units);

	/// Create a mesh from a list of 3D profiles
	///
	///	Consecutive profiles are connected using a triangle strip. Depending on the hasTop
	///	parameter the caps are closed using a triangle fan with a center defined by axis,
	///	disX, disY.
	///	@param units output mesh units
	///	@param profileList list of 3D profiles to generate from
	///	@param is_normals_in flag for normal direction
	///	@param hasTop flag telling if the caps should be closed
	///	@param axis axis orientation
	///	@param disX axis position in X
	///	@param disY axis position in Y
	///	@param isClosed if true then connect the last profile to the first profile otherwise just generate a sheet
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateExtruded(
		measures::mwMeasurable::Units units,
		const std::list<typename mw3dPolyLine<T>::Ptr>& profileList,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const T disX = 0,
		const T disY = 0,
		const bool isClosed = true);

	/// Creates a mesh from a 2D profile by revolving it around the provided axes.
	///
	///	@param units output mesh units
	///	@param profile 2D profile to generate from
	///	@param stepAngle the step angle for revolution in degrees
	///	@param is_normals_in flag for normal direction
	///	@param hasTop flags telling if the caps should be closed
	///	@param disX axis position in X
	///	@param disY axis position in Y
	///	@param axis Revolving mode. Possible values:
	///		@li mwMeasurableAxis<T>::AXIS_X revolve profile around X-axis.
	///		@image html "doc/Developer_guide/Toolpath_parameters/images/axis_x.gif" "" width=80%
	///		@li mwMeasurableAxis<T>::AXIS_Y revolve profile around Y-axis
	///		@image html "doc/Developer_guide/Toolpath_parameters/images/axis_y.gif" "" width=80%
	///		@li mwMeasurableAxis<T>::AXIS_Z revolve profile around Y-axis, then rotate resulting mesh
	///on 90 degrees from axis Y to axis Z
	///		@image html "doc/Developer_guide/Toolpath_parameters/images/axis_z.gif" "" width=80%
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateRevolved(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		const T& stepAngle,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const T disX = 0,
		const T disY = 0,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);

	/// Creates a mesh from a 2D profile by revolving it around the provided axes.
	///
	///	Profile is polygonized before revolving.
	///	@param units output mesh units
	///	@param profile the 2d polyline used for revolving.
	///	@param tolerance tolerance used for polygonization of profile
	///	@param axis axis used for revolving, see @ref CreateRevolved
	///	@param is_normals_in flag for normal direction
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateRevolved(
		measures::mwMeasurable::Units units,
		const mw2dContour<T>& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	/// Creates a mesh from a 2D profile, by revolving it around the provided axes.
	///
	///	@param units output mesh units
	///	@param profile the 2d polyline used for revolving.
	///	@param tolerance tolerance used for polygonization of profile
	///	@param axis axis used for revolving, see @ref CreateRevolved
	///	@param is_normals_in flag for normal direction
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateRevolved(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	/// Creates a mesh from a 3D profile, by revolving it around the provided axes.
	///
	///	@param units output mesh units
	///	@param profile the 3D profile used for revolving. It should be defined in XOY plane (Z=0).
	///	@param tolerance tolerance used for polygonization of profile
	///	@param axis axis used for revolving, see @ref CreateRevolved
	///	@param is_normals_in flag for normal direction
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateRevolved(
		measures::mwMeasurable::Units units,
		const typename mw3dPolyLine<T>::Ptr& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	/// Creates a mesh from a 2D profile by revolving it around given axis
	///
	/// Considered in 2D to be in XOY plane corresponding in 3D to XOZ
	///	@param units output mesh units
	///	@param profile the 2D profile
	///	@param startAngle the start angle for revolution in degrees
	///	@param endAngle the end angle for revolution in degrees
	///	@param stepAngle the step angle for revolution in degrees
	///	@param disX
	///	@param disY
	///	@param disZ
	///	@param is_normals_in flag for normal direction
	///	@param hasTop flag that defines if the caps should be closed
	///	@param axis axis used for revolving, see @ref CreateRevolved
	///	@param hasBack
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateRevolved(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		const T& startAngle,
		const T& endAngle,
		const T& stepAngle,
		const T disX = 0,
		const T disY = 0,
		const T disZ = 0,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_X,
		const mwHasBack hasBack = HAS_BACK_CONNECT_DIRECT);

	/// Creates a sphere mesh from the radius and center
	///
	///	@param units output mesh units
	///	@param center the center
	///	@param radius the radius
	///	@param stepAngle the step angle for revolution in degrees
	///	@param is_normals_in flag for normal direction
	///	@param axis pole axis orientation
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateSphere(
		measures::mwMeasurable::Units units,
		const TVertex& center,
		const T& radius,
		const T& stepAngle,
		const bool is_normals_in = false,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);

	/// Creates a mesh by extruding a 3D polyline along a given vector.
	///
	/// The mesh orientation is given by the orientation of the 3D closed polyline relatively to the
	/// sweep vector.
	///	@param basePolyline the base polyline (a reference to mw3dPolyLine)
	///	@param sweepVector a reference to vector3d representing the fiber
	///	@param units output mesh units
	///	@param iSlices the number of slices to be generated on the sweep part
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateExtruded(
		const mw3dPolyLine<T>& basePolyline,
		const vector3d& sweepVector,
		measures::mwMeasurable::Units units,
		const unsigned int iSlices = 1);

	/// Creates a mesh from a 3D bounding box by slicing it in small boxes first.
	///
	/// No little box can have any dimension greater than maxSegment. Each box is then split onto
	/// triangles (2 triangles per face)
	///	@param bb  the original 3d bounding box
	///	@param maxSegment the maximum length allowed for any dimension of the little boxed
	///	@param units output mesh units
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateBox(
		const mw3dBoundingBox<T>& bb, T maxSegment, measures::mwMeasurable::Units units);

	/// Creates a mesh by extruding a 3D polyline along a given vector.
	///
	/// The mesh orientation is given by the orientation of the 3d closed polyline relatively to the
	/// sweep vector.
	///	@param silhouette the silhouette (a vector of vector3d)
	///	@param sweepVector a reference to vector3d representing the fiber
	///	@param units output mesh units
	///	@param iSlices the number of slices to be generated on the sweep part
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateExtruded(
		const std::vector<TVertex>& silhouette,
		const vector3d& sweepVector,
		measures::mwMeasurable::Units units,
		const unsigned int iSlices = 1);

	/// Creates a mesh by extruding a 3D polyline from a start point to an end point.
	///
	/// The mesh orientation is given by the orientation of the 3d closed polyline relatively to the
	/// sweep vector.
	///	@param silhouette the silhouette (a vector of vector3d)
	///	@param startPoint start point
	///	@param endPoint end point
	///	@param iSlices the number of slices to be generated on the sweep part
	///	@param units output mesh units
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateExtruded(
		const std::vector<TVertex>& silhouette,
		const point3d& startPoint,
		const point3d& endPoint,
		measures::mwMeasurable::Units units,
		const unsigned int iSlices = 1);

	/// Creates meshes from cadcam shapes
	///
	///	The mesh is constructed from untransformed base shape, and transformed afterwards:
	///	- box is constructed from base bounding box
	///	- round shapes are constructed by revolving their profile
	///	@param shape the (cadcam) shape to be constructed.
	///	@param units output mesh units
	///	@param arcSegmentSize is the point distance to discretize curved shapes.
	///	@return Generated mesh
	static const typename mwTMesh<T>::Ptr CreateFromShape(
		const mw3dShape<T>& shape,
		measures::mwMeasurable::Units units,
		const T arcSegmentSize = static_cast<T>(0.01));

	/// Convert mesh with different types
	template <typename T2>
	static void Convert(const mwTMesh<T>& src, mwTMesh<T2>& dest);

	/// Convert mesh with different types
	template <typename T2>
	static void Convert(const Mesh& src, mwTMesh<T2>& dest);

	/// Creates the mesh of a disc segment aligned to an axis.
	///
	/// The mesh will be created as a triangle fan around the origin.
	///	@param units output mesh units
	///	@param radius The radius of the disc to be created.
	///	@param startAngleDegrees Degrees at which the segment should start.
	///	0 degrees is in direction of the next axis from the rotation axis when considering a
	///right-handed coordinate system.
	///	@param endAngleDegrees Degrees at which the segment should end.
	///	0 degrees is in direction of the next axis from the rotation axis when considering a
	///right-handed coordinate system.
	///	@param stepCount Defines the amount of triangles and therefore the precision of the disc.
	///	Must be at least 1 for segments < 180 degrees.
	///	Must be at least 2 for segments >= 180 degrees.
	///	Must be at least 3 for for full circles (360 degrees).
	///	THis is to avoid triangle degeneration and flipping.
	///	@param axis The axis to which the disc normal will be aligned.
	///	@return A mesh representing a disc segment.
	static const typename mwTMesh<T>::Ptr CreateDiscSegment(
		measures::mwMeasurable::Units units,
		const T& radius,
		const T startAngleDegrees,
		const T endAngleDegrees,
		const unsigned int stepCount,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);

	/// Creates the mesh of a disc aligned to an axis.
	///
	/// The mesh will be created as a triangle fan around the origin.
	///	@param units output mesh units
	///	@param radius The radius of the disc to be created.
	///	@param stepCount Defines the amount of vertices on the edge and therefore the precision of
	///the disc. Must be greater than 2.
	///	@param axis The axis to which the disc normal will be aligned.
	///	@param useNegativeNormals If set to true the vertex order of the triangles will be flipped
	///thus yielding inverse normals.
	///	@return A mesh representing a disc with normals aligned to a certain axis.
	static const typename mwTMesh<T>::Ptr CreateDisc(
		measures::mwMeasurable::Units units,
		const T& radius,
		const unsigned int stepCount,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool useNegativeNormals = false);

	/// Creates a mesh from faces and loops.
	///
	///	The mesh consists of a number of faces. Faces are made up of loops. Loops are made up of
	/// vertices and normals. 	The vertices and normals are referred to by their indices.
	///
	///	The number of faces is set by @p nfaces. The number of loops of each face is defined by the
	/// @p nloops array and 	equals @c 1 for a face without holes or @c 1+n for a face with n
	/// holes.
	///	@note The first loop must be given with vertices in counter-clockwise orientation and the
	/// holes in a clockwise orientation.
	///
	///	The number of vertices in each loop is defined by the @p nverts array. The number of
	/// vertices for the first 	loop of the i-th face will be at position @c j+1 where @c j is the
	/// sum of all loops of all previous faces. 	For each element n in @p nverts, there have to
	/// be n elements in @p indices and @p normal_indices if normals are used
	///	(@p indices and @p normal_indices have to be equal in size).
	///	Both indices arrays are grouped together so that the first @p nverts[0] indices belong to
	/// the first loop, the next @p nverts[1] indices to the second loop and so forth. This
	/// means the number of elements in @p indices and
	///	@p normal_indices is the sum of all elements in @p nverts. These indices then specify what
	/// vertices in
	///	@p verts and what normals in @p normals to use for a given loop. @n
	///	If you want to set the normal of a vertex to its face's normal you can set the index to @c
	/// -1.	If no normals are needed you can pass @c NULL as @p normal_indices and @p normals.
	///	@note The normals have to be normalized.
	///
	///	@param nfaces number of faces of the mesh to be created
	///	@param nloops array containing the number of loops for each face (must have @p nfaces
	/// elements)
	///	@param nverts array containing the number of vertices for each loop (must have as many
	/// elements as the sum of all @p nloops elements)
	///	@param indices array of indices for the vertices specified in @p verts
	///	@param verts array of vertices
	///	@param normal_indices array of indices for the normals specified in @p normals
	///	@param normals array of normal vectors
	///	@param units output mesh units
	///	@param coplanarityTolerance The tolerance used when checking the coplanarity of the vertices
	/// of a given face. 		If any face exceeds the tolerance, mesh creation fails.
	///	@return Generated mesh
	static typename mwTMesh<T>::Ptr Create(
		size_t nfaces,
		size_t nloops[],
		size_t nverts[],
		size_t indices[],
		TVertex verts[],
		int normal_indices[],
		TVertex normals[],
		measures::mwMeasurable::Units units,
		T coplanarityTolerance = mathdef::mw_tol(T()));

	/// Creates a triangle mesh out of a set of vertices
	///
	///	It is assumed that the given vertices lie in a single plane defined by the given normal. An
	/// exception is thrown 	if a vertex is further away from the plane than given @p maxPlaneDist.
	/// Further, it is assumed that the given vertices form a 	self-intersection free polygon when
	/// projected to the plane. The returned mesh is the triangulation of this polygon.
	///
	///	@param vertices which for the polygon in 3D space
	///	@param normal plane normal
	///	@param maxPlaneDist max allowed distance from any point in vertices to the plane
	///	@param units output mesh units
	///	@return mesh as the triangulation of the polygon
	static MeshPtr Create(
		std::vector<TVertex>& vertices,
		TVertex normal,
		T maxPlaneDist,
		measures::mwMeasurable::Units units);

	static const typename mwTMesh<T>::Ptr CreateExtruded(
		measures::mwMeasurable::Units units,
		const std::vector<mw2dPolyLine<T>>& profiles,
		const T bottomHeight,
		const mwTPoint3d<T>& direction);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateBox() instead.")
	static const MeshPtr Create(
		const mw3dBoundingBox<T>& boundingBox, measures::mwMeasurable::Units unit);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateExtruded() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const std::list<typename mw3dPolyLine<T>::Ptr>& profileList,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const T disX = 0,
		const T disY = 0);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateRevolved() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		const T& stepAngle,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const T disX = 0,
		const T disY = 0,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateRevolved() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const mw2dContour<T>& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateRevolved() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateRevolved() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const typename mw3dPolyLine<T>::Ptr& profile,
		T tolerance,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_Z,
		const bool is_normals_in = false);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateRevolved() instead.")
	static const MeshPtr Create(
		measures::mwMeasurable::Units units,
		const mw2dPolyLine<T>& profile,
		const T startAngle,
		const T endAngle,
		const T stepAngle,
		const T disX = 0,
		const T disY = 0,
		const T disZ = 0,
		const bool is_normals_in = false,
		const mwHasTop hasTop = HAS_TOP_BOTH,
		const typename mwMeasurableAxis<T>::axis& axis = mwMeasurableAxis<T>::AXIS_X,
		const mwHasBack hasBack = HAS_BACK_CONNECT_DIRECT);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateExtruded() instead.")
	static const MeshPtr Create(
		const mw3dPolyLine<T>& basePolyline,
		const vector3d& sweepVector,
		measures::mwMeasurable::Units units,
		const unsigned int iSlices = 1);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateBox() instead.")
	static const MeshPtr Create(
		const mw3dBoundingBox<T>& bb, T maxSegment, measures::mwMeasurable::Units unit);

	MW_DEPRECATED("Deprecated since 2017.08, please use CreateFromShape() instead.")
	static const MeshPtr Create(
		const mw3dShape<T>& shape,
		measures::mwMeasurable::Units units,
		const T arcSegmentSize = static_cast<T>(0.01));

private:
	mwMeshFactory();

};  // class mwMeshFactory

}  // namespace cadcam
#endif  //  MW_MWMESHFACTORY_HPP_