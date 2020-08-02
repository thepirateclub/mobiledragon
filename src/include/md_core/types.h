/** \file
 *	Basic types definitions. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TYPES_H__
#define __MD_TYPES_H__

#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)
#include <e32def.h>
#include <e32std.h>
#endif

//#define Fixed float

namespace mdragon
{

#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)

typedef char Char;
typedef unsigned char Byte;
typedef TInt16 Short;
typedef TUint16 Word;
typedef int Int;
typedef unsigned int DWord;
#define Long TInt64
typedef TReal32 Float;
typedef TReal64 Double;
typedef Int Bool;
#define True (1>0)
#define False (1<0)

#endif // SYMBIAN


#if defined(MD_OS_WINCE) || defined(MD_OS_WIN32)

typedef char Char;
typedef unsigned char Byte;
typedef short Short;
typedef unsigned short Word;
typedef int Int;
typedef unsigned int DWord;
typedef __int64 Long;
typedef float Float;
typedef double Double;
typedef Int Bool;
#define True true
#define False false

#endif //defined(MD_OS_WINCE) || defined(MD_OS_WIN32)

#ifdef MD_OS_PALM

typedef char Char;
typedef unsigned char Byte;
typedef short Short;
typedef unsigned short Word;
typedef int Int;
typedef unsigned int DWord;
typedef long long Long;
typedef float Float;
typedef double Double;
typedef Int Bool;
#define True (1>0)
#define False (1<0)

#endif // MD_OS_PALM

} // namespace mdragon

#endif // __MD_TYPES_H__
