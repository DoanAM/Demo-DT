// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSTLTRANSLATOR_HPP_
#define MW_MWSTLTRANSLATOR_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwFileName.hpp"
#include "mwFileStream.hpp"
#include "mwFileSystem.hpp"
#include "mwMesh.hpp"
#include "mwParserSTL.hpp"
#include "mwSTLFile.hpp"
#include "mwSTLParserException.hpp"
#include "mwFileIOStream.hpp"
#include "mwStdOutputStream.hpp"
#include "mwStream.hpp"
#include "mwString.hpp"
#include "mwmiscException.hpp"
#include "mwWarningPragmas.hpp"

#include <fstream>


#ifndef MW_FORCEINLINE
#if defined(_WIN32)
#define MW_FORCEINLINE __forceinline
#else
#define MW_FORCEINLINE inline
#endif
#endif

namespace cadcam
{
template <class T>
struct mwTPoint3d;
template <typename T, typename TVertex, typename TFaceNormal>
class MW_5AXUTIL_API mwContainerMesh;
template <typename T, typename _TVertex, typename _TFaceNormal>
class mwTTriangleVector;
template <class T>
struct mwTPoint3d;
}  // namespace cadcam

namespace misc
{
class mwFileName;
class mwstring;
class mwBinInputStream;
class mwBinOutputStream;
typedef std::wistream mwIStream;
typedef std::iostream mwAStream;
typedef std::wostream mwOStream;
class mwIFStream;
class mwOFStream;
}  // namespace misc

namespace interact
{
class mwUpdateHandlerBase;
}

namespace cadcam
{
/// This class is a STL translator.
///
/// Transforms triangle mesh in a STL.
template <typename T, typename TVertex = mwTPoint3d<T>, typename TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwTSTLTranslator
{
public:
	typedef interact::mwUpdateHandlerBase UpdateHandler;
	typedef misc::mwAutoPointer<UpdateHandler> UpdateHandlerPtr;

	typedef cadcam::mwTPoint3d<T> point3d;

	typedef cadcam::mwContainerMesh<T, TVertex, TFaceNormal> Mesh;
	typedef typename cadcam::mwTTriangleVector<T, TVertex, TFaceNormal> TriangleVector;
#ifdef _WIN32
	typedef unsigned __int64 uint64_t;
#endif

	struct HeaderData
	{
		HeaderData(): m_hasColor(false), m_hasMaterial(false) {}

		bool m_hasColor;

		enum ColorIndex
		{
			RCOLOR = 0,
			GCOLOR = 1,
			BCOLOR = 2,
			ACOLOR = 3,
			COLOR_SIZE = 4,
		};

		unsigned char m_color[COLOR_SIZE];
		bool m_hasMaterial;
		unsigned char m_diffuseColor[COLOR_SIZE];
		unsigned char m_specularColor[COLOR_SIZE];
		unsigned char m_ambientColor[COLOR_SIZE];
	};

	/// Read STL from stream
	///
	/// Reads data from a stream and creates a mesh.
	///	@param inputStream stream
	///	@param mesh reference to the mesh that will be created
	///	@param header header structure
	///	@param useFileNormals
	///	@param compressMesh
	///	@param isStlBinary
	static void ReadSTLFromStream(
		misc::mwBinInputStream& inputStream,
		Mesh& mesh,
		HeaderData& header,
		bool useFileNormals,
		bool compressMesh,
		bool isStlBinary);

	/// Read STL
	///
	/// Reads data from an external file and creates a mesh.
	///	@param fileName the name of the external file
	///	@param mesh reference to the mesh that will be created
	///	@param useFileNormals
	///	@param useStdStreams
	///	@param compressMesh
	///	@param updateHandler for progress and cancel
	inline static void ReadSTL(
		const misc::mwFileName& fileName,
		Mesh& mesh,
		bool useFileNormals = true,
		bool useStdStreams = false,
		bool compressMesh = true,
		UpdateHandlerPtr updateHandler = UpdateHandlerPtr());

	/// Read STL
	///
	/// Reads data from an external file and creates a mesh.
	///	@param fileName the name of the external file
	///	@param mesh reference to the mesh that will be created
	///	@param useFileNormals
	///	@param useStdStreams
	///	@param compressMesh
	///	@param updateHandler for progress and cancel
	inline static void ReadSTL(
		const misc::mwstring& fileName,
		Mesh& mesh,
		bool useFileNormals = true,
		bool useStdStreams = false,
		bool compressMesh = true,
		UpdateHandlerPtr updateHandler = UpdateHandlerPtr());

	/// Read STL
	///
	/// Reads data from an external file and creates a mesh.
	///	@param fileName the name of the external file
	///	@param mesh reference to the mesh that will be created
	///	@param header header data struct
	///	@param useFileNormals
	///	@param useStdStreams
	///	@param compressMesh
	///	@param updateHandler for progress and cancel
	static void ReadSTL(
		const misc::mwFileName& fileName,
		Mesh& mesh,
		HeaderData& header,
		bool useFileNormals,
		bool useStdStreams = false,
		bool compressMesh = true,
		UpdateHandlerPtr updateHandler = UpdateHandlerPtr());

	static void ReadSTL(
		std::istream& input,
		Mesh& mesh,
		HeaderData& header,
		bool useFileNormals = true,
		bool useStdStreams = false,
		bool compressMesh = true,
		UpdateHandlerPtr updateHandler = UpdateHandlerPtr());

	/// Write STL
	///
	/// Writers an existing mesh to an external file, in STL format
	///	@param fileName reference to the output stream
	///	@param mesh reference to the mesh
	///	@param header header data
	inline static void WriteSTL(
		const misc::mwFileName& fileName, const Mesh& mesh, HeaderData& header);

	/// Write STL
	///
	/// Writers an existing mesh to an external file, in STL format
	///	@param fileName reference to the output stream
	///	@param mesh reference to the mesh
	///	@param bBinaryMode binarymode default = true
	///	@param preserveHeader default = true
	///	@param truncateNumbers default = true
	inline static void WriteSTL(
		const misc::mwFileName& fileName,
		const Mesh& mesh,
		bool bBinaryMode = true,
		bool preserveHeader = true,
		bool truncateNumbers = true);

	/// Write STL
	///
	/// Writers an existing mesh to an external file, in STL format
	///	@param fileName reference to the output stream
	///	@param mesh reference to the mesh
	///	@param bBinaryMode binarymode default = true
	///	@param preserveHeader default = true
	///	@param truncateNumbers default = true
	static void WriteSTLExt(
		const misc::mwFileName& fileName,
		const Mesh& mesh,
		bool bBinaryMode = true,
		bool preserveHeader = true,
		bool truncateNumbers = true);

	/// Read STL binary
	///
	/// Reads data from a stream and creates a mesh.
	///	@param l_strm stream
	///	@param mesh reference to the mesh that will be created
	///	@param headerData header structure
	static void ReadSTLBinary(misc::mwBinInputStream& l_strm, Mesh& mesh, HeaderData& headerData);

	/// Read STL binary
	///
	/// Reads data from a stream and creates a mesh.
	///	@param l_strm stream
	///	@param mesh reference to the mesh that will be created
	///	@param headerData header structure
	static void ReadSTLBinary(std::istream& l_strm, Mesh& mesh, HeaderData& headerData);

	/// ReadSTLBinaryWithEOSValidation
	///
	/// Reads from an input stream and throws an exception if the stream is not properly finished
	///	@param l_strm reference to the input stream
	///	@param mesh reference to the mesh
	///	@param headerData struct that holds header information
	inline static void ReadSTLBinaryWithEOSValidation(
		misc::mwBinInputStream& l_strm, Mesh& mesh, HeaderData& headerData);

	/// ReadSTLAscii
	///
	/// Reads from an input ascii stl stream and creates a mesh.
	///	@param l_strm reference to the input stream
	///	@param mesh reference to the mesh
	inline static void ReadSTLAscii(misc::mwIStream& l_strm, Mesh& mesh);

	/// ReadSTLSolidAscii
	///
	/// Reads one solid from an input ascii stl stream and creates a mesh.
	///	@param l_strm reference to the input stream
	///	@param mesh reference to the mesh
	inline static void ReadSTLSolidAscii(misc::mwIStream& l_strm, Mesh& mesh);

	/// WriteSTLBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	inline static void WriteSTLBinary(misc::mwBinOutputStream& strm, const Mesh& mesh);

	/// WriteSTLBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	inline static void WriteSTLBinary(std::ostream& strm, const Mesh& mesh);

	/// WriteSTLBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	///	@param header header data
	inline static void WriteSTLBinary(
		misc::mwBinOutputStream& strm, const Mesh& mesh, HeaderData& header);

	/// WriteSTLBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	///	@param header header data
	inline static void WriteSTLBinary(std::ostream& strm, const Mesh& mesh, HeaderData& header);

	/// WriteSTLAscii
	///
	/// Writes data from an existing mesh to an ascii output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	///	@param truncateNumbers default = true
	inline static void WriteSTLAscii(
		misc::mwOStream& strm, const Mesh& mesh, bool truncateNumbers = true);

	/// WriteSTLAsciiExt
	///
	/// Writes data from an existing mesh to an ascii output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	///	@param truncateNumbers default = true
	static void WriteSTLAsciiExt(
		misc::mwOStream& strm, const Mesh& mesh, bool truncateNumbers = true);

private:
	/// Constructor
	mwTSTLTranslator();

public:
	/// IsSTLFileBinary
	///
	/// Checks if an STL file is binary, with optional validation
	///	@param fileName file name object
	///	@param validate default = false
	static bool IsSTLFileBinary(const misc::mwFileName& fileName, bool validate = false);
	/// IsSTLStreamBinary
	///
	/// Checks if an STL stream is binary, with optional validation
	///	@param input stream object. Must be seekable
	///	@param size size of STL data in stream
	///	@param validate default = false
	static bool IsSTLStreamBinary(
		std::istream& input, const misc::mwBinInputStream::mwsize_t size, bool validate = false);
	/// IsSTLStreamBinary
	///
	/// Checks if an STL stream is binary, with optional validation
	///	@param input stream object
	///	@param validate default = false
	static bool IsSTLStreamBinary(std::stringstream& input, bool validate = false);
	/// OpenFile
	///
	/// Opens an existing file ascii or binary mode, and assigns it to a stream
	///	@param fileName the name of the file to be opened
	///	@param binaryMode the mode of opening the file (true for binary, false for ascii)
	///	@param strm reference to a stream that will be used to interact with the file
	inline static void OpenFile(
		const misc::mwFileName& fileName, bool binaryMode, misc::mwIFStream& strm);
	/// OpenFile
	///
	/// Opens an existing file ascii or binary mode, and assigns it to a stream
	///	@param fileName the name of the file to be opened
	///	@param binaryMode the mode of opening the file (true for binary, false for ascii)
	///	@param strm reference to a stream that will be used to interact with the file
	inline static void OpenFile(
		const misc::mwFileName& fileName, bool binaryMode, misc::mwOFStream& strm);

	/// BufferedReadTriangle
	///
	/// Reads a triangle from an input binary .stl file
	///	@param strm reference to the input stream
	///	@param normal reference for the normal
	///	@param point1 reference to the triangle's first 3DPoint
	///	@param point2 reference to the triangle's second 3DPoint
	///	@param point3 reference to the triangle's third 3DPoint
	///	@param buffer the buffer that will be used for file reading
	inline static bool BufferedReadTriangle(
		misc::mwBinInputStream& strm,
		point3d& normal,
		point3d& point1,
		point3d& point2,
		point3d& point3,
		float* buffer);
	inline static bool BufferedReadTriangle(
		std::istream& strm,
		point3d& normal,
		point3d& point1,
		point3d& point2,
		point3d& point3,
		float* buffer);

	/// ReadPointFromBuffer
	///
	/// Utility method, reads a point from a given buffer, using data starting at
	/// extractionStartPosition
	///	@param point reference to the input stream
	///	@param buffer the input buffer
	///	@param extractionStartPosition the position at which extraction will commence
	inline static bool ReadPointFromBuffer(
		point3d& point, float* buffer, const size_t& extractionStartPosition);

	/// WriteAscii
	///
	/// Writes a point3d in an output .stl file
	///	@param strm reference to the output stream
	///	@param pt reference to the 3DPoint
	///	@param truncateNumbers default=false
	inline static void WriteAscii(
		misc::mwOStream& strm, const point3d& pt, bool truncateNumbers = true);

	/// WriteBinary
	///
	/// Writes a point3d in an output .stl file
	///	@param strm reference to the output stream
	///	@param pt reference to the 3DPoint
	inline static void WriteBinary(misc::mwBinOutputStream& strm, const point3d& pt);
	inline static void WriteBinary(std::ostream& strm, const point3d& pt);

	/// Converts a float to a double
	inline static const float GetFloatValue(const double doubleValue);
	MW_FORCEINLINE static const float GetFloatValue(const float floatValue);

	/// FoundAsciiSTLKeywords
	///
	/// Test if a block read from an .stl file contains keywords specific to an stl file in ascii
	/// format
	///	@param readBlockFromFile a block of text readed from an STL file
	///	@return true if some of the keywords specific to an ascii STL file were found
	///		false if no ascii STL keywords have been found
	inline static bool FoundAsciiSTLKeywords(const std::string& readBlockFromFile);

private:
	/// WriteBinaryHeader
	///
	/// Write header of binary STL
	///	@param stream output
	///	@param header header data
	///	@param size header size in bytes
	inline static void WriteBinaryHeader(
		misc::mwBinOutputStream& stream, const char* header, unsigned int size);
	inline static void WriteBinaryHeader(
		std::ostream& stream, const char* header, unsigned int size);

	/// WriteBinaryHeader
	///
	/// Write header of binary STL
	///	@param stream output
	///	@param header header data
	inline static void WriteBinaryHeader(misc::mwBinOutputStream& stream, HeaderData& header);
	inline static void WriteBinaryHeader(std::ostream& stream, HeaderData& header);

public:
	/// ReadBinaryHeader
	///
	/// Read header of binary STL
	///	@param stream output
	///	@param header header data
	///	@param size header size in bytes
	template <class Stream>
	static void ReadBinaryHeader(Stream& stream, char* header, unsigned int size);

	/// Parse the 80 byte header at the top of the file for the overall
	/// color of the entire part.
	inline static void ParseBinaryHeader(const char* header, HeaderData& headerData);

private:
	/// WriteMeshBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	inline static void WriteMeshBinary(misc::mwBinOutputStream& strm, const Mesh& mesh);
	/// WriteMeshBinary
	///
	/// Writes data from an existing mesh to an binary output stream
	///	@param strm reference to the output stream
	///	@param mesh reference to the mesh that will be written
	inline static void WriteMeshBinary(std::ostream& strm, const Mesh& mesh);
};


typedef mwTSTLTranslator<double>
	mwSTLTranslator;  ///< typedef for an STlTransalator for double data type
typedef mwTSTLTranslator<float>
	mwfSTLTranslator;  ///< typedef for an STlTransalator for float data type

const int g_stlColorPrefixSize = 7;
const char g_stlColorPrefix[g_stlColorPrefixSize] = "COLOR=";
const int g_stlMaterialPrefixSize = 11;
const char g_stlMaterialPrefix[g_stlMaterialPrefixSize] = ",MATERIAL=";
const unsigned int g_stlHeaderLength = 80;


/// This class is a STL translator.
///
/// Transforms triangle mesh in a STL.


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadSTL(
	const misc::mwFileName& fileName,
	Mesh& mesh,
	bool useFileNormals,
	bool useStdStreams,
	bool compressMesh,
	UpdateHandlerPtr updateHandler)
{
	HeaderData header;
	ReadSTL(fileName, mesh, header, useFileNormals, useStdStreams, compressMesh, updateHandler);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadSTL(
	const misc::mwstring& fileName,
	Mesh& mesh,
	bool useFileNormals,
	bool useStdStreams,
	bool compressMesh,
	UpdateHandlerPtr updateHandler)
{
	ReadSTL(
		::misc::mwFileName(fileName),
		mesh,
		useFileNormals,
		useStdStreams,
		compressMesh,
		updateHandler);
}


#ifdef _WIN32
template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTL(
	const misc::mwFileName& fileName, const Mesh& mesh, HeaderData& header)
{
	misc::mwOFStream strm;
	OpenFile(fileName, true, strm);

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	// TODO FIXME: Maybe use misc::mwBinOutputStreamAdapter instead and don't use std::wostreams?
	misc::mwStdOutputStream mwStream(strm);
	MW_WARNING_POP

	if (!strm.is_open() || !strm.good())
	{
		throw misc::mwException(
			0, _T("Can not use ") + fileName.GetFilePath() + _T(" to write an STL file."));
	}
	WriteSTLBinary(mwStream, mesh, header);
}
#else
template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTL(
	const misc::mwFileName& fileName, const Mesh& mesh, HeaderData& header)
{
	std::ofstream strm;
	std::string file_name = fileName.GetFilePath().ToUTF8();
	strm.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
	if (!strm.is_open() || !strm.good())
	{
		throw misc::mwException(
			0, _T("Can not use ") + fileName.GetFilePath() + _T(" to write an STL file."));
	}
	WriteSTLBinary(strm, mesh, header);
}
#endif


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTL(
	const misc::mwFileName& fileName,
	const Mesh& mesh,
	bool bBinaryMode,
	bool preserveHeader,
	bool truncateNumbers)
{
	if (bBinaryMode)
	{
#ifdef _WIN32
		misc::mwOFStream strm;
#else
		std::ofstream strm;
#endif
		char header[g_stlHeaderLength];
		bool fileExists = misc::mwFileSystem::FileExists(fileName);

		if (preserveHeader && fileExists)
		{
			misc::mwFileIOStream inputStream(fileName, true);
			try
			{
				ReadBinaryHeader(inputStream, header, g_stlHeaderLength);
			}
			catch (const mwmiscException& e)
			{
				if (e.GetErrorCode() == mwmiscException::UNEXPECTED_END_OF_INPUT_STREAM &&
					inputStream.GetDataLength() == 0)
				{
					// trying to load header from empty file.
					// this is allowable behavior.
					// assume file does not exist
					fileExists = false;
				}
				else
				{
					throw;
				}
			}
		}
#ifdef _WIN32
		MW_WARNING_PUSH
		MW_WARNING_DISABLE_DEPRECATED
		// TODO change this method so that it creates an std::ofstream instead of a std::wofstream
		// Then use the new mwBinOutputStreamAdapter class

		OpenFile(fileName, true, strm);
		misc::mwStdOutputStream mwStream(strm);

		MW_WARNING_POP
#else
		std::string file_name = fileName.GetFilePath().ToUTF8();
		strm.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
		auto& mwStream = strm;
#endif
		if (!strm.is_open() || !strm.good())
		{
			throw misc::mwException(
				0, _T("Can not use ") + fileName.GetFilePath() + _T(" to write an STL file."));
		}

		if (preserveHeader && fileExists)
		{
			WriteBinaryHeader(mwStream, header, g_stlHeaderLength);
			WriteMeshBinary(mwStream, mesh);
		}
		else
		{
			WriteSTLBinary(mwStream, mesh);
		}
	}
	else
	{
		misc::mwOFStream strm;
		OpenFile(fileName, false, strm);
		if (!strm.is_open() || !strm.good())
		{
			throw misc::mwException(
				0, _T("Can not use ") + fileName.GetFilePath() + _T(" to write an STL file."));
		}
		WriteSTLAscii(strm, mesh, truncateNumbers);
	}
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadSTLBinaryWithEOSValidation(
	misc::mwBinInputStream& l_strm, Mesh& mesh, HeaderData& headerData)
{
	ReadSTLBinary(l_strm, mesh, headerData);
	// we should be at the end of stream or throw exception
	char overEOSdummyData;
	misc::mwBinInputStream::mwsize_t overEOS = 1;

	try
	{
		l_strm.Read(&overEOSdummyData, overEOS);
		if (overEOS)
		{
			throw cadcam::mwSTLParserException(mwSTLParserException::INVALID_FILE_FORMAT);
		}
	}
	catch (...)
	{
		// we are safe, we tried an EOS read and got exception as expected
	}
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadSTLAscii(
	misc::mwIStream& l_strm, Mesh& mesh)
{
	typename cadcam::mwSTLFile<T>::Ptr StlAsciiFile = new cadcam::mwSTLFile<T>;
	typename cadcam::mwParserSTL<T>::Ptr parserStlAsciiFile =
		new cadcam::mwParserSTL<T>(StlAsciiFile);
	parserStlAsciiFile->Parse(l_strm);
	mesh.SetTriangles(StlAsciiFile->GetTriangles());
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadSTLSolidAscii(
	misc::mwIStream& l_strm, Mesh& mesh)
{
	typename cadcam::mwSTLFile<T>::Ptr StlAsciiFile = new cadcam::mwSTLFile<T>();
	typename cadcam::mwParserSTL<T>::Ptr parserStlAsciiFile =
		new cadcam::mwParserSTL<T>(StlAsciiFile);
	parserStlAsciiFile->Parse(l_strm);
	mesh.SetTriangles(StlAsciiFile->GetTriangles());
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTLBinary(
	misc::mwBinOutputStream& strm, const Mesh& mesh)
{
	HeaderData header;
	header.m_hasColor = false;
	WriteSTLBinary(strm, mesh, header);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTLBinary(
	std::ostream& strm, const Mesh& mesh)
{
	HeaderData header;
	header.m_hasColor = false;
	WriteSTLBinary(strm, mesh, header);
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTLBinary(
	misc::mwBinOutputStream& strm, const Mesh& mesh, HeaderData& header)
{
	if (header.m_hasColor)
	{
		WriteBinaryHeader(strm, header);
	}
	else
	{
		//                              0        1         2         3         4         5         6
		//                              7         8
		//                              12345678901234567890123456789012345678901234567890123456789012345678901234567890
		char headerNew[g_stlHeaderLength + 1] =
			"STL File                                                                        ";
		WriteBinaryHeader(strm, headerNew, g_stlHeaderLength);
	}

	WriteMeshBinary(strm, mesh);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTLBinary(
	std::ostream& strm, const Mesh& mesh, HeaderData& header)
{
	if (header.m_hasColor)
	{
		WriteBinaryHeader(strm, header);
	}
	else
	{
		//                              0        1         2         3         4         5         6
		//                              7         8
		//                              12345678901234567890123456789012345678901234567890123456789012345678901234567890
		char headerNew[g_stlHeaderLength + 1] =
			"STL File                                                                        ";
		WriteBinaryHeader(strm, headerNew, g_stlHeaderLength);
	}

	WriteMeshBinary(strm, mesh);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteSTLAscii(
	misc::mwOStream& strm, const Mesh& mesh, bool truncateNumbers)
{
	strm << _T("solid ascii") << std::endl;

	unsigned lTriangles = (unsigned)mesh.GetNumberOfTriangles();
	for (unsigned l = 0; l < lTriangles; ++l)
	{
		const typename mwTMesh<T>::point3d& normal = mesh.GetTriangleNormalVector(l);
		strm << _T("  facet normal ");
		if (truncateNumbers)
		{
			strm << GetFloatValue(normal.x()) << _T(" ");
			strm << GetFloatValue(normal.y()) << _T(" ");
			strm << GetFloatValue(normal.z()) << std::endl;
		}
		else
		{
			strm << normal.x() << _T(" ");
			strm << normal.y() << _T(" ");
			strm << normal.z() << std::endl;
		}
		strm << _T("    outer loop") << std::endl;
		WriteAscii(strm, mesh.GetTriangleFirstVertexPosition(l), truncateNumbers);
		WriteAscii(strm, mesh.GetTriangleSecondVertexPosition(l), truncateNumbers);
		WriteAscii(strm, mesh.GetTriangleThirdVertexPosition(l), truncateNumbers);
		strm << _T("    endloop") << std::endl;
		strm << _T("  endfacet") << std::endl;
	}
	strm << _T("endsolid") << std::endl;
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::OpenFile(
	const misc::mwFileName& fileName, bool binaryMode, misc::mwIFStream& strm)
{
	misc::mwstring filePath = fileName.GetFilePath();
	if (binaryMode)
		strm.open(filePath.c_str(), std::ios_base::binary);
	else
		strm.open(filePath.c_str());
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::OpenFile(
	const misc::mwFileName& fileName, bool binaryMode, misc::mwOFStream& strm)
{
	misc::mwstring filePath = fileName.GetFilePath();
	if (binaryMode)
		strm.open(filePath.c_str(), std::ios_base::binary);
	else
		strm.open(filePath.c_str(), std::ios_base::out, misc::mwOFStream::ASCII_ENC);
}


template <typename T, typename TVertex, typename TFaceNormal>
inline bool mwTSTLTranslator<T, TVertex, TFaceNormal>::BufferedReadTriangle(
	misc::mwBinInputStream& strm,
	point3d& normal,
	point3d& point1,
	point3d& point2,
	point3d& point3,
	float* buffer)
{
	const size_t nrOfPointsToBeReadInOneShot = 12;
	const misc::mwBinInputStream::mwsize_t bytesToRead =
		sizeof(float) * nrOfPointsToBeReadInOneShot;

	uint64_t bytesRead = bytesToRead;

	strm.Read(buffer, bytesRead);
	ReadPointFromBuffer(normal, buffer, 0);
	ReadPointFromBuffer(point1, buffer, 3);
	ReadPointFromBuffer(point2, buffer, 6);
	ReadPointFromBuffer(point3, buffer, 9);
	return true;
}

template <typename T, typename TVertex, typename TFaceNormal>
inline bool mwTSTLTranslator<T, TVertex, TFaceNormal>::BufferedReadTriangle(
	std::istream& strm,
	point3d& normal,
	point3d& point1,
	point3d& point2,
	point3d& point3,
	float* buffer)
{
	const size_t nrOfPointsToBeReadInOneShot = 12;
	const uint64_t bytesToRead = sizeof(float) * nrOfPointsToBeReadInOneShot;

	std::streamsize bytesRead = (std::streamsize)bytesToRead;

	strm.read((char*)buffer, bytesRead);
	ReadPointFromBuffer(normal, buffer, 0);
	ReadPointFromBuffer(point1, buffer, 3);
	ReadPointFromBuffer(point2, buffer, 6);
	ReadPointFromBuffer(point3, buffer, 9);
	return true;
}

template <typename T, typename TVertex, typename TFaceNormal>
inline bool mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadPointFromBuffer(
	point3d& point, float* buffer, const size_t& extractionStartPosition)
{
	point.x(buffer[extractionStartPosition]);
	point.y(buffer[extractionStartPosition + 1]);
	point.z(buffer[extractionStartPosition + 2]);
	return true;
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteAscii(
	misc::mwOStream& strm, const point3d& pt, bool truncateNumbers)
{
	if (truncateNumbers)
	{
		strm << _T("      vertex ") << GetFloatValue(pt.x()) << _T(" ");
		strm << GetFloatValue(pt.y()) << _T(" ");
		strm << GetFloatValue(pt.z()) << std::endl;
	}
	else
	{
		strm << _T("      vertex ") << pt.x() << _T(" ");
		strm << pt.y() << _T(" ");
		strm << pt.z() << std::endl;
	}
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinary(
	misc::mwBinOutputStream& strm, const point3d& pt)
{
	float temp[3] = {GetFloatValue(pt.x()), GetFloatValue(pt.y()), GetFloatValue(pt.z())};
	strm.Write(&temp[0], sizeof(float) * 3);
}
template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinary(
	std::ostream& strm, const point3d& pt)
{
	float temp[3] = {GetFloatValue(pt.x()), GetFloatValue(pt.y()), GetFloatValue(pt.z())};
	strm.write((const char*)(&(temp[0])), sizeof(float) * 3);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline const float mwTSTLTranslator<T, TVertex, TFaceNormal>::GetFloatValue(
	const double doubleValue)
{
	if (doubleValue < double(mathdef::MW_MIN_FLOAT))
	{
		return mathdef::MW_MIN_FLOAT;
	}

	if (doubleValue > double(mathdef::MW_MAX_FLOAT))
	{
		return mathdef::MW_MAX_FLOAT;
	}

	if (fabs(doubleValue) < double(FLT_MIN))
	{
		return 0.;
	}

	return static_cast<float>(doubleValue);
}

template <typename T, typename TVertex, typename TFaceNormal>
MW_FORCEINLINE const float mwTSTLTranslator<T, TVertex, TFaceNormal>::GetFloatValue(
	const float floatValue)
{
	return floatValue;
}


template <typename T, typename TVertex, typename TFaceNormal>
inline bool mwTSTLTranslator<T, TVertex, TFaceNormal>::FoundAsciiSTLKeywords(
	const std::string& readBlockFromFile)
{
	const int nrOfKeywords = 9;
	std::string asciiSTLKeywords[nrOfKeywords] = {
		"solid", "facet", "normal", "outer", "loop", "vertex", "endloop", "endfacet", "endsolid"};

	bool keywordFound = false;

	for (int i = 0; i < nrOfKeywords; ++i)
	{
		if (readBlockFromFile.find(asciiSTLKeywords[i]) != std::string::npos)
		{
			keywordFound = true;
			break;
		}
	}

	return keywordFound;
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinaryHeader(
	misc::mwBinOutputStream& stream, const char* header, unsigned int size)
{
	stream.Write(reinterpret_cast<const void*>(header), size);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinaryHeader(
	std::ostream& stream, const char* header, unsigned int size)
{
	stream.write(header, size);
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinaryHeader(
	misc::mwBinOutputStream& stream, HeaderData& header)
{
	int remainingBytes = g_stlHeaderLength;

	if (header.m_hasColor)
	{
		// write prefix
		stream.Write(g_stlColorPrefix, g_stlColorPrefixSize - 1);
		// write 4 bytes of color
		stream.Write(header.m_color, HeaderData::COLOR_SIZE);

		remainingBytes -= g_stlColorPrefixSize - 1 + HeaderData::COLOR_SIZE;

		if (header.m_hasMaterial)
		{
			// write prefix
			stream.Write(g_stlMaterialPrefix, g_stlMaterialPrefixSize - 1);
			// write 3*4 bytes of material
			stream.Write(header.m_diffuseColor, HeaderData::COLOR_SIZE);
			stream.Write(header.m_specularColor, HeaderData::COLOR_SIZE);
			stream.Write(header.m_ambientColor, HeaderData::COLOR_SIZE);

			remainingBytes -= g_stlMaterialPrefixSize - 1 + 3 * HeaderData::COLOR_SIZE;
		}
	}

	// write remaining bytes
	for (int i = 0; i < remainingBytes; ++i)
	{
		const int stub = 32;  // space code
		stream.Write(&stub, 1);
	}
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteBinaryHeader(
	std::ostream& stream, HeaderData& header)
{
	int remainingBytes = g_stlHeaderLength;

	if (header.m_hasColor)
	{
		// write prefix
		stream.write(g_stlColorPrefix, g_stlColorPrefixSize - 1);
		// write 4 bytes of color
		stream.write((const char*)header.m_color, HeaderData::COLOR_SIZE);

		remainingBytes -= g_stlColorPrefixSize - 1 + HeaderData::COLOR_SIZE;

		if (header.m_hasMaterial)
		{
			// write prefix
			stream.write(g_stlMaterialPrefix, g_stlMaterialPrefixSize - 1);
			// write 3*4 bytes of material
			stream.write((const char*)header.m_diffuseColor, HeaderData::COLOR_SIZE);
			stream.write((const char*)header.m_specularColor, HeaderData::COLOR_SIZE);
			stream.write((const char*)header.m_ambientColor, HeaderData::COLOR_SIZE);

			remainingBytes -= g_stlMaterialPrefixSize - 1 + 3 * HeaderData::COLOR_SIZE;
		}
	}

	// write remaining bytes
	for (int i = 0; i < remainingBytes; ++i)
	{
		const char stub = 32;  // space code
		stream.put(stub);
	}
}


template <typename T, typename TVertex, typename TFaceNormal>
template <class Stream>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ReadBinaryHeader(
	Stream& stream, char* header, unsigned int size)
{
	std::streamsize len = size;
	stream.read(header, len);
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::ParseBinaryHeader(
	const char* header, HeaderData& headerData)
{
	/* The Materialise Magics software uses the 80 byte header at the top of the file
	to represent the overall color of the entire part. If color is used, then
	somewhere in the header should be the ASCII string "COLOR=" followed by four
	bytes representing red, green, blue and alpha channel (transparency) in the
	range 0-255. This is the color of the entire object unless overridden at each
	facet. Magics also recognizes a material description; a more detailed surface
	characteristic. Just after "COLOR=RGBA" specification should be another ASCII
	string ",MATERIAL=" followed by three colors (3*4 bytes): first is a color
	of diffuse reflection, second is a color of specular highlight, and third is
	an ambient light. Material settings are preferred over color.*/

	// find first occurrence of g_stlColorPrefix

	const char* str = header;
	unsigned int len = g_stlHeaderLength - g_stlColorPrefixSize + 1 - HeaderData::COLOR_SIZE;
	bool found = false;
	for (unsigned int i = 0; i <= len; ++i, ++str)
	{
		if (strncmp(str, g_stlColorPrefix, g_stlColorPrefixSize - 1) == 0)
		{
			len -= i;
			str += g_stlColorPrefixSize - 1;
			found = true;
			break;
		}
	}

	if (!found)
	{
		headerData.m_hasColor = false;
		headerData.m_hasMaterial = false;
		return;
	}

	// read the color value

	const unsigned char* color = reinterpret_cast<const unsigned char*>(str);
	headerData.m_color[HeaderData::RCOLOR] = color[HeaderData::RCOLOR];
	headerData.m_color[HeaderData::GCOLOR] = color[HeaderData::GCOLOR];
	headerData.m_color[HeaderData::BCOLOR] = color[HeaderData::BCOLOR];
	headerData.m_color[HeaderData::ACOLOR] = color[HeaderData::ACOLOR];
	headerData.m_hasColor = true;

	// check if material information is presented

	if (len < (g_stlMaterialPrefixSize - 1 + 3 * HeaderData::COLOR_SIZE))
	{
		headerData.m_hasMaterial = false;
		return;
	}

	str += HeaderData::COLOR_SIZE;

	if (strncmp(str, g_stlMaterialPrefix, g_stlMaterialPrefixSize - 1) != 0)
	{
		headerData.m_hasMaterial = false;
		return;
	}

	// read material colors

	str += g_stlMaterialPrefixSize - 1;
	color = reinterpret_cast<const unsigned char*>(str);
	headerData.m_diffuseColor[HeaderData::RCOLOR] = color[HeaderData::RCOLOR];
	headerData.m_diffuseColor[HeaderData::GCOLOR] = color[HeaderData::GCOLOR];
	headerData.m_diffuseColor[HeaderData::BCOLOR] = color[HeaderData::BCOLOR];
	headerData.m_diffuseColor[HeaderData::ACOLOR] = color[HeaderData::ACOLOR];
	color += HeaderData::COLOR_SIZE;
	headerData.m_specularColor[HeaderData::RCOLOR] = color[HeaderData::RCOLOR];
	headerData.m_specularColor[HeaderData::GCOLOR] = color[HeaderData::GCOLOR];
	headerData.m_specularColor[HeaderData::BCOLOR] = color[HeaderData::BCOLOR];
	headerData.m_specularColor[HeaderData::ACOLOR] = color[HeaderData::ACOLOR];
	color += HeaderData::COLOR_SIZE;
	headerData.m_ambientColor[HeaderData::RCOLOR] = color[HeaderData::RCOLOR];
	headerData.m_ambientColor[HeaderData::GCOLOR] = color[HeaderData::GCOLOR];
	headerData.m_ambientColor[HeaderData::BCOLOR] = color[HeaderData::BCOLOR];
	headerData.m_ambientColor[HeaderData::ACOLOR] = color[HeaderData::ACOLOR];
	headerData.m_hasMaterial = true;
}


template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteMeshBinary(
	misc::mwBinOutputStream& strm, const Mesh& mesh)
{
	int nTotalTriangles = static_cast<int>(mesh.GetNumberOfTriangles());

	misc::mwBinInputStream::mwsize_t size = sizeof(nTotalTriangles);

	strm.Write(&nTotalTriangles, size);

	short dummyint = 0;
	for (int l = 0; l < nTotalTriangles; ++l)
	{
		WriteBinary(strm, mesh.GetTriangleNormalVector(l));
		WriteBinary(strm, mesh.GetTriangleFirstVertexPosition(l));
		WriteBinary(strm, mesh.GetTriangleSecondVertexPosition(l));
		WriteBinary(strm, mesh.GetTriangleThirdVertexPosition(l));

		if (mesh.IsTriangleAdditionalDataSupport())
		{
			unsigned short additionalData = mesh.GetTriangleAdditionalData(l);
			misc::mwBinInputStream::mwsize_t sizeInt = sizeof(additionalData);
			strm.Write(&additionalData, sizeInt);
		}
		else
		{
			misc::mwBinInputStream::mwsize_t sizeInt = sizeof(dummyint);
			strm.Write(&dummyint, sizeInt);
		}
	}
}

template <typename T, typename TVertex, typename TFaceNormal>
inline void mwTSTLTranslator<T, TVertex, TFaceNormal>::WriteMeshBinary(
	std::ostream& strm, const Mesh& mesh)
{
	int nTotalTriangles = static_cast<int>(mesh.GetNumberOfTriangles());

	size_t size = (std::streamsize)sizeof(nTotalTriangles);
	strm.write((const char*)&nTotalTriangles, (std::streamsize)size);

	short dummyint = 0;
	for (int l = 0; l < nTotalTriangles; ++l)
	{
		WriteBinary(strm, mesh.GetTriangleNormalVector(l));
		WriteBinary(strm, mesh.GetTriangleFirstVertexPosition(l));
		WriteBinary(strm, mesh.GetTriangleSecondVertexPosition(l));
		WriteBinary(strm, mesh.GetTriangleThirdVertexPosition(l));
		const std::streamsize sizeInt = (std::streamsize)sizeof(dummyint);
		strm.write((const char*)&dummyint, sizeInt);
	}
}
typedef mwTSTLTranslator<double>
	mwSTLTranslator;  ///< typedef for an STlTransalator for double data type
typedef mwTSTLTranslator<float>
	mwfSTLTranslator;  ///< typedef for an STlTransalator for float data type
}  // namespace cadcam
#endif  //	MW_MWSTLTRANSLATOR_HPP_
