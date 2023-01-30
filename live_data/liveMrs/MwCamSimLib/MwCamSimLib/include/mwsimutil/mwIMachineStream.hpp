// (C) 2010-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWIMACHINESTREAM_HPP_
#define MW_MWIMACHINESTREAM_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwString.hpp"
#include "mwBinIOStream.hpp"
#include "mwStream.hpp"
#include "mwFileName.hpp"
#include "mwMesh.hpp"
#include "mwMachineDefaults.hpp"
#include "mwSTLTranslator.hpp"




class MW_SIMUTIL_API mwIMachineStream
{
public:
	class mwFileNameStream
	{
		public:
			mwFileNameStream(const bool isDeletable, const misc::mwstring fileName);
			virtual ~mwFileNameStream();

		public:
			virtual misc::mwstring GetFileName();
			virtual bool IsDeletable();

		private:
			// avoid warning c4512
			mwFileNameStream& operator=(const mwFileNameStream&);
			const misc::mwstring m_fileName;
			const bool m_isDeletable;
	};

public:		
	mwIMachineStream(const misc::mwstring& machineFileName);	
	virtual ~mwIMachineStream();

public:
	virtual void FixForRelativePath( misc::mwFileName &fileName );
	virtual bool IsDefinitionAvailable();
	
	MW_DEPRECATED("Deprecated in 2019.04, do not use it")
	virtual bool IsGeometryAvailable(const misc::mwstring fileName);
	
	virtual bool IsGeometryAvailable(misc::mwFileName& realFileName, const misc::mwstring fileName);
	virtual bool IsPictureAvailable(misc::mwFileName& machinePicture);
	virtual bool IsPictureReflectionAvailable(const misc::mwstring fileName);
	virtual bool IsEmptyGeometry(const misc::mwstring fileName);

	virtual misc::mwAutoPointer< mwIMachineStream::mwFileNameStream> GetDefinitionStream();
	virtual misc::mwAutoPointer< mwIMachineStream::mwFileNameStream> GetPictureStream(const misc::mwFileName& machinePicture);
	virtual misc::mwAutoPointer< mwIMachineStream::mwFileNameStream> GetPictureStream();
	virtual misc::mwAutoPointer< mwIMachineStream::mwFileNameStream> GetPictureReflectionStream(const misc::mwstring fileName);
	virtual misc::mwAutoPointer<misc::mwBinInputStream> GetGeometryStlStream(const misc::mwstring fileName);
	virtual misc::mwAutoPointer<cadcam::mwTMesh<float> > GetGeometryMesh(const misc::mwstring fileName, const measures::mwMeasurable::Units unit, misc::mwAutoPointer<cadcam::mwfSTLTranslator::HeaderData> headerData = MW_NULL);

	virtual bool UseStlEOSValidation();

	MW_DEPRECATED("Deprecated in 2019.04, do not use it")
	virtual bool HasMeshesInsteadOfStl();

	virtual bool UseInitialAxisValueOutOfLimit()const;

	virtual const std::vector<misc::mwFileName> GetListOfCustomFilesToSaveInPresentation()const;

protected:
	virtual const misc::mwstring GetMachineName() const;
	virtual const misc::mwstring GetMachineFullName() const;
	virtual const misc::mwstring GetMachineFolder() const;

#pragma warning(suppress:4251)
	misc::mwAutoPointer<mwMachineDefaults> m_machineDefaults;

private:
	misc::mwstring m_machineName;
	misc::mwstring m_machineCoreName;
	misc::mwstring m_machineFolder;

};
#endif	//	MW_MWIMACHINESTREAM_HPP_
