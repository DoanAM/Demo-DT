// (C) 2014-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDREVOLVINGSET_HPP_
#define MW_MKDREVOLVINGSET_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdCoordinateTransform.hpp"

namespace machsim
{
	class MW_SIMUTIL_API mkdRevolvingSet : public mkdCoordinateTransform
	{
		public:
			typedef misc::mwAutoPointer<mkdRevolvingSet>		Ptr;

			/*! Parameterized constructor
				\param newID the name of this object.
				\param isWorkpiece specify if this set is for workpiece spindle or for tool spindle
				\param unit the unit of measure.
			 */
			mkdRevolvingSet(const id& newID, const bool isWorkpiece, const measures::mwMeasurable::Units& unit);
			
			//! Destructor
			virtual ~mkdRevolvingSet();

			virtual void SetIsTool(const bool &isTool);
			virtual void SetIsWorkpiece(const bool &isWorkpiece);

			virtual const bool IsTool() const;
			virtual const bool IsWorkpiece() const;

			virtual void SetReverseSpindleOrientation(const bool &isReverse);
			virtual const bool IsReverseSpindleOrientation() const;

			//! Visitor
			virtual void AcceptVisitor(mkdKOVisitor &visitor);

			//! Visitor
			virtual void AcceptVisitor(mkdKOConstVisitor &visitor) const;

			virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 

		protected:

			bool						m_isReverse;
			bool						m_isWorkpiece;

		private:
	};

};
#endif	//	MW_MKDREVOLVINGSET_HPP_
