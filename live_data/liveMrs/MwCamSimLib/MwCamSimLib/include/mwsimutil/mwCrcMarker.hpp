// (C) 2011-2017 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWCRCMARKER_HPP_
#define MW_MWCRCMARKER_HPP_
#include "mwDllImpExpDef.hpp"

//! Defines a position inside the toolpath structure.
/*! Defines a position inside the toolpath structure by specifying
	the pass, slice, section, section fit and move number. There is also
	a flag that signals if a section fit is a helix fit.
	(usually there is not much point in counting moves inside a helix fit)
*/
class MW_5AXUTIL_API mwCrcMarker
{
public:
	mwCrcMarker()
	{
		m_passNumber = 0;
		m_sliceNumber = 0;
		m_sectionNumber = 0;
		m_sectionFitNumber = 0;
		m_moveNumber = 0;
		m_referenceMoveIndex = 0;
		m_isHelixFit = false;
	}
	mwCrcMarker(
		const size_t passNumber,
		const size_t sliceNumber,
		const size_t sectionNumber,
		const size_t sectionFitNumber,
		const size_t moveNumber,
		const size_t referenceMoveIndex,
		const bool isHelixFit)
		: m_passNumber(passNumber)
		, m_sliceNumber(sliceNumber)
		, m_sectionNumber(sectionNumber)
		, m_sectionFitNumber(sectionFitNumber)
		, m_moveNumber(moveNumber)
		, m_referenceMoveIndex(referenceMoveIndex)
		, m_isHelixFit(isHelixFit)
	{
	}

	mwCrcMarker(const mwCrcMarker &toCopy)
	{
		m_passNumber = toCopy.GetPassNumber();
		m_sliceNumber = toCopy.GetSliceNumber();
		m_sectionNumber = toCopy.GetSectionNumber();
		m_sectionFitNumber = toCopy.GetSectionFitNumber();
		m_moveNumber = toCopy.GetMoveNumber();
		m_referenceMoveIndex = toCopy.GetReferenceMoveIndex();
		m_isHelixFit = toCopy.GetIsHelixFit();
	}

	bool operator==(const mwCrcMarker& other) const
	{
		return (m_passNumber == other.m_passNumber &&
			m_sliceNumber == other.m_sliceNumber &&
			m_sectionNumber == other.m_sectionNumber &&
			m_sectionFitNumber == other.m_sectionFitNumber &&
			m_moveNumber == other.m_moveNumber &&
			m_referenceMoveIndex == other.m_referenceMoveIndex &&
			m_isHelixFit == other.m_isHelixFit);
	}

	const mwCrcMarker& operator=(const mwCrcMarker& toCopy)
	{
		m_passNumber = toCopy.GetPassNumber();
		m_sliceNumber = toCopy.GetSliceNumber();
		m_sectionNumber = toCopy.GetSectionNumber();
		m_sectionFitNumber = toCopy.GetSectionFitNumber();
		m_moveNumber = toCopy.GetMoveNumber();
		m_referenceMoveIndex = toCopy.GetReferenceMoveIndex();
		m_isHelixFit = toCopy.GetIsHelixFit();

		return *this;
	}

	const size_t GetPassNumber() const
	{
		return m_passNumber;
	}
	void SetPassNumber(const size_t passNumber)
	{
		m_passNumber = passNumber;
	}

	const size_t GetSliceNumber() const
	{
		return m_sliceNumber;
	}
	void SetSliceNumber(const size_t sliceNumber)
	{
		m_sliceNumber = sliceNumber;
	}

	const size_t GetSectionNumber() const
	{
		return m_sectionNumber;
	}
	void SetSectionNumber(const size_t sectionNumber)
	{
		m_sectionNumber = sectionNumber;
	}

	const size_t GetSectionFitNumber() const
	{
		return m_sectionFitNumber;
	}
	void SetSectionFitNumber(const size_t sectionFitNumber)
	{
		m_sectionFitNumber = sectionFitNumber;
	}

	const size_t GetMoveNumber() const
	{
		return m_moveNumber;
	}
	void SetMoveNumber(const size_t moveNumber)
	{
		m_moveNumber = moveNumber;
	}

	const size_t GetReferenceMoveIndex() const
	{
		return m_referenceMoveIndex;
	}
	void SetReferenceMoveIndex(const size_t referenceMoveIndex)
	{
		m_referenceMoveIndex = referenceMoveIndex;
	}

	const bool GetIsHelixFit() const
	{
		return m_isHelixFit;
	}
	void SetIsHelixFit(const bool isHelixFit)
	{
		m_isHelixFit = isHelixFit;
	}

protected:
	size_t m_passNumber;
	size_t m_sliceNumber;
	size_t m_sectionNumber;
	size_t m_sectionFitNumber;
	size_t m_moveNumber;  // move number in current section fit
	size_t m_referenceMoveIndex;  // move number in all toolpath, start at 0, reference to mwCNCMoves
	bool m_isHelixFit;
};
#endif	//	MW_MWCRCMARKER_HPP_
