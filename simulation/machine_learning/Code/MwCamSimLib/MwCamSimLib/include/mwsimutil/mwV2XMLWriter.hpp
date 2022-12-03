// (C) 2006-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWV2XMLWRITER_HPP_
#define MW_MWV2XMLWRITER_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwFileName.hpp"
#include "mkdKinematicObject.hpp"
#include "mwMachsimMachDef.hpp"
#include "mwValueValidator.hpp"
#include "mwTiXMLReadWriteHelper.hpp"
#include <map>


class TiXmlElement;
class mkdAxis;
class mwIMachineStream;


namespace machsim
{
	class MW_SIMUTIL_API mwV2XMLWriter : public misc::mwTiXMLReadWriteHelper
	{
	public:
		class mwDiscreteValueValidatorWriter: public misc::mwValueValidatorVisitor<double>
		{
		public:
			//! Parameterized constructor
			mwDiscreteValueValidatorWriter( TiXmlElement& element );

			//! Visitor
			virtual void Visit( const misc::mwValueValidator<double>& visitor ) const;

			//! Visitor
			virtual void Visit( const misc::mwListBasedDiscreteValueValidator<double>& visitor ) const;

			//! Visitor
			virtual void Visit( const misc::mwSteppingBasedDiscreteValueValidator<double>& visitor ) const;

		private:
			// avoid warning c4512
			mwDiscreteValueValidatorWriter& operator=(const mwDiscreteValueValidatorWriter&);

			TiXmlElement& m_element;
		};


		/*! Parameterized constructor
			\param pIMachineStream the stream to the machine definition file.
			\param machineDef the machine definition object.
			\param writeSTLs indicate whether to save or not the machine STL geometries.
		 */
		mwV2XMLWriter(mwIMachineStream* pIMachineStream, const mwMachsimMachDef& machineDef, const bool writeSTLs = true);

		//! Writes the machine definition to xml file
		void Write();


		//!SetNodeMatrixValue
		/*!
			\param whereToSet		the xml node where to find the property to modify
			\param whatToSet		the property to modify / establish
			\param withWhichMatrixValue	the new matrix value
		*/
		static void SetNodeMatrixValue(TiXmlElement& whereToSet,
								const misc::mwstring& whatToSet,
								const mkdKinematicObject::matrix& withWhichMatrixValue);


		/*!	Check if the given matrix is isometric.
			If not, warn the user and replace it with identity.
			\param id - the name of the matrix object in the machine tree
			\param transform - the 4x4 matrix to be checked for isometry
		*/
		static void CheckConformationChanges(const misc::mwstring& id, cadcam::mwHomogenousMatrix& transform);

	private:
		/*! Copies the xml section "machine_data" from machineDefinition into rootElement
			\param rootElement the destination of the nodes from "machine_data" section.
			\param machineDefinition the source of the "machine_data" section.
		 */
		void XMLSimpleTranslateMachineDataSection(TiXmlElement& rootElement, const mwMachsimMachDef& machineDefinition);


		/*! Copies the collision information from the internal machine definition
			into the given xml element.
			\param rootElement the destination of the collision pairs defined
			in the internal machine definition.
		 */
		void XMLSimpleTranslateCollisions(TiXmlElement& rootElement);


		/*! Copies the "magazine" information from the internal machine definition
			into the given xml element.
			\param rootElement - the destination of the "magazine" nodes defined
			in the internal machine definition.
		 */
		void XMLSimpleTranslateMagazine(TiXmlElement& rootElement);


		/*! Copies the "processor" information from the internal machine definition
			into the given xml element.
			\param rootElement - the destination of the "processor" nodes defined
			in the internal machine definition.
		 */
		void XMLSimpleTranslatePreprocessors( TiXmlElement& rootElement );

	private:
		// avoid warning c4512
		mwV2XMLWriter& operator=(const mwV2XMLWriter&);

		friend class XML2TreeFillVisitor;

		//! Internal reference to machine definition.
		const machsim::mwMachsimMachDef&			m_machineDefinition;

		//! Internal definition of the machine definition stream.
		mwIMachineStream*							m_pIMachineStream;

		//! Specifies whether the machine STL should be saved or not.
		const bool									m_writeSTLs;
	};



	//#############################################################################
	//! Helper class used internally to visit the elements of the kinematic tree.
	class XML2TreeFillVisitor : public mkdKOSimConstVisitor
	{
	public:
		typedef std::map<const machsim::mkdKinematicObject*, TiXmlElement*>  ObjMap;

	public:
		//#############################################################################
		//! Parameterized constructor
		XML2TreeFillVisitor(
			  TiXmlElement& rootElement,
			  const mwMachsimMachDef& machineDef,
			  misc::mwFileName fileName,
			  const bool writeSTLs = true
			  )
			: m_rootElement(rootElement),
			  m_machDefinition(machineDef),
			  m_XMLFileName(fileName),
			  m_writeSTLs(writeSTLs)
		{
		}

		//#############################################################################
		//visit functions
		virtual void Visit( const machsim::mkdKinematicObject &toVisit );
		virtual void Visit( const machsim::mkdPolygonalGeometry &toVisit );
		virtual void Visit( const machsim::mkdToolpathGeometry &toVisit );
		virtual void Visit( const machsim::mkdHeldTool &toVisit );
		virtual void Visit( const machsim::mkdCoordinateTransform &toVisit ) ;
		virtual void Visit( const machsim::mkdRevolvingSet &toVisit ) ;
		virtual void Visit( const machsim::mkdRotationalAxis &toVisit ) ;
		virtual void Visit( const machsim::mkdTranslationalAxis &toVisit ) ;
		virtual void Visit( const machsim::mkdWorkPiece &toVisit );
		virtual void Visit( const machsim::mkdFixture &toVisit );
		virtual void Visit( const mkdStockGeometry &toVisit );
		virtual void Visit( const mkdTailStock &toVisit );
		virtual void Visit( const mkdInitialStock &toVisit );
		virtual void Visit( const mkdWireEDMHead &toVisit );
		virtual void Visit( const mkdMountAdapter &toVisit );

		//#############################################################################
		void CommonXMLNode( TiXmlElement& domElem,
							const machsim::mkdKinematicObject& toVisit,
							const misc::mwstring& namestr);

		const machsim::mwMachsimMachDef&  GetMachineDefinition() const ;

		misc::mwFileName				m_XMLFileName;


	private:
		void CommonAxisNode(TiXmlElement& axisElem,
			const mkdAxis& axis,
			const misc::mwstring& objectType);

	private:
		// avoid warning c4512
		XML2TreeFillVisitor& operator=(const XML2TreeFillVisitor&);

		TiXmlElement&						m_rootElement;
		ObjMap								parentMap;
		const machsim::mwMachsimMachDef&	m_machDefinition ;
		const bool							m_writeSTLs;
	};


	//#############################################################################
	//! For internal use only.
	template<class TGeo>
	class Geo2XmlHelper
	{
	public:
		static void GeosCommonXMLNode(XML2TreeFillVisitor& parent,
			TiXmlElement& domElem,
			const TGeo& geo,
			const misc::mwstring& objectType,
			const bool writeSTLs = true
			);
	private:
	};
	//#############################################################################

}; //namespace
#endif	//	MW_MWV2XMLWRITER_HPP_
