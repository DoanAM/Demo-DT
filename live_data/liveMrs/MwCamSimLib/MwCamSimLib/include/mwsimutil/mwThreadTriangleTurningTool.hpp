// (C) 2013-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTHREADTRIANGLETURNINGTOOL_HPP_
#define MW_MWTHREADTRIANGLETURNINGTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwUnitsFactory.hpp"

namespace cadcam
{
/// @class mwThreadTriangleTurningTool
/// Represents the thread lathe tool with a triangle-shaped insert
class MW_5AXUTIL_API mwThreadTriangleTurningTool: public mwTypedExtrudedTool
{
public:
	using mwExtrudedTool::AcceptVirtual;

	typedef misc::mwAutoPointer<mwThreadTriangleTurningTool> Ptr;

	/// Defines supported types of thread
	enum Type
	{
		TP_METRIC_ISO,  ///< Metric ISO 60 degrees
		TP_UNIFIED_THREAD_STANDARD,  ///< Unified thread standard
		TP_UNF_UNC,  ///< UNF UNC 60 degrees
		TP_BRITISH_STANDARD_WHITWORTH  ///< British standard whitworth
	};

	explicit mwThreadTriangleTurningTool(const Units units = Units::METRIC);

	/// @param holder is the holder to be used.
	/// @param type is the thread type to be used.
	/// @param insertThickness is the thickness of an insert.
	/// @param cornerRadius is the value of insert's corner radius
	/// @param inscribedCircleDiameter is the diameter is determined by placing a circle
	/// 		in the insert shape and measuring the circle's diameter.
	/// @param includedAngle is the value of the angle between sides of a thread/insert
	/// 		measured in an axial plane
	/// @param threadHeight is the distance from the minor diameter to the major diameter
	/// @param a is the distance to tool tip in Y-axis when placed in XY plane.
	/// @param b is the distance to tool tip in X-axis when placed in XY plane.
	mwThreadTriangleTurningTool(
		const HolderDefinition& holder,
		const Type type,
		const double insertThickness,
		const double cornerRadius,
		const double inscribedCircleDiameter,
		const double includedAngle,
		const double threadHeight,
		const double a,
		const double b);

	/// Returns current thread type
	Type GetType() const;

	/// Returns current corner radius
	double GetCornerRadius() const;

	/// Returns current diameter of inscribed circle
	double GetInscribedCircleDiameter() const;

	/// Returns current thread height
	double GetThreadHeight() const;

	/// Returns current included angle
	double GetIncludedAngle() const;

	/// Returns current size A
	double GetA() const;

	/// Returns current size B
	double GetB() const;

	mwThreadTriangleTurningTool(const mwThreadTriangleTurningTool& src);

	const mwThreadTriangleTurningTool& operator=(const mwThreadTriangleTurningTool& src);

	bool operator==(const mwThreadTriangleTurningTool& toCompare) const;

	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

private:
	Type m_type;
	double m_cornerRadius;
	double m_inscribedCircleDiameter;
	double m_includedAngle;
	double m_threadHeight;
	double m_a;
	double m_b;

	virtual void DoScale(const Units units, const double scaleFactor);

	void Copy(const mwThreadTriangleTurningTool& copy);
};
}  // namespace cadcam
#endif  //	MW_MWTHREADTRIANGLETURNINGTOOL_HPP_
