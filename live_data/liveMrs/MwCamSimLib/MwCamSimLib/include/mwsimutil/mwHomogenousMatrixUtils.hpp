// (C) 2005-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWHOMOGENOUSMATRIXUTILS_HPP_
#define MW_MWHOMOGENOUSMATRIXUTILS_HPP_
#include "mwDllImpExpDef.hpp"

#include <mwMatrix.hpp>
#include <mwTPoint3d.hpp>


namespace cadcam
{
/// This class represents a vector util.
template <class T>
class MW_5AXUTIL_API mwHomogenousMatrixUtils
{
	typedef mwTPoint3d<T> vector3d;
	typedef mwMatrix<T, 4, 4> homogenousMatrix;
	typedef enum vectors_order
	{
		first = 0,
		second,
		third
	} order;

public:
	/// The AxisDirections enumerates the axis directions, X, Y, Z positive or negative
	enum AxisDirections
	{
		DIR_NONE = 0,
		DIR_X_PLUS = 1,
		DIR_Y_PLUS = 2,
		DIR_Z_PLUS = 3,
		DIR_X_MINUS = -1,
		DIR_Y_MINUS = -2,
		DIR_Z_MINUS = -3
	};

	/// The HasRotation function
	///
	///	@param matrix homogenousMatrix matrix
	///	@returns if has rotation
	static const bool HasRotation(const homogenousMatrix& matrix);

	/// The GetIdentity function
	///
	///	@returns a homogenousMatrix eqal to identity
	static const homogenousMatrix GetIdentity();

	/// The GetRotationPart function
	///
	///	@param matrix homogenousMatrix
	///	@returns the scale/skew/rotation part as another homogenousMatrix
	static const homogenousMatrix GetRotationPart(const homogenousMatrix& matrix);

	/// The GetTranslationPart function
	///
	///	@param matrix homogenousMatrix
	///	@returns the translation part as a vector3d
	static const vector3d GetTranslationPartVector(const homogenousMatrix& matrix);

	/// The SetTranslationPart function
	///
	///	@param matrix homogenousMatrix
	///	@param translation vector3d - the translation part
	static void SetTranslationPartVector(homogenousMatrix& matrix, const vector3d& translation);

	/// The GetTranslationPart function
	///
	///	@param matrix homogenousMatrix
	///	@returns the translation part as a homogenousMatrix
	static const homogenousMatrix GetTranslationPart(const homogenousMatrix& matrix);

	/// The SetTranslationPart function
	///
	///	@param matrix homogenousMatrix
	///	@param  translation homogenousMatrix - the translation part
	static void SetTranslationPart(homogenousMatrix& matrix, const homogenousMatrix& translation);

	/// The AreRelativelyRotated function
	///
	///	@param matrix1 homogenousMatrix
	///	@param matrix2 homogenousMatrix
	///	@returns if the two matrices are relatively rotated
	static const bool AreRelativelyRotated(
		const homogenousMatrix& matrix1, const homogenousMatrix& matrix2);

	/// The AreEqual function
	///
	///	@param matrix1 homogenousMatrix
	///	@param matrix2 homogenousMatrix
	///	@returns if the two matrices are equal
	static const bool AreEqual(const homogenousMatrix& matrix1, const homogenousMatrix& matrix2);

	/// The AreEqual function
	///
	///	@param matrix1 homogenousMatrix
	///	@param matrix2 homogenousMatrix
	///	@param tolerance
	///	@returns if the two matrices are equal
	static bool AreEqualWithTolerance(
		const homogenousMatrix& matrix1, const homogenousMatrix& matrix2, const T tolerance);

	typedef AxisDirections AARotation[3];

	/// The IsRotationAxisAligned function
	///
	///	@param matrix homogenousMatrix
	///	@param AARot the axis directions
	///	@returns if the rotation is only switching the axis
	static const bool IsRotationAxisAligned(const homogenousMatrix& matrix, AARotation& AARot);

	/// The IsIsometric function
	///
	/// @param matrix homogenousMatrix
	/// @returns if the matrix applies solely rotation or/and translation
	static const bool IsIsometric(const homogenousMatrix& matrix);

	/// DeterminesConformationChanges
	///
	/// @param matrix homogenousMatrix
	/// @returns if applying the matrix doesn't cause any conformation changes (scaling, mirroring
	/// etc.)
	static const bool DeterminesConformationChanges(const homogenousMatrix& matrix);

	/// The RemoveDeformations
	///
	/// remove from param matrix non-rotation and non-translation parts;
	/// Finaly it will contain a rotation and a translation part only;
	///
	/// @param matrix homogenous matrix
	/// @returns homogenous matrix
	static const homogenousMatrix RemoveDeformations(const homogenousMatrix& matrix);

	/// The InvertIsometricHomogenousMatrix
	///
	/// invert isometric or homogenous matrix
	///
	///	@param matrix isometric or homogenous matrix
	///	@returns homogenous matrix
	static const homogenousMatrix InvertIsometricHomogenousMatrix(const homogenousMatrix& matrix);

private:
	/// Constructor not allowed since it's a static class
	mwHomogenousMatrixUtils();

	/// The CheckDeterminant function
	///
	/// @param matrix homogenousMatrix
	/// @returns the value of 3x3 matrix determinant;
	static const double CheckDeterminant(const homogenousMatrix& matrix);

	/// The RemovePerspective function
	///
	/// @param matrix homogenousMatrix
	/// @returns the matrix without perspective rule;
	static const homogenousMatrix RemovePerspective(const homogenousMatrix& matrix);
};
}  // namespace cadcam
#endif  //	MW_MWHOMOGENOUSMATRIXUTILS_HPP_
