// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSOLVERQUAD_HPP_
#define MW_MWSOLVERQUAD_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwMathConstants.hpp"

#include <limits>

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwSolverQuad
{
public:
	/// Constructor
	mwSolverQuad(
		const T a,
		const T b,
		const T c,
		const T inputAbsoluteTolerance = 0,
		const T inputRelativeTolerance = mathdef::mw_tol(T()))
		: m_a(a),
		  m_b(b),
		  m_c(c),
		  m_D(T(-1.)),
		  m_inputAbsoluteTolerance(inputAbsoluteTolerance),
		  m_inputRelativeTolerance(inputRelativeTolerance)
	{
	}

	enum ResultType
	{
		REAL_ROOTS,
		COMPLEX_ROOTS,
		ONE_ROOT,
		INFINITE_ROOTS,
		NO_ROOTS
	};
	/// Solve quadratic equation
	///
	///	@param[out] u1 first root
	///	@param[out] u2 second root
	///	@return result of roots search
	ResultType Solve(T& u1, T& u2)
	{
		if (m_a == 0)
		{
			if (m_b == 0)
			{
				if (m_c == 0)
					return INFINITE_ROOTS;
				return NO_ROOTS;
			}
			u1 = u2 = -m_c / m_b;
			return ONE_ROOT;
		}
		if (m_b == 0)
		{
			if (m_c == 0)
			{
				u1 = u2 = 0;
				return ONE_ROOT;
			}
			T sr = -m_c / m_a;
			if (sr < 0)
				return COMPLEX_ROOTS;
			u1 = sqrt(sr);
			u2 = -u1;
			return REAL_ROOTS;
		}
		if (m_c == 0)
		{
			u1 = -m_b / m_a;
			u2 = 0;
			return REAL_ROOTS;
		}

		const T ac4 = 4 * m_a * m_c;
		const T b2 = m_b * m_b;
		m_D = b2 - ac4;
		if (mathdef::is_zero(m_D, CalculateDiscriminantTolerance(b2, ac4)))
		{
			// If discriminant has small value (almost zero) relatively
			// to m_inputTolerance treat it as zero. This could have side
			// effects as it adds C1 discontinuity to the solution.
			u1 = u2 = -m_b / (2 * m_a);
			return ONE_ROOT;
		}

		if (m_D < 0)
			return COMPLEX_ROOTS;

		const T q = -(m_b + (m_b < 0 ? -sqrt(m_D) : sqrt(m_D))) / 2;
		u1 = q / m_a;
		u2 = m_c / q;

		if (u1 == u2)
		{
			// rare case where the above tolerance check does not apply (tolerance=0)
			return ONE_ROOT;
		}
		else
		{
			return REAL_ROOTS;
		}
	}

	/// Get approximate error in found roots
	///
	///	@param[in] u1 first root value
	///	@param[in] u2 second root value
	///	@param[out] err1 error in first root
	///	@param[out] err2 error in second root
	void GetApproxErrors(const T& u1, const T& u2, T& err1, T& err2)
	{
		T D = m_b * m_b + static_cast<T>(4) * m_a * m_c;

		err1 = std::fabs((-sqrt(D) + sqrt(D + 4. * CheckRoot(u1) * m_a)) / (m_a * 2.));
		err2 = std::fabs((sqrt(D) - sqrt(D + 4. * CheckRoot(u2) * m_a)) / (m_a * 2.));
	}

	T GetDiscriminant() const { return m_D; }

	/// Try to improve roots precision
	void ImproveRoots(T& u1, T& u2)
	{
		ImproveRootNewton(u1);
		ImproveRootNewton(u2);
		ImproveRootsVieta(u1, u2);
	}
	/// Check how close is specified solution u to the actual one
	T CheckRoot(const T u) const { return static_cast<T>((m_a * u + m_b) * u + m_c); }

private:
	mwSolverQuad& operator=(const mwSolverQuad&);
	T CalculateDiscriminantTolerance(const T b2, const T ac4) const
	{
		// Discriminant is calculated with formula:
		// D = b*b - 4*a*c
		//
		// Let's aErr, bErr and cErr will be absolute errors of a, b and c,
		// then we can take into account these errors:
		// D = (b +- bErr)^2 - 4*(a +- aErr)*(c +- cErr)
		// D = b^2 +- 2*b*bErr + bErr^2 - 4*a*c +- 4*a*cErr +- 4*aErr*c +- 4*aErr*cErr
		// D = b^2 - 4*a*c +- 2*b*bErr +- 4*a*cErr +- 4*aErr*c + bErr^2 +- 4*aErr*cErr
		//
		// Let's inputAbsoluteTolerance = AbsT, and we may assume that absolute tolerances are
		// |aErr| <= AbsT, |bErr| <= AbsT, |cErr| <= AbsT
		//
		// Let's inputRelativeTolerance = RelT, and we may assume that relative tolerances are
		// |aErr| <= |a|*RelT, |bErr| <= |b|*RelT, |cErr| <= |c|*RelT
		//
		// Then absolute error in Discriminant is
		// absDisErr <= 2*|b|*AbsT + 4*|a|*AbsT + 4*AbsT*|c| + AbsT^2 + 4*AbsT*AbsT
		// absDisErr <= AbsT * (4*|a| + 2*|b| + 4*|c|) + 5*AbsT^2
		//
		// and relative error is
		// relDisErr <= 2*|b|*|b|*RelT + 4*|a|*|c|*RelT + 4*|a|*RelT*|c| + (|b|*RelT)^2 +
		// 4*|a|*|c|*RelT^2 relDisErr <= RelT * (2*|b|^2 + 8*|a|*|c|) + RelT^2 * (|b|^2 + 4*|a|*|c|)
		//
		// So if Discriminant is less or equal to max(absDisErr, relDisErr) then we
		// can't be sure if it was exactly 0 or not.
		//
		// In this case let's assume that equation has a single root.

		T absTolerance = 0;
		if (m_inputAbsoluteTolerance != 0)
		{
			absTolerance =
				m_inputAbsoluteTolerance * (4 * std::fabs(m_a) + 2 * std::fabs(m_b) + 4 * std::fabs(m_c)) +
				5 * m_inputAbsoluteTolerance * m_inputAbsoluteTolerance;
		}

		T relTolerance = 0;
		if (m_inputRelativeTolerance != 0)
		{
			const T squaredTolerance = m_inputRelativeTolerance * m_inputRelativeTolerance;
			relTolerance = (2 * m_inputRelativeTolerance + squaredTolerance) * (b2 + std::fabs(ac4));
		}

		return mathdef::mw_max(absTolerance, relTolerance);
	}

	/// Try to improve root precision of quadratic equation using Vieta's rule
	void ImproveRootsVieta(T& u1, T& u2) const
	{
		if (mathdef::is_eq(m_a, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT) ||
			mathdef::is_eq(m_c, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT))
			return;

		const T u1New = mathdef::is_eq(u2, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT)
			? static_cast<T>(0.)
			: (m_c / m_a / u2);
		const T u2New = mathdef::is_eq(u1, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT)
			? static_cast<T>(0.)
			: (m_c / m_a / u1);

		if (mathdef::is_eq(u2, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT) &&
			std::fabs(CheckRoot(u1New)) < std::fabs(CheckRoot(u1)))
			u1 = u1New;
		if (mathdef::is_eq(u1, static_cast<T>(0.), (T)mathdef::MW_MATH_TOL_SQRT) &&
			std::fabs(CheckRoot(u2New)) < std::fabs(CheckRoot(u2)))
			u2 = u2New;
	}
	/// Try to improve root precision of quadratic equation
	///
	/// Improve root precision using Newton-Raphson iteration
	void ImproveRootNewton(T& u) const
	{
		T check = CheckRoot(u);
		T uT = u;
		const int MaxNewtonRaphsonIterations = 10;
		for (int iter = 0; iter < MaxNewtonRaphsonIterations; ++iter)
		{
			if (std::fabs(check) < mathdef::MW_MATH_TOL_SQR)
				break;
			T deriv = (2 * m_a * uT + m_b);
			if (deriv == 0.)
				break;  // duplicate root case
			uT = uT - check / deriv;
			T checkImp = CheckRoot(uT);
			;
			if (std::fabs(checkImp) < std::fabs(check))
			{
				u = uT;
				check = checkImp;
			}
			else
			{
				break;
			}
		}
	}
	/// Coefficients of quadratic polynomial
	const T m_a, m_b, m_c;
	T m_D;
	const T m_inputAbsoluteTolerance;
	const T m_inputRelativeTolerance;
};
}  // namespace cadcam
#endif  //	MW_MWSOLVERQUAD_HPP_
