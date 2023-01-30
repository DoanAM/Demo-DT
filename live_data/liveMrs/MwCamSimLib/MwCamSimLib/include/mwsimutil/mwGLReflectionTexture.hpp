// (C) 2006-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWGLREFLECTIONTEXTURE_HPP_
#define MW_MWGLREFLECTIONTEXTURE_HPP_

#include "mwString.hpp"
#include <vector>
#include <cstdint>

namespace mmedia
{
/** Texture Class
* Small class for holding a OGL reflection texture.
* If the image is rectangular will be cropped to square
* Originated from NEHE tut no. 23
*/
class mwGLReflectionTexture
{
public:
	//! Provides two different modes how the texture get filtered
	enum Filter_Mode {TFM_NEAREST,TFM_LINEAR};

	/** The constructor
	* @param BmpFileName Name of the *bmp file to load
	*/
	mwGLReflectionTexture(const misc::mwstring& bmpFileName, const Filter_Mode filterMode);

	/// Initializes a new mwGLReflectionTexture using in-memory texture bitmaps.
	/// All bitmaps must be in one of the image formats supported by SOIL (including file headers).
	/// If @c cubeMapTextures is an empty vector, @c texture is used for all 6 cube faces.
	/// Otherwise, @c cubeMapTextures must contain six bitmaps for the cube faces in the order
	/// xPos, xNeg, yPos, yNeg, zPos, zNeg.
	mwGLReflectionTexture(
		const std::vector<uint8_t>& texture,
		const std::vector<std::vector<uint8_t>>& cubeMapTextures,
		Filter_Mode filterMode);

	//! The destructor
	virtual ~mwGLReflectionTexture(void);

	/** Enable texture
	* Enables the texture for the actual OpenGL commands
	* @param intensity Intensity controls how much the ref texture get blended over the original color
    * @param reflectionMode Use reflection mode settings
	*/
	void Enable(const float intensity, const bool reflectionMode = true);

	/** Disable texture
	*   Disables the texture for the actual OpenGL commands
	*/
	void Disable() const;

private:
	struct mwReflectionTextureData
	{
		mwReflectionTextureData();
		~mwReflectionTextureData();

		int m_width;
		int m_height;
		int m_channels;
		// Byte array containing the texture data
		unsigned char* m_data;
	};

	/** Load texture
	*   Loads a texture in a *.bmp to an OGL Texture
	* @param bmpFileName Name of the *bmp file to load
	*/
	void LoadGLTexture(const misc::mwstring& bmpFileName);
	
	/** Load texture
	*   Loads a texture from memory to an OGL Texture. See
	*   @ref mwGLReflectionTexture(const std::vector<uint8_t>&,const std::vector<std::vector<uint8_t>>&,Filter_Mode)
	*   for details.
	*/
	void LoadGLTexture(
		const std::vector<uint8_t>& texture,
		const std::vector<std::vector<uint8_t>>& cubeMapTextures);

	/** Loads A Bitmap Image
	 *  Loads a *.bmp file to the texture object
	 * @param Filename Name of the *bmp file to load
	 */
	void LoadBMP(const misc::mwstring& filename, mwReflectionTextureData& reflectionTextureData);
	/** Loads An existing Bitmap Image (no chekck is performed)
	*  Loads a *.bmp file to the texture object
	* @param Filename Name of the *bmp file to load
	*/
	void LoadExistingBMP(const misc::mwstring& fileNameString, mwReflectionTextureData& reflectionTextureData);

	/** Loads An existing Bitmap from memory (no check is performed)
	*/
	void LoadBMP(const std::vector<uint8_t>& image, mwReflectionTextureData& reflectionTextureData);

	/** Initializes the GL texture
	*/
	void InitializeTexture();
	
	void ResizeTexturesToSquare();
	void ResizeTextureToSquare(mwReflectionTextureData& reflectionTextureData);

	mwReflectionTextureData		m_reflectionTextureDataPosX;
	mwReflectionTextureData		m_reflectionTextureDataNegX;
	mwReflectionTextureData		m_reflectionTextureDataPosY;
	mwReflectionTextureData		m_reflectionTextureDataNegY;
	mwReflectionTextureData		m_reflectionTextureDataPosZ;
	mwReflectionTextureData		m_reflectionTextureDataNegZ;

	/// Filter mode of the texture linear or nearest
	Filter_Mode					m_filterMode;
	/// GL texture name
	unsigned int				m_textureID;

};
}//namespace mmedia
#endif	//	MW_MWGLREFLECTIONTEXTURE_HPP_
