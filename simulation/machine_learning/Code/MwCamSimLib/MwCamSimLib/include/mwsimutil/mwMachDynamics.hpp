// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWMACHDYNAMICS_HPP_
#define MW_MWMACHDYNAMICS_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwMachDynamics : public measures::mwMeasurable
	{
	public:
		//#############################################################################
		mwMachDynamics();
		//#############################################################################
		mwMachDynamics(
			const Units units,
			const double feedRate, 
			const double rapidRate, 
			const double toolChangeTime = 5);
		//#############################################################################
		mwMachDynamics(const mwMachDynamics& toCopy);
		//#############################################################################
		const mwMachDynamics& operator = (const mwMachDynamics& toCopy);
		//#############################################################################
		const bool operator == (const mwMachDynamics& toCompare) const;
		//#############################################################################
		const bool operator != (const mwMachDynamics& toCompare) const;
		//#############################################################################
		inline void SetFeedRate(const double feedRate)
		{
			m_feedRate = feedRate;
		}
		//#############################################################################
		const double GetFeedRate() const
		{
			return m_feedRate;
		}
		//#############################################################################
		inline void SetRapidRate(const double rapidRate)
		{
			m_rapidRate = rapidRate;
		}
		//#############################################################################
		const double GetRapidRate() const
		{
			return m_rapidRate;
		}
		//#############################################################################
		inline void SetToolChangeTime(const double toolChangeTime)
		{
			m_toolChangeTime = toolChangeTime;
		}
		//#############################################################################
		const double GetToolChangeTime() const
		{
			return m_toolChangeTime;
		}
		//#############################################################################
	protected:
		//#############################################################################
		//! scaled all measurable data of the mwMachDynamics by the given scale factor
		/*!
			\param units not used here 
			\param scaleFactor  the mwMachDynamics is scaled by the scale factor
		*/
		void Scale(const Units units, const double& scaleFactor);
		//#############################################################################
	private:
		//#############################################################################
		double m_feedRate;
		double m_rapidRate;
		double m_toolChangeTime;
		//#############################################################################
	};
	//#############################################################################
};
//#############################################################################
#endif	//	MW_MWMACHDYNAMICS_HPP_
