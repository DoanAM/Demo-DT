// (C) 2006-2020 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWV2XMLREADER_HPP_
#define MW_MWV2XMLREADER_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwFileName.hpp"
#include "mwTiXMLReadWriteHelper.hpp"
#include "mwSTLTranslator.hpp"
#include "mwMachsimMachDef.hpp"		


class TiXmlNode;
class TiXmlElement;
class mwIMachineStream;
class mwIProgressDialogHandler;
class TiXmlDocument;

namespace machsim
{
	class MW_SIMUTIL_API mwV2XMLReader : public misc::mwTiXMLReadWriteHelper
	{
	public:
		typedef misc::mwAutoPointer<mwV2XMLReader>					Ptr;
		typedef misc::mwAutoPointer<mwMachsimMachDef>               MachDef ;
		typedef measures::mwUnitsFactory::Units						Units;
		typedef misc::mwAutoPointer< Units >						UnitsPtr;



		/*! Parameterized constructor
			\param pIMachineStream machine definition stream
			\param progress a progress handler. Can be zero when it is not needed.
		 */
		mwV2XMLReader( mwIMachineStream* pIMachineStream, mwIProgressDialogHandler* progress ) ;

		/*! Parameterized constructor
			\param pIMachineStream machine definition stream
			\param progress a progress handler. Can be zero when it is not needed.
			\param tiXmldoc xml document containing the kinematic definition.
		 */
		mwV2XMLReader( mwIMachineStream* pIMachineStream, mwIProgressDialogHandler* progress, const TiXmlDocument& tiXmldoc ) ;

		/*! Parameterized constructor
			\param pIMachineStream machine definition stream
			\param progress a progress handler. Can be zero when it is not needed.
		 */
		mwV2XMLReader(const misc::mwstring& xmlPath, mwIProgressDialogHandler* progress ) ;

		//! Destructor
		~mwV2XMLReader();


		/*! Creates the machine definition by reading the stream from the disk.
			\param defaultUnitsPtr measure unit for the machine geometries.
			\param loadSTL enables or disables loading the stl files.
			\param notifications enables a special behavior of the kinematic tree.
			\param useStlColor enables reading the padding bytes used for color
			from those geometries saved as binary stl.
			\param ignoreCollisionGroups omits loading the collision groups into
			the simulator. As a result no machine collision checking is later performed.
		 */
		virtual misc::mwAutoPointer<mwMachsimMachDef> CreateMachineDefinition(
			const UnitsPtr& defaultUnitsPtr = NULL ,
			const bool loadSTL = true,
			const bool notifications=false,
			const bool useStlColor=false,
			const bool ignoreCollisionGroups= false,
			const misc::mwstring& machineGeometriesPath = _T("") ,
			const bool doNotVerifyCollisionCheckingPairs = false,
			const bool autoCompleteMissingComponents = true
			) ;

	protected:
		//! Additional mesh customization (e.g. color)
		struct MeshLibraryItem
		{
			mkdPolygonalGeometry::polyDataRef	m_mesh;
			mkdPolygonalGeometry::StlHeaderPtr	m_stlHeader;
		};

		//! Loads a mesh from stl file.
		virtual void LoadSTL(mwIMachineStream* pIMachineStream,
			misc::mwstring nodeName,
			misc::mwstring nodeId,
			misc::mwstring file,
			const MachDef& machineDefinition,
			MeshLibraryItem& mesh);


		//! Verifies if a file exists and corrects with fallback to the machine root
		virtual bool CheckAndFixFilePath(misc::mwFileName &fileName);

		//! Deprecated. Please use CheckAndFixFilePath
		virtual bool GeometryFileExists(misc::mwstring fileName);

		//! Generates the canonical path for the given file.
		virtual void FixForRelativePath( misc::mwFileName &fileName );

		//! Read properties from stlHeader and save appearance
		virtual void UpdateAppearance(
			mkdPolygonalGeometry& geometry,
			mkdGeometry::appearance& app,
			mkdPolygonalGeometry::StlHeaderPtr stlHeader,
			bool useStlColor);

		//xml file path reference;
		mwIMachineStream* m_pIMachineStream;

		// handles information about loading progress
		mwIProgressDialogHandler* m_progress;

	private:

		//!AddAxis
		/*!
			\param	axisNode		xml node, contains information about an axis
			\param	parentAxis		parent of the axis passed through the first param
		*/
		void AddAxis(TiXmlNode* axisNode, mwMachsimMachDef::transform& parentAxis , MachDef& machineDefinition, bool loadSTL, bool useStlColor,const misc::mwFileName& mXMLPath, const misc::mwstring id = _T("")) ;

		//!AddGeometry
		/*!
			\param geoName		name of the geometry object
			\param parentAxis		reference to the parent object of the first param
			\param machineDefinition		reference to machine definition object
			\param unit		unit of added geometry
		*/
		void AddGeometry( TiXmlNode *geoNode,
			mwMachsimMachDef::transform& parentAxis ,
			MachDef& machineDefintion,
			bool loadSTL,
			bool useStlColor,
			const misc::mwFileName& mXMLPath,
			const misc::mwstring id = _T(""));

		//!AddCollCheck
		/*!
			\param	ccNode		reference to xml node that contains collision checking group data
		*/
		void AddCollCheck( TiXmlNode* ccNode ) ;

		//!AddMagazine
		/*!
		\param	ccNode		reference to xml node that contains machine magazine data
		*/
		void AddMagazine( TiXmlNode* magazineNode , MachDef& machineDefinition, bool loadSTL, bool useStlColor, const misc::mwFileName& mXMLPath);

		//!AddMagazineTree
		/*!
		\param	ccNode		reference to xml node that contains machine magazine data
		*/
		void AddMagazineTree( const misc::mwstring& id, TiXmlNode* magazineTreeNode , MachDef& machineDefinition, bool loadSTL, bool useStlColor,const misc::mwFileName& mXMLPath);

		//!AddPreprocessor
		/*!
			\param	ccNode		reference to xml node that contains preprocessor data
		*/
		void AddPreprocessor( TiXmlNode* ccNode , MachDef& machineDefinition, const misc::mwFileName& mXMLPath) ;

		void IterateThroughChildren( TiXmlNode* node, mwMachsimMachDef::transform& parentAxis, MachDef& machineDefinition, bool loadSTL, bool useStlColor, const misc::mwFileName& mXMLPath, const misc::mwstring treeID = _T(""));
		void IterateThroughMachineDataChildren( TiXmlNode* node, MachDef& machineDefinition );

		const cadcam::mwHomogenousMatrix GetMatrix(TiXmlNode* axisNode, const misc::mwstring& id, float xmlVersion);

		/*!	Check if the given matrix is isometric.
			If not, warn the user and replace it with identity.
			\param id - the name of the matrix object in the machine tree
			\param transform - the 4x4 matrix to be checked for isometry
		*/
		void CheckConformationChanges(const misc::mwstring& id, cadcam::mwHomogenousMatrix& transform);

		// Used to create missing stocks and initial stocks from an existing workpiece
		void AutoCompleteMissingComponents(misc::mwAutoPointer<mwMachsimMachDef> &machine, const bool loadSTL = true);

		// Build a geometry from another existing geometry
		template<typename TGeometry> void CreateGeometry(
			misc::mwAutoPointer<TGeometry>& newGeometry,
			misc::mwAutoPointer<mwMachsimMachDef> &machine,
			const misc::mwstring &treeID,
			const mwMachsimMachDef::object &parent,
			const mwMachsimMachDef::object &sibling,
			const misc::mwstring& defaultName,
			const bool loadSTL = true,
			const machsim::mkdPolygonalGeometry::polyDataRef meshData = MW_NULL,
			const misc::mwstring& fileNameSTL = _T(""),
			const bool transparent = false);

		const void GetMesh(
			const bool loadSTL,
			misc::mwstring nodeName,
			misc::mwstring nodeId,
			const misc::mwstring& fileName,
			const MachDef& machineDefinition,
			MeshLibraryItem& mesh);

		//CNC machines allow duplicate names which they need to be modified to be unique for MachSim machine
		bool CheckForDuplicateIDinCaseOfCNCSimMach(misc::mwstring& toFind, MachDef& machineDefinition);

		const cadcam::mwHomogenousMatrix ExtractMatrixFromCNCSimTransform(TiXmlNode* axisNode);

		TiXmlDocument*								m_tiXmldoc;

		bool										m_convertingFromCNCMach;
		std::list<misc::mwstring>					m_createdIDsWhileConverting;
		size_t										m_currentAddedIDNumber;

#pragma warning(push)
#pragma warning(disable:4251)
		std::map<misc::mwstring, MeshLibraryItem>	m_meshLibrary;
		typedef std::map< misc::mwstring, std::pair< mwMachSimCollisionGroup, mwMachSimCollisionGroup > > bufferedCollCheckMap;
		bufferedCollCheckMap m_bufferedCollCheckPairs;
#pragma warning(pop)

		//!folder-path from where the special geometries files (STLs for stock, initialstock, workpiece, fixture) will be loaded if not empty
			//corresponds to machsim.ini parameter - MachineGeometriesFolderPath
		misc::mwstring m_machineGeometriesFolderPath;

		mkdHeldTool::toolRef m_defaultTool;

	public:
		//! true if axis initial value is out of limits
		bool										m_axisInitialValueOutOfLimit;

#pragma warning(suppress:4251)
		std::vector<misc::mwstring>					m_initialValueOutOfLimitAxisIDs;
	};

} //namespace
#endif	//	MW_MWV2XMLREADER_HPP_
