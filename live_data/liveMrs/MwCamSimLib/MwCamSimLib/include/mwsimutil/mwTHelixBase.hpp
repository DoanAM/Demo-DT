// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTHELIXBASE_HPP_
#define MW_MWTHELIXBASE_HPP_

#include "mwTBaseGeometry3d.hpp"

namespace geoDef
{
/** 
 * \brief Implements a uniform pitch helix
 * \tparam T Type to work with.
 */
template <typename T>
class MW_5AXUTIL_API mwTHelixBase : public mwTBaseGeometry3d <T>
{
public:
	typedef typename mwTBaseGeometry<T>::ValueType ValueType;

	/*!
		\param radius radius of the helix 
		\param sweepAngle sweep angle in radians
		\param step pitch of the helix per radian
	*/
	mwTHelixBase(const ValueType& radius,
		const ValueType& sweepAngle,
		const ValueType& step);
	void SetRadius(const ValueType& radius);
	const ValueType& GetRadius() const;
	//! Set the step of the helix. How much it elevates per one radian?
	void SetStep(const ValueType& step);
	//! Get the step of the helix. How much it elevates per one radian?
	const ValueType& GetStep() const;
	//! Set the sweep angle in radians
	void SetSweepAngle(const ValueType& SweepAngle);
	//! Get the sweep angle in radians
	const ValueType& GetSweepAngle() const;
	//! Get length of the helix
	const ValueType Length() const;
	const bool operator==(const mwTHelixBase<T>& toCompare) const;
protected:
	ValueType m_Radius;
	ValueType m_Step;
	ValueType m_SweepAngle;
};
}
#endif	//	MW_MWTHELIXBASE_HPP_
