// (C) 2003-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMOVESCOMPMETHODS_HPP_
#define MW_MWMOVESCOMPMETHODS_HPP_

#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
/// provides 2 different methods to compare if 2 Moves are the same
class MW_5AXUTIL_API mwMovesCompMethods
{
public:
	/// It tests for equality by value
	///
	/// first is checking if they are the same type of move (CNC,35x,5x).And if yes then is cheeking
	/// if they are equal
	///	@param first the first move
	///	@param second the second move
	///	@return true if the moves are the same type and equal by value
	static const bool NormalCompareMoves(const mwCNCMove& first, const mwCNCMove& second);

	/// It tests that the moves are within tolerances
	///
	/// First is checking if they are the same type of move (CNC,35x,5x).
	///	And if yes then is cheeking if the moves are within delta tolerance
	///	and if the tool orientation vectors differ not more than minCos angle
	///	@param first the first move
	///	@param second the second move
	///	@param delta tolerance to be used
	///	@param minCos tolerance to be used
	///	@return true if the moves are the same type and within tolerances
	static const bool ExactCompareMoves(
		const mwCNCMove& first, const mwCNCMove& second, double delta, double minCos);

private:
	/// It tests that the moves are within tolerances
	///
	/// Is cheeking if the moves are within delta tolerance
	///	and if the tool orientation vectors differ not more than minCos angle
	///		@param move1 first move
	///		@param move2 second move
	///		@param delta tolerance to be used
	///		@param minCos tolerance to be used
	///		@return true if the moves are the same type and within tolerances
	static const bool ExactCompareTolerance5ax(
		const mw5axMove& move1, const mw5axMove& move2, double delta, double minCos);


	/// It tests that the moves are within tolerances
	///
	/// Is cheeking if the moves are within delta tolerance
	///	and if the tool orientation vectors differ not more than minCos angle
	///		@param move1 first move
	///		@param move2 second move
	///		@param delta tolerance to be used
	///		@param minCos tolerance to be used
	///		@return true if the moves are the same type and within tolerances
	static const bool ExactCompareTolerance6ax(
		const mw6axMove& move1, const mw6axMove& move2, double delta, double minCos);


	/// It tests that the moves are within tolerances
	///
	/// Is cheeking if the moves are within delta tolerance
	///	and if the tool orientation vectors differ not more than minCos angle
	///		@param move1 first move
	///		@param move2 second move
	///		@param delta tolerance to be used
	///		@param minCos tolerance to be used
	///		@return true if the moves are the same type and within tolerances
	static const bool ExactCompareTolerance3ax(
		const mw3axMove& move1, const mw3axMove& move2, double delta, double minCos);

	/// It tests that the moves are within tolerances
	///
	/// Is cheeking if the moves are within delta tolerance
	///	and if the tool orientation vectors differ not more than minCos angle
	///		@param move1 first move
	///		@param move2 second move
	///		@param delta tolerance to be used
	///		@param minCos tolerance to be used
	///		@return true if the moves are the same type and within tolerances
	static const bool ExactCompareToleranceCNC(
		const mwCNCMove& move1, const mwCNCMove& move2, double delta, double minCos);


	// ---------------------  Comparison Visitors ------------------

	/// Constructor not allowed since it's a static class
	mwMovesCompMethods();

	/// mwMoveCompare class
	///
	/// This class represents a mwMoveCompare
	class MW_5AXUTIL_API mwMoveCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		///	@param secondMove move to compare with
		mwMoveCompare(const mwCNCMove& secondMove);
		/// compares passed move with the one from constructor
		///
		///	@param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mwMoveCompare& operator=(mwMoveCompare&);  // avoid warning C4512
		/// passed move
		const mwCNCMove& mSecondMove;
		/// stores if they are equal
		bool mEquals;
	};

	/// mwCNCMoveCompare class
	///
	/// This class represents a mwCNCMoveCompare
	class MW_5AXUTIL_API mwCNCMoveCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to be compared with
		mwCNCMoveCompare(const mwCNCMove& firstMove);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mwCNCMoveCompare& operator=(mwCNCMoveCompare&);  // avoid warning C4512
		/// passed move
		const mwCNCMove& mFirstMove;
		/// stores if they are equal
		bool mEquals;
	};

	/// mw3axMoveCompare class
	///
	/// This class represents a mw3axMoveCompare
	class MW_5AXUTIL_API mw3axMoveCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to be compared with
		mw3axMoveCompare(const mw3axMove& firstMove);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw3axMoveCompare& operator=(mw3axMoveCompare&);  // avoid warning C4512
		/// passed move
		const mw3axMove& mFirstMove;
		/// stores if they are equal
		bool mEquals;
	};

	/// mw5axMoveCompare class
	///
	/// This class represents a mw5axMoveCompare
	class MW_5AXUTIL_API mw5axMoveCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to be compared with
		mw5axMoveCompare(const mw5axMove& firstMove);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw5axMoveCompare& operator=(mw5axMoveCompare&);  // avoid warning C4512
		/// passed move
		const mw5axMove& mFirstMove;
		/// stores if they are equal
		bool mEquals;
	};


	/// mw5axMoveCompare class
	///
	/// This class represents a mw5axMoveCompare
	class MW_5AXUTIL_API mw6axMoveCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to be compared with
		mw6axMoveCompare(const mw6axMove& firstMove);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw6axMoveCompare& operator=(const mw6axMoveCompare&);  // = delete
		/// passed move
		const mw6axMove& mFirstMove;
		/// stores if they are equal
		bool mEquals;
	};


	// -------------------  ExactComparison Visitors ----------------

	/// mwMoveExactCompare class
	///
	/// This class represents a mwMoveExactCompare
	class MW_5AXUTIL_API mwMoveExactCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param secondMove move to compare with
		/// @param delta tolerance need in comparation
		/// @param minCos tolerance need in comparation
		mwMoveExactCompare(const mwCNCMove& secondMove, double delta, double minCos);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mwMoveExactCompare& operator=(mwMoveExactCompare&);  // avoid warning C4512
		/// passed move
		const mwCNCMove& mSecondMove;
		/// stores if they are equal
		bool mEquals;
		/// tolerance
		double mDelta;
		/// tolerance
		double mMinCos;
	};

	/// mwCNCMoveExactCompare class
	///
	/// This class represents a mwCNCMoveExactCompare
	class MW_5AXUTIL_API mwCNCMoveExactCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to compare with
		/// @param delta tolerance need in comparation
		/// @param minCos tolerance need in comparation
		mwCNCMoveExactCompare(const mwCNCMove& firstMove, double delta, double minCos);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mwCNCMoveExactCompare& operator=(mwCNCMoveExactCompare&);  // avoid warning C4512
		/// passed move
		const mwCNCMove& mFirstMove;
		/// tolerance
		double mDelta;
		/// tolerance
		double mMinCos;
		/// stores if they are equal
		bool mEquals;
	};

	/// mw3axMoveExactCompare class
	///
	/// This class represents a mw3axMoveExactCompare
	class MW_5AXUTIL_API mw3axMoveExactCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to compare with
		/// @param delta tolerance need in comparation
		/// @param minCos tolerance need in comparation
		mw3axMoveExactCompare(const mw3axMove& firstMove, double delta, double minCos);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw3axMoveExactCompare& operator=(mw3axMoveExactCompare&);  // avoid warning C4512
		/// passed move
		const mw3axMove& mFirstMove;
		/// tolerance
		double mDelta;
		/// tolerance
		double mMinCos;
		/// stores if they are equal
		bool mEquals;
	};

	/// mw5axMoveExactCompare class
	///
	/// This class represents a mw5axMoveExactCompare
	class MW_5AXUTIL_API mw5axMoveExactCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to compare with
		/// @param delta tolerance need in comparation
		/// @param minCos tolerance need in comparation
		mw5axMoveExactCompare(const mw5axMove& firstMove, double delta, double minCos);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw5axMoveExactCompare& operator=(mw5axMoveExactCompare&);  // avoid warning C4512
		/// passed move
		const mw5axMove& mFirstMove;
		/// tolerance
		double mDelta;
		/// tolerance
		double mMinCos;
		/// stores if they are equal
		bool mEquals;
	};


	/// mw6axMoveExactCompare class
	///
	/// This class represents a mw6axMoveExactCompare
	class MW_5AXUTIL_API mw6axMoveExactCompare: public mwCNCMoveVisitor
	{
	public:
		/// constructor
		///
		/// @param firstMove move to compare with
		/// @param delta tolerance need in comparation
		/// @param minCos tolerance need in comparation
		mw6axMoveExactCompare(const mw6axMove& firstMove, double delta, double minCos);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mwCNCMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw3axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMove& mw);
		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw5axMarkedMove& mw);

		/// compares passed move with the one from constructor
		///
		/// @param mw move to compare
		virtual void Visit(const mw6axMove& mw);

		/// confirms if they are equal
		const bool Equals() const;

	private:
		mw6axMoveExactCompare& operator=(mw6axMoveExactCompare&);  // avoid warning C4512
		/// passed move
		const mw6axMove& mFirstMove;
		/// tolerance
		double mDelta;
		/// tolerance
		double mMinCos;
		/// stores if they are equal
		bool mEquals;
	};

	/// friend declarations to allow visitor classes to access the ExactCompareXXX functions defined
	/// withing the class
	friend class mw5axMoveExactCompare;
	/// friend declarations to allow visitor classes to access the ExactCompareXXX functions defined
	/// withing the class
	friend class mw3axMoveExactCompare;
	/// friend declarations to allow visitor classes to access the ExactCompareXXX functions defined
	/// withing the class
	friend class mwCNCMoveExactCompare;
};
}  // namespace cadcam
#endif  //	MW_MWMOVESCOMPMETHODS_HPP_
