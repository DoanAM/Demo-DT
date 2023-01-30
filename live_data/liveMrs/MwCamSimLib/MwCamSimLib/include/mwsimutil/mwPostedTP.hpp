// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
/// Posted tool path positions

//#############################################################################

#ifndef MW_MWPOSTEDTP_HPP_
#define MW_MWPOSTEDTP_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
#include <list>
#include "mwDllImpExpDef.hpp"
#include "mwToolpathAlignment.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a posted tool path.
	class MW_5AXUTIL_API mwPostedTP
	{
	public:
		//#############################################################################
		typedef mwToolpathAlignment::mwMatrix4d    mwMatrix4d;
		typedef mwToolpathAlignment::mwMatrix4dPtr mwMatrix4dPtr;
		//#############################################################################
		//!List of posted moves
		typedef std::list< mwPostedMovePtr >	     postedTPList;
		//!Iterator of posted moves list.
		typedef postedTPList::iterator		         iterator;
		//!Const iterator of posted moves list.
		typedef postedTPList::const_iterator	     const_iterator;
		//!Reverse iterator of posted moves list.
		typedef postedTPList::reverse_iterator       reverse_iterator;
		//!Reverse const iterator of posted moves list.
		typedef postedTPList::const_reverse_iterator const_reverse_iterator;
		//#############################################################################
		virtual ~mwPostedTP() = default;
		//#############################################################################
		//! Get number of elements
		virtual size_t GetNrOfItems() const;
		//#############################################################################
		//!Begin of the list.
		/*!Begin of posted moves list 
			\returns a const bidirectional iterator that points at the first element 
			of the sequence (or just beyond the end of an empty sequence).
		*/
		virtual const_iterator begin() const;
		//#############################################################################
		//!Begin of the list.
		/*!Begin of posted moves list
			\returns a const bidirectional reverse iterator that points at the first element
			of the sequence (or just beyond the end of an empty sequence).
		*/
		virtual const_reverse_iterator rbegin() const;
		//#############################################################################
		//!Begin of the list.
		/*!Begin of posted moves list 
			\returns a bidirectional iterator that points at the first element 
			of the sequence (or just beyond the end of an empty sequence).
		*/
		virtual iterator begin();
		//#############################################################################
		//!Begin of the list.
		/*!Begin of posted moves list
			\returns a bidirectional reverse iterator that points at the first element
			of the sequence (or just beyond the end of an empty sequence).
		*/
		virtual reverse_iterator rbegin();
		//#############################################################################
		//!End of the list.
		/*!End of posted moves list 
			\returns returns a const bidirectional iterator that points just beyond 
			the end of the sequence.
		*/
		virtual const_iterator end() const;
		//#############################################################################
		//!End of the list.
		/*!End of posted moves list
			\returns returns a const bidirectional reverse iterator that points just beyond
			the end of the sequence.
		*/
		virtual const_reverse_iterator rend() const;
		//#############################################################################
		//!End of the list.
		/*!End of posted moves list 
			\returns returns a const bidirectional iterator that points just beyond 
			the end of the sequence.
		*/
		virtual iterator end();
		//#############################################################################
		//!End of the list.
		/*!End of posted moves list
			\returns returns a const bidirectional reverse iterator that points just beyond
			the end of the sequence.
		*/
		virtual reverse_iterator rend();
		//#############################################################################
		//!Insert to the list.
		/*!Inserts a single element with value elem to the list of posted moves list.
			\param it is a bidirectional iterator that points at an element of the list.
			\param elem const reference to a posted move.
			\returns an iterator that points to the newly inserted element.
		*/
		virtual iterator insert(mwPostedTP::iterator it, const mwPostedMovePtr& elem);
		//#############################################################################
		//!Insert to the list.
		/*!Inserts a single element with value elem to the list of posted moves list.
			\param it is a bidirectional reverse iterator that points at an element of the list.
			\param elem const reference to a posted move.
			\returns an iterator that points to the newly inserted element.
		*/
		virtual reverse_iterator insert(mwPostedTP::reverse_iterator it, const mwPostedMovePtr& elem);
		//#############################################################################
		//!Push back to the list
		/*!Push back inserts an element with value elem at the end of the posted moves
			\param elem const reference to a posted move.
		*/
		virtual void push_back(const mwPostedMovePtr& elem); 
		//#############################################################################
		//!Get machine min values
		/*!Gets the machine point of origin in the globale coordinate system
			\returns list of posted move elements
		*/
		virtual std::vector<double>	GetMachMinVals( ) const;
		//#############################################################################
		//!Get machine max values
		/*!Gets the machine max values in the globale coordinate system
			\returns list of posted move elements
		*/
		virtual std::vector<double>	GetMachMaxVals( ) const;
		//#############################################################################
		//!Get min relative part values
		/*!Gets the min relative part values in the globale coordinate system
			\returns list of posted move elements
		*/
		virtual std::vector<double>	GetPartMinVals( ) const;
		//#############################################################################
		//!Get max relative part position
		/*!Gets the max relative part position in the globale coordinate system
			\returns list of posted move elements
		*/
		virtual std::vector<double>	GetPartMaxVals( ) const;
		//#############################################################################
		//! Equality operator
		/*! Are given postedTPVec objects equal?
			\param toCompare postedTPVec object to compare the current object with
			\returns true  if both postedTPVec objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwPostedTP& toCompare) const;
		//#############################################################################
		void Clear();
		//#############################################################################
		const mwMatrix4dPtr GetAlignMatrix() const; 
		//#############################################################################
		void SetAlignMatrix(const mwMatrix4dPtr& matrixPtr);
		//#############################################################################
		bool IsAlignMatrixValide() const;
		//#############################################################################
	private:
		//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		postedTPList	  mPostedTP;
		mwMatrix4dPtr     m_MatrixPtr;
#pragma warning(pop)
		//#############################################################################
	};
};
#endif	//	MW_MWPOSTEDTP_HPP_
