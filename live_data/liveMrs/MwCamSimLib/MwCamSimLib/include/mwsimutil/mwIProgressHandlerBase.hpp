// (C) 2012-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

/// \file
/// filename:   mwIProgressHandlerBase.hpp
/// purpose:    declaration of mwIProgressHandlerBase class

#ifndef MW_MWIPROGRESSHANDLERBASE_HPP_
#define MW_MWIPROGRESSHANDLERBASE_HPP_
#include "mwDllImpExpDef.hpp"

//! abstract progress handler bar without any UI logic
class MW_5AXUTIL_API mwIProgressHandlerBase
{

public:

	//! true if user has cancelled the process
	virtual bool IsAborted() = 0;

	//! sets the abort flag to cancel the process
	virtual void SetAborted(bool abort)=0;

	//! sets a number of steps (range of progress bar)
	virtual void SetStepCount( unsigned long stepCount ) = 0;

	//! sets a current position
	/** @return time elapsed from previous progess handler update in miliseconds. */
	virtual unsigned long SetPos( unsigned long value ) = 0;

	//! increases position of progress bar for stepCount
	/** @return time elapsed from previous progess handler update in miliseconds. */
	virtual unsigned long StepIt( unsigned long stepCount ) = 0;

	// general reset
	virtual void Reset() = 0;

	virtual ~mwIProgressHandlerBase(void)
	{
	}
};
#endif	//	MW_MWIPROGRESSHANDLERBASE_HPP_
