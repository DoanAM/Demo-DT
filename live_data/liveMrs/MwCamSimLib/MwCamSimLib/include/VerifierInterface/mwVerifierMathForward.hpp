// (C) 2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVVERIFIERMATHFORWARD_HPP_
#define MW_MWVVERIFIERMATHFORWARD_HPP_

namespace MATH
{
template <typename>
struct Quaternion;

template <typename>
struct Frame;
}  // namespace MATH

namespace VerifierUtil
{
typedef MATH::Quaternion<float> Quaternion;
typedef MATH::Frame<float> Frame;
};  // namespace VerifierUtil

#endif  //	MW_MWVVERIFIERMATHFORWARD_HPP_
