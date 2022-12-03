// (C) 2011-2017 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWCRCSEGMENT_HPP_
#define MW_MWCRCSEGMENT_HPP_
#include "mwCrcMarker.hpp"

class MW_5AXUTIL_API mwCrcSegment
{
public:
	mwCrcSegment()
	{
		m_compensation = 0.0;
		m_operationNumber = 0;
		m_start = mwCrcMarker();
		m_end = mwCrcMarker();
	}
	mwCrcSegment(
		const double compensation,
		const long operationNumber,
		const mwCrcMarker& start,
		const mwCrcMarker& end)
			: m_compensation(compensation)
			, m_operationNumber(operationNumber)
			, m_start(start)
			, m_end(end)
	{
	}
	bool operator==(const mwCrcSegment& other) const
	{
		return (m_compensation == other.m_compensation &&
			m_operationNumber == other.m_operationNumber &&
			m_start == other.m_start &&
			m_end == other.m_end);
	}
	const double GetCompensation() const
	{
		return m_compensation;
	}
	void SetCompensation(const double compensation)
	{
		m_compensation = compensation;
	}
	const long GetOperationNumber() const
	{
		return m_operationNumber;
	}
	void SetOperationNumber(const long operationNumber)
	{
		m_operationNumber = operationNumber;
	}
	const mwCrcMarker& GetStartMarker() const
	{
		return m_start;
	}
	void SetStartMarker(const mwCrcMarker& start)
	{
		m_start = start;
	}
	const mwCrcMarker& GetEndMarker() const
	{
		return m_end;
	}
	void SetEndMarker(const mwCrcMarker& end)
	{
		m_end = end;
	}
private:
	//!compensation value
	double m_compensation;

	//!number of the operation
	long m_operationNumber;

	//!position in the toolpath from where m_compensation applies
	mwCrcMarker m_start;

	//!position in the toolpath from where m_compensation no longer applies
	mwCrcMarker m_end;
};
#endif	//	MW_MWCRCSEGMENT_HPP_
