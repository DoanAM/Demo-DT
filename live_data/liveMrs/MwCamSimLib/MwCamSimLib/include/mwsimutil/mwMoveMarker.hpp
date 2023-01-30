// (C) 2015 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVEMARKER_HPP_
#define MW_MWMOVEMARKER_HPP_
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
class mwMoveMarkerVisitor;

class MW_5AXUTIL_API mwMoveMarker
{
public:
	virtual ~mwMoveMarker() {}

	virtual void AcceptVisitor(mwMoveMarkerVisitor& visitor) const = 0;
	virtual mwMoveMarker* Clone() const = 0;
};

}  // namespace cadcam
#endif  //	MW_MWMOVEMARKER_HPP_
