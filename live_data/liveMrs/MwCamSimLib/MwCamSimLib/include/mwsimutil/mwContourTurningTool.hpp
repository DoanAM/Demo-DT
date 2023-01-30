// (C) 2016-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCONTOURTURNINGTOOL_HPP_
#define MW_MWCONTOURTURNINGTOOL_HPP_
#include "mw2dContour.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwContourTurningTool: public mwTypedExtrudedTool
{
public:
	typedef misc::mwAutoPointer<mwContourTurningTool> Ptr;
	typedef mw2dContour<double> Contour2d;

	explicit mwContourTurningTool(const Units units = Units::METRIC);

	mwContourTurningTool(
		const HolderDefinition& holder, const Contour2d& insert, const double insertThickness);

	const Contour2d& GetInsert() const;

	mwContourTurningTool(const mwContourTurningTool& src);

	const mwContourTurningTool& operator=(const mwContourTurningTool& src);

	bool operator==(const mwContourTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	Contour2d m_insert;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwContourTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWCONTOURTURNINGTOOL_HPP_
