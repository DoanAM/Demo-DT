// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMATERIAL_HPP_
#define MW_MWMATERIAL_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwColor.hpp"
#include "mwTexture.hpp"
//#############################################################################
namespace misc
{
	class mwException;
};

namespace mmedia
{

//#############################################################################
	//! implements material properties for a surface
	/*! The class members determine how light reflects off an object to create colour:
			a.	The 'Ambient Intensity' field specifies how much ambient light from light 
				sources this surface shall reflect. Ambient light is omnidirectional
				and depends only on the number of light sources, not their positions 
				with respect to the surface. Ambient colour is calculated as 
				'Ambient Intensity' × 'Diffuse Color'. 
			b.	The 'Diffuse Color' field reflects all light sources depending on the angle 
				of the surface with respect to the light source. The more directly the surface 
				faces the light, the more diffuse light reflects. 
			c.	The 'Emissive Color' field models _T("glowing") objects. This can be useful for displaying 
				pre-lit models (where the light energy of the room is computed explicitly), 
				or for displaying scientific data. 
			d.	The 'Specular Color' and shininess fields determine the specular highlights 
				(e.g., the shiny spots on an apple). When the angle from the light to the surface
				is close to the angle from the surface to the viewer, the 'Specular Color' 
				is added to the diffuse and ambient colour calculations. Lower shininess 
				values produce soft glows, while higher values result in sharper, smaller highlights. 
			e.	The 'Transparency' field specifies how _T("clear") an object is, with 1.0 being 
				completely transparent, and 0.0 completely opaque. 
	*/
class MW_5AXUTIL_API mwMaterial
{
public:
	//! Constructor
	/*! This constructor init the members as follows:
			AmbientIntensity  0.2         
			DiffuseColor      0.8 0.8 0.8 
			EmissiveColor     0 0 0       
			Shininess         0.2         
			SpecularColor     0 0 0       
			Transparency      0    
			TwoSidedLighting  enabled
	*/
	mwMaterial();
//#############################################################################
	//! Constructor
	/*! This constructor allow you to init all the class members
			\param vfAmbientIntensity - the Ambient Intensity (it must be between 0.0 and 0.1)
			\param rDiffuseColor - a ref to a Diffuse Color
			\param rEmissiveColor - a ref to an Emissive Color
			\param vfShininess -  the Shininess (it must be between 0.0 and 0.1)
			\param rSpecularColor - a ref to an Specular Color
			\param fTransparency - the Transparency (it must be between 0.0 and 0.1)
			\param fReflectivity - the Reflectivity ( it must be between 0.0 and 0.1 )
			\param reflectivityBitmapFileName - the file name of the reflectivity bitmap texture, defaults to ""
			\throws mwException - if the passed values are not in the range 0.0 to 1.0
	*/
	mwMaterial( const float vfAmbientIntensity,
					const misc::mwColor& rDiffuseColor,
					const misc::mwColor& rEmissiveColor,
					const float vfShininess,
					const misc::mwColor& rSpecularColor,
					const float fTransparency,
					const float fReflectivity,
					const misc::mwFileName& reflectivityBitmapFileName = misc::mwFileName(_T(""))
				);
//#############################################################################
	//! gets AmbientIntensity
	/*! 			
		\returns the AmbientIntensity (a value between 0.0 and 1.0)
	*/
	inline const float GetAmbientIntensity() const
	{
		return m_fAmbientIntensity.GetValue();
	};

//#############################################################################
	//! sets AmbientIntensity
	/*! 			
		\param vfAmbientIntensity new AmbientIntensity (it must be betwenn 0.0 and 1.0)
		\throws mwException - if the passed value is not in the range 0.0 to 1.0
	*/
	void SetAmbientIntensity( const float vfAmbientIntensity)
		;
//#############################################################################
	//! gets DiffuseColor
	/*! 			
		\returns the DiffuseColor
	*/
	inline const misc::mwColor& GetDiffuseColor() const
		{ return m_DiffuseColor;};
//#############################################################################
	//! sets DiffuseColor
	/*! 			
		\param rDiffuseColor new DiffuseColor
	*/
	void SetDiffuseColor( const misc::mwColor &rDiffuseColor);
//#############################################################################
	//! gets EmissiveColor
	/*! 			
		\returns the EmissiveColor
	*/
	inline const misc::mwColor& GetEmissiveColor() const
		{ return m_EmissiveColor;};
//#############################################################################
	//! sets EmissiveColor
	/*! 			
		\param rEmissiveColor the new EmissiveColor
	*/
	void SetEmissiveColor( const misc::mwColor& rEmissiveColor );
//#############################################################################
	//! gets Shininess
	/*! 			
		\returns the Shininess (a value between 0.0 and 1.0)
	*/
	inline const float GetShininess() const
	{ 
		return m_fShininess.GetValue();
	};

//#############################################################################
	//! sets Shininess
	/*! 			
		\param vfShininess the new Shininess (it must be betwenn 0.0 and 1.0)
		\throws mwException - if the passed value is not in the range 0.0 to 1.0
	*/
	void SetShininess( const float vfShininess )
		;
//#############################################################################
	//! gets SpecularColor
	/*! 			
		\returns the SpecularColor
	*/
	inline const misc::mwColor& GetSpecularColor() const
		{ return m_SpecularColor;};
//#############################################################################
	//! sets SpecularColor
	/*! 			
		\param rSpecularColor the new SpecularColor
	*/
	void SetSpecularColor(const misc::mwColor& rSpecularColor);
//#############################################################################
	//! gets Transparency
	/*! 			
		\returns the Transparency  (a value betwenn 0.0 and 1.0)
	*/
	inline const float GetTransparency() const
	{
		return m_fTransparency.GetValue();
	};

//#############################################################################
	//! sets Transparency
	/*! 			
		\param vfTransparency the new Transparency  (it must be betwenn 0.0 and 1.0)
		\throws mwException - if the passed value is not in the range 0.0 to 1.0
	*/
	void SetTransparency( const float vfTransparency)
		;

	//#############################################################################
	//! gets Reflectivity
	/*! 			
		\returns the Reflectivity  (a value between 0.0 ( no reflectivity ) and 1.0 ( chrome-like ) )
	*/
	inline const float GetReflectivity() const
	{
		return m_reflectivityTexture.GetIntensity();
	};

	//#############################################################################
	//! sets Reflectivity
	/*! 			
		\param vfReflectivity the new Reflectivity  (it must be between 0.0 and 1.0)
		\throws mwException - if the passed value is not in the range 0.0 to 1.0
	*/
	void SetReflectivity( const float vfReflectivity )
		;

	//#############################################################################
	//! gets reflectivity bitmap file name
	/*! 			
		\returns the file name for the reflectivity texture
	*/
	inline const misc::mwFileName& GetReflectivityBitmapFileName() const
	{
		return m_reflectivityTexture.GetBitmapFileName();
	};

	//#############################################################################
	//! sets reflectivity bitmap file name
	/*! 			
		\param toSet the new reflectivity texture file name 
	*/
	void SetReflectivityBitmapFileName( const misc::mwFileName& toSet );

	//#############################################################################
	//! gets diffuse texture
	/*! 			
		\returns the diffuse texture
	*/
    const mwTexture& GetDiffuseTexture() const;
	
	//#############################################################################
	//! sets reflectivity bitmap file name
	/*! 			
		\param toSet the new reflectivity texture file name 
	*/
	void SetDiffuseTextureFileName( const misc::mwFileName& toSet );

    //#############################################################################
	//! gets reflectivity texture
	/*! 			
		\returns the reflectivity texture
	*/
    const mwTexture& GetReflectivityTexture() const;

	//#############################################################################
	//! gets diffuse texture
	/*! 			
		\returns the diffuse texture
	*/
    mwTexture& GetDiffuseTextureRef();

    //#############################################################################
	//! gets reflectivity texture
	/*! 			
		\returns the reflectivity texture
	*/
    mwTexture& GetReflectivityTextureRef();

    //#############################################################################
	//! gets two sided lighting flag state
	/*! 			
		\returns true if two sided lighting is enabled
	*/
	const bool IsTwoSidedLightingEnabled() const;

	//! sets two sided lighting flag state
	/*! 			
		\param toSet the new state
	*/
	void SetTwoSidedLightingEnabled(const bool toSet);
	
    //#############################################################################
	//! is equal operator
	/*! 
		\param tc with which to compare
		\return  true if they are equal
	*/
	inline const bool operator==( const mwMaterial &tc ) const
	{
		return	(mathdef::is_eq( m_fAmbientIntensity.GetValue(), tc.m_fAmbientIntensity.GetValue() ) ) &&
				(m_DiffuseColor == tc.m_DiffuseColor) &&
				(m_EmissiveColor == tc.m_EmissiveColor) &&
				(mathdef::is_eq( m_fShininess.GetValue(), tc.m_fShininess.GetValue() ) ) &&
				(m_SpecularColor == tc.m_SpecularColor) &&
				(mathdef::is_eq( m_fTransparency.GetValue(), tc.m_fTransparency.GetValue() ) ) &&
				(m_diffuseTexture == tc.m_diffuseTexture) &&
                (m_reflectivityTexture == tc.m_reflectivityTexture) &&
				(m_twoSidedLightingEnabled == tc.m_twoSidedLightingEnabled);
	}

//#######################################################################

	//! is different operator
	/*! 
		\param tc with which to compare
		\return false if they are not equal
	*/
	inline const bool operator!=( const mwMaterial &tc ) const
	{
		return !((*this) == tc);
	};

//#######################################################################

private:

	typedef	misc::mwClampedValue<float>			flValue;

#pragma warning(push)
#pragma warning(disable:4251)
	//! ambient intensity
	flValue m_fAmbientIntensity;
	//! diffuse color
	misc::mwColor m_DiffuseColor;
	//! emissive color
	misc::mwColor m_EmissiveColor;
	//! shininess
	flValue m_fShininess;
	//! specular color
	misc::mwColor m_SpecularColor;
	//! transparency
	flValue m_fTransparency;
#pragma warning(pop)
    //! diffuse texture
    mwTexture m_diffuseTexture;
    //! reflectivity texture
    mwTexture m_reflectivityTexture;
	//! two sided lighting flag
	bool m_twoSidedLightingEnabled;
};

///! compare two materials
/*! 
	\param first left hand
	\param second right hand
	\return  if first is lower then second
*/


inline const bool operator < (  const mwMaterial &first, const mwMaterial &second )
{
	return first.GetDiffuseColor() < second.GetDiffuseColor();
};

};
#endif	//	MW_MWMATERIAL_HPP_
