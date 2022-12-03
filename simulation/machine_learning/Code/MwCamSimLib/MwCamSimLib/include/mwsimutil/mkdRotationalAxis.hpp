// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDROTATIONALAXIS_HPP_
#define MW_MKDROTATIONALAXIS_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdAxis.hpp"


namespace machsim
{
	class MW_SIMUTIL_API mkdRotationalAxis : public mkdAxis
	{
	public:
		typedef misc::mwAutoPointer<mkdRotationalAxis> Ptr;

		/*! Parameterized constructor
			\param newID the object name
			\param newDirection the vector of this axis.
			\param newCenterPoint the rotation center of this axis.
			\param unit the unit of measure.
		 */
		mkdRotationalAxis(const id& newID,
			const vector &newDirection,
			const point &newCenterPoint,
			const measures::mwMeasurable::Units& unit );

		//!Set center point
		/*!Set new center point of the axis
			\param newCenterPoint the center point to set
		*/
		void SetCenterPoint(const point& newCenterPoint);

		//!Get center point
		/*!Get center point of the axis
			\returns current center point of the axis
		*/
		const point &GetCenterPoint() const;

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
		void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor);

		virtual void ParametrizationChange();

		//! Calculate the matrix of this object.
		const matrix CalculateValueMatrix();


	private:
		
		void ResetStoredValue();

		point	mCenterPoint;
		matrix	m_storedValueMatrix;
		double  m_storedValue;
	};

};
#endif	//	MW_MKDROTATIONALAXIS_HPP_
