// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DCLOSEDCONTOUR_HPP_
#define MW_MW3DCLOSEDCONTOUR_HPP_
#include "mw3dContour.hpp"


namespace cadcam
{
/// Class holding a ClosedContour, an array of mw3dGeometry objects
///
/// Please use mw3dContour instead of mw3dClosedContour.
/// See details in case mw73520
template <class T>
class MW_5AXUTIL_API mw3dClosedContour: public mw3dContour<T>
{
public:
	typedef misc::mwAutoPointer<mw3dClosedContour<T>> Ptr;
	/// Constructor
	mw3dClosedContour(): mw3dContour<T>() {}

	/// Copy constructor
	///
	/// Creates an exact copy of the Contour
	///	@param toCopy Contour to create a copy of
	mw3dClosedContour(const mw3dContour<T>& toCopy): mw3dContour<T>(toCopy) {}

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

	/// Returns true if start point and and point are equal.
	bool IsFinished() { return this->GetStartPoint() == this->GetEndPoint(); }

	/// Closes this contour by line, if this contour is
	/// not finished.
	void Finish()
	{
		if (!IsFinished())
		{
			Add(new mw3dLine<T>(this->GetEndPoint(), this->GetStartPoint()));
		}
	}

	/// Destructor
	virtual ~mw3dClosedContour() {}
};
}  // namespace cadcam
#endif  //	MW_MW3DCLOSEDCONTOUR_HPP_
