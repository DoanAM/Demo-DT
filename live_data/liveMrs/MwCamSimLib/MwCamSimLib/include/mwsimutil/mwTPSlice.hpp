// (C) 2003-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPSLICE_HPP_
#define MW_MWTPSLICE_HPP_

#include "mwAutoPointer.hpp"
#include "mwCollectionOfContainers.hpp"
#include "mwMovesAccessor.hpp"
#include "mwTPContour.hpp"
#include "mwTPLink.hpp"
#include "mwTPSection.hpp"

namespace cadcam
{
class mwTPPass;

/// this class implements a toolpath slice
///
/// A toolpath slice is a list of toolpath sections.
///	Each toolpath sections can be a toolpath contour or a toolpath link.
///	Please use visitor pattern(mwTPSVisitor) to detect which is which.
///	This class can be also saw as a continue list of moves which is actually the result of
///	concatenating all the moves from all sections.
///	If you try to add a move in slice and there is no section available then the class is
///	creating a default one which is a contour.
class MW_5AXUTIL_API mwTPSlice: public mwMovesAccessor<
					 misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSection>>>>
{
public:
	/// rename section
	typedef mwTPSection TPSection;
	/// rename slice pointer
	typedef misc::mwAutoPointer<mwTPSlice> Ptr;
	/// rename section pointer
	typedef misc::mwAutoPointer<TPSection> TPSectionPtr;
	/// rename sections
	typedef std::list<TPSectionPtr> TPSections;
	/// rename sections iterator
	typedef TPSections::iterator OverTPSectionsIterator;
	/// rename sections const iterator
	typedef TPSections::const_iterator ConstOverTPSectionsIterator;

	/// return a bidirectional iterator to the first section
	///
	/// return a bidirectional iterator that points at the first section
	///	available (or just beyond the end of the sequence if there is no section).
	OverTPSectionsIterator GetSectionsBegin() { return m_Collection.begin(); };

	/// const version of GetSectionsBegin()
	ConstOverTPSectionsIterator GetSectionsBegin() const { return m_Collection.begin(); };

	/// return a bidirectional iterator that points just beyond the end of the sections.
	OverTPSectionsIterator GetSectionsEnd() { return m_Collection.end(); };

	/// const version of GetSectionsEnd()
	ConstOverTPSectionsIterator GetSectionsEnd() const { return m_Collection.end(); };

	/// return how many sections are in in the sequence
	unsigned int GetSectionsCount() const { return (unsigned int)m_Collection.size(); };

	/// return last element of Slice
	misc::mwAutoPointer<cadcam::mwTPSection>& GetBack() { return m_Collection.back(); }


	/// inserts a section at the end of the sequence
	void PushBack(TPSectionPtr section) { m_Collection.push_back(section); };

	/// inserts a section at the begin of the sequence
	void PushFront(TPSectionPtr section) { m_Collection.push_front(section); };

	/// inserts a section just before specified position
	OverTPSectionsIterator Insert(OverTPSectionsIterator& insertionPoint, TPSectionPtr section)
	{
		return m_Collection.insert(insertionPoint, section);
	};

	/// erases all sections from sequence
	void Clear() { m_Collection.clear(); };

	/// removes the sections from the sequence in the range [first, last)
	OverTPSectionsIterator EraseSections(OverTPSectionsIterator first, OverTPSectionsIterator last)
	{
		return m_Collection.erase(first, last);
	}

	/// It tests that 2 slices have the same structure and equal moves
	const bool operator==(const mwTPSlice& toCompare) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsCount() != GetSectionsCount())
			return false;

		ConstOverTPSectionsIterator ToCompareIt(toCompare.GetSectionsBegin());

		ConstOverTPSectionsIterator End(GetSectionsEnd());

		for (ConstOverTPSectionsIterator It = GetSectionsBegin(); It != End; ++It, ++ToCompareIt)
		{
			if ((**It) != (**ToCompareIt))
				return false;
		}

		return true;
	}

	// It tests 2 slices for inequality
	inline const bool operator!=(const mwTPSlice& toCompare) const
	{
		return !((*this) == toCompare);
	};

	///	It tests that 2 slices have the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos
	///		@param toCompare the slice to be compared with.
	///		@param delta given tolerance factor.
	///		@param minCos given minimal cosinus of angle between moves orientations.
	const bool ExactCompareTolerance(const mwTPSlice& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsCount() != GetSectionsCount())
			return false;

		ConstOverTPSectionsIterator ToCompareIt(toCompare.GetSectionsBegin());

		ConstOverTPSectionsIterator End(GetSectionsEnd());

		for (ConstOverTPSectionsIterator It = GetSectionsBegin(); It != End; ++It, ++ToCompareIt)
		{
			if (!(*It)->ExactCompareTolerance(**ToCompareIt, delta, minCos))
				return false;
		}

		return true;
	}

	///	It tests that 2 slices have the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos and marks moves that
	///	don't satisfy these conditions
	///	@param toCompare the slice to be compared with.
	///	@param delta given tolerance factor.
	///	@param minCos given minimal cosine of angle between moves orientations.
	/// @param markersMap merkers' map
	bool ExactCompareToleranceMark(
		const mwTPSlice& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap) const
	{
		int nbDifferences = 0;
		return ExactCompareToleranceMark(toCompare, delta, minCos, markersMap, 0, nbDifferences);
	}

	bool ExactCompareToleranceMark(
		const mwTPSlice& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap,
		const int maxNbDifferences,
		int& nbDifferences) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsCount() != GetSectionsCount())
			return false;

		ConstOverTPSectionsIterator ToCompareIt(toCompare.GetSectionsBegin());
		ConstOverTPSectionsIterator End(GetSectionsEnd());
		bool result = true;

		for (ConstOverTPSectionsIterator It = GetSectionsBegin(); It != End; ++It, ++ToCompareIt)
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

	/// Deep-copy a given slice into this object
	///
	///	@param toCopy is input slice which will  be deep-copied in this object
	void DeepCopy(const mwTPSlice& toCopy)
	{
		// deep copy source tp sections
		m_Collection.clear();

		for (ConstOverTPSectionsIterator It = toCopy.GetSectionsBegin();
			 It != toCopy.GetSectionsEnd();
			 ++It)
		{
			TPSectionPtr sectionPtr;

			mwTpSectionDeepCopy sectionDeepCopy(sectionPtr);
			(*It)->AcceptVisitor(sectionDeepCopy);

			m_Collection.push_back(sectionPtr);
		}
	}

protected:
	/// assures that there is at least one section in the slice in order
	///
	/// to have where to add a new move
	virtual void AssureSpace4Move() { AssureAtLeastOneSection(); };

private:
	const mwTPSection& GetMoveSection(const ConstOverMovesIterator& move) const
	{
		return **GetContainer(move);
	}

	/// assures that there is at least one section in the slice
	///
	/// if there is none a default one as contour is added
	void AssureAtLeastOneSection()
	{
		if (m_Collection.empty())
		{
			m_Collection.push_back(new mwTPContour());
		}
	}

	class mwTpSectionDeepCopy: public mwTPSVisitor
	{
	public:
		mwTpSectionDeepCopy(TPSectionPtr& retDeepCopy): m_retDeepCopy(retDeepCopy)

		{
			m_retDeepCopy = NULL;
		}
		virtual void Visit(const mwTPSection& /*tps*/)
		{
			throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);
		}
		virtual void Visit(const mwTPContour& contour)
		{
			mwTPContour::Ptr contPtr = new mwTPContour();
			contPtr->DeepCopy(contour);

			m_retDeepCopy = contPtr;
		}
		virtual void Visit(const mwTPLink& link)
		{
			mwTPLink::Ptr linkPtr = new mwTPLink(link.GetLinkType());
			linkPtr->DeepCopy(link);

			m_retDeepCopy = linkPtr;
		}

	private:
		TPSectionPtr& m_retDeepCopy;  // will return deep copy of the visited object
		mwTpSectionDeepCopy& operator=(mwTpSectionDeepCopy&);  // = delete
	};

	friend class misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSlice>>>;
	friend class mwTPPass;
	friend class mwToolPath;
};

inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwTPSlice& toDump)
{
	os << _T("class cadcam::mwTPSlice\n");
	// public properties from cadcam::mwTPSlice class.
	os << _T("GetSectionsCount      = ") << toDump.GetSectionsCount() << _T("\n");
	os << _T("GetMovesCount         = ") << toDump.GetMovesCount() << _T("\n");
	os << _T("IsEmpty               = ") << toDump.IsEmpty() << _T("\n");
	os << _T("Collide               = ") << toDump.Collide() << _T("\n");
	os << _T("CountCollisions       = ") << toDump.CountCollisions() << _T("\n");
	return os;
}
}  // namespace cadcam
#endif  //	MW_MWTPSLICE_HPP_
