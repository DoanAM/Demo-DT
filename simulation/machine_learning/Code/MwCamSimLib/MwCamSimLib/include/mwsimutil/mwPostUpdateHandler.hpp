// (C) 2018-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWPOSTUPDATEHANDLER_HPP_
#define MW_MWPOSTUPDATEHANDLER_HPP_
#include "mwAutoPointer.hpp"
#include "mwPostException.hpp"

class MW_5AXUTIL_API mwPostUpdateHandler
{
public:
	typedef misc::mwAutoPointer<mwPostUpdateHandler> mwPostUpdateHandlerPtr;

	mwPostUpdateHandler()
	{
	}
	struct ProgressDescription
	{
		ProgressDescription()
			:m_postedProgressType(NO_ACTION)
			, m_percentage(0)
			, m_noOfStreams(0)
			, m_currStream(0)
		{
		}
		enum postTPCreatorID
		{
			NO_ACTION = 0,
			PROCESSING = 1,
			PROCESSING_6AXIS_COMPLETED = 2,
			PROCESSING_5AXIS_COMPLETED = 3,
			PROCESSING_4AXIS_COMPLETED = 4,
			PROCESSING_3AXIS_COMPLETED = 5,
			EXTRACTING_MOVES_FROM_TOOLPATH = 6,
			COMPUTE_POSTED_MOVES = 7,
			BLENDING_INTERPOLATION = 8,
			CALCULATE_WINDED_ANGLES = 9,
			HANDLE_LARGE_ANGLE_JUMPS = 10,
			REWIND = 11,
			PROCESSING_N_AXIS_COMPLETED = 12
		};
		postTPCreatorID m_postedProgressType;
		int m_percentage;
		int m_noOfStreams; // only for stream
		int m_currStream; // only for stream
	};
	
	virtual void SetProgress(const ProgressDescription& rProgress) = 0;
	virtual const bool IsCanceled() const = 0;

	virtual ~mwPostUpdateHandler(){}
};
#endif	//	MW_MWPOSTUPDATEHANDLER_HPP_
