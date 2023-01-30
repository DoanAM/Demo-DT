// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTSPACELOCATION_HPP_
#define MW_MWTSPACELOCATION_HPP_
//#############################################################################
#include <mwAutoPointer.hpp>
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
	template <typename TCoordSystem>
	class MW_5AXUTIL_API mwTSpaceLocation
	{
	public:
		typedef TCoordSystem CoordSystem;
		typedef typename CoordSystem::ValueType CSValueType;
		typedef typename misc::mwAutoPointer< mwTSpaceLocation<CoordSystem> > Ptr;
		typedef typename CoordSystem::PositionVector PositionVector;
	private:
		typedef mwTSpaceLocation<CoordSystem>			MySelf;
	public:
//#############################################################################	
		//! Constructor
		/* 
				\param cs the coordinate system to be stored
		*/
		inline mwTSpaceLocation(const CoordSystem &cs)			
		{			
			SetCoordSystem(cs);
		}
//#############################################################################
		//! copy constructor
		/* 
				\param toCopy the space location to be copy
		*/
		inline mwTSpaceLocation(const MySelf &toCopy)			
		{			
			SetCoordSystem(toCopy.GetCoordSystem());
		}
//#############################################################################
		//! assignment operator
		/* 
				\param toCopy the space location to be copy
				\returns updated this
		*/
		inline const MySelf& operator=(const MySelf& rToCopy)
		{			
			if(&rToCopy != this)
			{
				SetCoordSystem(rToCopy.GetCoordSystem());
			}
			return (*this);
		}
//#############################################################################	
		//! Set the coordinate system 
		/* 
				\param cs the new coordinate system
		*/
		inline void SetCoordSystem(const CoordSystem &cs)
		{
			m_CoordSystem=cs.Clone();
		}
//#############################################################################	
		//! gets the coordinate system
		/*  NOTE:
			You may get here compiler error of type:
				Can not convert to mwTijkCoordSystem3d (or other) 
					from mwTAbstractCoordSystem3d(or other AbstractCS).
			This is because you specialized your geometry based on mwTijkCoordSystem3d instead of:
			mwTAbstractCoordSystem3d.
			You have to go where you declared your geometry and change specialization from the
			real CS to the abstract CS base class associated.
			You will say : "We may just do a cast here and everything will work fine".
			Yes, Since CoordSystem is Template argument we could have safe implement this as
				return static_cast<CoordSystem&>(*m_CoordSystem);
			instead of:
				return *(m_CoordSystem);
			And in this case you would have not get any compiler error.
			But, this has the draw back that you can not get from a high abstraction to
			a lower abstraction.
			Let me give you an example:
				Let's say you have a Rectangle in a system 3d with O i j k.
				And someone created an algorithm that translates origin of any Rectangle defined in 3d.
			Following are the definitions:
			your object declaration will be:
				mwTRectangle<double, mwTijkCoordSystem3d<double>> myRactangle;
			algorithm function declaration will be:
				void Translate(mwTRectangle<double, mwTCoordSystem3d<double>> toTranslate,const Vector3d& offset);
			Both declarations are correct since the both are declaring the minimal information needed, but,
			if you try to pass your "myRactangle" object to the "Translate" function, the compiler will
			tell you that it is not possible since no conversion operator defined.
			The compiler is right since the Rectangles defined are different even if
			the mwTijkCoordSystem3d may be derived from mwTCoordSystem3d.
			So, in order to avoid such cases we decided to force everyone to be able to declare geometries 
			only based on the abstract classes of the CS. So the declarations will became:
				mwTRectangle<double, mwTAbstractCoordSystem3d<double>> myRactangle;
			and
				void Translate(mwTRectangle<double, mwTAbstractCoordSystem3d<double>> toTranslate,const Vector3d& offset);
			Doing this there will not be two distinguish objects and you will be able to call Translate function.
			You will say:
				"Thats ok for Translate, since i need only the Origin, and all the CS has origin,
				but how about an algorithm that	needs to know if the 3dCS has the j axis? In such a case i must declare
				that function receives a Rectangle which has at least a mwTijCoordSystem3d system."
			Well, i will argue you that the algorithm knows enough base on the fact that the template class
			is mwTAbstractCoordSystem3d. It knows that the Rectangle is in a 3d CS, so it should be able
			to transform such a system base on a i,j or k vector using a factory. The fact that one 3dCS decided to ignore
			such a transformation (as mwTiCoordSystem3d class is ignoring any transformation based on j or k vector ),
			is something that depends only of the implementation of that particular CS.
			So, the base line is that your "algorithm that	needs to know if the 3dCS has the j axis" actually should 
			just know if the system is 3d, and use the appropriate factory for j axis transformations he needs to do.

				\returns the coordinate system
		*/
		inline const CoordSystem& GetCoordSystem() const
		{
			return *(m_CoordSystem);
		}
//#############################################################################	
	protected:
		typedef typename CoordSystem::BaseCSPtr CoordSystemPtr;
		CoordSystemPtr m_CoordSystem;
	};
}
#endif	//	MW_MWTSPACELOCATION_HPP_
