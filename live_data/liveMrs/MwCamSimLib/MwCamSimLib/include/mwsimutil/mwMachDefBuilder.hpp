// (C) 2008-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwMachDefBuilder class

//#############################################################################

#ifndef MW_MWMACHDEFBUILDER_HPP_
#define MW_MWMACHDEFBUILDER_HPP_
//#############################################################################
#include "mwMachDef.hpp"
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTransfMatrix.hpp"
//#############################################################################
namespace post
{
//#############################################################################
	class MW_5AXUTIL_API mwMachDefBuilder
	{
	public:
//#############################################################################
		enum MachDefFactory
		{
			AUTODETECT_FULL = 0,
			AUTODETECT_SEMIAUTOMATIC = 1,
			MANUAL_MODE = 2
		};
//#############################################################################
		typedef std::vector<misc::mwstring> AxisNameVec;
//#############################################################################
		mwMachDefBuilder();
//#############################################################################
		mwMachDefBuilder(const mwMachDefBuilder& toCopy);
//#############################################################################
		mwMachDefBuilder& operator = (const mwMachDefBuilder& toCopy);
//#############################################################################
		mwMachDefBuilder(
			MachDefFactory machDefType,
			const AxisNameVec axisName,
			const mwMachDefPtr machDef,
			const mwTransfMatrixPtr& transfVectros = new mwTransfMatrix());
//#############################################################################
		const MachDefFactory& GetMachDefType() const;
//#############################################################################
		void SetMachDefFactory(const MachDefFactory machDefType);
//#############################################################################
		const mwMachDefPtr& GetMachDef() const;
//#############################################################################
		mwMachDefPtr& GetMachDef();
//#############################################################################
		void SetMachDef(const mwMachDefPtr& machDef);
//#############################################################################
		const AxisNameVec& GetAxisName() const;
//#############################################################################
		void SetAxisName(const AxisNameVec& axisName);
//#############################################################################
		const mwTransfMatrixPtr& GetTransfMatrixVect() const;
//#############################################################################
		void SetTransfMatrixVect(const mwTransfMatrixPtr& transfVectros);
//#############################################################################
	private:
//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		MachDefFactory m_machDefType;
		AxisNameVec m_axisName;
		mwMachDefPtr m_machDef;
		mwTransfMatrixPtr m_transfVectros;
#pragma warning(pop)
//#############################################################################
	};// end class mwMachDefBuilder
//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWMACHDEFBUILDER_HPP_
