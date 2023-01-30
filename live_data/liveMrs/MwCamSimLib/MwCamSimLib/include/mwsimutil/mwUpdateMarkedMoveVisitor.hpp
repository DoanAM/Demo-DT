// (C) 2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef _UPDATE_MARKED_MOVE_VISITOR_HPP_
#define _UPDATE_MARKED_MOVE_VISITOR_HPP_

#include "mw3dPolyLineComparer.hpp"
#include "mwCNCMove.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwUpdateMarkedMoveVisitor: public cadcam::mwCNCMoveVisitorSetter
{
public:
	mwUpdateMarkedMoveVisitor(const mwPolyLineSnakeCompare::DifferenceType differenceType);
	virtual void Visit(mw5axMarkedMove& move);
	inline bool GetUpdatedMove() const { return m_updatedMove; }

private:
	virtual void Default();
	void MoveWasUpdated();
	mwUpdateMarkedMoveVisitor& operator=(const mwUpdateMarkedMoveVisitor&);  // = delete

	const mwPolyLineSnakeCompare::DifferenceType m_differenceType;
	bool m_updatedMove;
};
}  // namespace cadcam

#endif  //_UPDATE_MARKED_MOVE_VISITOR_HPP_
