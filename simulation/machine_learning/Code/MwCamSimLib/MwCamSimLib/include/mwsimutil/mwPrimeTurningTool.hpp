// (C) 2016-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPRIMETURNINGTOOL_HPP_
#define MW_MWPRIMETURNINGTOOL_HPP_

#include "mwDefines.hpp"
#ifndef MW_USE_VS2008_COMPATIBILITY

#include "mw2dContour.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"

namespace cadcam
{
/// @class mwPrimeTurningTool
/// Represents the prime turning tool with a triangle or a diamand shaped insert
class MW_5AXUTIL_API mwPrimeTurningTool: public mwTypedExtrudedTool
{
public:
	typedef misc::mwAutoPointer<mwPrimeTurningTool> Ptr;
	typedef mw2dContour<double> Contour2d;

	/// Defines supported types of prime tool
	enum Type
	{
		TYPE_A,		///< a triangle shaped insert.
		TYPE_B		///< a diamond shaped insert.
	};

	/// Defines supported corner radiuses
	enum CornerRadius
	{
		CR_04,		///< Corner radius is 0.4 mm. Supported by both types A and B.
		CR_08		///< Corner radius is 0.8 mm. Supported by only type B.
	};

	/// Defines supported chip breakers
	enum ChipBreaker
	{
		CB_L3,
		CB_L3W,
		CB_L4,
		CB_L4W,
		CB_L5,
		CB_L5W,
		CB_H3,
		CB_H3W,
		CB_M5,
		CB_M5W
	};

	/// Defines supported chip breakers
	enum GradeCode
	{
		GC_1115,
		GC_2025,
		GC_4415,
		GC_4425,
		GC_X_4415,
		GC_X_4425,
		GC_H13A,
	};

	explicit mwPrimeTurningTool(const Units units = Units::METRIC);

	mwPrimeTurningTool(
		const HolderDefinition& holder, const Type type, const CornerRadius cornerRadius);

	mwPrimeTurningTool(
		const HolderDefinition& holder,
		const Type type,
		const CornerRadius cornerRadius,
		const ChipBreaker chipBreaker,
		const GradeCode gradeCode);

	/// Returns the insert type.
	Type GetType() const;

	/// Returns the insert corner radius.
	CornerRadius GetCornerRadius() const;

	/// Returns the insert chip breaker.
	ChipBreaker GetChipBreaker() const;

	GradeCode GetGradeCode() const;

	/// Returns Kapr current value.
	double GetKapr() const;

	/// Returns the insert contour.
	const Contour2d& GetInsert() const;

	mwPrimeTurningTool(const mwPrimeTurningTool& src);

	const mwPrimeTurningTool& operator=(const mwPrimeTurningTool& src);

	bool operator==(const mwPrimeTurningTool& toCompare) const;

	/// Implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	Type m_type;
	CornerRadius m_cornerRadius;
	ChipBreaker m_chipBreaker;
	GradeCode m_gradeCode;
	Contour2d m_insert;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwPrimeTurningTool& copy);
};
}  // namespace cadcam
#endif
#endif  //	MW_MWPRIMETURNINGTOOL_HPP_
