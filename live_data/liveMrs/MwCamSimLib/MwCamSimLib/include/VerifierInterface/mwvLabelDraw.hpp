// (C) 2020-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVLABELDRAW_HPP_
#define MW_MWVLABELDRAW_HPP_

#if !defined(NO_GL) && !defined(MW_IGNORE_GL) && !defined(MW_NO_GL)

#include "mwVerifierDllDefinition.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mwColor.hpp>

namespace VerifierUtil
{
class mwGLText;

class MW_VERIFIER_API LabelDraw
{
public:
	LabelDraw();

	~LabelDraw();


	/// Have to be called explicitly from application after the rendering device has been
	/// initialized.
	void InitializeDeviceResources();

	/// Have to be called explicitly from application bevore the rendering device will be released.
	void ReleaseDeviceResources();


	struct Style
	{
		float scale;
		misc::mwstring font;
		int fontSize;
		int fontWeight;
		float fontLineSpacing;
		float borderThickness;
		float borderRadius;
		float padding;
		float shadowOffset;
		misc::mwColor backgroundColor;
		misc::mwColor borderColor;
		misc::mwColor textColor;
		float backgroundAlpha;
		float shadowAlpha;

		Style();
	};

	void SetStyle(const Style& style);

	inline const Style& GetStyle() const { return m_style; }


	cadcam::mwPoint2di ComputeSize(const misc::mwstring& text);

	/// @param box In GL viewport coorinates.
	void Draw(const cadcam::mw2dfBoundingBox& box, const misc::mwstring& text);

protected:
	void CreateGLtext();


	void DrawBackground(const cadcam::mw2dfBoundingBox& box);

	void DrawRoundedBox(const cadcam::mw2dfBoundingBox& box, float radius);

	void DrawText(const cadcam::mw2dfBoundingBox& box, const misc::mwstring& text);


	float GetScaled(float value) const;

private:
	Style m_style;
	misc::mwAutoPointer<VerifierUtil::mwGLText> m_glText;

private:
	LabelDraw(const LabelDraw&);
	void operator=(const LabelDraw&);
};

}  // namespace VerifierUtil

#endif  // !defined(NO_GL) && !defined(MW_IGNORE_GL) && !defined(MW_NO_GL)
#endif  // MW_MWVLABELDRAW_HPP_
