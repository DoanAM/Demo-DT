// (C) 2013-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

//!Header file used internally by ModuleWorks for a caching calculation mechanism, please don't modify

#if _MSC_VER >= 1920 //If we are compiling with VisualStudio 2019
	#if defined(_WIN64) && defined(UNICODE) && !defined(_DEBUG) && _ITERATOR_DEBUG_LEVEL==0 //ReleaseUnicode x64 with MW default settings for iterators 
		#ifndef IS_CACHE_VALIDATION_ENABLED
			#define IS_CACHE_VALIDATION_ENABLED //Enable caching validation only in this context
		#endif
	#else
		#ifdef IS_CACHE_VALIDATION_ENABLED
			#undef IS_CACHE_VALIDATION_ENABLED
		#endif
	#endif
#endif

#ifdef CACHING_INTERNAL_BEGIN
	#undef CACHING_INTERNAL_BEGIN
#endif

#ifdef CACHING_INTERNAL_END
	#undef CACHING_INTERNAL_END
#endif

#ifdef CACHING_CLASS_PACKED
	#define CACHING_INTERNAL_BEGIN pack(push, 1)
#else 	
	#define CACHING_INTERNAL_BEGIN 
#endif


#ifdef CACHING_CLASS_PACKED
	#define CACHING_INTERNAL_END pack(pop)
#else 	
	#define CACHING_INTERNAL_END				
#endif
