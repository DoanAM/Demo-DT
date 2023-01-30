// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPOINTUV_HPP_
#define MW_MWPOINTUV_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"

#include <cmath>


namespace cadcam
{
/// This struct represents a UV point.
///
/// The UV point is an array with 2 dimension components (u,v).
#pragma CACHING_INTERNAL_BEGIN
struct MW_5AXUTIL_API mwPointUV
{
public:
	/// Sets UV point to origin.
	inline mwPointUV()
	{
		uv[U_] = 0.;
		uv[V_] = 0.;
	};


	/// Set UV point
	///
	/// Sets the UV point to the new position.
	///	@param newu constant u-coordinate of the UV point
	///	@param newv	constant v-coordinate of the UV point
	inline mwPointUV(const double& newu, const double& newv)
	{
		uv[U_] = newu;
		uv[V_] = newv;
	};


	/// Copy UV point
	///
	/// Creates a exact copy of a given UV point
	/// @param toCopy tool to create a copy of
	inline mwPointUV(const mwPointUV& toCopy)
	{
		uv[U_] = toCopy.uv[U_];
		uv[V_] = toCopy.uv[V_];
	};


	/// Set UV point
	///
	/// Sets the UV point to the new position.
	///	@param p2d const array of the UV point elements
	inline mwPointUV(const double p2d[])
	{
		uv[U_] = p2d[U_];
		uv[V_] = p2d[V_];
	};


	/// Assigment operator
	///
	/// Assigns one UV point object to another
	///  @param toCopy tool to copy the information from
	///  @returns current UV point with copied information
	inline const mwPointUV& operator=(const mwPointUV& toCopy)
	{
		if (this != &toCopy)
		{
			uv[U_] = toCopy.uv[U_];
			uv[V_] = toCopy.uv[V_];
		}

		return *this;
	};


	/// Assigment operator
	///
	/// Assigns one UV point an array
	///  @param toCopy tool to copy the information from an array with UV point information
	///  @returns current UV point with copied information
	inline const mwPointUV& operator=(const double toCopy[])
	{
		uv[U_] = toCopy[U_];
		uv[V_] = toCopy[V_];

		return *this;
	};


	/// Equality operator
	///
	/// Are given tools equal?
	///  @param toCompare tool to compare the current tool with
	///  @returns <b>true</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	inline bool operator==(const mwPointUV& toCompare)
	{
		return uv[U_] == toCompare.uv[U_] && uv[V_] == toCompare.uv[V_];
	}


	/// Inequality operator
	///
	/// Are given tools equal?
	///  @param toCompare tool to compare the current tool with
	///  @returns <b>false</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise
	inline bool operator!=(const mwPointUV& toCompare) { return !(*this == toCompare); }


	/// Set UV point
	///
	/// Sets new u-coordinate of the UV point.
	///	@param newu const u-coordinate of the UV point
	inline void u(const double newu) { uv[U_] = newu; };


	/// Set UV point
	///
	/// Sets new v-coordinate of the UV point.
	///	@param newv const v-coordinate of the UV point
	inline void v(const double newv) { uv[V_] = newv; };


	/// Get u-coordinate
	///
	/// Gets the u-coordinate of the UV point as a reference.
	///	@returns constant reference to the u-coordinate
	inline const double& u() const { return uv[U_]; };


	/// Get v-coordinate
	///
	/// Gets the v-coordinate of the UV point as a reference.
	///	@returns constant reference to the v-coordinate
	inline const double& v() const { return uv[V_]; };


	/// Get UV point
	///
	/// Gets a pointer to the UV point array.
	///	@returns pointer to the UV point array
	inline double* GetArray() { return uv; }


	/// Get UV point
	///
	/// Gets a pointer to the UV point array.
	///	@returns constant pointer to the UV point array
	inline const double* GetArray() const { return uv; }


	/// Indexer operator for const values
	///
	/// Returns, for a given index, a refernce to a UV point component.
	///	@param idx position of the UV point array
	///	@returns reference to a UV point component.
	inline double& operator[](const short idx) { return idx < 2 ? uv[idx] : uv[0]; }


	/// += operator
	///
	/// Add each component of a UV point to another
	///	@param toAdd const reference of a UV point
	inline void operator+=(const mwPointUV& toAdd)
	{
		uv[U_] += toAdd.uv[U_];
		uv[V_] += toAdd.uv[V_];
	}


	/// -= operator
	///
	/// Subtract each component of a UV point with another
	///	@param toAdd const reference of a UV point
	inline void operator-=(const mwPointUV& toAdd)
	{
		uv[U_] -= toAdd.uv[U_];
		uv[V_] -= toAdd.uv[V_];
	}


	/// *= operator
	///
	/// Mutiplicate each UV component with a factor
	///	@param factor const reference to a factor
	inline void operator*=(const double& factor)
	{
		uv[U_] *= factor;
		uv[V_] *= factor;
	}


	//// = operator
	///
	/// Divide each UV component by a factor
	///	@param factor const reference to a factor
	inline void operator/=(const double& factor)
	{
		uv[U_] /= factor;
		uv[V_] /= factor;
	}


	/// ~ operator
	///
	/// Returns length of the vektor represented by the UV point
	///	@returns constant length of the vektor represented by the UV point.
	inline const double operator~() const { return sqrt(uv[U_] * uv[U_] + uv[V_] * uv[V_]); }

private:
	enum
	{
		U_ = 0,
		V_ = 1
	};

	double uv[2];
};
#pragma CACHING_INTERNAL_END


/// + operator
///
/// Add each component of a UV point to another
///	@param first const reference of a UV point
///	@param second const reference of a UV point
///	@returns added const UV point
inline const mwPointUV operator+(const mwPointUV& first, const mwPointUV& second)
{
	return mwPointUV(first.u() + second.u(), first.v() + second.v());
}


/// - operator
///
/// Subtract each UV point component from another
///	@param first const reference of a UV point
///	@param second const reference of a UV point
///	@returns subtracted const UV point
inline const mwPointUV operator-(const mwPointUV& first, const mwPointUV& second)
{
	return mwPointUV(first.u() - second.u(), first.v() - second.v());
}


/// * operator
///
/// Multiplicate each UV component with a factor.
///	@param pt const reference to a UV point
///	@param factor const reference to a factor to multiplicate with
///	@returns new UV point object
inline const mwPointUV operator*(const mwPointUV& pt, const double& factor)
{
	return mwPointUV(pt.u() * factor, pt.v() * factor);
}


/// * operator
///
/// Multiplicate each UV component with a factor.
///	@param factor const reference to a factor to multiplicate with
///	@param pt const reference to a UV point
///	@returns new UV point object
inline const mwPointUV operator*(const double& factor, const mwPointUV& pt)
{
	return mwPointUV(pt.u() * factor, pt.v() * factor);
}


//// operator
///
/// Divide each UV component by a factor.
///	@param pt const reference to a UV point
///	@param factor const reference to a factor to divide with
///	@returns new UV point object
inline const mwPointUV operator/(const mwPointUV& pt, const double& factor)
{
	return mwPointUV(pt.u() / factor, pt.v() / factor);
}
}  // namespace cadcam
#endif  //	MW_MWPOINTUV_HPP_
