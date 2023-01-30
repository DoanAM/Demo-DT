// (C) 2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVINITSTOCKGEOMETRIESFORWARD_HPP_
#define MW_MWVINITSTOCKGEOMETRIESFORWARD_HPP_

namespace cadcam
{
template <class T>
class mwTFractedMesh;
}  // namespace cadcam

namespace boost
{
namespace serialization
{
class access;
}
}  // namespace boost

namespace VerifierUtil
{
class mwvInitStockGeometry;
class mwvInitStockCube;
class mwvInitStockEmptyCube;
class mwvInitStockCylinder;
class mwvInitStockMesh;
class mwvInitStockRevolved;
class mwvInitStockOffsettedMesh;

class mwvInitStockGeometryVisitor;

}  // namespace VerifierUtil

#endif  // MW_MWVINITSTOCKGEOMETRIESFORWARD_HPP_
