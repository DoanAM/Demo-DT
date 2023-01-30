// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCONTROLPOINT_HPP_
#define MW_MWCONTROLPOINT_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
/// This struct represents a control point.
///
/// The control point is an array with 3 dimension components (x,y,z) and a weight
#pragma CACHING_INTERNAL_BEGIN
struct MW_5AXUTIL_API mwControlPoint
{
public:
	/// Sets control point to origin and the weight = 0
	inline mwControlPoint()
	{
		xyzw[X_] = 0.;
		xyzw[Y_] = 0.;
		xyzw[Z_] = 0.;
		xyzw[W_] = 0.;
	};


	/// Set control point
	///
	/// Sets the control point to the new position with a new weight.
	///	@param newx x-coordinate of the control point
	///	@param newy	y-coordinate of the control point
	///	@param newz z-coordinate of the control point
	///	@param neww weight of the control point
	inline mwControlPoint(
		const double& newx, const double& newy, const double& newz, const double& neww)
	{
		xyzw[X_] = newx;
		xyzw[Y_] = newy;
		xyzw[Z_] = newz;
		xyzw[W_] = neww;
	};


	/// Copy control point
	///
	/// Creates a exact copy of a given control point
	/// @param toCopy tool to create a copy of
	inline mwControlPoint(const mwControlPoint& toCopy)
	{
		xyzw[X_] = toCopy.xyzw[X_];
		xyzw[Y_] = toCopy.xyzw[Y_];
		xyzw[Z_] = toCopy.xyzw[Z_];
		xyzw[W_] = toCopy.xyzw[W_];
	};


	/// Set control point
	///
	/// Sets the control point to the new position with a new weight.
	///	@param p2d array of control point elements
	inline mwControlPoint(const double p2d[])
	{
		xyzw[X_] = p2d[X_];
		xyzw[Y_] = p2d[Y_];
		xyzw[Z_] = p2d[Z_];
		xyzw[W_] = p2d[W_];
	};


	/// Assigment operator
	///
	/// Assigns one control point object to another
	///  @param toCopy tool to copy the information from
	///  @returns current control point with copied information
	inline const mwControlPoint& operator=(const mwControlPoint& toCopy)
	{
		if (this != &toCopy)
		{
			xyzw[X_] = toCopy.xyzw[X_];
			xyzw[Y_] = toCopy.xyzw[Y_];
			xyzw[Z_] = toCopy.xyzw[Z_];
			xyzw[W_] = toCopy.xyzw[W_];
		}

		return *this;
	};


	/// Assigment operator
	///
	/// Assigns one control point an array
	///  @param toCopy tool to copy the information from an array with control point information
	///  @returns current control point with copied information
	inline const mwControlPoint& operator=(const double toCopy[])
	{
		xyzw[X_] = toCopy[X_];
		xyzw[Y_] = toCopy[Y_];
		xyzw[Z_] = toCopy[Z_];
		xyzw[W_] = toCopy[W_];

		return *this;
	};


	/// Equality operator
	///
	/// Are given tools equal?
	///  @param toCompare tool to compare the current tool with
	///  @returns <b>true</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	inline bool operator==(const mwControlPoint& toCompare) const
	{
		return xyzw[X_] == toCompare.xyzw[X_] && xyzw[Y_] == toCompare.xyzw[Y_] &&
			xyzw[Z_] == toCompare.xyzw[Z_] && xyzw[W_] == toCompare.xyzw[W_];
	}


	/// Inequality operator
	///
	/// Are given tools equal?
	///  @param toCompare tool to compare the current tool with
	///  @returns <b>false</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise
	inline bool operator!=(const mwControlPoint& toCompare) { return !(*this == toCompare); }


	/// Set control point
	///
	/// Sets new x-coordinate of the control point.
	///	@param newx x-coordinate of the control point
	inline void x(const double newx) { xyzw[X_] = newx; };


	/// Set control point
	///
	/// Sets new y-coordinate of the control point.
	///	@param newy y-coordinate of the control point
	inline void y(const double newy) { xyzw[Y_] = newy; };


	/// Set control point
	///
	/// Sets new z-coordinate of the control point.
	///	@param newz z-coordinate of the control point
	inline void z(const double newz) { xyzw[Z_] = newz; };


	/// Set control point
	///
	/// Sets new weight of the control point.
	///	@param neww new weight of the control point
	inline void w(const double neww) { xyzw[W_] = neww; };


	/// Get x-coordinate
	///
	/// Gets the x-coordinate of the control point as a reference.
	///	@returns constant reference to the x-coordinate
	inline const double& x() const { return xyzw[X_]; };


	/// Get y-coordinate
	///
	/// Gets the y-coordinate of the control point as a reference.
	///	@returns constant reference to the y-coordinate
	inline const double& y() const { return xyzw[Y_]; };


	/// Get z-coordinate
	///
	/// Gets the z-coordinate of the control point as a reference.
	///	@returns constant reference to the z-coordinate
	inline const double& z() const { return xyzw[Z_]; };


	/// Get weight
	///
	/// Gets the weight of the control point as a reference.
	///	@returns constant reference to the weight
	inline const double& w() const { return xyzw[W_]; };


	/// Get x-coordinate
	///
	/// Gets the x-coordinate of the control point as a reference.
	///	@returns reference to the x-coordinate
	inline double& x() { return xyzw[X_]; };


	/// Get y-coordinate
	///
	/// Gets the y-coordinate of the control point as a reference.
	///	@returns reference to the y-coordinate
	inline double& y() { return xyzw[Y_]; };


	/// Get z-coordinate
	///
	/// Gets the z-coordinate of the control point as a reference.
	///	@returns reference to the z-coordinate
	inline double& z() { return xyzw[Z_]; };


	/// Get weight
	///
	/// Gets the weight of the control point as a reference.
	///	@returns reference to the weight
	inline double& w() { return xyzw[W_]; };


	/// Get control point
	///
	/// Gets a pointer to the control point array.
	///	@returns pointer to the control point array
	inline double* GetArray() { return xyzw; }


	/// Get control point
	///
	/// Gets a pointer to the control point array.
	///	@returns constant pointer to the control point array
	inline const double* GetArray() const { return xyzw; }


	/// Indexer operator for const values
	///
	/// Returns, for a given index, a constant refernce to a control point component.
	///	@param idx position of the control point array
	///	@returns reference to a control point component.
	inline double& operator[](const short idx) { return idx < 4 ? xyzw[idx] : xyzw[0]; };

private:
	enum
	{
		X_ = 0,
		Y_ = 1,
		Z_ = 2,
		W_ = 3
	};

	double xyzw[4];
};
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MWCONTROLPOINT_HPP_
