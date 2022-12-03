// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCODECVT_HPP_
#define MW_MWCODECVT_HPP_

#include <locale>
#include "mwString.hpp"


	//! mw base class for std::codecvt
	/*! mw base class for std::codecvt
	*/
class MW_5AXUTIL_API mwCodecvt: public std::codecvt < wchar_t , char , mbstate_t >
{
public:

	explicit mwCodecvt(size_t _R = 0)
		: std::codecvt < wchar_t , char , mbstate_t >(_R) {
	}
	virtual ~mwCodecvt(){}

	//! checks a partial header against codec's header
	/*! checks if a pased partial header matches 
		the begining of the header known by this codec
			\param vPartialHeader partial header to be check
			\return true if passed header fits
	*/
	const bool FitsHeader(const std::string& vPartialHeader) const
	{
		bool fits = true;
		if(GetHeader().size() < vPartialHeader.size())
		{
			fits= false;
		}
		else
		{
			for(size_t i = 0; i < vPartialHeader.size(); ++i)
			{
				if(GetHeader()[i] != vPartialHeader[i])
				{
					fits = false;
					break;
				}
			}
		}
		return fits;
	};

	//! checks a header against codec's header
	/*! checks if a pased header matches 
		the header known by this codec
			\param vPartialHeader header to be check
			\return true if passed header match
	*/
	const bool IsHeader(const std::string& vPartialHeader) const
	{
		return (GetHeader()==vPartialHeader);
	};

	//! gets header splited in a vector of bytes
	/*! gets header splited in a vector of bytes
			\return header
	*/
	virtual const std::string& GetHeader() const =0;

	virtual const bool WorksOnlyOnBinary() const =0;

	//! gets writable header
	/*! returns the header in a writable type
	\return header
	*/
	virtual const misc::mwstring& GetWritableHeader() const =0;

private:
	mwCodecvt(mwCodecvt&);
	mwCodecvt& operator = (mwCodecvt&);
};
#endif	//	MW_MWCODECVT_HPP_
