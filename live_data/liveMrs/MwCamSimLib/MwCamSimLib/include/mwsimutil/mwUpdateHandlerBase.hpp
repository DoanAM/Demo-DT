// (C) 2019 by ModuleWorks GmbH
// Owner: 5Axis UP & Additive

#ifndef MW_UPDATEHANDLERBASE_HPP_
#define MW_UPDATEHANDLERBASE_HPP_

#include "mwAutoPointer.hpp"
#include "mwmiscException.hpp"

namespace interact
{

/// Basic update handler interface without the clutter of mwUpdateHandlerExecutant.
///
/// Use this interface in algorithms to either set the progress using @ref SetProgress() or
/// if progress information is not avaiable call @ref VerifyIsCancel() to allow
/// canellation of the algorithm.
/// 
/// To create a custom update handler derive from this base class and override the callbacks
/// for updating the progress @ref OnProgressUpdate() and @ref IsCancel().
/// 
/// To interface with mwUpdateHandlerExecutant see mwUpdateHandlerHelper.hpp.
/// 
/// The purpose is to be as simple as possible. Do not extend this interface!
/// 
/// Further documentation and design decisions in our wiki:
/// "Progress & Cancel for Internal and External Algorithms"
/// https://wiki.moduleworks.com/pages/viewpage.action?pageId=191792266
class MW_5AXUTIL_API mwUpdateHandlerBase
{
public:
	typedef misc::mwAutoPointer<mwUpdateHandlerBase> Ptr;

	void SetProgress(double progress)
	{
		VerifyIsCanceled();
		OnProgressUpdate(progress);
	}

	void VerifyIsCanceled() const
	{
		if (IsCanceled())
		{
			throw mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION);
		}
	}

	virtual ~mwUpdateHandlerBase() {}

private:
	/// Will be called when the progress is updated using @ref SetProgress().
	virtual void OnProgressUpdate(double progress) = 0;

	/// Will be called by @ref VerifyIsCaneled() to determine if the computation should be canceled.
	/// @returns true for cancel, false for continue.
	virtual bool IsCanceled() const = 0;
};

} // namespace interact

#endif // MW_UPDATEHANDLERBASE_HPP_