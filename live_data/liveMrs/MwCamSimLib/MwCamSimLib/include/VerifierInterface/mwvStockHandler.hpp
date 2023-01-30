// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVSTOCKHANDLER_HPP_
#define MW_MWVSTOCKHANDLER_HPP_

#include "mwMachSimVerifier.hpp"
#include "mwVerifierRendering.hpp"
#include "mwvSectionPlaneRenderer.hpp"
#include "mwvSimulation4d.hpp"
#include "mwvUtilDefines.hpp"

#ifndef NO_GL

namespace VerifierUtil
{
class mwGLResourceManager;
class mwOldGLListsRenderer;
class mwGLListsRenderer;
class mwOldGLBufferRenderer;
class mwGLBufferRenderer;
namespace mwShaderRenderer
{
class ObjectVerifier;
}

class MW_VERIFIER_API mwvStockHandler : public mwvSectionPlaneRenderer::Renderable
{
public:
	enum RendererMode
	{
		RENDERER_GL_BUFFERS1 = 0,
		RENDERER_GL_BUFFERS2 = 1,
		RENDERER_GL_LISTS1 = 2,
		RENDERER_GL_LISTS2 = 3,
		RENDERER_GL_SHADER = 4
	};

	mwvStockHandler(mwMachSimVerifier* const pVerifier, const BoundingBox3d& box);
	virtual ~mwvStockHandler();

	void Draw();
	void Reset();
	void ClearRenderers();
	cadcam::mw3dBoundingBox<float> GetViewportBoundingBox();
	MW_FORCEINLINE void SetShowWorkpiece(bool show);
	MW_FORCEINLINE bool GetShowWorkpiece();
	MW_FORCEINLINE void SetDrawVBOs(bool drawVBOs);
	MW_FORCEINLINE bool GetDrawVBOs() const;
	MW_FORCEINLINE void SetUploadVBOs(bool uploadVBOs);
	MW_FORCEINLINE bool GetUploadVBOs() const;
	MW_FORCEINLINE RendererMode GetRenderMode() const;
	MW_FORCEINLINE void SetRendererMode(RendererMode);  // TODO: this method should be removed
	MW_FORCEINLINE mwMachSimVerifier* GetVerifier();
	MW_FORCEINLINE void SetShaderRenderer(mwShaderRenderer::ObjectVerifier* renderer);

	/// This class encapsulates the interaction with the DynamicModelTracker
	class MW_VERIFIER_API Sim4dFacade
	{
	public:
		explicit Sim4dFacade(mwvStockHandler* stockHandler = MW_NULL);
		bool IsRecordingEnabled() const;
		void SetRecordingEnabled(bool state);

		bool IsPlaybackEnabled() const;
		void SetPlaybackEnabled(bool state);

		int GetPlaybackPosition() const;
		void SetPlaybackPosition(int idx);

		// this will either only record the input or mult it to the real renderer as well
		mwvIndexedAbstractRenderer& GetRecordingRenderer();
		void ResetSim4d();
		void FrameDone();

		void SetRealRenderer(mwvIndexedAbstractRenderer& renderer);
		void RenderPlayback();
		void RenderPlayback(mwvIndexedAbstractRenderer& renderer);

		void SetStockHandler(mwvStockHandler& sh);
		int GetMaxCapturedFrameIndex() const;

		void Save(const misc::mwstring& fileName) const;
		void Load(const misc::mwstring& fileName);

		void SetProgressHandler(mwIDisplayableProgressHandler* newHandler);
		void DeleteFramesAfter(size_t newCurrentCaptureFrameIndex);
		void ConsolidateAndClearFramesBefore(size_t frameIndex);

	private:
		bool stockHandlerIsInCompatibleMode() const;
		bool m_isRecordingEnabled;
		bool m_isPlaybackEnabled;
		int m_currentPlaybackPosition;

		mwvStockHandler* m_stockHandler;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
		misc::mwAutoPointer<mwvSimulation4d> m_sim4d;
		mwvIndexedAbstractRenderer* m_realRenderer;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
		misc::mwAutoPointer<mwvIndexedAbstractRenderer> m_multer;
	};
	MW_FORCEINLINE Sim4dFacade& GetSim4d();

private:
	mwGLResourceManager* m_glResourceManager;

	mwOldGLListsRenderer* const m_testRendererGLLists;
	mwGLListsRenderer* const m_testRendererGLLists2;
	mwOldGLBufferRenderer* const m_testRendererVBO;
	mwGLBufferRenderer* const m_testRendererVBO2;
	mwShaderRenderer::ObjectVerifier* m_testRendererShader;

	mwRendering::RenderGroupSorter* const m_renderGroupSorter;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<int> m_groupIds;

	Sim4dFacade m_sim4d;

	mwMachSimVerifier* const m_pVerifier;
	RendererMode m_rendererMode;

	bool m_showWorkpiece;
	bool m_showEdges;
	bool m_drawVBOs;
	bool m_switchVisibility;
	bool m_firstZoom;
	bool m_uploadVBOs;
	bool m_dmtRecord;
	bool m_dmtPlayback;
};

MW_FORCEINLINE void mwvStockHandler::SetUploadVBOs(bool uploadVBOs)
{
	m_uploadVBOs = uploadVBOs;
}

MW_FORCEINLINE bool mwvStockHandler::GetUploadVBOs() const
{
	return m_uploadVBOs;
}

MW_FORCEINLINE bool mwvStockHandler::GetShowWorkpiece()
{
	return m_showWorkpiece;
}

MW_FORCEINLINE void mwvStockHandler::SetShowWorkpiece(bool show)
{
	m_showWorkpiece = show;
}

MW_FORCEINLINE void mwvStockHandler::SetDrawVBOs(bool drawVBOs)
{
	m_drawVBOs = drawVBOs;
}

MW_FORCEINLINE bool mwvStockHandler::GetDrawVBOs() const
{
	return m_drawVBOs;
}

MW_FORCEINLINE mwvStockHandler::RendererMode mwvStockHandler::GetRenderMode() const
{
	return m_rendererMode;
}

MW_FORCEINLINE void mwvStockHandler::SetRendererMode(RendererMode mode)
{
	m_rendererMode = mode;
}

MW_FORCEINLINE mwMachSimVerifier* mwvStockHandler::GetVerifier()
{
	return m_pVerifier;
}

MW_FORCEINLINE void mwvStockHandler::SetShaderRenderer(mwShaderRenderer::ObjectVerifier* renderer)
{
	m_testRendererShader = renderer;
}

MW_FORCEINLINE mwvStockHandler::Sim4dFacade& mwvStockHandler::GetSim4d()
{
	return m_sim4d;
}
}  // namespace VerifierUtil
#endif  // NO_GL
#endif  //	MW_MWVSTOCKHANDLER_HPP_
