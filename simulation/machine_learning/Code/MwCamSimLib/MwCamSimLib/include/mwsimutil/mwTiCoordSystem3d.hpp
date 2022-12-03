// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTICOORDSYSTEM3D_HPP_
#define MW_MWTICOORDSYSTEM3D_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTAbstractCoordSystem3d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a 3d system of coordinates
	/*!
		The class contain a system of coordinate in 3d holding the followings:
		 - Origin
		 - direction corresponding to i vector
	*/
	template <class T>
	class MW_5AXUTIL_API mwTiCoordSystem3d
	:public mwTAbstractCoordSystem3d<T>
	{
	public:
		typedef typename  mwTAbstractCoordSystem3d<T>::ValueType ValueType;
		typedef typename  mwTAbstractCoordSystem3d<T>::PositionVector PositionVector;
		typedef typename  mwTAbstractCoordSystem3d<T>::BaseCSPtr BaseCSPtr;
		typedef typename  mwTAbstractCoordSystem3d<T>::CoordSystemSetter CoordSystemSetter;
		typedef typename  mwTAbstractCoordSystem3d<T>::CoordSystemGetter CoordSystemGetter;

	private:
		typedef mwTiCoordSystem3d<ValueType>	MySelf;
	public:
		typedef typename misc::mwAutoPointer< MySelf >	Ptr;
//#############################################################################
		//! constructor
		/*
				\param origin the origin of this CS, default is (0,0,0)
				\param i the i axis of this CS, default is (1,0,0)
		*/
		mwTiCoordSystem3d(const PositionVector &origin=PositionVector(0,0,0),
						  const PositionVector &i=PositionVector(1,0,0));
//#############################################################################
		//! clones the CS
		/*
				\returns a clone of current CS
		*/
		virtual const BaseCSPtr Clone() const;
//#############################################################################
		//! Transforms a vector having absolute coordinates to CS relative coordinates
		/*! translates and rotates a vector	based on origin  and direction
			of current coordinate system
				\param vector the vector having absolute coordinates
				\returns transformed vector
		*/
		virtual const PositionVector TransformToMe(const PositionVector &vector) const;
//#############################################################################
		//! Transforms a vector having CS relative coordinates to absolute coordinates
		/*! translates and rotates a vector	based on origin  and direction
			of current coordinate system
				\param vector the vector having CS relative coordinates
				\returns transformed vector
		*/
		virtual const PositionVector TransformFromMe(const PositionVector &vector) const;
//#############################################################################
		//! implements visitor pattern for setting data in the current CS
		/*!
				\param setter the visitor to setting data in the current CS
		*/
		virtual void AcceptVisitor( const CoordSystemSetter& setter );
//#############################################################################
		//! implements visitor pattern for getting data from the current CS
		/*!
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	CoordSystemGetter& getter )const;
//#############################################################################
		//! Sets origin of CS
		/*
				\param orig the new origin
		*/
		virtual void SetOrigin(const PositionVector &orig);
//#############################################################################
		//! Gets origin of CS
		/*
				\returns orig of CS
		*/
		virtual const PositionVector& GetOrigin() const;
//#############################################################################
		//! Sets i axis of CS
		/*
				\param i the new i axis
		*/
		void Seti(const PositionVector &i);
//#############################################################################
		//! Gets i axis of CS
		/*
				\returns i axis of CS
		*/
		const PositionVector& Geti() const;
	protected:
	protected:
		PositionVector mOrigin;
		PositionVector mi;
	};
//#############################################################################
	typedef mwTiCoordSystem3d<float> CSiOrigin3df;
	typedef mwTiCoordSystem3d<double > CSiOrigin3dd;

}
#endif	//	MW_MWTICOORDSYSTEM3D_HPP_
