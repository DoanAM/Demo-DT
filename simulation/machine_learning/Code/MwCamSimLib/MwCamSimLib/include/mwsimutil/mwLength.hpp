// (C) 2016-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWLENGTH_HPP_
#define MW_MWLENGTH_HPP_
#include "mwCadcamFwdDecl.hpp"


namespace cadcam
{
namespace mwLength
{
template <typename TObj>
const typename TObj::ValueType Get(const TObj& src);

template <typename TPolyline>
const typename TPolyline::ValueType Get2d(const TPolyline& src);

template <typename TObj>
const typename TObj::ValueType Get(const std::vector<TObj>& src)
{
	typename TObj::ValueType res = 0;
	for (size_t i = 0; i < src.size(); ++i)
	{
		res += Get(src[i]);
	}
	return res;
}

template <typename TObj>
const bool IsZero(const TObj& src, const typename TObj::ValueType tolerance);

template <typename TObj>
const bool IsZero(const TObj& src);


template <typename TObj>
const bool IsGreater(
	const TObj& src,
	const typename TObj::ValueType threshold,
	const typename TObj::ValueType tolerance);

template <typename TObj>
const bool IsGreater(const TObj& src, const typename TObj::ValueType threshold);

template <typename TObj>
const bool IsGreaterVec(
	const std::vector<TObj>& src,
	const typename TObj::ValueType threshold,
	const typename TObj::ValueType tolerance);

template <typename TObj>
const bool IsGreaterVec(const std::vector<TObj>& src, const typename TObj::ValueType threshold);

}  // namespace mwLength
}  // namespace cadcam
#endif  //	MW_MWLENGTH_HPP_
