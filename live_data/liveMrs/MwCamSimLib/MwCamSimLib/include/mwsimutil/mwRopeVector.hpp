// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///                  this module describes the
/// mwRopeVector class

//#############################################################################

#ifndef MW_MWROPEVECTOR_HPP_
#define MW_MWROPEVECTOR_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include <cmath>
#include "mwPostException.hpp"
#include "mwDeprecated.hpp"
//#############################################################################
#define BIG_MEMORY_BLOCK 2097152
//#############################################################################
namespace post
{
	template<typename T>
	struct MW_5AXUTIL_API mwCell
	{
		/*****************************************************************************/
		enum ALLOC_TYPE
		{
			NULL_ALLOC = 0,
			MAX_ALLOC = 1 
		};
		/*****************************************************************************/
		mwCell()
		{
			m_size = 0;
			m_p = MW_NULL;
		}
		/*****************************************************************************/
		bool Alloc(unsigned int size, ALLOC_TYPE at = MAX_ALLOC)
		{
			if(size <= GetMax())
				m_size = size;
			else
			{
				if(at == MAX_ALLOC)
					m_size = GetMax();
				else // NULL_ALLOC
					m_size = 0;
			}
			if(m_size != 0)
			{
				m_p = new T[m_size];
				return true;
			}

			return false;// no alloc size memory 
		}
		/*****************************************************************************/
		~mwCell()
		{
			m_size = 0;
			delete []m_p;
		}
		/*****************************************************************************/
		unsigned int GetSize()
		{
			return m_size;
		}
		/*****************************************************************************/
		/*T& operator [] (unsigned int n)
		{
		return m_p[n];
		}//*/
		/*****************************************************************************/
		static unsigned int GetMax() 
		{
			return static_cast<unsigned int>(BIG_MEMORY_BLOCK / sizeof(T));
		}
		/*****************************************************************************/
		T* m_p;
		unsigned int m_size;
		/*****************************************************************************/
	};//end struct mwCell
	//#############################################################################
	template<typename T>
	class MW_5AXUTIL_API mwRopeVector
	{
	public:
		/*****************************************************************************/
		MW_DEPRECATED("Deprecated since 2017.12, please use misc::mwMemoryPoolList instead")
		mwRopeVector()
		{
			m_c = MW_NULL;
			m_size = m_nrOfCell = m_nrOfElementsInCell = 0;
		}
		/*****************************************************************************/
		MW_DEPRECATED("Deprecated since 2017.12, please use misc::mwMemoryPoolList instead")
		mwRopeVector(unsigned int size)
		{
			if(size > 0)
			{
				m_size = size;
				m_nrOfElementsInCell = mwCell<T>::GetMax();
				m_nrOfCell = static_cast<unsigned int>(ceil(static_cast<double>(m_size) / static_cast<double>(m_nrOfElementsInCell)));
				m_c = new mwCell<T>[m_nrOfCell];
				Alloc();
			}
			//else throw //Exception(0); 	
		}
		/*****************************************************************************/
		~mwRopeVector()
		{
			Clean();
		}
		/*****************************************************************************/
		mwRopeVector(const mwRopeVector& toCopy)
		{
			Clean(true);
			m_size = toCopy.m_size;
			m_nrOfCell = toCopy.m_nrOfCell;
			m_nrOfElementsInCell = toCopy.m_nrOfElementsInCell;
			m_c = new mwCell<T>[toCopy.m_nrOfCell];
			if(Alloc())
			{
				for(unsigned int i = 0; i < m_size; i++)
					this->SET(i) = toCopy[i];

			}
			throw mwPostException( mwPostException::BAD_ALLOCATION );
		}
		/*****************************************************************************/
		mwRopeVector& operator = (const mwRopeVector& toCopy)
		{
			Clean();
			m_size = toCopy.m_size;
			m_nrOfCell = toCopy.m_nrOfCell;
			m_nrOfElementsInCell = toCopy.m_nrOfElementsInCell;
			m_c = new mwCell<T>[toCopy.m_nrOfCell];
			if(Alloc())
			{
				for(unsigned int i = 0; i < m_size; i++)
					this->SET(i) = toCopy[i];

			}
			throw mwPostException( mwPostException::BAD_ALLOCATION );
			return *this;
		}
		/*****************************************************************************/
		T& operator [] (unsigned int n) 
		{
			const unsigned int m = n/m_nrOfElementsInCell; 
			return m_c[m].m_p[n - m*m_nrOfElementsInCell];
		}
		/*****************************************************************************/
		const T& operator [] (unsigned int n) const
		{
			const unsigned int m = n/m_nrOfElementsInCell; 
			return m_c[m].m_p[n - m*m_nrOfElementsInCell];
		}
		/*****************************************************************************/
		void operator += (const mwRopeVector& add)
		{
			const mwRopeVector<T> tmp(*this);
			Clean();
			m_size = tmp.GetSize() + add.GetSize();
			m_nrOfElementsInCell = mwCell<T>::GetMax();
			m_nrOfCell = m_size / m_nrOfElementsInCell;
			m_c = new mwCell<T>[m_nrOfCell];
			if(Alloc())
			{
				for(unsigned int i = 0; i < tmp.GetSize(); i++)
					this->SET(i) = tmp[i];
				for(unsigned int i = 0; i < add.GetSize(); i++)
					this->SET(tmp.GetSize() + i) = add[i];
			}
			throw mwPostException( mwPostException::BAD_ALLOCATION );
		}
		/*****************************************************************************/
		void Resize(unsigned int new_size)
		{
			if(new_size >= 0)
			{
				mwRopeVector<T> tmp(new_size);
				tmp.PartialCopy(*this, new_size);
				*this = tmp;
			}
			//else throw Exception(4); 	
		}
		/*****************************************************************************/
		void PartialCopy(const mwRopeVector& toCopy, unsigned int dim)// copy to this (in 0 to dim) from toCopy
		{
			for(unsigned int i = 0; i < dim && i < m_size && i < toCopy.GetSize(); i++)
				this->SET(i) = toCopy[i];
		}
		void DeleteElement(unsigned int index)
		{
			if(index >= 0 && index < m_size && m_size > 0)
			{
				for(unsigned int i = index; i < m_size - 1; i++)
					SET(i) = SET(i+1);
				Resize(m_size - 1);
			}
		}
		/*****************************************************************************/
		unsigned int GetSize() const{return m_size;} 
		/*****************************************************************************/
		unsigned int GetNrOfCell() const{return m_nrOfCell;} 
		/*****************************************************************************/
		unsigned int GetNrOfElementsInCell() const{return m_nrOfElementsInCell;} 
		/*****************************************************************************/
	private:
		/*****************************************************************************/
		T& SET(unsigned int n)
		{
			const unsigned int m = n/m_nrOfElementsInCell; 
			return m_c[m].m_p[n - m*m_nrOfElementsInCell];
		}
		/*****************************************************************************/
		void Clean(bool ignore = false)
		{
			if(!ignore)
			{
				if(m_c != MW_NULL)
					delete []m_c;
				m_c = MW_NULL;
				m_size = m_nrOfCell = m_nrOfElementsInCell = 0;
			}
		}
		/*****************************************************************************/
		bool Alloc()// called after constructor
		{
			// INIT
			for(unsigned int i = 0; i < m_nrOfCell; i++)
			{
				bool test = m_c[i].Alloc(m_size - i*m_nrOfElementsInCell > m_nrOfElementsInCell ? m_nrOfElementsInCell : m_size - i*m_nrOfElementsInCell);
				if(test == false)
					return false;
			}
			return true;
		}
		/*****************************************************************************/
		mwCell<T>* m_c;
		unsigned int m_size;
		unsigned int m_nrOfCell;
		unsigned int m_nrOfElementsInCell;
		/*****************************************************************************/
	};//end class mwRopeVector
}//end namespace post
//#############################################################################
#endif	//	MW_MWROPEVECTOR_HPP_
