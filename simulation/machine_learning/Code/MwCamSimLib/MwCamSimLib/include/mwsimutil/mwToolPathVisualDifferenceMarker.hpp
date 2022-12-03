// (C) 2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHVISUALDIFFERENCEMARKER_HPP_
#define MW_MWTOOLPATHVISUALDIFFERENCEMARKER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMoveMarker.hpp"
#include "mwMoveMarkerVisitor.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwToolPathVisualDifferenceMarker: public mwMoveMarker
{
public:
	virtual ~mwToolPathVisualDifferenceMarker() {}

	virtual void AcceptVisitor(mwMoveMarkerVisitor& visitor) const { visitor.Visit(*this); }

	virtual mwMoveMarker* Clone() const { return new mwToolPathVisualDifferenceMarker(); }
};

}  // namespace cadcam
#endif  //	MW_MWTOOLPATHVISUALDIFFERENCEMARKER_HPP_
