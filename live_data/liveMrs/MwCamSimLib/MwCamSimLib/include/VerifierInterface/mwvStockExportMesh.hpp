// (C) 2019-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSTOCKMESH_HPP_
#define MW_MWVSTOCKMESH_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvAbstractRendererPrimitives.hpp"

#include <iterator>
#include <mwDefines.hpp>
#include <mwException.hpp>
#include <mwMesh.hpp>
#include <mwTPoint3d.hpp>
#include <mwUnitsFactory.hpp>
#include <vector>

namespace VerifierUtil
{
class StockExportMeshFactory;

/// Color defined by red, green, blue and alpha
class Color4b
{
public:
	unsigned char r, g, b, a;

	explicit Color4b(unsigned rgba = 0)
		: r(rgba & 0xFF), g((rgba >> 8) & 0xFF), b((rgba >> 16) & 0xFF), a((rgba >> 24) & 0xFF)
	{
	}
	Color4b(
		const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		: r(r), g(g), b(b), a(a)
	{
	}

	mwvAbstractRendererPrimitives::ColorRGBA ToRendererRGBA() const
	{
		return mwvAbstractRendererPrimitives::ColorRGBA(
			r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	bool operator==(const Color4b& other) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}
	bool operator!=(const Color4b& other) const { return !(*this == other); }
};

/// Contains triangles describing the verifier's stock, as well as additional attributes at the
/// vertices.
class MW_VERIFIER_API StockExportMesh
{
public:
	struct TriangleView;

	explicit StockExportMesh(const measures::mwUnitsFactory::Units units)
		: m_mesh(units), m_hasVertexColors(false)
	{
	}
	explicit StockExportMesh(cadcam::mwfMesh mesh)
		:
#ifdef MW_USE_VS2008_COMPATIBILITY
		  m_mesh(mesh),
#else
		  m_mesh(std::move(mesh)),
#endif
		  m_hasVertexColors(false)
	{
	}

	/// Access the underlying cadcam::mwTMesh
	const cadcam::mwfMesh& GetMesh() const { return m_mesh; }

	/// Move this mesh into a cadcam::mwTMesh
	const cadcam::mwfMeshPtr ExtractMeshPtr()
	{
		cadcam::mwfMeshPtr mesh = new cadcam::mwfMesh(m_mesh.GetUnits());
		m_mesh.Swap(*mesh);
		m_vertexColor.clear();
		return mesh;
	}

	/// Get an iterable view of the contained triangles
	///
	/// This view allows you to efficiently iterate over all triangles:
	/// @code
	/// for (auto triangle : mesh.GetTriangleView()) {
	///    auto points[] = {triangle.GetPoint(0), triangle.GetPoint(1), triangle.GetPoint(2)};
	///    ...
	/// }
	/// @endcode
	TriangleView GetTriangleView() const;

	/// Returns true if this mesh contains vertex normal information
	bool HasVertexNormals() const { return m_mesh.GetNumberOfVertexNormals() > 0; }

	/// Returns true if this mesh contains vertex color information
	bool HasVertexColors() const { return m_hasVertexColors; }

	struct TriangleRef
	{
	public:
		/// Get triangle vertex position at vertexIdx between 0..2
		cadcam::mwTPoint3d<float> GetPoint(const int vertexIdx) const
		{
			ValidateVertexIdx(vertexIdx);
			return m_mesh->m_mesh.GetTriangleVertexData(m_idx, vertexIdx);
		}

		/// Get vertex normal at vertexIdx between 0..2
		cadcam::mwTPoint3d<float> GetVertexNormal(const int vertexIdx) const
		{
			ValidateVertexIdx(vertexIdx);
			return m_mesh->m_mesh.GetTriangleVertexNormal(m_idx, vertexIdx);
		}

		cadcam::mwTPoint3d<float> GetFaceNormal() const
		{
			ValidateFaceIdx();
			return m_mesh->m_mesh.GetNormal(m_idx);
		}

		/// Get vertex color at vertexIdx between 0..2.
		/// The stock mesh is colored according to the color scheme selected by
		/// mwMachSimVerifier::SetDrawMode(...). Note: this is only available if requested via
		/// ExportStockMeshOptions. Availability can be checked via
		/// StockExportMesh::HasVertexNormals().
		Color4b GetVertexColor(int vertexIdx) const
		{
			if (!m_mesh->HasVertexColors())
				throw misc::mwException(0, "Vertex color is not available.");
			ValidateVertexIdx(vertexIdx);
			return m_mesh->m_vertexColor[m_idx * 3 + vertexIdx];
		}

	private:
		TriangleRef(const StockExportMesh& mesh, const size_t idx) : m_mesh(&mesh), m_idx(idx) {}

		void ValidateVertexIdx(const int vertexIdx) const
		{
			if (vertexIdx < 0 || vertexIdx > 2)
				throw misc::mwIdxRangeException<size_t>(2, vertexIdx);
			ValidateFaceIdx();
		}

		void ValidateFaceIdx() const
		{
			if (m_idx >= m_mesh->m_mesh.GetNumberOfTriangles())
				throw misc::mwIdxRangeException<size_t>(
					m_mesh->m_mesh.GetNumberOfTriangles() - 1, m_idx);
		}

		friend struct TriangleView;
		const StockExportMesh* m_mesh;
		size_t m_idx;
	};

private:
	friend class StockExportMeshFactory;
	cadcam::mwfMesh m_mesh;
	std::vector<Color4b> m_vertexColor;
	bool m_hasVertexColors;
};

/// @sa GetTriangleView
struct StockExportMesh::TriangleView
{
public:
	struct const_iterator;

	TriangleView(const StockExportMesh& mesh) : m_stockMesh(&mesh) {}
	const_iterator begin() const;
	const_iterator end() const;
	std::size_t size() const;

private:
	const StockExportMesh* m_stockMesh;
};

struct StockExportMesh::TriangleView::const_iterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef TriangleRef value_type;
	typedef int difference_type;
	typedef const TriangleRef* pointer;
	typedef const TriangleRef& reference;

	const_iterator(const StockExportMesh& mesh, const size_t idx) : m_curTriangleRef(mesh, idx) {}
	const_iterator operator++()
	{
		const_iterator i = *this;
		m_curTriangleRef.m_idx++;
		return i;
	}
	const_iterator operator++(int)
	{
		m_curTriangleRef.m_idx++;
		return *this;
	}
	const_iterator operator--()
	{
		const_iterator i = *this;
		m_curTriangleRef.m_idx--;
		return i;
	}
	const_iterator operator--(int)
	{
		m_curTriangleRef.m_idx--;
		return *this;
	}
	const_iterator& operator+=(const difference_type offset)
	{
		m_curTriangleRef.m_idx += offset;
		return *this;
	}
	const_iterator operator+(difference_type offset) const
	{
		const_iterator tmp = *this;
		return tmp += offset;
	}
	const_iterator& operator-=(difference_type offset) { return (*this += -offset); }
	const_iterator operator-(difference_type offset) const
	{
		const_iterator tmp = *this;
		return tmp -= offset;
	}

	difference_type operator-(const const_iterator& other) const
	{
		return difference_type(m_curTriangleRef.m_idx - other.m_curTriangleRef.m_idx);
	}

	reference operator*() const { return m_curTriangleRef; }
	pointer operator->() const { return &m_curTriangleRef; }
	bool operator==(const const_iterator& rhs) const
	{
		return m_curTriangleRef.m_idx == rhs.m_curTriangleRef.m_idx;
	}
	bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

private:
	TriangleRef m_curTriangleRef;
};

inline StockExportMesh::TriangleView::const_iterator StockExportMesh::TriangleView::begin() const
{
	return const_iterator(*m_stockMesh, 0);
}

inline StockExportMesh::TriangleView::const_iterator StockExportMesh::TriangleView::end() const
{
	return const_iterator(*m_stockMesh, m_stockMesh->m_mesh.GetNumberOfTriangles());
}

inline std::size_t StockExportMesh::TriangleView::size() const
{
	return end() - begin();
}

inline StockExportMesh::TriangleView StockExportMesh::GetTriangleView() const
{
	return TriangleView(*this);
}
}  // namespace VerifierUtil

#endif
