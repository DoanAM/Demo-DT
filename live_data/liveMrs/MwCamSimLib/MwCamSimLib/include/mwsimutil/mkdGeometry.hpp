// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDGEOMETRY_HPP_
#define MW_MKDGEOMETRY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdKinematicObject.hpp"
#include "mwAppearance.hpp"


namespace machsim
{
	//!class mkdGeometry
	class MW_SIMUTIL_API mkdGeometry : public mkdKinematicObject
	{
	public:
		typedef misc::mwAutoPointer<mkdGeometry>	Ptr;
		typedef mmedia::mwAppearance				appearance;
		
		/*! Parameterized constructor
			\param newID the name of this object
			\param unit the unit of measure.
		 */
		mkdGeometry(const id &newID, const measures::mwMeasurable::Units unit);

		//! Returns the current appearance of this geometry.
		const appearance &GetAppearance() const;
		
		//! Returns the saved appearance of this geometry.
		const appearance &GetSavedAppearance() const;
		
		/*! Sets the current appearance of this geometry.
			\param newAppearance the new visual attribute for this geometry.
		 */
		void SetAppearance(const appearance& newAppearance);

		/*! Sets the saved appearance of this object
			\param newAppearance the new saved visual attribute.
		 */
		void SetSavedAppearance( const appearance &newAppearance );

		//! Reverts the current appearance to the saved value.
		void RevertToSavedAppearance();

		//! Reverts teh current color to the saved value.
		void RevertToSavedColor();

		//! OnAppearanceChanged notification.
		virtual void OnAppearanceChanged();
		
		/*! Set the coordinate system.
			\param newCS the new coordinate system matrix.
		 */
		void SetCoordinateSystem(const matrix &newCS);
		
		/*! Set the adjusting matrix.
			\param newCS the new adjusting matrix.
		 */
		void SetAdjustingTransform( const matrix &toSet );
		
		//! Returns the adjusting transformation matrix.
		const matrix GetAdjustingTransform() const;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ) = 0;
		
		virtual ~mkdGeometry() = 0;
	protected:
		/*! Scales the object.
			\param units the new unit of measure.
			\param factor the scaling factor.
		*/
		void Scale(const measures::mwMeasurable::Units units, const double& factor) ;
		//! used on cloning to avoid code duplication in derived classes
		void BaseGeometryClone(mkdGeometry& source, const bool justKinematicRelevantInfo);

	private:
		appearance		mAppearance;
		appearance		mSavedAppearance;
		bool			bSavedAppearance;
		matrix			m_adjustingMatrix;
	};
};
#endif	//	MW_MKDGEOMETRY_HPP_
