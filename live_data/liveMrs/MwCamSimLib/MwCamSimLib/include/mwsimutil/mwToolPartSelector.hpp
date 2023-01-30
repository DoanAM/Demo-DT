// (C) 2009-2015 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPARTSELECTOR_HPP_
#define MW_MWTOOLPARTSELECTOR_HPP_
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwToolPartSelector
{
public:
	mwToolPartSelector(
		bool hasCuttingPart = true,
		bool hasNonCuttinPart = true,
		bool hasArborPart = true,
		bool hasHolderPart = true)
		: m_hasCuttingPart(hasCuttingPart),
		  m_hasNonCuttingPart(hasNonCuttinPart),
		  m_hasArborPart(hasArborPart),
		  m_hasHolderPart(hasHolderPart)
	{
	}

	void SetCuttingPart(bool bCuttingPart) { m_hasCuttingPart = bCuttingPart; }
	bool IsCuttingPart() const { return m_hasCuttingPart; }

	void SetNonCuttingPart(bool bNonCuttingPart) { m_hasNonCuttingPart = bNonCuttingPart; }
	bool IsNonCuttingPart() const { return m_hasNonCuttingPart; }

	void SetArborPart(bool bArbor) { m_hasArborPart = bArbor; }
	bool IsArborPart() const { return m_hasArborPart; }

	void SetHolderPart(bool bHolder) { m_hasHolderPart = bHolder; }
	bool IsHolderPart() const { return m_hasHolderPart; }
	bool NoneSelected() const
	{
		return !(m_hasCuttingPart || m_hasNonCuttingPart || m_hasArborPart || m_hasHolderPart);
	}

	mwToolPartSelector GetMergeValuesUsingLogicalOr(const mwToolPartSelector& other) const
	{
		return mwToolPartSelector(
			m_hasCuttingPart || other.m_hasCuttingPart,
			m_hasNonCuttingPart || other.m_hasNonCuttingPart,
			m_hasArborPart || other.m_hasArborPart,
			m_hasHolderPart || other.m_hasHolderPart);
	}

private:
	bool m_hasCuttingPart;
	bool m_hasNonCuttingPart;
	bool m_hasArborPart;
	bool m_hasHolderPart;
};

}  // namespace cadcam
#endif  //	MW_MWTOOLPARTSELECTOR_HPP_
