/** \file
 *	Basic template memory management functions. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TL_MEMORY_H__
#define __MD_TL_MEMORY_H__

namespace mdragon
{

template <class T1, class T2> inline
void construct( T1 * pointer, const T2& t )
{
	assert ( pointer != NULL );
	new ( pointer ) T1 ( t );
}


template <class T> inline
void destroy( T * pointer )
{
	assert ( pointer != NULL );
	pointer->~T ();
}

template <class ForwardIterator>
void destroy( ForwardIterator first, ForwardIterator last )
{
	for( ; first != last; ++first )
		destroy( &*first );
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy( InputIterator first, InputIterator last,
                                   ForwardIterator result )
{
	for( ; first != last; ++first, ++result )
		construct( &*result, *first );
	return result;
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_move( InputIterator first, InputIterator last,
                                   ForwardIterator result )
{
	for( ; first != last; ++first, ++result )
	{
		construct( &*result, *first );
		destroy( first );
	}
	return result;
}

template <class BidirectionalIterator1, class BidirectionalIterator2> 
inline BidirectionalIterator2 uninitialized_move_backward( 
		BidirectionalIterator1 first, BidirectionalIterator1 last, 
		BidirectionalIterator2 result )
{
	for ( --first, --last, --result; last != first; --last, --result )
	{
		construct( &*result, *last );
		destroy( last );
	}
	return result;
}

template <class ForwardIterator, class T>
void uninitialized_fill( ForwardIterator first, ForwardIterator last, 
                        const T & t )
{
	for( ; first != last; ++first )
		construct( &*first, t );
}

template <class ForwardIterator, class Size, class T>
void uninitialized_fill_n( ForwardIterator first, Size n,
                                     const T & t )
{
	for( ; n ; ++first, --n )
		construct( &*first, t );
}


template<class T>
class temporary_buffer
{
public:
	typedef T value_type;
	typedef T * iterator;
	typedef const T * const_iterator;
	typedef T & reference;
	typedef const T & const_reference;
	typedef T * pointer;
	typedef const T * const_pointer;
	typedef ptrdiff_t difference_type;
	typedef size_type size_type;
	typedef temporary_buffer<T> self;

	inline explicit temporary_buffer( size_type size )
	{
		data_size = size;
		buffer = data_size ? new T [data_size] : NULL;
	}

	inline ~temporary_buffer() { delete [] buffer; }

	inline size_type size() const { return data_size; } 

	inline iterator begin()
	{
		return buffer;
	}

	inline iterator end()
	{
		return buffer + data_size;
	}

private:
	temporary_buffer ( const self & ) { ; }
	temporary_buffer & operator = (const self & ) { ; }

	T * buffer;
	size_type data_size;
};

} //namespace mdragon

#endif // __MD_TL_MEMORY_H__
