/** \file
 *	Memory management utility functions. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MEMORY_H__
#define __MD_MEMORY_H__

#undef NULL 
#define NULL 0

namespace mdragon
{

/// Fills memory block with given value.
/**
 *	@param dst - pointer to memory block.
 *	@param val - value to fill memory with.
 *	@param n - memory block size.
 */
void* memset( void *dst, Int val, Int n );

/// Copy characters of one string to another.
/**
 *	@param dst - destination string.
 *	@param src - source string.
 *	@param count - number of characters to copy.
 *	@return dst.
 */
char * strncpy ( Char * dst, const Char * src, Int count );

/// Compare characters of two strings.
/**
 *	@param string1 - first string to compare.
 *	@param string2 - second string to compare.
 *	@param count - number of characters to compare.
 *	@return < 0 string1 less than string2,
 *			0 string1 identical to string2, 
 *			> 0 string1 greater than string2.
 */
Int strncmp ( const Char * string1, const Char * string2, Int count );

/// Compare characters of two strings.
/**
 *	@param string1 - first string to compare.
 *	@param string2 - second string to compare.
 *	@return < 0 string1 less than string2,
 *			0 string1 identical to string2, 
 *			> 0 string1 greater than string2.
 */
Int strcmp (  const Char * string1,  const Char * string2 );

/// Searches a string for the first occurrence specified character. Case sensitive.
/**
 *	@param str - string to be searched.
 *	@param ch - character to search.
 *	@return address of the first occurrence of the character in the string 
 *			if successful, NULL otherwise.
 */
char * strchr ( const Char * str, Int ch );

/// Copies one string to another.
/**
 *	@param dst - pointer to destination string.
 *	@param src - pointer to the ASCIIZ source string.
 *	@return dst.
 */
Char * strcpy ( Char * dst, const Char * src );

/// Appends one string to another.
/**
 *	@param dst - pointer to a ASCIIZ string to which the function appends src. 
 *			That buffer must be large enough to hold both strings and the null terminator.
 *	@param str - pointer to a null-terminated string to be appended to dst.
 *	@return dst.
 */
Char * strcat ( Char * dst, const Char * src );

/// Finds the first occurrence of a substring within a string. Case sensitive.
/**
 *	@param where - string beign searched.
 *	@param what - string to search for.
 *	@return address of first occurrence of the matching substring if successful,
 *			NULL otherwise.
 */
Char * strstr (  const Char * str1,  const Char * str2 );

/// Get the length of a string.
/**
 *	@param str - ASCIIZ string.
 *	@return string length.
 */
Int strlen (  const Char * str );

/// Searches a string for the last occurrence of a specified character.
/**
 *	@param str - ASCIIZ string beign searched.
 *	@param ch - character to find.
 *	@return pointer to the last occurrence of ch in string, otherwise NULL.
 */
Char * strrchr (  const Char *srt, const Char ch );

/// Convert a string to lowercase.
/**
 *	@param str - string to convert.
 *	@return str.
 */
Char * _strlwr ( Char * str );

/// Convert a string to uppercase.
/**
 *	@param str - ASCIIZ string to convert.
 *	@return str.
 */
Char * _strupr ( Char * str );


Int * memcpy32( Int * dst, Int * src, Int count );

/// Copies data between buffers.
/**
 *  If source and destination buffers overlap, the behaviour is undefined,
 *	use memmove instead.
 *	@param dst - destination buffer.
 *	@param src - source buffer.
 *	@param count - number of bytes to copy.
 *	@return dst.
 */
void * memcpy( void * dst, const void * src, Int count );

/// Copies data between buffers.
/**
 *  If source and destination buffers overlap, the behaviour is undefined,
 *	use memmove instead.
 *	@param dst - destination buffer.
 *	@param src - source buffer.
 *	@param count - number of bytes to copy.
 *	@return dst.
 */
void * memmove( void * dst, const void * src, Int count );

/// Compares content of two buffers.
/**
 *	@param buf1 - first buffer to compare.
 *	@param buf2 - second buffer to compare.
 *	@param count - number of bytes to compare.
 *	@return < 0 buf1 less than buf2 
 *			0 buf1 identical to buf2 
 *			> 0 buf1 greater than buf2 
 */
Int memcmp ( const void * buf1, const void * buf2, Int count );


/// Allocates memory blocks.
/**
 *	@param size - bytes to allocate.
 *	@return void pointer to the allocated space, or NULL if there is 
			insufficient memory available.
 */
void* malloc( Int size );

/// Frees memory block allocated by malloc.
/**
 *	@param memblock - pointer to previously allocated memory block to be freed.
 */
void free( void* memblock );

/// Reallocate memory blocks.
/**
 *	@param memblock - pointer to memory block to reallocate.
 *	@param size - new memory block size.
 *	@return void pointer to reallocated memory block or NULL if there is 
 *			insufficient memory avalable.
 */
void *realloc( void *memblock, Int size );



void x64toa ( Long val, Char *buf, unsigned radix, Int is_neg );

void xtoa ( DWord val, Char *buf, unsigned radix, Int is_neg );

Char * _itoa ( Int value, Char *dst, Int radix );

Char * _ltoa ( Int value, Char *dst, Int radix );

Char * _ultoa ( DWord value, Char *dst, Int radix );

Char * _i64toa( Long val, Char *buf, Int radix );

Char * _ui64toa( Long val, Char *buf, Int radix );

void double_to_string( Double d, Char* buf );

} // namespace mdragon

#endif // __MD_MEMORY_H__
