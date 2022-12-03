// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDAXIS_HPP_
#define MW_MKDAXIS_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdCoordinateTransform.hpp"
#include "mwDiscreteValue.hpp"
#include <map>

namespace machsim
{
	class MW_SIMUTIL_API mkdAxis : public mkdCoordinateTransform
	{
	public:
		typedef misc::mwAutoPointer<mkdAxis>		Ptr;
		typedef misc::mwAutoPointer< misc::mwValueValidator<double> > valueValidator;
		typedef cadcam::mwTPoint3d<float>			vector;
		typedef cadcam::mwTPoint3d<float>			point;

		enum abnormalityType
		{
			MW_UNDERFLOW,
			MW_OVERFLOW,
			MW_MISMATCH,
			MW_NONE = 100
		};
		
		/*! Parameterized constructor
			\param newID the name of this axis.
			\param newDirection the axis vector.
			\param unit the unit of measure.
		 */
		mkdAxis(const id& newID,
			const vector& newDirection,
			const measures::mwMeasurable::Units& unit);

		//! Destructor
		virtual ~mkdAxis()=0;
		
		//!Set direction
		/*!
			\param newDir new direction to assign to the axis
		*/
		void SetDirection( const vector& newDir );

		//!Set the initial direction
		/*!
			\param newInitialDir new initial direction to assign to the axis
		*/
		void SetInitialDirection( const vector& newInitialDir );

		//!Get direction
		/*!
			\returns current direction of the axis
		*/
		const vector& GetDirection() const;

		//!Get the initial direction
		/*!
			\returns the initial direction of the axis
		*/
		const vector& GetInitialDirection() const;
		
		
		/*! Sets axis value.
			\param newValue new value to apply to the axis
			\returns abnormality type 
		*/
		abnormalityType SetValue( const double& newValue );
		
		
		//! Returns current axis value.		
		const double& GetValue() const;

		//!Is discrete
		/*!Does current axis only accept some predefined values?
			\returns true if the axis is discrete false otherwise
		*/
		const bool IsDiscrete() const;

		//!Set discrete value validator
		/*!Set discrete value validator for this axis - could be either list or stepping based
		\param validator the new validator
		*/
		void SetDiscreteValueValidator( const misc::mwDiscreteValue<double>::valueValidator& validator );

		//! Returns the discrete value validator.
		const misc::mwDiscreteValue<double>::valueValidator& GetDiscreteValueValidator() const;

		//!Set min value
		/*!Set minimum allowed value for this axis
			\param toSet new minimum limit for this axis
		*/
		void SetMinLimit( const double& toSet);

		//!Set max value
		/*!Set maximum allowed value for this axis
			\param toSet new maximum limit for this axis
		*/
		void SetMaxLimit( const double& toSet );

		//!Get min value
		/*!Get minimum allowed value for this axis
			\returns minimum limit for this axis
		*/
		const double& GetMinLimit() const;

		//!Get max value
		/*!Get maximum allowed value for this axis
			\returns maximum limit for this axis
		*/
		const double& GetMaxLimit() const;

		//!Set initial value
		/*!Set an initial value for this axis
		\param toSet value 
		*/
		void SetInitialValue( const double& toSet );
		
		//!Get initial value
		/*!Get initial value for this axis
		*/
		const double& GetInitialValue() const;
		
		/*!Set the coordinate system.
			\param newCS the new coordinate system matrix.
		 */
		virtual void SetCoordinateSystem( const matrix& newCS );

		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		void Scale( const measures::mwMeasurable::Units units, const double& scaleFactor ) ;

		//! Set visibility restriction
		void SetShowSlider(bool show);

		//! Get visibility restriction
		bool GetShowSlider() const;

		//Clone

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false )=0; 
		

	protected:
		
		//!Calculate value matrix
		virtual const matrix CalculateValueMatrix() = 0;
		virtual void ParametrizationChange();
		//! used on cloning to avoid code duplication in derived classes
		void BaseAxisClone(mkdAxis& source); 

		vector					m_direction;
		vector					m_initialDirection;

	private:
		
		double					m_value;
		double					m_minLimit;
		double					m_maxLimit;
#pragma warning(suppress:4251)
		valueValidator			m_valueValidator;

		double					m_initialValue;
		bool					m_showSlider;

		mutable double			m_cncValue;
		mutable double			m_cncMinLimit;
		mutable double			m_cncMaxLimit;
		mutable double			m_cncInitialValue;
	};

};
#endif	//	MW_MKDAXIS_HPP_
