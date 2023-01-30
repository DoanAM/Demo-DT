// (C) 2003-2011 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTVECTOR3_HPP_
#define MW_MWTVECTOR3_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTVector.hpp"

namespace mathdef
{

template <class T>
class MW_5AXUTIL_API mwTVector3 : public mwTVector<3,T>
{
public:

	typedef T ValueType;
//#############################################################################		
    // construction
    mwTVector3 ();
    mwTVector3 (T fX, T fY, T fZ);
    mwTVector3 (const mwTVector3& rkV);
	mwTVector3 (const mwTVector<3,T>& rkV);
//#############################################################################		
	// member access
	inline void x( const T &newx )
	{
		this->mArray[0] = newx;
	}
	//!Set 2d point
	/*!Sets new y-coordinate of the 2d point.
		\param newy const y-coordinate of the 2d point
	*/
	inline void y( const T &newy )
	{
		this->mArray[1] = newy;
	}
		//!Get x-coordinate
	/*!Gets the x-coordinate of the 2d point as a reference.
		\returns constant reference to the x-coordinate
	*/
	inline void z( const T &newz )
	{
		this->mArray[2] = newz;
	}
		//!Get x-coordinate
	/*!Gets the x-coordinate of the 2d point as a reference.
		\returns constant reference to the x-coordinate
	*/
	inline const T &x() const
	{
		return this->mArray[0];
	}
		//!Get y-coordinate
	/*!Gets the y-coordinate of the 2d point as a reference.
		\returns constant reference to the y-coordinate
	*/
	inline const T &y() const
	{
		return this->mArray[1];
	}
		//!Get y-coordinate
	/*!Gets the y-coordinate of the 2d point as a reference.
		\returns constant reference to the y-coordinate
	*/
	inline const T &z() const
	{
		return this->mArray[2];
	}
//#############################################################################		
    // assignment
    mwTVector3& operator= (const mwTVector3& rkV);
	mwTVector3& operator= (const mwTVector<3,T>& rkV);
//#############################################################################		
    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    mwTVector3 Cross (const mwTVector3& rkV) const;
    mwTVector3 UnitCross (const mwTVector3& rkV) const;
//#############################################################################		
    // Gram-Schmidt orthonormalization.  Take linearly independent vectors
    // U, V, and W and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (mwTVector3& rkU, mwTVector3& rkV, mwTVector3& rkW);

    // Input W must be initialized to a nonzero vector, output is {U,V,W},
    // an orthonormal basis.  A hint is provided about whether or not W
    // is already unit length.
    static void GenerateOrthonormalBasis (mwTVector3& rkU, mwTVector3& rkV,
        mwTVector3& rkW, bool bUnitLengthW);
//#############################################################################		
    // special vectors
    static const mwTVector3 MW_ZERO;
    static const mwTVector3 MW_UNIT_X;
    static const mwTVector3 MW_UNIT_Y;
    static const mwTVector3 MW_UNIT_Z;
};

typedef mwTVector3<float> Vector3f;
typedef mwTVector3<double> Vector3d;

}
#endif	//	MW_MWTVECTOR3_HPP_
