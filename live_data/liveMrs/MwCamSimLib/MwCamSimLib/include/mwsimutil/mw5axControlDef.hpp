// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MW5AXCONTROLDEF_HPP_
#define MW_MW5AXCONTROLDEF_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include <map>
#include "mwAutoPointer.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mw5axControlDef
	{
	public:
		//#############################################################################
		//! defines possible rotary limitation used on machines
		enum angleLimit
		{
			NO_LIMIT							=0,
			LIM_BETW_0_AND_360_DEG				=1,
			LIM_BETW_MINUS_180_AND_PLUS_180_DEG =2,
			VALUES_BASED_ON_MACHINE_LIMITS		=3,
			CUSTOM_VALUES						=4
		};
		//#############################################################################
		typedef misc::mwAutoPointer<mw5axControlDef> mw5axControlDefPtr;

		class MW_5AXUTIL_API RotAxisOutFormatSettings
		{
		public:
			RotAxisOutFormatSettings();

			RotAxisOutFormatSettings(angleLimit rotAngleFormattingType, short minValue = 0, short maxValue = 0);

			RotAxisOutFormatSettings(angleLimit rotAngleFormattingType, double minValue, double maxValue);

			const RotAxisOutFormatSettings& operator=(const RotAxisOutFormatSettings& toCopy);

			const bool operator==(const RotAxisOutFormatSettings& toCompare) const;

			inline const angleLimit GetRotAxOutFormatType() const { return m_rotAxisFormattingType; }

			inline void SetRotAxOutFormatType(const mw5axControlDef::angleLimit& newType) { m_rotAxisFormattingType = newType; }

			inline const double GetMax() const { return m_max; }

			inline void SetMax(const double& newValue) { m_max = newValue; }

			inline const double GetMin() const { return m_min; }

			inline void SetMin(const double& newValue) { m_min = newValue; }

		private:
			angleLimit m_rotAxisFormattingType;

			double	   m_min;
			double	   m_max;
		};

		typedef std::map<short, RotAxisOutFormatSettings>  ControlDefData;

		//! Default constructor
		/*! Creates a default mw5axControlDef object, with the following values:
		m_AngleLimitForRotAxis0 = NO_LIMIT
		m_AngleLimitForRotAxis1 = NO_LIMIT
		m_AngleLimitForRotAxis2 = NO_LIMIT
		*/
		mw5axControlDef ();
		//#############################################################################
		//! Sets control definition to default settings (NO_LIMIT,NO_LIMIT,NO_LIMIT)
		void Default();
		//#############################################################################
		//!Constructor
		/*!Constructs a mw5axControlDef object
			\param angleLimitForRotAxis0 angle limit for first rotary axis
			\param angleLimitForRotAxis1 angle limit for second rotary axis
			\param angleLimitForRotAxis2 angle limit for third rotary axis
	   */
		mw5axControlDef (const angleLimit& angleLimitForRotAxis0, 
						 const angleLimit& angleLimitForRotAxis1,
						 const angleLimit& angleLimitForRotAxis2 = NO_LIMIT);

		//#############################################################################
		mw5axControlDef(const ControlDefData& controlDefData);
		//#############################################################################
		//! copy constructor
		/*!Creates a new  mw5axControlDef object from an existing one
			\param toCopy the existing mw5axControlDef 
		*/
		mw5axControlDef( const mw5axControlDef &toCopy );
		//#############################################################################
		//!Copy operator
		/*!Creates an exact copy of an existing mw5axControlDef object
			\param toCopy the existing mw5axControlDef that will be copied 
				in the current object
			
		*/
		const mw5axControlDef &operator=( const mw5axControlDef &toCopy );
		//#############################################################################
		//! Comparison operator
		/*
		Compares two mw5axControlDef objects
			\return true it the compared objects are equal member by member,
					false otherwise
		*/
		const bool operator == (const mw5axControlDef& toCompare) const;
		//#############################################################################
		//! Gets Angle limit for rotary axis 0 
		/*!
			\returns angleLimit for rotary axis 0
		*/
		inline const angleLimit GetAngleLimitForFirstRotAxis() const
		{
			return m_controlDefData.find(0)->second.GetRotAxOutFormatType();
		}
		//#############################################################################
		//! Sets Angle limit for rotary axis 0 
		/*! 			
			\param newValue the new  angleLimit for rotary axis 0 
		*/
		inline void SetAngleLimitForFirstRotAxis(const mw5axControlDef::angleLimit& newValue ) 
		{ 
			m_controlDefData.find(0)->second.SetRotAxOutFormatType(newValue);
		}
		//#############################################################################
		//! Gets Angle limit for rotary axis 1 
		/*! 			
			\returns angleLimit for rotary axis 1
		*/
		inline const angleLimit GetAngleLimitForSecondRotAxis() const
		{ 
			return m_controlDefData.find(1)->second.GetRotAxOutFormatType();
		}
		//#############################################################################
		//! Sets Angle limit for rotary axis 1 
		/*! 			
			\param newValue the new  angleLimit for rotary axis 1
		*/
		inline void SetAngleLimitForSecondRotAxis(const mw5axControlDef::angleLimit& newValue ) 
		{ 
			m_controlDefData.find(1)->second.SetRotAxOutFormatType(newValue);
		}
		//#############################################################################
		//! Gets Angle limit for rotary axis 2
		/*!
			\returns angleLimit for rotary axis 2
		*/
		inline const angleLimit GetAngleLimitForThirdRotAxis() const
		{
			return m_controlDefData.find(2)->second.GetRotAxOutFormatType();
		}
		//#############################################################################
		//! Sets Angle limit for rotary axis 2 
		/*!
		\param newValue the new  angleLimit for rotary axis 2
		*/
		inline void SetAngleLimitForThirdRotAxis(const mw5axControlDef::angleLimit& newValue)
		{
			m_controlDefData.find(2)->second.SetRotAxOutFormatType(newValue);
		}
		//#############################################################################
	
		const RotAxisOutFormatSettings& GetRotAxisOutFormatSettings(const short& axisIndex) const;
	
		RotAxisOutFormatSettings& GetRotAxisOutFormatSettings(const short& axisIndex);

		const ControlDefData& GetControlDefData() const;

		void SetControlDefData(const ControlDefData& value);

		void SetDefaultSettings(short axIndex);

		void ValidateRotAxOutFormat() const;

private:
#pragma warning(push)
#pragma warning(disable:4251)
		ControlDefData m_controlDefData;
#pragma warning(pop)
		//#############################################################################
	};
	//#############################################################################
};
//#############################################################################
#endif	//	MW_MW5AXCONTROLDEF_HPP_
