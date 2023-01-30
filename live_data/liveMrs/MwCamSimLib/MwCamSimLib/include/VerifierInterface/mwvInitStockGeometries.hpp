// (C) 2017-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVINITSTOCKGEOMETRIES_HPP_
#define MW_MWVINITSTOCKGEOMETRIES_HPP_

#include "mwVerifierNestedEnums.hpp"
#include "mwvInitStockGeometriesForward.hpp"
#include "mwvInitStockGeometry.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mw3dBoundingBox.hpp>
#include <mwOverrideFinal.hpp>

namespace VerifierUtil
{
/// Initial stock geometry description for box-shaped stocks.
/// See also @ref mwMachSimVerifier::SetStockCube().
class MW_VERIFIER_API mwvInitStockCube : public mwvInitStockGeometry
{
public:
	mwvInitStockCube(const BoundingBox3d& stockBox);
	mwvInitStockCube(const BoundingBox3d& stockBox, const BoundingBox3d& additiveBox);

	Ptr Clone() const MW_OVERRIDE;

	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;
	const float GetTolerance() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_stockBox;
	BoundingBox3d m_additiveBox;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);
};

/// Initial empty stock description for additive-only simulation.
/// See also @ref mwMachSimVerifier::SetStockEmptyCube().
class MW_VERIFIER_API mwvInitStockEmptyCube : public mwvInitStockGeometry
{
public:
	mwvInitStockEmptyCube(const BoundingBox3d& additveBox);

	Ptr Clone() const MW_OVERRIDE;

	/// Returns an uninitialized BoundingBox3d.
	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;
	const float GetTolerance() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_additiveBox;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);
};


/// Initial stock geometry description for cylinder shapes.
/// See also @ref mwMachSimVerifier::SetStockCylinder().
class MW_VERIFIER_API mwvInitStockCylinder : public mwvInitStockGeometry
{
public:
	typedef cadcam::mwTPoint3d<float> float3d;

	mwvInitStockCylinder(
		const float height, const float radius, const float3d& pos, const float3d& axis);

	mwvInitStockCylinder(
		const float height,
		const float radius,
		const float3d& pos,
		const float3d& axis,
		const BoundingBox3d& additiveBox);

	Ptr Clone() const MW_OVERRIDE;

	float GetRadius() const;
	float GetHeight() const;
	float3d GetAxis() const;
	float3d GetRefPoint() const;

	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;
	const float GetTolerance() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_stockBox;
	BoundingBox3d m_additiveBox;

	float m_height;
	float m_radius;
	float3d m_refPoint;
	float3d m_axis;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);
};

template <class Archive>
void save_construct_data(
	Archive& ar, const VerifierUtil::mwvInitStockMesh* t, const unsigned int version);
template <class Archive>
void load_construct_data(
	Archive& ar, VerifierUtil::mwvInitStockMesh* t, const unsigned int version);

/// Initial stock geometry description based on meshes.
/// See also @ref mwMachSimVerifier::SetMesh().
class MW_VERIFIER_API mwvInitStockMesh : public mwvInitStockGeometry
{
public:
	typedef misc::mwAutoPointer<cadcam::mwTMesh<float>> MeshPtr;

	mwvInitStockMesh(
		const MeshPtr& mesh,
		float tolerance = -1,
		const BoundingBox3d& additiveBox = BoundingBox3d());
	mwvInitStockMesh(const MeshPtr& mesh, const BoundingBox3d& additiveBox);

	/// The stock will be the union of all meshes.
	mwvInitStockMesh(
		const std::vector<MeshPtr>& meshes,
		float tolerance = -1,
		const BoundingBox3d& additiveBox = BoundingBox3d());
	mwvInitStockMesh(const std::vector<MeshPtr>& meshes, const BoundingBox3d& additiveBox);
	~mwvInitStockMesh();

	Ptr Clone() const MW_OVERRIDE;

	const std::vector<MeshPtr>& GetMeshes() const;
	const float GetTolerance() const MW_OVERRIDE;

	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_stockBox;
	BoundingBox3d m_additiveBox;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<MeshPtr> m_meshes;
	float m_tolerance;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);

	template <class Archive>
	friend void save_construct_data(
		Archive& ar, const mwvInitStockMesh* t, const unsigned int version);
	template <class Archive>
	friend void load_construct_data(Archive& ar, mwvInitStockMesh* t, const unsigned int version);
};

/// Initial stock geometry description based on a 2D contour and the axis of revolution.
/// See also @ref mwMachSimVerifier::SetStockRevolved().
class MW_VERIFIER_API mwvInitStockRevolved : public mwvInitStockGeometry
{
public:
	typedef cadcam::mwTPoint3d<float> float3d;
	typedef ::VerifierUtil::StockSpindleAxis StockSpindleAxis;

	mwvInitStockRevolved(const cadcam::mw2dfContour& contour, const StockSpindleAxis revolvedAxis);
	mwvInitStockRevolved(
		const cadcam::mw2dfContour& contour,
		const StockSpindleAxis revolvedAxis,
		const BoundingBox3d& additiveBox);
	~mwvInitStockRevolved();
	Ptr Clone() const MW_OVERRIDE;

	const cadcam::mw2dfContour& GetContour() const;
	StockSpindleAxis GetRevolvedAxis() const;
	float GetRadius() const;
	float GetHeight() const;
	float3d GetRefPoint() const;

	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;
	const float GetTolerance() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_stockBox;
	BoundingBox3d m_additiveBox;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<cadcam::mw2dfContour> m_contour;
	StockSpindleAxis m_revolvedAxis;

	float m_radius;
	float m_height;
	float3d m_refPoint;


	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);

	template <class Archive>
	friend void save_construct_data(
		Archive& ar, const mwvInitStockRevolved* t, const unsigned int version);
	template <class Archive>
	friend void load_construct_data(
		Archive& ar, mwvInitStockRevolved* t, const unsigned int version);
};


/// @hidden
/// For internal use only.
class MW_VERIFIER_API mwvInitStockOffsettedMesh : public mwvInitStockGeometry
{
public:
	typedef misc::mwAutoPointer<cadcam::mwTFractedMesh<float>> FrMeshPtr;

	mwvInitStockOffsettedMesh(const FrMeshPtr& offsettedMesh);
	Ptr Clone() const MW_OVERRIDE;
	const BoundingBox3d GetBoundingBox() const MW_OVERRIDE;
	const BoundingBox3d GetAdditiveBox() const MW_OVERRIDE;

	const FrMeshPtr& GetOffsettedMesh() const;
	const float GetTolerance() const MW_OVERRIDE;

	/// @hidden
	void Accept(mwvInitStockGeometryVisitor& visitor) const MW_OVERRIDE;

private:
	BoundingBox3d m_stockBox;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	FrMeshPtr m_offsettedMesh;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);
};

/// @hidden
/// Visitor interface for stock geometries.
class MW_VERIFIER_API mwvInitStockGeometryVisitor
{
public:
	virtual ~mwvInitStockGeometryVisitor();

	virtual void Visit(const mwvInitStockGeometry&) = 0;
	virtual void Visit(const mwvInitStockCube& cube) = 0;
	virtual void Visit(const mwvInitStockEmptyCube& cube) = 0;
	virtual void Visit(const mwvInitStockCylinder& cylinder) = 0;
	virtual void Visit(const mwvInitStockMesh& mesh) = 0;
	virtual void Visit(const mwvInitStockRevolved& revolved) = 0;
	virtual void Visit(const mwvInitStockOffsettedMesh& offsettedMesh) = 0;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVINITSTOCKGEOMETRIES_HPP_
