// (C) 2006-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMMACHDEFHELPER_HPP_
#define MW_MWMACHSIMMACHDEFHELPER_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwMachsimMachDef.hpp"
#include "mwObjMapFiller.hpp"
#include "mwKinematicObjectTypeValidator.hpp"
#include "mwDeprecated.hpp"


namespace interact
{
	class mwLocaleIntf;
}

namespace machsim
{   

	class mkdKinematicTree;
	class mkdMSHelperKOVisitor;
	class mkdMSHelperKOConstVisitor;	


	//! Helper class to facilitate the access to machine definition data.
	class MW_SIMUTIL_API mwMachsimMachDefHelper
	{
	public :
		typedef misc::mwAutoPointer<mkdKinematicObject>							object;
		typedef machsim::mwMachsimMachDef::treeID								treeID;
		typedef machsim::mwMachsimMachDef::constTreeID							constTreeID;
		typedef std::list<misc::mwstring>										stringList;
		typedef misc::mwTreeNode<mkdKinematicObject::Ptr>						treeObject;
		typedef std::map<misc::mwstring, treeObject::constChildrenIterator >	treeObjectMap;
		typedef std::map<misc::mwstring, treeObjectMap >						objectGroupsMap;
		typedef misc::mwTree<mkdKinematicObject::Ptr>							objectsTree;
		typedef machsim::mwMachsimMachDef::CollisionGroupMap					collisionGroupMap;
		typedef std::vector<object>												objectsVector;
		typedef std::list< object >												kinematicObjList;
		

		struct AssociatedWorkpieceSet
		{
			misc::mwstring	m_workpiece;
			misc::mwstring	m_stock;
			stringList		m_fixtures;
			stringList		m_geometries;
		};

		/*! Sets the localization object used to provide translated error messages
			\param newinstance a pointer to the locale instance
			If it is missing we will try to instantiate a default one.
		*/
		static void SetResource(const misc::mwAutoPointer<interact::mwLocaleIntf>& newinstance);

		/*! Sets the unit of measure and scales the meshes if needed.
			\param machineDefinition machine definition that receives the new unit.
			If the new unit is the same as the old one no scaling is performed.
			\param units the new unit of measure.
		 */
		static void CustomScale(machsim::mwMachsimMachDef& machineDefinition, const measures::mwUnitsFactory::Units units ) ;

		//! Generates the collision checking pairs for the given machine definition.
		static void AutoGenerateCollisionCheckingPairs(
			machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring machineHowsingString = _T("Machine housing"),
			const misc::mwstring stringUsedForToolVersusAll = _T("%1$s vs all"),
			const misc::mwstring stringUsedForStaticPairings = _T("%1$s vs %2$s")
		);

		//! Generates a map of object groups from the machine definition
		static const mwMachsimMachDefHelper::objectGroupsMap GetGeometryLists(
			machsim::mwMachsimMachDef &machineDefinition, 
			const misc::mwstring machineHowsingString = _T("Machine housing")
		);

		/*! Retrieves from the given objects parameters all that match the given type.
			\param objects the source container to search for the given type.
			\param type the type of the object to be identified
			\return a container with object names matching the search criteria.
		 */
		static stringList GetObjectNamesByType(const machsim::mwMapValue::GlobalMap& objects, const machsim::mwMapValue::dicts& type);

		static stringList GetObjectNamesByType(const machsim::mwMachsimMachDef& machineDefinition, const machsim::mwMapValue::dicts& type);

		static void GetValidFixtures(
			const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring defaultFixture,
			std::vector<misc::mwstring>& validObjects);

		//! Returns the names of all kinematic elements in the given machine parameter.
		static stringList GetAllKinematicObjectNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all kinematic elements in the given objects container.
		static stringList GetAllKinematicObjectNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all geometry elements in the given machine parameter.
		static stringList GetPolygonalGeometryNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all geometry elements in the given objects container.
		static stringList GetPolygonalGeometryNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all toolpath elements in the given machine parameter.
		static stringList GetToolpathGeometryNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all toolpath elements in the given objects container.
		static stringList GetToolpathGeometryNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all tool elements in the given machine parameter.
		static stringList GetHeldToolNameList(const machsim::mwMachsimMachDef& machineDefinition,const bool alsoCheckMagazine = false);
		//! Returns the names of all tool elements in the given objects container.
		static stringList GetHeldToolNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all coordinate transform elements in the given machine parameter.
		static stringList GetCoordinateTransformNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all coordinate transform elements in the given objects container.
		static stringList GetCoordinateTransformNameList(const machsim::mwMapValue::GlobalMap& objects);

		static machsim::mkdCoordinateTransform::Ptr GetCoordinateTransform(
			const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring objectName);

		//! Returns the names of all axis elements in the given machine parameter.
		static stringList GetAllAxisNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all axis elements in the given objects container.
		static stringList GetAllAxisNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all rotational axis elements in the given machine parameter.
		static stringList GetRotationalAxisNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all rotational axis elements in the given objects container.
		static stringList GetRotationalAxisNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all axis and coordinate transform elements in the given machine parameter.
		static stringList GetAllAxisAndCoordinateTransformNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all axis and coordinate transform elements in the given objects container.
		static stringList GetAllAxisAndCoordinateTransformNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all translational axis elements in the given machine parameter.
		static stringList GetTranslationalAxisNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all translational axis elements in the given objects container.
		static stringList GetTranslationalAxisNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all workpiece elements in the given machine parameter.
		static stringList GetWorkpieceNameList(const machsim::mwMachsimMachDef& machineDefinition, bool alsoCheckMagazine = false);
		//! Returns the names of all workpiece elements in the given objects container.
		static stringList GetWorkpieceNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all fixture elements in the given machine parameter.
		static stringList GetFixtureNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all fixture elements in the given objects container.
		static stringList GetFixtureNameList(const machsim::mwMapValue::GlobalMap& objects);
		
		//! Returns the names of all stock elements in the given machine parameter.
		static stringList GetStockGeometryNameList(const machsim::mwMachsimMachDef& machineDefinitionconst, bool alsoCheckMagazine = false);
		//! Returns the names of all stock elements in the given objects container.
		static stringList GetStockGeometryNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all initial stock elements in the given machine parameter.
		static stringList GetInitialStockNameList(const machsim::mwMachsimMachDef& machineDefinition, bool alsoCheckMagazine = false);
		//! Returns the names of all initial stock elements in the given objects container.
		static stringList GetInitialStockNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all wire EDM head elements in the given machine parameter.
		static stringList GetWireEDMHeadNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all wire EDM head elements in the given objects container.
		static stringList GetWireEDMHeadNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all tailstock elements in the given machine parameter.
		static stringList GetTailStockNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all tailstock elements in the given objects container.
		static stringList GetTailStockNameList(const machsim::mwMapValue::GlobalMap& objects);

		//! Returns the names of all mount adapter elements in the given machine parameter.
		static stringList GetAllMountAdapterNameList(const machsim::mwMachsimMachDef& machineDefinition);
		//! Returns the names of all mount adapter elements in the given objects container.
		static stringList GetAllMountAdapterNameList(const machsim::mwMapValue::GlobalMap& objects);


		//! Returns the names of all default fixture elements in the given objects container.
		static const misc::mwstring GetDefaultFixture(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default fixture elements in the given machine parameter.
		static const misc::mwstring GetDefaultFixture(const mwMachsimMachDef& machineDefinition);

		//! Returns the names of all default stock elements in the given objects container.
		static const misc::mwstring GetDefaultStock(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default stock elements in the given machine parameter.
		static const misc::mwstring GetDefaultStock(const mwMachsimMachDef& machineDefinition);

		//! Returns the names of all default tool elements in the given objects container.
		static const misc::mwstring GetDefaultTool(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default tool elements in the given machine parameter.
		static const misc::mwstring GetDefaultTool(const mwMachsimMachDef& machineDefinition);
		
		//! Returns the names of all default workpiece elements in the given objects container.
		static const misc::mwstring GetDefaultWorkpiece(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default workpiece elements in the given machine parameter.
		static const misc::mwstring GetDefaultWorkpiece(const mwMachsimMachDef& machineDefinition);
				
		//! Returns the names of all default holder transform elements in the given objects container.
		static const misc::mwstring GetDefaultHolderTransform(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default holder transform elements in the given machine parameter.
		static const misc::mwstring GetDefaultHolderTransform(const mwMachsimMachDef& machineDefinition);

		//! Returns the names of all default workpiece elements in the given objects container.
		static const misc::mwstring GetDefaultWorkpieceTransform(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all default workpiece elements in the given machine parameter.
		static const misc::mwstring GetDefaultWorkpieceTransform(const mwMachsimMachDef& machineDefinition);

		//! Gets the correct workpiece name from an associated object
		static const misc::mwstring GetWorkpieceName(const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& workpice);

		//! Gets the correct stock name from an associated object
		static const misc::mwstring GetStockName(const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& stock);

		//! Returns the names of all machine housing elements in the given objects container.
		static const stringList GetMachineHousingNameList(const machsim::mwMapValue::GlobalMap& objects);
		//! Returns the names of all machine housing elements in the given machine parameter.
		static const stringList GetMachineHousingNameList(const mwMachsimMachDef& machineDefinition);
		
		//! Checks if two machine elements have the same parent or if one is parent of the other
		static const bool AreElementsRelated(const machsim::mwMachsimMachDef& machineDefinition, 
			const misc::mwstring& treeId1, const misc::mwstring& treeId2, const bool checkIfParent = true);

		//! Checks if two machine elements are within the specified kinematic module
		static const bool AreKinematicModuleElementsRelated(const machsim::mwMachsimMachDef& machineDefinition, 
			const misc::mwstring& kinematicModule, const misc::mwstring& treeId1, const misc::mwstring& treeId2 = _T(""));

		//! Recursive searches for all objects with dicts type under a given geometry and returns their name in nodeNames container.
		static bool GetAllDescendants( const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& geomId, const machsim::mwMapValue::dicts dicts, stringList& nodeNames);

		//! Gets all the parents list for the inputed geomID
		static const mwMachsimMachDefHelper::kinematicObjList GetKinematicDependencyList(const machsim::mwMachsimMachDef &machineDefinition, const misc::mwstring& geomID );
		//! Gets all the parents list for the inputed geomID
		static const mwMachsimMachDefHelper::kinematicObjList GetKinematicDependencyList(const mwMapValue::GlobalMap &objects, const misc::mwstring& geomID );
		//! Gets the spindle transform that is the first founded in the parents for the inputed geomID. This is done just for the machine not for the heads
		static misc::mwAutoPointer<machsim::mkdRevolvingSet> GetRevolvingSet( const machsim::mwMachsimMachDef &machineDefinition, const misc::mwstring& geomID ) ;
		static const std::vector<misc::mwAutoPointer<machsim::mkdFixture> > GetChildrenFixtureNameList(
			const machsim::mwMachsimMachDef &machineDefinition,
			const misc::mwstring& geomID);
		static const std::vector<misc::mwstring> GetAllNamesRespectingType(
			const machsim::mwMachsimMachDef &machineDefinition,
			const misc::mwstring& geomID,
			const machsim::mwMapValue::dicts type
		);
		//! Gets the revolving set object founded in the parents for the inputed geomID,if none found then it returns the first rotation axis, or NULL.
		static mwMachsimMachDefHelper::object GetRevolvingSetBranchStart( const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& workpieceSibling);
		static mwMachsimMachDefHelper::object GetWorkpieceBranchInsertionPoint( const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& workpieceSibling);
		static mwMachsimMachDefHelper::object GetWorkpieceBranch(const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& workpieceSibling, const bool stopWhenAnotherWorkpieceSetIsDetected);

		//########################################################################
		//! Gets the names of all machine elements respecting the kinematic structure.
		static void GetAllObjectsNameListInStrictOrderAsDefinedInKinematic(
			const machsim::mwMachsimMachDef& machineDefinition, stringList& objectsList, treeObject::constChildrenIterator* it=MW_NULL);

		//! Gets the names of all machine axes respecting the kinematic structure.
		static void GetAxisNameListInStrictOrderAsDefinedInKinematic(
			const machsim::mwMachsimMachDef& machineDefinition, stringList& axisList, treeObject::constChildrenIterator* it=MW_NULL);

		//! Gets the names of all machine tools respecting the kinematic structure.
		static void GetToolsNameListInStrictOrderAsDefinedInKinematic(
			const machsim::mwMachsimMachDef& machineDefinition, stringList& toolsList, treeObject::constChildrenIterator* it=MW_NULL);

		//! Gets the names of all machine workpieces respecting the kinematic structure.
		static void GetWorkpieceNameListInStrictOrderAsDefinedInKinematic(
			const machsim::mwMachsimMachDef& machineDefinition, stringList& workpieceList, treeObject::constChildrenIterator* it=MW_NULL);


				
		//########################################################################
		//! Fetches all kinematic objects from the given magazine kinematic module (e.g. <head>) into the passed elements container.
		static void GetAllObjectsFromKinematicModule(
			const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& treeId, objectsVector& elements);

		//! Fetches all fixture objects from the given magazine kinematic module (e.g. <head>) into the passed elements container.
		static void GetFixturesFromKinematicModule(
			const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& treeId, objectsVector& elements, treeObject::constChildrenIterator* it=MW_NULL);

		static void GetAssociatedWorkpieceSetFromKinematicModule(
			const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& treeId,
			AssociatedWorkpieceSet& associatedWorkpieceSet,
			treeObject::constChildrenIterator* it = MW_NULL);

		//! Fetches all revolving objects related tot he given stock
		static const std::vector<misc::mwstring> GetRevolvingObjectIDs(const machsim::mwMachsimMachDef& machineDefinition, 
			const misc::mwstring& stockName, bool forceGettingAllObjectsEvenIfRevolvingSetIsNotDefine = true);

		//! Fetches all the children of a set of given objects
		static const std::vector<misc::mwstring>GetFullObjectListExpandingMountAdapters(
			const machsim::mwMachsimMachDef& machineDef, const std::vector<misc::mwstring>& objNameList);


		//########################################################################
		//! Query if the given object is a type derived from mkdPolygonalGeometry.		
		static bool IsPolygonalGeometryBased(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdPolygonalGeometry type.
		static bool IsPolygonalGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdToolGraphic type.		
		static bool IsToolpathGraphic(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdHeldTool type.
		static bool IsHeldToolGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdCoordinateTransform type.
		static bool IsCoordinateTransform(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdRevolvingSet type.
		static bool IsRevolvingSet(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdAxis type.
		static bool IsAxis(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdRotationalAxis type.
		static bool IsRotationalAxis(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdTranslationalAxis type.		
		static bool IsTranslationalAxis(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdWorkPiece type.
		static bool IsWorkpieceGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdFixture type.
		static bool IsFixtureGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdStockGeometry type.		
		static bool IsStockGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdInitialStock type.
		static bool IsInitialStockGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdWireEDMHead type.
		static bool IsWireEDMHeadGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdMountAdapter type.		
		static bool IsMountAdapterGeometry(const machsim::mkdKinematicObject& mkdObj);
		//! Query if the given object is a mkdTailStock type
		static bool IsTailStockGeometry(const machsim::mkdKinematicObject& mkdObj);
		

		//########################################################################	
		/*! FindChildren
			Recursive method used by GetChildren to search for parentObject's children.
		*/
		static bool FindChildren(treeObject::constChildrenIterator It,	const object& parentObject,	objectsVector& childrenArray);		
		/*! GetChildren 
			Searches the kinematic tree for mkdObj's children.
			It does not retrieve children's children as method does not reenter its children.
			Use instead GetAllChildren to retrieve all the children of a kinematic object.
		*/
		static void GetChildren(const machsim::mwMachsimMachDef& machineDefinition, const object& mkdObj, objectsVector& childrenArray) ;

		/*! GetChildren 
			Searches the kinematic tree for mkdObj's children.
			It does not retrieve children's children as method does not reenter its children.
			Use instead GetAllChildren to retrieve all the children of a kinematic object.
		*/
		static void GetChildren(const machsim::mkdKinematicTree& kinematicTree, const object& mkdObj, objectsVector& childrenArray) ;

		/*! GetSiblings
			Searches the kinematic tree for mkdObj's siblings.
		*/
		static void GetSiblings(const machsim::mwMachsimMachDef& machineDefinition, const object& mkdObj, objectsVector& siblingsArray, const misc::mwstring& treeId = _T(""));

		/*! FindAllChildren
			Recursive method used by GetAllChildren to search for all parentObject's children.
			This method is reentrant and for each children it searches recursively its children.
		*/
		static bool FindAllChildren(treeObject::constChildrenIterator It,	const object& parentObject,	objectsVector& childrenArray);		

		/*! GetAllChildren 
			Searches the kinematic tree for mkdObj's children.
			It retrieves also children's children of mkdObj.
		*/
		static void GetAllChildren(const machsim::mwMachsimMachDef& machineDefinition, const object& mkdObj, objectsVector& childrenArray);

		/*! GetAllChildren 
			Searches the kinematic tree for mkdObj's children.
			It retrieves also children's children of mkdObj.
		*/
		static void GetAllChildren(const machsim::mkdKinematicTree& kinematicTree, const object& mkdObj, objectsVector& childrenArray);

		/*! FindParent 
			Recursive method used by GetParent to search for mkdObj's parent.
		*/
		static bool FindParent(treeObject::constChildrenIterator It, const object& mkdObj, object& objParent);
		
		/*! GetParent
			Searches for mkdObj's parent, in the specific (if provided) kinematic tree. If successful, the parent object will be returned.
			If method fails, it will return MW_NULL.
		*/
		static object GetParent(const machsim::mwMachsimMachDef& machineDefinition, const object& mkdObj, const misc::mwstring& treeId = _T(""));

		/*! Has Children 			
		*/
		static bool HasChildren(const mkdKinematicTree::treeID& treenode);

		/*! Has Children 			
		*/
		static bool HasChildren(const misc::mwstring& geomID, const machsim::mwMapValue::GlobalMap& objects) ;

		/*! Has Given Children	 check if the childrenToCheckFor is found as child to the current object 			
		*/
		static bool HasGivenChildren(const misc::mwstring& geomId, const misc::mwstring& childrenToCheckFor, const machsim::mwMapValue::GlobalMap& objects) ;

		/*! Has Given Children	 check if the childrenToCheckFor is found as child to the current object
		*/
		static bool HasGivenChildren(const mkdKinematicTree::treeID& treenode,
			const misc::mwstring& childrenToCheckFor,
			const machsim::mwMapValue::GlobalMap& objects) ;

		static const cadcam::mwHomogenousMatrix DoubleToFloatMatrixConv(const cadcam::mwHomogenousMatrixd& inputMatrix);

		//! Is Object Defined 		
		static bool IsObjectDefined(const misc::mwstring& objectID, const machsim::mwMapValue::GlobalMap& objects) ;

		//! Gets the children of given type; looks only one level below
		static void GetAllSiblingPartByType(const machsim::mwMachsimMachDef& machineDefinition,
			const mkdKinematicObject::Ptr & obj,
			const machsim::mwMapValue::dicts dicts,
			objectsVector& elements);

		//! Gets all the children of given type
		static void GetAllChildrenByType(const machsim::mwMachsimMachDef& machineDefinition,
			const mkdKinematicObject::Ptr & obj,
			const machsim::mwMapValue::dicts dicts,
			objectsVector& elements);

		//! Gets a tree iterator to an object given by name
		static  mkdKinematicTree::treeID GetIt(const misc::mwstring& toFind, const machsim::mwMapValue::GlobalMap& objects);

		//! Gets a pointer to a kinematic object starting from a name
		static  misc::mwAutoPointer<mkdKinematicObject>	GetObjectByName(const misc::mwstring& toFind,
			const machsim::mwMapValue::GlobalMap& objects);

		static void SetWorkpieceMesh(
			misc::mwAutoPointer<machsim::mwMachsimMachDef> machineDefinition,
			const misc::mwstring objectID,
			misc::mwAutoPointer<cadcam::mwTMesh<float>> workpieceMesh);

		static void SetToolMesh(
			misc::mwAutoPointer<machsim::mwMachsimMachDef> machineDefinition,
			const misc::mwstring toolName,
			misc::mwAutoPointer<cadcam::mwTool> currentTool,
			const misc::mwstring toolComment = _T(""),
			const int toolNumber = 0);
		
		static const double GetRecommendedProfileTolerance(const cadcam::mwTool::Ptr& tool);

		//! Gets a pointer to a object starting from a name
		template <typename T>
		static misc::mwAutoPointer<T> GetObjectT(
			const misc::mwstring& name, const machsim::mwMapValue::GlobalMap& objectsPool);

		/*!
		@deprecated Deprecated since the 2021.08 release. Please use node GetObjectT instead.
		Deprecation is needed because GetObject might interfer with WinAPI for non unicode build.
		*/
		template <typename T>
		MW_DEPRECATED("Deprecated since the 2021.08 release. Please use node GetObjectByName instead.")
		static misc::mwAutoPointer<T> GetObject(
				const misc::mwstring& name, const machsim::mwMapValue::GlobalMap& objectsPool)
		{
			return mwMachsimMachDefHelper::GetObjectT<T>(name, objectsPool);
		}

		//! Counts the objects of a given type
		static int Counter(const mwMapValue::dicts& objtype, const machsim::mwMapValue::GlobalMap& objects) ;

		//! Gets the first rotational axis, if any, that is a parent of the given object
 		static machsim::mkdRotationalAxis::Ptr GetParentRotationalAxis(const machsim::mwMachsimMachDef& machineDefinition,
 			const mkdPolygonalGeometry& geo);

		//! Gets the first rotational axis, if any, that is a parent of the given object
		static machsim::mkdRotationalAxis::Ptr GetParentRotationalAxis(const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& id);

		//! Gets the combined values of parent nested transforms until an axis is encountered
		static cadcam::mwHomogenousMatrix GetParentTransformsChain(const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& id);

		//! Gets the parent tool holder transform
		static const machsim::mkdCoordinateTransform::Ptr GetToolHolderTransform(const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring toolName);
		
		//! Gets the parent translational axis
		static machsim::mkdTranslationalAxis::Ptr GetParentTranslationalAxis(const machsim::mwMachsimMachDef& machineDefinition,
			const machsim::mkdKinematicObject& obj);

		//! Gets the parent rotation or translation axis
		static machsim::mkdAxis::Ptr GetParentTranslationalOrRotationalAxis(const machsim::mwMachsimMachDef& machineDefinition, const machsim::mkdKinematicObject& obj);
		//########################################################################
		///
		/// Helper methods to facilitate changing trees (e.g. <head> mounting) in the kinematic tree.
		///

        //! Query if a given kinematic module (e.g. <head>) exists in the passed machine's magazine.
		static bool HasKinematicModule( const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& treeId) ;
		//! Query if a given (parent) object has any children.
		static bool HasChildren(const machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& parentName);
		//! Query if a given (parent) kinematic object has any children.
		static bool HasChildren(const machsim::mwMachsimMachDef& machineDefinition, const object& parentObject);
		//! Query if a given (parent) tree node has any children.
		static bool HasChildren(const machsim::mwMachsimMachDef& machineDefinition, const treeID& parentId);


		//! Query the children of "geomId" for any existing "childToCheckFor" named object.
		static bool HasGivenChildren(const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& geomId, const misc::mwstring& childToCheckFor );
		//! Returns in "nodeName" the first object of "dicts" type existing among "geomId" children.
		static bool HasGivenChildren(const machsim::mwMapValue::GlobalMap& objects,const misc::mwstring& geomId, const machsim::mwMapValue::dicts dicts, misc::mwstring& nodeName);


		//! Query recursively the "geomId" sub-tree for any existing "childToCheckFor" named object.
		static bool HasGivenDescendant(const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& geomId, const misc::mwstring& childToCheckFor );
		//! Query recursively the "geomId" sub-tree for any existing "childToCheckFor" named object.
		static bool HasGivenDescendant(const machsim::mwMapValue::GlobalMap& objects, const treeID& treenode, const misc::mwstring& childToCheckFor );
		//! Query recursively the "geomId" sub-tree for any existing type "dicts" object and returns its name in "nodeName".
		static bool HasGivenDescendant(const machsim::mwMapValue::GlobalMap& objects,const misc::mwstring& geomId, const machsim::mwMapValue::dicts dicts, misc::mwstring& nodeName);


		//! Removes the sub-tree under "parentName"
		static void RemoveAllChildren(machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& parentName);		
		//! Removes objName object and ALL ITS CHILDREN!!
		static void RemoveObject(machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& objName);

		static void ResetToolData(machsim::mwMachsimMachDef& machineDefinition);

		//! Inserts the "toAdd" sub-tree under "parent" kinematic element.
		static void InsertTree( machsim::mwMachsimMachDef& machineDefinition, const machsim::mkdKinematicTree& toAdd, machsim::mwMachsimMachDef::transform& parent );
		//! Inserts the "toAdd" sub-tree under "parent" kinematic element.
		static void InsertTree( machsim::mwMachsimMachDef& machineDefinition, constTreeID& toAdd, machsim::mwMachsimMachDef::transform& parent );	

		//! Mounts the tree from "module" magazine's kinematic module (e.g. <head>) under machine "transform" kinematic element.
		static void MountKinematicModule(machsim::mwMachsimMachDef& machineDefinition, const misc::mwstring& transform, const misc::mwstring& module);

		//########################################################################
		
		static void SetCoordinateTransformMatrix(
			const misc::mwstring& coordinateTransformObjectID,
			const cadcam::mwHomogenousMatrix& matrix,
			machsim::mwMachsimMachDef& machineDefinition);

		static const cadcam::mwHomogenousMatrix& GetCoordinateTransformPropagatedMatrix(
			const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring objectName);

		static const cadcam::mwHomogenousMatrix& GetCoordinateTransformInitialMatrix(
			const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring objectName);

		static void SetCoordinateTransformValueMatrix(
			const misc::mwstring& objectName,
			const cadcam::mwHomogenousMatrix& matrix,
			machsim::mwMachsimMachDef& machineDefinition);

		static void SetCoordinateTransformInitialMatrix(
			const misc::mwstring& objectName,
			const cadcam::mwHomogenousMatrix& matrix,
			machsim::mwMachsimMachDef& machineDefinition);

		//! Iterates through all kinematic elements and for each of them calls "visitor" Visit method.
		static void VisitKinematicObjects( mkdMSHelperKOVisitor& visitor ) ;
		//! Iterates through all kinematic elements and for each of them calls "visitor" Visit method.
		static void VisitKinematicConstObjects( mkdMSHelperKOConstVisitor& visitor ) ;	

		//! Returns all children under given "subtreeID" element.
		static std::vector<misc::mwstring> RetrieveChildrenGeometryIDs(mwMachsimMachDef& machineDefinition, const misc::mwstring subtreeID = _T(""));

		//! Returns all objects that are collision checked against given "objectID"
		static std::vector<misc::mwstring> GetCheckAgainstObjects(const mwMachsimMachDef& machineDefinition, const misc::mwstring objectID);
				
		//! Fills the "objectMap" with the top axes found under "element" object.
		static void FetchTopAxesList( treeObject::constChildrenIterator element, treeObjectMap& objectMap );

		//! Returns the rotational axis found at given 1 based index among all rotational axes sorted alphabetically.
		static machsim::mkdRotationalAxis::Ptr GetRotationalAxisFromMachDef(
			const mwMachsimMachDef& machineDefinition, unsigned int axisIndexInMachineDefinition );

		//! Returns the stock in the kinematic branch that also contains the referenced geometry
		static misc::mwstring GetAssociatedStock(mwMachsimMachDef& machineDefinition, const misc::mwstring geoID);

		//! Returns a structure with all associated elements with workpiece.
		static mwMachsimMachDefHelper::AssociatedWorkpieceSet GetAssociatedWorkpieceSet(mwMachsimMachDef& machineDefinition, const misc::mwstring geoID);

		//! Deletes collision pairings involving tools
		static void DeleteToolPairings( machsim::mwMachsimMachDef& machineDefinition);
		//! Deletes collision pairings involving given tools
		static void DeleteToolPairings(machsim::mwMachsimMachDef& machineDefinition, const mwMachsimMachDefHelper::stringList &toolList);
		//! Creates tool pairings
		static void InsertToolPairings( 
			machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring stringUsedForToolVersusAll = _T("%1$s vs all")
			);
		//! Deletes collision pairings that are not in the machine
		static void RemoveAllObjectsFromCollisionGroupsThatAreNotInTheMachine( machsim::mwMachsimMachDef& machineDefinition );

		static void RemoveObjectsNotDefineInMachine(const machsim::mwMachsimMachDef& machineDefinition, mwMachSimCollisionGroup::objectGroup& objGroup);
		//! Gets branch containing a given id
		static const machsim::mkdKinematicTree::const_treeID GetStartOfBranchContainingId(
			machsim::mwMachsimMachDef::Ptr currentMachine,
			const misc::mwstring &id 
			);
		
		//! Returns true if branch is containing a given id
		static const bool IsBranchContainingId( machsim::mkdKinematicTree::const_treeID axis, machsim::mkdKinematicTree::const_treeID idSearched );

		//! Recursive searches for first object with dicts type under geomId and returns its name in nodeName.
		static bool HasDescendant(const machsim::mwMapValue::GlobalMap& objects,const misc::mwstring& geomId, const machsim::mwMapValue::dicts dicts, misc::mwstring& nodeName);

		//! Returns the type of the object
		static machsim::mwMapValue::dicts GetObjectType( const machsim::mwMachsimMachDef& machineDefinition, 
			const misc::mwstring& objectID);
		//! Returns the part of the tool for specified component id
		static machsim::mwMapValue::toolComponents GetToolComponentType(const misc::mwstring& componentID);

		//! Returns if the specified component id is part of the tool
		static bool IsToolComponent(const misc::mwstring& componentID);

		//! Returns the tool name from component id
		static misc::mwstring ExtractToolNameFromToolComponent(const misc::mwstring& componentID);

		//! Returns default name for cutting part
		static const misc::mwstring GetToolCuttingPartID();
		//! Returns default name for non cutting part
		static const misc::mwstring GetToolNonCuttingPartID();
		//! Returns default name for arbor part
		static const misc::mwstring GetToolArborPartID();
		//! Returns default name for holder part
		static const misc::mwstring GetToolHolderPartID();

		//! Returns true if both objects are under common parent
		static misc::mwstring GetTopMostCoordinateObjectUntilCommonAxis(const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& id);

		static machsim::mkdKinematicObject::Ptr GetTopParent(const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& id,
			const machsim::mwMapValue::dicts& stopToType);

		static void GetTopParents(const machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& id,
			const machsim::mwMapValue::dicts& filtreType,
			bool orderFromTop,
			objectsVector& elements);

		/*! FindFilterChildren
		Recursive method used by GetFilterChildren to search for all parentObject's children.
		This method is reentrant and for each children it searches recursively its children.
		*/
		static bool FindFilterChildren(treeObject::constChildrenIterator It,
			const object& parentObject,
			const machsim::mwMapValue::dicts& ignoreUnderType,
			const machsim::mwMapValue::dicts& contiuneIfTypeIsNotUnder,
			objectsVector& childrenArray);

		static bool IsUnwantedTypeUnder(treeObject::constChildrenIterator It,
			const machsim::mwMapValue::dicts& ignoreUnderType,
			const machsim::mwMapValue::dicts& contiuneIfTypeIsNotUnder);

		//! Returns only children that are not under ignore type
		// "ignoreUnderType" will ignore any object under this type 
		// Flag "contiuneIfTypeIsNotUnder" if this is type is not under "ignoreUnderType"  the objects will continue to be collected.
		// Use MW_NONE to ignore flag "contiuneIfTypeIsNotUnder"

		static void GetFilterChildren(const machsim::mkdKinematicTree& kinematicTree,
			const object& mkdObj,
			const machsim::mwMapValue::dicts& ignoreUnderType,
			const machsim::mwMapValue::dicts& contiuneIfTypeIsNotUnder,
			objectsVector& childrenArray);

		//! Returns top axis list from machine
		static const machsim::mwMachsimMachDefHelper::treeObjectMap GetTopAxisList(const machsim::mwMachsimMachDef& machineDefinition);

	private:
		//! Fetches the top level geometries located under element axis which must be also a top axis.
		static void FetchTopLevelGeometryNames(treeObject::constChildrenIterator element, const treeObjectMap& topAxes, treeObjectMap& objects);
		
		//! Fetches recursively all polygonal geometries under element node.
		static void RetrieveChildrenGeometryNames(treeObject::constChildrenIterator element, treeObjectMap& objects);

		//! Adds the given collision group to machine definition.
		static void InsertCollisionPairingsUsingGeometryLists(
			const objectGroupsMap& geometryLists,
			machsim::mwMachsimMachDef& machineDefinition,
			const misc::mwstring& stringUsedForToolVersusAll,
			const misc::mwstring& stringUsedForStaticPairings
		);

		//! Adds the dynamic coll. pair to collision group.
		static void InsertToolPairings(
			const objectGroupsMap& geometryLists,
			collisionGroupMap& groupMap,
			const misc::mwstring& stringUsedForToolVersusAll
		);
	
		//! Adds the static coll. pair to collision group.
		static void InsertStaticPairings(
			const objectGroupsMap& geometryLists, 
			collisionGroupMap& groupMap,
			const misc::mwstring& stringUsedForStaticPairings
		);
		
		//! Iterates the sub-tree under "parent" passing each node to visitor for processing.
		static void MultiPurposeKinematicObjectsVisitor(mkdMSHelperKOVisitor& visitor, const object& parent);
		//! Iterates the sub-tree under "parent" passing each node to visitor for processing.
		static void MultiPurposeKinematicConstObjectsVisitor(mkdMSHelperKOConstVisitor& visitor, const object& parent);
		
		struct  mwRevolvingSetCandidates
		{
			mwMachsimMachDefHelper::object m_firstPriorrity_WorkpieceSpindle;
			mwMachsimMachDefHelper::object m_firstPriority_MaximalParentWithAllWorkpieceSiblings;
			mwMachsimMachDefHelper::object m_secondPriorrity_FirstRotationAxis;
			mwMachsimMachDefHelper::object m_thirdPriorrity_FirstTranslationAxis;
			mwMachsimMachDefHelper::object m_forthPriority_MinimalParentWithAllWorkpieceSiblings;
			
		};
		
		static void RegisterMinimalOrMaximalParentWithAllWorkpieceSiblings(const machsim::mwMachsimMachDef& machineDefinition, 
			const object currentParrent, const object previousParent, int &missingParts, mwRevolvingSetCandidates &candidatesPool);
		
		//! Fill in the list with all visited object names.
		class mwMachineObjectsNamesGrabber: public machsim::mwMapIteratorInterface
		{
		public:

			//! Constructor
			mwMachineObjectsNamesGrabber(){}

			//! Collect names
			virtual void CallForElement
				( const machsim::mwMapValue::name& name
				, const machsim::mwMapValue& /*value*/ )
			{
				m_ids.push_back(name);
			}

			//! Get names
			const std::list<misc::mwstring>& GetNames() const
			{
				return m_ids;
			}
		private:
			std::list<misc::mwstring> m_ids;
		};

		//! Returns "defaultName" if found in the "stringsPool" otherwise the empty string.
		static const misc::mwstring GetValidDefaultName(const stringList& stringsPool, const misc::mwstring& defaultName);

		
		//! Recursive searches for first object with dicts type under treenode and returns its in nodeName.
		static bool HasDescendant(const machsim::mwMapValue::GlobalMap& objects,const treeID& treenode, const machsim::mwMapValue::dicts dicts, misc::mwstring& nodeName);

		//! Recursive searches for all objects with dicts type under treenode and returns their names in nodeName.
		static bool FindAllDescendants(const machsim::mwMapValue::GlobalMap& objects, const treeID& treenode, const machsim::mwMapValue::dicts dicts, stringList& nodeName);

		//! Recursive searches for all objects with dicts type under geomId and returns their names in nodeName.
		static bool FindAllDescendants(const machsim::mwMapValue::GlobalMap& objects, const misc::mwstring& geomId, const machsim::mwMapValue::dicts dicts, stringList& nodeName);
		
		//! Get tree iterator to a given object referenced by its id
		static const mkdKinematicTree::treeID GetIt(const mwMapValue::GlobalMap &objects, const misc::mwstring& toFind );

		//! Get the parent of an object by its tree id
		static mwMachsimMachDefHelper::object GetParent(const mkdKinematicTree::treeID& treenode);

		static misc::mwstring InitializeToolName(
			const std::vector<misc::mwstring>& axisToFind,
			const misc::mwstring& name,
			const mwMapValue::GlobalMap &objects);

		
	private:
		//! ctor not allowed since it is a static class only.
		mwMachsimMachDefHelper();

		template<typename T, typename U> static bool IsSameObjectType();
		template<typename T> static int ErrorCodeFromType();

		static bool HasWorkpieceSiblingParts(const machsim::mwMachsimMachDef& machineDefinition, const mkdKinematicObject::Ptr & obj, int& foundParts);
	};

//#####################################################################################



	//! Class implements the mesh scaling based on the new unit of measure.
	class MW_SIMUTIL_API MachsimMachDefCustomScaleVisitor : public mkdKOVisitor
	{
	public:
		MachsimMachDefCustomScaleVisitor(const measures::mwUnitsFactory::Units units) ;
		~MachsimMachDefCustomScaleVisitor() ;

		void Visit( mkdKinematicObject &toVisit ) ;
		void Visit( mkdPolygonalGeometry &toVisit ) ;
		void Visit( mkdToolpathGeometry &toVisit )  ;
		void Visit( mkdHeldTool &toVisit ) ;
		void Visit( mkdCoordinateTransform &toVisit ) ;
		void Visit( mkdRevolvingSet &toVisit ) ;
		void Visit( mkdRotationalAxis &toVisit ) ;
		void Visit( mkdTranslationalAxis &toVisit ) ;
		void Visit( mkdWorkPiece &toVisit ) ;
		void Visit( mkdFixture &toVisit ) ;
		void Visit( mkdStockGeometry &toVisit ) ;
		void Visit( mkdTailStock &toVisit ) ;
		void Visit( mkdInitialStock &toVisit ) ;
		void Visit( mkdWireEDMHead &toVisit ) ;
		void Visit( mkdMountAdapter &toVisit ) ;

	private:		
		measures::mwUnitsFactory::Units			m_units;
	};


	//! Visitor extending mkdKOSimConstVisitor class.
	//! This class can be extend by any implementation.
	class MW_SIMUTIL_API mkdMSHelperKOConstVisitor : public mkdKOSimConstVisitor
	{
	public:
		explicit mkdMSHelperKOConstVisitor( const mwMachsimMachDef& machineDef ) ;
		const mwMachsimMachDef&  GetMachineDefinition() const ;
		//visit methods
		void Visit( const machsim::mkdKinematicObject &toVisit );
		void Visit( const machsim::mkdPolygonalGeometry &toVisit );
		void Visit( const machsim::mkdToolpathGeometry &toVisit );
		void Visit( const machsim::mkdHeldTool &toVisit );
		void Visit( const machsim::mkdCoordinateTransform &toVisit ) ;
		void Visit( const machsim::mkdRevolvingSet &toVisit ) ;
		void Visit( const machsim::mkdRotationalAxis &toVisit ) ;
		void Visit( const machsim::mkdTranslationalAxis &toVisit ) ;
		void Visit( const machsim::mkdWorkPiece &toVisit );
		void Visit( const machsim::mkdFixture &toVisit );
		void Visit( const mkdStockGeometry &toVisit );
		void Visit( const mkdInitialStock &toVisit );
		void Visit( const mkdWireEDMHead &toVisit );
		void Visit( const mkdMountAdapter &toVisit );
	private:
		// avoid warning c4512
		mkdMSHelperKOConstVisitor& operator=(const mkdMSHelperKOConstVisitor&);
		const machsim::mwMachsimMachDef&			m_machineDef;
	};
	

	//! Visitor extending mkdKOSimVisitor class.
	//! This class can be extend by any implementation.
	class MW_SIMUTIL_API mkdMSHelperKOVisitor : public mkdKOSimVisitor
	{
	public:
		explicit mkdMSHelperKOVisitor( mwMachsimMachDef& machineDef ) ;
		mwMachsimMachDef&  GetMachineDefinition() ;
		//visit functions
		void Visit( machsim::mkdKinematicObject &toVisit );
		void Visit( machsim::mkdPolygonalGeometry &toVisit );
		void Visit( machsim::mkdToolpathGeometry &toVisit );
		void Visit( machsim::mkdHeldTool &toVisit );
		void Visit( machsim::mkdCoordinateTransform &toVisit ) ;
		void Visit( machsim::mkdRevolvingSet &toVisit ) ;
		void Visit( machsim::mkdRotationalAxis &toVisit ) ;
		void Visit( machsim::mkdTranslationalAxis &toVisit ) ;
		void Visit( machsim::mkdWorkPiece &toVisit );
		void Visit( machsim::mkdFixture &toVisit );
		void Visit( machsim::mkdStockGeometry &toVisit );
		void Visit( machsim::mkdInitialStock &toVisit );
		void Visit( machsim::mkdWireEDMHead &toVisit );
		void Visit( machsim::mkdMountAdapter &toVisit );
	private:
		// avoid warning c4512
		mkdMSHelperKOVisitor& operator=(const mkdMSHelperKOVisitor&);

		machsim::mwMachsimMachDef&			m_machineDef;	
	};
	

	//! This class collects all visited objects in containers separated by kinematic type.
	class MW_SIMUTIL_API TreeVisitor4AllGeoNames : public mkdMSHelperKOConstVisitor
	{
	public:
		typedef std::list<misc::mwstring>				GeoStringList ;

		//! ctor
		TreeVisitor4AllGeoNames( const mwMachsimMachDef& machineDef ) ;
		
		//! Visit methods	
		void Visit( const machsim::mkdKinematicObject& toVisit );
		void Visit( const machsim::mkdPolygonalGeometry& toVisit );
		void Visit( const machsim::mkdToolpathGeometry& toVisit ) ;
		void Visit( const machsim::mkdHeldTool& toVisit );
		void Visit( const machsim::mkdCoordinateTransform& toVisit ) ;
		void Visit( const machsim::mkdRevolvingSet& toVisit ) ;
		void Visit( const machsim::mkdRotationalAxis& toVisit ) ;
		void Visit( const machsim::mkdTranslationalAxis& toVisit ) ;
		void Visit( const machsim::mkdWorkPiece& toVisit );
		void Visit( const machsim::mkdFixture& toVisit );
		void Visit( const machsim::mkdStockGeometry& toVisit );
		void Visit( const machsim::mkdInitialStock& toVisit );
		void Visit( const machsim::mkdWireEDMHead& toVisit );
		void Visit( const machsim::mkdTailStock& toVisit);
		void Visit( const machsim::mkdMountAdapter& toVisit );

		//! Returns a container with all visited objects of a certain type.
		const GeoStringList& GetAllKinematicObjNameList() const;
		const GeoStringList& GetPolygonalGeoNameList() const;
		const GeoStringList& GetToolpathGeoNameList() const ;
		const GeoStringList& GetHeldToolNameList() const;
		const GeoStringList& GetCoordinateTransformNameList() const;
		const GeoStringList& GetRevolvedSetNameList() const;
		const GeoStringList& GetAllAxisNameList() const ;
		const GeoStringList& GetRotationalAxisNameList() const;
		const GeoStringList& GetTranslationalAxisNameList() const;
		const GeoStringList& GetWorkpieceNameList() const;
		const GeoStringList& GetFixtureNameList() const;
		const GeoStringList& GetStockGeoNameList() const;
		const GeoStringList& GetInitialStockNameList() const;
		const GeoStringList& GetWireEDMHeadNameList() const;
		const GeoStringList& GetTailStockNameList() const;
		const GeoStringList& GetMountAdapterNameList() const;

		
	private:
#pragma warning(push)
#pragma warning(disable:4251)
		GeoStringList	m_allKinematicObjList ;
		GeoStringList	m_polygonalGeoList;
		GeoStringList	m_toolpathGeoList ;
		GeoStringList	m_heldToolList;
		GeoStringList	m_coordinateTransformList;
		GeoStringList	m_revolvingSetList;
		GeoStringList	m_allAxisNameList ;
		GeoStringList	m_rotationalAxisNameList;
		GeoStringList	m_translationalAxisNameList;
		GeoStringList	m_workpieceNameList;
		GeoStringList	m_fixtureNameList;
		GeoStringList	m_stockGeoList;
		GeoStringList	m_initialStockList;	
		GeoStringList	m_wireEDMHeadList;
		GeoStringList	m_tailStockList;
		GeoStringList	m_mountAdapterList;
#pragma warning(pop)
	};
	

	//! Visitor facilitates retrieving the type of a visited object.
	class MW_SIMUTIL_API GeometryTypeGetterKOConstVisitor : public mkdKOSimConstVisitor
	{
	public:
		GeometryTypeGetterKOConstVisitor();
		~GeometryTypeGetterKOConstVisitor();

		bool IsPolygonalGeometry() const;
		bool IsToolpathGeometry() const;
		bool IsHeldToolGeometry() const;
		bool IsCoordinateTransformGeometry() const;
		bool IsRevolvingSetGeometry() const;
		bool IsRotationalAxisGeometry() const;
		bool IsTranslationalAxisGeometry() const;
		bool IsWorkpieceGeometry() const;
		bool IsFixtureGeometry() const;
		bool IsStockGeometry() const;
		bool IsInitialStockGeometry() const;
		bool IsWireEDMHeadGeometry() const;
		bool IsMountAdapterGeometry() const;
		bool IsTailStockGeometry() const;

	private:
		void Visit( const machsim::mkdKinematicObject& toVisit );
		void Visit( const machsim::mkdPolygonalGeometry& toVisit );
		void Visit( const machsim::mkdToolpathGeometry& toVisit ) ;
		void Visit( const machsim::mkdHeldTool& toVisit );
		void Visit( const machsim::mkdCoordinateTransform& toVisit ) ;
		void Visit( const machsim::mkdRevolvingSet& toVisit ) ;
		void Visit( const machsim::mkdRotationalAxis& toVisit ) ;
		void Visit( const machsim::mkdTranslationalAxis& toVisit ) ;
		void Visit( const machsim::mkdWorkPiece& toVisit );
		void Visit( const machsim::mkdFixture& toVisit );
		void Visit( const machsim::mkdStockGeometry& toVisit );
		void Visit( const machsim::mkdTailStock& toVisit );
		void Visit( const machsim::mkdInitialStock& toVisit );
		void Visit( const machsim::mkdWireEDMHead& toVisit );
		void Visit( const machsim::mkdMountAdapter& toVisit );

		void ResetType() ;

		//members
		bool m_bPolygonalGeo;
		bool m_bToolpathGeo;
		bool m_bHeldToolGeo;
		bool m_bCoordinateTransformGeo;
		bool m_bRevolvingSetGeo;
		bool m_bRotationalAxisGeo;
		bool m_bTranslationalAxisGeo;
		bool m_bWorkpieceGeo;
		bool m_bFixtureGeo;
		bool m_bStockGeo;
		bool m_bInitialStockGeo;
		bool m_bWireEDMHeadGeo;
		bool m_bMountAdapterGeo;
		bool m_bTailStockGeo;
	};
	
};//end namespace machsim
#endif	//	MW_MWMACHSIMMACHDEFHELPER_HPP_
