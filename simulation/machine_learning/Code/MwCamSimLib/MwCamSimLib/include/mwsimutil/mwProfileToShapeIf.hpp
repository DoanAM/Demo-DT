// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPROFILETOSHAPEIF_HPP_
#define MW_MWPROFILETOSHAPEIF_HPP_
#include "mw2dPolyLine.hpp"
#include "mw2dPolylineUtils.hpp"
#include "mwAutoPointer.hpp"


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwProfileToShapeIf
{
public:
	typedef mw2dPolyLine<T> Profile;


	static bool IsProfileXMonotonIncreasingAlongY(const mw2dPolyLine<T>& polyline)
	{
		typedef typename mw2dPolyLine<T>::PointListConstIt PointListConstIt;
		T x, x_prev = 0;
		for (PointListConstIt cit = polyline.GetPointBegin(); cit != polyline.GetPointEnd(); ++cit)
		{
			x = (**cit).x();
			if (cit == polyline.GetPointBegin())
			{
				x_prev = x;
			}
			else
			{
				if (x_prev > x)
				{
					return false;
				}
				else
					x_prev = x;
			}
		}
		return true;
	}


	static cadcam::mw2dPolyLine<T> MakeProfileXMonotonIncreaseAlongY(
		const mw2dPolyLine<T>& polyline)
	{
		typedef typename mw2dPolyLine<T>::PointListConstIt PointListConstIt;
		typedef typename mw2dPolyLine<T>::Point Point;
		T x, y, x_prev = 0;
		mw2dPolyLine<T> polyline_cc;
		for (PointListConstIt cit = polyline.GetPointBegin(); cit != polyline.GetPointEnd(); ++cit)
		{
			x = (**cit).x();
			y = (**cit).y();
			if (cit == polyline.GetPointBegin())
			{
				Point p(x, y);
				polyline_cc.AddPoint(p);
				x_prev = x;
			}
			else if ((cit == (polyline.GetPointEnd()--)) && (x == 0))
			{
				Point p(0, y);
				polyline_cc.AddPoint(p);
			}
			else
			{
				if (x_prev > x)
				{
					x = x_prev;
					Point p(x, y);
					polyline_cc.AddPoint(p);
				}
				else
				{
					Point p(x, y);
					polyline_cc.AddPoint(p);
					x_prev = x;
				}
			}
		}

		cadcam::mw2dPolyLineUtils<T>::Reduce(
			polyline_cc, (T)mathdef::MW_MATH_TOL_SQRT / static_cast<T>(2.1));

		return polyline_cc;
	}

protected:
	mwProfileToShapeIf() {}

	virtual void Create(const Profile& profile)
	{
		typename Profile::PointListConstIt it, ite;
		it = profile.GetPointBegin();
		ite = profile.GetPointEnd();
		T r1, r2, d1, d2;

		if (it != ite)
		{
			r1 = it->x();
			d1 = it->y();
			++it;
			for (; it != ite; ++it)
			{
				r2 = it->x();
				d2 = it->y();
				if (!mathdef::is_eq(
						d1,
						d2,
						static_cast<T>(
							mathdef::MW_MATH_TOL_FLOAT)))  // ignore points with same height
				{
					if (mathdef::is_eq(r1, r2, static_cast<T>(mathdef::MW_MATH_TOL_FLOAT)))
					{
						CreateCylinder(r1, d2 - d1, d1);
					}
					else
					{
						CreateCone(r1, r2, d2 - d1, d1);
					}
				}
				d1 = d2;
				r1 = r2;
			}
		}
	}

	virtual void CreateCylinder(const T& radius, const T& height, const T& position) = 0;
	virtual void CreateCone(
		const T& bottomRadius, const T& topRadius, const T& height, const T& position) = 0;
};

}  // namespace cadcam
#endif  //	MW_MWPROFILETOSHAPEIF_HPP_
