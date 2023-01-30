// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWANGLEUTILS_HPP_
#define MW_MWANGLEUTILS_HPP_
#include "mwDllImpExpDef.hpp"
#include <cstdlib>


namespace measures
{
	//!This class represents a angle util.
	template<class T>
	class MW_5AXUTIL_API mwAngleUtils
	{
	public:

		//! Get shortest angle in degrees
		/*! Get the shortest angle distance (always positive) between 2 given angles
			\param ang1 constant first angle 
			\param ang2 constant second angle 
			\returns a constant and shortest angle in degrees
		*/
		static const T GetShortestAngInDeg( const T ang1, const T ang2 );

				//! Get longest angle in degrees
		/*! Get the longest angle distance (always positive) between 2 given angles
			\param ang1 constant first angle 
			\param ang2 constant second angle 
			\returns a constant and longest angle in degrees
		*/
		static const T GetLongestAngInDeg( const T ang1, const T ang2 );

		//! Get counterclockwise angle in degrees
		/*!
			\param ang1 constant first angle 
			\param ang2 constant second angle 
			\returns a constant and CCW angle in degrees
		*/
		static const T GetCCWAngInDeg( const T ang1, const T ang2 );

		//! Map Angle between 0 and 360
		/*! Map a given angle in a angle between 0 and 360 degrees
			\param angleInDeg reference to a angle
		*/
		static void MapAngleBetween0And360(T &angleInDeg);

		//! Map Angle between -180 and +180
		/*! Map a given angle in a angle -180 and +180 degrees
			\param angleInDeg reference to the angle
		*/
		static void MapAngleBetwPlusMinus180( T &angleInDeg );

		//! Map Angle between (-pi/2,+pi/2]
		static void MapAngleBetwPlusMinus90(T &angleInRad);

		//! Map an angle between 0 and 2PI
		/*! Map the given angle to [0, 2*PI)
		\param angleInRad reference to the angle
		*/
		static void MapAngleBetween0And2PI(T& angleInRad);

		//! Map an angle interval between 0 and 2PI
		/*! Map the given angle interval, such that starting angle is in [0, 2*PI)
		\param leftInRad reference to the starting angle
		\param rightInRad reference to the ending angle
		*/
		static void MapAngleIntervalBetween0And2PI(T& startInRad, T& endInRad);

		//! Get winding factor from one angle to the next angle
		/*! E.g. if an angle is 170 and the next is 175, then winding factor is 0
			that means there is no winding required
			
			If the next angle is -160, then winding factor is 1, that means
			if we wind 1 x 360 degrees to -160 degree, then we will get 200
			
			Similarly, we will get a winding factor of -1, if the first angle is e.g.
			-170 and the next angle is +175, then winding factor is -1, so we will add
			-1 x 360 to the +175 and get -185
			
			The angles given can be in any range, so no need of having them between -180/180 etc.
			\param firstAng constant first angle
			\param nextAng constant next angle 
			\returns constant Winding factor
		*/
		static int GetWindingFactor( const T firstAng, const T nextAng );

		//! The IsAngleValidInUnitCircle function
		/*!
			\param startAngleInUnitCircle of type const T
			\param endAngleInUnitCircle of type const T
			\param curAngleToCheck of type const T
			\returns true if the specified angle is in circle interval
			The startAngleInUnitCircle and endAngleInUnitCircle parameters have a convention where
			the interval defined by startAngle and endAngle are defined in counter clock wise manner.
		*/
		static bool IsAngleValidInUnitCircle(
			const T startAngleInUnitCircle, const T endAngleInUnitCircle, const T curAngleToCheck);

		//! The IsAngleValidInUnitCircle function
		/*!
		\param startAngleInUnitCircle of type const T
		\param endAngleInUnitCircle of type const T
		\param curAngleToCheck of type const T
		\param angleTol of type const T
		\returns true if the specified angle is in circle interval
		The startAngleInUnitCircle and endAngleInUnitCircle parameters have a convention where
		the interval defined by startAngle and endAngle are defined in counter clock wise manner.
		*/
		static bool IsAngleValidInUnitCircle(
			const T startAngleInUnitCircle, const T endAngleInUnitCircle,
			const T curAngleToCheck, const T angleTol);

		static bool MapRadialAngleToInterval(T &radialAngle,const T xMin,const T xMax);

		static T AngularDistance(const T l1,const T b1, const T l2,const T b2);
		static T AngularDistanceDeg(const T l1,const T b1, const T l2,const T b2);
		//#############################################################################
		//!Map a integer value into an integer [0,u) interval knowing the upper bound of the interval (u)
		/*
			\param val2BeMapped is value to be mapped
			\param uBound is the upper bound of the interval (interval is [0,uBound) )
			\return a value from interval [0,u) obtained from input value to be mapped 
				by adding/subtracting the uBound value 
		*/
		static inline size_t MapValueBetw0AndUboundInterval(const int& val2BeMapped, const size_t& uBound)
		{
			int mappedVal = val2BeMapped;

			while (mappedVal < 0)
			{
				mappedVal += (int)uBound;
			}
			while (mappedVal >= (int)uBound)
			{
				mappedVal -= (int)uBound;
			}
			
			return (size_t)mappedVal;
		}
		//#############################################################################
	private:
		//! Constructor not allowed since it's a static class
		mwAngleUtils();
	};
}
#endif	//	MW_MWANGLEUTILS_HPP_
