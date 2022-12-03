// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOINT3DMATRIX_HPP_
#define MW_MW2DPOINT3DMATRIX_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"

#include <vector>


namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc

namespace cadcam
{
/// This class represents a 2d matrix of 3d points
#pragma CACHING_INTERNAL_BEGIN
class MW_5AXUTIL_API mw2dPoint3dMatrix
{
public:
	typedef std::vector<mwTPoint3d<double>> row;

	/// Default constructor
	///
	/// Constructs a matrix with given number of rows and columns
	///	If number of rows or columns < 1 an exception will be thrown
	///	@param rows number of rows in the new matrix
	///	@param columns number of columns in the new matrix
	mw2dPoint3dMatrix(const size_t rows, const size_t columns);

	/// returns number of rows in the matrix
	///
	/// @returns const size_t
	const size_t rows() const;

	/// returns number of columns in the matrix
	///
	/// @returns const size_t
	const size_t columns() const;

	/// Indexer operator
	///
	/// Returns, for a given index, a refernce of a row
	///	@param index position of the row in the matrix
	///	@returns reference to a row
	row& operator[](const size_t index);

	/// Indexer operator for const values
	///
	/// Returns, for a given index, a refernce of a const row
	///	@param index position of the row in the matrix
	///	@returns reference to a const row
	const row& operator[](const size_t index) const;

	/// Resize matrix
	///
	/// Resize the matrix with the new rows and columns size
	///	@param rows new number of rows in the new matrix
	///	@param columns new number of columns in the new matrix
	void ResizeMatrix(const size_t rows, const size_t columns);

private:
	/// a 2d matrix of mwPoint3d objects.
	std::vector<row> matrix;
};
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MW2DPOINT3DMATRIX_HPP_
