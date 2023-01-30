// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWTHREADHANDLERINTERFACE_HPP_
#define MW_MWTHREADHANDLERINTERFACE_HPP_
class mwThreadHandlerInterface
{
public:
	/// Callback - will be periodical called by suspending threads.
	virtual void Periodic() = 0;
	/// Callback - will be called by suspending threads when an exception occur.
	virtual void ExceptionHandler() = 0;
};
#endif  //	MW_MWTHREADHANDLERINTERFACE_HPP_
