// (C) 2004-2013 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYGONBOOLEAN_HPP_
#define MW_MW2DPOLYGONBOOLEAN_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


#pragma deprecated(mw2dPolygonBoolean)

/*
Deprecation reasons explained:

Instead of e.g.
	mw2dPolygonBoolean<double>::PerformBoolean(src1,src2,res, mw2dPolygonBoolean<double>::AND);
please use:
	res = PolygonBoolean::And<double>(src1, src2);
*/

namespace cadcam
{
#pragma warning(push)
#pragma warning(disable : 4995)

template <typename T>
class MW_5AXUTIL_API mw2dPolygonBoolean
{
public:
	typedef std::vector<mw2dMultipleClosedPolyLine<T>> PolyVec;
	typedef std::vector<mw2dPolyLine<T>> PolyLine2dVec;
	typedef std::vector<mw2dContour<T>> Contour2dVec;

	enum Operation
	{
		AND,
		DIF,
		XOR,
		OR,
	};

	static void PerformBoolean(
		const PolyVec& src1, const PolyVec& src2, PolyVec& res, const Operation operation);

	static void PerformBoolean(
		const PolyLine2dVec& src1,
		const PolyLine2dVec& src2,
		PolyLine2dVec& res,
		const Operation operation);

	static void PerformBoolean(
		const Contour2dVec& src1,
		const Contour2dVec& src2,
		Contour2dVec& res,
		const Operation operation,
		const T tolerance = static_cast<T>(0.01));

private:
	mw2dPolygonBoolean();
};

namespace PolygonBoolean
{
template <typename T>
class MW_5AXUTIL_API Types
{
public:
	typedef std::vector<mw2dMultipleClosedPolyLine<T>> PolyVec;
	typedef std::vector<mw2dPolyLine<T>> PolyLine2dVec;
	typedef std::vector<mw2dContour<T>> Contour2dVec;
};

template <typename T>
MW_5AXUTIL_API typename Types<T>::PolyVec And(
	const typename Types<T>::PolyVec& src1, const typename Types<T>::PolyVec& src2)
{
	typename Types<T>::PolyVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::AND);
	return res;
}

template <typename T>
MW_5AXUTIL_API typename Types<T>::PolyVec Dif(
	const typename Types<T>::PolyVec& src1, const typename Types<T>::PolyVec& src2)
{
	typename Types<T>::PolyVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::DIF);
	return res;
}

template <typename T>
MW_5AXUTIL_API typename Types<T>::PolyVec Xor(
	const typename Types<T>::PolyVec& src1, const typename Types<T>::PolyVec& src2)
{
	typename Types<T>::PolyVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::XOR);
	return res;
}

template <typename T>
MW_5AXUTIL_API typename Types<T>::PolyVec Or(
	const typename Types<T>::PolyVec& src1, const typename Types<T>::PolyVec& src2)
{
	typename Types<T>::PolyVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::OR);
	return res;
}

template <typename T>
typename Types<T>::Contour2dVec And(
	const typename Types<T>::Contour2dVec& src1,
	const typename Types<T>::Contour2dVec& src2,
	const T tolerance)
{
	typename Types<T>::Contour2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::AND, tolerance);
	return res;
}

template <typename T>
typename Types<T>::Contour2dVec Dif(
	const typename Types<T>::Contour2dVec& src1,
	const typename Types<T>::Contour2dVec& src2,
	const T tolerance)
{
	typename Types<T>::Contour2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::DIF, tolerance);
	return res;
}

template <typename T>
typename Types<T>::Contour2dVec Xor(
	const typename Types<T>::Contour2dVec& src1,
	const typename Types<T>::Contour2dVec& src2,
	const T tolerance)
{
	typename Types<T>::Contour2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::XOR, tolerance);
	return res;
}

template <typename T>
typename Types<T>::Contour2dVec Or(
	const typename Types<T>::Contour2dVec& src1,
	const typename Types<T>::Contour2dVec& src2,
	const T tolerance)
{
	typename Types<T>::Contour2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::OR, tolerance);
	return res;
}

template <typename T>
typename Types<T>::PolyLine2dVec And(
	const typename Types<T>::PolyLine2dVec& src1, const typename Types<T>::PolyLine2dVec& src2)
{
	typename Types<T>::PolyLine2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::AND);
	return res;
}

template <typename T>
typename Types<T>::PolyLine2dVec Dif(
	const typename Types<T>::PolyLine2dVec& src1, const typename Types<T>::PolyLine2dVec& src2)
{
	typename Types<T>::PolyLine2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::DIF);
	return res;
}

template <typename T>
typename Types<T>::PolyLine2dVec Xor(
	const typename Types<T>::PolyLine2dVec& src1, const typename Types<T>::PolyLine2dVec& src2)
{
	typename Types<T>::PolyLine2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::XOR);
	return res;
}

template <typename T>
typename Types<T>::PolyLine2dVec Or(
	const typename Types<T>::PolyLine2dVec& src1, const typename Types<T>::PolyLine2dVec& src2)
{
	typename Types<T>::PolyLine2dVec res;
	mw2dPolygonBoolean<T>::PerformBoolean(src1, src2, res, mw2dPolygonBoolean<T>::OR);
	return res;
}
}  // namespace PolygonBoolean
#pragma warning(pop)
}  // namespace cadcam
#endif  //	MW_MW2DPOLYGONBOOLEAN_HPP_
