// (C) 2010-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWKEEPPARTSATTRIBUTE_HPP_
#define MW_MWKEEPPARTSATTRIBUTE_HPP_
#include "mw3dLine.hpp"
#include "mwEnrichedPostedMove.hpp"


/// mwKeepPartsAttribute - stores information regarding which parts should be kept or removed at a
/// given move
class MW_5AXUTIL_API mwKeepPartsAttribute: public mwExtendedMoveAttribute
{
public:
	typedef cadcam::mwTPoint3d<float> Point3d;
	typedef std::vector<Point3d> Points3d;

	typedef cadcam::mw3dLine<float> Line3d;
	typedef std::vector<Line3d> Lines3d;


	/// mwKeepPartsAttribute
	/// @param points will mark the parts to be kept
	/// @param lines will mark the parts to be kept
	/// @param stockID indicates the target stock
	/// @param persistent - when set to true the attribute will be reapplied for each subsequent
	/// move
	mwKeepPartsAttribute(
		const Points3d& points,
		const Lines3d& lines,
		const misc::mwstring& stockID,
		bool persistent = false);


	/// mwKeepPartsAttribute
	/// @param points will mark the parts to be kept
	/// @param stockID indicates the target stock
	/// @param persistent - when set to true the attribute will be reapplied for each subsequent
	/// move
	mwKeepPartsAttribute(
		const Points3d& points, const misc::mwstring& stockID, bool persistent = false);


	/// mwKeepPartsAttribute
	/// @param point will mark the part to be kept
	/// @param stockID indicates the target stock
	/// @param persistent - when set to true the attribute will be reapplied for each subsequent
	/// move
	mwKeepPartsAttribute(
		const Point3d& point, const misc::mwstring& stockID, bool persistent = false);


	/// mwKeepPartsAlongLineAttribute
	/// @param lines will mark the parts to be kept
	/// @param stockID indicates the target stock
	/// @param persistent - when set to true the attribute will be reapplied for each subsequent
	/// move
	mwKeepPartsAttribute(
		const Lines3d& lines, const misc::mwstring& stockID, bool persistent = false);


	/// mwKeepPartsAlongLineAttribute
	/// @param line will mark the part to be kept
	/// @param stockID indicates the target stock
	/// @param persistent - when set to true the attribute will be reapplied for each subsequent
	/// move
	mwKeepPartsAttribute(
		const Line3d& line, const misc::mwstring& stockID, bool persistent = false);


	/// mwKeepPartsAttribute equal attribute
	const bool operator==(const mwKeepPartsAttribute& tc) const;


	/// mwKeepPartsAttribute different attribute
	const bool operator!=(const mwKeepPartsAttribute& tc) const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Accept mwExtendedMoveAttributeVisitor visitor const
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;


	/// Gets a reference to the vector of points used to determine the parts to be kept
	const Points3d& GetPoints() const;


	/// Sets the vector of points used to determine the parts to be kept
	void SetPoints(const Points3d& points);


	/// Sets the vector of lines used to determine the parts to be kept
	const Lines3d& GetLines() const;


	/// Sets the vector of lines used to determine the parts to be kept
	void SetLines(const Lines3d& lines);


	/// Returns true or false. If persistent, the attribute will be reapplied for each subsequent
	/// move
	bool IsPersistent() const;


	/// Sets a bool value. If true, the attribute will be reapplied for each subsequent move
	void EnablePersistency(bool enable);


	/// Returns the target stock
	const misc::mwstring& GetStockID() const;


	/// Sets the id of the target stock
	void SetStockID(const misc::mwstring& stockID);

private:
	Points3d m_points;
	Lines3d m_lines;
	misc::mwstring m_stockID;
	bool m_persistent;
};
#endif  //	MW_MWKEEPPARTSATTRIBUTE_HPP_
