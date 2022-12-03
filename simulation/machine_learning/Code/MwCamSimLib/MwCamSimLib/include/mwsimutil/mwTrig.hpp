// (C) 2006-2017 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTRIG_HPP_
#define MW_MWTRIG_HPP_
#include "mwMathConstants.hpp"
#include "mwDllImpExpDef.hpp"

#if defined(_WIN32) && !defined(UNDER_CE)
#include <eh.h>
#endif

#if defined(_WIN32)
#include <cfloat>
#endif

#include "mwDeprecated.hpp"

namespace mathdef
{
	MW_5AXUTIL_API double Sin(double radianAngle);
	MW_5AXUTIL_API double Cos(double radianAngle);
	MW_5AXUTIL_API void SinCos(double radianAngle, double& sinResult, double& cosResult);
	MW_5AXUTIL_API double Tan(double radianAngle);
	
	MW_5AXUTIL_API float Sin(float radianAngle);
	MW_5AXUTIL_API float Cos(float radianAngle);
	MW_5AXUTIL_API void SinCos(float radianAngle, float& sinResult, float& cosResult);
	MW_5AXUTIL_API float Tan(float radianAngle);

	MW_5AXUTIL_API void Sin4(const float radianAngle[4], float result[4]);
	MW_5AXUTIL_API void Cos4(const float radianAngle[4], float result[4]);
	MW_5AXUTIL_API void SinCos4(const float radianAngle[4], float sinResult[4], float cosResult[4]);

	MW_5AXUTIL_API float CosDegree(float degreeAngle);
	MW_5AXUTIL_API double CosDegree(double degreeAngle);
	MW_5AXUTIL_API float SinDegree(float degreeAngle);
	MW_5AXUTIL_API double SinDegree(double degreeAngle);
	
	template <typename T>
	MW_5AXUTIL_API T Asin(T value);

	template <typename T>
	MW_5AXUTIL_API T Acos(T value);

	// Note that this function introduces an error of about 0.001 degrees near the values of -1 and 1.
	// To prevent that, use Asin() above.
	template <typename T>
	MW_5AXUTIL_API T SnappingAsin(T value, T tolerance = static_cast<T>(1.e-10));

	// Note that this function introduces an error of about 0.001 degrees near the values of -1 and 1.
	// To prevent that, use Acos() above.
	template <typename T>
	MW_5AXUTIL_API T SnappingAcos(T value, T tolerance = static_cast<T>(1.e-10));

	//#############################################################################
	template < typename T >
	inline const T ExtATan2( const T& y, const T& x )
	{
		long double radValue;

		if ( mathdef::is_eq( (double)x, (double)0., mathdef::MW_MATH_TOL ) ) 
		{
			if ( y > 0 ) 
			{
				radValue = 90 * mathdef::MW_D2R;
			}
			else 
			{
				radValue = -90 * mathdef::MW_D2R;
			}
		}
		else if ( mathdef::is_eq( (double)y, (double)0., mathdef::MW_MATH_TOL ) )
		{
			if ( x > 0 ) 
			{
				radValue = 0;
			}
			else 
			{
				radValue = 180 * mathdef::MW_D2R;
			}
		}
		else
		{
			radValue = atan2( y, x );
		}

		return static_cast<T> ( radValue );
	}

	template < typename T >
	inline const T ExtATan2Positive( const T& y, const T& x )
	{
		long double radValue = ExtATan2(  y, x );
		if (radValue < 0) 
			radValue += mathdef::MW_2PI;
		return static_cast<T> ( radValue );
	}

	template <class T>
	MW_5AXUTIL_API T SafeAtan2(const T y, const T x);
	
	//
	// Everything below here is deprecated and will be removed soon!
	//
	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Sin()")
	inline const T sin(const T& radianAngle)
	{
		return (T)Sin((double)radianAngle);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Cos()")
	inline const T cos(const T& radianAngle)
	{
		return (T)Cos((double)radianAngle);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Sin()")
	inline const T mw_sin(const T radianAngle)
	{
		return Sin(radianAngle);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Cos()")
	inline const T mw_cos(const T radianAngle)
	{
		return Cos(radianAngle);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::SinCos()")
	inline void mw_sincos(const T radianAngle, T& sinResult, T& cosResult)
	{
		SinCos(radianAngle, sinResult, cosResult);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Tan()")
	inline const T mw_tan(const T& radianAngle)
	{
		T sinA = 0;
		T cosA = 0;
		SinCos(radianAngle, sinA, cosA);
		return sinA / cosA;
	}

	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Sin4()")
	inline void mw_sin4(const float radianAngle[4], float result[4])
	{
		Sin4(radianAngle, result);
	}

	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::Cos4()")
	inline void mw_cos4(const float radianAngle[4], float result[4])
	{
		Cos4(radianAngle, result);
	}

	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::SinCos4()")
	inline void mw_sincos4(const float radianAngle[4], float sinResult[4], float cosResult[4])
	{
		SinCos4(radianAngle, sinResult, cosResult);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::SnappingAsin()")
		inline const T asin(const T& value)
	{
		return SnappingAsin(value);
	}

	template <typename T>
	MW_DEPRECATED("Deprecated in 2016.04, please use mathdef::SnappingAcos()")
		inline const T acos(const T& value)
	{
		return SnappingAcos(value);
	}
}
#endif	//	MW_MWTRIG_HPP_
