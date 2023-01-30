// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTCOORDSYSTEM2D_HPP_
#define MW_MWTCOORDSYSTEM2D_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTAbstractCoordSystem2d.hpp"
//#############################################################################
namespace geoDef
{
	//#############################################################################
	//! Implements a 2d system of coordinates
	/*!
		The class contain a system of coordinate in 2d holding the followings:
		 - Origin
	*/
	template <typename T>
		class MW_5AXUTIL_API mwTCoordSystem2d : public mwTAbstractCoordSystem2d <T>
	{
	public:
		typedef typename  mwTAbstractCoordSystem2d<T>::ValueType ValueType;
		typedef typename  mwTAbstractCoordSystem2d<T>::PositionVector PositionVector;
		typedef typename  mwTAbstractCoordSystem2d<T>::BaseCSPtr BaseCSPtr;
		typedef typename  mwTAbstractCoordSystem2d<T>::CoordSystemSetter CoordSystemSetter;
		typedef typename  mwTAbstractCoordSystem2d<T>::CoordSystemGetter CoordSystemGetter;
	private:
		typedef mwTCoordSystem2d<ValueType>			MySelf;
	public:
		typedef typename misc::mwAutoPointer< MySelf >			Ptr;
//#############################################################################
		//! constructor
		/*
				\param origin the origin of this CS, default is (0,0)
		*/
		mwTCoordSystem2d(const PositionVector &origin=PositionVector (0,0));
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
		virtual void AcceptVisitor(	CoordSystemGetter& getter ) const;
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
	protected:
		PositionVector mOrigin;
	};
//#############################################################################
	typedef mwTCoordSystem2d< float > CSOrigin2df;
	typedef mwTCoordSystem2d< double > CSOrigin2dd;
};
#endif	//	MW_MWTCOORDSYSTEM2D_HPP_
