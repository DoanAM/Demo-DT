// (C) 2011-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWPOSTEDARCMOVE_HPP_
#define MW_MWPOSTEDARCMOVE_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwTPoint3d.hpp"
#include <vector>

namespace post
{
	class mwPostedMove;
	
	class MW_5AXUTIL_API mwPostedArcMove
	{
	public:
		//#############################################################################
		enum direction
		{
			MW_DIR_NOT_DEFINED = 0,
			MW_CW,
			MW_CCW
		};
		//#############################################################################
		enum type
		{
			MW_TYPE_NOT_DEFINED = 0,
			MW_ARC,
			MW_HELIX
		};
		//#############################################################################
		enum flag
		{
			ARC_START = 0, // DEPRECATED! - is not exported by post processor after release 2019.08
			ARC_POINT,
			ARC_END
		};
		//#############################################################################
		mwPostedArcMove()
		{
			m_direction = MW_DIR_NOT_DEFINED;
			m_type = MW_TYPE_NOT_DEFINED;
			m_flag = ARC_POINT;
		};
		//#############################################################################
		typedef misc::mwAutoPointer<post::mwPostedMove>  mwPostedMovePtr;
		typedef std::vector<mwPostedMovePtr> postedListVector;
		//#############################################################################
		mwPostedArcMove(
			const direction _direction, 
			const type _type, 
			const double _radius, 
			const cadcam::mwPoint3d& _normal, 
			const cadcam::mwPoint3d& _center,
			const double _arcSweep,
			const double _helixHeight)
				: m_direction(_direction)
				, m_type(_type)
				, m_radius(_radius)
				, m_centerRelative(_center)
				, m_centerAbsolute()
				, m_flag(ARC_POINT)
				, m_normal(_normal)
				, m_helixHeight(_helixHeight)
				, m_arcSweep(_arcSweep)
		{}
		//#############################################################################
		mwPostedArcMove(
			const direction _direction, 
			const type _type, 
			const double _radius, 
			const cadcam::mwPoint3d& _normal, 
			const cadcam::mwPoint3d& _centerRel, 
			const cadcam::mwPoint3d& _centerAbs,
			const double _arcSweep,
			const double _helixHeight)
				: m_direction(_direction)
				, m_type(_type)
				, m_radius(_radius)
				, m_centerRelative(_centerRel)
				, m_centerAbsolute(_centerAbs)
				, m_flag(ARC_POINT)
				, m_normal(_normal)
				, m_helixHeight(_helixHeight)
				, m_arcSweep(_arcSweep)
		{}
		//#############################################################################
		bool operator == (const mwPostedArcMove& toCompare) const;
		//#############################################################################
		const direction GetDirection() const
		{
			return m_direction;
		}
		//#############################################################################
		void SetDirection(const direction _direction)
		{
			m_direction = _direction;
		}
		//#############################################################################
		const type GetType() const
		{
			return m_type;
		}
		//#############################################################################
		void SetType(const type _type)
		{
			m_type = _type;
		}
		//#############################################################################
		const double GetRadius() const
		{
			return m_radius;
		}
		//#############################################################################
		void SetRadius(const double _radius)
		{
			m_radius = _radius;
		}
		//#############################################################################
		const cadcam::mwPoint3d GetCenterRelative() const
		{
			return m_centerRelative;
		}
		//#############################################################################
		void SetCenterRelative(const cadcam::mwPoint3d& _center)
		{
			m_centerRelative = _center;
		}
		//#############################################################################
		const cadcam::mwPoint3d GetCenterAbsolute() const
		{
			return m_centerAbsolute;
		}
		//#############################################################################
		void SetCenterAbsolute(const cadcam::mwPoint3d& _center)
		{
			m_centerAbsolute = _center;
		}
		//#############################################################################
		const flag GetFlag() const
		{
			return m_flag;
		}
		//#############################################################################
		void SetFlag(const flag _flag)
		{
			m_flag = _flag;
		}
		//#############################################################################
		const cadcam::mwPoint3d GetNormal() const
		{
			return m_normal;
		}
		//#############################################################################
		void SetNormal(const cadcam::mwPoint3d& _normal)
		{
			m_normal = _normal;
		}
		//#############################################################################
		//! Helix sweep angle in degree
		const double GetArcSweep() const
		{
			return m_arcSweep;
		}
		//#############################################################################
		//! Set Helix sweep angle in degree
		void SetArcSweep(const double _arcSweep)
		{
			m_arcSweep = _arcSweep;
		}
		//#############################################################################
		//! Helix height along the normal
		const double GetHelixHeight() const
		{
			return m_helixHeight;
		}
		//#############################################################################
		//! Set Helix height along the normal
		void SetHelixHeight(const double _helixHeight)
		{
			m_helixHeight = _helixHeight;
		}
		//#############################################################################
		const postedListVector& GetAllInterpolateMoves() const
		{
			return m_postedListVector;
		}
		//#############################################################################
		void SetAllInterpolateMoves(const postedListVector& _postedListVector)
		{
			m_postedListVector = _postedListVector;
		}
		//#############################################################################
	private:
		//#############################################################################
		direction         m_direction;
		type              m_type;
		double            m_radius;
		cadcam::mwPoint3d m_centerRelative;
		cadcam::mwPoint3d m_centerAbsolute;
		flag              m_flag;
		cadcam::mwPoint3d m_normal;
		double            m_helixHeight;
		double            m_arcSweep;
		postedListVector  m_postedListVector;
		//#############################################################################
	};//end class mwPostedArcMove
	//#############################################################################
	typedef misc::mwAutoPointer<mwPostedArcMove> mwPostedArcMovePtr;
	//#############################################################################
};//end namespace post

#endif
