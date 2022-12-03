// (C) 2014-2019 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWDISPLAYABLEPROGRESSPOOLSELECTOR_HPP_
#define MW_MWDISPLAYABLEPROGRESSPOOLSELECTOR_HPP_
#include "mwProgressKeeper.hpp"
#include "mwAutoPointer.hpp"
#include "mwString.hpp"
#include <map>
namespace misc
{
	class mwCriticalSection;
	class winCpuTickTimerRestartable;
}

//! Allow sharing of the same display context by multiple asynchronous progress handlers
/*! Groups by family the progress handlers and display one at a time by cycling through each family.
	Class switch the families after a specify cycling period of time or if there are 
	no more displayable members in current family.
	From a family is displayed the one having the shortest progress at the display request time.
	A family is identify based on the progress info string, and a progress is allow to move from
	one family to another just by changing it's info string. Such a change is automatically detected.
	Also a family member deceased is automatically detected, no action required from outside.
	The class use critical sections for synchronization when:
	a progress is born, a progress changes it's family, a progress dyes, and when it's searching for 
	next displayable candidate.
*/
class MW_5AXUTIL_API mwDisplayableProgressPoolSelector
{
public:
	//! Constructor
	mwDisplayableProgressPoolSelector();
	//! destructor needed for pimpl idiom
	~mwDisplayableProgressPoolSelector();
	//! creates a progress handler assigning it to the specified family
	/*! by default it's assign to an UnNamed family and life time is the same as for this class.
		If you wary that you will have too many progress handlers dangling around, then you should 
		call Release() function on the autopointer you get, and make sure you destroy the progress 
		handler when you are done with it.
		Note: 
		Calling ProgressHandler::Close will just mark the handler that is not displayable but will not remove
		it's assignment from this class, you must destroy it to get it really removed. 
		Calling ProgressHandler::Show will mark the handler that is displayable (by default it's not displayable)
		See also class description for details about what is a family and how it can be changed
	*/
	misc::mwAutoPointer<mwIProgressDialogHandler> CreateNewProgressHandler 
		(const misc::mwstring& initialFamily = _T(""));

	//! returns a copy of next progress that need to be display
	/*! it returns a copy and not the progress itself to allow asynchronous display. It may return Null
		if there is not displayable progress.
		See class description for more details about how the next displayable progress is picked.
	*/
	const misc::mwAutoPointer<mwProgressKeeper> GetNextDisplayableInformation();

	//! set in seconds the time frame during which info from the same family is return (default is 2 seconds)
	void SetFamilyCyclingTime(const double& newFamilyCyclingTime);

protected:
	//! self register progress keeper 
	class mwFamilyMemberProgressHandler: public mwProgressKeeper
	{
	public:
		typedef misc::mwAutoPointer<mwFamilyMemberProgressHandler> Ptr;
		mwFamilyMemberProgressHandler(mwDisplayableProgressPoolSelector& progressHandlersReggiserOffice,const misc::mwstring& initialFamily);
		//this triggers registering of family change
		void SetInfo(const misc::mwstring &info);
		//this triggers registering of deceased
		~mwFamilyMemberProgressHandler();
	private:
		mwFamilyMemberProgressHandler& operator=(const mwFamilyMemberProgressHandler&); // = delete
		mwDisplayableProgressPoolSelector& m_progressHandlersReggiserOffice;
		
	};
	friend class mwFamilyMemberProgressHandler;//to allow to self register on family change or deceased
	//!registration functions, you may do extra customizations here
	virtual void RegisterNewBorn(const mwFamilyMemberProgressHandler::Ptr infant)
	{
		RegisterToFamily(infant);
	}
	virtual void RegisterDeceased(const mwFamilyMemberProgressHandler::Ptr deceased)
	{
		UnregisterFromFamily (deceased, deceased->GetInfo());
	}
	virtual void RegisterFamilyChange(const mwFamilyMemberProgressHandler::Ptr transfering, misc::mwstring oldFamily)
	{
		RegisterToFamily ( UnregisterFromFamily(transfering, oldFamily) );
	}
private:
#pragma warning(push)
#pragma warning(disable : 4251)
	typedef std::vector < mwFamilyMemberProgressHandler::Ptr >	AFamily;
	typedef misc::mwstring												FamilyName;
	typedef std::map< FamilyName, AFamily >								RegistryOfAllProgresses;

	void RegisterToFamily(const mwFamilyMemberProgressHandler::Ptr joinner);
	//! it does not remove the family even it's members are all dead
	/*! the function returns the original pointer that contains ownership information
		since it's not sure that the one pass as function parameter is also containing this info.
	*/
	mwFamilyMemberProgressHandler::Ptr UnregisterFromFamily(const mwFamilyMemberProgressHandler::Ptr leaver, misc::mwstring oldFamily);

	//! try to grabs info from last updated family,
	/*! getting as reference the iterator after the last displayed family 
		since family may have extinguished inbetween
	*/
	bool GetFromLastDisplayedFamily(
		RegistryOfAllProgresses::iterator upperBoundFamilyIt,
		misc::mwAutoPointer<mwProgressKeeper>& toReturn);
	//! try to grabs info from families 
	/*! getting as reference the iterator after the last displayed family 
	*/
	bool GetFromNextFamilies(
		RegistryOfAllProgresses::iterator upperBoundFamilyIt,
		misc::mwAutoPointer<mwProgressKeeper>& toReturn);	

	RegistryOfAllProgresses									m_registry;
	misc::mwstring											m_lastDisaplyedFamily;
	misc::mwAutoPointer<misc::mwCriticalSection>			m_registryChangesCriticalSection;
	misc::mwAutoPointer<misc::winCpuTickTimerRestartable>	m_clock;
	double													m_familyCyclingTime;
	bool													m_IgnoreRegistrationRequests;
#pragma warning(pop)
};
#endif	//	MW_MWDISPLAYABLEPROGRESSPOOLSELECTOR_HPP_
