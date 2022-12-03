// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW4AXMACHDEF_HPP_
#define MW_MW4AXMACHDEF_HPP_

#include "mwMachDef.hpp"

namespace post
{
	//! this class stores the params needed for defining a machine
	class MW_5AXUTIL_API mw4axMachDef : public mwMachDef
	{
	public:
		enum MachType
		{
			HEAD=0,
			TABLE=1
		};
		//! default constructor
		/*! Creates a post machine definition using 4x4 matrix as spindle (holderTransform)
			MachType = HEAD;
			NumberOfAxes = MACHINE_4AXIS;
			RotAxisDir = vector3d(0, 0, -1);
			RotAxisBasePt = point3d(0, 0, 0);
			RotAxisMinLimit = -100000;
			RotAxisMaxLimit = 100000;
		*/
		mw4axMachDef();
		//! Virtual destructor
		~mw4axMachDef();
		//! Constructor - creates a post machine definition using spindle as vector
		/*!
			\param machineKinematicType define 4axis machine kinematic type
			\param units defines units used
			\param spindleDirection defines spindle
			\param rotAxisDirection defines rotary direction
			\param rotAxisBasePoint defines rotary base point
			\param vRotAxisMinLimit defines rotary axis minimum limit
			\param vRotAxisMaxLimit defines rotary axis maximum limit
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
		mw4axMachDef( 
			const MachType& machineKinematicType,
			const Units units,
			const vector3d& spindleDirection,
			const vector3d& rotAxisDirection,
			const point3d& rotAxisBasePoint,
			const double vRotAxisMinLimit,
			const double vRotAxisMaxLimit,
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
			\param machineKinematicType define 4axis machine kinematic type
			\param units defines units used
			\param rotAxisDirection defines rotary direction
			\param rotAxisBasePoint defines rotary base point
			\param vRotAxisMinLimit defines rotary axis minimum limit
			\param vRotAxisMaxLimit defines rotary axis maximum limit
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
		mw4axMachDef(
			const MachType& machineKinematicType,
			const Units units,
			const vector3d& rotAxisDirection,
			const point3d& rotAxisBasePoint,
			const double vRotAxisMinLimit,
			const double vRotAxisMaxLimit,
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
		mw4axMachDef(const mw4axMachDef& toCopy);
		//! Copy operator
		const mw4axMachDef& operator =(const mw4axMachDef& toCopy);
		//! Comparison operator
		/* Compares two mw4axMachDef objects
			\return true it the compared objects are equal member by member, 
			\false otherwise
		*/
		const bool operator == (const mw4axMachDef& toCompare) const;
		//! Gets MachType
		/*! 			
			\returns the MachType
		*/
		const MachType& GetMachType() const;
		//! Sets MachType
		void SetMachType(const MachType& machineType);
		//! Gets rotary axis direction
		/*! 			
			\returns the RotAxisDir
		*/
		const vector3d& GetRotAxisDir() const;
		//! Sets rotary axis direction
		void SetRotAxisDir(const vector3d& rotAxisDir);
		//! Gets rotary axis base point
		/*! 			
			\returns the RotAxisBasePt
		*/
		const point3d& GetRotAxisBasePt() const;
		//! Sets rotary axis base point
		void SetRotAxisBasePt(const point3d& rotAxisBasePt);
		//! Gets rotary minimum limit (in degrees)
		/*! 			
			\returns the RotAxisMinLimit
		*/
		const double GetRotAxisMinLimit() const;
		//! Sets rotary minimum limit (in degrees)
		void SetRotAxisMinLimit(const double RotAxisMinLimit);
		//! Gets rotary maximum limit (in degrees)
		/*! 			
			\returns the RotAxisMaxLimit
		*/
		const double GetRotAxisMaxLimit() const;
		//! Sets rotary maximum limit (in degrees)
		void SetRotAxisMaxLimit(const double RotAxisMaxLimit);
		//! Visitor method for mw4axMachDef class
		virtual void AcceptVisitor( mwMachineVisitor &visitor ) const;
		//! Gets a clone of machine
		/*!
			Return a mwMachDef autopointer to current object (an instance of mw3axMachDef, mw4axMachDef, mw5axMachDef, mw6axMachDef, mw6axCSMachDef)
		*/
		const mwMachDefPtr Clone() const;
		//! Normalize vectors (rotarty axis direction and spindle) 
		virtual void NormalizeVectors();
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
		//! scaled all measurable data of the machine definition by the given scale factor
		/*!
			\param units not used here 
			\param scaleFactor  the machine definition is scaled by the scale factor
		*/
		void Scale(const Units units,const double& scaleFactor);
		//! type of the 4 axis machine kinematics (based on where the rotary axis are mechanically built)
		MachType		m_machineType;
		//! rotational axis direction vectors representing the rotation
		vector3d		m_rotAxisDir;
		//! 3d points describing the base point of rotation. Note they could be anywhere on the rotation line
		point3d			m_rotAxisBasePt;
		//! minimum limits in degrees for rotary axis
		double			m_RotAxisMinLimit;
		//! maximum limits in degrees for rotary axis
		double			m_RotAxisMaxLimit;
	};
	//! Defines an autopointer to mw4axMachDef class
	typedef misc::mwAutoPointer<mw4axMachDef> mw4axMachDefPtr;
}

#endif
