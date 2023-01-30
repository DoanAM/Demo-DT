// (C) 2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWKINEMATICOBJECTCOMMONDEFINES_HPP_
#define MW_MWKINEMATICOBJECTCOMMONDEFINES_HPP_
#include "mwEfficientVector.hpp"
#include "mwString.hpp"
#include "mwAutoPointer.hpp"
#include <list> 	   
#include "mwMatrix.hpp"
#include <map> 

//this is a place to put all the common typedef's  and definitions for kinematic processor 
namespace machsim
{
	typedef misc::mwstring							AxisName;

	typedef misc::mwAutoPointer<AxisName>			axisNamePtr;

	typedef std::list<axisNamePtr>					axisNames;

	typedef misc::mwEfficientVector<float, unsigned short>	AxisValuesContainer;

	typedef std::pair	< misc::mwstring, cadcam::mwHomogenousMatrix >	transform;

	typedef std::map	< misc::mwstring, cadcam::mwHomogenousMatrix >	transforms;	

	typedef std::pair<misc::mwstring, double>					AxisValue;

	typedef std::vector<AxisValue>								AxisValues;

	typedef std::pair<misc::mwstring, misc::mwstring>          mwStringPair;

	typedef std::vector<mwStringPair>                          mwStringPairVect;

	typedef std::vector<mwStringPair>::iterator                mwStringPairVectIt;

	typedef std::vector<mwStringPair>::const_iterator          mwStringPairVectConstIt;

	typedef misc::mwAutoPointer<mwStringPairVect>              mwStringPairVectPtr;			

}
#endif	//	MW_MWKINEMATICOBJECTCOMMONDEFINES_HPP_
