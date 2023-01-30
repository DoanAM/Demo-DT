// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDCOORDINATETRANSFORM_HPP_
#define MW_MKDCOORDINATETRANSFORM_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdKinematicObject.hpp"

namespace machsim
{
	class MW_SIMUTIL_API mkdCoordinateTransform : public mkdKinematicObject
	{
		public:
			typedef misc::mwAutoPointer<mkdCoordinateTransform>		Ptr;

			/*! Parameterized constructor
				\param newID the name of this object.
				\param unit the unit of measure.
			 */
			mkdCoordinateTransform(const id& newID, const measures::mwMeasurable::Units& unit);
			
			//! Destructor
			virtual ~mkdCoordinateTransform();


			//! Returns the transformation matrix.
			const matrix &GetValueMatrix() const;
			

			/*! Sets a new transformation matrix.
				\param newValue the new matrix to apply to this object.
			 */
			void SetValueMatrix(const matrix &newValue);

			
			//! Returns the initial matrix assigned to this object.
			const matrix& GetInitialMatrix() const;
			
			/*! Sets the initial matrix for this object.
				\param newValue the initial matrix to be set.
			 */
			void SetInitialMatrix(const matrix &newValue);

			//! Returns the complete matrix that contain the propagated value.
			const matrix& GetPropagatedMatrix() const;

			/*! Sets the coordinate system matrix.
				\param newCS the new coordinate system matrix to be set.
			 */
			virtual void SetCoordinateSystem(const matrix &newCS);

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
			void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor) ;

			//! used on cloning to avoid code duplication in derived classes
			void BaseCoordinateTClone(mkdCoordinateTransform& source);


		protected:
			matrix						m_valueMatrix;
			matrix						m_initialMatrix;
			matrix						m_tmpMatrix;

	private:
	};

};
#endif	//	MW_MKDCOORDINATETRANSFORM_HPP_
