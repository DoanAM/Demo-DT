// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWMACHDEF_HPP_
#define MW_MWMACHDEF_HPP_

#include "mwDllImpExpDef.hpp"
#include <mwTPoint3d.hpp>
#include "mwMeasurable.hpp"
#include "mwAutoPointer.hpp"
#include "mwCompatibilityChecker.hpp"
#include <algorithm>
#include "mwPostCommonDefinitions.hpp"

namespace post
{
	class mwMachDef;
	class mw3axMachDef;
	class mw4axMachDef;
	class mw5axMachDef;
	class mw6axMachDef;// 5+1 (5axis with fixed 3rd rotation axis)
	class mw6axCSMachDef;// 6 axis with 3rd not fixed axis

	//! defines an autopointer to mwMachDef base class
	typedef misc::mwAutoPointer<mwMachDef> mwMachDefPtr;
	
	class MW_5AXUTIL_API mwMachineVisitor
	{
	public:
		//! visits a mwMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mwMachDef &mw ) const = 0;
		//! visits a mw3axMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mw3axMachDef &mw ) const = 0;
		//! visits a mw4axMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mw4axMachDef &mw ) const = 0;
		//! visits a mw5axMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mw5axMachDef &mw ) const = 0;
		//! visits a mw6axMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mw6axMachDef &mw ) const = 0;
		//! visits a mw6axCSMachDef
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit( const mw6axCSMachDef &mw ) const = 0;
	};// end class mwMachineVisitor
	//! this class stores the params needed for defining a machine
	class MW_5AXUTIL_API mwMachDef : public measures::mwMeasurable
	{
	public:
		// Defines all machines supported by multixpost
		enum NumbersOfAxes
		{
			MACHINE_3AXIS = 0,
			MACHINE_4AXIS = 1,
			MACHINE_5AXIS = 2,
			MACHINE_6AXIS = 3,
			MACHINE_6AXIS_CONTOUR = 4
		};
		// Defines all machines supported by multixpost
		enum MachineDefinitionType
		{
			MILLING_MACHINE = 0,
			TURNING_MACHINE = 1,
			CONTOUR_MACHINE = 2,
			LASER_MACHINE = 3,
			KNIFE_GRINDING_MACHINE = 4,
			ROBOTIC = 5,
			CONSTANT_TRANSLATION_MACHINE = 6
		};
		// Defines all machines supported by multixpost
		enum MachineTurningType
		{
			_NOT_TUNING = 0,
			_3TR_1ROT = 1,
			_3TR_2ROT = 2,
			_3TR_1ROT_1TURRET = 3
		};
	
		typedef cadcam::mwTPoint3d< double >              point3d;
		typedef cadcam::mwTPoint3d< double >              vector3d;
		typedef cadcam::mwMatrix<double, 4, 4>            mwMatrix4d;
		typedef misc::mwAutoPointer<mwMatrix4d>           mwMatrix4dPtr;
		typedef misc::mwAutoPointer<point3d>              point3dPtr;
		typedef std::pair<misc::mwstring, misc::mwstring> stringPair;
		
		//! Default constructor
		/*! Creates a post machine definition using 4x4 matrix as spindle (holderTransform)
			m_TransAxisMinLimit = -LimitTranslation();
			m_TransAxisMaxLimit = LimitTranslation();
			m_x = vector3d(1., 0., 0.);
			m_y = vector3d(0., 1., 0.);
			m_z = vector3d(0., 0., 1.);
			m_workpieceTransform = MW_NULL;
			m_holderTransform = MW_NULL;
			m_holderTransformInv = MW_NULL;
			InitializeMatrix();
			m_doValidations = true;
			m_arrowDirectionPtr = MW_NULL;
			m_type = MILLING_MACHINE;
		*/
		mwMachDef();
		//! Virtual destructor
		virtual ~mwMachDef();
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
		mwMachDef( 
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
		mwMachDef(
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
		mwMachDef(const mwMachDef& toCopy);
		//! Copy operator
		const mwMachDef& operator = (const mwMachDef &toCopy);
		//! Comparison operator
		/* Compares two objects
			\return true it the compared objects are equal member by member,
			\false otherwise
		*/
		const bool operator == (const mwMachDef& toCompare) const;
		//! Gets spindle direction vector as constant
		/*! 			 
			\returns const SpindleDir
		*/
		const vector3d& GetSpindleDir() const;
		//! Gets spindle direction vector as address 
		/*! 			
			\returns the SpindleDir
		*/
		vector3d& GetSpindleDir();
		//! Sets spindle direction vector
		void SetSpindleDir(const vector3d& spindDir);
		//! Gets machine number of axis (3,4,5,5+1, or 6)
		const NumbersOfAxes& GetNumberOfAxes() const;
		//! Gets a point in 3d with the x,y,z components
		/*! Gets a point in 3d with the x,y,z components where each of them
			represent the minimum limit of the according axis
		*/
		const point3d& GetTransAxisMinLimit() const;
		//! Gets a point in 3d with the x,y,z components
		/*! Gets a point in 3d with the x,y,z components where each of them
			represent the minimum limit of the according axis
		*/
		point3d& GetTransAxisMinLimit();
		//! Sets a point in 3d with the x,y,z components
		/*!
			Where each of them represent the minimum limit of the according axis
		*/
		void SetTransAxisMinLimit(const point3d& transAxisMinLimit);
		//! Gets a point in 3d with the x,y,z components 
		/*! Gets a point in 3d with the x,y,z components where each of them
			represent the maximum limit of the according axis
		*/
		const point3d& GetTransAxisMaxLimit() const;
		//! Gets a point in 3d with the x,y,z components 
		/*! Gets a point in 3d with the x,y,z components where each of them
			represent the maximum limit of the according axis
		*/
		point3d& GetTransAxisMaxLimit();
		//! Sets a point in 3d with the x,y,z components 
		/*!
			Where each of them represent the minimum limit of the according axis
		*/
		void SetTransAxisMaxLimit(const point3d& transAxisMaxLimit);
		//! Visit for mwMachDef class
		virtual void AcceptVisitor( mwMachineVisitor &visitor ) const;
		//! Gets a clone of machine
		/*!
			Return a mwMachDef autopointer to current object (an instance of mw3axMachDef, mw4axMachDef, mw5axMachDef, mw6axMachDef, mw6axCSMachDef)
		*/
		virtual const mwMachDefPtr Clone() const = 0;
		//! Gets translation X axis direction as const
		const vector3d& GetTranslationX() const;
		//! Gets translation X axis direction as reference
		vector3d& GetTranslationX();
		//! Gets translation Y axis direction as const
		const vector3d& GetTranslationY() const;
		//! Gets translation Y axis direction as reference
		vector3d& GetTranslationY();
		//! Gets translation Z axis direction as const
		const vector3d& GetTranslationZ() const;
		//! Gets translation Z axis direction as reference
		vector3d& GetTranslationZ();
		//! Sets translation axis directions, X, Y and Z
		void SetTranslationXYZ(const vector3d& x, const vector3d& y, const vector3d& z);
		//! Gets workpiece transformation
		/*!
			Returns 4x4 workpiece transformation as const
		*/
		const mwMatrix4dPtr& GetWorkpieceTransform(bool initialMatrix = true) const;
		//! Gets workpiece transformation
		/*!
			Returns 4x4 workpiece transformation as reference
		*/
		mwMatrix4dPtr& GetWorkpieceTransform(bool initialMatrix = true);
		//! Sets workpiece transformation
		void SetWorkpieceTransform(const mwMatrix4dPtr& workpieceTransform, bool initialMatrix = true);
		//! Gets holder transformation
		/*!
			Returns 4x4 holder transformation as const
		*/
		const mwMatrix4dPtr& GetHolderTransform(bool initialMatrix = true) const;
		//! Gets holder transformationó
		/*!
			Returns 4x4 holder transformation as reference
		*/
		mwMatrix4dPtr& GetHolderTransform(bool initialHTMatrix = true);
		//! Gets holder transformation inverse
		/*!
			Returns 4x4 holder transformation inverse as const
		*/
		const mwMatrix4dPtr& GetHolderTransformInv() const;
		//! Gets holder transformation inverse
		/*!
			Returns 4x4 holder transformation inverse as reference
		*/
		mwMatrix4dPtr& GetHolderTransformInv();
		//! Sets holder transformation 
		virtual void SetHolderTransform(const mwMatrix4dPtr& holderTransform, bool initialHTMatrix = true);
		//! Normalize spindle vector 
		virtual void NormalizeVectors();
		//! Gets transformation matrix
		/*!
			Return a 4x4 const matrix computed base on X,Y and Z direction axis, used to compute machine coordinate system
		*/
		const mwMatrix4dPtr& GetTransformationMatrix() const;
		//! Gets transformation matrix
		/*!
			Return a 4x4 reference matrix computed base on X,Y and Z direction axis, used to compute machine coordinate system
		*/
		mwMatrix4dPtr& GetTransformationMatrix();
		//! Return true if machine coordinate system is identity
		/*
			Return true if machine coordinate system computed base on X,Y and Z translation direction is identity
		*/
		const bool IsSystemOrthogonal() const;
		//! Gets true if current machine was validated or false otherwise
		const bool GetValidations() const;
		//! Sets validation flag
		/*!
			Sets validation flag to false to disable validation 
		*/
		void SetValidations(const bool doValidations);
		//! Validate current machine, it is defined wrong then an exception is thrown
		virtual void Validate() const;
		//! Gets arrow direction vector as const for laser machine
		/*! 
			Arrow direction vector defines cutting direction used by laser machines
		*/
		const point3dPtr& GetArrowDirectionPtr() const;
		//! Gets arrow direction vector as reference for laser machine
		/*!
			Arrow direction vector defines cutting direction used by laser machines
		*/
		point3dPtr& GetArrowDirectionPtr() ;
		//! Sets arrow direction vector for laser machine
		/*!
			Arrow direction vector defines cutting direction used by laser machines
		*/
		void SetArrowDirectionPtr(const point3dPtr& arrowDirectionPtr);
		//! Gets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		const MachineDefinitionType GetMachineDefinitionType() const;
		//! Sets machine definition to MachineDefinitionType type. 
		/*!
			There are 3 supported types: MILLING_MACHINE, TURNING_MACHINE and CONTOUR_MACHINE
		*/
		virtual void SetMachineDefinitionType(const MachineDefinitionType type) = 0;
		//! Gets machine definition to MachineTurningType type. 
		/*!
			There are 3 supported turning types:
			-3 translations and 1 rotation
			-3 translations and 2 rotations
			-3 translations one rotation and on turret
		*/
		virtual MachineTurningType GetMachineTurningType() const = 0;
		
		const bool IsSpindleDefinedAsVector() const;

		virtual void SpindleDefinedAsVector(const bool spindleDefinedAsVector);
		
		//! Gets maximum translation limit supported 
		static const point3d& LimitTranslation();
		//! Gets maximum rotary limit supported
		static const double& LimitRotation();
		//! Gets machine name and post setting ID
		const stringPair& GetMachineNameAndPostDefinitionID() const;
		//! Sets machine name and post setting ID
		void SetMachineNameAndPostDefinitionID(const stringPair& _stringPair);

		const bool AdditionalAxesWereUsed() const;
	protected:
		//! Scaled all measurable data of the machine definition by the given scale factor
		/*!
			\param units not used here 
			\param scaleFactor  the machine definition is scaled by the scale factor
		*/
		virtual void Scale(const Units units, const double& scaleFactor);
		//! Compute internal coordinate system base on provided X,Y and Z translation directions 
		void InitializeMatrix();
		//! Compute holder inverse matrix base on holder matrix
		void UpdateHolderTransfInv();
#pragma warning(push)
#pragma warning(disable:4251)
		//! a vector from tool tip showing towards holder and spindle when all rotary axis are set to zero
		vector3d		     m_spindDir;
		//! Numbers of axes 
		NumbersOfAxes        m_machineNrOfAx;
		//! minimum limits for all three translational axis x,y,z
		point3d			     m_TransAxisMinLimit;
		//! maximum limits for all three translational axis x,y,z
		point3d			     m_TransAxisMaxLimit;
		//! translation axes X
		vector3d		     m_x;
		//! translation axes Y
		vector3d		     m_y;
		//! translation axes Z
		vector3d		     m_z;
		//! 4x4 matrix used to transform orthogonal system to non-orthogonal system
		mwMatrix4dPtr        m_matrix;
		//! keep type of matrix
		bool                 m_orthogonalMatrix;
		//! workpiece 4x4 matrix transformation
		mwMatrix4dPtr        m_workpieceTransform;
		mwMatrix4dPtr        m_workpieceTransformUpdated;
		//! holder 4x4 matrix transformation
		mwMatrix4dPtr        m_holderTransform;
		mwMatrix4dPtr        m_holderTransformUpdated;
		//! holder 4x4 inverse matrix transformation
		mwMatrix4dPtr        m_holderTransformInv;
		//! if true then throw exception if needed. Always will be the last parameter, even after a refactoring
		mutable bool         m_doValidations;
		//! special post for Laser Machine
		point3dPtr           m_arrowDirectionPtr;
		//! machine type
		MachineDefinitionType m_type;
		//! define how machine spindle is defined, as vector or as 4x4 matrix
		bool                 m_spindleDefinedAsVector;
		//! maximum supported translation limit
		static const point3d m_limitTranslation;
		//! maximum supported rotary limit
		static const double m_limitRotation;
		//! contains machine name and post ID
		stringPair          m_stringPair;
#pragma warning(pop)
	private:
		//! Copy function used to copy all members
		void Copy(const mwMachDef& toCopy);
	};
}

#endif	//	MW_MWMACHDEF_HPP_