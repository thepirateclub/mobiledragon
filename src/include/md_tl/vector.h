/** \file
 *	Template vector class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_VECTOR_H__
#define __MD_VECTOR_H__

namespace mdragon
{

template<class T, size_type N>
class static_buffer
{
public:
	inline T * begin() { return 
			reinterpret_cast<T*>( raw_buffer ); }

	inline const T * begin() const { return 
			reinterpret_cast<const T*>( raw_buffer ); }
	
	inline size_type capacity() const { return N; }

	inline size_type max_size() const { return N; }

	inline void reserve( size_type n, size_type initialized_size ) 
	{ assert( n <= N ) ; }

	void swap( static_buffer & dst, size_type src_initialized_size,
				size_type dst_initialized_size );

private:
	union
	{
		double align__;
		Byte raw_buffer [ sizeof(T) * N ];
	};	
};

template<class T, size_type N>
void static_buffer<T,N>::swap( static_buffer<T,N> & dst, 
		size_type src_initialized_size, size_type dst_initialized_size )
{
		if( src_initialized_size < dst_initialized_size )
			dst.swap( *this, dst_initialized_size, src_initialized_size );
		else
		{
			swap_ranges( begin(), begin() + dst_initialized_size, 
					dst.begin() );
			uninitialized_move( begin() + dst_initialized_size, 
					begin() + src_initialized_size, 
					dst.begin() + dst_initialized_size );
		}
}


template<class T>
class dynamic_buffer
{
public:
	inline dynamic_buffer()
	{
		buffer_size = 0;
		raw_buffer = NULL;
	}

	inline ~dynamic_buffer()
	{
		delete [] raw_buffer;
	}

	inline T * begin() {return reinterpret_cast<T*>( raw_buffer );}

	inline const T * begin() const {return 
			reinterpret_cast<const T*>( raw_buffer ); }

	inline size_type capacity() const { return buffer_size; }
	
	inline size_type max_size() const { return 0x00ffffffUL / sizeof(T); }

	void reserve( size_type n, size_type initialized_size );


	void swap( dynamic_buffer & dst, size_type , size_type  )
	{
		mdragon::swap( buffer_size, dst.buffer_size );
		mdragon::swap( raw_buffer, dst.raw_buffer );
	}

private:
	size_type buffer_size;
	Byte * raw_buffer;
};


template<class T>
void dynamic_buffer<T>::reserve( size_type n, size_type initialized_size )
{
		if( n <= buffer_size )
			return;

		n = max<size_type>( 32, max( buffer_size * 2, n ) );

		Byte *new_buffer = new Byte[ sizeof(T) * n ];
		if( raw_buffer && initialized_size )
		{
			uninitialized_move( begin(), begin() + initialized_size, 
				reinterpret_cast<T*>( new_buffer ) );
		}
		delete [] raw_buffer;
		buffer_size = n;
		raw_buffer = new_buffer;
}

/// Template class of sequence container with linear element arrangement.
/**
 *	@param T - container element type.
 */
template <class T, class BufAlloc = dynamic_buffer<T> >
class vector
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
	typedef vector<T, BufAlloc> self;


	///////////////////////////////////////////////////////////////////////
	// Constructors
	///////////////////////////////////////////////////////////////////////

	/// Default constructor. Creates empty vector.
	inline vector()
	{
		data_size = 0;
		update_iterators();
	}

	/// Creates a vector with n copies of t.
	vector( size_type n, const_reference t = T() );

	/// Copy constructor.
	vector( const self & src );

	/// Destructor.
	~vector();


	/// Reserve capacity for n elements minimum.
	inline void reserve( size_type n )
	{
		buffer.reserve( n, data_size );
		update_iterators();
	}

	///////////////////////////////////////////////////////////
	// Iterator access
	///////////////////////////////////////////////////////////

	/// Returns an iterator pointing to the first vector element.
	inline iterator begin() { return buffer.begin(); }

	/// Returns a const_iterator pointing to the first vector element.
	inline const_iterator begin() const { return buffer.begin(); }

	/// Returns an iterator pointing past the end of vector elements.
	inline iterator end() { return end__; }

	/// Returns a const iterator pointing past the end of vector elements.
	inline const_iterator end() const { return end__; }


	/// Returns number of elements in vector.
	inline size_type size() const { return data_size; }

	inline size_type max_size() const { return buffer.max_size(); }

	/// Returns how much elements vector can hold without memory reallocation.
	inline size_type capacity() const { return buffer.capacity(); }

	/// Returns True is vector holds no elements.
	inline Bool empty() const { return data_size == 0; } 


	///////////////////////////////////////////////////////////////////////
	// Data subscription
	///////////////////////////////////////////////////////////////////////

	/// Returns reference to n'th element.
	inline reference at (size_type n)
	{
		assert( n < data_size );
		return *(begin() + n);
	}

	/// Returns const reference to n'th element.
	inline const_reference at (size_type n) const
	{
		assert( n < data_size );
		return *(begin() + n);
	}

	/// Returns reference to n'th element.
	inline reference operator [] ( size_type n ) { return at( n ); }

	/// Returns const reference to n'th element.
	inline const_reference operator [] ( size_type n ) const { return at( n ); }

	/// The assignment operator
	inline self & operator = ( const self & src)
	{
		assign( src );
		return *this;
	}

	/// Empties the vector and inserts n coopies of t.
	void assign( size_type n, const T & t );


	/// Empties the vector and inserts elements from range [first, last).
	template <class InputIterator>
	void assign( InputIterator first, InputIterator last )
	{
		if( ( ( &*first ) < end() ) && ( ( &*first ) >= begin() ) )
		{
			temporary_buffer<value_type> temp_buffer( last - first );
			copy( first, last, temp_buffer.begin() );
			clear();
			insert( begin(), temp_buffer.begin(), temp_buffer.end() );
		}
		else
		{
			clear();
			insert( begin(), first, last );
		}
	}

	/// Empties the vector and assigns content of src to it.
	void assign ( const self & src );


	/// Returns reference to the first element.
	inline reference front()
	{
		assert( data_size != 0 );
		return *begin();
	}

	/// Returns const reference to the first element.
	inline const_reference front() const
	{
		assert( data_size != 0 );
		return *begin();
	}

	/// Returns reference to the last element.
	inline reference back()
	{
		assert( data_size != 0 );
		return *( end() - 1 );
	}

	/// Returns const reference to the last element.
	inline const_reference back() const
	{
		assert( data_size != 0 );
		return *( end() - 1 );
	}

	/// Inserts a new element at the end.
	void push_back( const_reference t );


	/// Same as push_back( t ).
	inline self & operator += ( const_reference t )
	{
		push_back( t );
		return *this;
	}

	/// Inserts content of src at the end of vector.
	template<class T, class BufAlloc2> inline
	self & operator += ( const 
			vector<T, BufAlloc2> & src )
	{
		insert( end(), src.begin(), src.end() );
		return *this;
	}


	/// Removes the last element.
	void pop_back();

	/// Swaps the contents with another vector.
	void swap( self & dst );

	/// Inserts x before pos.
	iterator insert( iterator pos, const_reference t );


	/// Inserts the range [first, last) before pos.
	template <class InputIterator>
	void insert( iterator pos, InputIterator first, InputIterator last )
	{
		difference_type n = last - first;
		assert ( n >= 0 );
		check_range( pos );

		if( ( &*first  < &*end() ) && ( &*first >= &*begin() ) )
		{
			temporary_buffer<value_type> temp_buffer( n );
			copy( first, last, temp_buffer.begin() );
			insert( pos, temp_buffer.begin(), temp_buffer.end() );
		}
		else
		{
			difference_type i = pos - begin();
			reserve( data_size + n );
			pos = begin() + i;
			uninitialized_move_backward( pos, end(), end() + n );
			copy( first, last, pos );
			data_size += n;
			update_iterators();
		}
	}


	/// Erases the element at position pos.
	inline iterator erase( iterator pos )
	{
		return erase( pos, pos + 1 );
	}


	/// Erases the range [first, last).
	iterator erase( iterator first, iterator last );


	/// Erases the element by index.
	inline void erase_at( size_type index )
	{
		erase( begin() + index );
	}

	/// Get index of the first element matching t or npos.
	inline size_type index_of( const_reference t ) const 
	{
		const_iterator i = mdragon::find( begin(), end(), t );
		return ( i == end() ) ? npos : ( i - begin() );
	}

	/// Returns iterator to the fists element matching t or end().
	inline iterator find ( const_reference t )
	{
		return mdragon::find( begin(), end(), t );
	}

	/// Returns const iterator to the fists element matching t or end().
	inline const_iterator find ( const_reference t ) const
	{
		return mdragon::find( begin(), end(), t );
	}

	/// Remove first element equal to t.
	void remove( const_reference t )
	{
		iterator i = mdragon::find( begin(), end(), t );
		if( i != end() )
			erase( i );
	}

	/// Remove all elements equal to t.
	void remove_all( const_reference t )
	{
		iterator new_end = mdragon::remove ( begin(), end(), t );
		erase( new_end, end() );
	}

	/// Erases all of the elements.
	void clear();


	/// Inserts or erases elements at the end such that the size becomes n.
	void resize( size_type n, const_reference t = T() );

private:
	inline void check_range( iterator i )
	{
		assert( !( ( begin() > i ) || ( end() < i ) ) );
	}

	inline void check_range( iterator i1, iterator i2 )
	{
		assert( !( ( i1 > i2 ) || ( begin() > i1 ) || ( end() < i2 ) ) );
	}

	inline void update_iterators()
	{
#ifdef MD_TL_DEBUG
		begin__ = begin();
#endif
		end__ = begin() + data_size;
	}

#ifdef MD_TL_DEBUG
	iterator begin__;
#endif
	iterator end__;

	BufAlloc buffer;

	size_type data_size;

};

///////////////////////////////////////////////////////////////////
// constructors
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
vector<T,BufAlloc>::vector( size_type n, const_reference t )
{
	data_size = 0;
	reserve( n );
	uninitialized_fill_n( begin(), n, t );
	data_size = n;
	update_iterators();
}

/// copy constructor
template<class T, class BufAlloc>
vector<T,BufAlloc>::vector( const self & src )
{
	data_size = 0;
	reserve( src.data_size );
	data_size = src.data_size;
	uninitialized_copy( src.begin(), src.end(), begin() );
	update_iterators();
}

///////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
vector<T,BufAlloc>::~vector()
{
	destroy( begin(), end() );
}

///////////////////////////////////////////////////////////////////
// push_back
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
void vector<T,BufAlloc>::push_back( const T & t )
{
	reserve( data_size + 1 );
	construct( end(), t );
	++data_size;
	update_iterators();
}

///////////////////////////////////////////////////////////////////
// pop_back
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
void vector<T,BufAlloc>::pop_back()
{
	assert( data_size != 0 );
	--data_size;
	update_iterators();
	destroy( end() );
}


///////////////////////////////////////////////////////////////////
// assign
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
void vector<T,BufAlloc>::assign( size_type n, const T & t )
{
	clear();
	reserve( n );
	uninitialized_fill_n( begin(), n, t );
	data_size = n;
	update_iterators();
}

template<class T, class BufAlloc>
void vector<T,BufAlloc>::assign ( const vector<T,BufAlloc> & src )
{
	if( this == &src )
		return;
	clear();
	reserve( src.data_size );
	uninitialized_copy( src.begin(), src.end(), begin() );
	data_size = src.data_size;
	update_iterators();
}


///////////////////////////////////////////////////////////////////
// swap
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
void vector<T,BufAlloc>::swap( vector<T,BufAlloc> & dst )
{
	if( this == &dst )
		return;
	buffer.swap( dst.buffer, data_size, dst.data_size );
	mdragon::swap( data_size, dst.data_size );
	update_iterators();
	dst.update_iterators();
}

///////////////////////////////////////////////////////////////////
// insert
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
typename vector<T,BufAlloc>::iterator vector<T,BufAlloc>::insert( 
		typename vector<T,BufAlloc>::iterator pos, const T & t )
{
	check_range( pos );

	difference_type i = pos - begin();

	reserve( data_size + 1 );

	pos = begin() + i;

	uninitialized_move_backward( pos, end(), end() + 1 );
	construct( &*pos, t );
	++data_size;
	update_iterators();

	return pos;
}

///////////////////////////////////////////////////////////////////
// erase
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
typename vector<T,BufAlloc>::iterator vector<T,BufAlloc>::erase( 
		typename vector<T,BufAlloc>::iterator first, 
		typename vector<T,BufAlloc>::iterator last )
{
	check_range( first, last );

	destroy( first, last );
	uninitialized_move( last, end(), first );
	data_size -= ( last - first ) ;
	update_iterators();

	return first;
}


///////////////////////////////////////////////////////////////////
// clear
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc>
void vector<T,BufAlloc>::clear()
{
	destroy( begin(), end() );
	data_size = 0;
	update_iterators();
}

template<class T, class BufAlloc>
void vector<T,BufAlloc>::resize( typename vector<T,BufAlloc>::size_type n, 
	const T & t )
{
	reserve( n );

	if( n > data_size )
		uninitialized_fill ( end(), begin() + n, t );
	else
		destroy( begin() + n, end() );

	data_size = n;
	update_iterators();
}

///////////////////////////////////////////////////////////////////
// comparison operators
///////////////////////////////////////////////////////////////////
template<class T, class BufAlloc1, class BufAlloc2>
Bool operator == ( const vector<T,BufAlloc1> & src, 
				   const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) == 0 ;
}

template<class T, class BufAlloc1, class BufAlloc2>
Bool operator != ( const vector<T,BufAlloc1> & src, 
				   const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) != 0 ;
}

// Lexicographical comparison.
template<class T, class BufAlloc1, class BufAlloc2>
Bool operator < ( const vector<T,BufAlloc1> & src, 
				  const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) < 0;
}

// Lexicographical comparison.
template<class T, class BufAlloc1, class BufAlloc2>
Bool operator <= ( const vector<T,BufAlloc1> & src, 
				   const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) <= 0;
}

template<class T, class BufAlloc1, class BufAlloc2>
Bool operator > ( const vector<T,BufAlloc1> & src, 
				  const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) > 0;
}

template<class T, class BufAlloc1, class BufAlloc2>
Bool operator >= ( const vector<T,BufAlloc1> & src, 
				  const vector<T,BufAlloc2> & dst )
{
	return lexicographical_compare_3way ( src.begin(), src.end(), 
		dst.begin(), dst.end() ) >= 0;
}

} //namespace mdragon

#endif //__MTL_VECTOR_H__
