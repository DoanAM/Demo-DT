// (C) 2018-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCOLOREDMESH_HPP_
#define MW_MWCOLOREDMESH_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"
#include "mwUnitsFactory.hpp"
#include "mwAutoPointer.hpp"
#include "mwException.hpp"

namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mwColoredMesh : public mwTMesh<T>
{
public:
	typedef misc::mwAutoPointer<mwColoredMesh<T> >	Ptr;
	typedef unsigned short							Color;
	typedef std::vector<Color>						ColorVec;
	typedef mwTMesh<T>								Mesh;

	mwColoredMesh(const measures::mwUnitsFactory::Units& units) : mwTMesh<T>(units)
	{
	}

	mwColoredMesh(const Mesh& mesh, const Color color = 0x00) :
		mwTMesh<T>(mesh), m_colorVec(mesh.GetNumberOfTriangles(), color)
	{
	}

	virtual bool IsTriangleAdditionalDataSupport() const MW_OVERRIDE
	{
		return true;
	}

	virtual void SetTriangleAdditionalData(const size_t triangleIndex, const Color data) MW_OVERRIDE
	{
		SetTriangleColor(triangleIndex, data);
	}

	virtual Color GetTriangleAdditionalData(const size_t triangleIndex) const MW_OVERRIDE
	{
		return GetTriangleColor(triangleIndex);
	}

	void SetTriangleColor(const size_t triangleIndex, const Color color)
	{
		if (m_colorVec.size() <= triangleIndex)
		{
			m_colorVec.resize(triangleIndex + 1, 0x00);
		}

		if (triangleIndex >= m_colorVec.size())
			MW_EXCEPTION("Incorrect triangle index");
		m_colorVec[triangleIndex] = color;
	}

	Color GetTriangleColor(const size_t triangleIndex) const
	{
		if (triangleIndex >= m_colorVec.size())
			MW_EXCEPTION("Incorrect triangle index");

		return m_colorVec[triangleIndex];
	}

	void AddMesh(const mwColoredMesh<T>& toAdd)
	{
		m_colorVec.insert(m_colorVec.end(), toAdd.m_colorVec.begin(), toAdd.m_colorVec.end());
		mwTMesh<T>::AddMesh(toAdd);
	}

	const ColorVec& GetColorsVector() const
	{
		return m_colorVec;
	}

private:
	ColorVec m_colorVec;
};

}		// namespace cadcam
#endif	// MW_MWCOLOREDMESH_HPP_
