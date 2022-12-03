// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWOCTAGONALTURNINGTOOL_HPP_
#define MW_MWOCTAGONALTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwOctagonalTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwOctagonalTurningTool> Ptr;

	explicit mwOctagonalTurningTool(const Units units = Units::METRIC);

	mwOctagonalTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter);

	double GetInscribedCircleDiameter() const;

	double GetCornerRadius() const;

	mwOctagonalTurningTool(const mwOctagonalTurningTool& src);

	const mwOctagonalTurningTool& operator=(const mwOctagonalTurningTool& src);

	bool operator==(const mwOctagonalTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_inscribedCircleDiameter;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwOctagonalTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWOCTAGONALTURNINGTOOL_HPP_
