// (C) 2016-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOMPILERBIBASICTYPES_HPP_
#define MW_MWCOMPILERBIBASICTYPES_HPP_
#include "mwStringConversions.hpp"
#include <list>
#include "mwBinInputStream.hpp"
#include "mwStreamableSpecialTypes.hpp"

#include "mwUTFTypes.hpp"
   
#if defined(__linux__) || defined(__APPLE__)
	#ifndef _NATIVE_WCHAR_T_DEFINED
		#define _NATIVE_WCHAR_T_DEFINED
	#endif
#endif

namespace misc
{
	class mwBIBasicTypes;
}

namespace misc
{
	class MW_5AXUTIL_API mwCompilerBIBasicTypes
	{
	public:
			typedef mwBinInputStream::mwsize_t mwsize_t;
			//! Constructor
			/*!
					\param rInputStream the input stream to be used for reading
					\param vShrinkData specifies if you are reading shrink data.
						If this param value is true then all the doubles will be readed as
						they have the size of a float, and all the ints will be readed as
						they have the size of a short.
					\param isUnicode specifies if you are reading unicode data.
					\param is64bBin specifies if you are reading data write by a 64b OS.

			*/
			mwCompilerBIBasicTypes(mwBinInputStream& rInputStream,bool vShrinkData,bool isUnicode=false,bool is64bBin =false);

			virtual ~mwCompilerBIBasicTypes();
			// Basic types
		
			//! operator>>
			/*!
				\param value of type double &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  double &value );

			//! operator>>
			/*!
				\param value of type float &
				\return operator>> of type virtual mwBinInputStream&
			*/	
			virtual mwBinInputStream& operator>>(  float &value );

			//! operator>>
			/*!
				\param value of type bool &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  bool &value );

			//! operator>>
			/*!
				\param value of type char &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  char &value );

			//! operator>>
			/*!
				\param value of type short &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  short &value );

			//! operator>>
			/*!
				\param value of type int &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  int &value );

			//! operator>>
			/*!
				\param value of type unsigned char &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  unsigned char &value );

			//! operator>>
			/*!
				\param value of type unsigned short &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  unsigned short &value );

			#ifdef _NATIVE_WCHAR_T_DEFINED
			//! operator>>
			/*!
				\param value of type unsigned short &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  wchar_t &value );
			#endif
			//! operator>>
			/*!
				\param value of type unsigned int &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  unsigned int &value );

			//! operator>>
			/*!
				\param value of type long double &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  long double &value );

			//! operator>>
			/*!
				\param value of type int64_t &
				\return operator>> of type virtual mwBinInputStream&
			*/

			virtual mwBinInputStream& operator>>(  ::misc::int64_t &value );



			//! operator>>
			/*!
				\param value of type mwStreamableSize_t &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  mwStreamableSize_t &value );

			//! Helper function for deserializeg an size_t
			/*!
				\return deserialized value
			*/
			virtual const size_t GetSize_t()
			{
				mwStreamableSize_t tmpValueObj;
				(*this) >> tmpValueObj;
				return tmpValueObj.GetValue();
			}

			//! operator>>
			/*!
				\param value of type mwStreamableUnsignedInt64 &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  mwStreamableUnsignedInt64 &value );

			//! Helper function for deserializeg an size_t
			/*!
				\return deserialized value
			*/
			virtual const ::misc::uint64_t GetUnsignedInt64();

			//! operator>>
			/*!
				\param value of type misc::mwstring &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  misc::mwstring &value );
			virtual mwBinInputStream& operator>>(  misc::unicode::utf16_string &value );


		
		//! operator>> for reading into an output file stream
		/*! The first read thing is the length of the data to be read (a long integer)
			next the actual data is read
			\param file reference to a file stream where the read data is written
			\return the input stream after reading; usefull for operator concatanation
		*/
			mwBinInputStream& operator>>(   std::ostream& file  );

		//! Reads a file knowing its size
			/*! Helper function for operator>> misc::mwOFStream
				\param file the output file where to write the read content
				\param size the size of the read/write file
				\return the reference at the enclosing stream
			*/
			mwBinInputStream& ReadFileKnowingSize(   std::ostream& file , size_t size );
	
		

			//! allows deserializing of a std::pair object
			/*!
				\param value object to be deserialize
				\return the stream without the bytes used for deserializing the object
			*/
			template<class first_type, class second_type> mwBinInputStream& operator>>( std::pair< first_type, second_type > &value )
			{
				(*this) >> value.first;
				(*this) >> value.second;
				return m_InputStream;
			}
		
			//! allows deserializing of a std::vector object
			/*!
				\param value object to be deserialize
				\return the stream without the bytes used for deserializing the object
			*/
			template< class vector_type > mwBinInputStream& operator>>(std::vector< vector_type > &value )
			{
				size_t uitmpValue=this->GetSize_t();
				value.resize(uitmpValue);
				for (unsigned int i = 0; i < uitmpValue; i++)
				{
					(*this) >> value[i];
				}

				return m_InputStream;
			}
		
			//! allows deserializing of a std::list object
			/*!
				\param value object to be deserialize
				\return the stream without the bytes used for deserializing the object
			*/
			template< class list_type > mwBinInputStream& operator>>(std::list< list_type > &value )
			{
				size_t listSize=this->GetSize_t();
				for (size_t i = 0; i < listSize; i++)
				{
					list_type element;
					(*this) >> element;
					value.push_back(element);
				}

				return m_InputStream;
			}
		

			//! sets if you are reading unicode data
			/*!
					\param vUnicode speciffyes if you are reading unicode data
			*/
			inline void SetIsUnicode(const bool vUnicode)
			{
				m_Unicode=vUnicode;
			}
		
			//! Gets flag if you are reading unicode data
			/*!
				\return true if you are reading unicode data
						false otherwise
			*/
			inline const bool GetIsUnicode() const
			{
				return m_Unicode;
			}
		
			//! sets if you are reading data write by a 64b OS
			/*!
					\param is64bBin speciffyes if you are reading data write by a 64b OS
			*/
			inline void Set64bBin(const bool is64bBin)
			{
				m_64BytesBin=is64bBin;
			}
		
			//! Gets if you are reading data write by a 64b OS
			/*!
				\return true if you are reading data written by a x64 OS
						false otherwise
			*/
			inline const bool Get64bBin() const
			{
				return m_64BytesBin;
			}
		
		//! gets ShrinkData
			/*!
					\return the ShrinkData
			*/
			inline const bool GetShrinkData() const
			{ return m_ShrinkData;};
		
			//! sets ShrinkData
			/*!
					\param shrinkData the new ShrinkData
			*/
			inline void SetShrinkData(const bool shrinkData)
				{m_ShrinkData=shrinkData;};
		
		protected:
			//! the stream from which data is readed
			mwBinInputStream& m_InputStream;
		
		private:
		#pragma warning(push)
		#pragma warning(disable : 4251)
		
			
				mwCompilerBIBasicTypes& operator = (mwCompilerBIBasicTypes&);
		
			//! made it private with migration to 64 bytes platform
			/*! If you need to deserialize a size_t value (which is 32 bytes on 32 platforms and 64bytes on 64 platform)
					then use helper function GetSize_t or create an mwStreamableSize_t and use it's operator >> which is public.
				If you need to deserialize an uint64_t value (which is 64 bytes on both 32 and 64 platforms)
					then use the helper function GetUnsignedInt64 or create an mwStreamableUnsignedInt64 and use it's operator >> which is public .
				\param value of type uint64_t &
				\return operator>> of type virtual mwBinInputStream&
			*/
			virtual mwBinInputStream& operator>>(  ::misc::uint64_t &value );

		

			//! Rounds a double to the no of digits specifyed
			/*!
					\param vToRound the value to be rounded
					\param vDigits the no of digits
					\return the rounded value
			*/
			const double RoundDouble(const double vToRound, const int vDigits)const ;		

			//! speciffyes if you are reading shrinked data.
			bool m_ShrinkData;
			//! speciffyes if you are reading data write by a 64b OS
			bool m_64BytesBin;
			//! speciffyes if you are reading unicode data.
			bool m_Unicode;

			//! access ReadFileKnowingSize private function
			friend class misc::mwBIBasicTypes;
	
	#pragma warning(pop)
	};
}
#endif	//	MW_MWCOMPILERBIBASICTYPES_HPP_
