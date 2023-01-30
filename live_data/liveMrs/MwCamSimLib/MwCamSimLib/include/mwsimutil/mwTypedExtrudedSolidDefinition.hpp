// (C) 2016-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTYPEDEXTRUDEDSOLIDDEFINITION_HPP_
#define MW_MWTYPEDEXTRUDEDSOLIDDEFINITION_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwSolidDefinition.hpp"
#pragma warning(push)
#pragma warning(disable : 4996)
namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwTypedExtrudedSolidDefinition: public mwSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwTypedExtrudedSolidDefinition<T>> Ptr;
	typedef typename mwSolidDefinition<T>::Units Units;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	enum Hand
	{
		HD_LEFT = 0,
		HD_RIGHT = 1
	};

	enum Shank
	{
		SK_RECTANGULAR = 0,

		// !The cylindrical shank is reserved and not supported.
		SK_CYLINDRICAL = 1
	};

	explicit mwTypedExtrudedSolidDefinition(const Units units);

	mwTypedExtrudedSolidDefinition(
		const Hand hand, const Shank shank, const T height, const Units units);

	bool operator==(const mwTypedExtrudedSolidDefinition<T>& rToCompare) const;

	/// Returns the holder's hand.
	Hand GetHand() const;

	/// Returns the holder's shank shape type.
	Shank GetShank() const;

	/// Returns the height of the typed extruded solid.
	const T GetExtrusionHeight() const;

	MW_DEPRECATED("Deprecated since 2017.12. Use GetBoundingBox3d().GetSizeY()")
	virtual const T GetHeight() const { return this->GetBoundingBox3d().GetSizeY(); };

protected:
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	T m_height;
	Shank m_shank;
	Hand m_hand;
};
#pragma warning(pop)
template <typename T>
inline void cadcam::mwTypedExtrudedSolidDefinition<T>::Scale(const Units, const double& scaleFactor)
{
	m_height *= static_cast<T>(scaleFactor);
}

template <typename T>
cadcam::mwTypedExtrudedSolidDefinition<T>::mwTypedExtrudedSolidDefinition(
	const Hand hand, const Shank shank, const T height, const Units units)
	: mwSolidDefinition<T>(units), m_hand(hand), m_shank(shank), m_height(height)
{
	if (hand < mwTypedExtrudedSolidDefinition<T>::HD_LEFT ||
		hand > mwTypedExtrudedSolidDefinition<T>::HD_RIGHT)
		throw mwcadcamException(mwcadcamException::INVALID_TURNING_SOLID_DEFINITION_HAND);

	if (shank == mwTypedExtrudedSolidDefinition<T>::SK_CYLINDRICAL)
		throw mwcadcamException(
			mwcadcamException::
				TURNING_SOLID_DEFINITION_CYLINDRICAL_SHANK_RESERVED_AND_NOTSUPPORTED);

	if (shank != mwTypedExtrudedSolidDefinition<T>::SK_RECTANGULAR)
		throw mwcadcamException(mwcadcamException::INVALID_TURNING_SOLID_DEFINITION_SHANK);

	if (mathdef::is_lte(static_cast<T>(height), 0))
		throw mwcadcamException(mwcadcamException::INVALID_TURNING_SOLID_DEFINITION_HEIGHT);
}

template <typename T>
mwTypedExtrudedSolidDefinition<T>::mwTypedExtrudedSolidDefinition(const Units units)
	: mwSolidDefinition<T>(units),
	  m_height(
		  units == measures::mwUnitsFactory::METRIC ? static_cast<T>(10) : static_cast<T>(0.393)),
	  m_shank(mwTypedExtrudedSolidDefinition<T>::SK_RECTANGULAR),
	  m_hand(mwTypedExtrudedSolidDefinition<T>::HD_RIGHT)
{
}

template <typename T>
typename mwTypedExtrudedSolidDefinition<T>::Hand mwTypedExtrudedSolidDefinition<T>::GetHand() const
{
	return m_hand;
}

template <typename T>
typename mwTypedExtrudedSolidDefinition<T>::Shank mwTypedExtrudedSolidDefinition<T>::GetShank()
	const
{
	return m_shank;
}

template <typename T>
const T mwTypedExtrudedSolidDefinition<T>::GetExtrusionHeight() const
{
	return m_height;
}

template <typename T>
bool mwTypedExtrudedSolidDefinition<T>::operator==(
	const mwTypedExtrudedSolidDefinition<T>& rToCompare) const
{
	if (&rToCompare == this)
		return true;

	if (!mwSolidDefinition<T>::operator==(rToCompare))
		return false;

	return m_height == rToCompare.m_height && m_shank == rToCompare.m_shank &&
		m_hand == rToCompare.m_hand;
}
}  // namespace cadcam
#endif  //	MW_MWTYPEDEXTRUDEDSOLIDDEFINITION_HPP_
