// (C) 2010-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHINEDEFAULTS_HPP_
#define MW_MWMACHINEDEFAULTS_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwFileName.hpp"
#include "mwDeprecated.hpp"

class MW_SIMUTIL_API mwMachineDefaults
{
public:
	mwMachineDefaults(const misc::mwstring machineFolder);
	virtual ~mwMachineDefaults(void);

public:
	static misc::mwstring GetPrimaryDefinitionExtension();
	static misc::mwstring GetSecondaryDefinitionExtension();
	static misc::mwstring GetGeometryExtension();
	static misc::mwstring GetPictureExtension();
	static misc::mwstring GetPictureReflectionExtension();


	virtual bool QueryMachineXMLFileName(misc::mwFileName& fileName, misc::mwstring machineName) const;
	virtual bool QueryMachineMPSFileName(misc::mwFileName& fileName, misc::mwstring machineName) const; 
	virtual bool QueryMachineSTLFileName(misc::mwFileName& fileName, misc::mwstring geometryName) const;

	MW_DEPRECATED("Deprecated in 2019.04, do not use it")
	virtual bool QueryMachineSTLFileName(misc::mwFileName& fileName, const misc::mwstring machineName, misc::mwstring geometryName) const;

	virtual bool QueryMachinePictureFileName(misc::mwFileName& fileName, misc::mwstring machineName) const;
	virtual bool QueryMachinePictureReflectionFileName(misc::mwFileName& fileName, misc::mwstring pictureName) const;

	MW_DEPRECATED("Deprecated in 2019.04, do not use it")
	virtual bool QueryMachinePictureReflectionFileName(misc::mwFileName& fileName, misc::mwstring machineName, misc::mwstring pictureName) const ;

	virtual void PreserveRelativePaths( const misc::mwstring& machineName, misc::mwFileName& geometryFileName ) const;

	virtual bool HasMeshesInsteadOfStl(const misc::mwFileName& fileName) const;

	virtual misc::mwFileName BuildFileName(misc::mwstring machinePartName, misc::mwstring fileExtension) const;

protected:
	// avoid warning c4512
	mwMachineDefaults& operator=(const mwMachineDefaults&);

	MW_DEPRECATED("Deprecated in 2019.04, do not use it")
	static void AddExtension(misc::mwFileName& machinePartFilePath, misc::mwstring machinePartName, misc::mwstring fileExtension);

	virtual misc::mwFileName BuildMachinePartFileName(const misc::mwstring& machinePartName, const misc::mwstring& fileExtension) const;
	const misc::mwFileName BuildMachineFolder() const;
	const misc::mwstring GetMachineFolder() const;

	const misc::mwstring m_machineFolder;
};
#endif	//	MW_MWMACHINEDEFAULTS_HPP_
