// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGROOVETURNINGTOOL_HPP_
#define MW_MWGROOVETURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"


namespace cadcam
{
class MW_5AXUTIL_API mwGrooveTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;
	typedef misc::mwAutoPointer<mwGrooveTurningTool> Ptr;

	enum Type
	{
		TYPE_A = 0,
		TYPE_B = 1,
		TYPE_C = 2,
		TYPE_D = 3,
		TYPE_E = 4
	};

	explicit mwGrooveTurningTool(const Units units = Units::METRIC);

	mwGrooveTurningTool(const Type type, const Units units);

	mwGrooveTurningTool(
		const HolderDefinition& holder,
		const double insertThickness,
		const Type type,
		const double cornerRadius,
		const double a,
		const double b,
		const double c,
		const double d,
		const double e);

	Type GetType() const;

	double GetCornerRadius() const;

	double GetA() const;

	double GetB() const;

	double GetC() const;

	double GetD() const;

	double GetE() const;


	mwGrooveTurningTool(const mwGrooveTurningTool& src);

	const mwGrooveTurningTool& operator=(const mwGrooveTurningTool& src);

	bool operator==(const mwGrooveTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	Type m_type;
	double m_cornerRadius;
	double m_a;
	double m_b;
	double m_c;
	double m_d;
	double m_e;

	virtual void DoScale(const Units units, const double scaleFactor);

	void ValidateGrooveType(const Type type) const;

	void ValidateLinearParameter(const double parameter) const;

	void ValidateAngleE(const double parameter) const;

	void ValidateParams(const Type type) const;

	void SetDefaults(const Type type);

	void Copy(const mwGrooveTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWGROOVETURNINGTOOL_HPP_
