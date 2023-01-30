// (C) 2011-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWADDITIONALINFOATTRIBUTE_HPP_
#define MW_MWADDITIONALINFOATTRIBUTE_HPP_
#include "mwExtendedMoveAttribute.hpp"
#include "mwString.hpp"

#include <vector>


///  mwAdditionalInfoAttribute
/// Stores additional information by creating a table of strings implemented as a vector of vectors
/// A 'line' is a vector of strings, a 'table' is a vector of lines
class MW_5AXUTIL_API mwAdditionalInfoAttribute: public mwExtendedMoveAttribute
{
public:
	typedef std::vector<misc::mwstring> Line;
	typedef std::vector<Line> Table;
	typedef Table::const_iterator TableConstIterator;
	typedef Table::iterator TableIterator;


	/// mwAdditionalInfoAttribute constructor
	mwAdditionalInfoAttribute(void);


	/// mwAdditionalInfoAttribute destructor
	virtual ~mwAdditionalInfoAttribute(void);


	/// mwAdditionalInfoAttribute equal operator
	const bool operator==(const mwAdditionalInfoAttribute& tc) const;


	/// mwAdditionalInfoAttribute different operator
	const bool operator!=(const mwAdditionalInfoAttribute& tc) const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Const accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;


	/// Adds a new line
	void AddLine(const mwAdditionalInfoAttribute::Line& newLine);


	/// Returns a reference to the internal table
	const Table& GetTable() const;


	/// Returns the number of lines of the table
	const Table::size_type GetTableSize() const;


	/// Returns a const iterator to the first line of a table
	TableConstIterator GetTableBegin() const;


	/// Returns an iterator to the first line of a table
	TableIterator GetTableBegin();


	/// Returns a const iterator to the end of the table
	TableConstIterator GetTableEnd() const;


	/// Returns an iterator to the end of the table
	TableIterator GetTableEnd();

private:
#pragma warning(suppress : 4251)
	Table m_table;
};
#endif  //	MW_MWADDITIONALINFOATTRIBUTE_HPP_
