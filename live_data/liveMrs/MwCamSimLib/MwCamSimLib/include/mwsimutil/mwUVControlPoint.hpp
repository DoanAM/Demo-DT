// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWUVCONTROLPOINT_HPP_
#define MW_MWUVCONTROLPOINT_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
/// This struct represents a UV control point.
///
/// The UV control point is an array with 3 dimension components (u,v,w)
#pragma CACHING_INTERNAL_BEGIN
struct MW_5AXUTIL_API mwUVControlPoint
{
public:
	/// Sets UV control point to origin (0,0,0).
	inline mwUVControlPoint()
	{
		uvw[U_] = 0.;
		uvw[V_] = 0.;
		uvw[W_] = 0.;
	};


	/// Set UV control point
	///
	/// Sets the UV control point to the new position.
	///	@param newu constant u-coordinate of the UV control point
	///	@param newv	constant v-coordinate of the UV control point
	///	@param neww constant w-coordinate of the UV control point
	inline mwUVControlPoint(const double& newu, const double& newv, const double& neww)
	{
		uvw[U_] = newu;
		uvw[V_] = newv;
		uvw[W_] = neww;
	};


	/// Copy UV control point
	///
	/// Creates a exact copy of a given UV control point
	/// @param toCopy tool to create a copy of
	inline mwUVControlPoint(const mwUVControlPoint& toCopy)
	{
		uvw[U_] = toCopy.uvw[U_];
		uvw[V_] = toCopy.uvw[V_];
		uvw[W_] = toCopy.uvw[W_];
	};


	/// Set UV control point
	///
	/// Sets the UV control point to the new position.
	///	@param p2d const array of the UV control point elements
	inline mwUVControlPoint(const double p2d[])
	{
		uvw[U_] = p2d[U_];
		uvw[V_] = p2d[V_];
		uvw[W_] = p2d[W_];
	};


	/// Assigment operator
	///
	/// Assigns one UV control point object to another
	/// @param toCopy tool to copy the information from
	/// @returns current UV control point with copied information
	inline const mwUVControlPoint& operator=(const mwUVControlPoint& toCopy)
	{
		if (this != &toCopy)
		{
			uvw[U_] = toCopy.uvw[U_];
			uvw[V_] = toCopy.uvw[V_];
			uvw[W_] = toCopy.uvw[W_];
		}

		return *this;
	};


	/// Assigment operator
	///
	/// Assigns one UV control point an array
	/// @param toCopy tool to copy the information from an array with UV control point information
	/// @returns current UV control point with copied information
	inline const mwUVControlPoint& operator=(const double toCopy[])
	{
		uvw[U_] = toCopy[U_];
		uvw[V_] = toCopy[V_];
		uvw[W_] = toCopy[W_];

		return *this;
	};


	/// Equality operator
	///
	/// Are given tools equal?
	///  @param toCompare tool to compare the current tool with
	///  @returns <b>true</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	inline bool operator==(const mwUVControlPoint& toCompare)
	{
		return uvw[U_] == toCompare.uvw[U_] && uvw[V_] == toCompare.uvw[V_] &&
			uvw[W_] == toCompare.uvw[W_];
	}


	/// Inequality operator
	///
	/// Are given tools equal?
	/// @param toCompare tool to compare the current tool with
	/// @returns <b>false</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise
	inline bool operator!=(const mwUVControlPoint& toCompare) { return !(*this == toCompare); }


	/// Set UV control point
	///
	/// Sets new u-coordinate of the UV control point.
	///	@param newu const u-coordinate of the UV control point
	inline void u(const double newu) { uvw[U_] = newu; };


	/// Set UV control point
	///
	/// Sets new v-coordinate of the UV control point.
	///	@param newv const v-coordinate of the UV control point
	inline void v(const double newv) { uvw[V_] = newv; };


	/// Set UV control point
	///
	/// Sets new v-coordinate of the UV control point.
	///	@param neww const v-coordinate of the UV control point
	inline void w(const double neww) { uvw[W_] = neww; };


	/// Get u-coordinate
	///
	/// Gets the u-coordinate of the UV control point as a reference.
	///	@returns constant reference to the u-coordinate
	inline const double& u() const { return uvw[U_]; };


	/// Get v-coordinate
	///
	/// Gets the v-coordinate of the UV control point as a reference.
	///	@returns constant reference to the v-coordinate
	inline const double& v() const { return uvw[V_]; };


	/// Get w-coordinate
	///
	/// Gets the w-coordinate of the UV control point as a reference.
	///	@returns constant reference to the w-coordinate
	inline const double& w() const { return uvw[W_]; };


	/// Get u-coordinate
	///
	/// Gets the u-coordinate of the UV control point as a reference.
	///	@returns reference to the u-coordinate
	inline double& u() { return uvw[U_]; };


	/// Get v-coordinate
	///
	/// Gets the v-coordinate of the UV control point as a reference.
	///	@returns reference to the v-coordinate
	inline double& v() { return uvw[V_]; };


	/// Get w-coordinate
	///
	/// Gets the w-coordinate of the UV control point as a reference.
	///	@returns reference to the w-coordinate
	inline double& w() { return uvw[W_]; };


	/// Get UV control point
	///
	/// Gets a pointer to the UV control point array.
	///	@returns pointer to the UV control point array
	inline double* GetArray() { return uvw; }


	/// Get UV control point
	///
	/// Gets a pointer to the UV control point array.
	///	@returns constant pointer to the UV control point array
	inline const double* GetArray() const { return uvw; }


	/// Indexer operator for const values
	///
	/// Returns, for a given index, a refernce to a UV control point component.
	///	@param idx position of the UV control point array
	///	@returns reference to a UV control point component.
	inline double& operator[](const short idx) { return idx < 3 ? uvw[idx] : uvw[0]; };

private:
	enum
	{
		U_ = 0,
		V_ = 1,
		W_ = 2
	};

	double uvw[3];
};
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MWUVCONTROLPOINT_HPP_
