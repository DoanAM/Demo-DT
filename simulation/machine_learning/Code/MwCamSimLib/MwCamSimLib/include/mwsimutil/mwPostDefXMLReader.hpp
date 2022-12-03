// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostDefXMLReader class

//#############################################################################

#ifndef MW_MWPOSTDEFXMLREADER_HPP_
#define MW_MWPOSTDEFXMLREADER_HPP_
//#############################################################################
#include "mwString.hpp"
#include "mwMxpDllImpExpDef.hpp"
#include <mwTiXMLReadWriteHelper.hpp>
#include "mwMXPParam.hpp"
#include "mwPostCommonDefinitions.hpp"
#include "mw5axControlDef.hpp"

#pragma warning(push)
#pragma warning(disable: 4275 4251)
//#############################################################################
class TiXmlDocument;
class mwGenericPostDef;
class TiXmlNode;
namespace post
{
	class mwPosted5axMove;
}
//#############################################################################
//! allows reading of xml file for post
class MWMXP_API mwPostDefXMLReader : public misc::mwTiXMLReadWriteHelper
{
public:
	//#########################################################################	
	mwPostDefXMLReader();
	//#########################################################################	
	const mwGenericPostDef Read(const misc::mwstring fileName, const misc::mwstring id = _T(""), const bool validate = true);
	//#########################################################################	
	const mwGenericPostDef Read(const TiXmlDocument& doc2read, const misc::mwstring id = _T(""), const bool validate = true);
	//#########################################################################	
	const std::vector<mwGenericPostDef> ReadAllDefinitions(const misc::mwstring fileName, const bool isIOFMachine = false);
	//#########################################################################	
	std::vector<misc::mwstring> GetAvailablePostDefinitionsIDs(const misc::mwstring fileName);
	//#########################################################################	
	std::vector<misc::mwstring> GetAvailablePostDefinitionsIDs(const TiXmlDocument& doc2read);
	//#########################################################################	
	void SetDefaultMXPParam(const post::mwMXPParamPtr& mxpParamPtr);
	//#########################################################################	
	static const post::mwMXPParam GenerateInitialMultiXPostParams(
		const measures::mwUnitsFactory::Units operationUnits,
		const post::mwMXPParam::MachineLimits machineLimits,
		const misc::mwAutoPointer<bool> useFirstSol, 
		const bool filterDuplicateMoves,
		const misc::mwAutoPointer<post::mwPosted5axMove> referenceMovePtr,
		const misc::mwAutoPointer<double> prefredAngleValuePtr = MW_NULL);
private:
	//#########################################################################	
	void AddPostElemnt(const TiXmlElement* axisNode, mwGenericPostDef& machDef);
	//#########################################################################	
	void ReadAdditionalFixedAxis(
		const misc::mwstring elementName,
		const mwGenericPostDef &machDef,
		const TiXmlElement* axisNode);

	//#########################################################################	
	void ReadMXPParam(
		const TiXmlNode *docNode,
		post::mwMXPParamPtr& param,
		mwGenericPostDef& machDef);
	//#########################################################################	
	bool Read5AxControlDef(const TiXmlElement * element,
		misc::mwstring rotOutFormat,
		short rotAxIndex,
		post::mw5axControlDef::mw5axControlDefPtr crt5AxControlDefPtr);
	//#########################################################################	
	void ReadDet(const TiXmlElement* element, mwGenericPostDef& machDef);
	//#########################################################################	
	const bool IsPostElement(const misc::mwstring& elementName);
	//#########################################################################	
	void AddLegacySpindle(const TiXmlElement* axisNode, mwGenericPostDef& machDef);
	//#########################################################################	
	void AddAxis(const TiXmlElement* axisNode, mwGenericPostDef& machDef);
	//#########################################################################	
	void AddLegacyAxis(const TiXmlElement* axisNode, mwGenericPostDef& machDef);
	//#########################################################################	
	const post::mwMatrix4d GetMatrix(const TiXmlElement* axisNode);
	//#########################################################################	
	post::mwMXPParamPtr m_mxpParamPtr;
	post::AdditionalFixedAxesPtr m_additionalFixedAxesPtr;
	//#########################################################################	
};
//#############################################################################
#pragma warning(pop)
#endif	//	MW_MWPOSTDEFXMLREADER_HPP_
