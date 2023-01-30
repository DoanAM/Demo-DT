// (C) 2018-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DTRANSITIVEOFFSETTER_HPP_
#define MW_MW2DTRANSITIVEOFFSETTER_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"
#include <list>
#include <vector>

namespace cadcam
{
/// Class for constructing transitive offset from polyline
template <class T>
class MW_5AXUTIL_API mw2dTransitiveOffsetter
{
public:
	enum OffsetDir
	{
		LEFT,
		RIGHT
	};

	/// Constructor
	///
	/// mw2dTransitiveOffsetter inits offseter with direction and
	/// the way intersections/gaps are handled
	/// @param dir offset direction
	mw2dTransitiveOffsetter(
		const OffsetDir dir)
		: m_dir(dir)
	{
	}

	const typename mw2dContour<T>::Ptr Offset(
		const mw2dPolyLine<T>& src,
		const T lowerOffset,
		const T upperOffset,
		const bool selectPozitiveOffsets = true);

private:
	OffsetDir m_dir;
};  // class mw2dTransitiveOffsetter
}  // namespace cadcam
#endif	//	MW_MW2DTRANSITIVEOFFSETTER_HPP_
