// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDTRANSLATIONALAXIS_HPP_
#define MW_MKDTRANSLATIONALAXIS_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdAxis.hpp"




namespace machsim
{
	class MW_SIMUTIL_API mkdTranslationalAxis : public mkdAxis
	{
	public:
		typedef misc::mwAutoPointer< mkdTranslationalAxis > Ptr;

		/*! Parameterized constructor
			\param newID the name of this axis.
			\param newDirection the axis vector.
			\param unit the unit of measure.
		 */
		mkdTranslationalAxis(const id& newID, 
			const vector& newDirection , 
			const measures::mwMeasurable::Units& unit );

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;

		/*! Calculate the transformation matrix of this object for a given axis value.
			\param value axis value for which the matrix will be calculated.
			\param resultingMatrix the calculated matrix.
		 */
		void CalculateValueMatrix(const float& value, matrix& resultingMatrix) const;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 

	protected:
		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor) ;


		//! Calculate the matrix of this object.
		const matrix CalculateValueMatrix();
	private:
	};

};
#endif	//	MW_MKDTRANSLATIONALAXIS_HPP_
