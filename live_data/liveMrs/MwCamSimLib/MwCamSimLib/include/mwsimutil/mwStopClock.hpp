// (C) 2003-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTOPCLOCK_HPP_
#define MW_MWSTOPCLOCK_HPP_
#include <string>
#include <cstdio>
#include "mwBasicTypes.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwScopedPointer.hpp"
namespace misc
{

class mwStopClockImpl;

class MW_5AXUTIL_API mwStopClock
{
public:
	mwStopClock();
	virtual ~mwStopClock();
    mwStopClock(const mwStopClock& other);
    mwStopClock& operator=(const mwStopClock& rhs);

	virtual void Start();
	virtual void Stop();

	virtual misc::uint64_t GetDays() const;
	virtual misc::uint64_t GetHours() const;
	virtual misc::uint64_t GetMinutes() const;
	virtual misc::uint64_t GetSeconds() const;
	virtual misc::uint64_t GetMiliSeconds() const;
	virtual misc::uint64_t GetAllHours() const;
	virtual misc::uint64_t GetAllMinutes() const;
	virtual misc::uint64_t GetAllSeconds() const;
	virtual misc::uint64_t GetAllMiliseconds() const;

protected:
	virtual void Calculate() const {};

private:
#pragma warning(push)
#pragma warning(disable : 4251)

	mwScopedPointer<mwStopClockImpl> imp;

#pragma warning(pop)
};

inline std::string MillisecondsToString(const misc::uint64_t& milliseconds){
    int sec = (int)milliseconds / 1000;
    int min = sec / 60;
    int hour = min / 60;
    char s[16];
	//use std::sprintf and not the microsoft extensions
#pragma warning(suppress : 4996)
	std::sprintf(s, "%02d:%02d:%02d.%03d", hour % 24, min % 60, sec % 60, (int)milliseconds % 1000);
	return std::string(s);
}

}; // namespace misc
#endif	//	MW_MWSTOPCLOCK_HPP_
