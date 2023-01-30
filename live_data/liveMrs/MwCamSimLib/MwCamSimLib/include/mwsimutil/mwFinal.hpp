// (C) 2007-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFINAL_HPP_
#define MW_MWFINAL_HPP_

#include "mwDeprecated.hpp"

namespace misc
{
	class MW_DEPRECATED("Deprecated since 2021.04. Do not use it.") mwFinalBase
	{
	protected:
		mwFinalBase(){}
	};

	class MW_DEPRECATED("Deprecated since 2021.04. Do not use it.") mwFinal :
		protected virtual mwFinalBase 
	{
	public:
		mwFinal(){}
	private:
		//! Private copy constructor to make clients define their own
		mwFinal(const mwFinal &){};
		//! Private assignment operator to make clients define their own
		mwFinal& operator=(const mwFinal &)
		{
			return *this;
		}
	}; 

}
#endif	//	MW_MWFINAL_HPP_
