// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPARSERCOMMAND_HPP_
#define MW_MWPARSERCOMMAND_HPP_

#include "mwAutoPointer.hpp"
#include "mwString.hpp"

namespace misc
{

template <typename T>
class MW_5AXUTIL_API mwParserCommand
{
public:
	typedef typename misc::mwAutoPointer<mwParserCommand<T> > Ptr;

	mwParserCommand()
	{
	}

	virtual ~mwParserCommand()
	{
	}

	virtual void Parse(
		typename T::Ptr& data, const misc::mwstring& word, const unsigned int& linePos) = 0;
};

}  // namespace misc
#endif	//	MW_MWPARSERCOMMAND_HPP_
