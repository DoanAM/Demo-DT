// (C) 2012-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDMOUNTADAPTER_HPP_
#define MW_MKDMOUNTADAPTER_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdCoordinateTransform.hpp"


namespace machsim
{	
	class MW_SIMUTIL_API mkdMountAdapter  : public mkdCoordinateTransform
	{
		public:
			typedef misc::mwAutoPointer< mkdMountAdapter > Ptr;

			/*! Parameterized constructor
				\param newID the name of the object.
				\param unit the unit of measure
			 */
			mkdMountAdapter(const id& newID , const measures::mwMeasurable::Units& unit );
			
			//! Destructor
			virtual ~mkdMountAdapter();
			
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
			void Scale(const Units unit, const double& scaleFactor);
		
		private:
	};
};
#endif	//	MW_MKDMOUNTADAPTER_HPP_
