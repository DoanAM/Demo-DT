// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPSECTION_HPP_
#define MW_MWTPSECTION_HPP_
#include "mwAutoPointer.hpp"
#include "mwCollectionOfContainers.hpp"
#include "mwMovesAccessor.hpp"
#include "mwTPHelixFit.hpp"
#include "mwTPPolyLineFit.hpp"
#include "mwTPSectionFit.hpp"
#include "mwTPUtils.hpp"


namespace cadcam
{
class mwTPSection;
class mwTPContour;
class mwTPLink;

/// Base class for any visitor of classes derived from mwTPSection.
class MW_5AXUTIL_API mwTPSVisitor
{
public:
	virtual ~mwTPSVisitor() MW_DEFAULT_DESTRUCTOR_IMPL
	/// Allows you to visit a tool path section.
	///
	///	@param tps is the section to be visited.
	virtual void Visit(const mwTPSection& tps) = 0;
	/// Allows you to visit a tool path contour.
	///
	///	@param contour si the the contour to be visited.
	virtual void Visit(const mwTPContour& contour) = 0;
	/// Allows you to visit a tool path link.
	///
	///	@param link is the link to be visited.
	virtual void Visit(const mwTPLink& link) = 0;
};

/// @class mwTPSection
///	Base class for any toolpath section.
/// This class implements a list of moves.
class MW_5AXUTIL_API mwTPSection
	: public mwMovesAccessor<
		  misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSectionFit>>>>,
	  public mwTPAttributes
{
public:
	typedef misc::mwAutoPointer<mwTPSection> Ptr;
	/// Rename the section fit.
	typedef mwTPSectionFit TPSectionFit;
	/// Rename the section fit pointer.
	typedef misc::mwAutoPointer<TPSectionFit> TPSectionFitPtr;
	/// Rename the sections fit.
	typedef std::list<TPSectionFitPtr> TPSectionsFit;
	/// Rename the sections fit iterator.
	typedef TPSectionsFit::iterator OverTPSectionsFitIterator;
	/// Rename the sections fit const iterator.
	typedef TPSectionsFit::const_iterator ConstOverTPSectionsFitIterator;

	mwTPSection(const mwTPAttributes& attributes = mwTPAttributes())
	{
		CopyAttributesFrom(attributes);
	}
	/// Allows you to visit this class based on a Visitor pattern.
	virtual void AcceptVisitor(mwTPSVisitor& visitor) const = 0;
	/// This function returns the last element of section.
	misc::mwAutoPointer<cadcam::mwTPSectionFit>& GetBack() { return m_Collection.back(); }
	/// Returns a bidirectional iterator that points to the first section available
	/// (or the next after the last in the sequence if there are no fits).
	OverTPSectionsFitIterator GetSectionsFitBegin() { return m_Collection.begin(); }
	ConstOverTPSectionsFitIterator GetSectionsFitBegin() const { return m_Collection.begin(); }
	/// Returns a bidirectional iterator that points to the next element after the last fit
	OverTPSectionsFitIterator GetSectionsFitEnd() { return m_Collection.end(); }
	ConstOverTPSectionsFitIterator GetSectionsFitEnd() const { return m_Collection.end(); }
	unsigned int GetSectionsFitCount() const { return (unsigned int)m_Collection.size(); }

	/// Inserts a section at the end of the sequence.
	void PushBack(TPSectionFitPtr section) { m_Collection.push_back(section); }

	/// Inserts a section at the beginning of the sequence.
	void PushFront(TPSectionFitPtr section) { m_Collection.push_front(section); }
	/// Inserts a section immediately before the specified position.
	OverTPSectionsFitIterator Insert(
		const OverTPSectionsFitIterator& insertionPoint, TPSectionFitPtr section)
	{
		return m_Collection.insert(insertionPoint, section);
	}
	/// Erases all sections from the sequence.
	void Clear() { m_Collection.clear(); }
	/// Removes the given range of sections (first...last) from the sequence.
	OverTPSectionsFitIterator EraseSections(
		OverTPSectionsFitIterator first, OverTPSectionsFitIterator last)
	{
		return m_Collection.erase(first, last);
	}
	/// Checks whether 2 sections are the same
	///
	/// @param toCompare section to compare against
	///	@returns <b>true</b> if the sections equal, false otherwise
	const bool operator==(const mwTPSection& toCompare) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsFitCount() != GetSectionsFitCount())
			return false;

		if (this->GetAttributes() != toCompare.GetAttributes())
			return false;

		const mwTPUtils::SectionParams first = mwTPUtils::GetSectionParameters(*this);
		const mwTPUtils::SectionParams second = mwTPUtils::GetSectionParameters(toCompare);

		if (first.isLink != second.isLink || first.linkType != second.linkType)
			return false;

		ConstOverTPSectionsFitIterator ToCompareIt(toCompare.GetSectionsFitBegin());

		ConstOverTPSectionsFitIterator End(GetSectionsFitEnd());

		for (ConstOverTPSectionsFitIterator It = GetSectionsFitBegin(); It != End;
			 ++It, ++ToCompareIt)
		{
			mwSectionFitInfoGetter infoGetterFirst(true);
			(**It).AcceptVisitor(infoGetterFirst);

			mwSectionFitInfoGetter infoGetterSecond(true);
			(**ToCompareIt).AcceptVisitor(infoGetterSecond);

			if (infoGetterFirst.GetType() != infoGetterSecond.GetType())
				return false;

			switch (infoGetterFirst.GetType())
			{
			case mwSectionFitInfoGetter::TP_POLYLINE:
			{
				if (infoGetterFirst.GetPolyline() != infoGetterSecond.GetPolyline())
					return false;
				break;
			}
			case mwSectionFitInfoGetter::TP_HELIX:
			{
				if (infoGetterFirst.GetHelix() != infoGetterSecond.GetHelix())
					return false;
				break;
			}
			default: throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);
			}
		}
		return true;
	}

	/// Checks whether 2 sections are different
	///
	/// @param toCompare section to compare against
	///	@returns <b>true</b> if the sections are different, false otherwise
	const bool operator!=(const mwTPSection& toCompare) const { return !((*this) == toCompare); }

	///	Checks whether 2 slices have the same structure and equivalent moves.
	///
	/// As well as comparing the structures, it tests whether the distances between the positions of
	/// the moves are within tolerance and whether the difference between the tool orientation
	/// vectors is not more than minCos.
	///		@param toCompare is the slice that will be compared with the current slice.
	///		@param delta is the tolerance.
	///		@param minCos is the minimal cosine of the angle between the moves.
	const bool ExactCompareTolerance(
		const mwTPSection& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsFitCount() != GetSectionsFitCount())
			return false;

		ConstOverTPSectionsFitIterator ToCompareIt(toCompare.GetSectionsFitBegin());
		ConstOverTPSectionsFitIterator End(GetSectionsFitEnd());

		for (ConstOverTPSectionsFitIterator It = GetSectionsFitBegin(); It != End;
			 ++It, ++ToCompareIt)
		{
			mwSectionFitInfoGetter infoGetterFirst(true);
			(**It).AcceptVisitor(infoGetterFirst);

			mwSectionFitInfoGetter infoGetterSecond(true);
			(**ToCompareIt).AcceptVisitor(infoGetterSecond);
			if (infoGetterFirst.GetType() != infoGetterSecond.GetType())
				return false;

			switch (infoGetterFirst.GetType())
			{
			case mwSectionFitInfoGetter::TP_POLYLINE:
			{
				if (!infoGetterFirst.GetPolyline().ExactCompareTolerance(
						infoGetterSecond.GetPolyline(), delta, minCos))
					return false;
			}
			break;

			case mwSectionFitInfoGetter::TP_HELIX:
			{
				if (!infoGetterFirst.GetHelix().ExactCompareTolerance(
						infoGetterSecond.GetHelix(), delta, minCos))
					return false;
			}
			break;

			default: throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);
			}
		}

		return true;
	}
	///	Checks whether 2 slices have the same structure and equivalent moves.
	///
	/// As well as comparing the structures, it also checks whether the distances between the
	/// positions of the moves are within tolerance and whether the difference between the tool
	/// orientation vectors is not more than minCos. It marks moves that
	///	do not satisfy these conditions.
	///	@param toCompare is the slice that will be compared with the current slice.
	///	@param delta is the tolerance.
	///	@param minCos is the minimal cosine of the angle between moves.
	/// @param markersMap merkers' map
	bool ExactCompareToleranceMark(
		const mwTPSection& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap) const
	{
		int nbDifferences = 0;
		return ExactCompareToleranceMark(toCompare, delta, minCos, markersMap, 0, nbDifferences);
	}

	bool ExactCompareToleranceMark(
		const mwTPSection& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap,
		const int maxNbDifferences,
		int& nbDifferences) const
	{
		if (&toCompare == this)
			return true;

		if (toCompare.GetSectionsFitCount() != GetSectionsFitCount())
			return false;

		ConstOverTPSectionsFitIterator ToCompareIt(toCompare.GetSectionsFitBegin());
		ConstOverTPSectionsFitIterator End(GetSectionsFitEnd());
		bool result = true;

		for (ConstOverTPSectionsFitIterator It = GetSectionsFitBegin(); It != End;
			 ++It, ++ToCompareIt)
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

	static const bool IsAPolyLineFit(const mwTPSectionFit& sectionFit)
	{
		mwSectionFitInfoGetter infoFitGetter(false);
		sectionFit.AcceptVisitor(infoFitGetter);
		return infoFitGetter.GetType() == mwSectionFitInfoGetter::TP_POLYLINE;
	}

	/// Deep-copy a given tp section into this object
	/// @param toCopy is input tp section to be deep-copied into this object.
	void DeepCopy(const mwTPSection& toCopy)
	{
		// Deep copy the source tp section fits.
		m_Collection.clear();

		for (ConstOverTPSectionsFitIterator It = toCopy.GetSectionsFitBegin();
			 It != toCopy.GetSectionsFitEnd();
			 ++It)
		{
			TPSectionFitPtr sectionFitPtr;

			mwTpSectionFitDeepCopy sectionFitDeepCopy(sectionFitPtr);
			(*It)->AcceptVisitor(sectionFitDeepCopy);

			m_Collection.push_back(sectionFitPtr);
		}
		// Deep copy the attributes.
		mwTPAttributes::DeepCopy(toCopy);
	}

protected:
	virtual void AssureSpace4Move() { AssureAtLeastOneSectionFit(); }

private:
	class mwSectionFitInfoGetter: public mwTPSFitVisitor
	{
	public:
		enum Type
		{
			TP_UNKNOWN,
			TP_POLYLINE,
			TP_HELIX
		};
		mwSectionFitInfoGetter(const bool isDeepCopyable)
			: m_type(TP_UNKNOWN),
			  m_polyline(MW_NULL),
			  m_helix(MW_NULL),
			  m_isDeepCopyable(isDeepCopyable)
		{
		}

		virtual void Visit(const cadcam::mwTPSectionFit&)
		{
			throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);
		}

		virtual void Visit(const cadcam::mwTPPolyLineFit& src)
		{
			m_type = TP_POLYLINE;

			if (m_isDeepCopyable)
			{
				m_polyline = new mwTPPolyLineFit();
				m_polyline->DeepCopy(src);
			}
		}

		virtual void Visit(const cadcam::mwTPHelixFit& src)
		{
			m_type = TP_HELIX;

			if (m_isDeepCopyable)
			{
				m_helix = new mwTPHelixFit(src);
				m_helix->DeepCopy(src);
			}
		}

		const Type GetType() const
		{
			if (m_type == TP_UNKNOWN)
				throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);

			return m_type;
		}

		const mwTPPolyLineFit& GetPolyline() const
		{
			if (m_isDeepCopyable && m_polyline.IsNull())
				MW_EXCEPTION("Polyline is not initialized!");

			return *m_polyline;
		}

		const mwTPHelixFit& GetHelix() const
		{
			if (m_isDeepCopyable && m_helix.IsNull())
				MW_EXCEPTION("Helix is not initialized!");

			return *m_helix;
		}

	private:
		mwSectionFitInfoGetter& operator=(const mwSectionFitInfoGetter&);  // = delete
		Type m_type;

		mwTPPolyLineFit::Ptr m_polyline;
		mwTPHelixFit::Ptr m_helix;

		const bool m_isDeepCopyable;
	};
	/// Assures that there is at least one section in the slice. If there is no section, a default
	/// section is added as a contour.
	void AssureAtLeastOneSectionFit()
	{
		if (m_Collection.empty())
		{
			m_Collection.push_back(new mwTPPolyLineFit());
		}
		else
		{
			bool lastSectionIsHelixFit = !IsAPolyLineFit(*m_Collection.back());
			if (lastSectionIsHelixFit)
			{
				m_Collection.push_back(new mwTPPolyLineFit());
			}
		}
	}

	/// @class mwTpSectionFitDeepCopy
	/// Helper class to perform section fit deep copy
	class mwTpSectionFitDeepCopy: public mwTPSFitVisitor
	{
	public:
		mwTpSectionFitDeepCopy(TPSectionFitPtr& retDeepCopy): m_retDeepCopy(retDeepCopy)

		{
			m_retDeepCopy = NULL;
		}
		virtual void Visit(const cadcam::mwTPSectionFit&)
		{
			throw mwcadcamException(mwcadcamException::UNKNOWN_TOOLPATH_SECTION_TYPE);
		}
		virtual void Visit(const cadcam::mwTPPolyLineFit& polyFit)
		{
			mwTPPolyLineFit::Ptr polyFitPtr = new mwTPPolyLineFit();
			polyFitPtr->DeepCopy(polyFit);

			m_retDeepCopy = polyFitPtr;
		}
		virtual void Visit(const cadcam::mwTPHelixFit& helixFit)
		{
			mwTPHelixFit::Ptr helixFitPtr = new mwTPHelixFit(helixFit);
			helixFitPtr->DeepCopy(helixFit);

			m_retDeepCopy = helixFitPtr;
		}

	private:
		TPSectionFitPtr& m_retDeepCopy;  // Returns a deep copy of the visited object
		mwTpSectionFitDeepCopy& operator=(mwTpSectionFitDeepCopy&);  // = delete
	};
	friend class misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSection>>>;
	friend class mwTPSlice;
	friend class mwTPSectionFit;
};

inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwTPSection& toDump)
{
	os << _T("class cadcam::mwTPSection\n");
	// public properties from cadcam::mwTPSection class.
	os << _T("GetMovesCount         = ") << toDump.GetMovesCount() << _T("\n");
	os << _T("IsEmpty               = ") << toDump.IsEmpty() << _T("\n");
	os << _T("Collide               = ") << toDump.Collide() << _T("\n");
	os << _T("CountCollisions       = ") << toDump.CountCollisions() << _T("\n");
	return os;
}
}  // namespace cadcam
#endif  //	MW_MWTPSECTION_HPP_
