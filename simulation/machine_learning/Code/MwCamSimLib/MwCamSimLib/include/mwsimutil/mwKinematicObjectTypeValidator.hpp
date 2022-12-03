// (C) 2006-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWKINEMATICOBJECTTYPEVALIDATOR_HPP_
#define MW_MWKINEMATICOBJECTTYPEVALIDATOR_HPP_
#include "mkdKinematicObject.hpp"

namespace machsim
{
	template <class T >
	class MW_SIMUTIL_API mwKinematicObjectTypeValidator : public mkdKOConstVisitor
	{
	public:
		const misc::mwAutoPointer<T> GetValidatedObject(); 			

		mwKinematicObjectTypeValidator() :m_lastVisitedHadTType(false) {};

		const bool ObjectValidated() const	{ return m_lastVisitedHadTType; }

		virtual void Visit(const mkdKinematicObject& toVisit);		
		virtual void Visit(const mkdPolygonalGeometry& toVisit);
		virtual void Visit(const mkdToolpathGeometry& toVisit);
		virtual void Visit(const mkdHeldTool& toVisit);
		virtual void Visit(const mkdCoordinateTransform& toVisit);
		virtual void Visit(const mkdRevolvingSet& toVisit);
		virtual void Visit(const mkdRotationalAxis& toVisit);
		virtual void Visit(const mkdTranslationalAxis& toVisit);
		virtual void Visit(const mkdWorkPiece& toVisit);
		virtual void Visit(const mkdFixture& toVisit);
		virtual void Visit(const mkdStockGeometry& toVisit);
		virtual void Visit(const mkdTailStock& toVisit);
		virtual void Visit(const mkdInitialStock& toVisit);
		virtual void Visit(const mkdWireEDMHead& toVisit);
		virtual void Visit(const mkdMountAdapter& toVisit);	 		
	private:

		misc::mwAutoPointer<T>	m_validatedObject;
		bool					m_lastVisitedHadTType;

	};
	template <typename T, typename V>
	class DynamicCaster	: public mwKinematicObjectTypeValidator<T>   
	{	
	public:  		
		static bool TryDynamicCast(const V & toVisit, misc::mwAutoPointer<T>& validatedObject);
	};

	
} // machsim namespace
#endif	//	MW_MWKINEMATICOBJECTTYPEVALIDATOR_HPP_
