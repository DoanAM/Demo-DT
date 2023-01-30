// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWINTPBEZIERCURVE_HPP_
#define MW_MWINTPBEZIERCURVE_HPP_
#include "mw3dPoint.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// implements a Bezier cubic curve
template <typename Par, typename Val = mw3dPoint<Par>>
class MW_5AXUTIL_API mwIntpBezierCurve
{
public:
	mwIntpBezierCurve() {}

	/// Creates a Bezier curve segment x = f(t), t=[0..1]
	///	@param startVal the function value at t = 0
	///	@param endVal ... at t = 1
	///	@param dS the slope at the start point (t = 0)
	///	@param dE slope at the end point (t  = 1)
	mwIntpBezierCurve(Val startVal, Val endVal, Val dS, Val dE)
		: f0(startVal), f1(endVal), df0(dS), df1(dE)
	{
	}

	/// evaluates the curve at given point
	///	@param t function parameter t = [0..1]
	///	@param order of derivative to get. Zero by default which means the curve itself.
	///	@returns the value of interpolating polynomial at given parameter value
	inline Val Evaluate(const Par t, const int order = 0) const
	{
		Par t2 = t * t, t3 = t2 * t;
		Val b1 = df0 / static_cast<Par>(3.) + f0, b2 = f1 - df1 / static_cast<Par>(3.), b0 = f0,
			b3 = f1;
		Par omt2 = static_cast<Par>((1. - t) * (1. - t)),
			omt3 = static_cast<Par>(omt2 * (1. - t));  // (t-1) squared
		switch (order)
		{
		case 3:
			return static_cast<Val>(
				static_cast<Par>(-6.) * b0 + static_cast<Par>(18.) * b1 -
				static_cast<Par>(18.) * b2 + static_cast<Par>(6.) * b3);
		case 2:
			return static_cast<Val>(
				static_cast<Par>(6. * (1. - t)) * b0 - static_cast<Par>(12. * (1. - t)) * b1 +
				static_cast<Par>(6. * t) * b1 + static_cast<Par>(6. * (1. - t)) * b2 -
				static_cast<Par>(12. * t) * b2 + static_cast<Par>(6.) * t * b3);
		case 1:
			return static_cast<Val>(
				static_cast<Par>(-3. * omt2) * b0 + static_cast<Par>(3. * omt2) * b1 -
				static_cast<Par>(6. * t * (1. - t)) * b1 + static_cast<Par>(6. * t * (1 - t)) * b2 -
				static_cast<Par>(3. * t2) * b2 + static_cast<Par>(3. * t2) * b3);
		default:
			return static_cast<Val>(
				static_cast<Par>(omt3) * b0 + static_cast<Par>(3. * t * omt2) * b1 +
				static_cast<Par>(3. * t2 * (1. - t)) * b2 + t3 * b3);
		}
	}
	/// gets function values at start/end
	///	@param valStart variable to return value at start point
	///	@param valEnd variable to return value at the end point
	inline void GetValues(Val& valStart, Val& valEnd) const
	{
		valStart = f0;
		valEnd = f1;
	}

	/// gets function tangents at start/end
	///	@param tanStart variable to return tangent at start point
	///	@param tanEnd variable to return tangent at the end point
	inline void GetTangents(Val& tanStart, Val& tanEnd) const
	{
		tanStart = df0;
		tanEnd = df1;
	}

	/// sets curve tangents at start/end
	///	@param tanStart tangent at start point
	///	@param tanEnd tangent at the end point
	inline void SetTangents(const Val& tanStart, const Val& tanEnd)
	{
		df0 = tanStart;
		df1 = tanEnd;
	}
	/// Apply transformation to the curve
	inline void Transform(const mwMatrix<Par, 4, 4>& m)
	{
		mwMatrix<Par, 4, 4> r = m;
		f0.Transform(m);
		f1.Transform(m);
		r[0][3] = r[1][3] = r[2][3] = 0;
		df0.Transform(r);  // don't offset tangent vectors
		df1.Transform(r);
	}

	inline void GetExtremes(const Par t0, const Par t1, Par& min, Par& max)
	{
		Val s0 = Evaluate(t0);
		Val s1 = Evaluate(t1);


		min = mathdef::mw_min(s0.y(), s1.y());
		max = mathdef::mw_max(s0.y(), s1.y());

		mwIntpBezierCurve<Par> crv = *this;

		Val b1 = crv.df0 / static_cast<Par>(3) + crv.f0,
			b2 = crv.f1 - crv.df1 / static_cast<Par>(3), b0 = crv.f0, b3 = crv.f1;
		Par a = -3 * b0.y() + 9 * b1.y() - 9 * b2.y() + 3 * b3.y(),
			b = 6 * b0.y() - 12 * b1.y() + 6 * b2.y(), c = -3 * b0.y() + 3 * b1.y();

		Par D = b * b - 4 * a * c;
		Par ex1 = -1, ex2 = -1;

		if (D < 0)
			return;

		ex1 = (-b + sqrt(D)) / static_cast<Par>(2) / a;

		if (!mathdef::is_eq(D, 0))
			ex2 = (-b - sqrt(D)) / static_cast<Par>(2) / a;

		if (ex1 >= t0 && ex1 <= t1)
		{
			Par tmp = crv.Evaluate(ex1).y();
			max = mathdef::mw_max(max, tmp);
			min = mathdef::mw_min(min, tmp);
		}
		if (ex2 > t0 && ex2 < t1)
		{
			Par tmp = crv.Evaluate(ex2).y();
			max = mathdef::mw_max(max, tmp);
			min = mathdef::mw_min(min, tmp);
		}
	}

	/// gets chordal deviation of curve if approximated with polyline
	///	@param nSeg number of segments in approximating polyline
	///	@returns maximum deviation value

	inline double GetUniformDeviation(int nSeg)
	{
		if (nSeg <= 0)
			throw misc::mwException(0, _T("Invalid input"));

		Par dt = static_cast<Par>(1. / nSeg);
		double dev = -1;
		for (int i = 0; i < nSeg; ++i)
		{
			Par t0 = Par(i) * dt;
			Par t1 = Par(i + 1) * dt;
			Val s0 = Evaluate(t0);
			Val s1 = Evaluate(t1);

			// shift f0 to coordinate center and rotate to coincide w. abscissas axis
			// prepare matrices for transform
			mwMatrix<Par, 4, 4> T;
			T.LoadIdentity();
			Par ct = (s1.x() - s0.x()) / ~(s1 - s0);
			Par st = -(s1.y() - s0.y()) / ~(s1 - s0);
			T[0][0] = ct;
			T[0][1] = st;
			T[1][0] = -st;
			T[1][1] = ct;
			T[3][0] = -s0.x() * ct + s0.y() * st;
			T[3][1] = -s0.x() * st - s0.y() * ct;
			T[3][2] = -s0.z();
			T.Transpose();

			mwIntpBezierCurve<Par> crv = *this;
			crv.Transform(T);

			Val b1 = crv.df0 / (Par)3. + crv.f0, b2 = crv.f1 - crv.df1 / (Par)3., b0 = crv.f0,
				b3 = crv.f1;
			Par a = (Par)-3. * b0.y() + (Par)9. * b1.y() - (Par)9. * b2.y() + (Par)3. * b3.y(),
				b = (Par)6. * b0.y() - (Par)12. * b1.y() + (Par)6. * b2.y(),
				c = (Par)-3. * b0.y() + (Par)3. * b1.y();

			Par D = b * b - (Par)4. * a * c;
			Par ex1 = -1, ex2 = -1;

			if (D < 0)
				continue;

			ex1 = (-b + sqrt(D)) / (Par)2. / a;

			if (!mathdef::is_eq(D, (Par)0.))
				ex2 = (-b - sqrt(D)) / (Par)2. / a;

			double max = -1;

			if (ex1 > t0 && ex1 < t1)
				max = fabs(crv.Evaluate(ex1).y());
			if (ex2 > t0 && ex2 < t1)
			{
				double tmp = fabs(crv.Evaluate(ex2).y());
				if (tmp > max)
					max = tmp;
			}

			if (max > dev)
				dev = max;
		}
		return dev;
	}
private:
	Val f0, f1, df0, df1;
};
}  // namespace cadcam
#endif  //	MW_MWINTPBEZIERCURVE_HPP_
