// (C) 2006 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWANGLESERVICE_HPP_
#define MW_MWANGLESERVICE_HPP_
#include "mwAngleDegree.hpp"
#include "mwAngleRadian.hpp"

namespace measures
{
	template <typename T>
	class mwAngleService
	{
	public:

		static const mwAngleRadian<T> GetAngleRadian( const mwAngleDegree<T> &angle );
		static const mwAngleDegree<T> GetAngleDegree( const mwAngleRadian<T> &angle );
		static void ConvertAngle( const mwAngleDegree<T> &angleDegree, mwAngleRadian<T> &angleRadian );
		static void ConvertAngle( const mwAngleRadian<T> &angleRadian, mwAngleDegree<T> &angleDegree );
		static void MapAngleBetween0And360( mwAngleDegree<T> &angle );
		static void MapAngleBetweenPlusMinus180( mwAngleDegree<T> &angle );
		
	private:
		//static class
		mwAngleService();

	};
};
#endif	//	MW_MWANGLESERVICE_HPP_
