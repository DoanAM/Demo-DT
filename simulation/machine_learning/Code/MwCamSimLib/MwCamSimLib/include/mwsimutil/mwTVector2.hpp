// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTVECTOR2_HPP_
#define MW_MWTVECTOR2_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTVector.hpp"

namespace mathdef
{

	template <class T>
	class MW_5AXUTIL_API mwTVector2 : public mwTVector<2,T>
	{
	public:

		typedef T ValueType;
//#############################################################################
		// construction
		mwTVector2 ();
		mwTVector2 (T fX, T fY);
		mwTVector2 (const mwTVector2& rkV);
	    mwTVector2 (const mwTVector<2,T>& rkV);
//#############################################################################
		// member access
		void x( const T &newx );
		//!Set 2d point
		/*!Sets new y-coordinate of the 2d point.
			\param newy const y-coordinate of the 2d point
		*/
		void y( const T &newy );

		//!Get x-coordinate
		/*!Gets the x-coordinate of the 2d point as a reference.
			\returns constant reference to the x-coordinate
		*/
		const T &x() const;

		//!Get y-coordinate
		/*!Gets the y-coordinate of the 2d point as a reference.
			\returns constant reference to the y-coordinate
		*/
		const T &y() const;
//#############################################################################
		// assignment
		mwTVector2& operator= (const mwTVector2& rkV);
		mwTVector2& operator= (const mwTVector<2,T>& rkV);
//#############################################################################
		// returns (y,-x)
		mwTVector2 Perp () const;
//#############################################################################
		// returns (y,-x)/sqrt(x*x+y*y)
		mwTVector2 UnitPerp () const;
//#############################################################################
		// returns Cross((x,y,0),(V.x,V.y,0)) = x*V.y - y*V.x
		T Kross (const mwTVector2& rkV) const;
//#############################################################################
		// NOTE.  These exist to support template code that takes vectors of
		// dimensions 2 or 3.  In 2D, the input vector is ignored, but allows
		// the correct signature matching in the template code.
		mwTVector2 Cross (const mwTVector2& rkV) const;
		mwTVector2 UnitCross (const mwTVector2& rkV) const;
//#############################################################################
		// Gram-Schmidt orthonormalization.  Take linearly independent vectors U
		// and V and compute an orthonormal set (unit length, mutually
		// perpendicular).
		static void Orthonormalize (mwTVector2& rkU, mwTVector2& rkV);
//#############################################################################
		// Input V must be initialized to a nonzero vector, output is {U,V}, an
		// orthonormal basis.  A hint is provided about whether or not V is
		// already unit length.
		static void GenerateOrthonormalBasis (mwTVector2& rkU, mwTVector2& rkV,
			bool bUnitLengthV);
//#############################################################################
		// special vectors
		static const mwTVector2 MW_ZERO;
		static const mwTVector2 MW_UNIT_X;
		static const mwTVector2 MW_UNIT_Y;
	};

typedef mwTVector2<float> Vector2f;
typedef mwTVector2<double> Vector2d;

}
#endif	//	MW_MWTVECTOR2_HPP_
