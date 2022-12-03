// (C) 2012-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWOPENGLBACKGROUNDIMAGE_HPP_
#define MW_MWOPENGLBACKGROUNDIMAGE_HPP_
#include <mwString.hpp>
#include <mw2dBoundingBox.hpp>
#include "mwScreenPosition.hpp"
#include "mwColor.hpp"
#include "mwColorGradient.hpp"

#if defined (_WIN32)
#include <windows.h>
#elif (defined(__linux__) || defined(__APPLE__)) 
	typedef void *HINSTANCE;
#endif

namespace Gdiplus
{
	class Bitmap;
}

namespace mmedia
{
	class mwOpenGLInteractiveArena;

	class mwOpenGLBackgroundImage
	{
	public:
		enum bgType
		{
			BG_SOLID, 
			BG_GRADIENT, 
			BG_IMAGE
		};

		mwOpenGLBackgroundImage( mwOpenGLInteractiveArena &scene );
		~mwOpenGLBackgroundImage();
		
		const bgType &GetBackgroundType() const;
		void SetBackgroundType( const bgType typeToApply );
		
		void SetBackgroundImageFile( const misc::mwstring &fileName );
		const misc::mwstring& GetBackgroundImageFile() const;

		void SetBackgroundImagePosition( const mwScreenPosition::position &bgImagePosition );
		const mwScreenPosition::position &GetBackgroundImagePosition() const;
		
		void SetBrandingImageResource( HINSTANCE inst, unsigned int ID );
		void SetBrandingImagePosition( const mwScreenPosition::position &bgImagePosition );
		const mwScreenPosition::position &GetBrandingImagePosition() const;
		
		void SetBackgroundColor( const misc::mwColor &bgColor );
		const misc::mwColor &GetBackgroundColor() const;

		void SetBackgroundColorGradient( const mwColorGradient &bgGradient );
		const mwColorGradient &GetBackgroundColorGradient( ) const;
		
		void SetBrandingEnabled( const bool enable );
		const bool IsBrandingEnabled() const;

		void Render();

		void DeleteGLResourses();

	protected:
	private:
		// avoid warning c4512
		mwOpenGLBackgroundImage& operator=(const mwOpenGLBackgroundImage&);

		void SetBrandingImageFile( const misc::mwstring &fileName );
		typedef	cadcam::mw2dBoundingBox<int>	quadArea;

		typedef unsigned GLuint;

		bgType							m_backGroundType;
		mwScreenPosition::position		m_backgroundImagePosition;
		mwScreenPosition::position		m_brandingImagePosition;
		mwOpenGLInteractiveArena		&m_scene;
		GLuint							m_backGroundGradientGLList;
		GLuint							m_backGroundImageGLList;
		GLuint							m_backGroundBrandingGLList;
		GLuint							m_backgroundTextureID;
		GLuint							m_brandingTextureID;
		int								m_backgroundImageWidth;
		int								m_backgroundImageHeight;
		int								m_brandingImageWidth;
		int								m_brandingImageHeight;
		const int						m_zDepth;
		int								m_renderedHeight;
		int								m_renderedWidth;
		misc::mwColor							m_backgroundColor;
		mwColorGradient					m_backgroundColorGradient;
		std::vector<quadArea>			m_texQuads;
		bool							m_brandingEnabled;
		misc::mwstring					m_backgroundImageFile;

		void InitGLList( GLuint &glList );
		void InitGLTexture( GLuint &glTexture );
		void ResetGLList( GLuint &listID );
		void ResetGLTexture( GLuint &textureID );
		void UploadBitmapDataToTexture( Gdiplus::Bitmap &bmp, GLuint &glTexture );
		bool IsInitialized( GLuint glItem );
		void GenerateQuads( const mwScreenPosition::position &position, int imageWidth, int imageHeight );

};
}
#endif	//	MW_MWOPENGLBACKGROUNDIMAGE_HPP_
