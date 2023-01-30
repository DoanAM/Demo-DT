// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVEMARKERVISITOR_HPP_
#define MW_MWMOVEMARKERVISITOR_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwMoveMarker.hpp"

namespace cadcam
{
class mwToolPathDifferenceMarker;
class mwToolPathVisualDifferenceMarker;
class mwToolPathDifferentPositionMarker;
class mwToolPathDifferentOrientationMarker;

class MW_5AXUTIL_API mwMoveMarkerVisitor
{
public:
	virtual ~mwMoveMarkerVisitor() {}

	virtual void Visit(const mwMoveMarker&) {}

	virtual void Visit(const mwToolPathDifferenceMarker&) {}

	virtual void Visit(const mwToolPathVisualDifferenceMarker&) {}

	virtual void Visit(const mwToolPathDifferentPositionMarker&) {}

	virtual void Visit(const mwToolPathDifferentOrientationMarker&) {}
};

}  // namespace cadcam
#endif  //	MW_MWMOVEMARKERVISITOR_HPP_
