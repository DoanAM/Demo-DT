// (C) 2014-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCOORDINATESYSTEM_HPP_
#define MW_MWCOORDINATESYSTEM_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"


namespace cadcam
{
/// Represents a coordinate system
class MW_5AXUTIL_API mwCoordinateSystem
{
public:
	enum COORD_AXIS
	{
		X_AXIS,
		Y_AXIS,
		Z_AXIS,
		CUSTOM
	};

	/// mwCoordinateSystem constructor
	mwCoordinateSystem();
	/// mwCoordinateSystem
	///
	/// Coordinate system constructor
	///	@param _origin origin of the coordinate system
	explicit mwCoordinateSystem(const cadcam::mwPoint3d& _origin);
	/// mwCoordinateSystem
	///
	/// Coordinate system constructor
	///	@param _origin origin of the coordinate system
	///	@param _dirx directon of x axis
	///	@param _diry directon of y axis
	///	@param _dirz directon of z axis
	mwCoordinateSystem(
		const cadcam::mwPoint3d& _origin,
		const cadcam::mwPoint3d& _dirx,
		const cadcam::mwPoint3d& _diry,
		const cadcam::mwPoint3d& _dirz);
	/// mwCoordinateSystem constructor
	mwCoordinateSystem(const mwCoordinateSystem& toCopy);

	/// mwCoordinateSystem assignment operator
	const mwCoordinateSystem& operator=(const mwCoordinateSystem& toCopy);
	/// mwCoordinateSystem equal operator
	bool operator==(const mwCoordinateSystem& toCompare) const;
	/// mwCoordinateSystem different operator
	bool operator!=(const mwCoordinateSystem& toCompare) const;

	/// Returns the origin of the coordinate system
	const cadcam::mwPoint3d& GetOrigin() const;
	/// Returns the X direction of the coordinate system
	const cadcam::mwPoint3d& GetDirX() const;
	/// Returns the Y direction of the coordinate system
	const cadcam::mwPoint3d& GetDirY() const;
	/// Returns the Z direction of the coordinate system
	const cadcam::mwPoint3d& GetDirZ() const;

	/// Sets the origin of the coordinate system
	void SetOrigin(const cadcam::mwPoint3d& newo);
	/// Sets the X direction of the coordinate system
	void SetDirX(const cadcam::mwPoint3d& newx);
	/// Sets the Y direction of the coordinate system
	void SetDirY(const cadcam::mwPoint3d& newy);
	/// Sets the Z direction of the coordinate system
	void SetDirZ(const cadcam::mwPoint3d& newz);


	/// Converts absolute coordinates to relative coordinates
	cadcam::mwPoint3d AbsoluteCoordToRelativeCoord(const cadcam::mwPoint3d& absolute) const;
	/// Converts relative coordinates to absolute coordinates
	cadcam::mwPoint3d RelativeCoordToAbsoluteCoord(const cadcam::mwPoint3d& relative) const;

	/// Converts absolute direction to relative direction. Direction is normalized
	cadcam::mwPoint3d AbsoluteDirToRelativeDir(const cadcam::mwPoint3d& absolute) const;
	/// Converts relative direction to absolute direction. Direction is normalized
	cadcam::mwPoint3d RelativeDirToAbsoluteDir(const cadcam::mwPoint3d& relative) const;

	/// Converts a vector in absolute coordinates to one in relative coordinates
	cadcam::mwPoint3d AbsoluteVectorToRelativeVector(const cadcam::mwPoint3d& vec) const;
	/// Converts a vector in relative coordinates to one in absolute coordinates
	cadcam::mwPoint3d RelativeVectorToAbsoluteVector(const cadcam::mwPoint3d& vec) const;


	/// Converts an axis to a coordinate pair
	const std::pair<cadcam::mwPoint3d, cadcam::mwPoint3d> AxisToCoord(
		const int axis, const cadcam::mwPoint3d& start, const cadcam::mwPoint3d& end) const;
	/// Converts a coordinate pair to an axis index
	const int CoordToAxis(const cadcam::mwPoint3d& start, const cadcam::mwPoint3d& end) const;

	/// Converts an absolute axis direction to a relative one
	void AbsoluteAxisDirToRelativeAxisDir(
		const int axisABS,
		const cadcam::mwPoint3d& startABS,
		const cadcam::mwPoint3d& endABS,
		int& axisREL,
		cadcam::mwPoint3d& startREL,
		cadcam::mwPoint3d& endREL,
		const bool isVector = false) const;
	/// Converts a relative axis direction to an absolute one
	void RelativeAxisDirToAbsoluteAxisDir(
		const int axisREL,
		const cadcam::mwPoint3d& startREL,
		const cadcam::mwPoint3d& endREL,
		int& axisABS,
		cadcam::mwPoint3d& startABS,
		cadcam::mwPoint3d& endABS,
		const bool isVector = false) const;

	/// Validates a coordinate system : directions are not zero, or repeated, also system must be on
	/// the right hand
	bool IsCoordinateSystemValid() const;

protected:
	cadcam::mwPoint3d m_origin;
	cadcam::mwPoint3d m_dirX;
	cadcam::mwPoint3d m_dirY;
	cadcam::mwPoint3d m_dirZ;
};

}  // namespace cadcam
#endif  //	MW_MWCOORDINATESYSTEM_HPP_
