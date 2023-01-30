// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSTLFILE_HPP_
#define MW_MWSTLFILE_HPP_
#include "mwMesh.hpp"
#include "mwParser.hpp"
#include "mwSTLParserException.hpp"
#include "mwStringOps.hpp"

#include <vector>


namespace cadcam
{
/// This class is used for handling an .stl ascii file
///
/// Stores data readed from file in a cadcam::mwMesh
template <typename T>
class MW_5AXUTIL_API mwSTLFile
{
public:
	typedef misc::mwAutoPointer<mwSTLFile<T>> Ptr;
	typedef cadcam::mwTMesh<T> mesh3d;
	typedef typename cadcam::mwTMesh<T>::TriangleVector triangleVector3d;
	typedef cadcam::mwTPoint3d<T> dPoint3D;
	typedef std::vector<dPoint3D> vecVertex;


	/// Default constructor
	mwSTLFile(): m_InFacet(false), m_InLoop(false), m_InSolid(false) {}

	/// Destructor
	~mwSTLFile() {}

	/// GetNumberOfTriangles
	///
	/// Returns number of triangles contained in mesh
	///	@return unsigned long number of triangles contained in the mesh
	unsigned long GetNumberOfTriangles() { return m_TriangleVector.GetNumberOfTriangles(); }

	const bool IsDefinitionComplete() const { return !m_InFacet && !m_InLoop && !m_InSolid; }

	/// StringTrimAndToUpper
	///
	/// Trims leading and trailing spaces from a string and converts it to uppercase
	///	@param sToTransform reference to string to be transformed
	static void StringTrimAndToUpper(misc::mwstring& sToTransform)
	{
		misc::mwstring sCharToRemove(_T(" \t"));
		misc::trim(sToTransform, sCharToRemove);
		misc::string_up(sToTransform);
	}


	/// GetTriangles
	///
	///	@return reference to  constructed vector of triangles stored in the class
	const triangleVector3d& GetTriangles() { return m_TriangleVector; }


	// Starting block keywords ....

	/// Keyword_Solid
	///
	/// Called when encounters 'solid' keyword during file parsing
	void Keyword_Solid()
	{
		if (!m_InSolid)
			m_InSolid = true;
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
	}

	/// Keyword_Facet
	///
	/// Called when encounters 'facet' keyword during file parsing
	///	@param crtPoint coordinates of current triangle vertex
	void Keyword_Facet(const dPoint3D& crtPoint)
	{
		if (!m_InFacet)
			m_InFacet = true;
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
		AddNormal(crtPoint);
	}

	/// Keyword_Outer
	///
	/// Called when encounters 'outer' keyword during file parsing
	void Keyword_Outer()
	{
		if (!m_InLoop)
			m_InLoop = true;
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
	}

	/// Keyword_Vertex
	///
	/// Called when encounters 'vertex' keyword during file parsing
	///	@param crtPoint coordinates of current triangle vertex
	void Keyword_Vertex(const dPoint3D& crtPoint)
	{
		if (m_InSolid && m_InFacet && m_InLoop)
			AddVertex(crtPoint);
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
	}


	// Ending block keywords

	/// Keyword_EndFacet
	///
	/// Called when encounters 'endfacet' keyword during file parsing
	void Keyword_EndFacet()
	{
		if (m_InFacet)
		{
			m_InFacet = false;
		}
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
	}

	/// Keyword_EndLoop
	///
	/// Called when encounters 'endloop' keyword during file parsing
	void Keyword_EndLoop()
	{
		if (m_InLoop)
			m_InLoop = false;
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
		AddTriangle();
	}

	/// Keyword_EndSolid
	///
	/// Called when encounters 'endsolid' keyword during file parsing
	void Keyword_EndSolid()
	{
		if (m_InSolid)
		{
			m_InSolid = false;
		}
		else
			throw mwSTLParserException(mwSTLParserException::INVALID_SYNTAX);
	}


private:
	/// AddVertex
	///
	/// Adds a mwTPoint3d to a vector that holds triangle vertices
	///	@param crtPoint reference to point to be added to vector
	inline void AddVertex(const dPoint3D& crtPoint)
	{
		if (m_Vertices.size() < 3)  // Adds current 3D point to vector
			m_Vertices.push_back(crtPoint);
	}

	/// AddNormal
	///
	/// Adds the normal vector to current triangle
	///	@param crtPoint reference to normal vector to be added
	inline void AddNormal(const dPoint3D& crtPoint) { m_Normal = crtPoint; }

	/// Addtriangle
	///
	/// Adds a triangle to member variable m_TriangleMesh of type
	///    cadcam::mwTMesh, that stores the triangles readed from .stl ascii file
	inline void AddTriangle()
	{
		if (m_Vertices.size() == 3)
		{
			if (!m_Normal.IsExactlyZero())  // specified
				m_TriangleVector.AddTriangle(m_Vertices[0], m_Vertices[1], m_Vertices[2], m_Normal);
			else  // unspecified
				m_TriangleVector.AddTriangle(m_Vertices[0], m_Vertices[1], m_Vertices[2]);
			m_Vertices.clear();  // clear vertices vector
		}
	}


	// Private members
	triangleVector3d
		m_TriangleVector;  ///< vector that holds triangles loaded from input STL ASCII file
	vecVertex m_Vertices;  ///< Holds the three 3D points that generates a triangle
	dPoint3D m_Normal;  ///< Normal vector
	bool m_InFacet;  ///< flag to test if FACET keyword has been readed from ascii stl file
	bool m_InLoop;  ///< flag to test if LOOP keyword has been readed from ascii stl file
	bool m_InSolid;  ///< flag to test if SOLID keyword has been readed from ascii stl file
};
}  // namespace cadcam
#endif  //	MW_MWSTLFILE_HPP_
