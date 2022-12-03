// (C) 2010-2014 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWGLRENDERINGCONTEXTPRESERVINGPROGRESSHANDLERDECORATOR_HPP_
#define MW_MWGLRENDERINGCONTEXTPRESERVINGPROGRESSHANDLERDECORATOR_HPP_
#include "mwIProgressHandler.hpp"
#include "mwDllImpExpDef.hpp"

namespace mmedia
{
	//#####################################################################
	class MW_5AXUTIL_API mwGLRenderingContextPreservingProgressHandlerDecorator : public mwIProgressDialogHandler
	{
	public:			
		mwGLRenderingContextPreservingProgressHandlerDecorator(mwIProgressDialogHandler* toBeDecoratedProgressHandler);
		virtual ~mwGLRenderingContextPreservingProgressHandlerDecorator(void);

		virtual bool IsAborted();

		virtual void SetAborted(bool abort);

		virtual void SetStepCount( unsigned long stepCount );

		virtual unsigned long SetPos( unsigned long value );

		virtual unsigned long StepIt( unsigned long stepCount );

		virtual void SetInfo( const misc::mwstring &info );

		virtual void SetCaption( const misc::mwstring &caption );

		virtual void Show();

		virtual void Close();

		virtual void SetStyles(unsigned int styles);

		virtual void AddStyles(unsigned int styles);

		virtual void Reset();

	private:	
		mwIProgressDialogHandler*				m_decoratedProgressHandler;
	}; // mwGLRenderingContextPreservingProgressHandlerDecorator class declaration
}; // mmedia namespace
#endif	//	MW_MWGLRENDERINGCONTEXTPRESERVINGPROGRESSHANDLERDECORATOR_HPP_
