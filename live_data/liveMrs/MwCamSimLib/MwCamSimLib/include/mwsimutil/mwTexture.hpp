// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTEXTURE_HPP_
#define MW_MWTEXTURE_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwFileName.hpp"
#include "mwClampedValue.hpp"

namespace mmedia
{

class MW_5AXUTIL_API mwTexture
{
public:
	mwTexture();

    //! Constructor
    /*! This constructor allow you to init all the class members
            \param scaleX - X scaling factor
            \param scaleY - Y scaling factor
            \param offsetX - X offset
            \param offsetY - Y offset
            \param rotation - rotation angle (degrees)
            \param intensity - texture intensity (it must be between 0.0 and 1.0)
            \param bitmapFileName - the file name of the bitmap texture
    */
    mwTexture(float scaleX,
		float scaleY,
		float offsetX,
		float offsetY,
		float rotation,
		float intensity,
		const misc::mwFileName& bitmapFileName,
		const misc::mwstring& resourceName = _T(""));

    float GetScaleX() const;

    void SetScaleX(float scaleX);

    float GetScaleY() const;

    void SetScaleY(float scaleY);

    float GetOffsetX() const;

    void SetOffsetX(float offsetX);

    float GetOffsetY() const;

    void SetOffsetY(float offsetY);

    float GetRotation() const;

    void SetRotation(float rotation);

    float GetIntensity() const;

    void SetIntensity(float intensity);

    const misc::mwFileName& GetBitmapFileName() const;

    void SetBitmapFileName(const misc::mwFileName& fileName);

	const misc::mwstring& GetResourceFileName() const;

	void SetResourceFileName(const misc::mwstring& resourceName);

    bool operator==(const mwTexture& tc) const;

    bool operator!=(const mwTexture& tc) const;

private:
    typedef misc::mwClampedValue<float> flValue;

    //! X scaling factor
    float m_ScaleX;
    //! Y scaling factor
    float m_ScaleY;
    //! X offset
    float m_OffsetX;
    //! Y offset
    float m_OffsetY;
    //! rotation angle (degrees)
    float m_Rotation;

#pragma warning(push)
#pragma warning(disable:4251)
	//! texture intensity
	flValue m_Intensity;
#pragma warning(pop)

    //! texture bitmap file name
    misc::mwFileName m_BitmapFileName;
	//! resource name
	misc::mwstring m_resourceName;
};

}
#endif	//	MW_MWTEXTURE_HPP_
