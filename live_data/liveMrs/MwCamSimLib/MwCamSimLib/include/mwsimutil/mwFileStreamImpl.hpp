// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWFILESTREAMIMPL_HPP_
#define MW_MWFILESTREAMIMPL_HPP_

#include <fstream>
#include "mwCodecvt.hpp"
#include "mwString.hpp"

#if defined (_WIN32) && ! defined(UNDER_CE) && !defined(MW_USE_STLPORT) //OS1
#ifndef _Filet
#define _Filet FILE
#endif

//! a file buffer class that opens files having an unicode path
/*! a file buffer class that opens files having an unicode path
*/
template<class _E, class _Tr = std::char_traits<_E> >
class w_basic_filebuf : public std::basic_filebuf<_E, _Tr>
{
public:
    //! self renaming
    typedef w_basic_filebuf<_E, _Tr> _Myt;
	typedef typename std::basic_filebuf<_E, _Tr>::_Cvt _Cvt;

    //! constructor
    /*!
        \param _File file to be buffered
    */
    w_basic_filebuf(_Filet *_File = 0) : std::basic_filebuf<_E, _Tr>(_File){
        destroyableMyCvt = new _ACvt();
        myCvt=destroyableMyCvt;
    };

    //! opens specified file
    /*!
        \param _S file to be opened
        \param _M specifies the mode in which to be open(read,write etc)
        \return reference to itself
    */
    _Myt* open(const misc::mwstring &_S, std::ios_base::openmode _M);


	void SetMyCvt(std::basic_filebuf<_E, _Tr>::_Cvt* newCvt) {
        myCvt = newCvt;
    }

    ~w_basic_filebuf(){
        if (destroyableMyCvt!=NULL){
            this->close();
            delete destroyableMyCvt;
        }
    };
    //! opens specified file
    /*!
        \param name file to be opened
        \param mode specifies the mode in which to be open(read,write etc)
        \return handler to a file
    */
    FILE* __wFiopen(const misc::mwstring &name, std::ios_base::openmode mode) {
        // open a file
        static const wchar_t *mods[] = {
            L"r",  L"w",  L"w",  L"a",  L"rb",  L"wb",  L"wb",
            L"ab", L"r+", L"w+", L"a+", L"r+b", L"w+b", L"a+b",
            0
        };

        static const int valid[] = {
            std::ios_base::in,
            std::ios_base::out,
            std::ios_base::out | std::ios_base::trunc,
            std::ios_base::out | std::ios_base::app,
            std::ios_base::in  | std::ios_base::binary,
            std::ios_base::out | std::ios_base::binary,
            std::ios_base::out | std::ios_base::trunc | std::ios_base::binary,
            std::ios_base::out | std::ios_base::app   | std::ios_base::binary,
            std::ios_base::in  | std::ios_base::out,
            std::ios_base::in  | std::ios_base::out   | std::ios_base::trunc,
            std::ios_base::in  | std::ios_base::out   | std::ios_base::app,
            std::ios_base::in  | std::ios_base::out   | std::ios_base::binary,
            std::ios_base::in  | std::ios_base::out   | std::ios_base::trunc | std::ios_base::binary,
            std::ios_base::in  | std::ios_base::out   | std::ios_base::app   | std::ios_base::binary,
            0
        };

        FILE *fp;
        int n;
        std::ios_base::openmode atefl = mode & std::ios_base::ate;
        mode &= ~std::ios_base::ate;
        for (n = 0; valid[n] != 0 && valid[n] != mode; ++n)
            ;
        if (valid[n] == 0 )
            return (0);

        if (::_wfopen_s(&fp, name.c_str(), mods[n])!=0)
            return (0);

        if ( fp == 0)
            return (0);

        if (!atefl || ::fseek(fp, 0, SEEK_END) == 0)
            return (fp);
        ::fclose(fp); // can't position at end
        return (0);
    }

//! specifies max encoding length for a char
private:
    w_basic_filebuf(w_basic_filebuf&);
    w_basic_filebuf& operator = (w_basic_filebuf&);
	class _ACvt : public std::basic_filebuf<_E, _Tr>::_Cvt
    {};
    _ACvt* destroyableMyCvt;
	std::basic_filebuf<_E, _Tr>::_Cvt* myCvt;

}; //w_basic_filebuf



//////////////////////////////////////
// TEMPLATE CLASS basic_ifstream_ex
template<class _E, class _Tr = std::char_traits<_E> >
class basic_ifstream_ex : public std::basic_istream<_E, _Tr>
{
public:
	//! self renaming
	typedef basic_ifstream_ex<_E, _Tr> _Myt;
	//! renaming buffer
	typedef w_basic_filebuf<_E, _Tr> _Myfb;

	//! default constructor
	basic_ifstream_ex() : std::basic_istream<_E, _Tr>(&_Fb) {
	}

	//! constructor
	/*! opens specified file
		\param _S file to be opened
		\param _M specifies the mode in which to be open(read,write etc)
	*/
	explicit basic_ifstream_ex(const misc::mwstring &_S, std::ios_base::openmode _M = std::ios_base::in)
		: std::basic_istream<_E, _Tr>(&_Fb) {

		if (_Fb.open(_S, _M | std::ios_base::in) == 0)
			this->setstate(std::basic_ios<_E,_Tr>::failbit);

	}

	//! destructor
	virtual ~basic_ifstream_ex() {
	}

	//! return internal buffer
	/*!
		\return the buffer
	*/
	_Myfb *rdbuf() const
	{
		return ((_Myfb *)&_Fb);
	}

	//! confirms if file is sopen
	/*!
		\return true if file is open
	*/
	bool is_open() const
	{
		return (_Fb.is_open());
	}

	//! opens specified file
	/*!
		\param _S file to be opened
		\param _M specifies the mode in which to be open(read,write etc)
	*/
	void open(const misc::mwstring &_S, std::ios_base::openmode _M = std::ios_base::in)
	{
		if (_Fb.open(_S, _M | std::ios_base::in) == 0)
			this->setstate(std::ios_base::failbit);
	}

	//! opens specified file
	/*!
		\param _S file to be opened
		\param _M specifies the mode in which to be open(read,write etc)
	*/
#if _MSC_VER < 1900 // < VC 2015	
	void open(const misc::mwstring &_S, std::ios_base::open_mode _M) {
		open(_S, (std::ios_base::openmode)_M);
	}
#endif

	//! close opened file
	void close()
	{
		if (_Fb.close() == 0)
		  this->setstate(std::ios_base::failbit);
	}

	const bool GetFailed() const
	{
		return this->fail();
	}

private:
        basic_ifstream_ex(basic_ifstream_ex&);
	basic_ifstream_ex& operator = (basic_ifstream_ex&);
protected:
	//! the buffer
	_Myfb _Fb;
};


/////////////////////////////////////
// TEMPLATE CLASS basic_ofstream_ex
//
template<class _E, class _Tr = std::char_traits<_E> >
	class basic_ofstream_ex : public std::basic_ostream<_E, _Tr>
{

public:
	//! self renaming
	typedef basic_ofstream_ex<_E, _Tr> _Myt;
	//! renaming of the buffer
	typedef w_basic_filebuf<_E, _Tr> _Myfb;
	
	//! default constructor
	basic_ofstream_ex()
		: std::basic_ostream<_E, _Tr>(&_Fb) {
	}
	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	explicit basic_ofstream_ex(const misc::mwstring &_S, std::ios_base::openmode _M = std::ios_base::out | std::ios_base::trunc)
		: std::basic_ostream<_E, _Tr>(&_Fb) {
		if (_Fb.open(_S, _M | std::ios_base::out) == 0){
			this->setstate(std::ios_base::failbit);
		}
	}
	//! destructor
	virtual ~basic_ofstream_ex() {}

	//! return internal buffer
	/*!
		\return the bufer
	*/
	_Myfb *rdbuf() const {
		return ((_Myfb *)&_Fb);
	}

	//! confirms if file is sopen
	/*!
		\return true if file is open
	*/
	bool is_open() const {
		return (_Fb.is_open());
	}

	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	void open(const misc::mwstring &_S, std::ios_base::openmode _M = std::ios_base::out | std::ios_base::trunc) {
		if (_Fb.open(_S, _M | std::ios_base::out) == 0)
		{
			this->setstate(std::ios_base::failbit);
		}
	}

	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
#if _MSC_VER < 1900 // < VC 2017		
	void open(const misc::mwstring &_S, std::ios_base::open_mode _M) {
		open(_S, (std::ios_base::openmode)_M);
	}
#endif
	//! close opened file
	void close() {
		if (_Fb.close() == 0)
		{
		 	this->setstate(std::ios_base::failbit);
		}
	}

	const bool GetFailed() const
	{
		return this->fail();
	}
private:
    basic_ofstream_ex(basic_ofstream_ex&);
	basic_ofstream_ex& operator = (basic_ofstream_ex&);
protected:
	//! file buffer
	_Myfb _Fb;
};


#elif (defined(__linux__) || defined(__APPLE__)) || defined(MW_USE_STLPORT) //OS1 - WINDOWS IMPLEMENTATION ENDS HERE

#include "mwString.hpp"
#include <cctype>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <locale>

#ifndef _Filet
#define _Filet FILE
#endif

template<class CharT, class Traits = std::char_traits<CharT> >
    class MW_5AXUTIL_API w_basic_filebuf : public std::basic_filebuf<CharT, Traits>
{
  public:
    typedef w_basic_filebuf<CharT, Traits> my_type;
    //typedef typename std::basic_filebuf<CharT, Traits>::__codecvt_type __codecvt_type;

    //struct my_codecvt_t : public std::codecvt<wchar_t,char,std::mbstate_t>{
    //    my_codecvt_t(std::size_t refs = 0) : codecvt(refs) {}
    //    ~my_codecvt_t(){}
    //};

    w_basic_filebuf(_Filet * = 0)
    : std::basic_filebuf<CharT, Traits>() {};

    my_type* open(const misc::mwstring &string, std::ios_base::openmode mode) {
        std::string std_string = string.ToUTF8();
        std::basic_filebuf<CharT, Traits>::open(std_string.c_str(), mode);
        return this;
    }

    //~w_basic_filebuf() {};



private:
//    w_basic_filebuf(w_basic_filebuf&);
//    w_basic_filebuf& operator = (w_basic_filebuf&);
}; //w_basic_filebuf


//////////////////////////////////////
// TEMPLATE CLASS basic_ifstream_ex
//
//#if defined (_WIN32)
template<class _E, class _Tr = std::char_traits<_E> >
class MW_5AXUTIL_API basic_ifstream_ex : public std::basic_istream<_E, _Tr>
{
public:
	//! self renaming
	typedef basic_ifstream_ex<_E, _Tr> _Myt;
	//! renaming buffer
	typedef w_basic_filebuf<_E, _Tr> _Myfb;

	//! default constructor
	basic_ifstream_ex() : std::basic_istream<_E, _Tr>(&_Fb) {
	}

	//! constructor
	/*! opens specified file
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	explicit basic_ifstream_ex(const misc::mwstring &_See, std::ios_base::openmode _M = std::ios_base::in)
		: std::basic_istream<_E, _Tr>(&_Fb) {

		if (_Fb.open(_See, _M | std::ios_base::in) == 0)
			setstate(std::basic_ios<_E,_Tr>::failbit);

	}

	//! destructor
	virtual ~basic_ifstream_ex() {
	}

	//! return internal buffer
	/*!
		\return the bufer
	*/
	_Myfb *rdbuf() const
	{
		return ((_Myfb *)&_Fb);
	}

	//! confirms if file is sopen
	/*!
		\return true if file is open
	*/
	bool is_open() const
	{
		return (_Fb.is_open());
	}

	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	void open(const misc::mwstring &_See, std::ios_base::openmode _M = std::ios_base::in)
	{
		if (_Fb.open(_See, _M | std::ios_base::in) == 0)
			this->setstate(std::ios_base::failbit);
	}

	//! close opened file
	void close()
	{
		if (_Fb.close() == 0)
		  this->setstate(std::ios_base::failbit);
	}

	const bool GetFailed() const
	{
		return this->fail();
	}

private:
    basic_ifstream_ex(basic_ifstream_ex&);
	basic_ifstream_ex& operator = (basic_ifstream_ex&);
protected:
	//! the buffer
	_Myfb _Fb;
};  //basic_ifstream_ex


/////////////////////////////////////
// TEMPLATE CLASS basic_ofstream_ex
//
//#if defined (_WIN32)
template<class _E, class _Tr = std::char_traits<_E> >
	class MW_5AXUTIL_API basic_ofstream_ex : public std::basic_ostream<_E, _Tr>
{
public:
	//! self renaming
	typedef basic_ofstream_ex<_E, _Tr> _Myt;
	//! renaming of the buffer
	typedef w_basic_filebuf<_E, _Tr> _Myfb;

	//! default constructor
	basic_ofstream_ex()
		: std::basic_ostream<_E, _Tr>(&_Fb) {
	}
	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	explicit basic_ofstream_ex(const misc::mwstring &_See, std::ios_base::openmode _M = std::ios_base::out | std::ios_base::trunc)
		: std::basic_ostream<_E, _Tr>(&_Fb) {
		if (_Fb.open(_See, _M | std::ios_base::out) == 0)
		{
			this->setstate(std::basic_ios<_E,_Tr>::failbit);
        #ifdef DEBUG_MISC
            std::cout << "FAIL ------ failbit set!!!";
        #endif
		}
	}
	//! destructor
	virtual ~basic_ofstream_ex() {
	}

	//! return internal buffer
	/*!
		\return the bufer
	*/
	_Myfb *rdbuf() const {
		return ((_Myfb *)&_Fb);
	}

	//! confirms if file is sopen
	/*!
		\return true if file is open
	*/
	bool is_open() const {
		return (_Fb.is_open());
	}

	//! opens specified file
	/*!
		\param _S file to be opend
		\param _M specifyes the mode in wich to be open(read,write etc)
	*/
	void open(const misc::mwstring &_See, std::ios_base::openmode _M = std::ios_base::out | std::ios_base::trunc) {
		if (_Fb.open(_See, _M | std::ios_base::out) == 0)
		{
            std::basic_ostream<_E, _Tr>::setstate(std::basic_ios<_E,_Tr>::failbit);
		}
	}

	//! close opened file
	void close() {
		if (_Fb.close() == 0)
		{
            std::basic_ostream<_E, _Tr>::setstate(std::basic_ios<_E,_Tr>::failbit);
		}
	}

	const bool GetFailed() const
	{
		return this->fail();
	}
private:
    basic_ofstream_ex(basic_ofstream_ex&);
	basic_ofstream_ex& operator = (basic_ofstream_ex&);
protected:
	//! file buffer
	_Myfb _Fb;
}; // basic_ofstream_ex


#endif                //OS1
#endif	//	MW_MWFILESTREAMIMPL_HPP_
