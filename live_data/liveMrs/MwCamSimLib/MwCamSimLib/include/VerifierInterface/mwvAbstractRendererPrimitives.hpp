// (C) 2013-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVABSTRACTRENDERERPRIMITIVES_HPP_
#define MW_MWVABSTRACTRENDERERPRIMITIVES_HPP_
#include <mwDefines.hpp>
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
namespace mwvAbstractRendererPrimitives
{
/// Type of id used for render-groups, for example see mwvAbstractRenderer::DrawTriangles()
typedef int RenderGroupID;
/// Type used to represent 3d-points and -vectors for rendering.
typedef cadcam::mwTPoint3d<float> Vector3d;
/// Type used to identify a vertex.
typedef unsigned VertexID;
/// Invalid value of VertexId.
const VertexID INVALID_VERTEX_ID = 0xffffffffu;

/// Color used for rendering, defined by red, green, blue and alpha.
struct ColorRGBA
{
	float Red;
	float Green;
	float Blue;
	float Alpha;
	inline ColorRGBA() : Red(0), Green(0), Blue(0), Alpha(0) {}
	inline ColorRGBA(const ColorRGBA& c) : Red(c.Red), Green(c.Green), Blue(c.Blue), Alpha(c.Alpha)
	{
	}
	inline ColorRGBA(
		const float mwRed, const float mwGreen, const float mwBlue, const float mwAlpha)
		: Red(mwRed), Green(mwGreen), Blue(mwBlue), Alpha(mwAlpha)
	{
	}
	inline bool operator==(const ColorRGBA& other) const
	{
		return Red == other.Red && Green == other.Green && Blue == other.Blue &&
			Alpha == other.Alpha;
	}
	inline bool operator!=(const ColorRGBA& other) const { return !(*this == other); }
};

/// Vertex with 3d-position and color.
struct LineVertex
{
	ColorRGBA m_color;
	Vector3d m_position;
	static const unsigned COLOR_OFFSET = 0;
	static const unsigned VERTEX_OFFSET = sizeof(ColorRGBA);
	inline LineVertex(){};
	inline LineVertex(const Vector3d& position) : m_position(position){};
	inline LineVertex(const ColorRGBA& color, const Vector3d& position)
		: m_color(color), m_position(position){};
};

/// Vertex with 3d-position, color and normal.
struct TriangleVertex : public LineVertex
{
	Vector3d m_normal;
	static const unsigned NORMAL_OFFSET = sizeof(LineVertex);
	inline TriangleVertex(){};
	inline TriangleVertex(const Vector3d& position, const Vector3d& normal)
		: LineVertex(position), m_normal(normal){};
	inline TriangleVertex(const ColorRGBA& color, const Vector3d& position, const Vector3d& normal)
		: LineVertex(color, position), m_normal(normal){};
};

/// Represents triangle with vertex-normals, -colors and -ids.
struct RenderedTriangle
{
	Vector3d Vertices[3];
	Vector3d Normals[3];
	ColorRGBA Colors[3];
	/// Vertex ids within the group
	VertexID LocalID[3];
};

/// Represents line with vertex-colors.
struct RenderedLine
{
	Vector3d Vertices[2];
	ColorRGBA Colors[2];

#ifdef MW_USE_VS2008_COMPATIBILITY
	RenderedLine() {}
#else
	RenderedLine() = default;
#endif
	RenderedLine(const Vector3d& v0, const Vector3d& v1, const ColorRGBA& c0, const ColorRGBA& c1)
	{
		Vertices[0] = v0;
		Vertices[1] = v1;
		Colors[0] = c0;
		Colors[1] = c1;
	}
};

}  // namespace mwvAbstractRendererPrimitives
}  // namespace VerifierUtil
#endif  //	MW_MWVABSTRACTRENDERERPRIMITIVES_HPP_
