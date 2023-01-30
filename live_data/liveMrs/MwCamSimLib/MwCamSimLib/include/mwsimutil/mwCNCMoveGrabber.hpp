// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWCNCMOVEGRABBER_HPP_
#define MW_MWCNCMOVEGRABBER_HPP_
#include "mwCNCMove.hpp"
#include "mw3axMove.hpp"
#include "mw5axMove.hpp"
#include "mw5axMarkedMove.hpp"
#include "mw6axMove.hpp"
#include "mwPostException.hpp"
#include "mwPostCommonDefinitions.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwCNCMoveGrabber
	{
	public:
		//#############################################################################
		enum moveType
		{
			UNDEFINED,
			MOVE_CNC,
			MOVE_3AX,
			MOVE_5AX,
			MOVE_6AX
		};
		//#############################################################################
		typedef misc::mwAutoPointer<cadcam::mwCNCMove> mwCNCMovePtr;
		typedef misc::mwAutoPointer<cadcam::mw3axMove> mw3axMovePtr;
		typedef misc::mwAutoPointer<cadcam::mw5axMove> mw5axMovePtr;
		typedef misc::mwAutoPointer<cadcam::mw6axMove> mw6axMovePtr;
		//#############################################################################
		static mwCNCMovePtr Clone(const mwCNCMovePtr& toClone);
		//#############################################################################
		static moveType GetMoveType(const mwCNCMovePtr& toCheck);
		//#############################################################################
		static mw3axMovePtr SafeCast3ax(mwCNCMovePtr& toCast);
		//#############################################################################
		static const mw3axMovePtr SafeCast3ax(const mwCNCMovePtr& toCast);
		//#############################################################################
		static mw5axMovePtr SafeCast5ax(mwCNCMovePtr& toCast);
		//#############################################################################
		static const mw5axMovePtr SafeCast5ax(const mwCNCMovePtr& toCast);
		//#############################################################################
		static mw6axMovePtr SafeCast6ax(mwCNCMovePtr& toCast);
		//#############################################################################
		static const mw6axMovePtr SafeCast6ax(const mwCNCMovePtr& toCast);
		//#############################################################################
		static void ContactSurfacePtTransformation(
			mwCNCMovePtr& move,
			const post::mwMatrix4dPtr& translationAndRotation,
			const post::mwMatrix3dPtr& rotationOnly);
		//#############################################################################
		static void ContactSurfacePtTransformation(
			mwCNCMovePtr& move,
			const post::mwMatrix4d& rotationOnly);
		//#############################################################################
	private:
		mwCNCMoveGrabber& operator=(const mwCNCMoveGrabber&) { return *this; }
		//#############################################################################
		class mwCastingChecker : public cadcam::mwCNCMoveVisitor 
		{
		public:
			enum AxisTypes
			{
				mwCasting_3AXIS = 0,
				mwCasting_5AXIS = 1,
				mwCasting_6AXIS = 2
			};
			mwCastingChecker(AxisTypes axisTypes) 
				: m_AxisTypes(axisTypes)
			{

			}
			void Visit(const cadcam::mwCNCMove& /*visitor*/)
			{
				throw mwPostException(mwPostException::ABSTRACT_CNCMOVE_USED);
			}
			void Visit(const cadcam::mw3axMove& /*visitor*/)
			{
				if(m_AxisTypes != mwCasting_3AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
			}
			void Visit(const cadcam::mw5axMove& /*visitor*/) 
			{
				if(m_AxisTypes != mwCasting_5AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
			}
			void Visit(const cadcam::mw5axMarkedMove& /*visitor*/)
			{
				if (m_AxisTypes != mwCasting_5AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
			}
			void Visit(const cadcam::mw6axMove& /*visitor*/) 
			{
				if(m_AxisTypes != mwCasting_6AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
			}
			//#############################################################################
		private:
			AxisTypes m_AxisTypes;
			//#############################################################################
		};// end class mwCastingChecker
		//#############################################################################
		class mwCNCMoveCloner : public cadcam::mwCNCMoveVisitor 
		{
		public:
			//#############################################################################
			mwCNCMoveCloner(mwCNCMovePtr& clone)
				: m_clone(clone)
			{
			}
			//#############################################################################
			virtual void Visit( const cadcam::mwCNCMove &/*mw*/ )
			{
				throw mwPostException(mwPostException::ABSTRACT_CNCMOVE_USED);
			}
			//#############################################################################
			virtual void Visit( const cadcam::mw3axMove &mw )
			{
				m_clone = new cadcam::mw3axMove(mw);
			}
			//#############################################################################
			virtual void Visit( const cadcam::mw5axMove &mw )
			{
				m_clone = new cadcam::mw5axMove(mw);
			}
			//#############################################################################
			virtual void Visit(const cadcam::mw5axMarkedMove &mw)
			{
				m_clone = new cadcam::mw5axMarkedMove(mw);
			}
			//#############################################################################
			virtual void Visit( const cadcam::mw6axMove &mw )
			{
				m_clone = new cadcam::mw6axMove(mw);
			}
			//#############################################################################
		private:
			//#############################################################################
			//mwCNCMoveCloner(): m_clone(0){};// avoid warning c4510
			mwCNCMoveCloner& operator=(const mwCNCMoveCloner&) { return *this; }
			mwCNCMovePtr& m_clone;
			//#############################################################################
		};// end class mwCNCMoveCloner
		//#############################################################################
		class mwCNCMoveContactSurfacePointTransf : public cadcam::mwCNCMoveVisitorSetter
		{
		public:
			//#############################################################################
			mwCNCMoveContactSurfacePointTransf(
				const post::mwMatrix4dPtr& translationAndRotation,
				const post::mwMatrix3dPtr& rotationOnly)
				: m_translationAndRotation(translationAndRotation)
				, m_rotationOnly(rotationOnly)
			{
			}
			//#############################################################################
			virtual void Visit(cadcam::mwCNCMove &/*mw*/)
			{
				throw mwPostException(mwPostException::ABSTRACT_CNCMOVE_USED);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw3axMove &/*mw*/)
			{
				//
			}
			//#############################################################################
			virtual void Visit(cadcam::mw5axMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw5axMarkedMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw6axMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
		private:
			//#############################################################################
			//mwCNCMoveContactSurfacePointTransf(): m_clone(0){};// avoid warning c4510
			mwCNCMoveContactSurfacePointTransf& operator=(const mwCNCMoveContactSurfacePointTransf&) { return *this; }
			const post::mwMatrix4dPtr& m_translationAndRotation;
			const post::mwMatrix3dPtr& m_rotationOnly;
			void Transform(cadcam::mw5axMove &mw)
			{
				double d = ~(mw.GetPosition() - mw.GetPotentialSurfaceCP()); d;

				if (mw.HasPotentialSurfContactPoint())
				{
					if (m_translationAndRotation.IsNotNull())
					{
						cadcam::mwPoint3d position = mw.GetPotentialSurfaceCP();
						position.Transform(*m_translationAndRotation);
						mw.SetPotentialSurfaceCP(position);
					}
					if (m_rotationOnly.IsNotNull())
					{
						cadcam::mwPoint3d orientation = mw.GetPotentialSurfaceCPOrient();
						orientation.Transform(*m_rotationOnly);
						mw.SetPotentialSurfaceCPOrient(orientation);
					}
				}
				
			}
			//#############################################################################
		};// end class mwCNCMoveContactSurfacePointTransf
		//#############################################################################
		class mwCNCMoveContactSurfacePointTransf2 : public cadcam::mwCNCMoveVisitorSetter
		{
		public:
			//#############################################################################
			mwCNCMoveContactSurfacePointTransf2(
				const post::mwMatrix4d& rotOnly)
				: m_rotOnly(rotOnly)
			{
			}
			//#############################################################################
			virtual void Visit(cadcam::mwCNCMove &/*mw*/)
			{
				throw mwPostException(mwPostException::ABSTRACT_CNCMOVE_USED);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw3axMove &/*mw*/)
			{
				//
			}
			//#############################################################################
			virtual void Visit(cadcam::mw5axMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw5axMarkedMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
			virtual void Visit(cadcam::mw6axMove &mw)
			{
				Transform(mw);
			}
			//#############################################################################
		private:
			//#############################################################################
			//mwCNCMoveContactSurfacePointTransf2(): m_clone(0){};// avoid warning c4510
			mwCNCMoveContactSurfacePointTransf2& operator=(const mwCNCMoveContactSurfacePointTransf2&) { return *this; }
			const post::mwMatrix4d& m_rotOnly;
			void Transform(cadcam::mw5axMove &mw)
			{
				if (mw.HasPotentialSurfContactPoint())
				{
					cadcam::mwPoint3d position = mw.GetPotentialSurfaceCP();
					position.Transform(m_rotOnly);
					mw.SetPotentialSurfaceCP(position);

					cadcam::mwPoint3d orientation = mw.GetPotentialSurfaceCPOrient();
					orientation.Transform(m_rotOnly);
					mw.SetPotentialSurfaceCPOrient(orientation);
				}
			}
			//#############################################################################
		};// end class mwCNCMoveContactSurfacePointTransf
		//#############################################################################
	};// end class mwCNCMoveGrabber
	//#############################################################################
}// end namespace
//#############################################################################
#endif	//	MW_MWCNCMOVEGRABBER_HPP_
