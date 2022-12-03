// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPUTILS_HPP_
#define MW_MWTPUTILS_HPP_
#include "mwDefines.hpp"
#include "mwCadcamEnumDefinitions.hpp"
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

namespace mw
{
namespace TestHelper
{
	class ReportWriter;	
}
}

namespace cadcam
{
class mwToolPath;
class mwTPSection;
class mwTPPass;
class mwTPContour;
class mwTPLink;

class MW_5AXUTIL_API mwTPUtils
{
public:
	enum ToolpathType
	{
		TP_3_AXIS = 1,
		TP_3_PLUS_2_AXIS = 2,
		TP_5_AXIS = 3
	};

	enum ToolpathStatus
	{
		EQUAL = 0,
		ECTOL,
		REALC,
		DIFFERENT,
		EMPTY
	};

	struct SectionParams
	{
		bool isLink;
		mwTPLinkN::Types linkType;
	};

	/// Compare two TPs and create vector of reports
	/// @param first - toolpath to be compared.
	/// @param second - toolpath to be compared.
	/// @param tol given tolerance factor.
	/// @param delta given tolerance factor.
	/// @param minCos given minimal cosine of angle between moves orientations.
	/// @param toolLength the length of tool.
	/// @param reports reports comparison result
	static const ToolpathStatus CompareToolPathWithReports(
		const mwToolPath& first,
		const mwToolPath& second,
		const double tol,
		const double delta,
		const double minCos,
		const double toolLength,
		std::vector<std::pair<misc::mwstring, misc::mwstring>>& reports);

	struct ToolpathDifference
	{
		typedef GenericNames::Polyline3dVec Difference;
		typedef std::pair<misc::mwstring, Difference> AttributeDifference;

		Difference m_xyz;
		Difference m_abc;

		std::vector<AttributeDifference> m_attributes;

		ToolpathStatus m_status;
		std::vector<std::pair<misc::mwstring, misc::mwstring>> m_reports;

		// extedned values. filled only when useExtendedCompare option enabled
		double m_cutsSiblingsMaxDeviation;
		double m_cutsOrphansMaxDeviation;
		double m_cutsOrphansLength;
		double m_leadsSiblingsMaxDeviation;
		double m_leadsOrphansLength;
		double m_linksSiblingsMaxDeviation;
		double m_linksOrphansLength;
	};

#ifndef MW_USE_VS2008_COMPATIBILITY
	/// Compare two TPs and create vector of reports
	/// @param tpA - toolpath to be compared.
	/// @param tpB - toolpath to be compared.
	/// @param xyzTolerance - given tolerance for xyz.
	/// @param abcTolerance - given tolerance for abc.
	/// @param [out] result - output deviations.
	/// @param useExtendedCompare - enable aditional deviation calculation for reordered toolpaths.
	static void CompareToolPathWithReports(
		const mwToolPath& tpA,
		const mwToolPath& tpB,
		const double xyzTolerance,
		const double abcTolerance,
		ToolpathDifference& result,
		const bool useExtendedCompare = false);

	/// Only for internal usage in MW
	static void CompareToolPathWithReports(
		const mwToolPath& tpA,
		const mwToolPath& tpB,
		const double xyzTolerance,
		const double abcTolerance,
		ToolpathDifference& result,
		mw::TestHelper::ReportWriter& reportWriter,
		const bool useExtendedCompare = false);
#endif

	/// Gets the type of a toolpath
	///
	///	@param tp is toolpath to get the type from
	///	@return toolpath type as ToolpathType enum value
	static const ToolpathType GetToolpathType(const cadcam::mwToolPath& tp);
	static const SectionParams GetSectionParameters(const mwTPSection&);

	static const size_t GetLayersCount(const mwToolPath&, const GenericNames::Point3d&);
	static void MarkLayersMoves(mwToolPath&, const GenericNames::Point3d&, const double);

	static const double GetTPsDeviationDistance(const mwToolPath&, const mwToolPath&);

	static const GenericNames::Polyline3dVec GetTPsDeviation(
		const mwToolPath&, const mwToolPath&, const double, const double);

	static const double GetToolpathTime(const mwToolPath&);

	static const double GetMaxSegmentLength(const mwToolPath&);
	static const double GetMinSegmentLength(const mwToolPath&);
	static const double GetMaxAngle(const mwToolPath&);
	static const double GetMinAngle(const mwToolPath&);
	static const double GetArcMovesLength(const mwToolPath&);
	static const double GetLinearMovesLength(const mwToolPath&);
	static const double GetLinksLength(const mwToolPath&);
	static const double GetLeadsLength(const mwToolPath&);
	static const double GetTPLength(const mwToolPath&);
	static const size_t GetArcMovesCount(const mwToolPath&);
	static const size_t GetLinearMovesCount(const mwToolPath&);
	static const size_t GetAttrMovesCount(const mwToolPath&);
	static const size_t GetLinksCount(const mwToolPath&);
	static const size_t GetLeadsCount(const mwToolPath&);
	static const size_t GetCutsCount(const mwToolPath&);
	static const size_t GetAnglesGreaterThanXCount(const mwToolPath&, const double);
	static void RemoveSurfaceInfo(cadcam::mwToolPath& toolPath);

	static misc::mwstring GetToolpathHash(const cadcam::mwToolPath& toolPath);

private:
	enum SectionType
	{
		TP_LINK,
		TP_CONTOUR
	};

	struct SectionInfo
	{
		SectionType m_type;  // type of section (contour/link)
		const cadcam::mwTPSection* m_ptr;  // address of TpSection in memory
	};

	typedef std::vector<SectionInfo> SectionInfoVector;

	typedef std::vector<GenericNames::Point3d> DirectionVector;

	struct SectionInfoFinder
	{
		SectionInfoFinder(const cadcam::mwTPSection& tpSection): m_tpSection(tpSection) {}
		const bool operator()(const mwTPUtils::SectionInfo& si) const
		{
			return si.m_ptr == &m_tpSection;
		}

	private:
		const cadcam::mwTPSection& m_tpSection;
		SectionInfoFinder& operator=(const SectionInfoFinder&);  // = delete
	};


	/// Build sections info from a pass
	/// @param pass is pass to build the sections info from
	/// @return a vector containing all section info from pass (in the order from pass structure)
	static const SectionInfoVector BuildPassSectionsInfo(const cadcam::mwTPPass& pass);

	/// Build edge links info from a pass
	/// Edge links are first and last continuous sections of type links from toolpath
	/// @param pass is pass to build the edge links info from
	/// @return a vector containing all edge links info from pass
	static const SectionInfoVector BuildPassEdgeLinksInfo(const cadcam::mwTPPass& pass);

	/// Check if all moves from a given section have a given orientation
	/// @param section is section to be tested
	/// @param givenOrientation is given orientation
	/// @return true if all moves from given section have the given orientation
	/// 		false otherwise
	static const bool HaveAllMovesFromSectionGivenOrientation(
		const cadcam::mwTPSection& section, const GenericNames::Point3d& givenOrientation);

	/// Check if a section exist in a section info vector
	/// @param tpSection is section to be tested
	/// @param siv is section info vector where to search
	/// @return true if section is found in section info vector
	///		false otherwise
	static const bool IsSectionInSectionInfoVector(
		const cadcam::mwTPSection& tpSection, const SectionInfoVector& siv);

	/// Check if all moves from a section info vector have the given orientation
	/// @param siv is section info vector where to search
	/// @param givenOrientation is orientation to be searched
	/// @return true if section is found in section info vector
	/// 		false otherwise
	static const bool HaveAllMovesFromSectionInfoVectorGivenOrientation(
		const SectionInfoVector& siv, const GenericNames::Point3d& givenOrientation);

	/// Get edge links info
	/// @param beginIt start iterator in a container containing section infos
	/// @param endIt end iterator in a container containing section infos
	/// @param edgeLinks return edge links infos
	template <class TIt>
	static void GetEdgeLinksInfo(
		const TIt& beginIt, const TIt& endIt, SectionInfoVector& edgeLinks);

	static const size_t GetLinksLeadsCount(const cadcam::mwToolPath& tp, const bool isLeadCounter);
	static const double GetLinksLeadsLength(const cadcam::mwToolPath& tp, const bool isLeadCounter);
	static const double GetArcsLinesLength(const cadcam::mwToolPath& tp, const bool isArcCounter);
};

}  // namespace cadcam
#endif  //	MW_MWTPUTILS_HPP_
