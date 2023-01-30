// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVEGENERICMARKER_HPP_
#define MW_MWMOVEGENERICMARKER_HPP_
#include "mwAutoPointer.hpp"
#include "mwCadcamEnumDefinitions.hpp"
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwMoveGenericMarker
{
public:
	typedef misc::mwAutoPointer<mwMoveGenericMarker> Ptr;

	typedef mwMoveGenericMarkerN::StatusAttribute StatusAttribute;
	static const StatusAttribute UNCHANGED = mwMoveGenericMarkerN::UNCHANGED;
	static const StatusAttribute MODIFIED = mwMoveGenericMarkerN::MODIFIED;
	static const StatusAttribute REMOVED = mwMoveGenericMarkerN::REMOVED;
	static const StatusAttribute MW_GENERATED = mwMoveGenericMarkerN::MW_GENERATED;

	/// construct a mwMoveGenericMarker
	///
	///	@param data - pointer to a generic ( custom ) marker
	mwMoveGenericMarker(void* data);

	/// copy constructor
	///
	///	@param toCopy - marker which will be copy
	mwMoveGenericMarker(const mwMoveGenericMarker& toCopy);
	mwMoveGenericMarker& operator=(const mwMoveGenericMarker& toCopy);

	/// Deletes data if MW_GENERATED
	~mwMoveGenericMarker();

	/// obtain the generic ( custom ) marker
	///
	///	@return the pointer to the generic (custom) marker
	void* GetData() const;

	/// set the generic ( custom ) marker
	///
	///	@param data pointer to the generic ( custom ) marker
	void SetData(void* data);

	/// sets the status regarding the marker, default is UNCHANGED
	///
	///	@param status describing the attribute of the current marker
	void SetStatus(StatusAttribute status);

	/// get the current status attribute of the current marker
	///
	///	@return the status attribute of the current marker
	const StatusAttribute& GetStatus() const;

	const bool operator==(const mwMoveGenericMarker& toCompare) const;

	const bool operator!=(const mwMoveGenericMarker& toCompare) const;

protected:
	void* m_genericData;
	StatusAttribute m_status;
};
}  // namespace cadcam
#endif  //	MW_MWMOVEGENERICMARKER_HPP_
