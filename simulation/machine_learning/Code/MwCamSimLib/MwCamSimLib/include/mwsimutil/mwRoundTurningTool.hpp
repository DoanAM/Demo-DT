// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWROUNDTURNINGTOOL_HPP_
#define MW_MWROUNDTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
/// @class mwRoundTurningTool
/// Represents the lathe tool with a round insert.
class MW_5AXUTIL_API mwRoundTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwRoundTurningTool> Ptr;

	explicit mwRoundTurningTool(const Units units = Units::METRIC);

	/// @param holder is the holder to be used.
	/// @param insertThickness is the thickness of an insert.
	/// @param diameter is the diameter of the insert.
	mwRoundTurningTool(
		const HolderDefinition& holder, const double insertThickness, const double diameter);

	double GetDiameter() const;

	mwRoundTurningTool(const mwRoundTurningTool& src);

	const mwRoundTurningTool& operator=(const mwRoundTurningTool& src);

	bool operator==(const mwRoundTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_diameter;

	virtual void DoScale(const Units units, const double scaleFactor);

	void ValidateDiameter(const double diameter) const;

	void Copy(const mwRoundTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWROUNDTURNINGTOOL_HPP_
