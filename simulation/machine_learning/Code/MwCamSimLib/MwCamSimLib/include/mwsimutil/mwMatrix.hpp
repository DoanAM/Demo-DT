// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMATRIX_HPP_
#define MW_MWMATRIX_HPP_
#include "mwDefines.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwLanguageFeatures.hpp"
#include "mwMathConstants.hpp"
#include "mwMathException.hpp"
#include "mwRealArray2D.hpp"
#include "mwVector.hpp"

namespace mw
{
namespace Verifier
{
namespace math
{
template <typename Real>
struct TMatrix3;
template <typename Real>
struct TMatrix4;
}  // namespace math
}  // namespace Verifier
}  // namespace mw

namespace cadcam
{
class MW_5AXUTIL_API mwMatrixNoInitializeTag
{
};
/// This struct represents a matrix
template <class T, int rows, int columns>
struct MW_5AXUTIL_API mwMatrix
{
public:
	/// Constructor
	///
	/// Constructs the matrix, no initialization performed for performance reasons
	explicit mwMatrix(mwMatrixNoInitializeTag) MW_NOEXCEPT {}

	/// Constructor
	///
	/// Constructs the matrix, if homogeneous then initialize as identity
	mwMatrix() { LoadIdentityIfIsHomogenous(BoolType<rows == columns>()); }

	/// Copy Constructor and cast constructor
	///
	/// The 'explicit' keyword is necessary in order to have NO implicit conversions
	///	between different types. (e.g. a matrix of floats converted implicit
	///	to a matrix of double)
	template <typename T2>
	explicit mwMatrix(const mwMatrix<T2, rows, columns>& matrix)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				(*this)[row][col] = static_cast<T>(matrix[row][col]);
			}
		}
	}

	/// Indexer operator for non const  values
	///
	/// Returns, for a given index, a real array row
	///	@param index position of the row in the matrix
	///	@returns a real array row
	cadcam::mwVector<T, columns>& operator[](unsigned long index) { return mArray[index]; }

	/// Indexer operator for const values
	///
	/// Returns, for a given index, a const real array row
	///	@param index position of the row in the matrix
	///	@returns a const real array row
	const cadcam::mwVector<T, columns>& operator[](unsigned long index) const
	{
		return mArray[index];
	}

	/// IsHomogenous
	///
	/// @returns true if the matrix is homogeneous (square) i.e.
	///	nr of rows == nr of columns
	bool IsHomogenous() const { return rows == columns; }

	/// Assignment operator, return a copy of the given matrix
#ifdef MW_USE_VS2008_COMPATIBILITY
	mwMatrix<T, rows, columns>& operator=(const mwMatrix<T, rows, columns>& toCopy)
	{
		if (&toCopy == this)
			return *this;

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				(*this)[i][j] = toCopy[i][j];
			}
		}
		return *this;
	}
#else
	mwMatrix<T, rows, columns>& operator=(const mwMatrix<T, rows, columns>& toCopy) =
		default;  // best benefits from compiler optimizations
#endif

	bool operator==(const mwMatrix<T, rows, columns>& tc) const
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				if ((*this)[i][j] != tc[i][j])
					return false;
			}
		}
		return true;
	}

	bool operator!=(const mwMatrix<T, rows, columns>& tc) const { return !(operator==(tc)); }

	/// Set identity matrix
	///
	/// The diagonal values of the matrix is 1 and the rest = 0.
	void LoadIdentity()
	{
		MW_STATIC_ASSERT_MSG(rows == columns, "Cannot set identity matrix");

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				mArray[i][j] = (i == j ? static_cast<T>(1) : static_cast<T>(0));
			}
		}
	}

	/// Is identity matrix
	///
	/// Test whether the matrix is identity
	///	@param prec optional precision can be passes (default 1e-5)
	bool IsIdentity(const T prec = 1e-5) const
	{
		MW_STATIC_ASSERT_MSG(rows == columns, "Cannot test for identity matrix");

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				const T val = (i == j ? static_cast<T>(1) : static_cast<T>(0));
				if (!mathdef::is_eq(mArray[i][j], val, prec))
					return false;
			}
		}
		return true;
	}

	/// Multiply matrices
	///	@param oth const reference to the multiplying matrix
	void operator*=(const mwMatrix<T, rows, columns>& oth)
	{
		MW_STATIC_ASSERT_MSG(rows == columns, "Can *= only homogeneous matrices");

		mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				T val = 0;
				for (int i = 0; i < columns; ++i)
				{
					val += mArray[row][i] * oth[i][col];
				}
				tmp[row][col] = val;
			}
		}

		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] = tmp[row][col];
			}
		}
	}

	/// Multiply matrices
	///	@param oth const reference to the multiplying matrix
	mwMatrix<T, rows, columns> operator*(const mwMatrix<T, rows, columns>& oth) const
	{
		MW_STATIC_ASSERT_MSG(rows == columns, "Can *= only homogeneous matrices");

		mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				T val(0);
				for (int i = 0; i < columns; ++i)
				{
					val += mArray[row][i] * oth[i][col];
				}
				tmp[row][col] = val;
			}
		}
		return tmp;
	}

	/// Multiply each element of the matrix with a scalar
	///	@param oth const reference to the scalar of T type
	void operator*=(const T oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] *= oth;
			}
		}
	}

	/// Divide each element of the matrix by a scalar
	///	@param oth const reference to the scalar of T type
	void operator/=(const T oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] /= oth;
			}
		}
	}

	/// Add matrices
	///	@param oth const reference to the other matrix
	void operator+=(const mwMatrix<T, rows, columns>& oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] += oth[row][col];
			}
		}
	}

	/// Add a scalar to each element of the matrix
	///	@param oth const reference to the scalar of T type
	void operator+=(const T oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] += oth;
			}
		}
	}

	/// Add matrices
	///	@param oth const reference to the other matrix
	void operator-=(const mwMatrix<T, rows, columns>& oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] -= oth[row][col];
			}
		}
	}

	/// Subtract a scalar from each element of the matrix
	///	@param oth const reference to the scalar of T type
	void operator-=(const T oth)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				mArray[row][col] -= oth;
			}
		}
	}

	/// Transposition in-place
	mwMatrix<T, rows, columns>& Transpose()
	{
		MW_STATIC_ASSERT_MSG(
			rows == columns, "Can do in-place transposition only for homogeneous matrices");

		T tmpVal;
		for (int row = 0; row + 1 < rows; ++row)
		{
			for (int col = row + 1; col < columns; ++col)
			{
				tmpVal = mArray[row][col];
				mArray[row][col] = mArray[col][row];
				mArray[col][row] = tmpVal;
			}
		}
		return *this;
	}

	/// Retrieves pointer to actual data
	///	@returns an array of elements
	inline T* GetData() { return &mArray[0][0]; }

	/// Retrieves pointer to actual data
	///	@returns an array of elements
	inline const T* GetData() const { return &mArray[0][0]; }

	/// Convert to string
	misc::mwstring ToString() const
	{
		misc::mwstring res;
		for (int row = 0; row < rows; ++row)
		{
			res += (row == 0) ? _T("(") : _T(" (");
			for (int col = 0; col < columns; ++col)
			{
				if (col)
					res += _T(", ");
				res += misc::from_value(mArray[row][col], 5);
			}
			res += _T(")");
		}
		return _T("[") + res + _T("]");
	}

	// Internal interface with mw::Verifier::math
	operator mw::Verifier::math::TMatrix3<T>&();
	operator const mw::Verifier::math::TMatrix3<T>&() const;
	operator mw::Verifier::math::TMatrix4<T>&();
	operator const mw::Verifier::math::TMatrix4<T>&() const;

protected:
private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	cadcam::mwVector<T, columns> mArray[rows];

	template <bool B>
	struct BoolType
	{
	};
	void LoadIdentityIfIsHomogenous(BoolType<true>) { LoadIdentity(); }
	void LoadIdentityIfIsHomogenous(BoolType<false>) {}

};  // end of struct

template <>
MW_5AXUTIL_API inline void mwMatrix<float, 4, 4>::LoadIdentity()
{
	cadcam::mwVector<float, 4>& row0 = mArray[0];
	cadcam::mwVector<float, 4>& row1 = mArray[1];
	cadcam::mwVector<float, 4>& row2 = mArray[2];
	cadcam::mwVector<float, 4>& row3 = mArray[3];
	row0[0] = row1[1] = row2[2] = row3[3] = 1.0f;
	row0[1] = row0[2] = row0[3] = row1[0] = row1[2] = row1[3] = row2[0] = row2[1] = row2[3] =
		row3[0] = row3[1] = row3[2] = 0.0f;
}
template <>
MW_5AXUTIL_API inline void mwMatrix<double, 4, 4>::LoadIdentity()
{
	cadcam::mwVector<double, 4>& row0 = mArray[0];
	cadcam::mwVector<double, 4>& row1 = mArray[1];
	cadcam::mwVector<double, 4>& row2 = mArray[2];
	cadcam::mwVector<double, 4>& row3 = mArray[3];
	row0[0] = row1[1] = row2[2] = row3[3] = 1;
	row0[1] = row0[2] = row0[3] = row1[0] = row1[2] = row1[3] = row2[0] = row2[1] = row2[3] =
		row3[0] = row3[1] = row3[2] = 0;
}

#ifdef MW_USE_VS2008_COMPATIBILITY
/// Assignment operator, return a copy of the given matrix
template <>
MW_5AXUTIL_API inline mwMatrix<float, 4, 4>& mwMatrix<float, 4, 4>::operator=(
	const mwMatrix<float, 4, 4>& toCopy)
{
	if (&toCopy == this)
		return *this;

	cadcam::mwVector<float, 4>& dstRow0 = mArray[0];
	const cadcam::mwVector<float, 4>& srcRow0 = toCopy[0];
	dstRow0[0] = srcRow0[0];
	dstRow0[1] = srcRow0[1];
	dstRow0[2] = srcRow0[2];
	dstRow0[3] = srcRow0[3];
	cadcam::mwVector<float, 4>& dstRow1 = mArray[1];
	const cadcam::mwVector<float, 4>& srcRow1 = toCopy[1];
	dstRow1[0] = srcRow1[0];
	dstRow1[1] = srcRow1[1];
	dstRow1[2] = srcRow1[2];
	dstRow1[3] = srcRow1[3];
	cadcam::mwVector<float, 4>& dstRow2 = mArray[2];
	const cadcam::mwVector<float, 4>& srcRow2 = toCopy[2];
	dstRow2[0] = srcRow2[0];
	dstRow2[1] = srcRow2[1];
	dstRow2[2] = srcRow2[2];
	dstRow2[3] = srcRow2[3];
	cadcam::mwVector<float, 4>& dstRow3 = mArray[3];
	const cadcam::mwVector<float, 4>& srcRow3 = toCopy[3];
	dstRow3[0] = srcRow3[0];
	dstRow3[1] = srcRow3[1];
	dstRow3[2] = srcRow3[2];
	dstRow3[3] = srcRow3[3];

	return *this;
}
#endif

// specialization for 4x4 matrices to benefit from compiler optimizations
template <>
MW_5AXUTIL_API inline bool mwMatrix<float, 4, 4>::operator==(const mwMatrix<float, 4, 4>& mat) const
{
	return (*this)[0][0] == mat[0][0] && (*this)[0][1] == mat[0][1] && (*this)[0][2] == mat[0][2] &&
		(*this)[0][3] == mat[0][3] && (*this)[1][0] == mat[1][0] && (*this)[1][1] == mat[1][1] &&
		(*this)[1][2] == mat[1][2] && (*this)[1][3] == mat[1][3] && (*this)[2][0] == mat[2][0] &&
		(*this)[2][1] == mat[2][1] && (*this)[2][2] == mat[2][2] && (*this)[2][3] == mat[2][3] &&
		(*this)[3][0] == mat[3][0] && (*this)[3][1] == mat[3][1] && (*this)[3][2] == mat[3][2] &&
		(*this)[3][3] == mat[3][3];
}

template <>
MW_5AXUTIL_API inline bool mwMatrix<double, 4, 4>::operator==(
	const mwMatrix<double, 4, 4>& mat) const
{
	return (*this)[0][0] == mat[0][0] && (*this)[0][1] == mat[0][1] && (*this)[0][2] == mat[0][2] &&
		(*this)[0][3] == mat[0][3] && (*this)[1][0] == mat[1][0] && (*this)[1][1] == mat[1][1] &&
		(*this)[1][2] == mat[1][2] && (*this)[1][3] == mat[1][3] && (*this)[2][0] == mat[2][0] &&
		(*this)[2][1] == mat[2][1] && (*this)[2][2] == mat[2][2] && (*this)[2][3] == mat[2][3] &&
		(*this)[3][0] == mat[3][0] && (*this)[3][1] == mat[3][1] && (*this)[3][2] == mat[3][2] &&
		(*this)[3][3] == mat[3][3];
}

/// MultiplyMatrices
///
/// Multiply matrices (result = mat * oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
///
///	NOTE: Initially this was defined as  operator* but was changed to
///	function because VC6 compiler issues errors when compiling code that uses it
///	(operator not found, could not deduce template arguments, etc).
template <class T, int rows, int columns, int othrows, int othcolumns>
inline cadcam::mwMatrix<T, rows, othcolumns> MultiplyMatrices(
	const mwMatrix<T, rows, columns>& mat, const mwMatrix<T, othrows, othcolumns>& oth)
{
	MW_STATIC_ASSERT_MSG(
		columns == othrows, "For Mat1 x Mat2, Mat1.NrColumns must equal Mat2.NrRows");

	mwMatrix<T, rows, othcolumns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < othcolumns; ++col)
		{
			T val = 0;
			for (int i = 0; i < columns; ++i)
			{
				val += mat[row][i] * oth[i][col];
			}
			tmp[row][col] = val;
		}
	}
	return tmp;
}

/// OptimizedMultiplyMatrices 4x4
///
/// Multiply matrices (result = mat * oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
/// @param rez result of multiplication
template <class T>
inline void OptimizedMultiplyMatrices(
	const mwMatrix<T, 4, 4>& mat, const mwMatrix<T, 4, 4>& oth, mwMatrix<T, 4, 4>& rez)
{
	const T* matData = mat.GetData();
	const T* othData = oth.GetData();
	T* rezData = rez.GetData();

	rezData[0] = matData[0] * othData[0] + matData[1] * othData[4] + matData[2] * othData[8] +
		matData[3] * othData[12];
	rezData[1] = matData[0] * othData[1] + matData[1] * othData[5] + matData[2] * othData[9] +
		matData[3] * othData[13];
	rezData[2] = matData[0] * othData[2] + matData[1] * othData[6] + matData[2] * othData[10] +
		matData[3] * othData[14];
	rezData[3] = matData[0] * othData[3] + matData[1] * othData[7] + matData[2] * othData[11] +
		matData[3] * othData[15];

	rezData[4] = matData[4] * othData[0] + matData[5] * othData[4] + matData[6] * othData[8] +
		matData[7] * othData[12];
	rezData[5] = matData[4] * othData[1] + matData[5] * othData[5] + matData[6] * othData[9] +
		matData[7] * othData[13];
	rezData[6] = matData[4] * othData[2] + matData[5] * othData[6] + matData[6] * othData[10] +
		matData[7] * othData[14];
	rezData[7] = matData[4] * othData[3] + matData[5] * othData[7] + matData[6] * othData[11] +
		matData[7] * othData[15];

	rezData[8] = matData[8] * othData[0] + matData[9] * othData[4] + matData[10] * othData[8] +
		matData[11] * othData[12];
	rezData[9] = matData[8] * othData[1] + matData[9] * othData[5] + matData[10] * othData[9] +
		matData[11] * othData[13];
	rezData[10] = matData[8] * othData[2] + matData[9] * othData[6] + matData[10] * othData[10] +
		matData[11] * othData[14];
	rezData[11] = matData[8] * othData[3] + matData[9] * othData[7] + matData[10] * othData[11] +
		matData[11] * othData[15];

	rezData[12] = matData[12] * othData[0] + matData[13] * othData[4] + matData[14] * othData[8] +
		matData[15] * othData[12];
	rezData[13] = matData[12] * othData[1] + matData[13] * othData[5] + matData[14] * othData[9] +
		matData[15] * othData[13];
	rezData[14] = matData[12] * othData[2] + matData[13] * othData[6] + matData[14] * othData[10] +
		matData[15] * othData[14];
	rezData[15] = matData[12] * othData[3] + matData[13] * othData[7] + matData[14] * othData[11] +
		matData[15] * othData[15];

	return;
}

/// OptimizedMultiplyTransformationMatrices 4x4
///
/// Multiply matrices (result = mat * oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
/// @param rez result of multiplication
template <class T>
inline void OptimizedMultiplyTransformationMatrices(
	const mwMatrix<T, 4, 4>& mat, const mwMatrix<T, 4, 4>& oth, mwMatrix<T, 4, 4>& rez)
{
	const T* matData = mat.GetData();
	const T* othData = oth.GetData();
	T* rezData = rez.GetData();

	rezData[0] = matData[0] * othData[0] + matData[1] * othData[4] + matData[2] * othData[8];
	rezData[1] = matData[0] * othData[1] + matData[1] * othData[5] + matData[2] * othData[9];
	rezData[2] = matData[0] * othData[2] + matData[1] * othData[6] + matData[2] * othData[10];
	rezData[3] =
		matData[0] * othData[3] + matData[1] * othData[7] + matData[2] * othData[11] + matData[3];

	rezData[4] = matData[4] * othData[0] + matData[5] * othData[4] + matData[6] * othData[8];
	rezData[5] = matData[4] * othData[1] + matData[5] * othData[5] + matData[6] * othData[9];
	rezData[6] = matData[4] * othData[2] + matData[5] * othData[6] + matData[6] * othData[10];
	rezData[7] =
		matData[4] * othData[3] + matData[5] * othData[7] + matData[6] * othData[11] + matData[7];

	rezData[8] = matData[8] * othData[0] + matData[9] * othData[4] + matData[10] * othData[8];
	rezData[9] = matData[8] * othData[1] + matData[9] * othData[5] + matData[10] * othData[9];
	rezData[10] = matData[8] * othData[2] + matData[9] * othData[6] + matData[10] * othData[10];
	rezData[11] =
		matData[8] * othData[3] + matData[9] * othData[7] + matData[10] * othData[11] + matData[11];

	return;
}

/// OptimizedMultiplyMatrices 3x3
///
/// Multiply matrices (result = mat * oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
/// @param rez result of multiplication
template <class T>
inline void OptimizedMultiplyMatrices(
	const mwMatrix<T, 3, 3>& mat, const mwMatrix<T, 3, 3>& oth, mwMatrix<T, 3, 3>& rez)
{
	rez[0][0] = mat[0][0] * oth[0][0] + mat[0][1] * oth[1][0] + mat[0][2] * oth[2][0];
	rez[0][1] = mat[0][0] * oth[0][1] + mat[0][1] * oth[1][1] + mat[0][2] * oth[2][1];
	rez[0][2] = mat[0][0] * oth[0][2] + mat[0][1] * oth[1][2] + mat[0][2] * oth[2][2];

	rez[1][0] = mat[1][0] * oth[0][0] + mat[1][1] * oth[1][0] + mat[1][2] * oth[2][0];
	rez[1][1] = mat[1][0] * oth[0][1] + mat[1][1] * oth[1][1] + mat[1][2] * oth[2][1];
	rez[1][2] = mat[1][0] * oth[0][2] + mat[1][1] * oth[1][2] + mat[1][2] * oth[2][2];

	rez[2][0] = mat[2][0] * oth[0][0] + mat[2][1] * oth[1][0] + mat[2][2] * oth[2][0];
	rez[2][1] = mat[2][0] * oth[0][1] + mat[2][1] * oth[1][1] + mat[2][2] * oth[2][1];
	rez[2][2] = mat[2][0] * oth[0][2] + mat[2][1] * oth[1][2] + mat[2][2] * oth[2][2];

	return;
}

/// OptimizedMultiplyMatrices 2x2
///
/// Multiply matrices (result = mat * oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
/// @param rez result of multiplication
template <class T>
inline void OptimizedMultiplyMatrices(
	const mwMatrix<T, 2, 2>& mat, const mwMatrix<T, 2, 2>& oth, mwMatrix<T, 2, 2>& rez)
{
	rez[0][0] = mat[0][0] * oth[0][0] + mat[0][1] * oth[1][0];
	rez[0][1] = mat[0][0] * oth[0][1] + mat[0][1] * oth[1][1];

	rez[1][0] = mat[1][0] * oth[0][0] + mat[1][1] * oth[1][0];
	rez[1][1] = mat[1][0] * oth[0][1] + mat[1][1] * oth[1][1];

	return;
}

/// Multiply matrix with vector (result = mat * vec)
///	@param mat const reference to the matrix
///	@param rVec const reference to the multiplying vector
///	@throws mwMathException if matrix and vector are incompatible
template <class T, int rows, int columns>
inline mwVector<T, columns> operator*(
	const mwMatrix<T, rows, columns>& mat, const mwVector<T, columns>& rVec)
{
	mwVector<T, columns> tmp;
	for (int row = 0; row < rows; ++row)
	{
		T val(0);
		for (int col = 0; col < columns; ++col)
		{
			val += mat[row][col] * rVec[col];
		}
		tmp[row] = val;
	}
	return tmp;
}

/// Multiply matrix with vector (result = mat * vec)
///	@param mat const reference to the matrix
///	@param rVec const reference to the multiplying vector
///	@throws mwMathException if matrix and vector are incompatible
template <>
MW_5AXUTIL_API inline mwVector<float, 4> operator*(
	const mwMatrix<float, 4, 4>& mat, const mwVector<float, 4>& rVec)
{
	mwVector<float, 4> rezData;
	const float* matData = mat.GetData();

	rezData[0] =
		matData[0] * rVec[0] + matData[1] * rVec[1] + matData[2] * rVec[2] + matData[3] * rVec[3];
	rezData[1] =
		matData[4] * rVec[0] + matData[5] * rVec[1] + matData[6] * rVec[2] + matData[7] * rVec[3];
	rezData[2] =
		matData[8] * rVec[0] + matData[9] * rVec[1] + matData[10] * rVec[2] + matData[11] * rVec[3];
	rezData[3] = matData[12] * rVec[0] + matData[13] * rVec[1] + matData[14] * rVec[2] +
		matData[15] * rVec[3];

	return rezData;
}

/// Multiply each element of a matrix with a scalar
///	@param mat const reference to one matrix
///	@param oth const reference to the scalar of T type
template <class T, int rows, int columns>
inline cadcam::mwMatrix<T, rows, columns> operator*(
	const mwMatrix<T, rows, columns>& mat, const T& oth)
{
	mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] * oth;
		}
	}
	return tmp;
}

/// Divide each element of a matrix by a scalar
///	@param mat const reference to one matrix
///	@param oth const reference to the scalar of T type
template <class T, int rows, int columns>
inline cadcam::mwMatrix<T, rows, columns> operator/(
	const mwMatrix<T, rows, columns>& mat, const T& oth)
{
	mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] / oth;
		}
	}
	return tmp;
}

/// Add matrices (result = mat + oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix
template <class T, int matrows, int matcolumns, int othrows, int othcolumns>
inline cadcam::mwMatrix<T, matrows, matcolumns> operator+(
	const mwMatrix<T, matrows, matcolumns>& mat, const mwMatrix<T, othrows, othcolumns>& oth)
{
	MW_STATIC_ASSERT_MSG(othrows == matrows, "For addition, Mat1.NrRows must equal Mat2.NrRows");
	MW_STATIC_ASSERT_MSG(
		othcolumns == matcolumns, "For addition, Mat1.NrColumns must equal Mat2.NrColumns");

	mwMatrix<T, matrows, matcolumns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < matrows; ++row)
	{
		for (int col = 0; col < matcolumns; ++col)
		{
			tmp[row][col] = mat[row][col] + oth[row][col];
		}
	}
	return tmp;
}

/// Add a scalar to each element of a matrix
///	@param mat const reference to one matrix
///	@param oth const reference to the scalar of T type
template <class T, int rows, int columns>
inline cadcam::mwMatrix<T, rows, columns> operator+(
	const mwMatrix<T, rows, columns>& mat, const T& oth)
{
	mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] + oth;
		}
	}
	return tmp;
}

/// Subtract matrices (result = mat - oth)
///	@param mat const reference to one matrix
///	@param oth const reference to the other matrix

template <class T, int matrows, int matcolumns, int othrows, int othcolumns>
inline cadcam::mwMatrix<T, matrows, matcolumns> operator-(
	const mwMatrix<T, matrows, matcolumns>& mat, const mwMatrix<T, othrows, othcolumns>& oth)
{
	MW_STATIC_ASSERT_MSG(othrows == matrows, "For subtraction, Mat1.NrRows must equal Mat2.NrRows");
	MW_STATIC_ASSERT_MSG(
		othcolumns == matcolumns, "For subtraction, Mat1.NrColumns must equal Mat2.NrColumns");

	mwMatrix<T, matrows, matcolumns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < matrows; ++row)
	{
		for (int col = 0; col < matcolumns; ++col)
		{
			tmp[row][col] = mat[row][col] - oth[row][col];
		}
	}
	return tmp;
}

/// Subtract a scalar from each element of a matrix
///	@param mat const reference to one matrix
///	@param oth const reference to the scalar of T type

template <class T, int rows, int columns>
inline cadcam::mwMatrix<T, rows, columns> operator-(
	const mwMatrix<T, rows, columns>& mat, const T& oth)
{
	mwMatrix<T, rows, columns> tmp((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] - oth;
		}
	}
	return tmp;
}

/// GetMinorMatrix
template <class T, int rows, int columns>
inline mwMatrix<T, rows - 1, columns - 1> GetMinorMatrix(
	const mwMatrix<T, rows, columns>& mat, int minorRow, int minorColumn)
{
	MW_STATIC_ASSERT_MSG(rows == columns, "Can get minor matrix only for homogenous matrices");

	mwMatrix<T, rows - 1, columns - 1> minormat((mwMatrixNoInitializeTag()));
	int minorrow = 0, minorcol;
	for (int row = 0; row < rows; ++row)
	{
		minorcol = 0;
		if (row == minorRow)
			continue;
		for (int col = 0; col < columns; ++col)
		{
			if (col == minorColumn)
				continue;
			minormat[minorrow][minorcol] = mat[row][col];
			minorcol++;
		}
		minorrow++;
	}
	return minormat;
}

/// Matrix inverse
///	@param mat const ref to original matrix
///	@returns const inverted matrix
template <class T, int rows, int columns>
inline mwMatrix<T, columns, rows> operator!(const mwMatrix<T, rows, columns>& mat)
{
	MW_STATIC_ASSERT_MSG(rows == columns, "Can find determinant only for homogenous matrices");

	T det = ~mat;
	if (det == 0)
		throw misc::mwMathException(
			_T("Can compute inverse only for nonsingular matrices (det != 0)"),
			misc::mwMathException::DETERMINANT_IS_ZERO);

	mwMatrix<T, columns, rows> inverted((mwMatrixNoInitializeTag()));
	// mwMatrix<T, rows - 1, columns - 1> minormat;
	int sign = 1;
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			sign = (row + col) % 2 ? -1 : 1;
			inverted[col][row] = sign * ~GetMinorMatrix(mat, row, col) / det;
		}
	}

	return inverted;
}

///	Transposition
///	@param mat const ref to matrix to be transposed
///	@returns const transposed matrix
template <class T, int rows, int columns>
inline mwMatrix<T, columns, rows> Transpose(const mwMatrix<T, rows, columns>& mat)
{
	mwMatrix<T, columns, rows> transpmat((mwMatrixNoInitializeTag()));
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			transpmat[col][row] = mat[row][col];
		}
	}
	return transpmat;
}

/// Returns determinant of the matrix
///	@param mat const ref to matrix for which determinant is to be computed
///	@returns const determinant of the matrix
template <typename T, int rows, int columns>
inline T operator~(const mwMatrix<T, rows, columns>& mat)
{
	MW_STATIC_ASSERT_MSG(rows == columns, "Can find determinant only for homogenous matrices");

	int sign = 1;
	T det = 0;
	for (int col = 0; col < columns; ++col)
	{
		det += sign * mat[0][col] * ~GetMinorMatrix(mat, 0, col);
		sign = -sign;
	}
	return det;
}

/// compute the determinant of a matrix
///
///	@param mat source matrix
///	@returns determinant of type const float
template <>
inline float operator~(const mwMatrix<float, 1, 1>& mat)
{
	return mat[0][0];
}
/// compute the determinant of a matrix
///
///	@param mat source matrix
///	@returns determinant of type const double
template <>
inline double operator~(const mwMatrix<double, 1, 1>& mat)
{
	return mat[0][0];
}
/// compute the determinant of a matrix
///
///	@param mat source matrix
///	@returns determinant of type const float
template <>
inline float operator~(const mwMatrix<float, 2, 2>& mat)
{
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}
/// compute the determinant of a 2X2 matrix
///
///	@param mat source matrix
///	@returns determinant of type const double
template <>
inline double operator~(const mwMatrix<double, 2, 2>& mat)
{
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

/// compute the determinant of a 3X3 matrix
///
///	@param mat source matrix
///	@returns determinant of type const float
template <>
inline float operator~(const mwMatrix<float, 3, 3>& mat)
{
	return mat[0][0] * mat[1][1] * mat[2][2] + mat[1][0] * mat[2][1] * mat[0][2] +
		mat[2][0] * mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1] * mat[2][0] -
		mat[1][2] * mat[2][1] * mat[0][0] - mat[2][2] * mat[0][1] * mat[1][0];
}

/// compute the determinant of a 3X3 matrix
///
///	@param mat source matrix
///	@returns determinant of type const float
template <>
inline double operator~(const mwMatrix<double, 3, 3>& mat)
{
	return mat[0][0] * mat[1][1] * mat[2][2] + mat[1][0] * mat[2][1] * mat[0][2] +
		mat[2][0] * mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1] * mat[2][0] -
		mat[1][2] * mat[2][1] * mat[0][0] - mat[2][2] * mat[0][1] * mat[1][0];
}

#ifndef MW_GENERATE_DOCUMENTATION
template <>
inline mwMatrix<float, 3, 3>::operator mw::Verifier::math::TMatrix3<float>&()
{
	return *static_cast<mw::Verifier::math::TMatrix3<float>*>(static_cast<void*>(this));
}
template <>
inline mwMatrix<float, 3, 3>::operator const mw::Verifier::math::TMatrix3<float>&() const
{
	return *static_cast<const mw::Verifier::math::TMatrix3<float>*>(static_cast<const void*>(this));
}
template <>
inline mwMatrix<float, 4, 4>::operator mw::Verifier::math::TMatrix4<float>&()
{
	return *static_cast<mw::Verifier::math::TMatrix4<float>*>(static_cast<void*>(this));
}
template <>
inline mwMatrix<float, 4, 4>::operator const mw::Verifier::math::TMatrix4<float>&() const
{
	return *static_cast<const mw::Verifier::math::TMatrix4<float>*>(static_cast<const void*>(this));
}
template <>
inline mwMatrix<double, 3, 3>::operator mw::Verifier::math::TMatrix3<double>&()
{
	return *static_cast<mw::Verifier::math::TMatrix3<double>*>(static_cast<void*>(this));
}
template <>
inline mwMatrix<double, 3, 3>::operator const mw::Verifier::math::TMatrix3<double>&() const
{
	return *static_cast<const mw::Verifier::math::TMatrix3<double>*>(
		static_cast<const void*>(this));
}
template <>
inline mwMatrix<double, 4, 4>::operator mw::Verifier::math::TMatrix4<double>&()
{
	return *static_cast<mw::Verifier::math::TMatrix4<double>*>(static_cast<void*>(this));
}
template <>
inline mwMatrix<double, 4, 4>::operator const mw::Verifier::math::TMatrix4<double>&() const
{
	return *static_cast<const mw::Verifier::math::TMatrix4<double>*>(
		static_cast<const void*>(this));
}
#endif  // !MW_GENERATE_DOCUMENTATION

typedef mwMatrix<float, 4, 4> mwHomogenousMatrix;
typedef mwMatrix<float, 3, 3> mw2dHomogenousMatrix;
typedef mwMatrix<double, 3, 3> mw2dHomogenousMatrixd;
typedef mwMatrix<double, 4, 4> mwHomogenousMatrixd;

}  // namespace cadcam
#endif  //	MW_MWMATRIX_HPP_
