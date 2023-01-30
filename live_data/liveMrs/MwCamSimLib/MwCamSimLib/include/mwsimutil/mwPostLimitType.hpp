// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWPOSTLIMITTYPE_HPP_
#define MW_MWPOSTLIMITTYPE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostLimitType
	{
	public:
		//#############################################################################
		enum rangeLimits
		{
			LIMIT_MIN,
			LIMIT_MAX
		};
		enum axisTypes
		{
			AXIS_X = 0,
			AXIS_Y = 1,
			AXIS_Z = 2,
			AXIS_R1 = 3,
			AXIS_R2 = 4,
			AXIS_R3 = 5
		};
		//#############################################################################
		class mwLimits
		{
		public:

			mwLimits()
			{
				m_value = 0.;
				m_exceed = false;
			}

			mwLimits(const double value, const bool exceed)
				: m_value(value) , m_exceed(exceed){}

			const double GetValue() const {return m_value;}
			void SetRange(const double value) {m_value = value;}
			const bool GetExceed() const {return m_exceed;}
			void SetExceed(const bool exceed) {m_exceed = exceed;}

		private:

			double      m_value;
			bool        m_exceed;
		};//end class mwLimits
		//#############################################################################
		mwPostLimitType()
		{
			m_maxX.SetRange(-1e308);
			m_minX.SetRange(1e308);

			m_maxY.SetRange(-1e308);
			m_minY.SetRange(1e308);

			m_maxZ.SetRange(-1e308);
			m_minZ.SetRange(1e308);

			m_maxR1.SetRange(-1e308);
			m_minR1.SetRange(1e308);

			m_maxR2.SetRange(-1e308);
			m_minR2.SetRange(1e308);

			m_maxR3.SetRange(-1e308);
			m_minR3.SetRange(1e308);

			m_circular.SetRange(0);
		}
		//#############################################################################
		const mwLimits GetMinX() const {return m_minX;} 
		mwLimits& GetMinX() {return m_minX;}
		void SetMinX(const mwLimits l) {m_minX = l;}

		const mwLimits GetMaxX() const {return m_maxX;} 
		mwLimits& GetMaxX() {return m_maxX;}
		void SetMaxX(const mwLimits l) {m_maxX = l;}

		const mwLimits GetMinY() const {return m_minY;} 
		mwLimits& GetMinY() {return m_minY;}
		void SetMinY(const mwLimits l) {m_minY = l;}

		const mwLimits GetMaxY() const {return m_maxY;} 
		mwLimits& GetMaxY() {return m_maxY;}
		void SetMaxY(const mwLimits l) {m_maxY = l;}

		const mwLimits GetMinZ() const {return m_minZ;} 
		mwLimits& GetMinZ() {return m_minZ;}
		void SetMinZ(const mwLimits l) {m_minZ = l;}

		const mwLimits GetMaxZ() const {return m_maxZ;} 
		mwLimits& GetMaxZ() {return m_maxZ;}
		void SetMaxZ(const mwLimits l) {m_maxZ = l;}

		const mwLimits GetMinR1() const {return m_minR1;} 
		mwLimits& GetMinR1() {return m_minR1;}
		void SetMinR1(const mwLimits l) {m_minR1 = l;}

		const mwLimits GetMaxR1() const {return m_maxR1;} 
		mwLimits& GetMaxR1() {return m_maxR1;}
		void SetMaxR1(const mwLimits l) {m_maxR1 = l;}

		const mwLimits GetMinR2() const {return m_minR2;} 
		mwLimits& GetMinR2() {return m_minR2;}
		void SetMinR2(const mwLimits l) {m_minR2 = l;}

		const mwLimits GetMaxR2() const {return m_maxR2;} 
		mwLimits& GetMaxR2() {return m_maxR2;}
		void SetMaxR2(const mwLimits l) {m_maxR2 = l;}

		const mwLimits GetMinR3() const {return m_minR3;} 
		mwLimits& GetMinR3() {return m_minR3;}
		void SetMinR3(const mwLimits l) {m_minR3 = l;}

		const mwLimits GetMaxR3() const {return m_maxR3;} 
		mwLimits& GetMaxR3() {return m_maxR3;}
		void SetMaxR3(const mwLimits l) {m_maxR3 = l;}

		const mwLimits GetCircular() const { return m_circular; }
		mwLimits& GetCircular() { return m_circular; }
		void SetCircular(const mwLimits l) { m_circular = l; }
		//#############################################################################
		unsigned short CountExceededLimits() const
		{
			unsigned short limits = 0;
			if(m_minX.GetExceed())
				limits++;
			if(m_maxX.GetExceed())
				limits++;
			if(m_minY.GetExceed())
				limits++;
			if(m_maxY.GetExceed())
				limits++;
			if(m_minZ.GetExceed())
				limits++;
			if(m_maxZ.GetExceed())
				limits++;
			if(m_minR1.GetExceed())
				limits++;
			if(m_maxR1.GetExceed())
				limits++;
			if(m_minR2.GetExceed())
				limits++;
			if(m_maxR2.GetExceed())
				limits++;

			return limits;
		}
		//#############################################################################
	private:
		//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		mwLimits m_minX;
		mwLimits m_maxX;
		mwLimits m_minY;
		mwLimits m_maxY;
		mwLimits m_minZ;
		mwLimits m_maxZ;
		mwLimits m_minR1;
		mwLimits m_maxR1;
		mwLimits m_minR2;
		mwLimits m_maxR2;
		mwLimits m_minR3;
		mwLimits m_maxR3;
		mwLimits m_circular;
#pragma warning(pop)
		//#############################################################################
	};
	//#############################################################################
}
#endif	//	MW_MWPOSTLIMITTYPE_HPP_
