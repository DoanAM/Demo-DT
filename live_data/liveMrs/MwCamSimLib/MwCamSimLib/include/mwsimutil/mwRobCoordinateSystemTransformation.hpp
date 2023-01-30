// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBCOORDINTAESYSTEMTRANSFORMATION_HPP_
#define MW_MWROBCOORDINTAESYSTEMTRANSFORMATION_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"

namespace post
{
//! Represents a coordinate system
class MW_5AXUTIL_API mwRobCoordinateSystemTransformation
{
public:
	//! CoordinateSystemTransformation constructor
	mwRobCoordinateSystemTransformation();
	//! CoordinateSystemTransformation
	/*!Coordinate system constructor
	 */
	explicit mwRobCoordinateSystemTransformation(
		const cadcam::mwPoint3d& rotation, const cadcam::mwPoint3d& translation);
	//! CoordinateSystemTransformation
	/*!Coordinate system constructor
		\param rotations angles in degree
		\param translations values
		*/

	mwRobCoordinateSystemTransformation(const mwRobCoordinateSystemTransformation& toCopy);

	//! CoordinateSystemTransformation assignment operator
	const mwRobCoordinateSystemTransformation& operator=(
		const mwRobCoordinateSystemTransformation& toCopy);
	//! CoordinateSystemTransformation equal operator
	bool operator==(const mwRobCoordinateSystemTransformation& toCompare) const;
	//! CoordinateSystemTransformation different operator
	bool operator!=(const mwRobCoordinateSystemTransformation& toCompare) const;

	//! Returns the origin of the coordinate system
	const cadcam::mwPoint3d& GetRotation() const;
	const cadcam::mwPoint3d& GetTranslation() const;

	void SetRotation(const cadcam::mwPoint3d& newRot);
	void SetTranslation(const cadcam::mwPoint3d& newRot);

protected:
	cadcam::mwPoint3d m_rotation;
	cadcam::mwPoint3d m_translation;
};

}  // namespace post
#endif	//	MW_MWROBCOORDINTAESYSTEMTRANSFORMATION_HPP_
