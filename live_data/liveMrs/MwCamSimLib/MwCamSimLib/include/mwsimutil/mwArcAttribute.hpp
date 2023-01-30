// (C) 2010-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWARCATTRIBUTE_HPP_
#define MW_MWARCATTRIBUTE_HPP_
#include "mwEnrichedPostedMove.hpp"
#include "mwTPoint3d.hpp"


/// mwArcAttribute
/// Stores information for a move that is part of an arc
class MW_5AXUTIL_API mwArcAttribute: public mwExtendedMoveAttribute
{
public:
	/// mwArcAttribute constructor
	mwArcAttribute(void);


	/// mwArcAttribute destructor
	virtual ~mwArcAttribute(void);


	/// mwArcAttribute equal operator
	const bool operator==(const mwArcAttribute& tc) const;


	/// mwArcAttribute different operator
	const bool operator!=(const mwArcAttribute& tc) const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Accept mwExtendedMoveAttributeVisitor visitor const
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;


	/// Returns the center of the arc
	const cadcam::mwTPoint3d<float>& GetCenter() const;


	/// Sets the center of the arc
	void SetCenter(const cadcam::mwTPoint3d<float>& center);


	/// Returns the normal of the arc
	const cadcam::mwTPoint3d<float>& GetNormal() const;


	/// Sets the normal of the arc
	void SetNormal(const cadcam::mwTPoint3d<float>& normal);


	/// Returns true if the move is intermediate. The last move in an arc is not intermediate
	const bool GetIsIntermediate() const;


	/// Set true if the move is intermediate. The last move in an arc is not intermediate
	void SetIsIntermediate(const bool value);


	/// Returns the total time of the arc
	const float GetArcTotalTime() const;


	/// Sets the total time of the arc
	void SetArcTotalTime(const float arcTotalTime);


	/// Returns true if the arc is clockwise
	MW_DEPRECATED(
		"Deprecated since 2020.08, arc is always CCW seen from normal direction. This parameter "
		"has no effect.")
	const bool GetIsCW() const;


	/// Set true if the arc is clockwise
	MW_DEPRECATED(
		"Deprecated since 2020.08, arc is always CCW seen from normal direction. This parameter "
		"has no effect.")
	void SetIsCW(const bool value);


	/// Returns the radius of the arc
	const float GetRadius() const;


	/// Sets the radius of the arc
	void SetRadius(const float radius);

	void SetArcSweep(const float arcSweep);
	float GetArcSweep() const;

private:
	cadcam::mwTPoint3d<float> m_center;
	cadcam::mwTPoint3d<float> m_normal;
	bool m_isIntermediate;
	float m_arcTotalTime;
	float m_radius;
	float m_arcSweep;
};
#endif  //	MW_MWARCATTRIBUTE_HPP_
