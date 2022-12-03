// (C) 2004-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDTOOLPATHGEOMETRY_HPP_
#define MW_MKDTOOLPATHGEOMETRY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdGeometry.hpp"
#include "mwAutoPointer.hpp"
#include "mw3dPolyLine.hpp"
#include "mwEASCIIParser.hpp"


namespace tpgraphic
{
	class mwToolpathBaseManager;
}

namespace machsim
{
	class MW_SIMUTIL_API mkdToolpathGeometry : public mkdGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdToolpathGeometry>	Ptr;
		
		//! tool path data representation
		typedef machsim::mwEASCIIParser::PolyLine			PolyLine;		
		typedef machsim::mwEASCIIParser::coloredPolyLine	coloredPolyLine;
		typedef machsim::mwEASCIIParser::polyData			polyData;
		typedef machsim::mwEASCIIParser::polyDataRef 		polyDataRef;

		/*! Parameterized constructor
			\param newID the name of this object.
			\param STLFileName the file associated with the content of this object.
			\param unit the unit of measure.
		 */
		mkdToolpathGeometry(const id& newID,
			const misc::mwstring& STLFileName,
			measures::mwUnitsFactory::Units unit);

		//! Returns the path to the file associated with the content of this object.
		const misc::mwstring& GetSTLFileName() const;

		/*! Sets the path to the file associated with the content of this object.
			\param newSTLFileName the file path.
		 */
		void SetSTLFileName(const misc::mwstring& newSTLFileName);

		//! Return the tool path manager responsible for creating/drawing,etc
		//! the content of this object.
		tpgraphic::mwToolpathBaseManager*  GetToolpathManager() const;

		/*! Sets the tool path manager responsible for creating/drawing,etc
			the content of this object.
			\param toolpathManager point to the tool path manager.
		 */
		void SetToolpathManager(tpgraphic::mwToolpathBaseManager* toolpathManager);


		//! Visitor
		virtual void AcceptVisitor(mkdKOVisitor &visitor);

		//! Visitor
		virtual void AcceptVisitor(mkdKOConstVisitor &visitor) const;	

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 
	
	protected:
		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor);

	private:
		misc::mwstring						mSTLFileName;
		tpgraphic::mwToolpathBaseManager*	m_toolpathManager ;
		
	};
};
#endif	//	MW_MKDTOOLPATHGEOMETRY_HPP_
