// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHINEKINEMATICSPROCESSORPLUGIN_HPP_
#define MW_MWMACHINEKINEMATICSPROCESSORPLUGIN_HPP_
#include "mkdKinematicObject.hpp"
#include "mwStringConversions.hpp"
#include "mwExtendedMoveAttribute.hpp"


namespace machsim
{
	class mwMachineKinematicsProcessorPlugin
	{
	public:
		
		enum oorType
		{
			MW_OOR_UNDERFLOW,
			MW_OOR_OVERFLOW,
			MW_OOR_MISMATCH
		};	
		

		//!Start Move
		/*!
			This function is called before all changed objects are enumerated
		*/
		virtual void StartMove()
		{
		};
		
		//!Object changed
		/*!
			This function is changed for every object that has changed
			since last call
		*/
		virtual void ObjectChanged( const mkdKinematicObject &/*changedObject*/, 
			const mkdHomogenousMatrix &/*startState*/, 
			const mkdHomogenousMatrix &/*endState*/) 
		{
		};

		//!End Move
		/*!
			This function is called after all changed objects are enumerated
		*/
		virtual void EndMove()
		{
		};

		virtual void AfterMove()
		{
		};

		//!Out of range
		/*!
			This function is called if one of the following
			events occur:
			- Value underflow. Passed value is smalled than
			the minimum allowed value
			- Value overflow. Passed value is greater than 
			the maximum allowed value
			- Value out of range. A not allowed value has been
			specified for a discrete axis
		*/
		virtual void ValueOutOfRange( const oorType &/*type*/, 
			const misc::mwstring &/*valueName*/,
			const double &/*value*/ )
		{
		};


		virtual void ObjectAdded( const mkdKinematicObject &addedObject, 
			const mkdKinematicObject *parentObject ) = 0;

		virtual void ObjectRemoved( const mkdKinematicObject &addedObject ) = 0;
		
		virtual void Reset() 
		{
		};
		
		virtual ~mwMachineKinematicsProcessorPlugin(void) 
		{
		};


	protected:
	private:
	};

};
#endif	//	MW_MWMACHINEKINEMATICSPROCESSORPLUGIN_HPP_
