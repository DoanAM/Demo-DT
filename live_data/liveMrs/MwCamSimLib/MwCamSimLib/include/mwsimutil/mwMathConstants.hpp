// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Application

//Until 2021.08 this file was part of the project mathdef. To resolve the circular dependency between
//misc and mathdef, it got moved to the project misc.

#ifndef MW_MWMATHCONSTANTS_HPP_
#define MW_MWMATHCONSTANTS_HPP_
#include "mwBasicTypes.hpp"
#include <cmath>
#include <cstdlib>

#ifdef UNDER_CE
	#include <types.h>
#else
	#include <sys/types.h>
#endif

#include <cfloat>
#include <limits>
#include <utility>
#include <cmath>



namespace mathdef
{
//!Math const PI
static const double MW_PI	= 3.1415926535897932384626433832795;

//!Math const 2*PI
const double MW_2PI			= 2.*MW_PI;

//!Math const PI/2_
const double MW_PI_2		= MW_PI/2.;

//!Math const 3PI/2_
const double MW_3PI_2		= 3.*MW_PI/2.;

//!Degrees to radians conversion factor
const double MW_D2R			= MW_PI/180.;

//!Radian to degree conversion factor
const double MW_R2D			= 180./MW_PI;

//!Smallest reliable difference between two double values.
/*!Lower than this threshold the values are considered equal.
*/
const double MW_MATH_TOL	= 1e-12;

//!Smallest reliable difference between two float values.
/*!Lower than this threshold the values are considered equal.
*/
const float MW_MATH_TOL_FLOAT = 1e-6f;

//!SQR of MW_MATH_TOL_FLOAT.
const float MW_MATH_TOL_FLOAT_SQR = MW_MATH_TOL_FLOAT*MW_MATH_TOL_FLOAT;

//!Smallest reliable difference between two long double values.
/*!Lower than this threshold the values are considered equal.
*/
const long double MW_MATH_TOL_LD	= 1e-16;

//!SQR of MW_MATH_TOL.
const double MW_MATH_TOL_SQR	= MW_MATH_TOL*MW_MATH_TOL;

//!SQRT of MW_MATH_TOL.
const double MW_MATH_TOL_SQRT	= 1e-6;

//!SQRT of MW_MATH_TOL_FLOAT.
const float MW_MATH_TOL_FLOAT_SQRT	= 1e-3f;

//!Max double
const double MW_MAX_DOUBLE	= 1e308;
//!Min double
const double MW_MIN_DOUBLE	= -MW_MAX_DOUBLE;

//!Max float
const float	 MW_MAX_FLOAT	= 3e38f;
//!Min float
const float  MW_MIN_FLOAT	= -MW_MAX_FLOAT;

//!Max short
const short  MW_MAX_SHORT	= 32767;
//!Min short
const short  MW_MIN_SHORT	= -32768;

//!Max unsigned short
const unsigned short
			 MW_MAX_USHORT	= 0xffff;

//!Max int
const int    MW_MAX_INT		= 2147483647;
//!Min int
const int    MW_MIN_INT		= (-2147483647 - 1);

//!Max unsigned int
const unsigned int
			 MW_MAX_UINT	= 0xffffffff;

//!Max long
const long   MW_MAX_LONG	= 2147483647;
//!Min long
const long   MW_MIN_LONG	= (-2147483647 - 1);

//!Max long long
const long long MW_MAX_LONG_LONG = 9223372036854775807;
//!Min long long
const long long MW_MIN_LONG_LONG = (-9223372036854775807 - 1);

//!Max unsigned long
const unsigned long MW_MAX_ULONG	= 0xffffffffUL;

const float MW_FLOAT_NAN=::std::numeric_limits<float>::quiet_NaN();

#ifdef _WIN64
const size_t MW_MAX_SIZET = 18446744073709551615;
#endif

//!Get tolerance for double precision
inline double mw_tol(double)
{
	return MW_MATH_TOL;
}

//!Get tolerance for float precision
inline float mw_tol(float)
{
	return MW_MATH_TOL_FLOAT;
}

//!Get sqrt tolerance for double precision
inline double mw_tol_sqrt(double)
{
	return MW_MATH_TOL_SQRT;
}

//!Get sqrt tolerance for float precision
inline float mw_tol_sqrt(float)
{
	return MW_MATH_TOL_FLOAT_SQRT;
}

//!Get sqrt tolerance for double precision
inline double mw_tol_sqr(double)
{
	return MW_MATH_TOL_SQR;
}

//!Get sqrt tolerance for float precision
inline float mw_tol_sqr(float)
{
	return MW_MATH_TOL_FLOAT_SQR;
}

//! Compare two values with relative tolerance using Knuth algorithm for values bigger then 2 and usual is_eq for lower values
/*! from https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/ :
	"If you are comparing against zero, then Knuth based comparisons are usually meaningless.
	If you are comparing against a non-zero number then Knut algorithm is what you want.
	If you are comparing two arbitrary numbers that could be zero or non-zero then you need the kitchen sink. Good luck and God speed."

	Well, KnuthCompare is the "kitchen sink" :). It is comparing the numbers and if they are greater then 2 it's using the Knuth algorithm,
	if not then it's using is_eq algorithm.	But because of this, it is very slow.
	If you are sure that your numbers are not around 0 then you should call  boost::test_tools::check_is_close (Knuth implementation of boost)
*/
bool KnuthCompare(
	const double& val1, const double& val2, const double tolerance = MW_MATH_TOL);


//! Compare two values with relative tolerance using Knuth algorithm for values bigger then 2 and usual is_eq for lower values
/*! from https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/ :
	"If you are comparing against zero, then Knuth based comparisons are usually meaningless.
	If you are comparing against a non-zero number then Knut algorithm is what you want.
	If you are comparing two arbitrary numbers that could be zero or non-zero then you need the kitchen sink. Good luck and God speed."

	Well, KnuthCompare is the "kitchen sink" :). It is comparing the numbers and if they are greater then 2 it's using the Knuth algorithm,
	if not then it's using is_eq algorithm.	But because of this, it is very slow.
	If you are sure that your numbers are not around 0 then you should call  boost::test_tools::check_is_close (Knuth implementation of boost)
*/
bool KnuthCompare(
	const float& val1, const float& val2, const float tolerance = MW_MATH_TOL_FLOAT);

//! strictly-less or KnuthCompare equal
inline bool Knuth_is_lte(
	const double& val1, const double val2, const double tolerance = MW_MATH_TOL)
{
	return (val1 < val2) || KnuthCompare(val1, val2, tolerance);
}

//! strictly-less or KnuthCompare equal
inline bool Knuth_is_lte(
	const float& val1, const float val2, const float tolerance = MW_MATH_TOL_FLOAT)
{
	return (val1 < val2) || KnuthCompare(val1, val2, tolerance);
}

//! strictly-less and not KnuthCompare equal
inline bool Knuth_is_lt(
	const double& val1, const double val2, const double tolerance = MW_MATH_TOL)
{
	return (val1 < val2) && !(KnuthCompare(val1, val2, tolerance));
}

//! strictly-less and not KnuthCompare equal
inline bool Knuth_is_lt(
	const float& val1, const float val2, const float tolerance = MW_MATH_TOL_FLOAT)
{
	return (val1 < val2) && !(KnuthCompare(val1, val2, tolerance));
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuthCompare(
	const double& val1, const double& val2, const double tolerance = MW_MATH_TOL)
{
	return std::fabs(val1 - val2) <= tolerance * std::fabs(val1);
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuthCompare(
	const float& val1, const float& val2, const float tolerance = MW_MATH_TOL_FLOAT)
{
	// http://fcmp.sourceforge.net/

	int exponent;
	float delta;
	float difference;

	frexp(std::fabs(val1) > std::fabs(val2) ? val1 : val2, &exponent);
	delta = ldexp(tolerance, exponent);

	difference = val1 - val2;

	if (difference > delta)
		return false; /* x1 > x2 */
	else if (difference < -delta)
		return false;  /* x1 < x2 */
	else /* -delta <= difference <= delta */
		return true;  /* x1 == x2 */
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuth_is_lte(
	const double& val1, const double val2, const double tolerance = MW_MATH_TOL)
{
	return val1 <= (val2 + tolerance * std::fabs(val1));
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuth_is_lte(
	const float& val1, const float val2, const float tolerance = MW_MATH_TOL_FLOAT)
{
	return val1 <= (val2 + tolerance * std::fabs(val1));
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuth_is_lt(
	const double& val1, const double val2, const double tolerance = MW_MATH_TOL)
{
	return val1 < (val2 - tolerance * std::fabs(val1));
}

//! deprecated use either KnuthCompare, either is_eq or boost::test_tools::check_is_close (see comments from KnuthCompare)
inline bool ExclusiveKnuth_is_lt(
	const float& val1, const float val2, const float tolerance = MW_MATH_TOL_FLOAT)
{
	return val1 < (val2 - tolerance * std::fabs(val1));
}

//! check if two values are exactly equal
inline bool is_eq(const size_t& val1, const size_t& val2)
{
	return val1 == val2;
}

//! check if a value is exactly zero
inline bool is_zero(const size_t& val)
{
	return val == 0;
}

//! check if two values are not exactly equal
inline bool is_neq(const size_t& val1, const size_t& val2)
{
	return val1 != val2;
}

//! check if a value is exactly not zero
inline bool is_not_zero(const size_t& val)
{
	return val != 0;
}

//! check equality with absolute two sided tolerance
inline bool is_eq(const double& val1, const double& val2)
{
	return std::fabs(val1 - val2) <= MW_MATH_TOL;
}

//! check if a value is zero with two sided tolerance
inline bool is_zero(const double& val)
{
	return std::fabs(val) <= MW_MATH_TOL;
}

//! check if value is exactly zero
inline bool is_zero(const long& val)
{
	return val == 0;
}

#ifdef _WIN64
//! check if two values are exactly equal
inline bool is_eq(const unsigned int& val1, const unsigned int& val2)
{
	return val1 == val2;
}
//! check if a value is exactly zero
inline bool is_zero(const unsigned int& val)
{
	return val == 0;
}
#else
#if defined (_WIN32)
//! check if two values are exactly equal
inline bool is_eq(const misc::uint64_t& val1, const misc::uint64_t& val2)
{
	return val1 == val2;
}
//! check if a value is exactly zero
inline bool is_zero(const misc::uint64_t& val)
{
	return val == 0;
}
#endif
#endif

//!is equal with two sided tolerance
/*!Are given float values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\returns <b>true</b> if absolute difference between both values <= tolerance,
<b>false</b> otherwise
*/
inline bool is_eq(const float& val1, const float& val2)
{
	return std::fabs(val1 - val2) <= MW_MATH_TOL_FLOAT;
}

//! check if a value is zero with two sided tolerance
inline bool is_zero(const float& val)
{
	return std::fabs(val) <= MW_MATH_TOL_FLOAT;
}

//!is equal ?
/*!Are given long double values equal?
\param val1 first value to compare
\param val2 second value to compare
\returns <b>true</b> if absolute difference between both values <= tolerance,
<b>false</b> otherwise
*/
inline bool is_eq(const long double& val1, const long double& val2)
{
	return std::fabs(val1 - val2) <= MW_MATH_TOL_LD;
}

//! check if a value is zero with two sided tolerance
inline bool is_zero(const long double& val)
{
	return std::fabs(val) <= MW_MATH_TOL_LD;
}

//!is not equal with two sided tolerance
/*!Are given double values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\returns <b>true</b> if absolute difference between both values > tolerance,
  <b>false</b> otherwise
*/
inline bool is_neq(const double& val1, const double& val2)
{
	return !is_eq(val1, val2);
}

//! check if a value is not zero with two sided tolerance
inline bool is_not_zero(const double& val)
{
	return !is_zero(val);
}

//!is not equal with two sided tolerance
/*!Are given float values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\returns <b>true</b> if absolute difference between both values > tolerance,
<b>false</b> otherwise
*/
inline bool is_neq(const float& val1, const float& val2)
{
	return !is_eq(val1, val2);
}

//! check if a value is not zero with two sided tolerance
inline bool is_not_zero(const float& val)
{
	return !is_zero(val);
}

//!is not exactly equal?
/*!Are given long double values equal?
\param val1 first value to compare
\param val2 second value to compare
\returns <b>true</b> if absolute difference between both values > tolerance,
<b>false</b> otherwise
*/
inline bool is_neq(const long double& val1, const long double& val2)
{
	return !is_eq(val1, val2);
}

//! check if a value is not exactly zero
inline bool is_not_zero(const long double& val)
{
	return !is_zero(val);
}

//! is given value greater than the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is greater than second value 
	 plus tolerance, and false otherwise
*/
inline bool is_gt(const double& toCompare, const double& source)
{
	return toCompare > (source + MW_MATH_TOL);
}

//! is given value greater than the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is greater than second value 
plus tolerance, and false otherwise
*/
inline bool is_gt(const float& toCompare, const float& source)
{
	return toCompare > (source + MW_MATH_TOL_FLOAT);
}
#if defined (_WIN32)
//! is given value greater than the reference value
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is greater than second value 
*/
inline bool is_gt(const misc::uint64_t& toCompare, const misc::uint64_t& source)
{
	return toCompare > source;
}
#endif

//! is given value greater or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is >= than second value 
	 minus tolerance, and false otherwise
*/
inline bool is_gte(const double& toCompare, const double& source)
{
	return toCompare >= (source - MW_MATH_TOL);
}

//! is given value greater or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is >= than second value 
minus tolerance, and false otherwise
*/
inline bool is_gte(const float& toCompare, const float& source)
{
	return toCompare >= (source - MW_MATH_TOL_FLOAT);
}

#if defined (_WIN32)
//! is given value greater or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is >= than second value 
*/
inline bool is_gte(const misc::uint64_t& toCompare, const misc::uint64_t& source)
{
	return toCompare >= source;
}
#endif

//! is given value less than the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is less than second value 
	 minus tolerance, and false otherwise
*/
inline bool is_lt(const double& toCompare, const double& source)
{
	return toCompare < (source - MW_MATH_TOL);
}

//! is given value less than the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is less than second value 
minus tolerance, and false otherwise
*/
inline bool is_lt(const float& toCompare, const float& source)
{
	return toCompare < (source - MW_MATH_TOL_FLOAT);
}
#if defined (_WIN32)
//! is given value less than the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is less than second value 
*/
inline bool is_lt(const misc::uint64_t& toCompare, const misc::uint64_t& source)
{
	return toCompare < source;
}
#endif

//! is given value less or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is <= than second value 
	 plus tolerance, and false otherwise
*/
inline bool is_lte(const double& toCompare, const double& source)
{
	return toCompare <= (source + MW_MATH_TOL);
}

//! is given value less or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is <= than second value 
plus tolerance, and false otherwise
*/
inline bool is_lte(const float& toCompare, const float& source)
{
	return toCompare <= (source + MW_MATH_TOL_FLOAT);
}
#if defined (_WIN32)
//! is given value less or equals to the reference value in current tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is <= than second value 
*/
inline bool is_lte(const misc::uint64_t& toCompare, const misc::uint64_t& source)
{
	return toCompare <= source;
}
#endif

//! is given value less than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is less than second value, and false otherwise
*/
inline bool is_lt(const unsigned int& toCompare, const unsigned int& source)
{
	return toCompare < source;
}

//! is given value less or equal than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is less or equal than second value, and false otherwise
*/
inline bool is_lte(const unsigned int& toCompare, const unsigned int& source)
{
	return toCompare <= source;
}

//! is given value greater than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is greater or equal than second value, and false otherwise
*/
inline bool is_gt(const unsigned int& toCompare, const unsigned int& source)
{
	return toCompare > source;
}

//! is given value greater or equal than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\returns true if first value is greater than second value, and false otherwise
*/
inline bool is_gte(const unsigned int& toCompare, const unsigned int& source)
{
	return toCompare >= source;
}

//! is given value greater than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is greater than second value 
	 plus tolerance, and false otherwise
*/
inline bool is_gt(const double& toCompare, const double& source, const double& prec)
{
	return toCompare > (source + prec);
}

//! is given value greater than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is greater than second value 
plus tolerance, and false otherwise
*/
inline bool is_gt(const float& toCompare, const float& source, const float& prec)
{
	return toCompare > (source + prec);
}

//! is given value greater or equals to the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is >= than second value 
	 minus tolerance, and false otherwise
*/
inline bool is_gte(const double& toCompare, const double& source, const double& prec)
{
	return toCompare >= (source - prec);
}

//! is given value greater or equals to the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is >= than second value 
minus tolerance, and false otherwise
*/
inline bool is_gte(const float& toCompare, const float& source, const float& prec)
{
	return toCompare >= (source - prec);
}

//! is given value less than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is less than second value 
	 minus tolerance, and false otherwise
*/
inline bool is_lt(const double& toCompare, const double& source, const double& prec)
{
	return toCompare < (source - prec);
}

//! is given value less than the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is less than second value 
minus tolerance, and false otherwise
*/
inline bool is_lt(const float& toCompare, const float& source, const float& prec)
{
	return toCompare < (source - prec);
}

//! is given value less or equals to the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is <= than second value 
	 plus tolerance, and false otherwise
*/
inline bool is_lte(const double& toCompare, const double& source, const double& prec)
{
	return toCompare <= (source + prec);
}

//! is given value less or equals to the reference value in given tolerance
/*!
	\param toCompare value to compare
	\param source reference value
	\param prec tolerance to compare with
	\returns true if first value is <= than second value 
plus tolerance, and false otherwise
*/
inline bool is_lte(const float& toCompare, const float& source, const float& prec)
{
	return toCompare <= (source + prec);
}

//!is equal ?
/*!Are given double values equal within tolerance
	\param val1 first value to compare
	\param val2 second value to compare
	\param prec precision
	\returns <b>true</b> if absolute difference between both values <= tolerance,
<b>false</b> otherwise
*/
inline bool is_eq(const double& val1, const double& val2, const double& prec)
{
	return std::fabs(val1 - val2) <= prec;
}

//! is value zero within specified tolerance
inline bool is_zero(const double& val, const double& prec)
{
	return std::fabs(val) <= prec;
}

//! is value zero within specified tolerance
inline bool is_zero(const long& val, const long& prec)
{
	return std::abs(val) <= prec;
}

//! is value zero within specified tolerance
inline bool is_zero(const int& val, const int& prec)
{
	return std::abs(val) <= prec;
}

//!is equal ?
/*!Are given float values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\param prec precision
	\returns <b>true</b> if absolute difference between both values <= tolerance,
<b>false</b> otherwise
*/
inline bool is_eq(const float& val1, const float& val2, const float& prec)
{
	return std::fabs(val1 - val2) <= prec;
}

//! is value zero within specified tolerance
inline bool is_zero(const float& val, const float& prec)
{
	return std::fabs(val) <= prec;
}

//!is not equal?
/*!Are given double values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\param prec precision
	\returns <b>true</b> if absolute difference between both values > tolerance,
  <b>false</b> otherwise
*/
inline bool is_neq(const double& val1, const double& val2, const double& prec)
{
	return !is_eq(val1, val2, prec);
}

//! is value different from zero within specified tolerance
inline bool is_not_zero(const double& val, const double& prec)
{
	return !is_zero(val, prec);
}

//!is not equal?
/*!Are given float values equal?
	\param val1 first value to compare
	\param val2 second value to compare
	\param prec precision
	\returns <b>true</b> if absolute difference between both values > tolerance,
<b>false</b> otherwise
*/
inline bool is_neq(const float& val1, const float& val2, const float& prec)
{
	return !is_eq(val1, val2, prec);
}

//! is value different from zero within specified tolerance
inline bool is_not_zero(const float& val, const float& prec)
{
	return !is_zero(val, prec);
}

//! is within range?
/*!	is value in the range [a, b]? Depending on isIncludeBegin and isIncludeEnd
		range may be (a, b), or [a, b), or (a, b], or [a, b].
*/
template<typename T>
bool is_within(
	const T value,
	const T from,
	const T to,
	const bool isIncludeBegin = true,
	const bool isIncludeEnd = true,
	const T tolerance = mw_tol(T()))
{
	if(!(isIncludeBegin ? is_lte(from, value, tolerance) : is_lt(from, value, tolerance)))
		return false;
	if(!(isIncludeEnd ? is_lte(value, to, tolerance) : is_lt(value, to, tolerance)))
		return false;
	return true;
}

inline bool is_within(
	const size_t value,
	const size_t from,
	const size_t to,
	const bool isIncludeBegin = true,
	const bool isIncludeEnd = true
) 
{
	if (!(isIncludeBegin ? from <= value : from < value))
		return false;
	if (!(isIncludeEnd ? value <= to : value < to))
		return false;
	return true;
}


//! is within range?
inline bool is_within(
	const double value,
	const double from,
	const double to,
	const bool isIncludeBegin = true,
	const bool isIncludeEnd = true,
	const double tolerance = mw_tol(double()))
{
	return is_within<double>(value, from, to, isIncludeBegin, isIncludeEnd, tolerance);
}
//! is within range?
inline bool is_within(
	const float value,
	const float from,
	const float to,
	const bool isIncludeBegin = true,
	const bool isIncludeEnd = true,
	const float tolerance = mw_tol(float()))
{
	return is_within<float>(value, from, to, isIncludeBegin, isIncludeEnd, tolerance);
}

//!is nan
/*!Is given double value nan?
\param val value to check
\returns <b>true</b> if val is nan,	<b>false</b> otherwise
*/
template <class T> bool is_nan(T val);

// round
/* Rounds the given value - vToRound - to
/  a certain number of decimals - vDigits
*/
inline double mw_round(const double vToRound, const int vDigits)
{
	static const double base = 10.0;
	double complete5, complete5IntPart;

	complete5 = vToRound * pow(base, static_cast<double>(vDigits + 1));

	if(vToRound < 0.0)
	{
		complete5 -= 5.0;
	}
	else
	{
		complete5 += 5.0;
	}

	complete5 /= base;
	modf(complete5, &complete5IntPart);

	return complete5IntPart / pow(base, static_cast<double>(vDigits));
}

//! swap values
/*!Exchange given values 
  \param val1 value to assign val2
  \param val2 value to assign val1
*/
template<class T> inline void mw_swap(T& val1, T& val2)
{
	T tmp = val1;
	val1 = val2;
	val2 = tmp;
}

//! get the sign of a value
/*! get the sign of a value
	\param rValue value to test
	\return -1 if value is negative, 1 if positive 
	and 0 if zero was passed
*/
template<class T>
T Sign(const T& rValue)
{
	if(rValue > 0)
		return 1;

	if(rValue < 0)
		return -1;

	return 0;
}

//! get the sign bit of a value
/*! get the sign bit of a value
\param rValue value to test
\return true if negative bit is set
*/
template<class T>
bool SignBit(const T& rValue);

/*! Get the non zero sign of a value. Useful for mathematical 
calculations when zero is irelevant or functionally identical 
to positive numbers
\param rValue value to test
\return -1 if value is negative, 1 otherwise
*/
template<class T>
T NonZeroSign(const T& rValue)
{
	if (rValue < 0)
		return -1;

	return 1;
}

//! Returns the absolute value
/*!
	\param rValue value to test
	\return the absolute value of rValue
*/
template<typename T> inline T Abs(const T& rValue)
{
	if(rValue > 0)
		return rValue;

	if(rValue < 0)
		return -rValue;

	return T(0);
}

//! Returns the absolute value
/*!
	\param rValue value to test
	\return the absolute value of rValue
*/
template<>
inline float Abs<float>(const float& rValue)
{
	return std::fabs(rValue);
}

//! Returns the absolute value
/*!
	\param rValue value to test
	\return the absolute value of rValue
*/
template<>
inline double Abs<double>(const double& rValue)
{
	return std::fabs(rValue);
}

//! base 2 logarithms rounded down to integer value
inline unsigned mw_log2(unsigned x)
{
	unsigned ans = 0;
	while(x >>= 1)
	{
		ans++;
	}
	return ans;
}

//! base 2 logarithm
inline float mw_log2(float x)
{
	const float LOG_2 = static_cast<float>(0.69314718055994530941723212145818);
	return static_cast<float>(log(x)/LOG_2);
}

//! base 2 logarithm
inline double mw_log2(double x)
{
	const double LOG_2 = 0.69314718055994530941723212145818;
	return log(x)/LOG_2;
}

inline double mw_log(double x)
{
	return log(x);
}

inline float mw_log(float x)
{
#ifndef UNDER_CE
	return logf(x);
#else
	return (float)mw_log((double)x);
#endif
}

//! Get minimum of two values
/*!
\param v1 first value to compare
\param v2 second value to compare
\returns smaller one
*/
template<class T> inline T mw_min(const T& v1, const T& v2)
{
	return v1 > v2 ? v2 : v1;
}

//! Get minimum of three values
/*!
\param v1 first value to compare
\param v2 second value to compare
\param v3 third value to compare
\returns smaller one
*/
template<class T> inline T mw_min(const T& v1, const T& v2, const T& v3)
{
	return mw_min(v1, mw_min(v2, v3));
}

//! Get minimum of four values
/*!
\param v1 first value to compare
\param v2 second value to compare
\param v3 third value to compare
\param v4 fourth value to compare
\returns smaller one
*/
template<class T> inline T mw_min(const T& v1, const T& v2, const T& v3, const T& v4)
{
	return mw_min(v1, mw_min(v2, v3, v4));
}

//! Get minimum of five values
/*!
\param v1 first value to compare
\param v2 second value to compare
\param v3 third value to compare
\param v4 fourth value to compare
\param v5 fifth value to compare
\returns smaller one
*/
template<class T> inline T mw_min(
	const T& v1, const T& v2, const T& v3, const T& v4, const T& v5)
{
	return mw_min(v1, mw_min(v2, v3, v4, v5));
}

//! Get minimum of six values
/*!
\param v1 first value to compare
\param v2 second value to compare
\param v3 third value to compare
\param v4 fourth value to compare
\param v5 fifth value to compare
\param v6 sixth value to compare
\returns smaller one
*/
template<class T> inline T mw_min(
	const T& v1, const T& v2, const T& v3, const T& v4, const T& v5, const T& v6)
{
	return mw_min(v1, mw_min(v2, v3, v4, v5, v6));
}

//!Get maximum
/*!Gets maximum for given parameters:
	\param v1 first value to compare
	\param v2 second value to compare
	\returns greater one
*/
template<class T> inline T mw_max(const T& v1, const T& v2)
{
	return v1 > v2 ? v1 : v2;
}

//! maximum of three values
template<class T> inline T mw_max(const T& v1, const T& v2, const T& v3)
{
	return mw_max(v1, mw_max(v2, v3));
}

//! maximum of four values
template<class T> inline T mw_max(const T& v1, const T& v2, const T& v3, const T& v4)
{
	return mw_max(v1, mw_max(v2, v3, v4));
}

//! maximum of five values
template<class T> inline T mw_max(
	const T& v1, const T& v2, const T& v3, const T& v4, const T& v5)
{
	return mw_max(v1, mw_max(v2, v3, v4, v5));
}

//! maximum of six values
template<class T> inline T mw_max(
	const T& v1, const T& v2, const T& v3, const T& v4, const T& v5, const T& v6)
{
	return mw_max(v1, mw_max(v2, v3, v4, v5, v6));
}


//!returns the floor of the value with specified tolerance
inline double mw_floor(const double& v1, const double& prec)
{
	return floor(v1 + prec);
}

//!returns the floor of the value with specified tolerance
inline float mw_floor(const float& v1, const float& prec)
{
	return static_cast<float>(floor(v1 + prec));
}

//!returns the floor of the value with tolerance
inline double mw_floor(const double& v1)
{
	return mw_floor(v1 , MW_MATH_TOL);
}

//!returns the floor of the value with tolerance
inline float mw_floor(const float& v1)
{
	return mw_floor(v1 , MW_MATH_TOL_FLOAT);
}

//!returns the ceil of the value with specified tolerance
inline double mw_ceil(const double& v1, const double& prec)
{
	double toReturn = ceil(v1 - prec);
	
	if (is_eq(toReturn,0.,prec))
		return 0.; //not to get -0

	return toReturn;
}

//!returns the ceil of the value with specified tolerance
inline float mw_ceil(const float& v1, const float& prec)
{
	float toReturn = static_cast<float>(ceil(v1 - prec));
	
	if (is_eq(toReturn,0.f,prec))
		return 0.; //not to get -0

	return toReturn;

}

//!returns the ceil of the value with tolerance
inline double mw_ceil(const double& v1)
{
	return mw_ceil(v1, MW_MATH_TOL);
}

//!returns the ceil of the value with tolerance
inline float mw_ceil(const float& v1)
{
	return mw_ceil(v1, MW_MATH_TOL_FLOAT);
}

//!returns truncated value with tolerance
inline double mw_truncate(
	const double v1,
	const double lastNonZeroDigit = MW_MATH_TOL,
	const double floorPrec = MW_MATH_TOL_SQRT)
{
	return mw_floor(v1/lastNonZeroDigit, floorPrec) * lastNonZeroDigit;
}

//!returns truncated value with tolerance
inline float mw_truncate(
	const float v1,
	const float lastNonZeroDigit = MW_MATH_TOL_FLOAT,
	const float floorPrec = MW_MATH_TOL_FLOAT_SQRT)
{
	return mw_floor(v1/lastNonZeroDigit, floorPrec) * lastNonZeroDigit;
}

#ifdef _WIN64
//!Get maxvalue
inline size_t mw_maxvalue(size_t)
{
	return MW_MAX_SIZET;
}
#endif

//!Get maxvalue
inline int mw_maxvalue(int)
{
	return MW_MAX_INT;
}

//!Get maxvalue
inline double mw_maxvalue(double)
{
	return MW_MAX_DOUBLE;
}

//!Get maxvalue
inline float mw_maxvalue(float)
{
	return MW_MAX_FLOAT;
}

//!Get maxvalue
inline short mw_maxvalue(short)
{
	return MW_MAX_SHORT;
}

//!Get maxvalue
inline long mw_maxvalue(long)
{
	return MW_MAX_LONG;
}

//!Get maxvalue
inline long long mw_maxvalue(long long)
{
	return MW_MAX_LONG_LONG;
}

//!Get maxvalue
inline unsigned short mw_maxvalue(unsigned short)
{
	return MW_MAX_USHORT;
}
//!Get maxvalue
inline unsigned int mw_maxvalue(unsigned int)
{
	return MW_MAX_UINT;
}
//!Get maxvalue
inline unsigned long mw_maxvalue(unsigned long)
{
	return MW_MAX_ULONG;
}
//!Get maxvalue

//!Get minvalue
inline int mw_minvalue(int)
{
	return MW_MIN_INT;
}

//!Get minvalue
inline unsigned int mw_minvalue(unsigned int)
{
	return 0;
}

//!Get minvalue
inline double mw_minvalue(double)
{
	return MW_MIN_DOUBLE;
}

//!Get minvalue
inline float mw_minvalue(float)
{
	return MW_MIN_FLOAT;
}

//!Get minvalue
inline short mw_minvalue(short)
{
	return MW_MIN_SHORT;
}

//!Get minvalue
inline long mw_minvalue(long)
{
	return MW_MIN_LONG;
}

//!Get minvalue
inline long long mw_minvalue(long long)
{
	return MW_MIN_LONG_LONG;
}

//! Get smallest positive value
inline double mwMinPositiveValue(double)
{
	return DBL_MIN;
}

//! Get smallest positive value
inline float mwMinPositiveValue(float)
{
	return FLT_MIN;
}

//! Is given double number de-normalized in T space
template<typename T> bool IsSubnormal(const double src)
{
	return src && std::fabs(src) <= mathdef::mwMinPositiveValue(T());
}
//!Round value with tolerance
template<class T>
inline T mw_round(const T val, const T tol)
{
	if(val == 0.0)
		return val;
	const T absVal(std::fabs(val));
	const T valSign(val/absVal);
	const T dst(fmod(absVal, tol));
	const T tol_2(tol/static_cast<T>(2.0));
	if(dst < tol_2)
		return valSign*(absVal - dst);
	return valSign*(absVal + (tol - dst));
}

//!Limit input value by given range
template<class T>
inline T mw_limit(const T value, const T low, const T high)
{
	if(value < low)
		return low;

	if(value > high)
		return high;

	return value;
}

//!Limit input value by given range
template<class T>
inline T mw_limit(const T value, const std::pair<T, T> range)
{
	if (value < range.first)
		return range.first;

	if (value > range.second)
		return range.second;

	return value;
}

//! pseudo random number in interval
template<class T>
inline T mw_rand(const T a, const T b)
{
	const T t = static_cast<T>(rand()) / (RAND_MAX - 1);
	const T v = a + (b - a) * t;
	return mw_limit(v, a, b);
}

//! Get src modulo base, works for negative values too
//! The modulo is defined as floored division as described by Donald Knuth (see
//! https://en.wikipedia.org/wiki/Modulo_operation#Variants_of_the_definition) Thus, the result has
//! the sign of @p base, e.g. mw_mod(-1, 10) -> 9
template<class T>
inline T mw_mod(const T src, const T base)
{
	if(base == 0.)
		return src;

	const T m = src - base * floor(src/base);

	// handle boundary cases resulted from floating-point cut off
	if(base > 0)  // modulo range: [0..base)
	{
		if(m >= base)  // mw_mod(-1e-16, 360.): m = 360.
			return 0;

		if(m < 0)
		{
			if(base+m == base)
				return 0;  // just in case...
			else
				return base + m;  // mw_mod(106.81415022205296, _TWO_PI): m= -1.421e-14
		}
	}
	else  // modulo range: (y..0]
	{
		if(m <= base)  // Mod(1e-16, -360.): m = -360.
			return 0;

		if(m > 0)
		{
			if(base + m == base)
				return 0;  // just in case...
			else
				return base+m;  // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
		}
	}
	return m;
}


//!Wrap input value into given range
template<class T>
inline T mw_wrap(const T value, const T low, const T high)
{
	// Make sure we don't introduce any errors if we are already in range
	if(value >= low && value <= high)
		return value;

	// Linear transformation so that value=low => 0 and value=high => 1
	T scaledAndShifted = (value - low) / (high - low);

	// Subtract periods to get value into range 0..1
	T floored = scaledAndShifted - floor(scaledAndShifted);

	// Transform back and invoke mw_limit to make extra sure we don't blow range
	return mw_limit<T>(floored * (high - low) + low, low, high);
}

//! Compute the square root, clamping negative values
/*!
\param value value to compute the square root of
\return the square root for positive input, 0 otherwise
*/
template<class T>
inline T mw_sqrt(T value)
{
	if(value < 0)
	{
		value = 0;
	}
	return sqrt(value);
}

inline double mwSqrtMinPositiveValue(double)
{	
	return 1.4916681462400413e-154;
}

//! Get smallest positive value
inline float mwSqrtMinPositiveValue(float)
{
	return 1.0842021725674598e-19F;
}

//! Compute squared value
template<class T>
inline T mw_square(const T val)
{
	return val * val;
}

//! Less than predicate with tolerance
template<class T>
class mwLess
{
public:
	explicit mwLess(const T tolerance = mw_tol(T()))
		: m_tolerance(tolerance)
	{
	}

	inline bool operator()(const T& a, const T& b) const
	{
		return is_lt(a, b, m_tolerance);
	}

private:
	T m_tolerance;
};
}  // namespace mathdef

template<typename T> inline T mw_abs(const T& rValue)
{
	// Warning!!! Use this function instead of abs from std library. In GCC implementation
	// of c++ standard library abs(float) and abs(double) are missing
	return mathdef::Abs<T>(rValue);
}
#endif	//	MW_MWMATHCONSTANTS_HPP_
