/** \file
 *	Template static array. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ARRAY_H__
#define __MD_ARRAY_H__

namespace mdragon 
{

/// Template static array class.
/**
 *	@param T array element type.
 *	@param N array size.
 */
template <class T, size_type N> 
class array 
{
public:
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T & reference;
	typedef const T & const_reference;
	typedef T* pointer;
	typedef Int difference_type;
	typedef size_type size_type;
	typedef array<T,N> self;


	/// Returns an iterator pointing to the first element.
	inline iterator begin() {return &elems[0];}

	/// Returns a const iterator pointing to the first element.
	inline const_iterator begin() const {return &elems[0];}

	/// Returns an iterator pointing past the end of the array.
	inline iterator end() {return &elems[N];}

	/// Returns an const iterator pointing past the end of the array.
	inline const_iterator end() const {return &elems[N];}

	/// Returns the size of the array.
	inline size_type size() const {return N;}

	/// Return const reference to n'th element.
	inline const_reference at(size_type n) const
	{
		assert( n < N );
		return elems[n];
	}

	/// Return reference to n'th element.
	inline reference at(size_type n)
	{
		assert( n < N );
		return elems[n];
	}

	/// Return const reference to n'th element.
	inline const_reference operator [] (size_type n) const {return at(n);}

	/// Return reference to n'th element.
	inline reference operator[](size_type n) {return at(n); }

	/// Get index of first element matching t, or end().
	inline size_type index_of( const_reference t ) const 
	{
		const_iterator i = find( t );
		return ( i == end() ) ? npos : ( i - begin() );
	}

	/// Returns iterator pointing to first element matching t or end().
	inline iterator find ( const_reference t )
	{
		return mdragon::find( begin(), end(), t );
	}

	/// Returns const iterator pointing to first element matching t or end().
	inline const_iterator find ( const_reference t ) const
	{
		return mdragon::find( begin(), end(), t );
	}

	/// The assignment operator
	template <class X> inline
	self & operator = ( const array<X,N> & src )
	{
		mdragon::copy( src.begin(), src.end(), begin() );
		return *this;
	}

	/// Swaps the contents with another array.
	inline void swap( self & dst )
	{
		swap_ranges( begin(), end(), dst.begin() );
	}

	/// Assings value t to every element in the array.
	inline void assign( const T & t )
	{
		fill_n( begin(), N, t );
	}

	/// Array elements.
	T elems[N];
};


//////////////////////////////////////////////////////////////////////////
// global comparison operators
//////////////////////////////////////////////////////////////////////////

template<class T, size_type N> inline
Bool operator == ( const array<T,N>& src, const array<T,N> & dst )
{
	return lexicographical_compare_3way( src.begin(), src.end(), 
			dst.begin(), dst.end() ) == 0;
}

template<class T, size_type N> inline
Bool operator != (const array<T,N> & src, const array<T,N> & dst )
{
	return lexicographical_compare_3way( src.begin(), src.end(), 
			dst.begin(), dst.end() ) != 0;
}


template<class T, size_type N> inline
Bool operator < (const array<T,N> & src, const array<T,N> & dst)
{
	return lexicographical_compare_3way(src.begin(), src.end(), 
			dst.begin(), dst.end()) < 0;
}

template<class T, size_type N> inline
Bool operator <= (const array<T,N> & src, const array<T,N> & dst)
{
	return lexicographical_compare_3way(src.begin(), src.end(), 
			dst.begin(), dst.end()) <= 0;
}

template<class T, size_type N> inline
Bool operator > (const array<T,N> & src, const array<T,N> & dst)
{
	return lexicographical_compare_3way(src.begin(), src.end(), 
			dst.begin(), dst.end()) > 0;
}

template<class T, size_type N> inline
Bool operator >= (const array<T,N> & src, const array<T,N> & dst)
{
	return lexicographical_compare_3way(src.begin(), src.end(), 
			dst.begin(), dst.end()) >= 0;
}

} //namespace mdragon

#endif //__MD_ARRAY_H__
