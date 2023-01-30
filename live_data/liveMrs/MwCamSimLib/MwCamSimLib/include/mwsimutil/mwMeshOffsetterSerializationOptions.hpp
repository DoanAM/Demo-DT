// (C) 2013 by ModuleWorks GmbH
// Owner: CutSim

/// \file
///               this module declares the
/// mwMeshOffsetterSerializationOptions class

#ifndef MW_MWMESHOFFSETTERSERIALIZATIONOPTIONS_HPP_
#define MW_MWMESHOFFSETTERSERIALIZATIONOPTIONS_HPP_
namespace Verifier
{
class mwMeshOffsetterSerializationOptions
{
public:
	typedef unsigned int type;

	// Options
	static const unsigned int COMPRESS_LIBZ = 1;
	static const unsigned int COMPRESS_GZIP = 2;
	// static const unsigned int COMPRESS_BZIP2    =   4;    Not available due to lack of an actual
	// bzip2 library in the ModuleWorks code tree
	//                                                      (the bzip2 compression of
	//                                                      mwCompressedFile.cpp uses copy-pasted
	//                                                      bzip2 source code)
	static const unsigned int OMIT_MESHES = 8;
	// static const unsigned int                   =  16;
	// static const unsigned int                   =  32;
	// static const unsigned int                   =  64;
	// static const unsigned int                   = 128;

	static const unsigned int DEFAULT = 2;  // Compress gzip and write meshes
};
}  // namespace Verifier
#endif  //	MW_MWMESHOFFSETTERSERIALIZATIONOPTIONS_HPP_
