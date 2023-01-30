// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWENRICHEDPOSTEDTP_HPP_
#define MW_MWENRICHEDPOSTEDTP_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwEnrichedPostedMove.hpp"
#include "mwMemoryPoolList.hpp"

#include <list>


namespace cadcam
{
class MW_5AXUTIL_API mwEnrichedPostedTP
{
public:
	typedef mwEnrichedPostedMove EnrichedPostedMove;
	typedef misc::mwMemoryPoolList<EnrichedPostedMove> EnrichedPostedMovesList;
	typedef EnrichedPostedMovesList::const_iterator ConstIterator;
	typedef EnrichedPostedMovesList::iterator Iterator;

	/// Default Constructor
	mwEnrichedPostedTP();

	/// Default Destructor
	~mwEnrichedPostedTP();

	/// copy constructor
	mwEnrichedPostedTP(const mwEnrichedPostedTP& rToCopy);

	/// copy operator
	const mwEnrichedPostedTP& operator=(const mwEnrichedPostedTP& rToCopy);

	const bool operator==(const mwEnrichedPostedTP& tc) const;

	const bool operator!=(const mwEnrichedPostedTP& tc) const;

	/// return the number of moves
	inline const size_t GetSize() const { return m_movesList.size(); }

	/// returns a bidirectional iterator to the first move
	inline ConstIterator GetMovesBegin() const { return m_movesList.begin(); }

	/// returns a bidirectional iterator that points just beyond the end of the moves.
	inline ConstIterator GetMovesEnd() const { return m_movesList.end(); }

	inline Iterator GetMovesBegin() { return m_movesList.begin(); }

	inline Iterator GetMovesEnd() { return m_movesList.end(); }

	/// return true if tp is empty
	inline const bool IsEmpty() const { return m_movesList.empty(); }

	/// push back an enriched move
	void push_back(const EnrichedPostedMove& enrichedMove);

	/// insert a enrichedMove
	void insert(Iterator position, const EnrichedPostedMove& move);

	/// remove an enrichedMove
	Iterator remove(Iterator toRemove);

private:
	EnrichedPostedMovesList m_movesList;

	void ValidateNrOfAxes(const size_t nrOfAxes);
};
}  // namespace cadcam
#endif  //	MW_MWENRICHEDPOSTEDTP_HPP_
