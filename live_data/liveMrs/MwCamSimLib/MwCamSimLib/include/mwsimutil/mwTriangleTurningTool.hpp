// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTRIANGLETURNINGTOOL_HPP_
#define MW_MWTRIANGLETURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
/// @class mwTriangleTurningTool
/// Represents the lathe tool with a triangle-shaped insert
class MW_5AXUTIL_API mwTriangleTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwTriangleTurningTool> Ptr;

	explicit mwTriangleTurningTool(const Units units = Units::METRIC);
	/// @param holder is the holder to be used.
	/// @param insertThickness is the thickness of an insert.
	/// @param cornerRadius is the corner radius at the tip.
	/// @param inscribedCircleDiameter is the diameter of a circle inscribed into an insert.
	mwTriangleTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter);

	double GetInscribedCircleDiameter() const;

	double GetCornerRadius() const;

	mwTriangleTurningTool(const mwTriangleTurningTool& src);

	const mwTriangleTurningTool& operator=(const mwTriangleTurningTool& src);

	bool operator==(const mwTriangleTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_inscribedCircleDiameter;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwTriangleTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWTRIANGLETURNINGTOOL_HPP_
