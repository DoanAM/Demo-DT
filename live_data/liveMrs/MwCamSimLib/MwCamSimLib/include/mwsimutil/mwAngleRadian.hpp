// (C) 2003-2006 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWANGLERADIAN_HPP_
#define MW_MWANGLERADIAN_HPP_
#include "mwDllImpExpDef.hpp"

namespace measures
{
	template <typename T>
	class MW_5AXUTIL_API mwAngleRadian
	{
	private:
		typedef mwAngleRadian						Myself;
	public:		
		//#############################################################################
		//! Constructor
		explicit mwAngleRadian(const T &newAngle);
		//#############################################################################
		//! Copy Constructor
		mwAngleRadian(const mwAngleRadian<T>& rToCopy);
		//#############################################################################
		virtual ~mwAngleRadian(){};
		//########################## Operators ########################################			
		//!Assignment operator
		/*!Assigns one mwAngleRadian object to another
		\param toCopy mwAngleRadian to copy the information from
		\returns current mwAngleRadian with copied information
		*/
		const mwAngleRadian<T> &operator=( const mwAngleRadian<T> &rToCopy );
		//#############################################################################
		//!Equality operator in tolerance
		/*!Are given mwAngleRadian equal?
		\param toCompare tool to compare the current measurable with
		\returns <b>true</b> if both mwLenght contain the same parameters,
		<b>false</b> otherwise
		*/
		bool operator==( const mwAngleRadian<T> &rToCompare ) const;
		//#############################################################################
		//! Set Length
		/*
		\param units - will perform a scale if units is different from 
		the current one and set the current measure with units
		*/
		void SetAngle(const T &newAngle);
		//#############################################################################
		//! Get units
		/*
		\return units - obtain the current units
		*/
		inline const T GetAngle() const
		{
			return m_angle;
		}
		//#############################################################################		
	protected:
		//#############################################################################
		T m_angle;
	};
	//#############################################################################
};
#endif	//	MW_MWANGLERADIAN_HPP_
