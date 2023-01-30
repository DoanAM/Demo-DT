// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDKINEMATICOBJECT_HPP_
#define MW_MKDKINEMATICOBJECT_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwStringConversions.hpp"
#include "mwMatrix.hpp"
#include "mwTPoint3d.hpp"
#include "mwAutoPointer.hpp"
#include "mwMeasurable.hpp"
#include <list>
#include "mwDefines.hpp"

namespace machsim
{
namespace detail
{
class mwMachineItemNodeProxy;
}
}

namespace machsim
{
	typedef cadcam::mwHomogenousMatrix		mkdHomogenousMatrix;
	typedef cadcam::mwTPoint3d<float>		mkdDirection;
			
	class mkdKOVisitor;
	class mkdKOConstVisitor;
	class mkdKinematicTreeInterface;


	//! class mkdKinematicObject	
	class MW_SIMUTIL_API mkdKinematicObject : public measures::mwMeasurable
	{
	public:
		typedef misc::mwAutoPointer<mkdKinematicObject>			Ptr;
		typedef misc::mwstring									id;
		typedef mkdHomogenousMatrix								matrix;
		typedef mkdDirection									vector;
		
		
		/*! Parameterized constructor
			\param newID the name of this object.
			\param unit the unit of measure.
		 */
		mkdKinematicObject(const id &newID, const measures::mwMeasurable::Units& unit);
		
		//! Destructor
		virtual ~mkdKinematicObject();
		
		/*! Sets the name of this object
			\param newID the new name for this object
		 */
		void SetID(const id& newID);

		//! Returns the name of this object.
		const id &GetID() const;
					
		//!Set the local coordinate system
		/*!Sets the local coordinate system 
			(in the parent coordinates)
			\param newCS new coordinate system to be used
		*/
		virtual void SetCoordinateSystem(const matrix &newCS);

		//!Gets the coordinate system
		/*!
			\returns the local coordinate system currently used by 
			the object
		*/
		const matrix &GetCoordinateSystem() const;
		
		/*! Sets the kinematic tree interface.
			\param newEventSink the new kinematic tree interface.
		 */
		void SetKinematicTree(mkdKinematicTreeInterface* newEventSink);

		
		//! Visitor
		virtual void AcceptVisitor(mkdKOVisitor &visitor) = 0;

		//! Visitor
		virtual void AcceptVisitor(mkdKOConstVisitor &visitor) const = 0;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false )=0;
		
		
	public:
		bool HasCNCSimProxy() const { return m_pCncsimNodeProxy != nullptr; }
		detail::mwMachineItemNodeProxy& GetCNCSimProxy() { return *m_pCncsimNodeProxy; }
		const detail::mwMachineItemNodeProxy& GetCNCSimProxy() const { return *m_pCncsimNodeProxy; }
		void SetCNCSimProxy(std::shared_ptr<detail::mwMachineItemNodeProxy> proxy);

	protected:
		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		virtual void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor) = 0;

		/*! Uses the internal kinematic tree to propagate the given matrix to the 
			children of this kinematic object.
			\param toPropagate the matrix to propagate to children.
		 */
		void PropagateMatrix(const matrix& toPropagate);
		
		//! used on cloning to avoid code duplication in derived classes
		void BaseKObjectClone(mkdKinematicObject& source);

#ifndef MW_USE_VS2008_COMPATIBILITY
		virtual void OnCNCSimHandleSet();
#endif

	private:
		id									mID;
		matrix								mLocalCS;		
		mkdKinematicTreeInterface*			mKinematicTree;//this should be always NULL until the simulator is placeing the object in the machine tree  

#pragma warning(suppress:4251)
		std::shared_ptr<detail::mwMachineItemNodeProxy>			m_pCncsimNodeProxy;
	};


	//!Abstract kinematic tree interface.
	class mkdKinematicTreeInterface
	{
	public:
		virtual ~mkdKinematicTreeInterface() = default;

		virtual void PropagateMatrixToChildren( 
			const mkdKinematicObject &thisObject, 
			const mkdKinematicObject::matrix &toPropagate ) = 0;

		virtual void MatrixChangeFeedback( 
			const mkdKinematicObject &thisObject,
			const mkdKinematicObject::matrix &oldState, 
			const mkdKinematicObject::matrix &currentState ) = 0;
	protected:
	private:
	};


	//!Forward declarations for all machine kinematic elements.
	class mkdGeometry;
	class mkdPolygonalGeometry;
	class mkdCoordinateTransform;
	class mkdRevolvingSet;
	class mkdRotationalAxis;
	class mkdTranslationalAxis;
	class mkdToolpathGeometry;
	class mkdHeldTool;
	class mkdWorkPiece;
	class mkdFixture;
	class mkdStockGeometry;
	class mkdTailStock;
	class mkdInitialStock;
	class mkdWireEDMHead;
	class mkdMountAdapter;


	//!Interface to be implemented by a kinematic object visitor class.
	class MW_SIMUTIL_API mkdKOVisitor 
	{
	public:
		virtual ~mkdKOVisitor(){};
		virtual void Visit( mkdKinematicObject &toVisit ) = 0;
		virtual void Visit( mkdPolygonalGeometry &toVisit ) = 0;
		virtual void Visit( mkdToolpathGeometry &toVisit ) = 0;
		virtual void Visit( mkdHeldTool &toVisit ) = 0;
		virtual void Visit( mkdCoordinateTransform &toVisit ) = 0;
		virtual void Visit( mkdRevolvingSet &toVisit ) = 0;
		virtual void Visit( mkdRotationalAxis &toVisit ) = 0;
		virtual void Visit( mkdTranslationalAxis &toVisit ) = 0;
		virtual void Visit( mkdWorkPiece &toVisit ) = 0;
		virtual void Visit( mkdFixture &toVisit ) = 0;
		virtual void Visit( mkdStockGeometry &toVisit ) = 0;
		virtual void Visit( mkdTailStock &toVisit ) = 0;
		virtual void Visit( mkdInitialStock &toVisit ) = 0;
		virtual void Visit( mkdWireEDMHead &toVisit ) = 0;
		virtual void Visit( mkdMountAdapter &toVisit ) = 0;
	};
	

	//!Interface to be implemented by a kinematic (const) object visitor class.
	class MW_SIMUTIL_API mkdKOConstVisitor 
	{
	public:
		virtual ~mkdKOConstVisitor(){};
		virtual void Visit( const mkdKinematicObject &toVisit ) = 0;
		virtual void Visit( const mkdPolygonalGeometry &toVisit ) = 0;
		virtual void Visit( const mkdToolpathGeometry &toVisit ) = 0;
		virtual void Visit( const mkdHeldTool &toVisit ) = 0;
		virtual void Visit( const mkdCoordinateTransform &toVisit ) = 0;
		virtual void Visit( const mkdRevolvingSet &toVisit ) = 0;
		virtual void Visit( const mkdRotationalAxis &toVisit ) = 0;
		virtual void Visit( const mkdTranslationalAxis &toVisit ) = 0;
		virtual void Visit( const mkdWorkPiece &toVisit ) = 0;
		virtual void Visit( const mkdFixture &toVisit ) = 0;
		virtual void Visit( const mkdStockGeometry &toVisit ) = 0;
		virtual void Visit( const mkdTailStock &toVisit ) = 0;
		virtual void Visit( const mkdInitialStock &toVisit ) = 0;
		virtual void Visit( const mkdWireEDMHead &toVisit ) = 0;
		virtual void Visit( const mkdMountAdapter &toVisit ) = 0;
	};

	//!Interface to be implemented by a kinematic object visitor class.
	class MW_SIMUTIL_API mkdKOSimConstVisitor : public mkdKOConstVisitor
	{
	public:
		typedef misc::mwAutoPointer< mkdKinematicObject >	mkdKOPtr;
		mkdKOSimConstVisitor()
		{
		}

		void SetCurrentParent( const mkdKOPtr& newparent )
		{
			parent = newparent;
		}

		mkdKOPtr& GetCurrentParent()
		{
			return parent;
		}

		const mkdKOPtr& GetCurrentParent() const
		{
			return parent;
		}

	private:
#pragma warning(suppress:4251)
		mkdKOPtr							parent;
	};

	//!Interface to be implemented by a kinematic (const) object visitor class.
	class MW_SIMUTIL_API mkdKOSimVisitor : public mkdKOVisitor
	{
	public:
		typedef misc::mwAutoPointer< mkdKinematicObject >	mkdKOPtr;
		mkdKOSimVisitor()
		{
		}

		void SetCurrentParent( const mkdKOPtr& newparent )
		{
			parent = newparent;
		}

		mkdKOPtr& GetCurrentParent()
		{
			return parent;
		}

		const mkdKOPtr& GetCurrentParent() const
		{
			return parent;
		}

	private:
#pragma warning(suppress:4251)
		mkdKOPtr							parent;
	};	

};
#endif	//	MW_MKDKINEMATICOBJECT_HPP_
