// (C) 2020-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWIPOSTEDMOVESTREAM_HPP_
#define MW_MWIPOSTEDMOVESTREAM_HPP_
#include "mwDllImpExpDef.hpp"
#include <vector>

template <class PostedMoveType>
class MW_5AXUTIL_API mwIPostedMoveStream
{
public:
	virtual bool hasNext() = 0;

	virtual std::vector<PostedMoveType> getNext() = 0;
	
	virtual ~mwIPostedMoveStream(){};
};
#endif	//	MW_MWIPOSTEDMOVESTREAM_HPP_
