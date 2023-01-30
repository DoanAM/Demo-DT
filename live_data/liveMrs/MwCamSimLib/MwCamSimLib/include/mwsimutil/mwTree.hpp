// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTREE_HPP_
#define MW_MWTREE_HPP_
#include <list>
#include <stack>
#include "mwDllImpExpDef.hpp"

#include "mwAvoid_Warnings.hpp"

namespace misc
{
	template <class T> class mwTreeOverallIterator;
	template <class T> class mwTreeConstOverallIterator;
	template <class T> class mwTreeSiblingIterator;
	template <class T> class mwTreeConstSiblingIterator;
	template <class T> class mwTreeChildIterator;
	template <class T> class mwTreeConstChildIterator;
	template <class T> class mwTree;

	template <class T> class MW_5AXUTIL_API mwTreeNode
	{
		public:
			typedef mwTreeNode<T>						node;
			typedef std::list< node *>					childrenList;
			typedef mwTreeChildIterator<T>				childrenIterator;
			typedef mwTreeConstChildIterator<T>			constChildrenIterator;
			typedef mwTreeSiblingIterator<T>			siblingIterator;
			typedef mwTreeConstSiblingIterator<T>		constSiblingIterator;
			typedef mwTreeOverallIterator<T>			overallIterator;
			typedef mwTreeConstOverallIterator<T>		constOverallIterator;
			typedef childrenIterator					nodeID;
		private:
			typedef typename childrenList::iterator				ci;
			typedef typename childrenList::const_iterator		cci;
			friend class mwTreeOverallIterator<T>;
			friend class mwTreeConstOverallIterator<T>;
			friend class mwTreeSiblingIterator<T>;
			friend class mwTreeConstSiblingIterator<T>;
			friend class mwTreeChildIterator<T>;
			friend class mwTreeConstChildIterator<T>;
		public:


			mwTreeNode()
				:mParent( 0 )
			{
			};


			mwTreeNode( const T &element )
				:mParent( 0 ), mElement( element )
			{
			};


			//copy constructor
			mwTreeNode( const mwTreeNode& tocopy )
			{
				//these children are deleted at destruction time, so
				//we need to comment this for now
				//mChildren = tocopy.mChildren;

				mElement = tocopy.mElement;
				mParent = tocopy.mParent;
				mThisNode = tocopy.mThisNode;
			};


			virtual ~mwTreeNode()
			{
				ci It;
				ci End( mChildren.end() );

				for( It = mChildren.begin(); It != End; It++ )
					delete *It;
			};


			childrenIterator GetChildrenBegin()
			{
				return childrenIterator( mChildren.begin() );
			};


			constChildrenIterator GetChildrenBegin() const
			{
				return constChildrenIterator( mChildren.begin() );
			};


			childrenIterator GetChildrenEnd()
			{
				return mChildren.end();
			};


			constChildrenIterator GetChildrenEnd() const
			{
				return mChildren.end();
			};


			siblingIterator GetSiblingsBegin()
			{
				mwTreeNode<T> *parent = GetParent();

				if( !parent )
					return siblingIterator();

				else
					return siblingIterator( parent->GetChildrenBegin(),
					GetThisNode() );
			};


			constSiblingIterator GetSiblingsBegin() const
			{
				const mwTreeNode<T> *parent = GetParent();

				if( !parent )
					return constSiblingIterator();

				else
					return constSiblingIterator( parent->GetChildrenBegin(),
					GetThisNode() );
			};


			siblingIterator GetSiblingsEnd()
			{
				mwTreeNode<T> *parent = GetParent();

				if( !parent )
					return siblingIterator();

				else
					return siblingIterator( parent->GetChildrenEnd(),
					GetThisNode() );
			};


			constSiblingIterator GetSiblingsEnd() const
			{
				const mwTreeNode<T> *parent = GetParent();

				if( !parent )
					return constSiblingIterator();

				else
					return constSiblingIterator( parent->GetChildrenEnd(),
					GetThisNode() );
			};


			overallIterator GetOverallBegin()
			{
				return overallIterator( &mChildren, mChildren.begin() );
			}


			constOverallIterator GetOverallBegin() const
			{
			}


			overallIterator GetOverallEnd()
			{
				return overallIterator( &mChildren, mChildren.end() );
			}


			constOverallIterator GetOverallEnd() const
			{
			}


			nodeID AddChild( const mwTreeNode &child )
			{
				ci _inserted = mChildren.insert( mChildren.end(),
					new mwTreeNode( child ) );
				(*_inserted)->SetParent( this );
				(*_inserted)->SetThisNode( _inserted );

				return nodeID( _inserted );
			};


			void RemoveChild( const nodeID &toRemove )
			{
				nodeID _del( toRemove );
				delete _del.operator->();
				mChildren.erase( _del.mIt );
			};


			void Reset()
			{
				ci It;
				ci End( mChildren.end() );

				for( It = mChildren.begin(); It != End; It++ )
					delete *It;

				mChildren.clear();
			};


			T &GetElement()
			{
				return mElement;
			};


			const T &GetElement() const
			{
				return mElement;
			};


			void SetElement( const T &element )
			{
				mElement = element;
			};


			mwTreeNode *GetParent()
			{
				return mParent;
			};


			const mwTreeNode *GetParent() const
			{
				return mParent;
			};


		protected:


			void SetParent( mwTreeNode *parent )
			{
				mParent = parent;
			};


			ci &GetThisNode()
			{
				return mThisNode;
			};


			const ci &GetThisNode() const
			{
				return mThisNode;
			};


			void SetThisNode( ci &tn )
			{
				mThisNode = tn;
			};

			childrenList		mChildren;
			T					mElement;
			mwTreeNode			*mParent;
			ci					mThisNode;

		private:

			friend class mwTree<T>;
	};

	template <class T> class MW_5AXUTIL_API mwTree : private mwTreeNode<T>
	{
		public:
			//Tavi - to discuss this function with Alex
			const mwTree& operator = (const mwTree& toCopy)
			{
				if (this != &toCopy)
				{

					Copy(toCopy);
				}

				return *this;
			}

			mwTree(const mwTree& toCopy)
			{
				Copy(toCopy);
			}

			mwTree()
			{
				this->Reset();
			}

			const bool Empty() const
			{
				return GetElementsBegin() == GetElementsEnd();
			}


			const typename misc::mwTreeNode<T>::nodeID AddElement( const T &toAdd )
			{
				return this->AddChild( toAdd );
			};


			const typename misc::mwTreeNode<T>::nodeID AddElement( const T &toAdd, typename misc::mwTreeNode<T>::nodeID &parentElement )
			{
				return parentElement->AddChild( toAdd );
			};


			void RemoveElement( typename misc::mwTreeNode<T>::nodeID &toRemove )
			{
				mwTreeNode<T> *parentNode = toRemove->GetParent();

				if( parentNode )
					parentNode->RemoveChild( toRemove );
				else
					this->RemoveChild( toRemove );
			};


			void Reset()
			{
				mwTreeNode<T>::Reset();
			};


			typename misc::mwTreeNode<T>::childrenIterator GetElementsBegin()
			{
				return this->GetChildrenBegin();
			};


			typename misc::mwTreeNode<T>::constChildrenIterator GetElementsBegin() const
			{
				return this->GetChildrenBegin();
			};


			typename misc::mwTreeNode<T>::childrenIterator GetElementsEnd()
			{
				return this->GetChildrenEnd();
			};


			typename misc::mwTreeNode<T>::constChildrenIterator GetElementsEnd() const
			{
				return this->GetChildrenEnd();
			};


			typename misc::mwTreeNode<T>::overallIterator GetOverallElementsBegin()
			{
				return this->GetOverallBegin( );
			};


			typename misc::mwTreeNode<T>::constOverallIterator GetOverallElementsBegin() const
			{
				return this->GetOverallBegin();
			}


			typename misc::mwTreeNode<T>::overallIterator GetOverallElementsEnd()
			{
				return this->GetOverallEnd();
			};


			typename misc::mwTreeNode<T>::constOverallIterator GetOverallElementsEnd() const
			{
				this->GetOverallEnd();
			};

		protected:
		private:

	void Copy(const mwTree& toCopy)
	{
		this->Reset();

		if(!toCopy.Empty())
		{
			typename misc::mwTreeNode<T>::constChildrenIterator toCopyNodeChildIt =  toCopy.GetElementsBegin();
			typename misc::mwTreeNode<T>::constChildrenIterator toCopyNodeChildItEnd =  toCopy.GetElementsEnd();

			for ( ; toCopyNodeChildIt != toCopyNodeChildItEnd ; ++toCopyNodeChildIt)
			{
				typename misc::mwTreeNode<T>::childrenIterator myNodeIt = AddElement(toCopyNodeChildIt->GetElement());
				CloneTree(toCopyNodeChildIt, myNodeIt);
			}
		}
	}
	
	void CloneTree (typename misc::mwTreeNode<T>::constChildrenIterator toCopyNodeIt,
		typename misc::mwTreeNode<T>::childrenIterator myNodeIt)
	{
		if ( Empty() ) // this tree is empty
		{
			// ASSERT use Copy method instead!!
			return;
		}

		typename misc::mwTreeNode<T>::constChildrenIterator toCopyNodeChildIt =  toCopyNodeIt->GetChildrenBegin();
		typename misc::mwTreeNode<T>::constChildrenIterator toCopyNodeChildItEnd =  toCopyNodeIt->GetChildrenEnd();


		for ( ; toCopyNodeChildIt != toCopyNodeChildItEnd ; ++toCopyNodeChildIt)
		{
			typename misc::mwTreeNode<T>::childrenIterator myChildNodeIt = AddElement(toCopyNodeChildIt->GetElement(), myNodeIt);
			CloneTree(toCopyNodeChildIt, myChildNodeIt);
		}

	}

};
	template <class T> class MW_5AXUTIL_API mwTreeChildIterator
	{
		public:


			mwTreeChildIterator()
				:m_isNull(true)
			{
			};


			mwTreeNode<T> &operator*()
			{
				return *(*mIt);
			};


			const mwTreeNode<T> &operator*() const
			{
				return *(*mIt);
			};


			mwTreeNode<T>	*operator->()
			{
				return *mIt;
			};


			const mwTreeNode<T>	*operator->() const
			{
				return *mIt;
			};


			bool operator ==( const mwTreeChildIterator<T> &tc ) const
			{
				bool rtrn=false;
				if (m_isNull)
				{
					if (tc.m_isNull)
					{
						rtrn=true;
					}
				}else
				{
					if (!tc.m_isNull)
					{
						rtrn=(mIt == tc.mIt);
					}
				}
				return rtrn;
			};


			const bool operator !=( const mwTreeChildIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			const bool operator <( const mwTreeChildIterator<T> &tc ) const
			{
				return (*mIt) < (*tc.mIt);
			};


			mwTreeChildIterator &operator++()
			{
				++mIt;
				return *this;
			};


			mwTreeChildIterator operator++( int )
			{
				mwTreeChildIterator tempVal( *this );
				mIt++;
				return tempVal;
			};


			mwTreeChildIterator &operator--()
			{
				--mIt;
				return *this;
			};


			mwTreeChildIterator operator--( int )
			{
				mwTreeChildIterator tempVal( *this );
				mIt--;
				return tempVal;
			};

		protected:
		private:
			friend class mwTreeNode<T>;
			bool m_isNull;
			typedef typename mwTreeNode<T>::ci				realIt;


			mwTreeChildIterator( const realIt &ri )
				:mIt( ri ),m_isNull(false)
			{
			};

			realIt		mIt;
			friend class mwTreeConstChildIterator<T>;
	};

	template <class T> class MW_5AXUTIL_API mwTreeConstChildIterator
	{
		public:


			mwTreeConstChildIterator()
				:m_isNull(true)
			{
			};


			mwTreeConstChildIterator( const mwTreeChildIterator<T> &tc )
				:mIt( tc.mIt ), m_isNull(tc.m_isNull)
			{
			};


			const mwTreeNode<T> &operator*()
			{
				return *(*mIt);
			};


			const mwTreeNode<T>	*operator->()
			{
				return *mIt;
			};


			bool operator ==( const mwTreeConstChildIterator<T> &tc ) const
			{
				bool rtrn=false;
				if (m_isNull)
				{
					if (tc.m_isNull)
					{
						rtrn=true;
					}
				}else
				{
					if (!tc.m_isNull)
					{
						rtrn=(mIt == tc.mIt);
					}
				}
				return rtrn;
			};


			bool operator !=( const mwTreeConstChildIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			bool operator <( const mwTreeConstChildIterator<T> &tc ) const
			{
				return (*mIt) < (*tc.mIt);
			};


			mwTreeConstChildIterator &operator++()
			{
				++mIt;
				return *this;
			};


			mwTreeConstChildIterator operator++( int )
			{
				mwTreeConstChildIterator tempVal( *this );
				mIt++;
				return tempVal;
			};


			mwTreeConstChildIterator &operator--()
			{
				--mIt;
				return *this;
			};


			mwTreeConstChildIterator operator--( int )
			{
				mwTreeConstChildIterator tempVal( *this );
				mIt--;
				return tempVal;
			};

		protected:
		private:
			friend class mwTreeNode<T>;
			bool m_isNull;
			typedef typename mwTreeNode<T>::cci				realIt;


			mwTreeConstChildIterator( const realIt &ri )
				:mIt( ri ),m_isNull(false)
			{
			};

			realIt		mIt;
	};

	template <class T> class MW_5AXUTIL_API mwTreeSiblingIterator
	{
		public:


			mwTreeSiblingIterator()
			{
			};


			mwTreeNode<T> &operator*()
			{
				return *(mIt);
			};


			const mwTreeNode<T> &operator*() const
			{
				return *(mIt);
			};


			mwTreeNode<T>	*operator->()
			{
				return mIt.operator->();
			};


			const mwTreeNode<T>	*operator->() const
			{
				return mIt.operator->();
			};


			bool operator ==( const mwTreeSiblingIterator<T> &tc ) const
			{
				return mIt == tc.mIt;
			};


			bool operator !=( const mwTreeSiblingIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			bool operator <( const mwTreeSiblingIterator<T> &tc ) const
			{
				return (*mIt) < (*tc.mIt);
			};


			mwTreeSiblingIterator &operator++()
			{
				++mIt;
				if( mIt == mThisNode )
					++mIt;

				return *this;
			};


			mwTreeSiblingIterator operator++( int )
			{
				mwTreeSiblingIterator tempVal( *this );
				mIt++;
				if( mIt == mThisNode )
					mIt++;

				return tempVal;
			};


			mwTreeSiblingIterator &operator--()
			{
				--mIt;
				if( mIt == mThisNode )
					--mIt;

				return *this;
			};


			mwTreeSiblingIterator operator--( int )
			{
				mwTreeSiblingIterator tempVal( *this );
				mIt--;
				if( mIt == mThisNode )
					mIt--;

				return tempVal;
			};

		protected:
		private:

			typedef mwTreeChildIterator<T>				realIt;

			mwTreeSiblingIterator( const realIt &ri, const realIt &tn )
				:mIt( ri ), mThisNode( tn )
			{
				if( mIt == mThisNode )
					mIt++;
			};

			realIt									mIt;
			realIt									mThisNode;
			friend class mwTreeNode<T>;
			friend class mwTreeConstSiblingIterator<T>;
	};

	template <class T> class MW_5AXUTIL_API mwTreeConstSiblingIterator
	{
		public:

			mwTreeConstSiblingIterator()
			{
			};


			mwTreeConstSiblingIterator( const mwTreeSiblingIterator<T> &tc )
				:mIt( tc.mIt ), mThisNode( tc.mThisNode )
			{
			};


			const mwTreeNode<T> &operator*()
			{
				return *(mIt);
			};


			const mwTreeNode<T>	*operator->()
			{
				return mIt.operator->();
			};


			bool operator ==( const mwTreeConstSiblingIterator<T> &tc ) const
			{
				return mIt == tc.mIt && mThisNode == tc.mThisNode;
			};


			bool operator !=( const mwTreeConstSiblingIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			bool operator <( const mwTreeConstSiblingIterator<T> &tc ) const
			{
				return (*mIt) < (*tc.mIt);
			};


			mwTreeConstSiblingIterator &operator++()
			{
				++mIt;
				if( mIt == mThisNode )
					++mIt;

				return *this;
			};


			mwTreeConstSiblingIterator operator++( int )
			{
				mwTreeConstSiblingIterator tempVal( *this );
				mIt++;
				if( mIt == mThisNode )
					mIt++;

				return tempVal;
			};


			mwTreeConstSiblingIterator &operator--()
			{
				--mIt;
				if( mIt == mThisNode )
					--mIt;

				return *this;
			};


			mwTreeConstSiblingIterator operator--( int )
			{
				mwTreeConstSiblingIterator tempVal( *this );
				mIt--;
				if( mIt == mThisNode )
					mIt--;

				return tempVal;
			};

		protected:
		private:

			typedef mwTreeConstChildIterator<T>				realIt;

			mwTreeConstSiblingIterator( const realIt &ri, const realIt &tn )
				:mIt( ri ), mThisNode( tn )
			{
				if( mIt == mThisNode )
					mIt++;
			};

			realIt									mIt;
			realIt									mThisNode;
			friend class mwTreeNode<T>;
	};


	template <class T> class MW_5AXUTIL_API mwTreeOverallIterator
	{
		public:


			mwTreeOverallIterator()
			{
			};


			mwTreeNode<T> &operator*()
			{
				return *(*(mCurrentContext.contextIterator));
			};


			const mwTreeNode<T> &operator*() const
			{
				return *(*(mCurrentContext.contextIterator));
			};


			mwTreeNode<T>	*operator->()
			{
				return *(mCurrentContext.contextIterator.operator->());
			};


			const mwTreeNode<T>	*operator->() const
			{
				return *(mCurrentContext.contextIterator.operator->());
			};


			bool operator ==( const mwTreeOverallIterator<T> &tc ) const
			{
				return mCurrentContext == tc.mCurrentContext
					&& mHLContext == tc.mHLContext;
			};


			bool operator !=( const mwTreeOverallIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			mwTreeOverallIterator &operator++()
			{
				if( mCurrentContext.contextIterator !=
					mCurrentContext.contextContainer->end() )
				{
					if( (*(mCurrentContext.contextIterator))->mChildren.size() )
						PushContext(
						&(*(mCurrentContext.contextIterator))->mChildren,
						(*(mCurrentContext.contextIterator))->mChildren.begin() );
					else
					{
						mCurrentContext.contextIterator++;
						if( mCurrentContext.contextIterator ==
							mCurrentContext.contextContainer->end() )
						{
							if( mHLContext.size() )
								PopContext();
						}
					}
				}
				else
				{
					if( mHLContext.size() )
						PopContext();
				}

				return *this;
			};


			mwTreeOverallIterator operator++( int )
			{
				mwTreeOverallIterator tempVal( *this );
				++(*this);

				return tempVal;
			};

		protected:
		private:

			friend class mwTreeNode<T>;
			friend class mwTreeConstOverallIterator<T>;

			typedef typename mwTreeNode<T>::childrenList					*iList;
			typedef typename mwTreeNode<T>::childrenList::iterator		iIt;


			mwTreeOverallIterator( iList list, const iIt &newIt )
			{
				mCurrentContext.contextContainer = list;
				mCurrentContext.contextIterator = newIt;
			};

			void PushContext( iList newList, const iIt &newIt )
			{
				mCurrentContext.contextIterator++;
				mHLContext.push_back( mCurrentContext );
				mCurrentContext.contextContainer = newList;
				mCurrentContext.contextIterator = newIt;
			};

			void PopContext()
			{
				mCurrentContext = mHLContext.back();
				mHLContext.pop_back();
				if( mCurrentContext.contextIterator ==
					mCurrentContext.contextContainer->end() )
					if( mHLContext.size() )
						PopContext();
			};

			struct overallIterationContext
			{
				iList		contextContainer;
				iIt		contextIterator;

				bool operator ==( const overallIterationContext &tc )
					const
				{
					return contextContainer == tc.contextContainer
						&& contextIterator == tc.contextIterator;
				}
			};

			std::list< overallIterationContext >		mHLContext;
			overallIterationContext				mCurrentContext;
	};


	template <class T> class MW_5AXUTIL_API mwTreeConstOverallIterator
	{
		public:

			mwTreeConstOverallIterator()
			{
			};


			mwTreeConstOverallIterator( const mwTreeOverallIterator<T> &tc )
			{
				mCurrentContext.contextContainer =
					tc.mCurrentContext.contextContainer;

				mCurrentContext.contextIterator =
					tc.mCurrentContext.contextIterator;

				typename std::list< typename mwTreeOverallIterator<T>::overallIterationContext >
					::const_iterator It;
				typename std::list< typename mwTreeOverallIterator<T>::overallIterationContext >
					::const_iterator End( tc.mHLContext.end() );

				for( It = tc.mHLContext.begin(); It != End; It++ )
				{
					overallIterationContext tctxt;
					tctxt.contextContainer = It->contextContainer;
					tctxt.contextIterator = It->contextIterator;

					mHLContext.push_back( tctxt );
				}
			};


			const mwTreeNode<T> &operator*()
			{
				return *(*(mCurrentContext.contextIterator));
			};


			const mwTreeNode<T>	*operator->()
			{
				return *(mCurrentContext.contextIterator.operator->());
			};


			bool operator ==( const mwTreeConstOverallIterator<T> &tc ) const
			{
				return mCurrentContext == tc.mCurrentContext
					&& mHLContext == tc.mHLContext;
			};


			bool operator !=( const mwTreeConstOverallIterator<T> &tc ) const
			{
				return !( *this == tc );
			};


			mwTreeConstOverallIterator &operator++()
			{
				if( mCurrentContext.contextIterator !=
					mCurrentContext.contextContainer->end() )
				{
					if( (*(mCurrentContext.contextIterator))->mChildren.size() )
						PushContext(
						&(*(mCurrentContext.contextIterator))->mChildren,
						(*(mCurrentContext.contextIterator))->mChildren.begin() );
					else
					{
						mCurrentContext.contextIterator++;
						if( mCurrentContext.contextIterator ==
							mCurrentContext.contextContainer->end() )
						{
							if( mHLContext.size() )
								PopContext();
						}
					}
				}
				else
				{
					if( mHLContext.size() )
						PopContext();
				}

				return *this;
			};


			mwTreeConstOverallIterator operator++( int )
			{
				mwTreeConstOverallIterator tempVal( *this );
				++(*this);

				return tempVal;
			};

		protected:
		private:

			friend class mwTreeNode<T>;

			typedef typename mwTreeNode<T>::childrenList						*iList;
			typedef typename mwTreeNode<T>::childrenList::const_iterator		iIt;


			mwTreeConstOverallIterator( iList list, const iIt &newIt )
			{
				mCurrentContext.contextContainer = list;
				mCurrentContext.contextIterator = newIt;
			};

			void PushContext( iList newList, const iIt &newIt )
			{
				mCurrentContext.contextIterator++;
				mHLContext.push_back( mCurrentContext );
				mCurrentContext.contextContainer = newList;
				mCurrentContext.contextIterator = newIt;
			};

			void PopContext()
			{
				mCurrentContext = mHLContext.back();
				mHLContext.pop_back();
				if( mCurrentContext.contextIterator ==
					mCurrentContext.contextContainer->end() )
					if( mHLContext.size() )
						PopContext();
			};

			struct overallIterationContext
			{
				iList		contextContainer;
				iIt			contextIterator;

				const bool operator ==( const overallIterationContext &tc )
					const
				{
					return contextContainer == tc.contextContainer
						&& contextIterator == tc.contextIterator;
				}
			};

			std::list< overallIterationContext >		mHLContext;
			overallIterationContext						mCurrentContext;
	};
};
#endif	//	MW_MWTREE_HPP_
