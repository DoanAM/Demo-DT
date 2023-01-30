// (C) 2003-2007 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPROFILETOCYLINDERAPPROXIMATION_HPP_
#define MW_MWPROFILETOCYLINDERAPPROXIMATION_HPP_
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwException.hpp"
#include "mwProfileToShapeIf.hpp"


namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mwTProfileToCylinderApproximation: public mwProfileToShapeIf<T>
{
public:
	typedef cadcam::mw2dPolyLine<T> Profile;

	mwTProfileToCylinderApproximation(const Profile& src);

	const T& GetRadius() const { return m_Radius; }

	const T& GetHeight() const { return m_Height; }

protected:
	virtual void CreateCylinder(const T& radius, const T& height, const T& position);

	virtual void CreateCone(
		const T& bottomRadius, const T& topRadius, const T& height, const T& position);

	T m_Radius, m_Height;


private:
	void CheckHeight(const T& newHeight);
	void CheckRadius(const T& newRadius);

};  // mwTProfileToCylinderApproximation class

typedef cadcam::mwTProfileToCylinderApproximation<double> mwProfileToCylinderApproximation;

}  // namespace cadcam
#endif  //	MW_MWPROFILETOCYLINDERAPPROXIMATION_HPP_
