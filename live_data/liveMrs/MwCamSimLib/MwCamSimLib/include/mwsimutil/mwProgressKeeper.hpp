// (C) 2014 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWPROGRESSKEEPER_HPP_
#define MW_MWPROGRESSKEEPER_HPP_
#include "mwIProgressHandler.hpp"

//! keeps progress data, useful for asynchronous display of the progress
class MW_5AXUTIL_API mwProgressKeeper : public mwIProgressDialogHandler
{
public:
	mwProgressKeeper()
		:m_shouldBeDisplayed(false),m_isAborted(false),m_stepCount(100),m_pos(0){};
	virtual void SetInfo(const misc::mwstring &info){m_info = info;}
	virtual void Show(){m_shouldBeDisplayed = true;}
	virtual void Close(){m_shouldBeDisplayed = false;}
	virtual bool IsAborted(){return m_isAborted;}
	virtual void SetAborted(bool abort)
	{
		m_isAborted = abort; 
		if (m_isAborted)
		{
			m_shouldBeDisplayed=false;
		}
	}
	virtual void SetStepCount(unsigned long stepCount){m_stepCount = stepCount;}
	virtual unsigned long SetPos(unsigned long value){m_pos = value; return 0;}
	virtual unsigned long StepIt(unsigned long stepCount){m_pos += stepCount; return 0;}
	virtual void Reset(){m_pos=0;m_isAborted=false;}

	inline const misc::mwstring& GetInfo() const 
	{ return m_info; }
	inline const bool& ShouldBeDisplayed() const 
	{ return m_shouldBeDisplayed; }
	inline const unsigned long& GetStepCount() const 
	{ return m_stepCount; }
	inline const unsigned long& GetPos() const 
	{ return m_pos; }
protected:
	misc::mwstring m_info;
	bool m_shouldBeDisplayed;
	bool m_isAborted;
	unsigned long m_stepCount;
	unsigned long m_pos;
private:
	virtual void SetCaption(const misc::mwstring &/*caption*/)
	{//do nothing this method will be removed since the object should derive from mwIDisplayableProgressHandler
	}
	virtual void SetStyles(unsigned int /*styles*/)
	{//do nothing this method will be removed since the object should derive from mwIDisplayableProgressHandler
	}
	virtual void AddStyles(unsigned int /*styles*/)
	{//do nothing this method will be removed since the object should derive from mwIDisplayableProgressHandler
	}
};
#endif	//	MW_MWPROGRESSKEEPER_HPP_
