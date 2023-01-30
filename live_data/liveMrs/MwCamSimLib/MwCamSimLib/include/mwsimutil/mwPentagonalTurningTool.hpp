// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPENTAGONALTURNINGTOOL_HPP_
#define MW_MWPENTAGONALTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwPentagonalTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwPentagonalTurningTool> Ptr;

	explicit mwPentagonalTurningTool(const Units units = Units::METRIC);

	mwPentagonalTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter);

	double GetInscribedCircleDiameter() const;

	double GetCornerRadius() const;

	mwPentagonalTurningTool(const mwPentagonalTurningTool& src);

	const mwPentagonalTurningTool& operator=(const mwPentagonalTurningTool& src);

	bool operator==(const mwPentagonalTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_inscribedCircleDiameter;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwPentagonalTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWPENTAGONALTURNINGTOOL_HPP_
