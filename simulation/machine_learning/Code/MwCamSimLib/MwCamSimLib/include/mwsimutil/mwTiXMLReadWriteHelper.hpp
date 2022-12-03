// (C) 2012-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTIXMLREADWRITEHELPER_HPP_
#define MW_MWTIXMLREADWRITEHELPER_HPP_

#ifndef MW_UNDER_CE

#include "mwSimUtilDllImpExpDef.hpp"
#include "mwString.hpp"

class TiXmlElement;
class TiXmlAttribute;
class TiXmlDeclaration;

namespace misc
{
	class MW_SIMUTIL_API mwTiXMLReadWriteHelper
	{
	public:
		/// The name of the UTF-8 encoding.
		static const mwstring UTF_8;

		static mwstring GetUTF_8();

		static void SetAttributeValue( TiXmlElement *whereToSet, const misc::mwstring& whatToSet, const misc::mwstring& withWhichVAlue);
		void SetAttributeValue( TiXmlAttribute *attribute, const misc::mwstring& newValue);
	protected:
		mwTiXMLReadWriteHelper( const misc::mwstring &xmlVersion,
			const misc::mwstring &xmlEncoding);

		mwTiXMLReadWriteHelper( const misc::mwstring &xmlVersion = _T("1.0"));

		misc::mwstring GetElementName( const TiXmlElement *element );
		//! Returns the XML representation of the element.
		misc::mwstring GetElementXml(const TiXmlElement* pElement);

		misc::mwstring GetAttributeName( const TiXmlAttribute *attribute );
		misc::mwstring GetAttributeValue( const TiXmlAttribute *attribute );
		misc::mwstring GetAttributeValue( const TiXmlElement *element, const misc::mwstring &attrName );
		void ApplyXMLDeclaration( const TiXmlDeclaration *decl );
		misc::mwstring ToString(const char* toConvert);
		std::string FromString(const misc::mwstring& toConvert);

	private:
		misc::mwstring			m_xmlVersion;
		misc::mwstring			m_xmlEncoding;
	};
}
#endif
#endif	//	MW_MWTIXMLREADWRITEHELPER_HPP_
