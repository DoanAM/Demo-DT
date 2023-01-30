// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWDIAMONDTURNINGTOOL_HPP_
#define MW_MWDIAMONDTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
/// @class mwDiamondTurningTool
/// Represents the lathe tool with a diamond-shaped insert.
class MW_5AXUTIL_API mwDiamondTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;

	typedef misc::mwAutoPointer<mwDiamondTurningTool> Ptr;

	explicit mwDiamondTurningTool(const Units units = Units::METRIC);

	/// @param holder is the holder to be used.
	/// @param insertThickness is the thickness of an insert.
	/// @param cornerRadius is the corner radius at the tip.
	/// @param inscribedCircleDiameter is the diameter of a circle inscribed into an insert.
	/// @param formAngle is the diamond angle at the tip.
	mwDiamondTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter,
		const double formAngle);

	double GetCornerRadius() const;

	double GetInscribedCircleDiameter() const;

	double GetFormAngle() const;


	mwDiamondTurningTool(const mwDiamondTurningTool& src);

	const mwDiamondTurningTool& operator=(const mwDiamondTurningTool& src);

	bool operator==(const mwDiamondTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_inscribedCircleDiameter;
	double m_formAngle;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwDiamondTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWDIAMONDTURNINGTOOL_HPP_
