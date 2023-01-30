// (C) 2017-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVINITSTOCKGEOMETRY_HPP_
#define MW_MWVINITSTOCKGEOMETRY_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvInitStockGeometriesForward.hpp"

#include <mw3dGeometryTypedefs.hpp>
#include <mwAutoPointer.hpp>

namespace VerifierUtil
{
/// Interface for stock geometries.
class MW_VERIFIER_API mwvInitStockGeometry
{
public:
	typedef misc::mwAutoPointer<mwvInitStockGeometry> Ptr;
	typedef cadcam::mw3dBoundingBox<float> BoundingBox3d;

	virtual ~mwvInitStockGeometry();

	/// Returns a cloned copy of the object.
	virtual Ptr Clone() const;

	/// The (solid stock) bounding box.
	virtual const BoundingBox3d GetBoundingBox() const;
	/// The additive space bounding box.
	virtual const BoundingBox3d GetAdditiveBox() const;

	virtual const float GetTolerance() const;

	/// @hidden
	virtual void Accept(mwvInitStockGeometryVisitor& visitor) const;

protected:
	mwvInitStockGeometry();

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int file_version);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVINITSTOCKGEOMETRY_HPP_
