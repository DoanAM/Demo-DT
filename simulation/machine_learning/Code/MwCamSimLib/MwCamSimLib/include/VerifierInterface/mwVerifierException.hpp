// (C) 2015-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVERIFIEREXCEPTION_HPP_
#define MW_MWVERIFIEREXCEPTION_HPP_

#include "mwVerifierDllDefinition.hpp"

#include <mwException.hpp>

#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif

class MW_VERIFIER_API mwVerifierException : public misc::mwException
{
public:
	enum errorIDD
	{
		SETSTOCKREVOLVED_INVALID_CONTOUR_ELEMENT = 3310,
		SETSTOCKREVOLVED_MIX_SUBCONTOURS = 3311,
		SETSTOCKREVOLVED_NOT_CONTINUOUS = 3312,
		SETSTOCKREVOLVED_SELF_INTERSECTIONS = 3313,
		SETSTOCKREVOLVED_ABOVE_ZERO = 3314,
		SETSTOCKREVOLVED_OPEN_AT_ZERO_ONLY = 3315,
		INTERSECTION_INFINITE_NO_END_ODD = 3316,
		INTERSECTION_INFINITE_NO_END_EVEN = 3317,
		INTERSECTION_UNIDENTIFIED_TYPE = 3318,
		INTERSECTION_ODD_NUMBER = 3319,
		INTERSECTION_MULTIPLICITY_UNDETERMINED = 3320,
		SETSTOCKREVOLVED_EMPTY_CONTOUR = 3321,
		STOCK_NOT_SET = 3322,
		OPEN_POLYLINE = 3323,
		VERIFIER_LICENSE_INVALID = 3324,
		OUT_OF_MEMORY = 3325,
		INVALID_RESTORE_POINT = 3326,
		ZERO_ECCENTRIC_AXIS = 4624,
		STOCK_MUST_BE_5X = 4625,
		MOVE_INTERPOLATION_AMBIGUOUS = 4881,
		ENGAGEMENT_NOT_SUPPORTED_FOR_TOOL = 4995,
		ENGAGEMENT_NOT_SUPPORTED_FOR_TOOLBEHAVIOR = 4996,
		CUTTING_SIMULATION_SMART_MEASURE_LICENSE_INVALID = 4997,
		UNSUPPORTED_HEIGHT_STOCK = 4998,
		UNSUPPORTED_REVOLVED_MODEL = 4999,
	};

	mwVerifierException(errorIDD errorCode, const misc::mwException* prevLevel = 0);

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
	\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;
};

#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif
