// (C) 2006-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMMACHDEF_HPP_
#define MW_MWMACHSIMMACHDEF_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdKinematicObject.hpp"
#include "mkdGeometry.hpp"
#include "mkdPolygonalGeometry.hpp"
#include "mkdDynamicGeometry.hpp"
#include "mkdCoordinateTransform.hpp"
#include "mkdRevolvingSet.hpp"
#include "mkdHeldTool.hpp"
#include "mkdAxis.hpp"
#include "mkdRotationalAxis.hpp"
#include "mkdTranslationalAxis.hpp"
#include "mkdWorkPiece.hpp"
#include "mkdFixture.hpp"
#include "mkdToolpathGeometry.hpp"
#include "mkdStockGeometry.hpp"
#include "mkdTailStock.hpp"
#include "mkdInitialStock.hpp"
#include "mkdWireEDMHead.hpp"
#include "mkdMountAdapter.hpp"
#include "mwMachSimCollisionGroup.hpp"
#include "mwMachineKinematicsProcessorPlugin.hpp"
#include "mwObjMapFiller.hpp"
#include "mwMachSimPreprocessor.hpp"
#include "mwToolHelper.hpp"
#include "mwEndMill.hpp"
#include "mwAutoPointer.hpp"
#include "mwString.hpp"
#include "mwTree.hpp"
#include "mkdKinematicTree.hpp"
#include "mwGenericPostDef.hpp"


namespace machsim
{
    
	class mkdKinematicTree;

	//! Class implements the storage for machine definition.
	//! For more functionality you can also have a look at class mwMachsimMachDefHelper.
    class MW_SIMUTIL_API mwMachsimMachDef : public measures::mwMeasurable
	{
	public:	
		//types
		typedef misc::mwAutoPointer<mwMachsimMachDef>								Ptr;
		typedef misc::mwAutoPointer<mkdCoordinateTransform>							transform;
		typedef misc::mwAutoPointer<mkdGeometry>									geometry;
		typedef misc::mwAutoPointer<mkdHeldTool>									tool;
		typedef misc::mwAutoPointer<mkdAxis>										axis;
		typedef misc::mwAutoPointer<mkdRevolvingSet>								revolvingSet;
		typedef misc::mwAutoPointer<mkdKinematicObject>								object; 
		typedef misc::mwAutoPointer<mkdKinematicObject>								kinematicEntry;
		typedef misc::mwTreeNode<kinematicEntry>::nodeID							treeID;
		typedef misc::mwTreeNode<mkdKinematicObject::Ptr>::constChildrenIterator	constTreeID;
		typedef misc::mwAutoPointer<mwMachineKinematicsProcessorPlugin>						plugin;
		typedef std::list<plugin>													plugins;
		typedef plugins::iterator													pluginID;
		
		//! A top entry in the machine's magazine. (e.g. <head>)
		class KinematicModule
		{		
			//! Initialize
			void Init();
			//! Clean up internal data
			void Reset();
		public:
			//! Constructor
			KinematicModule();
			//! Constructor
			KinematicModule(const mkdKinematicTree&);			
			//! Destructor
			~KinematicModule();			
	
			//! Clones the module, including the internal kinematic tree
			/*! 
				\param justKinematicRelevantInfo allow you saving memory by not copying mesh data or other info that is not related to the kinematics need
			*/
			const misc::mwAutoPointer<mwMachsimMachDef::KinematicModule> Clone(const bool justKinematicRelevantInfo = false) const;

			//! Returns a map of ids and mapValue objects
			const mwMapValue::GlobalMap& GetTreeMap() const;
			//! Returns a map of ids and mapValue objects
			mwMapValue::GlobalMap& GetTreeMap();

			//! Returns the kinematic tree
			const mkdKinematicTree& GetTree() const;
			//! Returns the kinematic tree
			mkdKinematicTree& GetTree();

		private:		
			misc::mwAutoPointer<mkdKinematicTree>		m_moduleTree;		//! Module sub-tree
			mwMapValue::GlobalMap	m_moduleObjMap;		//! Associated container
		};

		//! Magazine container
		typedef std::map<misc::mwstring, KinematicModule>  Magazine;

		//! collision group definition
		struct pairCollisionGroup
		{
			misc::mwstring name;				//name of collision pair
			mwMachSimCollisionGroup	 group1;	//1-st group
			mwMachSimCollisionGroup	 group2;	//2-nd group

			pairCollisionGroup() { }
			const misc::mwAutoPointer<pairCollisionGroup> Clone() const
			{
				misc::mwAutoPointer<pairCollisionGroup> retObject =  new pairCollisionGroup;

				retObject->name = name;
				retObject->group1 = (*group1.Clone());
				retObject->group2 = (*group2.Clone());
				return retObject;
			}
			pairCollisionGroup(const pairCollisionGroup& toCopy)
				: name(toCopy.name)
				, group1(toCopy.group1)
				, group2(toCopy.group2)
			{ }
			const bool IsObjectDefined(const misc::mwstring& ID) const
			{
				return group1.IsObjectDefined(ID) || group2.IsObjectDefined(ID);
			}
		};

		//types
		typedef std::map < misc::mwstring, pairCollisionGroup >						CollisionGroupMap  ;
		typedef std::pair< misc::mwstring, pairCollisionGroup >						cg_pair ;
		typedef CollisionGroupMap::iterator											cg_iterator ;
		typedef CollisionGroupMap::const_iterator									cg_constiterator ;

		typedef mwMachSimPreprocessor                                               preprocessor;
		typedef std::list< preprocessor >											preprocessors;

		//!axis visibility as a pair of axis name , and its visibility
		typedef std::map< misc::mwstring, bool >									mwstringBoolMap;
		typedef mwstringBoolMap::iterator											mwstringBoolMapIterator ;

		//! list of file dependencies (e.g. STL files)
		typedef std::list< misc::mwFileName >										fileDependenciesList ;		

		//!Units - the machine unit of measure that is read from xml file
		typedef measures::mwUnitsFactory::Units                                     Units ;
		typedef std::list<misc::mwstring>											AxisList ;
		
		
			
		//########################################################################

		/*! Parameterized constructor
			\param unit machine definition unit of measure.
			\param notifications enables a special behavior of internal mkdKinematicTree instance.
			\param writeSTL enables saving of machine geometries meshes into their STLs. 			
		 */
		mwMachsimMachDef(const measures::mwUnitsFactory::Units unit, bool notifications, bool writeSTL = true);
		/*! Copy constructor
		*/
		mwMachsimMachDef(const mwMachsimMachDef& tc);

		/*!	Copy operator
		*/
		mwMachsimMachDef& operator=(const mwMachsimMachDef& tc);
	
	public:
		/*! Cloning method this is deep coping method
			Note: it does not register the plugins also. You will have to manually register them in resulting clone if you need them.
			\param justKinematicRelevantInfo allow you saving memory by not copying mesh data or other info that is not related to the kinematics need
		*/
		const misc::mwAutoPointer<mwMachsimMachDef> Clone(const bool justKinematicRelevantInfo = false )  const;

		//! Destructor
		~mwMachsimMachDef();		

		//! Returns whether the machine geometries meshes are saved or not.
		const bool GetWriteSTLsFlag()const;

		//! Enables saving of machine geometries meshes into their STLs. 			
		void SetWriteSTLsFlag(const bool state);

		//! Returns the machine name
		const misc::mwstring& GetMachineName() const ;

		//!return mwGenericPostDef
		const std::vector<mwGenericPostDef>& GetMachinePostDef() const;

		//!Sers mwGenericPostDef
    	void SetMachinePostDef( const std::vector<mwGenericPostDef>& postingConfigurations );

		//! Sets the machine name		
		void SetMachineName(const misc::mwstring& machName);

		//! Returns the machine controller name
		const misc::mwstring& GetMachineControllerName() const;

		//! Sets the machine controller name
		void SetMachineControllerName(const misc::mwstring& controller);

		/*! Returns the machine isometric view.
			\return existing view transform matrix
		*/
		const cadcam::mwHomogenousMatrix& GetViewTransform() const;
		
		/*! Sets the machine isometric view.
			\param toSet matrix to be used as view transform
		*/
		void SetViewTransform(const cadcam::mwHomogenousMatrix& toSet);

		/*! Adds and object under the given parent transformation.
			\param toAdd	kinematic object to add in machine definition.
			\param parent	parent of toAdd kinematic object.
			\param treeID	tree node where to look for the toAdd object.
		*/
		void AddObj(object toAdd, transform& parent, const misc::mwstring treeID = _T("")) ;

		/*! Adds an object from XML under the given parent transformation.
		\param toAdd	kinematic object to add in machine definition.
		\param parent	parent of toAdd kinematic object.
		\param treeID	tree node where to look for the toAdd object.
		*/
		void AddObjFromXMLReader(object toAdd, transform& parent, const misc::mwstring treeID = _T(""));
		
		/*! Query if the given kinematic module (e.g. <head>) exists in the magazine.
			\param treeID the name of the module to search for.
		 */
		bool IsKinematicModuleDefined( const misc::mwstring& treeID) const;

		/*! Adds a new kinematic module (e.g. <head>) to magazine. 
			\param id the name of a new magazine module. This is a unique id.
			If it already exists an exception will be thrown.
		 */
		void AddKinematicModule(const misc::mwstring& id);

		/*! Removes a kinematic module (e.g. <head>) from the magazine.
			\param treeID the name of the module
		 */
		void RemoveKinematicModule( const misc::mwstring& treeID );

		/*! Removes an object from the machine.
			\param toRemove	the name of the object to be removed.
			\param treeID the tree node where to search for the object to be removed.
		 */
		void RemoveObj( object toRemove, const misc::mwstring treeID = _T("") );

		/*! Removes an object from the machine and its associated file from the disk.
			\param toRemove	the name of the object to be removed.
			\param treeID the tree node where to search for the object to be removed.
		 */
		void RemoveObjAndAssociatedSTLs( object toRemove, const misc::mwstring treeID = _T("") );

		//! AddCollCheck
		/*! Add collision checking groups to a local map in machine definition
			\param ccID			collision checking ID
			\param group1		first collision group to be added.
			\param group2		second collision group to be added.
		*/
		void AddCollCheck(const misc::mwstring& ccID, 
						  const mwMachSimCollisionGroup& group1, 
						  const mwMachSimCollisionGroup& group2,
						  const bool doNotVerifyCollisionCheckingPairs = false
						  ) ;

		//! RemoveCollCheck
		/*! Remove collision checking definition
			\param ccID			collision checking ID to be removed.
		*/
		void RemoveCollCheck(const misc::mwstring& ccID);

		//! AddPreprocessor
		/*! Adds a preprocessor a local map in machine definition.
			\param preprocessor new object to be added
		*/
		void AddPreprocessor(const mwMachSimPreprocessor& preprocessor);

		/*! Retrieves a geometry searching by its name.
			\param geoName the geometry name to look for.
			\param treeID the node name where to search for. If empty, the entire
			machine definition will be used.
			\return the geometry that matches the search criteria.
		 */
		mwMachsimMachDef::geometry  GetGeometryByName(
			const misc::mwstring& geoName, 
			const misc::mwstring& treeID = _T("")) const ;


		/*! Retrieves a kinematic object searching by its name.
			\param toFind the kinematic object name to look for.
			\param treeID the node name where to search for. If empty, the entire
			machine definition will be used.
			\return the kinematic object that matches the search criteria.
		 */
		mwMachsimMachDef::object  GetObjectByName(
			const misc::mwstring& toFind, 
			const misc::mwstring& treeID = _T("")) const;


		/*! Adds a file to machine dependencies.
			\param fileName the path to the file to be added.
		 */
		void AddItemToMachineDefinitionFileDependencies(const misc::mwFileName& fileName);


		//! WriteKinematicObjects
		/*! This function is used internally to iterate all machine elements and
			save the machine definition into a xml file.

			\param	visitor		mkdKOSinConstVisitor derived class object that
			implements visiting mechanism.
		*/
		void WriteKinematicObjects(mkdKOSimConstVisitor& visitor) const ;


		//! WriteKinematicObjects
		/*! This function is used internally to iterate all elements of a given
			tree node and save the definition into a xml file.

			\param	visitor		mkdKOSinConstVisitor derived class object that
			implements visiting mechanism.
		*/
		void WriteKinematicObjects(mkdKOSimConstVisitor& visitor, const misc::mwstring& tree) const ;

		//! WritePreprocessors
		/*! Writes preprocessors when saving a machine definition
			\param	folder		destination folder
		*/
		void WritePreprocessors(const misc::mwstring& folder) const;

		//! GetAxisByName
		/*! Returns an object derived from mkdAxis with the name provided in the
			axisName parameter.
			\param	axisName the axis name to search for in the machine.
			\param treeID - the specific kinematic tree to be visited, if not specified, the main one will be used
			\return kinematic object derived from mkdAxis (e.g. mkdRotationalAxis,
			mkdTranslationalAxis)
		*/
		mwMachsimMachDef::axis GetAxisByName(const misc::mwstring& axisName,const misc::mwstring& treeID = _T("")) const ;
				
		/*! Returns a container containing all objects located under a given magazine node.
			If the empty string is provided then all objects in the machine will
			be provided.

			\param treeID the name of the magazine's kinematic module (e.g. <head>)
			where to narrow the search. If empty, the main tree will be used for searching.
			\return reference to kinematic objects map that match the search criteria.
		*/
		mwMapValue::GlobalMap& GetObjects(const misc::mwstring& treeID = _T("")) const;
		

		/*! GetCollisionGroupMap
			\return a const reference to collision group map contained by this machine definition			
		*/
		const mwMachsimMachDef::CollisionGroupMap& GetCollisionGroupMap() const ;
		
		/*! GetCollisionGroupMap
			\return a reference to collision group map contained by this machine definition			
		*/
		mwMachsimMachDef::CollisionGroupMap& GetCollisionGroupMap();
		
		/*! GetPreprocessors
			\return a const reference to the list of preprocessors contained by this machine definition
		*/
		const mwMachsimMachDef::preprocessors& GetPreprocessors() const ;

		/*
			Get mounting points 		
		*/
		const std::vector<misc::mwstring>& GetReferenceMountingPoints()const;

		/*
			Set mounting points 		
		*/
		void SetReferenceMountingPoints(std::vector<misc::mwstring>& mountings );


		/*! GetFileDependencies
			\return a const reference to file dependencies list contained by machine definition
		*/
		const mwMachsimMachDef::fileDependenciesList& GetFileDependencies() const ;
		
		/*! SetCollisionChesk
			\param collCheck reference to collision check that will be kept in machine definition
		*/
		void SetCollisions(const mwMachsimMachDef::CollisionGroupMap& collCheck);
		
		/*! SetPreprocessors
			\param preprocessors reference to preprocessors that will be kept in machine definition
		*/
		void SetPreprocessors(const preprocessors& preps) ;


		/*! Copy the magazine from the passed machine parameter into this machine definition.
			\param machsimMachDef the source where to take the magazine from.
		 */
		void CopyMagazine(const mwMachsimMachDef& machsimMachDef);

		
		/*! Scales the machine definition component objects	    
			\param units - the new unit of measure
			\param scaleFactor - the factor to scale objects with;
		*/
		void Scale(const Units units, const double& scaleFactor);
			
		/*! Visits kinematic object tree
			\param visitor - the actual visitor
			\param treeID - the specific kinematic tree to be visited, if not specified, the main one will be used
		*/
		void VisitTree(mkdKOVisitor& visitor, const misc::mwstring& treeID = _T(""));
		
		
		/*! Visits all the machine definition's kinematic objects, from all trees
			\param visitor - the actual visitor
		*/
		void VisitKinematicObjects(mkdKOVisitor& visitor) ;

		//! Returns the machine xml version.
		const float GetXMLVersion() const ;

		/*! Sets the machine xml version.
			\param xmlVer the version of machine definition xml file.
		 */
		void SetXMLVersion(const float xmlVer) ;

		//! Returns the latest xml version available.
		static const float GetUptodateXMLVersion();

		//! Returns post version available.
		const float GetPostVersion();
	
		/*! Returns the internal kinematic tree
			\return const pointer to the internal kinematic tree
		 */
		const mkdKinematicTree* GetTreePtr() const;

		/*! Returns the internal kinematic tree
			\return pointer to the internal kinematic tree
		 */
		mkdKinematicTree* GetTreePtr();

		/*! Retrieves a tree from the magazine identified by the given kinematic module (e.g. <head>) name.
			\param treeID the name of the module in the magazine.
			\return a const pointer to the identified kinematic tree.
		 */
		const mkdKinematicTree* GetKinematicModuleTreePtr(const misc::mwstring& treeID) const;

		/*! Retrieves the names of the magazine kinematic modules (e.g. <head>s)
			\param treeIds the array with magazine modules identifiers/names.
		 */
		void GetKinematicModuleIds(std::vector<misc::mwstring>& treeIds) const;

		/*! Replaces an object in the machine definition. The object can be located 
			in the main three or in one of the magazine kinematic modules (e.g. <head>)
			\param oldID the name of the object to be replaced.
			\param newID the name of the object that will replace the old one.
			\param treeID the module name where to search for both objects. 
			If empty, the main three will be used.
		 */
		void ReplaceObjectName(const misc::mwstring& oldID, const misc::mwstring& newID, const misc::mwstring& treeID);


		/*! Replaces one kinematic module (e.g. <head>) with the content of another module of the magazine.
			\param oldID the name of the module who's tree will be replaced.
			\param newID the name of the module who's tree will replace the other one.
		 */
		void ReplaceKinematicModuleName(const misc::mwstring& oldID, const misc::mwstring& newID);
		
		/*! Returns the kinematic tree identified by the given parameter.
			\param treeID the kinematic module (e.g. <head>) name who's kinematic tree will be returned.
			If empty, the main kinematic tree will be returned.
			\return the identified kinematic tree.
		 */
		mkdKinematicTree& GetTree(const misc::mwstring treeID = _T(""));
		
		/*! Returns the kinematic tree identified by the given parameter.
			\param treeID the kinematic module (e.g. <head>) name who's kinematic tree will be returned.
			If empty, the main kinematic tree will be returned.
			\return the identified kinematic tree.
		 */
		const mkdKinematicTree& GetTree(misc::mwstring treeID = _T("")) const;


		/*! Function returns the 1st level children of the id object. If empty,
			the 1st level children of the main kinematic tree will be returned.
			Optionally the id can be located in the kinematic module (e.g. <head>)
			identified by the tree parameter.
			
			\param id the object who's children will be returned.
			\param tree the module name where to search for id.
			\param children container to receive the identified object names.
		 */
		void GetChildren(const misc::mwstring& id, 
			const misc::mwstring& tree, 
			std::vector<misc::mwstring>& children);

		
		/*! Inserts a tree under the given parent transformation.
			\param toAdd the kinematic tree to be added.
			\param parent the transformation where the tree will be added.
		 */
		void InsertTree(const machsim::mkdKinematicTree& toAdd, transform& parent);

		/*! Inserts a tree under the given parent transformation.
			\param toAdd an iterator to the kinematic tree node to be added.
			\param parent the transformation where the tree will be added.
		 */
		void InsertTree(constTreeID& toAdd, transform& parent);

		/*! Inserts an object under the given parent transformation.
			\param toAdd the kinematic element to be added.
			\param parent the parent transform under which the element will be 
			added.
		 */
		void InsertObject(object toAdd, transform& parent);

		/*! Removes a kinematic element from the main tree identified by the 
			given parameter together will all its children.
			\param toFind the node to be removed and all its children.
		 */
		void RemoveChildren(const misc::mwstring& toFind);

		/*
			remove mounting points  

		*/
		void RemoveMountingPoints();

		/*! Test if the given object exists in the main tree or in the given 
			kinematic module (e.g. <head>), if a non-empty treeID is provided.
			\param	objectID to search for.
			\param treeID the module name where to search for the object. If empty,
			the main tree will be searched.
			\return true if the referenced object exists.
		*/
		const bool IsObjectDefined(const misc::mwstring& objectID, const misc::mwstring& treeID = _T("")) const;

		
		/*! Test if the given object exists in the main tree or in any of the 
			existing magazine's kinematic modules (e.g. <head>s)
			\param	objectID to search for.			
			\return true if the referenced object exists.
		*/
		bool IsObjectDefinedInAnyTree(const misc::mwstring& objectID) const;


		/*! Test if the given object exists only in one of the existing magazine's 
			kinematic modules (e.g. <head>s)
			\param	objectID to search for.			
			\return true if the referenced object exists is not found in the main
			kinematic tree but in one of the magazine modules.
		*/
		bool IsObjectDefinedOnlyInTheMagazine(const misc::mwstring& objectID) const;

		
		/*! Searches for an object and returns its node. 

			\param toFind the name of the object to be searched for.
			\param treeID the name of the magazine's kinematic module (e.g. <head>)
			where to narrow the search. If empty, the main tree will be used for searching.
			\return on success it returns the node of the identified object, otherwise
			an exception will be thrown.
		*/
		const mwMachsimMachDef::treeID GetIt(const misc::mwstring& toFind, const misc::mwstring& treeID = _T("")) const;


		/*! Searches for an initial stock in the magazine's kinematic module (e.g. <head>)
			referenced by treeID or if empty, in the main tree. The search will return 
			an initial stock that is a sibling of the stock object identified by stockID.
			
			\param stockID the name of the stock that identifies the branch where
			to search for an initial stock.
			\param treeID the name of the module to narrow the search. If empty,
			the main tree will be used.
			\return on success the identified object will be returned, otherwise
			a NULL auto pointer.
		 */
		misc::mwAutoPointer<machsim::mkdInitialStock> GetInitialStock(
			const misc::mwstring& stockID, 
			const misc::mwstring& treeID = _T("") ) const;


		/*! Searches for a stock in the magazine's kinematic module (e.g. <head>)
			referenced by treeID or if empty, in the main tree. The search will 
			return a stock that is a sibling of the workpiece object identified by workpieceID.
			
			\param workpieceID the name of the workpiece that identifies the 
			branch where to search for an existing stock.
			\param treeID the name of the module (e.g. <head>) to narrow the search. 
			If empty then the main tree will be used.
			\return on success the identified object will be returned, otherwise
			a NULL auto pointer.
		 */
		misc::mwAutoPointer<machsim::mkdStockGeometry> GetStock(
			const misc::mwstring& workpieceID, 
			const misc::mwstring& treeID = _T("")) const;

		/*! Searches for a workpiece in the magazine's kinematic module (e.g. <head>)
		referenced by treeID or if empty, in the main tree. The search will
		return a workpiece that is a sibling of the workpiece object identified by workpieceID.

		\param workpieceID the name of the workpiece that identifies the
		branch where to search for an existing stock.
		\param treeID the name of the module (e.g. <head>) to narrow the search.
		If empty then the main tree will be used.
		\return on success the identified object will be returned, otherwise
		a NULL auto pointer.
		*/
		misc::mwAutoPointer<machsim::mkdWorkPiece> GetWorkpiece(
			const misc::mwstring& workpieceID,
			const misc::mwstring& treeID = _T("")) const;

		/*! Method will call into param tocall method CallForElement for each object
			found in the machine or treeId branch that is identified by passed
			type parameter.
			\param tocall implements CallForElement callback function
			\param type used to identified machine objects
			\param treeId specifies the location where to search the objects.
		 */
		void IterateThroughObjects(mwMapIteratorInterface& tocall, 
			const mwMapValue::dicts& type, 
			const misc::mwstring& treeId = _T("") ) const ;
		
		/*! Searches in the magazine's kinematic module (e.g. <head>) the object id, and if it find it,
			returns the kinematic module (e.g. <head>) Id
			\param objectId the name of the object that we are searching
			\return the kinematic module (e.g. <head>) Id , otherwise ("")
		 */
		const misc::mwstring GetKinematicModuleContainingId(const misc::mwstring &objectId) const;
	
		/*! Searches in the magazine's kinematic module (e.g. <head>) the if is containing an workpiece
			\param treeID the name of the magazine's kinematic module (e.g. <head>) where we are searching the workpiece
			\return true if we are found one workpiece and false if not
		 */
		const bool IsKinematicModuleContainingWorkpiece( machsim::mkdKinematicTree::const_treeID treeID );
		
		/*! Searches in the magazine's kinematic module (e.g. <head>) the stock object and is returning it's Id
			\param treeID the name of the magazine's kinematic module (e.g. <head>) where we are searching the stock
			\return the stock Id , otherwise ("")
		 */
		const misc::mwstring GetStockIdFromKinematicModule( const misc::mwstring &treeId );

		/*! Searches in the magazine's kinematic module (e.g. <head>) the workpiece object and is returning it's Id
			\param treeID the name of the magazine's kinematic module (e.g. <head>) where we are searching the workpiece
			\return the workpiece Id , otherwise ("")
		 */
		const misc::mwstring GetWorkpieceName(const misc::mwstring &treeId = _T(""));
		
		/*! Searches in the childrens of currentId if we have an object that is tool
			\param currentId the name of the object of which childrens we will search 
			\return true if we are found one tool and false if not
		 */
		const bool IsKinematicModuleContainingTool( machsim::mkdKinematicTree::const_treeID currentId );

		/*! Searches in the childrens of currentId if we have an object that is tool
			\param currentId the name of the object of which childrens we will search 
			\return the first tool Id , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedToolName( machsim::mkdKinematicTree::const_treeID currentId );

		/*! Searches in the childrens of currentId if we have an object that is stock
			\param currentId the name of the object of which childrens we will search 
			\return the first stock Id , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedStockName( machsim::mkdKinematicTree::const_treeID currentId );

		/*! Searches in the childrens of currentId if we have an object that is workpiece
			\param currentId the name of the object of which childrens we will search 
			\return the first workpiece Id , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedWorkpieceName( machsim::mkdKinematicTree::const_treeID currentId );
		
		/*! Searches in the childrens of currentId if we have an object that is fixture
			\param currentId the name of the object of which childrens we will search 
			\return the first fixture Id , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedFixtureName( machsim::mkdKinematicTree::const_treeID currentId );
		
		/*! Searches in the childrens of currentId if we have an object that is mountAdapter
			\param currentId the name of the object of which childrens we will search 
			\return the first mountAdapter Id , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedMountAdapterName( machsim::mkdKinematicTree::const_treeID currentId );

		/*! Searches in the childrens of currentId if we have an object that have the searched type
			\param currentId the name of the object of which childrens we will search 
			\param searchedType the type of the object of which childrens we will search 
			\return the first found object Id that have the searched type , otherwise ("")
		 */
		const misc::mwstring GetFirstFoundedObjectTypeName( machsim::mkdKinematicTree::const_treeID currentId, const machsim::mwMapValue::dicts searchedType );

		//! Clears the content of the machine definition.
		void Clear();

		//! Register a machine simulator plugin
		pluginID RegisterPlugin(const plugin& toRegister);

		//! Remove a machine simulator plugin
		void UnregisterPlugin(pluginID& toUnregister);

		//! Remove all machine simulator plugins
		void UnregisterAllPlugins();

	protected:
	private:
		/*! Copy a kinematic tree from the given machine definition into this object.
			The given tree will be copied or the sub-tree identified by id if not
			empty. The kinematic will be copied at top level into this object.

			\param machsimMachDef the source from where the kinematic will be copied.
			\param tree the node of the kinematic to be copied.
			\param id an element existing under tree node that is used to identify
			the sub-tree to be copied, if not NULL.
		 */
		void CopyTree(const mwMachsimMachDef& machsimMachDef, const misc::mwstring& tree, const misc::mwstring& id);
			/*! Clone a kinematic tree from the given machine definition into this object.
			The given tree will be cloned or the sub-tree identified by id if not
			empty. The kinematic will be copied at top level into this object.

			\param machsimMachDef the source from where the kinematic will be cloned.
			\param tree the node of the kinematic to be cloned.
			\param id an element existing under tree node that is used to identify
			the sub-tree to be copied, if not NULL.
		 */
		void TreeIndexParser(mwMachsimMachDef& machsimMachDef, const misc::mwstring& tree, const misc::mwstring& id) const;
		//! Returns true if the given object exists in the map.
		const bool IsObjectDefined(const misc::mwstring& objectID, const mwMapValue::GlobalMap& objectMap) const;
		
		//! Recursive function that iterates all machine objects and passes them to visitor for processing.
		void VisitKinematicObjectsForWriter(mkdKOSimConstVisitor& visitor, const object& parent) const;

		//! Recursive function that iterates all machine objects and passes them to visitor for processing.
		void VisitKinematicObjectsForWriter(mkdKOSimConstVisitor& visitor, const misc::mwstring& parent, const misc::mwstring& tree) const;
	
		//! Fills in the given container with the internal kinematic elements.
		void BuildGlobalMap(mwMapValue::GlobalMap& gmap, mkdKinematicTree& toCopy);

		//! Fills in the given container with the kinematic elements under the given tree iterator.
		void BuildGlobalMap(mwMapValue::GlobalMap& gmap, treeID toCopyNodeIt);

		//! Scales all kinematic elements of the main tree or of the magazine's module (e.g. <head>) identified by treeID.
		void ScaleTree(const Units units, const double& scaleFactor, const misc::mwstring& treeID = _T("") );

		//! Validate collision group object
		bool ValidateCollisionGroupObject(const misc::mwstring& objectID);
		

#pragma warning(push)
#pragma warning(disable:4251)
		//!kinematic tree structure - a hierarchy of kinematic objects 
		mkdKinematicTree::Ptr					m_tree;

		//! machine magazine (section)
		mutable Magazine						m_magazine;

		//!a map of kinematic objects - this keep the objects in machine definition
		mutable mwMapValue::GlobalMap			m_objects;

		//! machine simulator plugins
		plugins									m_plugins;

		//!collision group map - keep collision group organized
		CollisionGroupMap						m_cgMap;

		//!preprocessors
		preprocessors                           m_preprocessors;

		//!file dependencies list 
		fileDependenciesList					m_machDefFileDependencies;

		std::vector <mwGenericPostDef>			m_postingConfigurations;
		std::vector<misc::mwstring>				m_referencedMountingPoints;
#pragma warning(pop)

		//! internal kinematic tree is allowed (or not) to receive notifications from internal members
		bool									m_notifications;
		
		//!machine name
		misc::mwstring							m_machineName ;

		//!machine controller name
		misc::mwstring							m_machineControllerName;

		//! machine view matrix
		cadcam::mwHomogenousMatrix				m_viewTransform;

		//xml version as present in xml file
		float                                   m_xmlVersion;
		static const float                      m_uptodateXMLVersion;

		//! indicates whether to save stl files when saving internal xml
		bool									m_writeSTL;	

		float                                   m_postVersion;

	}; // class


}; // namespace
#endif	//	MW_MWMACHSIMMACHDEF_HPP_
