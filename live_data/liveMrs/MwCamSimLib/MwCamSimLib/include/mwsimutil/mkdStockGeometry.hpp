// (C) 2005-2018 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDSTOCKGEOMETRY_HPP_
#define MW_MKDSTOCKGEOMETRY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdDynamicGeometry.hpp"
#include "mwDeprecated.hpp"
#include "mwColor.hpp"

class mwMachSimVerifier;

namespace machsim
{
namespace detail
{
class mwVerifierProxy;
}
}

namespace machsim
{
	class MW_SIMUTIL_API mkdStockGeometry : public mkdDynamicGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdStockGeometry> Ptr;

		/*! Parameterized constructor
			\param newID the name of the object
			\param dataRef the mesh associated to this object.
			\param STLFileName stl file associated to the mesh.
			\param unit the unit of measure.
		 */
		mkdStockGeometry
			( const id& newID
			, const polyDataRef& dataRef
			, const misc::mwstring& STLFileName
            , measures::mwUnitsFactory::Units unit );

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;


		//! Returns the associated mesh to this object.
		polyDataRef GetCurrentGeometry();

		//! Returns the verifier associated to this object.
		MW_DEPRECATED("Deprecated in 2018.08. Currently works. Please contact MW for a solution or use mwMachSimFacade::GetVerificationService()")
		mwMachSimVerifier* GetVerifier() const;

		//! for internal use only
		void SetVerifierProxy(std::shared_ptr<detail::mwVerifierProxy> impl);
		std::shared_ptr<detail::mwVerifierProxy> GetVerifierProxy() const {
			return m_verifierProxy;
		}

		//! Returns the zero based index of the verifier associated with this object.
		MW_DEPRECATED("Deprecated in 2018.08. Currently works. Please contact MW for a solution or use mwMachSimFacade::GetVerificationService()")
		const unsigned long& GetVerifierInstanceID() const;
		
		//! Notification that the appearance of this stock has changed.
		virtual void OnAppearanceChanged();

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 

	protected:
		/*! Scales the mesh associated to this object.
			\param unit the new unit of measure.
			\param scaleFactor the mesh scaling factor.
		*/
		void Scale(const measures::mwMeasurable::Units unit, const double& scaleFactor);


	private:
		std::shared_ptr<detail::mwVerifierProxy> m_verifierProxy;
		unsigned long			m_verifierInstanceID;
	};
};
#endif	//	MW_MKDSTOCKGEOMETRY_HPP_
