// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Forward declaration of all API types.

#ifndef MW_MWVMEASUREFORWARD_HPP_
#define MW_MWVMEASUREFORWARD_HPP_

namespace VerifierUtil
{
namespace Measure
{
struct ArcEdge;
struct Axis;
struct Corner;
struct Curvature;
struct DisplayedDimensions;
struct Distance;
struct DrawnMeasurement;
struct DrawStyle;
struct Edge;
struct Geometry;
struct LinearEdge;
struct MeshWithEdges;
struct MouseControlCallbacks;
struct SelectionOptions;
struct Surface;
struct Vertex;
struct WindowCallbacks;

class DepthsAndStencilIndices;
class Drawing;
class GuardedVerifier;
class MeasuredObjectInterface;
class Measurement;
class MouseControl;
class Projection;
class Tool;
class TouchControl;

typedef int MeasurePointIdx;
typedef unsigned MeasuredObjectID;
}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREFORWARD_HPP_
