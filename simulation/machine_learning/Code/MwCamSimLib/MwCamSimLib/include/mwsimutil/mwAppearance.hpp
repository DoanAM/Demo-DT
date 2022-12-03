// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWAPPEARANCE_HPP_
#define MW_MWAPPEARANCE_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMaterial.hpp"
#include "mwAppearanceApplier.hpp"

namespace mmedia
{
	//!This class represents visualization properties.
	class MW_5AXUTIL_API mwAppearance
	{
	public:

		typedef misc::mwColor color;

		//!Constructor
		/*!Constructs mwAppearance object
		*/
		explicit mwAppearance();

		mwAppearance(const mwAppearance &toCopy);

		const mwAppearance& operator=( const mwAppearance& toCopy );

		void Default();

		MW_DEPRECATED("Deprecated since 2022.04.")
		mwAppearanceApplierIntf& GetAppearanceApplier() const;

		MW_DEPRECATED("Deprecated since 2022.04.")
		void SetAppearanceApplier( mwAppearanceApplierIntf::Ptr& newImpl );

		/*! Returns mwMaterial object reference
		*/		
		mwMaterial & Material();

		/*! Returns mwMaterial object const reference
		*/		
		const mwMaterial & Material() const;

		/*! Sets mwMaterial object.
			\param value mwMaterial object to be setted.
		*/		
		void Material( const mwMaterial & value );

        //! Returns Color
	    /*! 			
			    \return color
	    */
        const misc::mwColor& Color() const;

	    //! sets Color
	    /*! 			
			    \param color new Color
	    */
	    void Color( const misc::mwColor &color );

		//! sets Highlight status
	    /*! 			
			    \param highlight new isHighlighted
	    */
	    void IsHighlighted( bool value );

		//! Returns Highlight status
	    /*! 			
			    \return highlight
	    */
        const bool IsHighlighted() const;

		/*! Returns the diameter of rasterized points.
		*/
		double PointSize() const;

		/*! Specifies the diameter of rasterized points.
			\param value the diameter of rasterized points
		*/	
		void PointSize( double value );

		/*! Returns the width of rasterized lines.
		*/
		double LineWidth() const;

		/*! Specifies the width of rasterized lines.
			\param value the width of rasterized lines
		*/	
		void LineWidth( double value );

		/*! Returns line stipple factor.
		*/
		int LineStippleFactor() const;

		/*! Sets a multiplier for each bit in the line stipple pattern. If factor is 3, for example, each bit in
			the pattern will be used three times before the next bit in the pattern is used. The factor parameter
			is clamped to the range [1, 256] and defaults to one.
			\param value line stipple factor.
		*/	
		void LineStippleFactor( int value );

		/*! Returns line Stipple Pattern.
		*/
		unsigned short LineStipplePattern() const;

		/*! Sets a 16-bit integer whose bit pattern determines which fragments of a line will be drawn when the line
			is rasterized. Bit zero is used first, and the default pattern is all ones.
			\param value line Stipple Pattern
		*/	
		void LineStipplePattern( unsigned short value );

		misc::mwstring LabelData() const;

		void LabelData(misc::mwstring &data);

		//! Sets culling faces status
		/*!
		\param mCullFaces new mCullFaces
		*/
		void CullFaces(bool value);

		//! Returns culling faces status
		/*!
		\return mCullFaces
		*/
		const bool CullFaces() const;

		//! Default line stipple pattern - solid line.
		static const unsigned short LINE_PATTERN_SOLID       ;
		//! Line will be drawn as sequence of dashes.
		static const unsigned short LINE_PATTERN_DASH        ;
		//! Line will be drawn as sequence of alternating dashes and dots.
		static const unsigned short LINE_PATTERN_DASH_DOT    ;
		//! "dash - dot - dot" line stipple pattern.
		static const unsigned short LINE_PATTERN_DASH_DOT_DOT;

		//######################################################################
		//! = operator
		/*! Test whether this object is equal to the given mwAppearance object.
			\param tc specified mwAppearance object.
			\return true if this object are equal to the given mwAppearance object.
		*/
		bool operator==( const mwAppearance &tc ) const;

		//#######################################################################
		//! != operator
		/*! Test whether this object is not equal to the given mwAppearance object.
			\param tc specified mwAppearance object.
			\return true if this object are not equal to the given mwAppearance object.
		*/
		bool operator!=( const mwAppearance &tc ) const;

		//#######################################################################

	private:
		void ResetAppearanceApplier();

		void Copy( const mwAppearance &toCopy );

		//! Contains information about material properties
		mwMaterial  mMaterial;
		//! The diameter of rasterized points
		double      mPointSize;
		//! The width of rasterized lines
		double      mLineWidth;
		//! A multiplier for each bit in the line stipple pattern
		double      mLineStippleFactor;
		//! A 16-bit integer whose bit pattern determines which fragments of a line will be drawn when the line is rasterized
		double      mLineStipplePattern;

#pragma warning(push)
#pragma warning(disable:4251)
        //! The color value
		misc::mwColor     mColor;

		mutable mwAppearanceApplierIntf::Ptr			m_applier;
#pragma warning(pop)

		//! The highlight status
		bool		mIsHighlighted;
		//! Activates color difference between front and back faces
		bool		mCullFaces;
		
		misc::mwstring mLabelData;
	};

	//! < operator
	/*! Test whether given first object is less than given second object
		\param first first mwAppearance object reference
		\param second second mwAppearance object reference
		\return true if first object is less than second object
	*/
	inline const bool operator < ( const mwAppearance &first, const mwAppearance &second )
	{
		return first.Material() < second.Material()
			&& first.Color() < second.Color();
	};
}
#endif	//	MW_MWAPPEARANCE_HPP_
