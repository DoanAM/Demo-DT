// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWMEASURABLE_HPP_
#define MW_MWMEASURABLE_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwUnitsFactory.hpp"
#include "mwCachingInternalDefs.hpp"


namespace measures
{
	#pragma CACHING_INTERNAL_BEGIN
	class MW_5AXUTIL_API MW_5AXCORE_API mwMeasurable
	{
	public:
		typedef mwUnitsFactory::Units	Units;
//#############################################################################
		//! Constructor
		mwMeasurable(Units units );
//#############################################################################
		//! Copy Constructor
		mwMeasurable( const mwMeasurable& rToCopy );
//#############################################################################
		virtual ~mwMeasurable(){};
//########################## Operators ########################################			
		//!Assignment operator
		/*!Assigns one measurable object to another
		  \param toCopy measurable to copy the information from
		  \returns current measurable with copied information
		*/
		const mwMeasurable &operator=( const mwMeasurable& rToCopy );
//#############################################################################
		//!Equality operator
		/*!Are given measures equal?
		  \param toCompare tool to compare the current measurable with
		  \returns <b>true</b> if both measures contain the same parameters,
		  <b>false</b> otherwise
		*/
		bool operator==( const mwMeasurable& rToCompare ) const;
//#############################################################################
        //! Set units
        /*! if scalingDisabled is true will set the current measure to units
        /! otherwise will perform a scale if units is different from the current
        /! one and set the current measures to units
        
            \param units - measures unit to set
            \param scalingDisabled - false: perform scale, true: do not perform scale;
        */
        void SetUnits( const Units units, const bool scalingDisabled = false ) ;
//#############################################################################
		//! Get units
		/*
			\return units - obtain the current units
		*/
		inline Units GetUnits() const
		{
			return m_Units;
		}

//#############################################################################
		static double GetMM2INCH();
		static double GetINCH2MM();
		static double GetMETRIC_MAX_DOUBLE();
		static double GetINCH_MAX_DOUBLE();

//#############################################################################		
	protected:
		//! Scale, it is called on SetUnits function from this base class
        /*! each derived class must implement this to proper scale it's members 
        /! and proper set it's members units. 
        /! Note you may get scale factor 1, this means you have to call SetUnits with
		   scalingDisabled on true, use PropagateUnitsChange for such members
            \param units - measures unit to set on members (consider use of PropagateUnitsChange)
            \param scaleFactor - value to use for scaling, it may be 1 if scalingDisabled was true (use PropagateUnitsChange)
        */
		virtual void Scale( const Units units, const double& scaleFactor ) = 0;
		//! propagates the unnits change with or without scaling based on the scale factor value
		inline void PropagateUnitsChange (mwMeasurable& toBeChangedOnNewUnits, const Units units,const double& scaleFactor)
			{ toBeChangedOnNewUnits.SetUnits (units , scaleFactor==1); };
//#############################################################################
	public:
//#############################################################################
		//!Factor for scaling millimeters to inches
		static const double MW_MM2INCH;
		//!Factor for scaling inches to millimeters
		static const double MW_INCH2MM;

		//!Maximum metric value
		static const double MW_METRIC_MAX_DOUBLE;
		//!Maximum inch value used so there won't be any overflow exceptions when scaling from inch to metric
		static const double MW_INCH_MAX_DOUBLE;

	private:
//#############################################################################
		//! Copies data
		void Copy(const mwMeasurable& rToCopy);
//#############################################################################
		void Validate(const Units units);
//#############################################################################
		Units m_Units;

	};
	#pragma CACHING_INTERNAL_END
//#############################################################################
}
#endif	//	MW_MWMEASURABLE_HPP_
