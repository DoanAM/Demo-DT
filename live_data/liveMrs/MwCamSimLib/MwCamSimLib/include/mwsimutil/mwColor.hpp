// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOLOR_HPP_
#define MW_MWCOLOR_HPP_
#include "mwRangeException.hpp"
#include "mwMathConstants.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
class mwColor4f; // forward declaration for conversion constructors
class mwColor4b; // forward declaration for conversion constructors

//! implements a color in the RGB colour triple format
/*! each component from the RGB triple is a float in the range : [ 0 , 1 ] */
class MW_5AXUTIL_API mwColor
{
public:
	//! Default Constructor
	/*! This constructor init class with black color which is: R = 0, B = 0, G = 0 */
	mwColor()
	{
		m_rgb[0] = 0.0f;
		m_rgb[1] = 0.0f;
		m_rgb[2] = 0.0f;
	}

	//! Constructor
	/*! This constructor allow you to init the class by specifying the color in RGB.
			\param vfRed - the red component of the color (it must be between 0 and 1)
			\param vfGreen - the green component of the color (it must be between 0 and 1)
			\param vfBlue - the blue component of the color (it must be between 0 and 1)
			\throws mwException - if the passed values are not in the range 0.0 to 1.0
	*/
	mwColor(const float vfRed, const float vfGreen, const float vfBlue)
	{
		m_rgb[0] = vfRed;
		m_rgb[1] = vfGreen;
		m_rgb[2] = vfBlue;
	}

	explicit mwColor(const mwColor4f& color);
	explicit mwColor(const mwColor4b& color);

	bool operator==(const mwColor& toCompare) const
	{
		return mathdef::is_eq(m_rgb[0], toCompare.m_rgb[0])
			&& mathdef::is_eq(m_rgb[1], toCompare.m_rgb[1])
			&& mathdef::is_eq(m_rgb[2], toCompare.m_rgb[2]);
	}

	bool operator!=(const mwColor& toCompare) const { return !(*this == toCompare); }

	float GetRed() const { return m_rgb[0]; }
	float GetGreen() const { return m_rgb[1]; }
	float GetBlue() const { return m_rgb[2]; }

	//! sets Red
	/*!
			\param vfRed the new red component of the color (it must be between 0 and 1)
			\throws mwException - if the passed value is not in the range 0 to 1
	*/
	void SetRed(const float vfRed)
	{
		if (vfRed < Min() || vfRed > Max())
			throw misc::mwRangeException<float>(Min(), Max(), vfRed);
		m_rgb[0] = vfRed;
	}

	//! sets Green
	/*!
			\param vfGreen the new green component of the color (it must be between 0 and 1)
			\throws mwException - if the passed value is not in the range 0 to 1
	*/
	void SetGreen(const float vfGreen)
	{
		if (vfGreen < Min() || vfGreen > Max())
			throw misc::mwRangeException<float>(Min(), Max(), vfGreen);
		m_rgb[1] = vfGreen;
	}

	//! sets Blue
	/*!
			\param vfBlue the new blue component of the color (it must be between 0 and 1)
			\throws mwException - if the passed value is not in the range 0.0 to 1.0
	*/
	void SetBlue(const float vfBlue)
	{
		if (vfBlue < Min() || vfBlue > Max())
			throw misc::mwRangeException<float>(Min(), Max(), vfBlue);
		m_rgb[2] = vfBlue;
	}

	MW_DEPRECATED("Deprecated function since 2021.12. Will be removed in the future.")
	static float GetMax() { return 1.0f; }

	MW_DEPRECATED("Deprecated function since 2021.12. Will be removed in the future.")
	static float GetMin() { return 0.0f; }

	//! \return float array of length 3 in order red, green, blue
	const float* GetRGB() const { return m_rgb; }

	//! \return float array of length 3 in order red, green, blue
	const float* AsArray() const { return m_rgb; }

private:
	static float Min() { return 0.0f; }
	static float Max() { return 1.0f; }
	float m_rgb[3];
};

//! compare two colors
/*! Comparison happens in the order R, G, B.
	\param first left hand
	\param second right hand
	\return  if first is lower than second
*/
inline bool operator<(const mwColor& first, const mwColor& second)
{
	if (first.GetRed() != second.GetRed()) return first.GetRed() < second.GetRed();
	if (first.GetGreen() != second.GetGreen()) return first.GetGreen() < second.GetGreen();
	return first.GetBlue() < second.GetBlue();
}

//! Implements an RGBA Color with 4 floats. Float color values in range of 0 to 1.
class MW_5AXUTIL_API mwColor4f
{
public:
	//! Default constructs to color black (0,0,0,1).
	mwColor4f()
	{
		m_rgba[0] = 0.f;
		m_rgba[1] = 0.f;
		m_rgba[2] = 0.f;
		m_rgba[3] = 1.f;
	}

	//! \throws mwException - if the passed values are not in range of 0 to 1
	mwColor4f(const float red, const float green, const float blue, const float alpha = 1.f)
	{
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
		SetAlpha(alpha);
	}

	explicit mwColor4f(const mwColor& color, const float alpha = 1.f)
	{
		SetRed(color.GetRed());
		SetGreen(color.GetGreen());
		SetBlue(color.GetBlue());
		SetAlpha(alpha);
	}

	explicit mwColor4f(const mwColor4b& color);

	bool operator==(const mwColor4f& other) const
	{
		return m_rgba[0] == other.m_rgba[0]
			&& m_rgba[1] == other.m_rgba[1]
			&& m_rgba[2] == other.m_rgba[2]
			&& m_rgba[3] == other.m_rgba[3];
	}

	bool operator!=(const mwColor4f& other) const { return !(*this == other); }

	float GetRed() const { return m_rgba[0]; }
	float GetGreen() const { return m_rgba[1]; }
	float GetBlue() const { return m_rgba[2]; }
	float GetAlpha() const { return m_rgba[3]; }

	//! \throws mwException - if the passed value is not in range of 0 to 1
	void SetRed(const float red)
	{
		if (red < 0.f || red > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, red);
		m_rgba[0] = red;
	}

	//! \throws mwException - if the passed value is not in range of 0 to 1
	void SetGreen(const float green)
	{
		if (green < 0.f || green > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, green);
		m_rgba[1] = green;
	}

	//! \throws mwException - if the passed value is not in range of 0 to 1
	void SetBlue(const float blue)
	{
		if (blue < 0.f || blue > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, blue);
		m_rgba[2] = blue;
	}

	//! \throws mwException - if the passed value is not in range of 0 to 1
	void SetAlpha(const float alpha)
	{
		if (alpha < 0.f || alpha > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, alpha);
		m_rgba[3] = alpha;
	}

	//! \return float array of length 4 in order red, green, blue, alpha
	const float* AsArray() const { return m_rgba; }

private:
	float m_rgba[4];
};

//! Implements an RGBA Color with 4 bytes. Color value range: [0,255]
class MW_5AXUTIL_API mwColor4b
{
public:
	//! Default constructs to color black (0,0,0,255).
	mwColor4b()
	{
		m_rgba[0] = 0;
		m_rgba[1] = 0;
		m_rgba[2] = 0;
		m_rgba[3] = 255;
	}

	mwColor4b(
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue,
		const unsigned char alpha = 255)
	{
		m_rgba[0] = red;
		m_rgba[1] = green;
		m_rgba[2] = blue;
		m_rgba[3] = alpha;
	}

	//! \throws mwException - if color values are not in range of 0 to 1
	explicit mwColor4b(const mwColor& color, const unsigned char alpha = 255)
	{
		if (color.GetRed() < 0.f || color.GetRed() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetRed());
		if (color.GetGreen() < 0.f || color.GetGreen() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetGreen());
		if (color.GetBlue() < 0.f || color.GetBlue() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetBlue());

		m_rgba[0] = static_cast<unsigned char>(color.GetRed() * 255);
		m_rgba[1] = static_cast<unsigned char>(color.GetGreen() * 255);
		m_rgba[2] = static_cast<unsigned char>(color.GetBlue() * 255);
		m_rgba[3] = alpha;
	}

	//! \throws mwException - if color or alpha values are not in range of 0 to 1
	mwColor4b(const mwColor& color, const float alpha)
	{
		if (color.GetRed() < 0.f || color.GetRed() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetRed());
		if (color.GetGreen() < 0.f || color.GetGreen() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetGreen());
		if (color.GetBlue() < 0.f || color.GetBlue() > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, color.GetBlue());
		if (alpha < 0.f || alpha > 1.f)
			throw misc::mwRangeException<float>(0.f, 1.f, alpha);

		m_rgba[0] = static_cast<unsigned char>(color.GetRed() * 255);
		m_rgba[1] = static_cast<unsigned char>(color.GetGreen() * 255);
		m_rgba[2] = static_cast<unsigned char>(color.GetBlue() * 255);
		m_rgba[3] = static_cast<unsigned char>(alpha * 255);
	}

	explicit mwColor4b(const mwColor4f& color)
	{
		m_rgba[0] = static_cast<unsigned char>(color.GetRed() * 255);
		m_rgba[1] = static_cast<unsigned char>(color.GetGreen() * 255);
		m_rgba[2] = static_cast<unsigned char>(color.GetBlue() * 255);
		m_rgba[3] = static_cast<unsigned char>(color.GetAlpha() * 255);
	}

	bool operator==(const mwColor4b& other) const
	{
		return m_rgba[0] == other.m_rgba[0]
			&& m_rgba[1] == other.m_rgba[1]
			&& m_rgba[2] == other.m_rgba[2]
			&& m_rgba[3] == other.m_rgba[3];
	}

	bool operator!=(const mwColor4b& other) const { return !(*this == other); }

	unsigned char GetRed() const { return m_rgba[0]; }
	unsigned char GetGreen() const { return m_rgba[1]; }
	unsigned char GetBlue() const { return m_rgba[2]; }
	unsigned char GetAlpha() const { return m_rgba[3]; }

	void SetRed(unsigned char red) { m_rgba[0] = red; }
	void SetGreen(unsigned char green) { m_rgba[1] = green; }
	void SetBlue(unsigned char blue) { m_rgba[2] = blue; }
	void SetAlpha(unsigned char alpha) { m_rgba[3] = alpha; }

	unsigned int ToHexABGR() const
	{
		unsigned int abgr = m_rgba[3];
		abgr <<= 8;
		abgr |= m_rgba[2];
		abgr <<= 8;
		abgr |= m_rgba[1];
		abgr <<= 8;
		abgr |= m_rgba[0];
		return abgr;
	}

	unsigned int ToHexRGBA() const
	{
		unsigned int rgba = m_rgba[0];
		rgba <<= 8;
		rgba |= m_rgba[1];
		rgba <<= 8;
		rgba |= m_rgba[2];
		rgba <<= 8;
		rgba |= m_rgba[3];
		return rgba;
	}

	static mwColor4b FromHexABGR(unsigned int abgr)
	{
		return mwColor4b(
			(abgr >> 0) & 0xFF,
			(abgr >> 8) & 0xFF,
			(abgr >> 16) & 0xFF,
			(abgr >> 24) & 0xFF
		);
	}

	static mwColor4b FromHexRGBA(unsigned int rgba)
	{
		return mwColor4b(
			(rgba >> 24) & 0xFF,
			(rgba >> 16) & 0xFF,
			(rgba >> 8) & 0xFF,
			(rgba >> 0) & 0xFF
		);
	}
private:
	unsigned char m_rgba[4];
};

inline mwColor::mwColor(const mwColor4f& color)
{
	m_rgb[0] = color.GetRed();
	m_rgb[1] = color.GetGreen();
	m_rgb[2] = color.GetBlue();
}

inline mwColor::mwColor(const mwColor4b& color)
{
	m_rgb[0] = color.GetRed() / 255.f;
	m_rgb[1] = color.GetGreen() / 255.f;
	m_rgb[2] = color.GetBlue() / 255.f;
}

inline mwColor4f::mwColor4f(const mwColor4b& color)
{
	m_rgba[0] = color.GetRed() / 255.f;
	m_rgba[1] = color.GetGreen() / 255.f;
	m_rgba[2] = color.GetBlue() / 255.f;
	m_rgba[3] = color.GetAlpha() / 255.f;
}

}  // namespace misc

namespace mmedia
{
MW_DEPRECATED("Deprecated since 2017.08. This typedef will be removed in the future. Use misc::mwColor instead.")
typedef misc::mwColor mwColor;
}  // namespace mmedia
#endif  //	MW_MWCOLOR_HPP_
