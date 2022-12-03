// (C) 2004-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOLYLINECUTTER_HPP_
#define MW_MW3DPOLYLINECUTTER_HPP_
#include "mw3dLineCutter.hpp"
#include "mw3dPolyLine.hpp"
#include "mwAutoPointer.hpp"
#include "mwException.hpp"

#include <list>
#include <queue>


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mw3dPolyLineCutter
{
public:
	typedef mw3dLine<T> Line;
	typedef typename Line::Ptr LinePtr;
	typedef typename std::list<LinePtr> LineList;

	typedef mw3dPolyLine<T> PolyLine;
	typedef typename PolyLine::Ptr PolyLinePtr;

	typedef typename Line::Point Point;
	typedef typename Line::PointPtr PointPtr;

	/// Constructor
	///
	///	@param target polyline reference to be cutted
	mw3dPolyLineCutter(const PolyLine& target): _Target(target) {}
	/// Destructor
	virtual ~mw3dPolyLineCutter() {}

	/// Gets polyline reference
	const PolyLine& GetTarget() const { return this->_Target; }
	/// Gets result of cutting
	LineList& GetResult() { return this->_Result; }


	/// Cuts this polyline by the vicinity of the given polyline.
	/// @param pl polylyne.
	/// @param radius radius of vicinity.
	void CutPolyLine(const mw3dPolyLine<T>& pl, T radius)
	{
		ResetResult();

		// empty polyline to cut, return empty result
		if (GetTarget().GetCount() == 0)
			return;

		typename PolyLine::LineListConstIt ti = GetTarget().GetLineBegin();
		typename PolyLine::LineListConstIt te = GetTarget().GetLineEnd();

		// nothing to cut with, return original uncut polyline
		if (pl.GetCount() == 0)
		{
			for (; ti != te; ++ti)
			{
				_Result.push_back(new Line((*ti)->GetStartPoint(), (*ti)->GetEndPoint()));
			}
			return;
		}

		// put all segments of target polyline into queue
		std::list<LinePtr> queue;
		for (; ti != te; ++ti)
		{
			queue.push_back(*ti);
		}

		typename PolyLine::LineListConstIt i = pl.GetLineBegin();
		typename PolyLine::LineListConstIt e = pl.GetLineEnd();
		// traverse segments of polyline to cut with
		for (; i != e; ++i)
		{
			typename std::list<LinePtr>::iterator stcIt(queue.begin());
			for (; stcIt != queue.end();)
			{
				LinePtr lineToCut(*stcIt);
				mw3dLineCutter<T> cutter1(*lineToCut);
				cutter1.CutSphere((*i)->GetStartPoint(), radius);

				LinePtr l1 = cutter1.GetResult1();
				LinePtr l2 = cutter1.GetResult2();

				std::list<LinePtr> cutResult;

				if (l1)
				{
					mw3dLineCutter<T> cutter2(*l1);
					cutter2.CutCylinder(**i, radius);
					if (cutter2.GetResult1().IsNotNull())
						cutResult.push_back(cutter2.GetResult1());
					if (cutter2.GetResult2().IsNotNull())
						cutResult.push_back(cutter2.GetResult2());
				}
				if (l2)
				{
					mw3dLineCutter<T> cutter3(*l2);
					cutter3.CutCylinder(**i, radius);
					if (cutter3.GetResult1().IsNotNull())
						cutResult.push_back(cutter3.GetResult1());
					if (cutter3.GetResult2().IsNotNull())
						cutResult.push_back(cutter3.GetResult2());
				}

				if (!cutResult.empty())
				{  // insert cut result instead of source line segment
					if (cutResult.size() == 1 && (*cutResult.back() == *lineToCut))
					{
						++stcIt;
						continue;
					}
					stcIt = queue.erase(stcIt);
					queue.insert(stcIt, cutResult.begin(), cutResult.end());
				}
				else
				{
					++stcIt;
				}
			}
		}

		typename std::list<LinePtr>::iterator it(queue.begin()), en(queue.end());
		for (; it != en; ++it)
		{
			mw3dLineCutter<T> cutter4(**it);
			cutter4.CutSphere(pl.GetEndPoint(), radius);
			LinePtr l1 = cutter4.GetResult1();
			LinePtr l2 = cutter4.GetResult2();
			if (l1)
				_Result.push_back(l1);
			if (l2)
				_Result.push_back(l2);
		}
	}

private:
	mw3dPolyLineCutter& operator=(
		mw3dPolyLineCutter&);  // avoid warning C4512 : assignment operator could not be generated
	/// Clears the result list
	void ResetResult() { _Result.clear(); }

	/// polyline reference
	const PolyLine& _Target;
	/// result list
	LineList _Result;
};

typedef mw3dPolyLineCutter<float> mw3dfPolyLineCutter;
typedef mw3dPolyLineCutter<double> mw3ddPolyLineCutter;
}  // namespace cadcam
#endif  //	MW_MW3DPOLYLINECUTTER_HPP_
