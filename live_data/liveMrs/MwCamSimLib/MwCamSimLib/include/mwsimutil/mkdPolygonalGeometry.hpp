// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDPOLYGONALGEOMETRY_HPP_
#define MW_MKDPOLYGONALGEOMETRY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdGeometry.hpp"
#include "mwSTLTranslator.hpp"


namespace machsim
{
	class MW_SIMUTIL_API mkdPolygonalGeometry : public mkdGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdPolygonalGeometry>		Ptr;
		typedef cadcam::mwTMesh<float>							polyData;
		typedef misc::mwAutoPointer<polyData>					polyDataRef;
		typedef cadcam::mwTSTLTranslator<float>::HeaderData		StlHeader;
		typedef misc::mwAutoPointer<cadcam::mwTSTLTranslator<float>::HeaderData> StlHeaderPtr;

		struct UV {
			float uv[2];
		};
		typedef std::vector<UV>									texCoordsUV;
		typedef misc::mwAutoPointer<texCoordsUV>				texCoordsUVRef;

		

		/*! Parameterized constructor
			\param newID the name of this object.
			\param dataRef the mesh associated to this kinematic object.
			\param STLFileName the stl file associated with to the mesh.
			\param unit the unit of measure.
		 */
		mkdPolygonalGeometry(const id& newID,
			polyDataRef& dataRef,
			const misc::mwstring& STLFileName,
			measures::mwUnitsFactory::Units unit);


		/*! Parameterized constructor
			\param newID the name of this object.			
			\param STLFileName the stl file associated with to the mesh.
			\param unit the unit of measure.
		 */
        mkdPolygonalGeometry(const id& newID,
			const misc::mwstring& STLFileName,
			measures::mwUnitsFactory::Units unit);

		//! Destructor
		virtual ~mkdPolygonalGeometry(){};


		/*! Sets the mesh associated to this object.
			\param dataRef the new mesh associated to this object.
		 */
		virtual void SetPolygonalGeometry(const polyDataRef& dataRef);

		/*! Sets a new mesh associated to this object.
			\param dataRef the new mesh associated to this object.
			\param STLFileName the new stl file corresponding to the mesh.
		 */
		virtual void SetPolygonalGeometry(const polyDataRef& dataRef,
			const misc::mwstring& STLFileName );

		//! Returns the mesh associated to this object.
		virtual polyDataRef& GetPolygonalGeometry();

		//! Returns the mesh associated to this object.
		virtual const polyDataRef& GetPolygonalGeometry() const;

		/*! Sets a new set of mesh  texture coordinates vector associated to this object.
			\param coords the new mesh texture coordinates associated to this object.
		 */
		void SetTexCoords(const texCoordsUVRef& coords);

		//! Returns the mesh texture coordinates vector associated to this object.
		texCoordsUVRef& GetTexCoords();

		//! Returns the mesh texture coordinates vector associated to this object.
		const texCoordsUVRef& GetTexCoords() const;

		//! Returns the content of the stl header.
		StlHeaderPtr GetStlHeader() const;

		/*! Sets the content of the stl header.
			\param stlHeader the new attributes of the stl header.
		 */
		void SetStlHeader(StlHeaderPtr stlHeader);

		//! Returns the path to stl file.
		const misc::mwstring& GetSTLFileName() const;

		//! Visitor
		virtual void AcceptVisitor(mkdKOVisitor &visitor);

		//! Visitor
		virtual void AcceptVisitor(mkdKOConstVisitor &visitor) const;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 
		


	protected:

		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor) ;

		/*! Used by some derived classes also, sicne they have same pattern
		*/
		template <class T> misc::mwAutoPointer<T> CloneHelper(
			const bool justKinematicRelevantInfo)
		{
			mkdPolygonalGeometry::polyDataRef polygonalGeo;
			misc::mwstring stlFileName;
			if (!justKinematicRelevantInfo)
			{
				polygonalGeo = GetPolygonalGeometry().IsNotNull()? new cadcam::mwTMesh<float>(*GetPolygonalGeometry()):MW_NULL;
				stlFileName = GetSTLFileName();
			}
			misc::mwAutoPointer<T> tempOBJ = new T(GetID(),
				polygonalGeo,
				stlFileName,
				GetUnits());	

			tempOBJ->BasePolyGeoClone(*this, justKinematicRelevantInfo);

			return tempOBJ;
		}
		
		//! used on cloning to avoid code duplication in derived classes
		void BasePolyGeoClone(mkdPolygonalGeometry& source , const bool justKinematicRelevantInfo);

		virtual void SetPolygonalGeometry(const polyDataRef& dataRef) const;

	private:
#pragma warning(push)
#pragma warning(disable:4251)
		mutable polyDataRef			mPolygonalMesh;
		mutable misc::mwstring		mSTLFileName;
		StlHeaderPtr		m_stlHeader;
		texCoordsUVRef		m_texCoords;

		mutable polyDataRef	m_cncPolygonalMesh;
		mutable polyDataRef	m_cncConstPolygonalMesh;
#pragma warning(pop)
	};
};
#endif	//	MW_MKDPOLYGONALGEOMETRY_HPP_
