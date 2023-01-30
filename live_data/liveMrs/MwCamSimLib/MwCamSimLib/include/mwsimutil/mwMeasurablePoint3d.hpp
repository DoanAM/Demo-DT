// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMEASURABLEPOINT3D_HPP_
#define MW_MWMEASURABLEPOINT3D_HPP_
#include "mw3dPoint.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"

namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mwMeasurablePoint3d: public mw3dPoint<T>, public measures::mwMeasurable
{
public:
	typedef measures::mwUnitsFactory::Units Units;
	mwMeasurablePoint3d(const Units units);
	mwMeasurablePoint3d(const mwMeasurablePoint3d<T>& rToCopy);
	mwMeasurablePoint3d(const mw3dPoint<T>& rToCopy, const Units units);
	mwMeasurablePoint3d(const T& first, const T& second, const T& third, const Units units);

	virtual ~mwMeasurablePoint3d(){}
	const mwMeasurablePoint3d& operator=(const mwMeasurablePoint3d<T>& rToCopy);
	bool operator==(const mwMeasurablePoint3d<T>& rToCompare);
protected:
	virtual void Scale(const Units units, const double& scaleFactor);
};
}  // namespace cadcam
#endif  //	MW_MWMEASURABLEPOINT3D_HPP_
