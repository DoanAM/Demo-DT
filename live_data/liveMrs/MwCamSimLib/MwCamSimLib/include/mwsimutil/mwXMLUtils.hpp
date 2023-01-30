// (C) 2010-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWXMLUTILS_HPP_
#define MW_MWXMLUTILS_HPP_

#ifndef MW_UNDER_CE

#include <list>
#include <vector>
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
namespace xmlUtils
{
// Eg: mw5axParams m_machParams; => {type = mw5axParams, name = MachParams}
struct ClassInfo
{
	misc::mwstring name;
	misc::mwstring type;
};

// parameter's location in the API hierarchy
// Example: std::vector<ClassInfo>{ 
//  {"MirrorPlaneNormal", "mwVector3d"},
//  {"MirrorTpRoughParams", "mwMirrorTpRoughParams"},
//  {"RoughingParams", "mwRoughingParams"},
//  {"MachParams", "mw5axParams"} }
typedef std::vector<ClassInfo> ParameterLocation;

struct XMLDifference
{
	misc::mwstring origValue;
	misc::mwstring modifValue;
	ParameterLocation paramLocation;
};

typedef std::vector<XMLDifference> XMLDifferences;	// list of parameters

/// Compares two XML files created using mw5axParamsXmlSerializer
/// @returns a vector of parameter locations for which the values differ
MW_5AXUTIL_API XMLDifferences CompareXMLFiles(
	const mwstring& originalFilename,
	const mwstring& modifiedFilename);
} // namespace xmlUtils

//!This class can be used to compare two XML files
/*!Use this class to retrieve modified elements in XML files.
Iterates through original XML file and compares it's elements with
elements from modified XML file and returns a list of elements
that are modified from modified XML.
*/
class MW_5AXUTIL_API MW_DEPRECATED("Deprecated since 2021.08, please use xmlUtils instead.") mwXMLUtils
{
public:
	typedef std::pair<misc::mwstring,misc::mwstring> XMLElement;
	typedef std::list<XMLElement> XMLDifference;
	typedef std::list<XMLDifference> XMLDifferenceList;
	typedef std::list<misc::mwstring> XtraInfoList;


	/*! Compare two XML files
	\param originalFilename represent original tinyxml file
	\param modifiedFilename represents modified tinyxml file
	\returns a list of modifications
	*/
	static void CompareByElement( const mwstring& originalFilename,
		const mwstring& modifiedFilename,XMLDifferenceList &paramlist, XtraInfoList &extraInfoList);

	/*! Searches for a string in the list of results returned by comparison
	\param paramlist - list of modifications
	\param toSearch - search string
	\returns an iterator to the list of modifications
	*/
	static const XMLDifferenceList::const_iterator Search(XMLDifferenceList &paramlist ,
		const misc::mwstring & toSearch );

private:

	mwXMLUtils();
}; // class mwXMLUtils
} // namespace misc
#endif	//	MW_UNDER_CE
#endif	//	MW_MWXMLUTILS_HPP_
