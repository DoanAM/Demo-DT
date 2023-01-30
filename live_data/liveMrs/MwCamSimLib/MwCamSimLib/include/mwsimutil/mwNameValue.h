// (C) 2007-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWNAMEVALUE_H_
#define MW_MWNAMEVALUE_H_

#include "mwString.hpp"

struct mwPresetNames
{
	misc::mwstring m_fileName;
	misc::mwstring m_showName;

	const mwPresetNames& operator=(const mwPresetNames& tc)
	{
		m_fileName = tc.m_fileName;
		m_showName = tc.m_showName;
		return *this;
	}
};
#endif	//	MW_MWNAMEVALUE_H_
