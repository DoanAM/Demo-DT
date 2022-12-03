// (C) 2008-2015 by ModuleWorks GmbH
// Owner: 5Axis Core

/// \file
///        Implementation of
/// mwIProgressHandler

#ifndef MW_MWIPROGRESSHANDLER_HPP_
#define MW_MWIPROGRESSHANDLER_HPP_
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwIProgressHandlerBase.hpp"

//! abstract progress bar
class MW_5AXUTIL_API mwIDisplayableProgressHandler : public mwIProgressHandlerBase
{

public:
	//! sets a comment
	virtual void SetInfo( const misc::mwstring &info ) = 0;

	//! show control/dialog
	virtual void Show() = 0;

	//! hide/close control/dialog
	virtual void Close() = 0;

	virtual ~mwIDisplayableProgressHandler(void)
	{
	}
};

class MW_5AXUTIL_API mwIProgressDialogHandler : public mwIDisplayableProgressHandler
{

public:
	//! sets a title
	virtual void SetCaption( const misc::mwstring &caption ) = 0;

	//! style flag values
	enum Styles
	{
		//! regular progress bar dialog
		STYLE_NONE  = 0,
		//! no abort feature
		STYLE_NO_ABORT = 1,
		//! don't show progress bar
		STYLE_NO_PROGRESS = 2,
		//! don't show time
		STYLE_NO_TIME = 4,
		//! don't estimate time
		STYLE_NO_ESTIMATE = 8,
		//! don't put progress window on top
		STYLE_NOT_ON_TOP = 16,

		//! show only message and elapsed time styles combination
		STYLE_ONLY_INFO = STYLE_NO_ABORT | STYLE_NO_PROGRESS | STYLE_NO_TIME | STYLE_NO_ESTIMATE,
	};

	//! setup specific styles
	virtual void SetStyles(unsigned int styles) = 0;

	//! add styles, preserving existing ones
	virtual void AddStyles(unsigned int styles) = 0;

	virtual ~mwIProgressDialogHandler(void)
	{
	}
};


/* Pragma Deprecated: Instead of mwIProgressHandler please use mwIProgressDialogHandler,
  or better, one of it's parents from which it is inherited
to better signal what the code is using: basic, displayable, dialog, etc
*/
typedef class mwIProgressDialogHandler mwIProgressHandler;
#pragma deprecated(mwIProgressHandler)


//! abstract process
/*!encapsulate one or more commands,
that are usually taking long enough
to worth to display a progress for
*/
class MW_5AXUTIL_API mwIProgressProcess
{
public:

	virtual int Run(mwIProgressDialogHandler* progress) = 0;

	//provide default implementation since most process are blocking
	virtual bool IsBackgroundProcess ()
	{return false;};

	virtual ~mwIProgressProcess(void)
	{
	}
};

//! abstract runner of specified process
/*!allow customization of the progress handler
and assures all are safe before and after running a process,
ex: no other process is running
*/
class MW_5AXUTIL_API mwIProgressProcessRunner
{
public:

	//! run specified process
	virtual int Execute(mwIProgressProcess* process, mwIProgressDialogHandler* progress) = 0;

	virtual ~mwIProgressProcessRunner(void)
	{
	}
};


//! use progress handler for trivial loops
class MW_5AXUTIL_API mwProgressHandlerSimpleLoop
{

public :

	mwProgressHandlerSimpleLoop(mwIProgressDialogHandler* progressHandler
		, unsigned long count)
		: m_step(0), m_updateCount(1), m_delayedProgressBarUpdate(true), m_progressHandler(progressHandler),m_CurrentPos(0)
	{
		if (progressHandler)
		{
			progressHandler->SetStepCount(count);
			progressHandler->SetPos(0);
		}
	}

	void SetDelayedProgressBarUpdate( bool delayedProgressBarUpdate ) 
	{ 
		m_delayedProgressBarUpdate = delayedProgressBarUpdate; 
	}

	//! @return true if progress has updated
	bool StepIt()
	{
		++m_CurrentPos;
		if (m_progressHandler)
		{
			++m_step;

			if(m_delayedProgressBarUpdate)
			{
				if (m_step % m_updateCount == 0)
				{
					unsigned long time = m_progressHandler->StepIt(m_step);
					m_step = 0;
					const unsigned long minTime = 500;
					const unsigned long normTime = 1000;
					const unsigned long maxTime = 1500;

					if (time < minTime)
					{
						m_updateCount *= 2;
					}
					else if (time < normTime)
					{
						++m_updateCount;
					}
					else if (time < maxTime)
					{
						if (m_updateCount > 1)
						{
							--m_updateCount;
						}
					}
					else
					{
						if (m_updateCount > 1)
						{
							m_updateCount /= 2;
						}
					}

					return true;
				}
			}
			else
			{
				m_progressHandler->StepIt(m_step);
				m_step = 0;  
				return true;
			}
		}

		return false;
	}

	bool IsAborted()
	{
		if(m_progressHandler)
		{
			return m_progressHandler->IsAborted();
		}

		return false;
	}

	void SetPos(unsigned long value)
	{
		if (m_progressHandler)
		{
			for (unsigned long i=m_CurrentPos; i < value; ++i)
			{
				StepIt();//this is delayed update
			}
		}else
		{
			if (value > m_CurrentPos)
			{
				m_CurrentPos = value;
			}
		}
	}


	unsigned int m_step;
	unsigned int m_updateCount;
	unsigned long m_CurrentPos;
	bool m_delayedProgressBarUpdate;
	mwIProgressDialogHandler* m_progressHandler;
};
#endif	//	MW_MWIPROGRESSHANDLER_HPP_
