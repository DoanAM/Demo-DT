// (C) 2005-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWACTIONKEYBINDING_HPP_
#define MW_MWACTIONKEYBINDING_HPP_
#include	"mwDllImpExpDef.hpp"
#include	"mwString.hpp"
#include	"mwVKey.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
	class MW_5AXUTIL_API mwActionKeyBinding
	{
	public:

		mwActionKeyBinding();
		mwActionKeyBinding(const mwVKey& boundKey);
		mwActionKeyBinding(const mwVKey& boundKey,const unsigned short keyModifier );
		
		const misc::mwVKey& GetBoundVKey()const;
		unsigned short GetKeyModifier() const;

		bool ModifierHasAlt() const;
		bool ModifierHasShift() const;
		bool ModifierHasCtrl() const;
		
		void SetBoundVKey(const mwVKey& newkey); 
		void SetKeyModifier( const unsigned short newModifier );

		bool operator==(const mwActionKeyBinding &secondActionBind) const;
		bool operator!=(const mwActionKeyBinding &secondActionBind) const;
		
		misc::mwstring ToString() const;

		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			mwActionKeyBinding( unsigned int boundKey );		
		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			mwActionKeyBinding( unsigned int boundKey, unsigned short keyModifier );	

		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			unsigned int GetBoundKey() const;
		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			void SetBoundKey( const unsigned int newKey );

		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			static unsigned short GetKeyCode( const misc::mwstring& keyName );	
		MW_DEPRECATED("Deprecated in 2015.12, Not supporting extended keys , please don't use")
			static misc::mwstring GetKeyName( const unsigned short& keyCode );

		enum modifier
		{
			NONE = 0x00,
			SHIFT = 0x01,
			CTRL = 0x02,
			ALT = 0x04,
			EXT = 0x08 // HOTKEYF_EXT
		};

	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	
		misc::mwVKey m_virtualKey;
		unsigned short m_modifier;
	
	#pragma warning(pop)
	};

}
#endif	//	MW_MWACTIONKEYBINDING_HPP_
