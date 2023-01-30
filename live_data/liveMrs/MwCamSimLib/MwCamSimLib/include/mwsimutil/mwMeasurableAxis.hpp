// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMEASURABLEAXIS_HPP_
#define MW_MWMEASURABLEAXIS_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"


namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mwMeasurableAxis: public measures::mwMeasurable
{
public:
	enum axis
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z
	};
	mwMeasurableAxis(const axis vAxis, const Units units);
	mwMeasurableAxis(const mwMeasurableAxis<T>& rToCopy);
	mwMeasurableAxis(const axis vAxis, const T& value, const Units units);
	virtual ~mwMeasurableAxis(){}
	const mwMeasurableAxis& operator=(const mwMeasurableAxis<T>& rToCopy);
	bool operator==(const mwMeasurableAxis<T>& rToCompare);
	const T GetValue() const { return m_value; }
	void SetValue(const T& vValue);
	const axis GetAxis() const { return m_axis; }
	void SetAxis(const axis vAxis);
protected:
	virtual void Scale(const Units units, const double& scaleFactor);
private:
	void Copy(const mwMeasurableAxis<T>& rToCopy);
	void Validate(const axis vAxis);
	T m_value;
	axis m_axis;
};

}  // namespace cadcam
#endif  //	MW_MWMEASURABLEAXIS_HPP_
