// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTCSijkGetter class

#ifndef MW_MWTCSIJKGETTER_HPP_
#define MW_MWTCSIJKGETTER_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTijkCoordSystem3d.hpp"
#include "mwTijCoordSystem3d.hpp"
#include "mwTiCoordSystem3d.hpp"
//#############################################################################
namespace geoDef
{
	//! Visitor pattern for getting data from a coordinate system
	template<typename T>
	class MW_5AXUTIL_API mwTCSijkGetter : public mwTCSGetter3dIntf<T>
	{
	private:
		typedef mwTCSijkGetter MySelf;
	public:
		typedef T ValueType;
		typedef typename mwTAbstractCoordSystem3d<ValueType>::PositionVector PositionVector;
		//#############################################################################
		mwTCSijkGetter()
		{
		}
		//#############################################################################
		virtual void Visit(const mwTAbstractCoordSystem3d<ValueType>& )
		{
			throw misc::mwException(0,_T("Unable to get coordinates from an abstract class"));
		}
		//#############################################################################
		virtual void Visit(const mwTCoordSystem3d<ValueType>& )
		{
			throw misc::mwException(0,_T("Unable to get Helix coordinates from an mwTCoordSystem3d"));
		}
		//#############################################################################
		virtual void Visit(const mwTiCoordSystem3d<ValueType>& )
		{
			throw misc::mwException(0,_T("Unable to get Helix coordinates from an mwTiCoordSystem3d"));
		}
		//#############################################################################
		virtual void Visit(const mwTijCoordSystem3d<ValueType>& tv)
		{
			m_origin = tv.GetOrigin();
			m_i = tv.Geti();
			m_j = tv.Getj();
			m_k = m_i.Cross(m_j);
		}
		//#############################################################################
		virtual void Visit(const mwTijkCoordSystem3d<ValueType>& tv) 
		{
			m_origin = tv.GetOrigin();
			m_i = tv.Geti();
			m_j = tv.Getj();
			m_k = tv.Getk();
		}
		//#############################################################################
		virtual ~mwTCSijkGetter(){};
		//#############################################################################
		const PositionVector& GetOrigin() const
		{
			return m_origin;
		}
		//#############################################################################
		const PositionVector& Geti() const
		{
			return m_i;
		}
		//#############################################################################
		const PositionVector& Getj() const
		{
			return m_j;
		}
		//#############################################################################
		const PositionVector& Getk() const
		{
			return m_k;
		}
		//#############################################################################
	private:
		PositionVector m_origin,m_i,m_j,m_k;
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf& ){return *this;};
		//#############################################################################

	};

}
#endif	//	MW_MWTCSIJKGETTER_HPP_
