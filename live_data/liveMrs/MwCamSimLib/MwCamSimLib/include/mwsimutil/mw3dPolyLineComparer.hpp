// (C) 2004-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOLYLINECOMPARER_HPP_
#define MW_MW3DPOLYLINECOMPARER_HPP_
#include "mw3dPolyLineCutter.hpp"
#include "mwAutoPointer.hpp"
#include "mwUpdateHandlerInterface.hpp"
#include "mwmiscException.hpp"

#include <list>


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mw3dPolyLineComparer
{
public:
	typedef mw3dPolyLine<T> PolyLine;
	typedef typename PolyLine::Ptr PolyLinePtr;

	/// Constuctor
	///
	/// @param target first polyline reference
	/// @param source second polyline reference
	mw3dPolyLineComparer(const PolyLine& target, const PolyLine& source)
		: _Target(target), _Source(source)
	{
	}
	/// Destructor
	virtual ~mw3dPolyLineComparer() {}

	/// Gets first polyline reference
	const PolyLine& GetTarget() const { return this->_Target; }
	/// Gets second polyline reference
	const PolyLine& GetSource() const { return this->_Source; }

	/// Returns true if, and only if, all point distances of
	///
	/// both polylines are less than factor.
	/// @param factor comparison factor
	/// @return true.

	bool IsTolerant(T factor);

private:
	mw3dPolyLineComparer& operator=(mw3dPolyLineComparer&);  // avoid warning C4512
	/// First polyline object
	const PolyLine& _Target;
	/// Second polyline object
	const PolyLine& _Source;
};


/// This class is used for comparing two polilines using Snake compare algorithm
class MW_5AXUTIL_API mwPolyLineSnakeCompare
{
public:
	static void VerifyIfCanceledCompare(const interact::mwUpdateHandlerInterface::Ptr& uhePtr)
	{
		if (uhePtr.IsNotNull() && uhePtr->IsCanceled())
		{
			throw mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION);
		}
	}

	enum DifferenceType
	{
		PLSC_DT_NONE,
		PLSC_DT_POSITION,
		PLSC_DT_ORIENTATION
	};

	typedef std::pair<size_t, DifferenceType> DifferenceInfo;
	typedef std::list<DifferenceInfo> MoveIndices;

	template <class ContainerConstIterator, class DistanceCalculator>
	static bool Compare(
		ContainerConstIterator itInputBegin1,
		ContainerConstIterator itInputEnd1,
		ContainerConstIterator itInputBegin2,
		ContainerConstIterator itInputEnd2,
		DistanceCalculator distCalculator,
		double delta,
		double delta1,
		double toolLength,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL)
	{
		if (itInputBegin1 == itInputEnd1 && itInputBegin2 != itInputEnd2)
			return false;


		ContainerConstIterator tmpIt = itInputBegin2;
		if (itInputBegin2 == itInputEnd2 || ++tmpIt == itInputEnd2)
			return true;

		ExitGettingFarther exitStrategy;
		return Compare(
				   itInputBegin1,
				   itInputEnd1,
				   itInputBegin2,
				   itInputEnd2,
				   distCalculator,
				   delta,
				   delta1,
				   toolLength,
				   true,
				   exitStrategy,
				   uhePtr)
			.empty();
	}

	template <class ContainerConstIterator, class DistanceCalculator>
	static MoveIndices MarkDifferences(
		ContainerConstIterator itInputBegin1,
		ContainerConstIterator itInputEnd1,
		ContainerConstIterator itInputBegin2,
		ContainerConstIterator itInputEnd2,
		DistanceCalculator distCalculator,
		double delta,
		double delta1,
		double toolLength,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0)
	{
		if (itInputBegin1 == itInputEnd1)
			return MoveIndices();

		if (itInputBegin2 == itInputEnd2)
		{
			MoveIndices result;
			size_t moveIdx = 0;
			for (ContainerConstIterator it = itInputBegin1; it != itInputEnd1; ++it, ++moveIdx)
			{
				VerifyIfCanceledCompare(uhePtr);

				result.push_back(DifferenceInfo(moveIdx, PLSC_DT_POSITION));
				if (maxNbDifferences > 0 && (int)result.size() >= maxNbDifferences)
				{
					return result;
				}
			}
			return result;
		}

		ContainerConstIterator tmpIt = itInputBegin2;
		if (++tmpIt == itInputEnd2)
		{
			MoveIndices result;
			size_t moveIdx = 0;
			for (ContainerConstIterator it = itInputBegin1; it != itInputEnd1; ++it, ++moveIdx)
			{
				VerifyIfCanceledCompare(uhePtr);

				double dis;
				double disX;

				distCalculator(it, itInputBegin2, toolLength, dis, disX);

				if (dis > delta)
				{
					result.push_back(DifferenceInfo(moveIdx, PLSC_DT_POSITION));
				}
				else
				{
					if (disX > delta1)
					{
						result.push_back(DifferenceInfo(moveIdx, PLSC_DT_ORIENTATION));
					}
				}
				if (maxNbDifferences > 0 && (int)result.size() >= maxNbDifferences)
				{
					return result;
				}
			}
			return result;
		}

		ExitGettingFarther exitStrategy;
		return Compare(
			itInputBegin1,
			itInputEnd1,
			itInputBegin2,
			itInputEnd2,
			distCalculator,
			delta,
			delta1,
			toolLength,
			false,
			exitStrategy,
			uhePtr,
			maxNbDifferences);
	}

private:
	mwPolyLineSnakeCompare();

	class ExitCondition
	{
	public:
		virtual bool operator()(double dis, double disX) const = 0;
		virtual void SetDistances(double dis, double disX) = 0;
	};

	class ExitGettingFarther: public ExitCondition
	{
	public:
		ExitGettingFarther(): m_dis(0), m_disX(0) {}

		virtual bool operator()(double dis, double disX) const
		{
			return dis >= m_dis && disX >= m_disX;
		}

		virtual void SetDistances(double dis, double disX)
		{
			m_dis = dis;
			m_disX = disX;
		}

	private:
		double m_dis;
		double m_disX;
	};

	class ExitNever: public ExitCondition
	{
	public:
		virtual bool operator()(double, double) const { return false; }

		virtual void SetDistances(double, double) {}
	};

	// this is used to avoid duplicated moves
	template <class ContainerConstIterator, class DistanceCalculator>
	static void GetNextSegment(
		ContainerConstIterator& it2p,
		ContainerConstIterator& it2,
		const ContainerConstIterator& itInputEnd2,
		DistanceCalculator distCalculator,
		double toolLength,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL)
	{
		it2p = it2;

		double dis = mathdef::MW_MAX_DOUBLE;
		double disX = mathdef::MW_MAX_DOUBLE;
		do
		{
			VerifyIfCanceledCompare(uhePtr);

			++it2;
			if (it2 != itInputEnd2)
			{
				distCalculator(it2, it2p, toolLength, dis, disX);
			}
			else
			{
				break;
			}
		} while (mathdef::is_eq(dis, 0) && mathdef::is_eq(disX, 0));
	}

	template <class ContainerConstIterator, class DistanceCalculator>
	static MoveIndices Compare(
		ContainerConstIterator itInputBegin1,
		ContainerConstIterator itInputEnd1,
		ContainerConstIterator itInputBegin2,
		ContainerConstIterator itInputEnd2,
		DistanceCalculator distCalculator,
		double delta,
		double delta1,
		double toolLength,
		bool exitOnDifferent,
		ExitCondition& exitStrategy,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL,
		const int maxNbDifferences = 0)
	{
		ContainerConstIterator End1 = itInputEnd1;
		ContainerConstIterator it1 = itInputBegin1;
		ContainerConstIterator End2 = itInputEnd2;
		ContainerConstIterator it2 = itInputBegin2;
		ContainerConstIterator it2p = it2;

		++it2;

		ContainerConstIterator prevSegmentStart = it2p;
		ContainerConstIterator prevSegmentEnd = it2;

		ContainerConstIterator minIntervalFirstSegmentStart = it2p;
		ContainerConstIterator minIntervalFirstSegmentEnd = it2;
		ContainerConstIterator minIntervalLastSegmentStart = it2p;
		ContainerConstIterator minIntervalLastSegmentEnd = it2;

		// Need to keep iterators to previous segment due to the utilisation of GetNextSegment()
		// so that we compare directly iterators instead of pointed values.
		ContainerConstIterator candidateMinIntervalLastSegmentStart = minIntervalLastSegmentStart;
		ContainerConstIterator candidateMinIntervalLastSegmentEnd = minIntervalLastSegmentEnd;

		MoveIndices result;
		size_t moveIdx = 0;
		bool isMinInterval = false;

		for (; it1 != End1; ++it1, ++moveIdx)
		{
			bool once = false;

			double minDist = mathdef::MW_MAX_DOUBLE;

			bool newInterval = true;
			if (isMinInterval)
			{
				minIntervalLastSegmentStart = candidateMinIntervalLastSegmentStart;
				minIntervalLastSegmentEnd = candidateMinIntervalLastSegmentEnd;
				isMinInterval = false;
			}

			ContainerConstIterator crtSegmentStart = minIntervalLastSegmentStart;
			ContainerConstIterator crtSegmentEnd = minIntervalLastSegmentEnd;
			bool passedEndOfPrevInterval = false;

			for (it2p = minIntervalFirstSegmentStart, it2 = minIntervalFirstSegmentEnd;
				 it2 != End2;)
			{
				VerifyIfCanceledCompare(uhePtr);

				if (it2p == crtSegmentEnd)
					passedEndOfPrevInterval = true;

				double dis;
				double disX;

				distCalculator(it1, it2, it2p, toolLength, dis, disX);

				const bool foundSegmentInTolerance = dis <= delta && disX <= delta1;

				DifferenceType differenceType = PLSC_DT_NONE;
				if (dis > delta)
				{
					differenceType = PLSC_DT_POSITION;
				}
				else
				{
					if (disX > delta1)
					{
						differenceType = PLSC_DT_ORIENTATION;
					}
				}

				if (exitOnDifferent && it1 == itInputBegin1 && it2p == itInputBegin2 &&
					!foundSegmentInTolerance)
				{
					result.push_back(DifferenceInfo(moveIdx, differenceType));
					return result;  //<<<<<<<<<<<<<<<<<<<<<<<<OUT
				}

				if (foundSegmentInTolerance)
				{
					if (newInterval)  // the beginning of an interval
					{
						if (!once)
						{
							minIntervalFirstSegmentStart = it2p;
							minIntervalFirstSegmentEnd = it2;
							minDist = dis;
							once = true;
						}
						prevSegmentStart = it2p;
						prevSegmentEnd = it2;
						newInterval = false;
					}
					if (minDist > dis)  // case 80016: update less frequently
										// minIntervalFirstSegment & minIntervalLastSegment
					{
						minDist = dis;
						minIntervalFirstSegmentStart = prevSegmentStart;
						minIntervalFirstSegmentEnd = prevSegmentEnd;
					}
					isMinInterval = true;
				}
				else
				{
					if (once)
					{
						if (isMinInterval)
						{
							minIntervalLastSegmentStart = candidateMinIntervalLastSegmentStart;
							minIntervalLastSegmentEnd = candidateMinIntervalLastSegmentEnd;
						}
						if (it1 == itInputBegin1)
							break;
					}

					newInterval = true;  // current tolerance interval finished
					isMinInterval = false;

					if (passedEndOfPrevInterval)  // we've passed the end of the previous interval
					{
						if (once)
							break;

						exitStrategy.SetDistances(dis, disX);
						once = mwPolyLineSearchForward(
							it1,
							minIntervalFirstSegmentStart,
							minIntervalFirstSegmentEnd,
							it2p,
							it2,
							End2,
							distCalculator,
							delta,
							delta1,
							exitStrategy,
							toolLength,
							minDist,
							differenceType,
							uhePtr);
						if (!once)
						{
							result.push_back(DifferenceInfo(moveIdx, differenceType));
							if (maxNbDifferences > 0 && (int)result.size() >= maxNbDifferences)
							{
								return result;
							}
							if (exitOnDifferent)
							{
								return result;
							}
							break;
						}
						else
						{
							// update minIntervalLastSegment<>
							isMinInterval = true;
						}
					}
				}
				candidateMinIntervalLastSegmentStart = it2p;
				candidateMinIntervalLastSegmentEnd = it2;
				GetNextSegment(it2p, it2, End2, distCalculator, toolLength, uhePtr);

				if (!once && it2 == End2)
				{
					result.push_back(DifferenceInfo(moveIdx, differenceType));
					if (maxNbDifferences > 0 && (int)result.size() >= maxNbDifferences)
					{
						return result;
					}
				}
			}
		}

		return result;
	}


	template <class ContainerConstIterator, class DistanceCalculator>
	static bool mwPolyLineSearchForward(
		ContainerConstIterator it1,
		ContainerConstIterator& minIntervalFirstSegmentStart,
		ContainerConstIterator& minIntervalFirstSegmentEnd,
		ContainerConstIterator& it2p,
		ContainerConstIterator& it2,
		ContainerConstIterator itInputEnd2,
		DistanceCalculator distCalculator,
		double delta,
		double delta1,
		const ExitCondition& exitCondition,
		double toolLength,
		double& minDist,
		DifferenceType& differenceType,
		interact::mwUpdateHandlerInterface::Ptr uhePtr = MW_NULL)
	{
		ContainerConstIterator _it2p = it2p;
		ContainerConstIterator _it2 = it2;

		GetNextSegment(_it2p, _it2, itInputEnd2, distCalculator, toolLength, uhePtr);

		for (; _it2 != itInputEnd2;)
		{
			double _dis;
			double _disX;

			distCalculator(it1, _it2, _it2p, toolLength, _dis, _disX);

			const bool foundSegmentInTolerance = _dis <= delta && _disX <= delta1;

			if (foundSegmentInTolerance)
			{
				differenceType = PLSC_DT_NONE;
				minDist = _dis;
				minIntervalFirstSegmentStart = _it2p;
				minIntervalFirstSegmentEnd = _it2;
				it2p = _it2p;
				it2 = _it2;
				return true;
			}

			// Determine type of difference.
			// If we found at least one point that has a position in tolerance then we report
			// orientation as different.
			if (differenceType == PLSC_DT_NONE)
			{
				if (_dis > delta)
				{
					differenceType = PLSC_DT_POSITION;
				}
				else
				{
					differenceType = PLSC_DT_ORIENTATION;
				}
			}
			else
			{
				if (differenceType == PLSC_DT_POSITION)
				{
					if (_dis <= delta)  //  && _disX > delta1
					{
						differenceType = PLSC_DT_ORIENTATION;
					}
				}
			}

			if (exitCondition(_dis, _disX))
			{
				return false;
			}

			GetNextSegment(_it2p, _it2, itInputEnd2, distCalculator, toolLength, uhePtr);
		}
		return false;
	}
};


typedef mw3dPolyLineComparer<float> mw3dfPolyLineComparer;
typedef mw3dPolyLineComparer<double> mw3ddPolyLineComparer;
}  // namespace cadcam
#endif  //	MW_MW3DPOLYLINECOMPARER_HPP_
