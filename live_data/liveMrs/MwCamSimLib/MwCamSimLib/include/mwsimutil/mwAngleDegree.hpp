// (C) 2003-2006 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWANGLEDEGREE_HPP_
#define MW_MWANGLEDEGREE_HPP_
#include "mwDllImpExpDef.hpp"

namespace measures
{
	template <typename T>
	class MW_5AXUTIL_API mwAngleDegree
	{
	private:
		typedef mwAngleDegree						Myself;
	public:		
		//#############################################################################
		//! Constructor
		explicit mwAngleDegree(const T &newAngle);
		//#############################################################################
		//! Copy Constructor
		mwAngleDegree(const mwAngleDegree& rToCopy);
		//#############################################################################
		virtual ~mwAngleDegree(){};
		//########################## Operators ########################################			
		//!Assignment operator
		/*!Assigns one mwAngleDegree object to another
		\param toCopy mwAngleDegree to copy the information from
		\returns current mwAngleDegree with copied information
		*/
		const mwAngleDegree<T> &operator=( const mwAngleDegree<T> &rToCopy );
		//#############################################################################
		//!Equality operator in tolerance
		/*!Are given mwAngleDegree equal?
		\param toCompare tool to compare the current measurable with
		\returns <b>true</b> if both mwLenght contain the same parameters,
		<b>false</b> otherwise
		*/
		bool operator==( const mwAngleDegree &rToCompare ) const;
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
#endif	//	MW_MWANGLEDEGREE_HPP_
