// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSQUARETURNINGTOOL_HPP_
#define MW_MWSQUARETURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
/// @class mwSquareTurningTool
/// Represents the lathe tool with a square-shaped insert.
class MW_5AXUTIL_API mwSquareTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwSquareTurningTool> Ptr;

	explicit mwSquareTurningTool(const Units units = Units::METRIC);

	/// @param holder is the holder to be used.
	/// @param insertThickness is the thickness of an insert.
	/// @param cornerRadius is the corner radius at the tip.
	/// @param inscribedCircleDiameter is the diameter of a circle inscribed into an insert.
	mwSquareTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter);

	double GetCornerRadius() const;

	double GetInscribedCircleDiameter() const;

	mwSquareTurningTool(const mwSquareTurningTool& src);

	const mwSquareTurningTool& operator=(const mwSquareTurningTool& src);

	bool operator==(const mwSquareTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_inscribedCircleDiameter;
	double m_cornerRadius;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwSquareTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWSQUARETURNINGTOOL_HPP_
