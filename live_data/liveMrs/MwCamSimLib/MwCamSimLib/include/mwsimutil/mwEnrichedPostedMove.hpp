// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWENRICHEDPOSTEDMOVE_HPP_
#define MW_MWENRICHEDPOSTEDMOVE_HPP_
#include "mwCadcamEnumDefinitions.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwEfficientVector.hpp"
#include "mwException.hpp"
#include "mwExtendedMoveAttribute.hpp"
#include "mwMemoryMultiAllocator.hpp"
#include "mwcadcamException.hpp"

#include <vector>

class MW_5AXUTIL_API mwEnrichedPostedMove
{
public:
	typedef std::vector<float> AxesValues;

	typedef misc::mwEfficientVector<float, unsigned short> AxisValuesContainer;
	typedef AxisValuesContainer::const_iterator AxesValuesConstIterator;
	typedef AxisValuesContainer::iterator AxesValuesIterator;

	typedef mwExtendedMoveAttributeList ExtendedAttributes;
	typedef ExtendedAttributes::iterator ExtendedAttributesIt;
	typedef ExtendedAttributes::const_iterator ExtendedAttributesConstIt;


	/// mwEnrichedPostedMove type
	typedef ::mwEnrichedPostedMoveN::Types Types;

	static const Types TYPE_UNDEFINED = ::mwEnrichedPostedMoveN::TYPE_UNDEFINED;
	static const Types APPROACH_MOVE = ::mwEnrichedPostedMoveN::APPROACH_MOVE;
	static const Types ENTRY_MACRO_MOVE = ::mwEnrichedPostedMoveN::ENTRY_MACRO_MOVE;
	static const Types CONNECTION_NOT_CLEAREANCE_ARREA_MOVE =
		::mwEnrichedPostedMoveN::CONNECTION_NOT_CLEAREANCE_ARREA_MOVE;
	static const Types CONNECTION_CLEAREANCE_ARREA_MOVE =
		::mwEnrichedPostedMoveN::CONNECTION_CLEAREANCE_ARREA_MOVE;
	static const Types EXIT_MACRO_MOVE = ::mwEnrichedPostedMoveN::EXIT_MACRO_MOVE;
	static const Types RETRACT_MOVE = ::mwEnrichedPostedMoveN::RETRACT_MOVE;
	static const Types CONTOUR_MOVE = ::mwEnrichedPostedMoveN::CONTOUR_MOVE;
	static const Types REWIND_RETRACT_MOVE = ::mwEnrichedPostedMoveN::REWIND_RETRACT_MOVE;
	static const Types REWIND_MOVE = ::mwEnrichedPostedMoveN::REWIND_MOVE;
	static const Types REWIND_APPROACH_MOVE = ::mwEnrichedPostedMoveN::REWIND_APPROACH_MOVE;
	static const Types DWELL_MOVE = ::mwEnrichedPostedMoveN::DWELL_MOVE;
	static const Types TOOL_CHANGE_MOVE = ::mwEnrichedPostedMoveN::TOOL_CHANGE_MOVE;
	static const Types KEEP_THIS_LAST_TYPES = ::mwEnrichedPostedMoveN::KEEP_THIS_LAST_TYPES;

	mwEnrichedPostedMove();

	mwEnrichedPostedMove(misc::mwMemoryMultiAllocator& allocator);

	/// Construct enrichedPostedMove
	explicit mwEnrichedPostedMove(const size_t nrOfAxes);

	/// copy constructor
	mwEnrichedPostedMove(const mwEnrichedPostedMove& rToCopy);

	mwEnrichedPostedMove(
		const mwEnrichedPostedMove& rToCopy, misc::mwMemoryMultiAllocator& allocator);

	/// Destruct enrichedPostedMove
	~mwEnrichedPostedMove();

	/// copy operator
	const mwEnrichedPostedMove& operator=(const mwEnrichedPostedMove& rToCopy);

	bool operator==(const mwEnrichedPostedMove& tc) const;

	bool operator!=(const mwEnrichedPostedMove& tc) const;

	const size_t GetNrOfAxes() const { return m_axisValues.size(); }
	void ResetAxes(const size_t nrOfAxes);

	/// gets AxesComment
	///
	///	@returns the AxesComment
	const misc::mwstring& GetComment() const
	{
		if (m_comment != MW_NULL)
			return *m_comment;
		else
			return GetEmptyString();
	};

	const misc::mwstring& GetMoveId() const
	{
		if (m_moveId != MW_NULL)
			return *m_moveId;
		else
			return GetEmptyString();
	};


	/// sets Comment
	///
	///	@param comment the new AxesComment

	void SetComment(const misc::mwstring& comment)
	{
		if (m_comment)
		{
			delete m_comment;
		}
		if (!comment.empty())
			m_comment = new misc::mwstring(comment);
		else
			m_comment = MW_NULL;
	};

	void SetMoveId(const misc::mwstring& rMoveId)
	{
		if (m_moveId)
		{
			delete m_moveId;
		}
		if (!rMoveId.empty())
			m_moveId = new misc::mwstring(rMoveId);
		else
			m_moveId = MW_NULL;
	};

	void SetAxisValue(size_t axisIndex, const float value) { m_axisValues[axisIndex] = value; }

	void SetAxesValues(const std::vector<float>& values)
	{
		m_axisValues.resize(values.size(), &values[0]);
	}

	void SetAxesValues(const AxisValuesContainer& values) { m_axisValues = values; }

	void SetAxesValues(const size_t axisCount, const float* values)
	{
		m_axisValues.resize(axisCount, values);
	}


	void SetAxisCount(const size_t axisCount) { m_axisValues.resize(axisCount); }

	/// returns a bidirectional iterator to the first axis
	AxesValuesConstIterator GetAxesBegin() const { return m_axisValues.begin(); }

	/// returns a bidirectional iterator that points just beyond the end of the axes.
	AxesValuesConstIterator GetAxesEnd() const { return m_axisValues.end(); }

	AxesValuesIterator GetAxesBegin() { return m_axisValues.begin(); }

	AxesValuesIterator GetAxesEnd() { return m_axisValues.end(); }

	const float GetAxisValue(size_t index) const { return m_axisValues[index]; }


	const AxisValuesContainer& GetAxesValues() const { return m_axisValues; }


	AxisValuesContainer& GetAxesValues() { return m_axisValues; }


	const size_t GetAxisCount() const { return m_axisValues.size(); }


	const float& operator[](const unsigned int index) const
	{
		if (index >= static_cast<unsigned int>(m_axisValues.size()))
			throw mwcadcamException(mwcadcamException::INDEX_OUT_OF_BOUNDS);

		return m_axisValues[index];
	}

	float& operator[](const unsigned int index)
	{
		if (index >= static_cast<unsigned int>(m_axisValues.size()))
			throw mwcadcamException(mwcadcamException::INDEX_OUT_OF_BOUNDS);

		return m_axisValues[index];
	}

	/// Get flag for rapid moves
	///	@returns flag for rapid moves
	bool IsRapid() const;

	/// Set flag for rapid moves
	///	@param toSet flag for rapid moves
	void SetIsRapid(const bool toSet);

	/// Get flag for phantom moves
	/// @returns flag for phantom moves
	bool IsPhantom() const;

	/// Set flag for phantom moves
	/// @param toSet flag for phantom moves
	void SetIsPhantom(const bool toSet);

	/// Get feed rate of the move
	///	@returns feed rate of the move
	float GetFeedrate() const;

	/// Set feed rate of the move
	///	@param value feed rate of the move
	void SetFeedrate(float value);

	/// Get Spindle Speed of the move
	///	@returns feed rate of the move
	float GetSpindleSpeed() const;

	/// Set Spindle Speed of the move
	///	@param value spindle speed of the move
	void SetSpindleSpeed(float value);

	/// Get Time of the move
	///	@returns feed rate of the move
	float GetTime() const;

	/// Set Time of the move
	///	@param value time of the move
	void SetTime(float value);

	/// Gets the move type
	Types GetMoveType() const;

	/// Sets the move type
	void SetMoveType(const Types moveType);

	/// Set extended attributes
	void SetExtendedAttributes(const ExtendedAttributes& toSet);
	/// Get extended attributes
	const ExtendedAttributes& GetExtendedAttributes() const;
	/// Get extended attributes to modify
	ExtendedAttributes& GetExtendedAttributes();

	/// Return axes value in string format (debug)
	misc::mwstring ToString() const;

	/// Return true if move is submove
	bool IsSubMove() const;

	/// Sets submove flag
	void SetSubMove(const bool toSet);


	MW_DEPRECATED("Deprecated in 2015.12, use GetAxisValue instead")
	float GetAxesValue(unsigned int index) const { return m_axisValues[index]; }


	MW_DEPRECATED("Deprecated in 2015.12, use SetComment instead")
	void SetAxesComment(const misc::mwstring& rAxesComment)
	{
		if (m_comment)
		{
			delete m_comment;
		}
		if (!rAxesComment.empty())
			m_comment = new misc::mwstring(rAxesComment);
		else
			m_comment = MW_NULL;
	};

	MW_DEPRECATED("Deprecated in 2015.12, use GetComment instead")
	const misc::mwstring& GetAxesComment() const
	{
		if (m_comment != MW_NULL)
			return *m_comment;
		else
			return GetEmptyString();
	};


	MW_DEPRECATED("Deprecated in 2015.12, please use GetAxesValues")
	const float* GetAxesValuesPtr() const  // deprecated
	{
		return &m_axisValues[0];
	}


	MW_DEPRECATED("Deprecated in 2015.12, please use GetAxesValues")
	float* GetAxesValuesPtr()  // deprecated
	{
		return &m_axisValues[0];
	}

private:
	misc::mwstring* m_comment;
	misc::mwstring* m_moveId;
	AxisValuesContainer m_axisValues;
	bool m_isRapid;
	bool m_isPhantom;
	float m_feedRate;
	float m_spindleSpeed;
	float m_time;
	Types m_moveType;
	bool m_isSubMove;

	static const misc::mwstring& GetEmptyString();


	/// extended attributes
	ExtendedAttributes m_extendedAttributes;
};
#endif  //	MW_MWENRICHEDPOSTEDMOVE_HPP_
