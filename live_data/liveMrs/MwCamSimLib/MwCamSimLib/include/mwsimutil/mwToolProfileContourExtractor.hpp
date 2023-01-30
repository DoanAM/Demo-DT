// (C) 2009-2021 by ModuleWorks GmbH
// Owner: MachSim

/******************************************************************************
*               File: mwToolProfileContourExtractor.hpp						  *
*******************************************************************************
*               Description: Extract the 2dcontour from revolved tools.       *
******************************************************************************/

#ifndef MW_MWTOOLPROFILECONTOUREXTRACTOR_HPP_
#define MW_MWTOOLPROFILECONTOUREXTRACTOR_HPP_
#include "mwTool.hpp"
#include "mw2dContour.hpp"
#include "mwToolPartSelector.hpp"


#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif


namespace cadcam
{
	template <typename T>
	class mwRevolvedToolApproximation;
	template <typename T>
	class mwRevolvedToolApproximationCreator;

	class MW_5AXUTIL_API mwToolProfileContourExtractor: private mwToolVisitor
	{
	public:

		mwToolProfileContourExtractor(const mwTool& tool);

		//!* it returns the contour in absolute coordinates unless relativeToPreviusPartCoordinates (Thus, each one's Y 0 level corresponds to the top Y of all of the previously )
		mw2ddContourPtr GetProfile(const mwToolPartSelector& parts, const bool relativeToPreviusPartCoordinates=false) const;
		
		~mwToolProfileContourExtractor();

	protected:

		virtual void Visit( const mwTool &visitor );
		virtual void Visit( const mwBoreBar &visitor );
		virtual void Visit( const mwBullMill &visitor );
		virtual void Visit( const mwChamferMill &visitor );
		virtual void Visit( const mwCntrBore &visitor );
		virtual void Visit( const mwCSink &visitor );
		virtual void Visit( const mwCtrDrill &visitor );
		virtual void Visit( const mwDoveMill &visitor );
		virtual void Visit( const mwDrill &visitor );
		virtual void Visit( const mwEndMill &visitor );
		virtual void Visit( const mwFaceMill &visitor );
		virtual void Visit( const mwLolMill &visitor );
		virtual void Visit( const mwRadMill &visitor );
		virtual void Visit( const mwReamer &visitor );
		virtual void Visit( const mwSlotMill &visitor );
		virtual void Visit( const mwSphereMill &visitor );
		virtual void Visit( const mwSpotDrill &visitor );
		virtual void Visit( const mwTaperMill &visitor );
		virtual void Visit( const mwTapLH &visitor );
		virtual void Visit( const mwTapRH &visitor );	
		virtual void Visit( const mwBarrelMill &visitor );
		virtual void Visit( const mwBarrelAdvancedMill& visitor );
		virtual void Visit(const cadcam::mwBarrelBarrSecMill& visitor);
		virtual void Visit(const cadcam::mwBarrelDProfMill& visitor);
		virtual void Visit(const mwBarrelLensMill &visitor);
		virtual void Visit(const mwBarrelTangentMill& visitor);
		virtual void Visit(const mwBarrelTangentMillConicalShaft& visitor);
		virtual void Visit(const mwBarrelTaperMill& visitor);
		virtual void Visit(const mwConvexTipMill &visitor);
		virtual void Visit(const mwThreadTapTool &visitor);
		virtual void Visit( const mwGenericRevolvedTool& visitor );
		virtual void Visit( const mwGenericExtrudedTool& visitor );
		virtual void Visit( const mwWireTool& visitor );
		virtual void Visit( const mwGenericSawingTool& visitor ) ;
		virtual void Visit( const mwChainSawTool& visitor ) ;
		virtual void Visit( const mwGenericTool& visitor);
		virtual void Visit(const mwPotGrinderTool& visitor);
		virtual void Visit(const mwThreadMillSingleFormTool& visitor);
		void ExtractByToolApproximation(const mwTool& tool);

#pragma warning(suppress:4251)
		mwToolPtr m_copiedTool;

		mwRevolvedToolApproximation<double>  *m_toolApproximation;
	private:
		bool operator==(const mwToolProfileContourExtractor &toCompare) const;
		mwToolProfileContourExtractor(const mwToolProfileContourExtractor& toCopy);
		virtual void Default();
	};

}


#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility pop
#endif
#endif	//	MW_MWTOOLPROFILECONTOUREXTRACTOR_HPP_
