// (C) 2007-2021 by ModuleWorks GmbH
// Owner: 5Axis Multiblade

/// \file
///  this module describes the
/// mwPostedNaxMove class

//#############################################################################

#ifndef MW_MWPOSTEDNAXMOVE_HPP_
#define MW_MWPOSTEDNAXMOVE_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
#include <map>
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a posted N axis move.
	class MW_5AXUTIL_API mwPostedNaxMove : public mwPostedMove
	{
	public:

		typedef std::vector<double>			RobotRealAxisValues;

		enum EulerAngleType
		{
			Rx_Ry_Rz = 0,
			Rz_Ry_Rx = 1
		};

		//#############################################################################
		//!Default constructor
		mwPostedNaxMove(const bool shortPostedMove = false);
		//#############################################################################
		//!Constructor
		mwPostedNaxMove(
			const std::vector<double>& axisValue,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType,
			const point3d& newPotSurfContPnt,
			const point3d& newPotSurfContPntOrient,
			const size_t newPotSurfID,
			const bool newPotSurfContPntPresent,
			const size_t indexToPostedMove,
			const bool addByPost);

		mwPostedNaxMove(
			const std::vector<double>& axisValue,
			const double feedr,
			const bool rapidFlag,
			const Types moveType);

		//#############################################################################
		//!Constructor
		//#############################################################################
		// !Virtual destructor
		~mwPostedNaxMove();
		//!Copy constructor
		/*!Creates a exact copy of a given tool 
			\param toCopy tool to create a copy of
		*/
		mwPostedNaxMove( const mwPostedNaxMove &toCopy );
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwPostedNaxMove &operator = (const mwPostedNaxMove &toCopy);
		bool operator == (const mwPostedNaxMove& toCompare) const;
		//#############################################################################
		virtual void AcceptVisitor( mwPostedVisitor &visitor ) const;
		//#############################################################################
		const mwPostedMovePtr Clone() const
		{
			return new mwPostedNaxMove(*this);
		}

		const RobotRealAxisValues& GetAxisValues() const;

		void SetAxisValues(const RobotRealAxisValues& value);
		
		void AddAxisValue(const double& value);

		void SetEulerAngles(const vector3d& value, EulerAngleType type);

		const post::mwPostedMove::vector3d& GetEulerAngles(
			mwPostedNaxMove::EulerAngleType type) const;

		//#############################################################################
		protected:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################
		void Copy(const mwPostedNaxMove &toCopy);
		//#############################################################################
		RobotRealAxisValues				m_axisValues;
		//#############################################################################

		std::map<EulerAngleType, vector3d>	m_eulerAngles;
#pragma warning(pop)
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwPostedNaxMove> mwPostedNaxMovePtr;
};
//#############################################################################
#endif	//	MW_MWPOSTEDNAXMOVE_HPP_
