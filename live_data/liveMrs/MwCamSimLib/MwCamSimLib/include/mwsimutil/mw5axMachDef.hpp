// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW5AXMACHDEF_HPP_
#define MW_MW5AXMACHDEF_HPP_

#include "mwMachDef.hpp"

namespace post
{
	//! this class stores the params needed for defining a machine
	class MW_5AXUTIL_API mw5axMachDef : public mwMachDef
	{
	public:
		//! Specify supported 5axis machine types
		enum MachType
		{
			TABLE_TABLE_LEGACY=0, // outdated
			HEAD_HEAD=1,
			HEAD_TABLE=2,
			TABLE_TABLE_NEW=3
		};
		//! default constructor
		/*! Creates a post machine definition using 4x4 matrix as spindle (holderTransform)
			MachType = HEAD_TABLE;
			NumberOfAxes = MACHINE_5AXIS;
			RotAxisDir0 = vector3d(0, 0, -1);
			RotAxisDir1 = vector3d(0, -1, 0);
			RotAxisBasePt0 = point3d( 0,0,0 );
			RotAxisBasePt1 = point3d( 0,0,0 );
			RotAxisMinLimit0 = -100000;
			RotAxisMinLimit1= -100000;
			RotAxisMaxLimit0 = 100000;
			RotAxisMaxLimit1 = 100000;
		*/
		mw5axMachDef();
		//! Virtual destructor
		~mw5axMachDef();
		//! Constructor - creates a post machine definition using spindle as vector
		/*!
			\param machineKinematicType define 5axis machine kinematic type
			\param units defines units used
			\param spindleDirection defines spindle
			\param rotAxisDirection0 defines first rotary direction
			\param rotAxisDirection1 defines second rotary direction
			\param rotAxisBasePoint0 defines first rotary base point
			\param rotAxisBasePoint1 defines second rotary base point
			\param vRotAxisMinLimit0 defines first rotary axis minimum limit
			\param vRotAxisMinLimit1 defines second rotary axis minimum limit
			\param vRotAxisMaxLimit0 defines first rotary axis maximum limit
			\param vRotAxisMaxLimit1 defines second rotary axis maximum limit
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
		mw5axMachDef( 
			const MachType& machineKinematicType,
			const Units units,
			const vector3d& spindleDirection,
			const vector3d& rotAxisDirection0,
			const vector3d& rotAxisDirection1,
			const point3d& rotAxisBasePoint0,
			const point3d& rotAxisBasePoint1,
			const double vRotAxisMinLimit0,
			const double vRotAxisMinLimit1,
			const double vRotAxisMaxLimit0,
			const double vRotAxisMaxLimit1,
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
			\param machineKinematicType define 5axis machine kinematic type
			\param units defines units used
			\param rotAxisDirection0 defines first rotary direction
			\param rotAxisDirection1 defines second rotary direction
			\param rotAxisBasePoint0 defines first rotary base point
			\param rotAxisBasePoint1 defines second rotary base point
			\param vRotAxisMinLimit0 defines first rotary axis minimum limit
			\param vRotAxisMinLimit1 defines second rotary axis minimum limit
			\param vRotAxisMaxLimit0 defines first rotary axis maximum limit
			\param vRotAxisMaxLimit1 defines second rotary axis maximum limit
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
		mw5axMachDef(
			const MachType& machineKinematicType,
			const Units units,
			const vector3d& rotAxisDirection0,
			const vector3d& rotAxisDirection1,
			const point3d& rotAxisBasePoint0,
			const point3d& rotAxisBasePoint1,
			const double vRotAxisMinLimit0,
			const double vRotAxisMinLimit1,
			const double vRotAxisMaxLimit0,
			const double vRotAxisMaxLimit1,
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
		mw5axMachDef(const mw5axMachDef& toCopy);
		//! Copy operator
		const mw5axMachDef& operator =(const mw5axMachDef& toCopy);
		//! Comparison operator
		/* Compares two mw5axMachDef objects
			\return true it the compared objects are equal member by member, 
			\false otherwise
		*/
		const bool operator == (const mw5axMachDef& toCompare) const;
		//! Gets MachType
		/*! 			
			\returns the MachType
		*/
		const MachType& GetMachType() const;
		//! Sets MachType
		void SetMachType(const MachType& machineType);
		//! Gets first rotary axis direction
		/*! 			
			\returns the RotAxisDir0
		*/
		const vector3d& GetRotAxisDir0() const;
		//! Sets first rotary axis direction
		void SetRotAxisDir0(const vector3d& rotAxisDir);
		//! Gets second rotary axis direction
		/*! 			
			\returns the RotAxisDir1
		*/
		const vector3d& GetRotAxisDir1() const;
		//! Sets second rotary axis direction
		void SetRotAxisDir1(const vector3d& rotAxisDir);
		//! Gets first rotary axis base point
		/*! 			
			\returns the RotAxisBasePt0
		*/
		const point3d& GetRotAxisBasePt0() const;
		//! Sets first rotary axis base point
		void SetRotAxisBasePt0(const point3d& rotAxisBasePt);
		//! Gets second rotary axis base point
		/*! 			
			\returns the RotAxisBasePt1
		*/
		const point3d& GetRotAxisBasePt1() const;
		//! Sets second rotary axis base point
		void SetRotAxisBasePt1(const point3d& rotAxisBasePt);
		//! Gets first rotary minimum limit (in degrees)
		/*! 			
			\returns the RotAxisMinLimit0
		*/
		const double GetRotAxisMinLimit0() const;
		//! Sets first rotary minimum limit (in degrees)
		void SetRotAxisMinLimit0(const double RotAxisMinLimit);
		//! Gets second rotary minimum limit (in degrees)
		/*! 			
			\returns the RotAxisMinLimit1
		*/
		const double GetRotAxisMinLimit1() const;
		//! Sets second rotary minimum limit (in degrees)
		void SetRotAxisMinLimit1(const double RotAxisMinLimit);
		//! Gets first rotary maximum limit (in degrees)
		/*! 			
			\returns the RotAxisMaxLimit0
		*/
		const double GetRotAxisMaxLimit0() const;
		//! Sets first rotary maximum limit (in degrees)
		void SetRotAxisMaxLimit0(const double RotAxisMaxLimit);
		//! Gets second rotary maximum limit (in degrees)
		/*! 			
			\returns the RotAxisMaxLimit1
		*/
		const double GetRotAxisMaxLimit1() const;
		//! Sets second rotary maximum limit (in degrees)
		void SetRotAxisMaxLimit1(const double RotAxisMaxLimit);
		//! Visitor method for mw5axMachDef class
		virtual void AcceptVisitor( mwMachineVisitor &visitor ) const;
		//! Gets a clone of machine
		/*!
			Return a mwMachDef autopointer to current object (an instance of mw3axMachDef, mw4axMachDef, mw5axMachDef, mw6axMachDef, mw6axCSMachDef)
		*/
		const mwMachDefPtr Clone() const;
		//! Normalize all vectors (first rotary axis direction, second rotary axis direction and spindle) 
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
		//! type of the 5 axis machine kinematics (based on where the rotary axis are mechanically built)
		MachType		m_machineType;
		//! rotational axis direction vectors representing the rotation
		vector3d		m_rotAxisDir[2];
		//! 3d points describing the base point of rotation. Note they could be anywhere on the rotation line
		point3d			m_rotAxisBasePt[2];
		//! minimum limits in degrees for both rotary axis
		double			m_RotAxisMinLimit[2];
		//! maximum limits in degrees for both rotary axis
		double			m_RotAxisMaxLimit[2];
	};
	//! Defines an autopointer to mw5axMachDef class
	typedef misc::mwAutoPointer<mw5axMachDef> mw5axMachDefPtr;
}

#endif
