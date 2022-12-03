// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWOBJMAPFILLER_HPP_
#define MW_MWOBJMAPFILLER_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdKinematicObject.hpp"
#include "mwTree.hpp"
#include <map>

namespace machsim
{	
	//########################################################################
	//! Class mwMapValue maps an identifier to every type of kinematic object in the machine.
	class MW_SIMUTIL_API mwMapValue
	{
	public:

		typedef misc::mwTreeNode<mkdKinematicObject::Ptr>::nodeID		id;		
		typedef misc::mwstring											name;
		typedef std::map< name, mwMapValue >							GlobalMap;

		//! Kinematic element identifier
		enum dicts
		{
			MW_ALL=0,
			MW_TR_AXIS = 1,
			MW_GEOMETRIES = 2,
			MW_TOOLS = 4,
			MW_TRANSFORMS = 8,
			MW_WORKPIECES = 16,
			MW_STOCKS = 32,
			MW_TOOLPATHS = 64,
			MW_INITIALSTOCK = 128,
			MW_ROT_AXIS = 512,
			MW_FIXTURES = 1024,
			MW_WIRE_EDM_HEADS = 2048,
			MW_MOUNT_ADAPTER = 4096,
			MW_REVOLVING_SET = 8192,
			MW_TAILSTOCK = 16384,

			MW_AXIS = MW_TR_AXIS | MW_ROT_AXIS,

			//! objects that have STL file
			MW_POLYGONAL_GEOMETRY = MW_GEOMETRIES | MW_WORKPIECES
			    | MW_INITIALSTOCK | MW_FIXTURES
				| MW_STOCKS | MW_WIRE_EDM_HEADS | MW_TAILSTOCK,

			//! objects that have appearance
			MW_GEOMETRIC_OBJECT = MW_POLYGONAL_GEOMETRY | MW_TOOLS,

		};

		enum toolComponents
		{
			MW_TOOL_CUTTING		= 0,
			MW_TOOL_NONCUTTING	= 1,
			MW_TOOL_ARBOR		= 2,
			MW_TOOL_HOLDER		= 3,
		};

		//! Default constructor.
		mwMapValue()
		:	type( MW_ALL )
		{
		}

		//! Parameterized constructor
		mwMapValue( const enum dicts& _type, const id& _treeid )
		:	type( _type ),
			treeid( _treeid )
		{
		}

		//! Copy constructor
		mwMapValue( const mwMapValue& copy )
			:	type( copy.type ),
			treeid(copy.treeid )
		{
		}

		//!clone 
		misc::mwAutoPointer<mwMapValue> Clone()
		{
			misc::mwAutoPointer<mwMapValue> retObject =  new mwMapValue;
			retObject->type = type;
			retObject->treeid = treeid;
			return retObject;
 		}
		//! Returns an identifier
		const dicts& GetType() const
		{
			return type;
		}

		//! Returns a kinematic tree node
		const id& GetId() const
		{
			return treeid;
		}

	private:
		dicts									type;

#pragma warning(suppress:4251)
		id										treeid;
	};


	//########################################################################
	//! Interface used to iterate kinematic elements. 
	class mwMapIteratorInterface
	{
	public:
		virtual ~mwMapIteratorInterface() {};
		
		/*! Callback function - called by the machine simulator.
			\param name - the name of the element iterated by the simulator.
			\param value - the information about the iterated element.
		 */

		virtual void CallForElement(
			const mwMapValue::name& name,
			const mwMapValue& value) = 0;
	};


	//########################################################################
	//! Designated for internal use.
	class mwObjMapFiller : public mkdKOConstVisitor
	{
	public:
		mwObjMapFiller( mwMapValue::GlobalMap& _mObjects,
			mwMapValue::id& _treeid )
		:	mObjects( _mObjects ),
			treeid( _treeid )
		{
		}

		static bool IsMachineHousing(const misc::mwstring& id)
		{
			if (id.find(_T("mh_")) != misc::mwstring::npos)
			{
				return true;
			}
			return false;
		}

		virtual ~mwObjMapFiller(){};
		virtual void Visit( const mkdKinematicObject &toVisit );
		virtual void Visit( const mkdPolygonalGeometry &toVisit );
		virtual void Visit( const mkdToolpathGeometry &toVisit );
		virtual void Visit( const mkdHeldTool &toVisit );
		virtual void Visit( const mkdCoordinateTransform &toVisit );
		virtual void Visit( const mkdRevolvingSet &toVisit );
		virtual void Visit( const mkdRotationalAxis &toVisit );
		virtual void Visit( const mkdTranslationalAxis &toVisit );
		virtual void Visit( const mkdWorkPiece &toVisit );
		virtual void Visit( const mkdFixture &toVisit );
		virtual void Visit( const mkdStockGeometry &toVisit );
		virtual void Visit( const mkdTailStock &toVisit );
		virtual void Visit( const mkdInitialStock &toVisit );
		virtual void Visit( const mkdWireEDMHead &toVisit );
		virtual void Visit( const mkdMountAdapter &toVisit );

	private:
        // avoid warning c4512
		mwObjMapFiller& operator=(const mwObjMapFiller&);
		mwMapValue::GlobalMap&					mObjects;
		mwMapValue::id&							treeid;

		void Add( const mwMapValue::name& name,
			const mwMapValue::dicts& type );
	};

	//########################################################################
	//! Designated for internal use.
	class mwObjGetType : public mkdKOConstVisitor
	{
	public:
		static mwMapValue::dicts GetType(const mkdKinematicObject &toVisit);

		virtual void Visit( const mkdKinematicObject &toVisit );
		virtual void Visit( const mkdPolygonalGeometry &toVisit );
		virtual void Visit( const mkdToolpathGeometry &toVisit );
		virtual void Visit( const mkdHeldTool &toVisit );
		virtual void Visit( const mkdCoordinateTransform &toVisit );
		virtual void Visit( const mkdRevolvingSet &toVisit );
		virtual void Visit( const mkdRotationalAxis &toVisit );
		virtual void Visit( const mkdTranslationalAxis &toVisit );
		virtual void Visit( const mkdWorkPiece &toVisit );
		virtual void Visit( const mkdFixture &toVisit );
		virtual void Visit( const mkdStockGeometry &toVisit );
		virtual void Visit( const mkdTailStock &toVisit );
		virtual void Visit( const mkdInitialStock &toVisit );
		virtual void Visit( const mkdWireEDMHead &toVisit );
		virtual void Visit( const mkdMountAdapter &toVisit );

	private:
		mwMapValue::dicts		m_type;
	};

	//########################################################################
} //namespace
#endif	//	MW_MWOBJMAPFILLER_HPP_
