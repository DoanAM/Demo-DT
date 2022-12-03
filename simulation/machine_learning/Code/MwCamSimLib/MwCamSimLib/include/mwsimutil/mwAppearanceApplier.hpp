// (C) 2016-2018 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWAPPEARANCEAPPLIER_HPP_
#define MW_MWAPPEARANCEAPPLIER_HPP_
#include <map>
#include "mwAutoPointer.hpp"
#include "mwGLReflectionTexture.hpp"
#include "mwMaterial.hpp"

#if defined(_WIN32) && !defined(NO_GL)
typedef unsigned int GLenum;
typedef void(__stdcall* PFNGLACTIVETEXTUREPROC) (GLenum texture);
#endif

namespace mmedia
{
	class mwAppearance;

	class mwAppearanceApplierIntf
	{
	public:
		typedef misc::mwAutoPointer< mwAppearanceApplierIntf >		Ptr;
		virtual void Compile( const mwAppearance& appearance ) = 0;
		virtual void Enable( const mwAppearance& appearance ) = 0;
		virtual void Disable( const mwAppearance& appearance ) = 0;

		virtual int GetDiffuseTextureUnit() = 0;
		virtual int GetReflectionTextureUnit() = 0;

		virtual bool ShouldUseDiffuseTexture( const mwAppearance& appearance ) = 0;
		virtual bool ShouldUseReflectionTexture( const mwAppearance& appearance ) = 0;

		virtual ~mwAppearanceApplierIntf() {}
	};


#if defined(_WIN32) && !defined(NO_GL)
	class mwAppearanceDefaultApplier : public mwAppearanceApplierIntf
	{
	public:
		typedef misc::mwAutoPointer< mwGLReflectionTexture >		ReflectionTexturePtr;
		typedef misc::mwstring										TextureMapKey;
		typedef ReflectionTexturePtr								TextureMapValue;
		typedef std::map< TextureMapKey, TextureMapValue >			TextureMap;

		mwAppearanceDefaultApplier();

		static void ClearTextureMap();

		virtual void Compile( const mwAppearance& appearance ); 
		virtual void Enable( const mwAppearance& appearance );
		virtual void Disable( const mwAppearance& appearance );

		virtual int GetDiffuseTextureUnit();
		virtual int GetReflectionTextureUnit();

		virtual bool ShouldUseDiffuseTexture( const mwAppearance& appearance );
		virtual bool ShouldUseReflectionTexture( const mwAppearance& appearance );

	private:
		void CompileMaterial( const mwMaterial &tc );
		void CompileTexture( const mwTexture& texture );
		void EnableTexture( int textureUnit, const mwTexture& texture, bool reflection );
		void DisableTexture( int textureUnit, const mwTexture& texture);

		void ActivateTextureUnit( int textureUnit );

		static void InitializeOpenGL13();

		bool glBlendColor(float red, float green, float blue, float alpha) const;

	private:
		
		struct TextureMapStaticData
		{
			TextureMap m_textureMap;
		};

		static PFNGLACTIVETEXTUREPROC glActiveTexture;
		static bool m_openGL13Supported;
		static bool m_openGL13Initialized;
		static bool m_glBlendColorSupported;
	};
#endif

}; // namespace
#endif	//	MW_MWAPPEARANCEAPPLIER_HPP_
