// (C) 2003-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPPASS_HPP_
#define MW_MWTPPASS_HPP_

#include "mwAutoPointer.hpp"
#include "mwCollectionOfContainers.hpp"
#include "mwMovesAccessor.hpp"
#include "mwTPSlice.hpp"


namespace cadcam
{
class mwToolPath;

/// this class implements a toolpath pass
///
/// A toolpath pass is a list of toolpath slices.
///	This class can be also saw as a continue list of moves which is actually the result of
///	concatenating all the moves from all slices.
///	If you try to add a move in pass and there is no slice available then the class is
///	creating a default one for you.
class MW_5AXUTIL_API mwTPPass: public mwMovesAccessor<
					misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSlice>>>>
{
public:
	/// rename slice
	typedef mwTPSlice TPSlice;
	/// rename pass ptr
	typedef misc::mwAutoPointer<mwTPPass> Ptr;
	/// rename slice ptr
	typedef misc::mwAutoPointer<TPSlice> TPSlicePtr;
	/// reneme slices
	typedef std::list<TPSlicePtr> TPSlices;
	/// reneme slices iterator
	typedef TPSlices::iterator OverTPSlicesIterator;
	/// rename  slices const iterator
	typedef TPSlices::const_iterator ConstOverTPSlicesIterator;

	/// return a bidirectional iterator to the first slice
	///
	/// return a bidirectional iterator that points at the first slice
	///	available (or just beyond the end of the sequence if there is no slice).
	OverTPSlicesIterator GetSlicesBegin() { return m_Collection.begin(); };

	/// const version of GetSlicesBegin()
	ConstOverTPSlicesIterator GetSlicesBegin() const { return m_Collection.begin(); };

	/// return a bidirectional iterator that points just beyond the end of the slices.
	OverTPSlicesIterator GetSlicesEnd() { return m_Collection.end(); };

	/// return a last element of container
	misc::mwAutoPointer<cadcam::mwTPSlice>& GetBack() { return m_Collection.back(); }

	/// const version of GetSlicesEnd()
	ConstOverTPSlicesIterator GetSlicesEnd() const { return m_Collection.end(); };

	/// return how many slices are in in the sequence
	unsigned int GetSlicesCount() const { return (unsigned int)m_Collection.size(); };

	/// inserts a slice at the end of the sequence
	void PushBack(TPSlicePtr slice) { m_Collection.push_back(slice); };

	/// inserts a slice at the beginning of the sequence
	void PushFront(TPSlicePtr slice) { m_Collection.push_front(slice); };

	/// inserts a slice just before specified position
	OverTPSlicesIterator Insert(OverTPSlicesIterator& insertionPoint, TPSlicePtr slice)
	{
		return m_Collection.insert(insertionPoint, slice);
	};

	/// erases all slices from sequence
	void Clear() { m_Collection.clear(); };

	/// removes the slices from the sequence in the range [first, last)
	OverTPSlicesIterator EraseSlices(OverTPSlicesIterator first, OverTPSlicesIterator last)
	{
		return m_Collection.erase(first, last);
	}

	/// inserts a toolpath section at the end of the sequence
	///
	/// if there is no slice available in the sequence then a default one is created
	///  @param section the section to be added
	void PushBack(TPSlice::TPSectionPtr section)
	{
		AssureAtLeastOneSlice();
		(*(--m_Collection.end()))->PushBack(section);
	};

	/// It tests that 2 passes have the same structure and equal moves
	const bool operator==(const mwTPPass& toCompare) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSlicesCount() != GetSlicesCount())
			return false;

		ConstOverTPSlicesIterator ToCompareIt(toCompare.GetSlicesBegin());

		ConstOverTPSlicesIterator End(GetSlicesEnd());

		for (ConstOverTPSlicesIterator It = GetSlicesBegin(); It != End; ++It, ++ToCompareIt)
		{
			if ((**It) != (**ToCompareIt))
				return false;
		}

		return true;
	}

	/// It tests 2 passes for inequality
	inline const bool operator!=(const mwTPPass& toCompare) const
	{
		return !((*this) == toCompare);
	};

	///	It tests that 2 passes has the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos
	///		@param toCompare the pass to be compared with.
	///		@param delta given tolerance factor.
	///		@param minCos given minimal cosinus of angle between moves orientations.
	const bool ExactCompareTolerance(const mwTPPass& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSlicesCount() != GetSlicesCount())
			return false;

		ConstOverTPSlicesIterator ToCompareIt(toCompare.GetSlicesBegin());

		ConstOverTPSlicesIterator End(GetSlicesEnd());

		for (ConstOverTPSlicesIterator It = GetSlicesBegin(); It != End; ++It, ++ToCompareIt)
		{
			if (!(*It)->ExactCompareTolerance(**ToCompareIt, delta, minCos))
				return false;
		}

		return true;
	}

	///	It tests that 2 passes have the same structure and equivalent moves
	///
	/// Besides structures it tests that move positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos and adds markers to
	///	moves that don't satisfy these conditions
	///	@param toCompare the pass to be compared with.
	///	@param delta given tolerance factor.
	///	@param minCos given minimal cosine of angle between moves orientations.
	/// @param markersMap merkers' map
	bool ExactCompareToleranceMark(
		const mwTPPass& toCompare, double delta, double minCos, GenericMarkersMap& markersMap) const
	{
		int nbDifferences = 0;
		return ExactCompareToleranceMark(toCompare, delta, minCos, markersMap, 0, nbDifferences);
	}

	bool ExactCompareToleranceMark(
		const mwTPPass& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap,
		const int maxNbDifferences,
		int& nbDifferences) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSlicesCount() != GetSlicesCount())
			return false;

		ConstOverTPSlicesIterator ToCompareIt(toCompare.GetSlicesBegin());
		ConstOverTPSlicesIterator End(GetSlicesEnd());
		bool result = true;

		for (ConstOverTPSlicesIterator It = GetSlicesBegin(); It != End; ++It, ++ToCompareIt)
		{
			if (!(*It)->ExactCompareToleranceMark(
					**ToCompareIt, delta, minCos, markersMap, maxNbDifferences, nbDifferences))
			{
				if (maxNbDifferences > 0 && nbDifferences >= maxNbDifferences)
				{
					return false;
				}
				result = false;
			}
		}

		return result;
	}

	/// Deep-copy a given pass into this object
	///
	///	@param toCopy is input pass which will  be deep-copied in this object
	void DeepCopy(const mwTPPass& toCopy)
	{
		// deep copy source slices
		m_Collection.clear();

		for (ConstOverTPSlicesIterator It = toCopy.GetSlicesBegin(); It != toCopy.GetSlicesEnd();
			 ++It)
		{
			TPSlicePtr slicePtr(new TPSlice());
			slicePtr->DeepCopy(**It);
			m_Collection.push_back(slicePtr);
		}
	}

protected:
	/// assures that there is at least one slice in the pass in order
	///
	/// to have where to add a new move
	virtual void AssureSpace4Move() { AssureAtLeastOneSlice(); };

private:
	/// assures that there is at least one slice in the pass
	///
	/// if there is none a default is added
	void AssureAtLeastOneSlice()
	{
		if (m_Collection.empty())
		{
			m_Collection.push_back(new mwTPSlice());
		}
	}

	const mwTPSection& GetMoveSection(const ConstOverMovesIterator& move) const
	{
		return (*GetContainer(move))->GetMoveSection(GetValue(move));
	}

	/// friend class needed for accesing private member
	friend class misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPPass>>>;
	friend class mwToolPath;
};

inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwTPPass& toDump)
{
	os << _T("class cadcam::mwTPPass\n");
	// public properties from cadcam::mwTPPass class.
	os << _T("GetSlicesCount        = ") << toDump.GetSlicesCount() << _T("\n");
	os << _T("GetMovesCount         = ") << toDump.GetMovesCount() << _T("\n");
	os << _T("IsEmpty               = ") << toDump.IsEmpty() << _T("\n");
	os << _T("Collide               = ") << toDump.Collide() << _T("\n");
	os << _T("CountCollisions       = ") << toDump.CountCollisions() << _T("\n");
	return os;
}
}  // namespace cadcam
#endif  //	MW_MWTPPASS_HPP_
