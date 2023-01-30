// (C) 2008-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMPREPROCESSOR_HPP_
#define MW_MWMACHSIMPREPROCESSOR_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwAutoPointer.hpp"	

class MW_SIMUTIL_API mwMachSimPreprocessor
{
public:
	enum type 
	{
		MODIFIER = 0,
		INSERTER
	};

    //! Constructor
    mwMachSimPreprocessor();

    //! Get preprocessor source code filename
    const misc::mwstring& GetFileName() const;

    //! Set preprocessor source code filename
    void SetFileName(const misc::mwstring& fileName);

    //! Get preprocessor instance variable name
    const misc::mwstring& GetInstanceVariableName() const;

    //! Set preprocessor instance variable name
    void SetInstanceVariableName(const misc::mwstring& instanceVariableName);

	//! Get preprocessor type
	const type& GetType() const;

	//! Set preprocessor type
	void SetType(const type& toSet);
	//! Deep cloning 
	const misc::mwAutoPointer<mwMachSimPreprocessor> Clone() const;

private:
    misc::mwstring	m_fileName;
    misc::mwstring	m_instanceVariableName;
	type			m_type;
};
#endif	//	MW_MWMACHSIMPREPROCESSOR_HPP_
