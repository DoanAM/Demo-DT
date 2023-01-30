// (C) 2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWPOSTCOMPONENTESDEFINITIONS_HPP_
#define MW_MWPOSTCOMPONENTESDEFINITIONS_HPP_

#include "mwMatrix.hpp"
#include "mwTPoint3d.hpp"
#include <map>

namespace post
{

	typedef std::pair<misc::mwstring, misc::mwstring>          mwStringPair;
	typedef std::vector<mwStringPair>                          mwStringPairVect;
	typedef std::vector<mwStringPair>::iterator                mwStringPairVectIt;
	typedef std::vector<mwStringPair>::const_iterator          mwStringPairVectConstIt;
	typedef misc::mwAutoPointer<mwStringPairVect>              mwStringPairVectPtr;

	typedef cadcam::mwTPoint3d< double >     point3d;
	typedef point3d                          vector3d;
	typedef misc::mwAutoPointer<point3d>     point3dPtr;
	typedef misc::mwAutoPointer<vector3d>    vector3dPtr;

	typedef cadcam::mwMatrix<double, 4, 4>   mwMatrix4d;
	typedef misc::mwAutoPointer<mwMatrix4d>  mwMatrix4dPtr;

	typedef cadcam::mwMatrix<double, 3, 3>   mwMatrix3d;
	typedef misc::mwAutoPointer<mwMatrix3d>  mwMatrix3dPtr;

	typedef std::map<misc::mwstring, mwMatrix4d> mwMatrix4dMap;

	typedef std::pair<misc::mwstring, double>			FixedAxis;
	typedef std::vector<FixedAxis>						AdditionalFixedAxes;
	typedef misc::mwAutoPointer<AdditionalFixedAxes>	AdditionalFixedAxesPtr;

	typedef std::pair<mwMatrix4d, bool>			AdditionalTransfMatrix;
	typedef std::map<misc::mwstring, AdditionalTransfMatrix> AdditionalTransfMatrixMap;
	typedef misc::mwAutoPointer<AdditionalTransfMatrixMap>	AdditionalTransfMatrixMapPtr;

	/*! class used to define a spindle in .xml file for MultiXPost.
			-this class contains spindle orientation and cutting direction
		*/

		//! container class for post processor
		/*
			contains a post definition for xml files
		*/
	struct mwSpindle
	{

		mwSpindle()
			: m_orientation(point3d(0, 0, 1))
			, m_directionPtr(MW_NULL)
		{};
		mwSpindle(vector3d orientation, vector3dPtr directionPtr = MW_NULL)
			: m_orientation(orientation)
			, m_directionPtr(directionPtr)
		{};
		const bool operator == (const mwSpindle& toCompare) const
		{
			if (&toCompare == this)
				return true;
			if ((m_directionPtr != MW_NULL && toCompare.m_directionPtr == MW_NULL) || (m_directionPtr == MW_NULL && toCompare.m_directionPtr != MW_NULL))
				return false;
			if (m_directionPtr != MW_NULL && toCompare.m_directionPtr != MW_NULL && *m_directionPtr != *toCompare.m_directionPtr)
				return false;
			return m_orientation == toCompare.m_orientation;

		}
		misc::mwAutoPointer<mwSpindle> Clone() const
		{
			misc::mwAutoPointer<mwSpindle> retSpin = new mwSpindle(m_orientation);
			if (m_directionPtr.IsNotNull())
				retSpin->m_directionPtr = new point3d(*m_directionPtr);
			return retSpin;
		}
		vector3d m_orientation; // Spindle Orientation
		//A tool data specification that accounts for the way the tool is mounted in the turret. Orientations include right-handed (RG) and left-handed (LF).
		vector3dPtr m_directionPtr; // Cutting Direction
		// Field in the tool data display that shows the rotational direction of the spindle and the directional orientation of the tool.
		// This is not null only for 6-axis-contour machines (like 6-axis-chain-saw machines)
	};
	typedef std::map<misc::mwstring, mwSpindle>  mwSpindles; // This map defines a spindle (For every tool there is a string, a 3d vector, and for 6-axis contour machines there is also a cutting direction)
}

#endif