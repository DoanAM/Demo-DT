// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDKINEMATICTREE_HPP_
#define MW_MKDKINEMATICTREE_HPP_
#pragma warning(push)
#pragma warning(disable:4275)
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwTree.hpp"
#include "mwAutoPointer.hpp"
#include "mkdKinematicObject.hpp"
#include <map>
#include <list>


namespace machsim
{	
	class MW_SIMUTIL_API mkdKinematicTree : public mkdKinematicTreeInterface
	{
	public:
		typedef misc::mwAutoPointer<mkdKinematicTree>		Ptr;
		typedef misc::mwAutoPointer<mkdKinematicObject>		kinematicEntry;
		typedef misc::mwTree<kinematicEntry>				def;
		typedef misc::mwTreeNode<kinematicEntry>::nodeID	treeID;
		typedef misc::mwTreeNode<kinematicEntry>::constChildrenIterator
															const_treeID;
		
		//! Kinematic change details.
		struct objSceneChange
		{
			objSceneChange():_changeCount(0) 
			{
			};

			mkdHomogenousMatrix		_startMatrix;
			mkdHomogenousMatrix		_endMatrix;
			unsigned long			_changeCount;
		};


		typedef std::map<treeID, objSceneChange>			sceneChange;	
		typedef sceneChange::iterator						sceneChangeIterator;
		typedef sceneChange::const_iterator					sceneChangeConstIterator;

		
		/*! Parameterized constructor
			\param receivesNotificationsFromMembers enables matrix propagation
			from the node that has changed to its children.
		 */
		mkdKinematicTree(const bool receivesNotificationsFromMembers = true);

		//! Destructor
		~mkdKinematicTree();

		//! Copy constructor
		mkdKinematicTree(const mkdKinematicTree& copy);

		//! Copy operator
		const mkdKinematicTree& operator=(const mkdKinematicTree& toCopy);

		//! Clone 
		/*! 
			\param justKinematicRelevantInfo allow you saving memory by not copying mesh data or other info that is not related to the kinematics need
		*/
		const misc::mwAutoPointer<mkdKinematicTree> Clone( const bool justKinematicRelevantInfo = false ) const;
		
		/*! Inserts an object into the tree. 
			\param toInsert the object to insert into the tree
			\param parentNode parent node of the current object. 0 to insert
			current object on the top level
			\returns id of the inserted object
		*/
		treeID InsertObject(kinematicEntry& toInsert, treeID parentNode);
		
		/*! Inserts an object into the tree on the top level.
			\param toInsert the object to insert into the tree.			
			\returns id of the inserted object.
		*/
		treeID InsertObject(kinematicEntry& toInsert);
				
		/*! Removes an object from the tree. If the object has child nodes 
			these nodes are also going to be removed.
			\param toRemove id of the object to remove from the tree
			\remark if no object with the specified id was found in the tree
			the function silently ignores this fact
		*/
		void RemoveObject(treeID toRemove);
		
		//!Reset tree
		/*! Removes all objects and resets everything */
		void Reset();
		
		//!Reset scene change
		void ResetSceneChange();

		//! Returns an iterator to the first element in changed container.
		sceneChangeIterator GetSceneChangeBegin();

		//! Returns an iterator to the first element in changed container.
		sceneChangeConstIterator GetSceneChangeBegin() const;

		//! Returns an iterator to the past-the-end element in the changed container.
		sceneChangeIterator GetSceneChangeEnd();

		//! Returns an iterator to the past-the-end element in the changed container.
		sceneChangeConstIterator GetSceneChangeEnd() const;

		//! Returns the internal kinematic tree.
		const misc::mwTree<kinematicEntry>& GetInternalTree() const;

		//! Returns the internal kinematic tree.
		misc::mwTree<kinematicEntry>& GetInternalTree(); 

		//! Enables or disables the matrix change notifications.
		void EnableMatrixChangeFeedBack(const bool enable);

		//!Returns the allowance for sending matrix change notifications.
		const bool IsMatrixChangeFeedBackEnabled() const;

		//!Toggles the repositioning mode flag.
		void ToggleRepositioningMode(const bool toggle);

		//!Returns the repositioning mode flag.
		const bool IsRepositioningModeToggled() const;

	protected:
	private:		

		//!Propagates the object matrix to its children
		virtual void PropagateMatrixToChildren(
			const mkdKinematicObject &thisObject, 
			const mkdKinematicObject::matrix &toPropagate );

		//!Processes the current matrix of an object
		virtual void MatrixChangeFeedback( 
			const mkdKinematicObject &thisObject,
			const mkdKinematicObject::matrix &oldState, 
			const mkdKinematicObject::matrix &currentState );

		//!Clone the given tree
		void CopyTree (const mkdKinematicTree& toCopy);
		void CopyTreeRecursive(misc::mwTreeNode< kinematicEntry >::constChildrenIterator toCopyNodeIt,
			treeID myNodeIt);
		void CloneTreeRecursive(misc::mwTreeNode< kinematicEntry >::constChildrenIterator toCopyNodeIt,
			treeID myNodeIt, misc::mwAutoPointer<mkdKinematicTree>& retObject, const bool justKinematicRelevantInfo) const;



	private:
		typedef misc::mwTreeNode< kinematicEntry >			kinematicNode;
		typedef std::map< mkdKinematicObject *, treeID >	treeElemMap;

#pragma warning(push)
#pragma warning(disable:4251)
		misc::mwTree< kinematicEntry >						m_tree;
		treeElemMap											m_elements;		
		sceneChange											m_lastChanges;
#pragma warning(pop)
		bool												m_enableMatrixChangeFeedBack;
		bool												m_repositioningMode;
		bool												m_receivesNotificationsFromMembers;		
	};
}

#pragma warning(pop)
#endif	//	MW_MKDKINEMATICTREE_HPP_
