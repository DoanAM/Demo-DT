// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTABSTRACTCOORDSYSTEM2D_HPP_
#define MW_MWTABSTRACTCOORDSYSTEM2D_HPP_
//#############################################################################
#include "mwTVector2.hpp"
#include "mwTCoordSystem.hpp"
//#############################################################################
namespace geoDef
{
	//=========== Templates declarations.=============
	template < typename T >		class mwTAbstractCoordSystem2d;
	template < typename T >		class mwTCoordSystem2d;
	template < typename T >		class mwTiCoordSystem2d;
	template < typename T >		class mwTijCoordSystem2d;
	//#############################################################################
	//! Visitor pattern for setting a coordinate system
	template <typename T>
	class MW_5AXUTIL_API mwTCSSetter2dIntf
	{
	private:
		typedef mwTCSSetter2dIntf<T> MySelf;
	public:
		typedef  T ValueType;
		//#############################################################################
		virtual void Visit(mwTAbstractCoordSystem2d<ValueType>& tv) const =0;
		virtual void Visit(mwTCoordSystem2d<ValueType>& tv) const =0;
		virtual void Visit(mwTiCoordSystem2d<ValueType>& tv) const =0;
		virtual void Visit(mwTijCoordSystem2d<ValueType>& tv) const =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTCSSetter2dIntf(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Visitor pattern for getting data from a coordinate system
	template <typename T>
	class MW_5AXUTIL_API mwTCSGetter2dIntf
	{
	private:
		typedef mwTCSGetter2dIntf<T> MySelf;
	public:
		typedef T ValueType;
		//#############################################################################
		virtual void Visit(const mwTAbstractCoordSystem2d<ValueType>& tv) =0;
		virtual void Visit(const mwTCoordSystem2d<ValueType>& tv) =0;
		virtual void Visit(const mwTiCoordSystem2d<ValueType>& tv) =0;
		virtual void Visit(const mwTijCoordSystem2d<ValueType>& tv) =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTCSGetter2dIntf(){};
		//#############################################################################
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Base class for any 2d system of coordinates
	template <typename T>
		class MW_5AXUTIL_API mwTAbstractCoordSystem2d : public mwTCoordSystem <mathdef::mwTVector2<T> >
	{
	public:
		typedef typename mwTCoordSystem <mathdef::mwTVector2<T> >::ValueType ValueType;
	private:

		typedef mwTAbstractCoordSystem2d<ValueType>			MySelf;
	public:
		typedef mathdef::mwTVector2<T>					PositionVector;
		typedef misc::mwAutoPointer< MySelf >			Ptr;
		typedef Ptr							BaseCSPtr;
		typedef mwTCSGetter2dIntf <ValueType>		CoordSystemGetter;
		typedef mwTCSSetter2dIntf <ValueType>		CoordSystemSetter;
//#############################################################################
		//! clones the CS
		/*
				\returns a clone of current CS
		*/
		virtual const BaseCSPtr Clone() const=0;
//#############################################################################
		//! implements visitor pattern for setting data in the current CS
		/*!
				\param setter the visitor to setting data in the current CS
		*/
		virtual void AcceptVisitor( const CoordSystemSetter& setter )=0;
//#############################################################################
		//! implements visitor pattern for getting data from the current CS
		/*!
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	CoordSystemGetter& getter ) const=0;
//#############################################################################
		//! Sets origin of CS
		/*
				\param orig the new origin
		*/
		virtual void SetOrigin(const PositionVector &orig)=0;
//#############################################################################
		//! Gets origin of CS
		/*
				\returns orig of CS
		*/
		virtual const PositionVector& GetOrigin() const=0;
//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTAbstractCoordSystem2d(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
//#############################################################################
	typedef mwTAbstractCoordSystem2d< float > CS2df;
	typedef mwTAbstractCoordSystem2d< double > CS2dd;
}
#endif	//	MW_MWTABSTRACTCOORDSYSTEM2D_HPP_
