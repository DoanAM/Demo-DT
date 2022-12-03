// (C) 2015 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHDIFFERENCEMARKER_HPP_
#define MW_MWTOOLPATHDIFFERENCEMARKER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMoveMarker.hpp"
#include "mwMoveMarkerVisitor.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwToolPathDifferenceMarker: public mwMoveMarker
{
public:
	virtual ~mwToolPathDifferenceMarker() {}

	virtual void AcceptVisitor(mwMoveMarkerVisitor& visitor) const { visitor.Visit(*this); }

	virtual mwMoveMarker* Clone() const { return new mwToolPathDifferenceMarker(); }
};

}  // namespace cadcam
#endif  //	MW_MWTOOLPATHDIFFERENCEMARKER_HPP_
