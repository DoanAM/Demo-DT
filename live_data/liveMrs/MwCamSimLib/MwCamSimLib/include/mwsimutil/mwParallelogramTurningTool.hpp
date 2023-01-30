// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPARALLELOGRAMTURNINGTOOL_HPP_
#define MW_MWPARALLELOGRAMTURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwParallelogramTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwParallelogramTurningTool> Ptr;

	explicit mwParallelogramTurningTool(const Units units = Units::METRIC);

	mwParallelogramTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const double cornerRadius,
		const double formAngle,
		const double width,
		const double length);

	double GetCornerRadius() const;

	double GetFormAngle() const;

	double GetWidth() const;

	double GetLength() const;


	mwParallelogramTurningTool(const mwParallelogramTurningTool& src);

	const mwParallelogramTurningTool& operator=(const mwParallelogramTurningTool& src);

	bool operator==(const mwParallelogramTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	double m_cornerRadius;
	double m_formAngle;
	double m_width;
	double m_length;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwParallelogramTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWPARALLELOGRAMTURNINGTOOL_HPP_
