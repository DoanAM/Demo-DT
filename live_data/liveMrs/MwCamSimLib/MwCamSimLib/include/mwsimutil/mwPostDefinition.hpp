// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWPOSTDEFINITION_HPP_
#define MW_MWPOSTDEFINITION_HPP_
//#############################################################################
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMachDef.hpp"
#include "mwMachDefBuilder.hpp"
#include "mwMachDynamics.hpp"
#include "mwPostCommonDefinitions.hpp"
#include "mwMXPParam.hpp"
#include "mw5axControlDef.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostDefinition
	{
	public:
		//#############################################################################
		typedef misc::mwstring                    id;
		typedef std::vector<double>               initialValues;
		typedef std::pair<misc::mwstring, double> axisValue;
		typedef misc::mwAutoPointer<axisValue>    axisValuePtr;
		//#############################################################################
		mwPostDefinition();
		//#############################################################################
		mwPostDefinition(
				const post::mwMachDefPtr& machDef, 
				const post::mwMachDefBuilder::MachDefFactory& detectionMode,
				const std::vector<misc::mwstring>& axisNames,
				const post::mwMachDynamics& machDynamics = post::mwMachDynamics(),
				const misc::mwstring& toolName = _T("tool"),
				const misc::mwstring& workpieceName = _T("workpiece"),
				const post::mwTranslationPos firstTrAxis = post::HEAD,
				const post::mwTranslationPos secondTrAxis = post::HEAD,
				const post::mwTranslationPos thirdTrAxis = post::HEAD,
				const post::mwSpindles spindles = post::mwSpindles(),
				const id& postSettingsId = _T(""),
				const initialValues& initValues = initialValues(),
				const mwMXPParamPtr& mxpParamPtr = MW_NULL,
				const axisValuePtr& _axisValuePtr = MW_NULL,
				const post::mw5axControlDef::mw5axControlDefPtr& controlDefPtr = MW_NULL,
				const post::AdditionalFixedAxesPtr& additionalFixedAxesPtr = MW_NULL,
				const bool isRoboticMode = false,
				const post::mwStringPairVectPtr& mountingPairsPtr = MW_NULL);
		//#############################################################################
		mwPostDefinition(
			const post::mwMachDefPtr& machDef,
			const post::mwMachDefBuilder::MachDefFactory& detectionMode,
			const std::vector<misc::mwstring>& axisNames,
			const post::mwMachDynamics& machDynamics = post::mwMachDynamics(),
			const misc::mwstring& toolName = _T("tool"),
			const misc::mwstring& workpieceName = _T("workpiece"),
			const post::mwTranslationPos firstTrAxis = post::HEAD,
			const post::mwTranslationPos secondTrAxis = post::HEAD,
			const post::mwTranslationPos thirdTrAxis = post::HEAD,
			const post::mwMatrix4dMap matrixMap = post::mwMatrix4dMap(),
			const id& postSettingsId = _T(""),
			const initialValues& initValues = initialValues(),
			const mwMXPParamPtr& mxpParamPtr = MW_NULL,
			const axisValuePtr& _axisValuePtr = MW_NULL,
			const post::mw5axControlDef::mw5axControlDefPtr& controlDefPtr = MW_NULL,
			const post::AdditionalFixedAxesPtr& additionalFixedAxesPtr = MW_NULL,
			const bool isRoboticMode = false,
			const post::mwStringPairVectPtr& mountingsPairsPtr = MW_NULL);
		//#############################################################################
		mwPostDefinition(const mwPostDefinition &toCopy);
		//#############################################################################
		const mwPostDefinition& operator = (const mwPostDefinition& toCopy);
		//#############################################################################
		const bool operator == (const mwPostDefinition& toCompare) const;
		//#############################################################################
		const bool operator != (const mwPostDefinition& toCompare) const;
		//#############################################################################
		static const post::mwSpindles GenerateDefaultSpindle(const post::mwMachDefPtr& machDef, const misc::mwstring& toolName = _T("tool"));
		//#############################################################################
		const post::mwMachDefPtr& GetMachDefPtr() const;
		//#############################################################################
		post::mwMachDefPtr& GetMachDefPtr();
		//#############################################################################
		void SetMachDefPtr(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		const post::mwMachDefBuilder::MachDefFactory GetMachDefFactory() const;
		//#############################################################################
		void SetMachDefFactory(const post::mwMachDefBuilder::MachDefFactory detectionMode);
		//#############################################################################
		const std::vector<misc::mwstring>& GetAxisNames() const;
		//#############################################################################
		void SetAxisNames(const std::vector<misc::mwstring>& axisNames);
		//#############################################################################
		const post::mwMachDynamics& GetMachDynamics() const;
		//#############################################################################
		post::mwMachDynamics& GetMachDynamics();
		//#############################################################################
		void SetMachDynamics(const post::mwMachDynamics& machDynamics);
		//#############################################################################
		const misc::mwstring& GetToolName() const;
		//#############################################################################
		void SetToolName(const misc::mwstring& toolName);
		//#############################################################################
		const misc::mwstring& GetWorkpieceName() const;
		//#############################################################################
		void SetWorkpieceName(const misc::mwstring& workpieceName);
		//#############################################################################
		const post::mwTranslationPos GetFirstTrAxis() const;
		//#############################################################################
		void SetFirstTrAxis(const post::mwTranslationPos firstTrAxis);
		//#############################################################################
		const post::mwTranslationPos GetSecondTrAxis() const;
		//#############################################################################
		void SetSecondTrAxis(const post::mwTranslationPos secondTrAxis);
		//#############################################################################
		const post::mwTranslationPos GetThirdTrAxis() const;
		//#############################################################################
		void SetThirdTrAxis(const post::mwTranslationPos thirdTrAxis);
		//#############################################################################
		const post::mwSpindles& GetSpindles() const;
		//#############################################################################
		void SetSpindles(const post::mwSpindles& spindles);
		//#############################################################################
		const post::mwMatrix4dMap& GetMatrixMap() const;
		//#############################################################################
		void SetMatrixMap(const post::mwMatrix4dMap& matrixMap);
		//#############################################################################
		const id& GetID() const;
		//#############################################################################
		void SetID(const id& _id);
		//#############################################################################
		const initialValues GetInitialValues() const;
		//#############################################################################
		void SetInitialValues(const initialValues& initValues);
		//#############################################################################
		const mwMXPParamPtr& GetMxpParamPtr() const;
		//#############################################################################
		mwMXPParamPtr& GetMxpParamPtr();
		//#############################################################################
		void SetMxpParamPtr(const mwMXPParamPtr& mxpParamPtr);
		//#############################################################################
		const axisValuePtr GetAxisValuePtr() const;
		//#############################################################################
		void SetAxisValuePtr(const axisValuePtr& _axisValuePtr);
		//#############################################################################
		const post::mw5axControlDef::mw5axControlDefPtr& Get5AxControlDefPtr() const;
		//#############################################################################
		post::mw5axControlDef::mw5axControlDefPtr& Get5AxControlDefPtr();
		//#############################################################################
		void Set5AxControlDefPtr(const post::mw5axControlDef::mw5axControlDefPtr& mxpParamPtr);
		//#############################################################################
		void SetAdditionalFixedAxesPtr(const AdditionalFixedAxesPtr& additionalFixedAxesPtr);
		//#############################################################################
		const AdditionalFixedAxesPtr& GetAdditionalFixedAxesPtr() const;
		//#############################################################################
		AdditionalFixedAxesPtr& GetAdditionalFixedAxesPtr();
		//#############################################################################
		const mwMachDef::MachineDefinitionType GetMachineDefinitionType() const;
		void SetMachineDefinitionType(const mwMachDef::MachineDefinitionType type);

		bool IsRoboticMode() const;
		void SetIsRoboticMode(bool isRobotic);
		//#############################################################################
		const post::mwStringPairVectPtr& GetMountingPairsPtr() const;
		post::mwStringPairVectPtr& GetMountingPairsPtr();
		void SetMountingPairsPtr(const post::mwStringPairVectPtr& mountingPairsPtr);
		//#############################################################################

	private:
		//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		post::mwMachDefPtr m_machDefPtr; 
		post::mwMachDefBuilder::MachDefFactory m_detectionMode;
		std::vector<misc::mwstring> m_axisNames;
		post::mwMachDynamics m_machDynamics;
		misc::mwstring m_toolName;
		misc::mwstring m_workpieceName;
		post::mwTranslationPos m_firstTrAxis;
		post::mwTranslationPos m_secondTrAxis;
		post::mwTranslationPos m_thirdTrAxis;
		post::mwSpindles m_spindles;
		post::mwMatrix4dMap m_matrixMap;
		id m_postSettingsId;
		initialValues m_initialValues;
		post::mwMXPParamPtr m_mxpParamPtr;
		axisValuePtr m_axisValuePtr;
		post::mw5axControlDef::mw5axControlDefPtr m_5axControlDefPtr;
		post::AdditionalFixedAxesPtr			   m_additionalFixedAxesPtr;
		bool m_isRoboticMode;
		mwMachDef::MachineDefinitionType m_postType;
		post::mwStringPairVectPtr m_mountingPairsPtr;
#pragma warning(pop)
		void ConvertToRoboticPostDef();
		//#############################################################################
		void Copy(const mwPostDefinition& toCopy);
		//#############################################################################
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwPostDefinition> mwPostDefinitionPtr;
	typedef std::vector<mwPostDefinitionPtr> mwPostDefinitionPtrVect;
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTDEFINITION_HPP_
