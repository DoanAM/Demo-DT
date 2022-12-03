// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWHEXAGONALTURNINGTOOL_HPP_
#define MW_MWHEXAGONALTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwHexagonalTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwHexagonalTurningTool> Ptr;

	explicit mwHexagonalTurningTool(const Units units = Units::METRIC);

	mwHexagonalTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter);

	double GetInscribedCircleDiameter() const;

	double GetCornerRadius() const;

	mwHexagonalTurningTool(const mwHexagonalTurningTool& src);

	const mwHexagonalTurningTool& operator=(const mwHexagonalTurningTool& src);

	bool operator==(const mwHexagonalTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_inscribedCircleDiameter;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwHexagonalTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWHEXAGONALTURNINGTOOL_HPP_
