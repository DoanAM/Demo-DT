// (C) 2003-2013 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWVERSIONEDOBJECT_HPP_
#define MW_MWVERSIONEDOBJECT_HPP_
#include "mwSimUtilDllImpExpDef.hpp"

namespace misc
{
	class MW_SIMUTIL_API mwVersionedObject
	{
	public:
		typedef unsigned long version;
		
		inline mwVersionedObject()
			:mVersion( 0 )
		{
		};
		
		virtual inline ~mwVersionedObject()
		{
			mVersion = static_cast<version>(-1);
		};

		inline void IncreaseVersion()
		{
			mVersion++;
		};
		
		inline const unsigned long &GetCurrentVersion() const
		{
			return mVersion;
		};
		
		const bool HasChanged( const version &refVersion ) const
		{
			return mVersion != refVersion;
		};
		
	protected:
	private:
		version			mVersion;
	};
};
#endif	//	MW_MWVERSIONEDOBJECT_HPP_
