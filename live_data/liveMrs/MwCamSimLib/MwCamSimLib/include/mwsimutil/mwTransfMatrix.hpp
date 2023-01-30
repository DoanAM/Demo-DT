// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwTransfMatrix class

//#############################################################################

#ifndef MW_MWTRANSFMATRIX_HPP_
#define MW_MWTRANSFMATRIX_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwPostComponentsDefinitions.hpp"
//#############################################################################
class MW_5AXUTIL_API mwTransfMatrix
{
public:
	//#############################################################################
	typedef post::mwMatrix4d                                        TransfMatrixd;
	typedef cadcam::mwHomogenousMatrix                              TransfMatrixf;
	typedef post::mwMatrix4dMap                                     TransfMatrixdMap;
	typedef std::map<misc::mwstring, post::mwMatrix4d>              TransfMatrixfMap;
	typedef post::mwMatrix4dMap::iterator                           iterator;
	typedef post::mwMatrix4dMap::const_iterator                     const_iterator;
	//#############################################################################
	mwTransfMatrix();
	//#############################################################################
	mwTransfMatrix(const mwTransfMatrix& toCopy);
	//#############################################################################
	const mwTransfMatrix& operator = (const mwTransfMatrix& toCopy);
	//#############################################################################
	//#############################################################################
	//#############################################################################
	const TransfMatrixdMap& GetWorkpieceMatrix() const;
	TransfMatrixdMap& GetWorkpieceMatrix();
	void SetWorkpieceMatrix(const mwTransfMatrix::TransfMatrixdMap& transfMatrixdMap);
	//#############################################################################
	const TransfMatrixdMap& GetWorkpieceMatrixCombined() const;
	TransfMatrixdMap& GetWorkpieceMatrixCombined();
	void SetWorkpieceMatrixCombined(const mwTransfMatrix::TransfMatrixdMap& transfMatrixdMap);
	//#############################################################################
	const bool SetWorkpieceMatrix(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	const bool SetWorkpieceMatrix(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	const bool FindWorkpiece(const misc::mwstring& name, TransfMatrixd& matrix) const;
	//#############################################################################
	const bool FindWorkpiece(const misc::mwstring& name, TransfMatrixf& matrix) const;
	//#############################################################################
	void AddWorkpieceMatrix(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	void AddWorkpieceMatrix(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	const bool SetWorkpieceMatrixCombined(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	const bool SetWorkpieceMatrixCombined(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	const bool FindWorkpieceCombined(const misc::mwstring& name, TransfMatrixd& matrix) const;
	//#############################################################################
	const bool FindWorkpieceCombined(const misc::mwstring& name, TransfMatrixf& matrix) const;
	//#############################################################################
	void AddWorkpieceMatrixCombined(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	void AddWorkpieceMatrixCombined(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	//#############################################################################
	//#############################################################################
	const TransfMatrixdMap& GetHolderMatrix() const;
	TransfMatrixdMap& GetHolderMatrix();
	void SetHolderMatrix(const mwTransfMatrix::TransfMatrixdMap& transfMatrixdMap);
	//#############################################################################
	const TransfMatrixdMap& GetHolderMatrixCombined() const;
	TransfMatrixdMap& GetHolderMatrixCombined();
	void SetHolderMatrixCombined(const mwTransfMatrix::TransfMatrixdMap& transfMatrixdMap);
	//#############################################################################
	const bool SetHolderMatrix(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	const bool SetHolderMatrix(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	const bool FindHolder(const misc::mwstring& name, TransfMatrixd& matrix) const;
	//#############################################################################
	void AddHolderMatrix(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	void AddHolderMatrix(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	//#############################################################################
	//#############################################################################
	const bool SetHolderMatrixCombined(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	const bool SetHolderMatrixCombined(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	const bool FindHolderCombined(const misc::mwstring& name, TransfMatrixd& matrix) const;
	//#############################################################################
	void AddHolderMatrixCombined(const misc::mwstring& name, const TransfMatrixd& matrix);
	//#############################################################################
	void AddHolderMatrixCombined(const misc::mwstring& name, const TransfMatrixf& matrix);
	//#############################################################################
	//#############################################################################
	//#############################################################################
	static const TransfMatrixd FloatMatrixToDoubleMatrix(const TransfMatrixf& matrix);
	//#############################################################################
	static const TransfMatrixf DoubleMatrixToFloatMatrix(const TransfMatrixd& matrix);
	//#############################################################################
private:
	//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
	TransfMatrixdMap m_workpiece;
	TransfMatrixdMap m_holder;
	TransfMatrixdMap m_workpieceCombined;
	TransfMatrixdMap m_holderCombined;
#pragma warning(pop)
	//#############################################################################
};
//#############################################################################
typedef misc::mwAutoPointer<mwTransfMatrix> mwTransfMatrixPtr;
//#############################################################################
#endif	//	MW_MWTRANSFMATRIX_HPP_
