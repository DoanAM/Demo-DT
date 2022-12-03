// (C) 2020-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Diverse optional features manually included.

#ifndef MW_MWVMEASUREMISC_HPP_
#define MW_MWVMEASUREMISC_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw3dGeometryTypedefs.hpp>
#include <mwAutoPointer.hpp>
#include <mwDeprecated.hpp>

class mwMachSimVerifier;

namespace VerifierUtil
{
namespace Measure
{
class MW_VERIFIER_API GuardedVerifier
{
public:
	virtual ~GuardedVerifier() {}

	virtual mwMachSimVerifier& Lock() = 0;

	virtual void Unlock() = 0;
};

struct MW_VERIFIER_API MeshWithEdges
{
	misc::mwAutoPointer<const cadcam::mwfMesh> mesh;
	std::vector<int> edgePoints;  ///< pairs of mesh points indices

	explicit MeshWithEdges(
		const misc::mwAutoPointer<const cadcam::mwfMesh>& mesh, const std::vector<int>& edgePoints);

	~MeshWithEdges();
};

struct MW_VERIFIER_API SelectionOptions
{
	bool vertex;  ///< = true
	bool linearEdge;  ///< = true
	bool arcEdge;  ///< = true
	bool edgeMidpoint;  ///< = true
	bool circularEdgeCenter;  ///< = false
	bool smallCircularEdgeCenter;  ///< = true
	bool adjustToPrimaryPoint;  ///< = true

	SelectionOptions();

	/// @deprecated Use smallCircularEdgeCenter instead.
	// MW_DEPRECATED("Deprecated, use smallCircularEdgeCenter instead")
	bool& circularEdgeCenterSelectionForSmallEdges;

	/// @deprecated Use vertex instead.
	// MW_DEPRECATED("Deprecated, use vertex instead")
	bool& vertexSnapping;

	/// @deprecated Use edgeMidpoint instead.
	// MW_DEPRECATED("Deprecated, use edgeMidpoint instead")
	bool& edgeMidpointSnapping;

	SelectionOptions& operator=(const SelectionOptions& right);
};

struct MW_VERIFIER_API DisplayedDimensions
{
	bool arcRadius;  ///< = true
	bool curvature;  ///< = true
	bool thickness;  ///< = true
	bool depth;  ///< = true
	bool clearance;  ///< = true
	bool corner;  ///< = true
	bool distance;  ///< = true

	DisplayedDimensions();

	/// @deprecated Use DisplayedDimensions() instead.
	MW_DEPRECATED("Deprecated in 2021.08, use DisplayedDimensions() instead")
	explicit DisplayedDimensions(
		bool arcRadius,
		bool curvature = true,
		bool thickness = true,
		bool depth = true,
		bool clearance = true,
		bool corner = true,
		bool distance = true);
};

struct MW_VERIFIER_API DrawnMeasurement : DisplayedDimensions
{
	misc::mwAutoPointer<Measurement> measurement;

	bool highlighted;

	DrawnMeasurement();

	explicit DrawnMeasurement(
		const misc::mwAutoPointer<Measurement>& measurement, bool highlighted = false);

	~DrawnMeasurement();

	/// @deprecated Use DrawnMeasurement(measurement, highlighted) instead.
	MW_DEPRECATED("Deprecated in 2021.08, use DrawnMeasurement(measurement, highlighted) instead")
	explicit DrawnMeasurement(
		const misc::mwAutoPointer<Measurement>& measurement,
		bool highlighted,
		bool arcRadius,
		bool curvature = true,
		bool thickness = true,
		bool depth = true,
		bool clearance = true,
		bool corner = true,
		bool distance = true);
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREMISC_HPP_
