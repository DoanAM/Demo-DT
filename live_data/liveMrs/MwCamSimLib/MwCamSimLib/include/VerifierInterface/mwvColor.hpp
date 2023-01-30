// (C) 2007-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVCOLOR_HPP_
#define MW_MWVCOLOR_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvUtilDefines.hpp"

#include <mwMiscFwdDecl.hpp>

namespace VerifierUtil
{
/// Structure for holding an RGBA color value. Each channel is represented by a `float` between
/// `0.0f` and `1.0f` and internally stored using an 8-bit (unsigned) integer for each channel.
///
/// If it is preferred to store each channel as an actual `float`, see VerifierUtil::Color.
class MW_VERIFIER_API mwvColor
{
public:
	/// Sets the color to opaque black, i.e., the RGBA value `(0.0f, 0.0f, 0.0f, 1.0f)`.
	mwvColor();

	/// Sets color with default alpha channel of `1.0f`.
	mwvColor(const float& r, const float& g, const float& b);

	mwvColor(const float& r, const float& g, const float& b, const float& a);

	/// Sets color with default alpha channel of `1.0f`.
	mwvColor(const unsigned char r, const unsigned char g, const unsigned char b);

	mwvColor(
		const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);

	mwvColor(const mwvColor& c);

	mwvColor& operator=(const mwvColor& c);

	bool operator==(const mwvColor& a) const;

	bool operator!=(const mwvColor& a) const;


	float r() const;

	float g() const;

	float b() const;

	float a() const;


	unsigned char r8() const;

	unsigned char g8() const;

	unsigned char b8() const;

	unsigned char a8() const;


	void r(float r);

	void g(float g);

	void b(float b);

	void a(float a);


	void r8(char r);

	void g8(char g);

	void b8(char b);

	void a8(char a);


	float3d ToFloat3d() const;
	/*!	*/
	misc::mwColor ToMisc() const;

private:
	unsigned char m_R;
	unsigned char m_G;
	unsigned char m_B;
	unsigned char m_A;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVCOLOR_HPP_
