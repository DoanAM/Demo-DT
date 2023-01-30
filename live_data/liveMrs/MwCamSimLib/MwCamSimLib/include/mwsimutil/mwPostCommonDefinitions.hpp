// (C) 2008-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWPOSTCOMMONDEFINITIONS_HPP_
#define MW_MWPOSTCOMMONDEFINITIONS_HPP_

#include "mwPosted3axMove.hpp"
#include "mwPosted4axMove.hpp"
#include "mwPosted5axMove.hpp"
#include "mwPosted6axMove.hpp"
#include "mwPostedNaxMove.hpp"
#include "mwMemoryPoolList.hpp"
#include <map>
#include <utility>
#include <vector>
#include "mwString.hpp"
#include "mwRealArrayLarge.hpp"
#include "mwPostComponentsDefinitions.hpp"

namespace post
{
	static const float post_data_version = 1.0f;

	typedef cadcam::mwTPoint3d< double >     point3d;
	typedef point3d                          vector3d;
	typedef misc::mwAutoPointer<point3d>     point3dPtr;
	typedef misc::mwAutoPointer<vector3d>    vector3dPtr;
	
	typedef misc::mwMemoryPoolList<post::mwPosted3axMove>         posted3axList;
	typedef misc::mwAutoPointer<posted3axList>                    posted3axListPtr;
	typedef misc::mwMemoryPoolList<post::mwPosted4axMove>         posted4axList;
	typedef misc::mwAutoPointer<posted4axList>                    posted4axListPtr;
	typedef misc::mwMemoryPoolList<post::mwPosted5axMove>         posted5axList;
	typedef misc::mwAutoPointer<posted5axList>                    posted5axListPtr;
	typedef misc::mwMemoryPoolList<post::mwPosted6axMove>         posted6axList;
	typedef misc::mwAutoPointer<posted6axList>                    posted6axListPtr;
	typedef misc::mwMemoryPoolList<post::mwPostedNaxMove>         postedNaxList;
	typedef misc::mwAutoPointer<postedNaxList>                    postedNaxListPtr;

	typedef cadcam::mwMatrix<double, 4, 4>   mwMatrix4d;
	typedef misc::mwAutoPointer<mwMatrix4d>  mwMatrix4dPtr;

	typedef cadcam::mwMatrix<double, 3, 3>   mwMatrix3d;
	typedef misc::mwAutoPointer<mwMatrix3d>  mwMatrix3dPtr;

	typedef std::map<misc::mwstring, mwMatrix4d> mwMatrix4dMap;

	typedef std::pair<misc::mwstring, double>			FixedAxis;
	typedef std::vector<FixedAxis>						AdditionalFixedAxes;
	typedef misc::mwAutoPointer<AdditionalFixedAxes>	AdditionalFixedAxesPtr;
	struct mwTransformation3d
	{
		cadcam::mwMatrix<double, 3, 3> m_R;
		point3d m_T;
		double m_angle0;
		double m_angle1;
		mwPosted5axMove::anglesState m_angleState;
	};
	typedef misc::mwAutoPointer<mwTransformation3d> mwTransformation3dPtr;
	
	typedef std::pair<mwMatrix4d, bool>			AdditionalTransfMatrix;
	typedef std::map<misc::mwstring, AdditionalTransfMatrix> AdditionalTransfMatrixMap;
	typedef misc::mwAutoPointer<AdditionalTransfMatrixMap>	AdditionalTransfMatrixMapPtr;
	
	
	enum mwTranslationPos
	{
		HEAD = 0,
		TABLE
	};
	
	typedef std::pair<misc::mwstring, misc::mwstring>          mwStringPair;
	typedef std::vector<mwStringPair>                          mwStringPairVect;
	typedef std::vector<mwStringPair>::iterator                mwStringPairVectIt;
	typedef std::vector<mwStringPair>::const_iterator          mwStringPairVectConstIt;
	typedef misc::mwAutoPointer<mwStringPairVect>              mwStringPairVectPtr;
	
	struct mwValidSolutions
	{
		mwValidSolutions()
		{
			m_first = m_second = true;
		}
		bool m_first;
		bool m_second;
		const bool Has1Solution() const
		{
			return (m_first && !m_second) || (!m_first && m_second);
		}
	};
	typedef std::list<mwValidSolutions> mwValidSolutionsList;
	typedef misc::mwAutoPointer<mwValidSolutionsList> mwValidSolutionsListPtr;
	
	struct mwMirrorPosted5AxMove
	{
		double m_first_angle0;
		double m_first_angle1;
		double m_second_angle0;
		double m_second_angle1;
		mwPosted5axMove::anglesState m_angsState;
		point3d m_firstAbsMachPos;
		point3d m_secondAbsMachPos;
		void Reset()
		{
			m_first_angle0 = 0;
			m_first_angle1 = 0;
			m_second_angle0 = 0;
			m_second_angle1 = 0;
		}
	};
	struct mwMirrorPosted6AxMove
	{
		double m_first_angle0;
		double m_first_angle1;
		double m_first_angle2;
		double m_second_angle0;
		double m_second_angle1;
		double m_second_angle2;
		mwPosted6axMove::anglesState m_angsState;
		point3d m_firstAbsMachPos;
		point3d m_secondAbsMachPos;
		void Reset()
		{
			m_first_angle0 = 0;
			m_first_angle1 = 0;
			m_first_angle2 = 0;
			m_second_angle0 = 0;
			m_second_angle1 = 0;
			m_second_angle2 = 0;
		}
	};
	
	static const point3d SIX_AXIS_TOOL_DIR_SIDE(1, 0, 0);

	struct typedMove
	{
		misc::mwAutoPointer<cadcam::mwCNCMove> m_move;
		post::mwPostedMove::Types              m_type;
		bool                                   m_contour;

		typedMove()
			: m_move(MW_NULL)
			, m_type(post::mwPostedMove::KEEP_THIS_LAST_TYPES)
			, m_contour(false){}
		typedMove(
			misc::mwAutoPointer<cadcam::mwCNCMove> move,
			post::mwPostedMove::Types type,
			bool contour)
			: m_move(move)
			, m_type(type)
			, m_contour(contour){}
	};

	typedef misc::mwRealArrayLarge<typedMove> typedMoves;

	struct postStreammingUtils
	{
		misc::mwAutoPointer<post::mwPostedMove>	m_previousChunkLastPostedMove;
		misc::mwAutoPointer<post::mwPostedMove>	m_previousChunkLastBuildedPostedMove;
		misc::mwAutoPointer<post::mwPostedMove>	m_previousChunkLastSmallPostBuildedPostedMove;
		misc::mwAutoPointer<post::typedMove>	m_previousChunkLastTypedMove;
		std::vector<size_t>				m_chunksSizes;
		std::vector<size_t>				m_headAndTableRotationSolutions;
		misc::mwstring					m_mxpOutputFilePath;
		size_t							m_lastIndexToPostedMove;
		size_t							m_processedChunks;
		int								m_windingCountRotAng0;
		int								m_windingCountRotAng1;
		int								m_windingCountRotAng2;
		bool							m_changeHeadAndTableStrategy;
		bool							m_activateHTRotWhilePosting6axTo4ax;
		bool							m_setThroughSmallPosting;

		postStreammingUtils()
			: m_previousChunkLastPostedMove(MW_NULL)
			, m_previousChunkLastBuildedPostedMove(MW_NULL)
			, m_previousChunkLastSmallPostBuildedPostedMove(MW_NULL)
			, m_previousChunkLastTypedMove(MW_NULL)
			, m_lastIndexToPostedMove(0)
			, m_windingCountRotAng0(0)
			, m_windingCountRotAng1(0)
			, m_windingCountRotAng2(0)
			, m_chunksSizes(0)
			, m_processedChunks(0)
			, m_changeHeadAndTableStrategy(false)
			, m_activateHTRotWhilePosting6axTo4ax(false)
			, m_setThroughSmallPosting(false) {}
	};

	struct ArcContainer
	{
		post::mwPostedArcMovePtr m_postedArcMovePtr;
		unsigned int m_start;
		unsigned int m_end;
	};
}

#endif