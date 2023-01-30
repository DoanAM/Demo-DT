// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTREAMABLESPECIALTYPES_HPP_
#define MW_MWSTREAMABLESPECIALTYPES_HPP_


#include "mwBasicTypes.hpp"
#include <cstddef>

namespace misc
{
	//! wraps size_t
	/*! wraps size_t such as to became a class from an type in order to allow
			functions overloading against unsigned int and uint64_t
	*/
	class mwStreamableSize_t
	{
	private:
		typedef mwStreamableSize_t						Myself;
	public:

		//! Constructor
		/*!
		*/
		mwStreamableSize_t ():m_value(0){};

		//! Constructor
		/*! I would not recommend you to remove this explicit.
		*/
		explicit mwStreamableSize_t (const size_t& value)
			:m_value(value){};

		//! gets Value
		/*!
				\returns the Value
		*/
		inline const size_t& GetValue() const
			{ return m_value;};

	private:

		//! prevents use of this class somewhere other then in streaming.
		/*! setter is not allowed in order to prevent use of this class
			somewhere other then in streaming. I hope no one will use such a class
			some where else since will not be easy to change it's value, unless is
			creating a new one, so the class is more than inefficients, and
			i hope this will be enough to not be used.
		*/
		inline void SetValue(const size_t& value);

		size_t m_value;
	};

	//! wraps uint64_t
	/*! wraps uint64_t such as to help size_t to became a class from an type in order to allow 
			functions overloading against unsigned int and uint64_t
	*/
	class mwStreamableUnsignedInt64
	{
	private:
		typedef mwStreamableUnsignedInt64						Myself;
	public:

		//! Constructor
		/*! I would not recommend you to remove this explicit.
		*/
		mwStreamableUnsignedInt64 ()
			:m_value(0){};

		//! Constructor
		/*! I would not recommend you to remove this explicit.
		*/
		explicit mwStreamableUnsignedInt64 (const ::misc::uint64_t& value)
			:m_value(value){};


		//! gets Value
		/*! 			
				\returns the Value
		*/
		inline const ::misc::uint64_t& GetValue() const
			{ return m_value;};

	private:
	
		//! prevents use of this class somewhere other then in streaming.
		/*! setter is not allowed in order to prevent use of this class 
			somewhere other then in streaming. I hope no one will use such a class 
			some where else since will not be easy to change it's value, unless is
			creating a new one, so the class is more than inefficients, and
			i hope this will be enough to not be used.
		*/
		inline void SetValue(const ::misc::uint64_t& value);


		//! does not allow creation from an unsigned int
		/*! on 32b compiling size_t is unsigned int and not uint64_t.
			By declaring this constructor private we intend to prevent the creation
			of a mwStreamableUnsignedInt64 from a variable of type size_t.
			If you need to seraialize/deserialize an size_t variable then please create 
			a mwStreamableSize_t class instead of a mwStreamableUnsignedInt64
				\returns the Value
		*/
		mwStreamableUnsignedInt64 (const unsigned int& value);
		::misc::uint64_t m_value;
	};
}
#endif	//	MW_MWSTREAMABLESPECIALTYPES_HPP_
