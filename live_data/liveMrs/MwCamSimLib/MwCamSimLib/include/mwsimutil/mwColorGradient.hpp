// (C) 2005-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWCOLORGRADIENT_HPP_
#define MW_MWCOLORGRADIENT_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwColor.hpp"

namespace mmedia
{
	//!This class represents a color gradient
	class MW_5AXUTIL_API mwColorGradient
	{
	public:
		//! The gradient types
		enum GradientTypes
		{
			horizontal = 1,
			vertical = 2,
			diagonal_falling = 3,
			diagonal_ascending = 4,
			two_thirds_of_startcolor = 5,
			one_half_of_startcolor = 6
		};

		//! Default constructor
		mwColorGradient();

		//! Constructor
		/*! Builds a mwColorGradient object using the given parameters
			\param type the gradient's "orientation"
			\param startColor 
			\param endColor
		*/
		mwColorGradient( GradientTypes type, 
			const misc::mwColor& startColor, const misc::mwColor& endColor);

		//! Gets the gradient's "orientation"
		const GradientTypes GetType() const;
		
		//! Sets the gradient's "orientation"
		/*! The GradientTypes enum is used here
			\param toSet of type GradientTypes
		*/
		void SetType( const GradientTypes toSet );
		
		//! Gets the start color
		const misc::mwColor& GetStartColor() const;
		
		//! Sets the start color
		/*! 
			\param toSet start color
		*/
		void SetStartColor(const misc::mwColor& toSet);

		//! Gets the end color
		const misc::mwColor& GetEndColor() const;
		
		//! Sets the end color
		/*! 
			\param toSet end color
		*/
		void SetEndColor(const misc::mwColor& toSet);

		//! Comparison operator
		/*! 
			\param rToCompare mwColorGradient object to be compared with
			\returns <b>true</b> if both gradients contain the same parameters,
			<b>false</b> otherwise
		*/	
		const bool operator==( const mwColorGradient& toCompare ) const;
		const misc::mwColor & GetLowerLeftCornerColor() const;
		const misc::mwColor & GetLowerRightCornerColor() const;
		const misc::mwColor & GetUpperRightCornerColor() const;
		const misc::mwColor & GetUpperLeftCornerColor() const;
	protected:
	private:
		//! The gradient's "orientation"
		GradientTypes	m_type;

#pragma warning(push)
#pragma warning(disable:4251)
		//! The gradient's start color
		misc::mwColor			m_startColor;
		//! The gradient's end color
		misc::mwColor			m_endColor;

		misc::mwColor			m_lowerLeftCornerColor;
		misc::mwColor			m_lowerRightCornerColor;
		misc::mwColor			m_upperRightCornerColor;
		misc::mwColor			m_upperLeftCornerColor;
#pragma warning(pop)

		void InitializeColors();
	};
} // mmedia namespace
#endif	//	MW_MWCOLORGRADIENT_HPP_
