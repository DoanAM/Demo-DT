// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DCLOSEDCONTOUR_HPP_
#define MW_MW2DCLOSEDCONTOUR_HPP_
#include "mw2dContour.hpp"


namespace cadcam
{
/// Class holding a ClosedContour, an array of mw2dGeometry objects
///
/// Please use mw2dContour instead of mw2dClosedContour.
///    See details in case mw73520
template <class T>
class MW_5AXUTIL_API mw2dClosedContour: public mw2dContour<T>
{
public:
	typedef misc::mwAutoPointer<mw2dClosedContour<T>> Ptr;
	/// Constructor
	inline mw2dClosedContour();

	/// Copy constructor
	///
	/// Creates an exact copy of the Contour
	///   @param toCopy Contour to create a copy of
	inline mw2dClosedContour(const mw2dContour<T>& toCopy);

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	inline virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const;

	/// Returns true if start point and and point are equal.
	inline bool IsFinished();

	/// Closes this contour by line, if this contour is not finished.
	inline void Finish();

	inline virtual ~mw2dClosedContour();
};

template <class T>
inline mw2dClosedContour<T>::mw2dClosedContour()
{
}

template <class T>
inline mw2dClosedContour<T>::mw2dClosedContour(const mw2dContour<T>& toCopy): mw2dContour<T>(toCopy)
{
}

template <class T>
inline void mw2dClosedContour<T>::AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const
{
	visitor.Visit(*this);
}

template <class T>
inline bool mw2dClosedContour<T>::IsFinished()
{
	return this->GetStartPoint() == this->GetEndPoint();
}

template <class T>
inline void mw2dClosedContour<T>::Finish()
{
	if (!IsFinished())
	{
		this->Add(new mw2dLine<T>(this->GetEndPoint(), this->GetStartPoint()));
	}
}

template <class T>
inline mw2dClosedContour<T>::~mw2dClosedContour()
{
}
}  // namespace cadcam
#endif  //	MW_MW2DCLOSEDCONTOUR_HPP_
