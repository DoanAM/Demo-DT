// (C) 2012-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW6AXCSMACHDEF_HPP_
#define MW_MW6AXCSMACHDEF_HPP_

#include "mwMachDef.hpp"

namespace post
{
	//! this class stores the params needed for defining a machine
	class MW_5AXUTIL_API mw6axCSMachDef : public mwMachDef
	{
	public:
		enum AxisType
		{
			HEAD = 0,
			TABLE = 1
		};
		//! default constructor
		/*! Creates a post machine definition using 4x4 matrix as spindle (holderTransform)
			1stType = HEAD;
			2ndType = TABLE;
			3rdType = TABLE;
			NumberOfAxes = MACHINE_6AXIS;
			sawDirection = vector3d(0, 0, 1)
			RotAxisDir0 = vector3d(0, 0, -1);
			RotAxisDir1 = vector3d(0, -1, 0);
			RotAxisDir2 = vector3d(-1, 0, 0);
			RotAxisBasePt0 = point3d( 0,0,0 );
			RotAxisBasePt1 = point3d( 0,0,0 );
			RotAxisBasePt2 = point3d( 0,0,0 );
			RotAxisMinLimit0 = -100000;
			RotAxisMinLimit1= -100000;
			RotAxisMinLimit2= -100000;
			RotAxisMaxLimit0 = 100000;
			RotAxisMaxLimit1 = 100000;
			RotAxisMaxLimit2 = 100000;
		*/
		mw6axCSMachDef();
		//! virtual destructor
		~mw6axCSMachDef();
		//! Constructor - creates a post machine definition using spindle as vector
		/*!
			\param _1stType define first rotary axis mounting position (HEAD or TABLE)
			\param _2ndType define second rotary axis mounting position (HEAD or TABLE)
			\param _3rdType define third rotary axis mounting position (HEAD or TABLE)
			\param units defines units used
			\param spindleDirection defines spindle
			\param sawDirection defines cutting 6axis direction
			\param rotAxisDirection0 defines first rotary direction
			\param rotAxisDirection1 defines second rotary direction
			\param rotAxisDirection2 defines third rotary direction
			\param rotAxisBasePoint0 defines first rotary base point
			\param rotAxisBasePoint1 defines second rotary base point
			\param rotAxisBasePoint2 defines third rotary base point
			\param vRotAxisMinLimit0 defines first rotary axis minimum limit
			\param vRotAxisMinLimit1 defines second rotary axis minimum limit
			\param vRotAxisMinLimit2 defines third rotary axis minimum limit
			\param vRotAxisMaxLimit0 defines first rotary axis maximum limit
			\param vRotAxisMaxLimit1 defines second rotary axis maximum limit
			\param vRotAxisMaxLimit2 defines third rotary axis maximum limit
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
		mw6axCSMachDef( 
			const AxisType& _1stType,	
			const AxisType& _2ndType,
		    const AxisType& _3rdType,
			const Units units,
			const vector3d& spindleDirection,
			const vector3d& sawDirection,
			const vector3d& rotAxisDirection0,
			const vector3d& rotAxisDirection1,
			const vector3d& rotAxisDirection2,
			const point3d& rotAxisBasePoint0,
			const point3d& rotAxisBasePoint1,
			const point3d& rotAxisBasePoint2,
			const double vRotAxisMinLimit0,
			const double vRotAxisMinLimit1,
			const double vRotAxisMinLimit2,
			const double vRotAxisMaxLimit0,
			const double vRotAxisMaxLimit1,
			const double vRotAxisMaxLimit2,
			const point3d& TransAxisMinLimit = -LimitTranslation(),
			const point3d& TransAxisMaxLimit = LimitTranslation(),
			const vector3d& translationX = vector3d(1., 0., 0.),
			const vector3d& translationY = vector3d(0., 1., 0.),
			const vector3d& translationZ = vector3d(0., 0., 1.),
			const mwMatrix4dPtr& workpieceTransform = MW_NULL,
			const mwMatrix4dPtr& holderTransform = MW_NULL,
			const bool doValidations = true,
			const MachineDefinitionType type = CONTOUR_MACHINE);
		//#############################################################################
		//! Constructor - creates a post machine definition using 4x4 matrix as spindle and cutting direction (holderTransform)
		/*!
			\param _1stType define first rotary axis mounting position (HEAD or TABLE)
			\param _2ndType define second rotary axis mounting position (HEAD or TABLE)
			\param _3rdType define third rotary axis mounting position (HEAD or TABLE)
			\param units defines units used
			\param rotAxisDirection0 defines first rotary direction
			\param rotAxisDirection1 defines second rotary direction
			\param rotAxisDirection2 defines third rotary direction
			\param rotAxisBasePoint0 defines first rotary base point
			\param rotAxisBasePoint1 defines second rotary base point
			\param rotAxisBasePoint2 defines third rotary base point
			\param vRotAxisMinLimit0 defines first rotary axis minimum limit
			\param vRotAxisMinLimit1 defines second rotary axis minimum limit
			\param vRotAxisMinLimit2 defines third rotary axis minimum limit
			\param vRotAxisMaxLimit0 defines first rotary axis maximum limit
			\param vRotAxisMaxLimit1 defines second rotary axis maximum limit
			\param vRotAxisMaxLimit2 defines third rotary axis maximum limit
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
		mw6axCSMachDef(
			const AxisType& _1stType,
			const AxisType& _2ndType,
			const AxisType& _3rdType,
			const Units units,
			const vector3d& rotAxisDirection0,
			const vector3d& rotAxisDirection1,
			const vector3d& rotAxisDirection2,
			const point3d& rotAxisBasePoint0,
			const point3d& rotAxisBasePoint1,
			const point3d& rotAxisBasePoint2,
			const double vRotAxisMinLimit0,
			const double vRotAxisMinLimit1,
			const double vRotAxisMinLimit2,
			const double vRotAxisMaxLimit0,
			const double vRotAxisMaxLimit1,
			const double vRotAxisMaxLimit2,
			const point3d& TransAxisMinLimit = -LimitTranslation(),
			const point3d& TransAxisMaxLimit = LimitTranslation(),
			const vector3d& translationX = vector3d(1., 0., 0.),
			const vector3d& translationY = vector3d(0., 1., 0.),
			const vector3d& translationZ = vector3d(0., 0., 1.),
			const mwMatrix4dPtr& workpieceTransform = MW_NULL,
			const mwMatrix4dPtr& holderTransform = MW_NULL,
			const bool doValidations = true,
			const MachineDefinitionType type = CONTOUR_MACHINE);
	
		//! Copy constructor
		mw6axCSMachDef(const mw6axCSMachDef& toCopy);
		//! Copy operator
		const mw6axCSMachDef& operator = (const mw6axCSMachDef& toCopy);
		//! Comparison operator
		/* Compares two mw6axMachDef objects
			\return true it the compared objects are equal member by member, 
			\false otherwise
		*/
		const bool operator == (const mw6axCSMachDef& toCompare) const;
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
		//! Sets sedond rotary axis direction
		void SetRotAxisDir1(const vector3d& rotAxisDir);
		//! Gets third rotary axis direction
		/*! 			
			\returns the RotAxisDir2
		*/
		const vector3d& GetRotAxisDir2() const;
		//! Sets third rotary axis direction
		void SetRotAxisDir2(const vector3d& rotAxisDir);
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
		//! Gets third rotary axis base point
		/*! 			
			\returns the RotAxisBasePt2
		*/
		const point3d& GetRotAxisBasePt2() const;
		//! Sets third rotary axis base point
		void SetRotAxisBasePt2(const point3d& rotAxisBasePt);
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
		//! Gets third rotary minimum limit (in degrees)
		/*! 			
			\returns the RotAxisMinLimit2
		*/
		const double GetRotAxisMinLimit2() const;
		//! Sets third rotary minimum limit (in degrees)
		void SetRotAxisMinLimit2(const double RotAxisMinLimit);
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
		//! Gets third rotary maximum limit (in degrees)
		/*! 			
			\returns the RotAxisMaxLimit1
		*/
		const double GetRotAxisMaxLimit2() const;
		//! Sets third rotary maximum limit (in degrees)
		void SetRotAxisMaxLimit2(const double RotAxisMaxLimit);
		//! Visitor method for mw5axMachDef class
		virtual void AcceptVisitor( mwMachineVisitor &visitor ) const;
		//! Gets a clone of machine
		/*!
			Return a mwMachDef autopointer to current object (an instance of mw3axMachDef, mw4axMachDef, mw5axMachDef, mw6axMachDef, mw6axCSMachDef)
		*/
		const mwMachDefPtr Clone() const;
		//! Normalize all vectors (first rotary axis direction, second rotary axis direction, third rotary axis direction and spindle) 
		virtual void NormalizeVectors();
		//! Gets first rotary axis mounting position (HEAD or TABLE)
		const AxisType GetFirstAxisType() const;
		//! Sets first rotary axis mounting position (HEAD or TABLE)
		void SetFirstAxisType(const AxisType at);
		//! Gets second rotary axis mounting position (HEAD or TABLE)
		const AxisType GetSecondAxisType() const;
		//! Sets second rotary axis mounting position (HEAD or TABLE)
		void SetSecondAxisType(const AxisType at);
		//! Gets third rotary axis mounting position (HEAD or TABLE)
		const AxisType GetThirdAxisType() const;
		//! Sets third rotary axis mounting position (HEAD or TABLE)
		void SetThirdAxisType(const AxisType at);
		//! Gets contour (saw) cutting direction, default is (0,0,0)
		const vector3d& GetSawDirection() const;
		//! Sets contour (saw) cutting direction
		void SetSawDirection(const vector3d& value);
		//! Validate current machine, it is defined wrong then an exception is thrown
		virtual void Validate() const;
		//! Sets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		virtual void SetMachineDefinitionType(const MachineDefinitionType type);
		//! Sets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		virtual MachineTurningType GetMachineTurningType() const;
		//! Sets holder transformation 
		virtual void SetHolderTransform(const mwMatrix4dPtr& holderTransform, bool initialHTMatrix = true);

		void SpindleDefinedAsVector(const bool spindleDefinedAsVector);
	protected:
		//! Copy function used to copy all members
		void Copy(const mw6axCSMachDef& toCopy);
		//! scaled all measurable data of the machine definition by the given scale factor
		/*!
			\param units not used here 
			\param scaleFactor  the machine definition is scaled by the scale factor
		*/
		void Scale(const Units units,const double& scaleFactor);
		//! rotational axis direction vectors representing the rotation
		vector3d		m_rotAxisDir[3];
		//! 3d points describing the base point of rotation. Note they could be anywhere on the rotation line
		point3d			m_rotAxisBasePt[3];
		//! minimum limits in degrees for all 3 rotary axis
		double			m_RotAxisMinLimit[3];
		//! maximum limits in degrees for all 3 rotary axis
		double			m_RotAxisMaxLimit[3];
		//! first axis type
		AxisType        m_1stType;
		//! second axis type
		AxisType        m_2ndType;
		//! third axis type
		AxisType        m_3rdType;
		//! saw original direction
		vector3d        m_sawDirection;
	};
	//! Defines an autopointer to mw6axMachDef class
	typedef misc::mwAutoPointer<mw6axCSMachDef> mw6axCSMachDefPtr;
}

#endif