// (C) 2020 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Declares the measurement results.

#ifndef MW_MWVMEASUREMEASUREMENT_HPP_
#define MW_MWVMEASUREMEASUREMENT_HPP_

#include "mwvMeasureCommon.hpp"

#include <mwDeprecated.hpp>

namespace VerifierUtil
{
namespace Measure
{
class Measurement
{
public:
	virtual ~Measurement() {}

	/// @return a positive value.
	virtual int GetMeasurePointCount() const = 0;

	/// The first geometry belongs to the primary measure-point.
	virtual const Geometry& GetGeometry(MeasurePointIdx idx) const = 0;

	/// @return null if is not measured (you do not own the returned pointer).
	virtual const Distance* GetThickness() const = 0;

	/// @copydoc GetThickness()
	virtual const Distance* GetDepth() const = 0;

	/// @copydoc GetThickness()
	virtual const Distance* GetClearance() const = 0;

	/// @copydoc GetThickness()
	virtual const Corner* GetCorner() const = 0;

	/// @copydoc GetThickness()
	virtual const Curvature* GetCurvature() const = 0;

	/// @copydoc GetThickness()
	virtual const Distance* GetDistance() const = 0;


	/// @deprecated Use GetGeometry() instead.
	MW_DEPRECATED("Deprecated in 2021.04, use GetGeometry() instead")
	const Geometry& GetMeasurePointGeometry(MeasurePointIdx idx) const;
};

inline const Geometry& Measurement::GetMeasurePointGeometry(MeasurePointIdx idx) const
{
	return GetGeometry(idx);
}

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREMEASUREMENT_HPP_
