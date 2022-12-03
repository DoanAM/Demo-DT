// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMACHSIMVERIFIERPROGRESSHANDLER_HPP_
#define MW_MWMACHSIMVERIFIERPROGRESSHANDLER_HPP_
#include "mwVerifierNestedEnums.hpp"

#include <mwIProgressHandler.hpp>
#include <mwOverrideFinal.hpp>

#ifdef SetJob
#undef SetJob  // defined in winspool.h
#endif

/// Use this progress handler to be notified about the progress of internal operations in
/// mwMachSimVerifier.
///
/// The progress handler is guaranteed to be called on the main thread (the thread you use for
/// mwMachSimVerifier API calls). The simulation is blocked by any progress handler methods (until
/// they return). So you should try to implement these callbacks as efficiently as possible.
///
/// Most of the methods defined in this class are irrelevant (for legacy reasons). They
/// are not called by mwMachSimVerifier, and calling them yourself has no useful effect. The only
/// relevant methods are:
/// - `SetJob`: Implement this method to receive what kind of job the verifier is working on. A
///   single API call may consist of multiple jobs.
/// - `SetStepCount`: Implement this method to be notified about the number of steps that the
///   current operation has. This does not necessarily correlate with the expected duration of that
///   job. This method is called whenever the job type changes.
/// - `SetPos`:  Implement this method to be notified about the progress of the current job (0 <= @p
///   value <= stepCount). You can use this method to trigger an update of your progress UI. For
///   performance reasons you probably don't want to do much work in this function, since it can
///   be called quite often.
///
///   The return value is unused (just return zero).
/// - `IsAborted`: Your callback should return “true” here if the current API call has to be
///   aborted. This may leave the verifier in an inconsistent state (e.g. half-simulated moves). Use
///   this to allow your user to abort simulations when they notice that e.g. simulation settings
///   are wrong, or when they don't want to wait anymore. You probably want to restart the
///   simulation from a known “good” state afterwards.
///
///   @note This callback may be called multiple times, even if you already returned “true” once.
///   After you've decided to abort please make sure that your callback keeps returning “true”
///   consistently, until the end of the current API call.
class mwMachSimVerifierProgressHandler : public mwIProgressDialogHandler
{
public:
	typedef VerifierUtil::mwMachSimVerifierProgressHandlerJobType JobType;

	static const JobType JobUnknown = VerifierUtil::JobUnknown;
	static const JobType JobInitializeTarget = VerifierUtil::JobInitializeTarget;
	static const JobType JobInitializeMesh = VerifierUtil::JobInitializeMesh;
	static const JobType JobCalcGougesList = VerifierUtil::JobCalcGougesList;
	static const JobType JobCalcExcessList = VerifierUtil::JobCalcExcessList;
	static const JobType JobCalcDeviation = VerifierUtil::JobCalcDeviation;
	static const JobType JobDrawStockMesh = VerifierUtil::JobDrawStockMesh;
	static const JobType JobFreeWorkpiece = VerifierUtil::JobFreeWorkpiece;
	static const JobType JobFreeTarget = VerifierUtil::JobFreeTarget;
	static const JobType JobSimulateMoveList = VerifierUtil::JobSimulateMoveList;
	static const JobType JobOffsettingMesh = VerifierUtil::JobOffsettingMesh;
	static const JobType JobSaveSimulation = VerifierUtil::JobSaveSimulation;
	static const JobType JobLoadSimulation = VerifierUtil::JobLoadSimulation;

	/// Called whenever the current job type changes.
	///
	/// Implement this method to receive what kind of job the verifier is working on. A single API
	/// call may consist of multiple jobs.
	virtual void SetJob(JobType job) = 0;

	/// @hidden
	virtual void SetCaption(const misc::mwstring&)
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void SetStyles(unsigned int)
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void AddStyles(unsigned int)
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void SetInfo(const misc::mwstring&)
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void Show()
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void Close()
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void SetAborted(bool)
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual void Reset()
	{
		// DEPRECATED, not used by mwMachSimVerifier
	}

	/// @hidden
	virtual unsigned long StepIt(unsigned long)
	{
		// DEPRECATED, not used by mwMachSimVerifier
		return 0;
	}
};
#endif  //	MW_MWMACHSIMVERIFIERPROGRESSHANDLER_HPP_
