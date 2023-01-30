// (C) 2004-2018 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWSTLREADERSRV_HPP_
#define MW_MWSTLREADERSRV_HPP_
#include "mwSTLTranslator.hpp"
#include "mkdPolygonalGeometry.hpp"
#include "mkdToolpathGeometry.hpp"
#include "mwFileStream.hpp"
#include "mwMeasurable.hpp"
#include "mwIMachineStream.hpp"


namespace machsim
{
	class STLReaderSrv
	{
	public:
		static mkdPolygonalGeometry::polyDataRef 
			ReadStl(
			const misc::mwstring& fileName,
			const measures::mwMeasurable::Units unit)
		{
			mkdPolygonalGeometry::polyDataRef meshRef = new 
				mkdPolygonalGeometry::polyData(unit);

			cadcam::mwTSTLTranslator<float>::HeaderData header;
			ReadStl(fileName, unit, *meshRef, header);

			return meshRef;
		}

		static void ReadStl(const misc::mwstring& fileName,
			const measures::mwMeasurable::Units unit,
			mkdPolygonalGeometry::polyData& meshRef,
			cadcam::mwTSTLTranslator<float>::HeaderData& header)
		{
			meshRef.SetUnits(unit, true);
			misc::mwFileName file(fileName);	
			cadcam::mwTSTLTranslator<float>::ReadSTL(file, meshRef, header, true);
		}

		static mkdToolpathGeometry::polyDataRef 
			ReadAsc(const misc::mwstring& fileName)
		{
			mkdToolpathGeometry::polyDataRef polyRef = mkdToolpathGeometry::polyDataRef(new
				mkdToolpathGeometry::polyData());

			misc::mwIFStream  ifs( fileName.c_str() );
			machsim::mwEASCIIParser parser( ifs );
			parser.Parse();			
			
			machsim::mkdToolpathGeometry::polyData::iterator it ;
			for(it = parser.GetPolyBegin(); it != parser.GetPolyEnd(); ++ it)
			{
				(*polyRef).push_back(*it);
			}
			return polyRef;
		}

		static void ReadStl(
			mwIMachineStream* pIMachineStream,
			const misc::mwstring& fileName,
			const measures::mwMeasurable::Units unit,
			mkdPolygonalGeometry::polyData& meshRef,
			cadcam::mwTSTLTranslator<float>::HeaderData& headerData,
			bool useFileNormals)
		{
			meshRef.SetUnits(unit, true);

			if (pIMachineStream->IsEmptyGeometry(fileName))
			{
				return;
			}
		
			misc::mwAutoPointer<cadcam::mwTSTLTranslator<float>::HeaderData> newHeaderData = new cadcam::mwTSTLTranslator<float>::HeaderData();
			misc::mwAutoPointer<mkdPolygonalGeometry::polyData> meshPtr = pIMachineStream->GetGeometryMesh(fileName,unit, newHeaderData);
			meshRef = *meshPtr;
			headerData = *newHeaderData;
			
			//recreate normals
			if (!useFileNormals)
			{
				meshRef.RecalculateNormals();
			}

		}
		
	};
};
#endif	//	MW_MWSTLREADERSRV_HPP_
