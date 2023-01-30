// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DCONTOUREMPTINESSVISITOR_HPP_
#define MW_MW2DCONTOUREMPTINESSVISITOR_HPP_
#include "mw2dGeometry.hpp"
#include "mw2dPolyLine.hpp"


namespace cadcam
{
template <typename T>
class mw2dContourEmptinessVisitor: public mw2dGeometryConstVisitor<T>
{
public:
	virtual void Visit(const mw2dGeometry<T>&) { m_empty = false; }
	virtual void Visit(const mw2dPoint<T>&) { m_empty = false; }
	virtual void Visit(const mw2dLine<T>&) { m_empty = false; }
	virtual void Visit(const mw2dArc<T>&) { m_empty = false; }
	virtual void Visit(const mw2dContour<T>& contour) { m_empty = contour.IsEmpty(); }
	virtual void Visit(const mw2dPolyLine<T>& polyLine) { m_empty = polyLine.IsEmpty(); }
	virtual void Visit(const mw2dCurve<T>&) { m_empty = false; }
	bool IsEmpty() { return m_empty; }

private:
	bool m_empty;
};
};  // namespace cadcam
#endif  //	MW_MW2DCONTOUREMPTINESSVISITOR_HPP_
