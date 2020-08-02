/** \file
 *	Template library additionals. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TL_H__
#define __MD_TL_H__

#pragma warning ( disable : 4291 )

template<class T>
void* operator new (unsigned int, T* ptr)
{
	return ptr;
}

namespace mdragon
{

typedef DWord size_type;
typedef Int ptrdiff_t;
const DWord npos = 0xffffffffUL;

void mtl_assert(Bool expression, const Char *expression_string, 
				const Char *file, Int line);

#if ( defined(DEBUG) && defined(MD_OS_WINCE) ) || defined(_DEBUG)
	#define MD_TL_DEBUG
	#define assert(e) \
		mtl_assert(e, #e, __FILE__, __LINE__)
#else
	#define assert(expression__)
#endif

} //namespace mdragon


#endif //__MD_TL_H__
