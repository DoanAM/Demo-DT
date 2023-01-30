// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW3AXMACHDEF_HPP_
#define MW_MW3AXMACHDEF_HPP_

#include "mwMachDef.hpp"

namespace post
{
	//! This class stores the params needed for defining a machine
	class MW_5AXUTIL_API mw3axMachDef : public mwMachDef
	{
	public:
		//! Default constructor
		/*! Creates a post machine definition using 4x4 matrix as spindle (holderTransform)
			NumberOfAxes = MACHINE_3AXIS;
		*/
		mw3axMachDef();

		//! Virtual destructor
		~mw3axMachDef();
		
		//! Constructor - creates a post machine definition using spindle as vector
		/*!
			\param units defines units used
			\param spindleDirection defines spindle
			\param TransAxisMinLimit defines minimum translations limit
			\param TransAxisMaxLimit defines maximum translations limit
			\param translationX defines X translation direction
			\param translationY defines Y translation direction
			\param translationZ defines Z translation direction
			\param workpieceTransform defines a 4x4 transformation matrix for workpiece
			\param holderTransform defines a 4x4 transformation matrix for holder
			\param doValidations activate machine validation on constructor
			\param type defines machine type
		*/
		mw3axMachDef( 
			const Units units,
			const vector3d& spindleDirection,
			const point3d& TransAxisMinLimit = -LimitTranslation(),
			const point3d& TransAxisMaxLimit = LimitTranslation(),
			const vector3d& translationX = vector3d(1., 0., 0.),
			const vector3d& translationY = vector3d(0., 1., 0.),
			const vector3d& translationZ = vector3d(0., 0., 1.),
			const mwMatrix4dPtr& workpieceTransform = MW_NULL,
			const mwMatrix4dPtr& holderTransform = MW_NULL,
			const bool doValidations = true,
			const MachineDefinitionType type = MILLING_MACHINE);

		//! Constructor - creates a post machine definition using 4x4 matrix as spindle (holderTransform)
		/*!
			\param units defines units used
			\param TransAxisMinLimit defines minimum translations limit
			\param TransAxisMaxLimit defines maximum translations limit
			\param translationX defines X translation direction
			\param translationY defines Y translation direction
			\param translationZ defines Z translation direction
			\param workpieceTransform defines a 4x4 transformation matrix for workpiece
			\param holderTransform defines a 4x4 transformation matrix for holder
			\param doValidations activate machine validation on constructor
			\param type defines machine type
		*/
		mw3axMachDef(
			const Units units,
			const point3d& TransAxisMinLimit = -LimitTranslation(),
			const point3d& TransAxisMaxLimit = LimitTranslation(),
			const vector3d& translationX = vector3d(1., 0., 0.),
			const vector3d& translationY = vector3d(0., 1., 0.),
			const vector3d& translationZ = vector3d(0., 0., 1.),
			const mwMatrix4dPtr& workpieceTransform = MW_NULL,
			const mwMatrix4dPtr& holderTransform = MW_NULL,
			const bool doValidations = true,
			const MachineDefinitionType type = MILLING_MACHINE);
	
		//! Copy constructor
		mw3axMachDef(const mw3axMachDef& toCopy);
		
		//! Copy operator
		const mw3axMachDef& operator = (const mw3axMachDef& toCopy);
		
		//! Comparison operator
		/* Compares two mw3axMachDef objects
			\return true it the compared objects are equal member by member,
			\false otherwise
		*/
		const bool operator == (const mw3axMachDef& toCompare) const;
		
		//! Visitor method for mw3axMachDef class
		virtual void AcceptVisitor( mwMachineVisitor &visitor ) const;
		
		//! Gets a clone of machine
		/*!
			Return a mwMachDef autopointer to current object (an instance of mw3axMachDef, mw4axMachDef, mw5axMachDef, mw6axMachDef, mw6axCSMachDef)
		*/
		const mwMachDefPtr Clone() const;
		
		//! Validate current machine, it is defined wrong then an exception is thrown
		virtual void Validate() const;
		
		//! Sets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		virtual void SetMachineDefinitionType(const MachineDefinitionType type);
		
		//! Gets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		virtual MachineTurningType GetMachineTurningType() const;
	protected:
		//! Scaled all measurable data of the machine definition by the given scale factor
		/*!
			\param units not used here 
			\param scaleFactor  the machine definition is scaled by the scale factor
		*/
		void Scale(const Units units,const double& scaleFactor);
	};
	//! Defines an autopointer to mw3axMachDef class
	typedef misc::mwAutoPointer<mw3axMachDef> mw3axMachDefPtr;
}

#endif