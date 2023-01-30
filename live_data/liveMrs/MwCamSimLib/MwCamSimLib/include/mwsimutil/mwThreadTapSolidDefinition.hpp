// (C) 2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWTHREADTAPSOLIDDEFINITION_HPP_
#define MW_MWTHREADTAPSOLIDDEFINITION_HPP_

#include "mwAutoPointer.hpp"
#include "mwSolidDefinition.hpp"

#include <mwLanguageFeatures.hpp>

namespace cadcam
{
/// This class describes a (cylindrical) threaded solid. The solid is intended to be used as part of
/// a thread-tapping tool. The shape of the threads is currently unspecified, and they may be
/// simulated as circles.
template <typename T>
class MW_5AXUTIL_API mwThreadTapSolidDefinition: public mwSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwThreadTapSolidDefinition<T>> Ptr;
	typedef typename mwSolidDefinition<T>::Units Units;

	enum ThreadDirection
	{
		TD_LEFT_HANDED,
		TD_RIGHT_HANDED,
	};

	struct Parameters
	{
		T outerRadius;
		T innerRadius;
		T height;
		T pitch;
		ThreadDirection threadDirection;

		Parameters()
			: outerRadius(0), innerRadius(0), height(0), pitch(0), threadDirection(TD_RIGHT_HANDED)
		{
		}

		Parameters(T outerRadius, T innerRadius, T height, T pitch, ThreadDirection threadDirection)
			: outerRadius(outerRadius),
			  innerRadius(innerRadius),
			  height(height),
			  pitch(pitch),
			  threadDirection(threadDirection)
		{
		}

		bool operator==(const Parameters& other) const
		{
			return outerRadius == other.outerRadius && innerRadius == other.innerRadius &&
				height == other.height && pitch == other.pitch &&
				threadDirection == other.threadDirection;
		}
	};

	/// Calculates the inner radius based on outerRadius and pitch:
	/// https://en.wikipedia.org/wiki/ISO_metric_screw_thread The thread is assumed to be
	/// right-handed.
	///
	/// @note The shape of the threads is currently unspecified. Therefore the tool mesh and the
	/// simulation may not look like an ISO metric thread, even when using this helper function.
	static Parameters CreateISOMetricThreadParameters(
		const T outerRadius, const T pitch, const T height);

	/// Creates a cylindrical solid with the given radius and height.
	/// * the volume between outer and inner radius is filled by threads
	/// * the volume inside the inner radius is completely filled
	/// * the distance between two thread revolutions is given by the pitch
	/// * the shape of the threads is unspecified
	mwThreadTapSolidDefinition(const Parameters& params, const Units units);

	const Parameters& GetParameters() const { return m_params; }

	/// Returns the solid's bounding box (not necessarily in tool coordinates).
	const mw3dBoundingBox<T> GetBoundingBox3d() const MW_FINAL;

	void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor) MW_FINAL;
	void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const MW_FINAL;

	bool operator==(const mwThreadTapSolidDefinition<T>& other) const
	{
		return mwSolidDefinition<T>::operator==(other) && m_params == other.m_params;
	}

private:
	Parameters m_params;

protected:
	void Scale(const Units units, const double& scaleFactor) MW_FINAL;
};

}  // namespace cadcam
#endif  //	MW_MWTHREADTAPSOLIDDEFINITION_HPP_
