// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWPOSTEDMOVECASTER_HPP_
#define MW_MWPOSTEDMOVECASTER_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwPosted3axMove.hpp"
#include "mwPosted4axMove.hpp"
#include "mwPosted5axMove.hpp"
#include "mwPosted6axMove.hpp"
#include "mwPostedNaxMove.hpp"

namespace post
{
	//! allow casting/conversion from a posting move type to another type
	//! Note: casting returns same object while conversion create a new one
	//! allow ShallowComparer of two autopointers of mwPostedMove(s)

	class MW_5AXUTIL_API mwPostedMoveCaster 
	{
	public:				
		
		//! creates a NEW posted move based on pass input, you may also call no template versions:ConverTo3ax,ConverTo4ax,ConverTo5ax,ConverTo6ax
		/*! Note the specializations of this function are defined outside of the class at the end of this hpp file
		*/
		template<typename TDesiredMove> inline static misc::mwAutoPointer <TDesiredMove> Convert(const mwPostedMove& /*toConvert*/)
		{
			throw misc::mwException(0, _T("Specialization not availabel for this type of posted move"));
		};
		
		//! creates a NEW 3axis posted move based on pass input
		static const mwPosted3axMovePtr ConverTo3ax(const mwPostedMove&);
		//! creates a NEW 4axis posted move based on pass input
		static const mwPosted4axMovePtr ConverTo4ax(const mwPostedMove&);
		//! creates a NEW 5axis posted move based on pass input
		static const mwPosted5axMovePtr ConverTo5ax(const mwPostedMove&);
		//! creates a NEW 6axis posted move based on pass input
		static const mwPosted6axMovePtr ConverTo6ax(const mwPostedMove&);

		static const mwPostedNaxMovePtr ConverToNax(const mwPostedMove&);

		
		static const mwPosted3axMovePtr SafeCast3ax(const mwPostedMovePtr&);
		static mwPosted3axMovePtr SafeCast3ax(mwPostedMovePtr&);
		static const mwPosted3axMove& SafeCast3ax(const mwPostedMove&);
		static mwPosted3axMove& SafeCast3ax(mwPostedMove&);
		
		static const mwPosted4axMovePtr SafeCast4ax(const mwPostedMovePtr&);
		static mwPosted4axMovePtr SafeCast4ax(mwPostedMovePtr&);
		static const mwPosted4axMove& SafeCast4ax(const mwPostedMove&);
		static mwPosted4axMove& SafeCast4ax(mwPostedMove&);
		
		static const mwPosted5axMovePtr SafeCast5ax(const mwPostedMovePtr&);
		static mwPosted5axMovePtr SafeCast5ax(mwPostedMovePtr&);
		static const mwPosted5axMove& SafeCast5ax(const mwPostedMove&);
		static mwPosted5axMove& SafeCast5ax(mwPostedMove&);
		
		static const mwPosted6axMovePtr SafeCast6ax(const mwPostedMovePtr&);
		static mwPosted6axMovePtr SafeCast6ax(mwPostedMovePtr&);
		static const mwPosted6axMove& SafeCast6ax(const mwPostedMove&);
		static mwPosted6axMove& SafeCast6ax(mwPostedMove&);

		static const mwPostedNaxMovePtr SafeCastNax(const mwPostedMovePtr&);
		static mwPostedNaxMovePtr SafeCastNax(mwPostedMovePtr&);
		static const mwPostedNaxMove& SafeCastNax(const mwPostedMove&);
		static mwPostedNaxMove& SafeCastNax(mwPostedMove&);
		
		static const bool ShallowComparer(const mwPostedMovePtr& first, const mwPostedMovePtr& second);

		static const double GetMaxAngleChange(const mwPostedMove& move1, const mwPostedMove& move2);
		
	private:
	
		mwPostedMoveCaster(){}; // allow only static functions....		

	};//end class mwPostedMoveCaster definition
	
	//! 3axis specialization of Convert template function
	template<> inline mwPosted3axMovePtr mwPostedMoveCaster::Convert<mwPosted3axMove>(const mwPostedMove& toConvert)
	{
		return mwPostedMoveCaster::ConverTo3ax(toConvert);
	}
	//! 4axis specialization of Convert template function
	template<> inline mwPosted4axMovePtr mwPostedMoveCaster::Convert<mwPosted4axMove>(const mwPostedMove& toConvert)
	{
		return mwPostedMoveCaster::ConverTo4ax(toConvert);
	}
	//! 5axis specialization of Convert
	template<> inline mwPosted5axMovePtr mwPostedMoveCaster::Convert<mwPosted5axMove>(const mwPostedMove& toConvert)
	{
		return mwPostedMoveCaster::ConverTo5ax(toConvert);
	}
	//! 6axis specialization of Convert
	template<> inline mwPosted6axMovePtr mwPostedMoveCaster::Convert<mwPosted6axMove>(const mwPostedMove& toConvert)
	{
		return mwPostedMoveCaster::ConverTo6ax(toConvert);
	}

	template<> inline mwPostedNaxMovePtr mwPostedMoveCaster::Convert<mwPostedNaxMove>(const mwPostedMove& toConvert)
	{
		return mwPostedMoveCaster::ConverToNax(toConvert);
	}
}//end namespace post

#endif