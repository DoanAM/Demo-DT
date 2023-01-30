// (C) 2007-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWGLTEXT_HPP_
#define MW_MWGLTEXT_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mwDeprecated.hpp>
#include <mwTPoint2d.hpp>
#include <mwTPoint3d.hpp>
#include <string>

namespace VerifierUtil
{
/// configure font
struct MW_VERIFIER_API mwFontOptions
{
	/// default constructor, font size 12 pt
	mwFontOptions() : m_size(12), m_weight(100) {}

	void SetName(const misc::mwstring& name = "") { m_name = name; }
	const misc::mwstring& GetName() const { return m_name; }

	/// set size of font in point
	void SetFontSize(int size) { m_size = size; }
	/// get size of font in point
	int GetFontSize() const { return m_size; }

	void SetFontWeight(int weight) { m_weight = weight; }
	int GetFontWeight() const { return m_weight; }

private:
	misc::mwstring m_name;
	int m_size;
	int m_weight;
};

/// metrics of font, used to e.g. scale text boxes
struct MW_VERIFIER_API mwFontMetrics
{
	/// default constructor, all metrics 0
	mwFontMetrics() : m_avgCharWidth(0), m_charHeight(0), m_descent(0) {}

	/// set average width of characters
	void SetAverageCharWidth(int width) { m_avgCharWidth = width; }
	/// get average width of characters
	int GetAverageCharWidth() const { return m_avgCharWidth; }

	/// set height of characters (pixels above and below the base line).
	void SetCharHeight(int height) { m_charHeight = height; }
	/// get height of characters (pixels above and below the base line).
	int GetCharHeight() const { return m_charHeight; }

	/// set descent of characters (pixels below the base line)
	void SetDescent(int descent) { m_descent = descent; }
	/// get descent of characters (pixels below the base line)
	int GetDescent() const { return m_descent; }

private:
	int m_avgCharWidth;
	int m_charHeight;
	int m_descent;
};

class mwGLResourceManager;
class mwGLText_Impl;

/// Renders a string using OpenGL
class MW_VERIFIER_API mwGLText
{
public:
	typedef ::cadcam::mwTPoint2d<float> float2d;
	typedef ::cadcam::mwTPoint3d<float> float3d;

	/// Construct a mwGLText instance
	///
	/// mwGLText can be used to render a string on screen, using OpenGL. The OpenGL resources
	/// necessary for this are created statically, on first use. They are shared between mwGLText
	/// instances for performance reasons, and they are kept alive even if no mwGLText instance
	/// exists anymore. If you want to free the OpenGL resources created by this class you can call
	/// the ReleaseStaticOpenGLResources() function.
	mwGLText(const mwFontOptions& fontOptions = mwFontOptions());

	MW_DEPRECATED(
		"Please switch to the non-deprecated constructor. mwGLResourceManager is not part of the "
		"API.")
	mwGLText(mwGLResourceManager* pGLResourceManager);

	MW_DEPRECATED(
		"Please switch to the non-deprecated constructor. mwGLResourceManager is not part of the "
		"API.")
	mwGLText(mwGLResourceManager* pGLResourceManager, const mwFontOptions& fontOptions);

	~mwGLText();

	/// Prints a text in 3d
	/* Prints a text the active ogl context using 3d coordinates
	 * @parameter position Position of the test in 3d scene coordinates
	 * @parameter color RGB Color of the text
	 * @parameter alpha Alpha value of the text when blending is enabled
	 * @parameter text The text to be printed to th actual OGL context
	 */
	void Print(float3d position, float3d color, float alpha, const misc::mwstring& text);

	/// Prints a text in 2d
	/* Prints a text the active ogl context using 2d coordinates
	 * @parameter position Position of the test in 2d windows coordinates
	 * @parameter color RGB Color of the text
	 * @parameter alpha Alpha value of the text when blending is enabled
	 * @parameter text The text to be printed to th actual OGL context
	 */
	void Print(float2d position, float3d color, float alpha, const misc::mwstring& text);

	cadcam::mw2diBoundingBox ComputeTextBox(const misc::mwstring& text) const;

	/// gets metrics of currently used font or default metrics if font could not be loaded
	mwFontMetrics GetFontMetrics() const;

	/// gets currently used font options
	mwFontOptions GetFontOptions() const;
	/// set font options
	void SetFontOptions(const mwFontOptions& options);

	/// Deletes all static OpenGL resources allocated by this class
	static void ReleaseStaticOpenGLResources();

private:
	mwGLText_Impl* m_pImpl;
};
};  // namespace VerifierUtil
#endif  //	MW_MWGLTEXT_HPP_
