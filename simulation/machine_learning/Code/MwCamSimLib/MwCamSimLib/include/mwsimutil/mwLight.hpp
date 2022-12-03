// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWLIGHT_HPP_
#define MW_MWLIGHT_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwClampedValue.hpp>
#include "mwColor.hpp"
#include <mwTPoint3d.hpp>

//#############################################################################
namespace misc
{
	class mwException;
};

namespace mmedia
{
//#############################################################################
	//! implements a light
	/*! The class members determine the light properties:
			a.	Ambient color
			b.	Diffuse color
			c.	Specular color
			d.	Light position
			e.	Spot with direction, exponent and cut_off
			f.	Light attenuation factors
	*/
	class MW_5AXUTIL_API mwLight
	{
	public:
		//! Constructor
		/*! This constructor init the members as follows:
				Ambient			1.0	1.0	1.0
				Diffuse			0.0 0.0 0.0
				Specular		0.0 0.0 0.0
				Position		0.0 0.0 1.0
				PositionWeight	0.0
				Direction		0.0 0.0 -1.0
				Exponent		0.0
				SpotOn			false
				Cutoff			90.0
				attConstant		1.0
				attLinear		0.0
				attQuadratic	0.0
		*/
		mwLight();
		//! Constructor
		/*! This constructor allows you to init color members
				\param AmbientColor - the Ambient Color
				\param DiffuseColor - the Diffuse Color
				\param SpecularColor - the Specular Color
		*/
		mwLight(	const misc::mwColor& AmbientColor,
					const misc::mwColor& DiffuseColor,
					const misc::mwColor& SpecularColor					
				);
		//! Constructor
		/*! This constructor allows you to init all class members
				\param AmbientColor - the Ambient Color
				\param DiffuseColor - the Diffuse Color
				\param SpecularColor - the Specular Color
				\param Position - the Light Source position
				\param PositionWeight - if 0.0 then light is treated as a directional source
					- attenuation is disabled, and Diffuse and specular lighting
					calculations take the lights direction, but not its actual position,
					into account. Otherwise, diffuse and specular lighting calculations
					are based on the actual location of the light in eye coordinates, and
					attenuation is enabled.
				\param Direction - the Direction of light, when SpotOn is true
				\param Exponent - Only values in the range [0,128] are accepted. 
					Effective light intensity is attenuated by the cosine of the angle between
					the direction of the light and the direction from the light to the vertex
					being lighted, raised to the power of the spot exponent. Thus, higher spot
					exponents result in a more focused light source, regardless of the spot cutoff
					angle (see the following paragraph). The default spot exponent is 0,
					resulting in uniform light distribution.
				\param SpotOn - Is light having a spot? false means uniform light distribution
				\param Cutoff - the Spot Cutoff, only valid from 0 to 90					
				\param attConstant - Constant Attenuation factor - default 1.0
				\param attLinear - Linear Attenuation factor - default 0.0
				\param attQuadratic - Quadratic Attenuation factor - default 0.0
					Only nonnegative values are accepted. If the light is positional, rather than
					directional, its intensity is attenuated by the reciprocal of the sum of: the
					constant factor, the linear factor multiplied by the distance between the light
					and the vertex being lighted, and the quadratic factor multiplied by the square
					of the same distance. The default attenuation factors are (1,0,0), resulting in
					no attenuation.
				\throws mwException - if the passed values are not in the valid range
		*/
		mwLight(	const misc::mwColor& AmbientColor,
					const misc::mwColor& DiffuseColor,
					const misc::mwColor& SpecularColor,
					const cadcam::mwTPoint3d<float> &Position,
					float PositionWeight,
					const cadcam::mwTPoint3d<float> &Direction,
					float Exponent,
					bool SpotOn,
					float Cutoff,
					float attConstant,
					float attLinear,
					float attQuadratic
				)
			;

//#############################################################################
		typedef misc::mwClampedValue< float >			lightAttribute;
	
//#############################################################################
		//! Equality operator
		const bool operator==( const mwLight &toCompare ) const;

//#############################################################################
		//! sets Ambient Color
		/*! 			
				\param AmbientColor - the new Ambient Color
		*/
		inline void SetAmbientColor( const misc::mwColor &AmbientColor )
		{
			m_AmbientColor = AmbientColor;
		};

//#############################################################################
		//! gets Ambient Color
		/*! 			
				\returns the ambient color
		*/
		inline const misc::mwColor& GetAmbientColor() const
		{
			return m_AmbientColor;
		};

//#############################################################################
		//! sets Diffuse Color
		/*! 			
				\param DiffuseColor - the new Diffuse Color
		*/
		inline void SetDiffuseColor( const misc::mwColor &DiffuseColor )
		{
			m_DiffuseColor = DiffuseColor;
		};

//#############################################################################
		//! gets Diffuse Color
		/*! 			
				\returns the diffuse color
		*/
		inline const misc::mwColor& GetDiffuseColor() const
		{
			return m_DiffuseColor;
		};

//#############################################################################
		//! sets Specular Color
		/*! 			
				\param SpecularColor - the new Specular Color
		*/
		inline void SetSpecularColor( const misc::mwColor &SpecularColor )
		{
			m_SpecularColor = SpecularColor;
		};

//#############################################################################
		//! gets Specular Color
		/*! 			
				\returns the specular color
		*/
		inline const misc::mwColor& GetSpecularColor() const
		{
			return m_SpecularColor;
		};

//#############################################################################
		//! sets Position
		/*! 			
				\param Position - the new Light source Position
		*/
		inline void SetPosition( const cadcam::mwTPoint3d<float> &Position )
		{
			m_Position = Position;
		};

//#############################################################################
		//! gets Position
		/*! 			
				\returns the Light source Position
		*/
		inline const cadcam::mwTPoint3d<float>& GetPosition() const
		{
			return m_Position;
		};

//#############################################################################
		//! sets Position Weight
		/*! 			
				\param PositionWeight - the new Light Position Weight
		*/
		inline void SetPositionWeight( float PositionWeight )
		{
			m_PositionWeight = PositionWeight;
		};

//#############################################################################
		//! gets Position Weight
		/*! 			
				\returns the Light Position Weight
		*/
		inline float GetPositionWeight() const
		{
			return m_PositionWeight;
		};

//#############################################################################
		//! sets Direction
		/*! 			
				\param Direction - the new Light Spot Direction
				\throws mwException is SpotOn is false
		*/
		void SetDirection( const cadcam::mwTPoint3d<float> &Direction )
			;

//#############################################################################
		//! gets Direction
		/*! 			
				\returns the Light Spot Direction
				\throws mwException is SpotOn is false
		*/
		const cadcam::mwTPoint3d<float>& GetDirection() const
			;

//#############################################################################
		//! sets SpotOn
		/*! 			
				\param SpotOn - true if Spot mode is turned on, false otherwise
		*/
		inline void SetSpotOn( bool SpotOn )
		{
			m_SpotOn = SpotOn;
		};

//#############################################################################
		//! gets SpotOn value
		/*! 			
				\returns true if Spot mode is turned on, false otherwise
		*/
		inline float GetSpotOn() const
		{
			return m_SpotOn;
		};

//#############################################################################
		//! sets Constant Attenuation Factor
		/*! 			
				\param factor attConstant - the new factor
		*/
		inline void SetConstantAttFactor( float factor )
		{
			m_attConstant = factor;
		};

//#############################################################################
		//! gets Constant Attenuation Factor
		/*! 			
				\returns the Constant Attenuation Factor
		*/
		inline float GetConstantAttFactor() const
		{
			return m_attConstant;
		};

//#############################################################################
		//! sets Linear Attenuation Factor
		/*! 			
				\param factor attLinear - the new factor
		*/
		inline void SetLinearAttFactor( float factor )
		{
			m_attLinear = factor;
		};

//#############################################################################
		//! gets Linear Attenuation Factor
		/*! 			
				\returns the Linear Attenuation Factor
		*/
		inline float GetLinearAttFactor() const
		{
			return m_attLinear;
		};

//#############################################################################
		//! sets Quadratic Attenuation Factor
		/*! 			
				\param factor attQuadratic - the new factor
		*/
		inline void SetQuadraticAttFactor( float factor )
		{
			m_attQuadratic = factor;
		};

//#############################################################################
		//! gets Quadratic Attenuation Factor
		/*! 			
				\returns the Quadratic Attenuation Factor
		*/
		inline float GetQuadraticAttFactor() const
		{
			return m_attQuadratic;
		};

//#############################################################################
		//! sets Exponent
		/*! 			
				\param Exponent - the new Light Spot Exponent
				\throws mwException if Exponent is not in valid range [0,128]
		*/
		inline void SetExponent( float Exponent )
			
		{
			m_Exponent = Exponent;
		}

//#############################################################################
		//! gets Exponent
		/*! 			
				\returns the Light Spot Exponent
		*/
		inline float GetExponent() const
		{
			return m_Exponent.GetValue();
		};

//#############################################################################
		//! sets Cutoff
		/*! 			
				\param Cutoff - the new Light Spot Cutoff (SpotOn must be true)
				\throws mwException if Cutoff is not in valid range [0,90]
		*/
		void SetCutoff( float Cutoff )
			;

//#############################################################################
		//! gets Cutoff
		/*! 			
				\returns the Light Spot Cutoff (SpotOn must be true)
				\throws mwException if SpotOn is false
		*/
		float GetCutoff() const
			;
	
//#############################################################################
		//! Set follow camera flag
		/*!
			\param follow true if you want the light to follow the camera,
			false otherwise.
			\remark setting more than one like to follow the camera doesn't 
			make much sense (normally)
		*/
		inline void SetFollowCamera( const bool follow = true )
		{
			mFollowCamera = follow;
		};

//#############################################################################
		//! Get follow camera flag
		/*!
			\returns true if the light is configured to follow the camera
		*/
		inline const bool GetFollowCamera() const
		{
			return mFollowCamera;
		};

		protected:

//#############################################################################
			void SetDefaults();

#pragma warning(push)
#pragma warning(disable:4251)
			misc::mwColor m_AmbientColor, m_DiffuseColor, m_SpecularColor;
			lightAttribute m_Exponent;
			lightAttribute m_Cutoff;
#pragma warning(pop)
			cadcam::mwTPoint3d<float> m_Position;
			float m_PositionWeight;
			cadcam::mwTPoint3d<float> m_Direction;
			bool m_SpotOn;
			float m_attConstant;
			float m_attLinear;
			float m_attQuadratic;
			bool mFollowCamera;
	};
};
#endif	//	MW_MWLIGHT_HPP_
