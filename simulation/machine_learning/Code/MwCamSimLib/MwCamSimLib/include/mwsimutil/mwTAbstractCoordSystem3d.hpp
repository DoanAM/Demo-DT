// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTABSTRACTCOORDSYSTEM3D_HPP_
#define MW_MWTABSTRACTCOORDSYSTEM3D_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTVector3.hpp"
#include "mwTCoordSystem.hpp"
//#############################################################################
namespace geoDef
{
	//=========== Templates declarations.=============
	template < typename T >					class mwTAbstractCoordSystem3d;
	template < typename T >					class mwTCoordSystem3d;
	template < typename T >					class mwTiCoordSystem3d;
	template < typename T >					class mwTijCoordSystem3d;
	template < typename T >					class mwTijkCoordSystem3d;
//#############################################################################
	//! Visitor pattern for setting a coordinate system
	template <typename T>
		class mwTCSSetter3dIntf
	{
	private:
		typedef mwTCSSetter3dIntf<T> MySelf;
	public:
		typedef T ValueType;
		//#############################################################################
		virtual void Visit(mwTAbstractCoordSystem3d<ValueType>& tv) const =0;
		virtual void Visit(mwTCoordSystem3d<ValueType>& tv) const =0;
		virtual void Visit(mwTiCoordSystem3d<ValueType>& tv) const =0;
		virtual void Visit(mwTijCoordSystem3d<ValueType>& tv) const =0;
		virtual void Visit(mwTijkCoordSystem3d<ValueType>& tv) const =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTCSSetter3dIntf(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Visitor pattern for getting data from a coordinate system
	template <typename T>
		class MW_5AXUTIL_API mwTCSGetter3dIntf
	{
	private:
		typedef mwTCSGetter3dIntf<T> MySelf;
	public:
		typedef T ValueType;
		//#############################################################################
		virtual void Visit(const mwTAbstractCoordSystem3d<ValueType>& tv) =0;
		virtual void Visit(const mwTCoordSystem3d<ValueType>& tv) =0;
		virtual void Visit(const mwTiCoordSystem3d<ValueType>& tv) =0;
		virtual void Visit(const mwTijCoordSystem3d<ValueType>& tv) =0;
		virtual void Visit(const mwTijkCoordSystem3d<ValueType>& tv) =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTCSGetter3dIntf(){};
		//#############################################################################
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
//#############################################################################
	//! Base class for any 3d system of coordinates
	template <typename T>
		class MW_5AXUTIL_API mwTAbstractCoordSystem3d : public mwTCoordSystem < mathdef::mwTVector3<T> >
	{
	public:
		typedef typename mwTCoordSystem <mathdef::mwTVector3<T> >::ValueType ValueType;
	private:
		typedef mwTAbstractCoordSystem3d<ValueType>	MySelf;
	public:
		typedef mathdef::mwTVector3<T>					PositionVector;
		typedef misc::mwAutoPointer< MySelf >	Ptr;
		typedef Ptr									BaseCSPtr;
		typedef mwTCSGetter3dIntf <ValueType>		CoordSystemGetter;
		typedef mwTCSSetter3dIntf <ValueType>		CoordSystemSetter;
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
		virtual void AcceptVisitor(	CoordSystemGetter& getter )const=0;
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
		virtual ~mwTAbstractCoordSystem3d(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
//#############################################################################
	typedef mwTAbstractCoordSystem3d< float > CS3df;
	typedef mwTAbstractCoordSystem3d< double > CS3dd;
}
#endif	//	MW_MWTABSTRACTCOORDSYSTEM3D_HPP_
