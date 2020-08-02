/** \file
 *	Basic algorithms templates. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ALGORITHM_H__
#define __MD_ALGORITHM_H__

#undef min
#undef max

namespace mdragon
{

/// Returns absolute value of t.
template <class T> inline 
T abs( T t )
{
	return t < 0 ? -t : t;
}

///////////////////////////////////////////////////////////
// Minimum and maximum
///////////////////////////////////////////////////////////


/// Returns the lesser of its two arguments.
/**
 *	Compares objects using operator <.
 *	@param a - first value.
 *	@param b - second value.
 *	@return lesser of a and b.
 */
template <class T> inline
const T & min( const T & a, const T & b )
{
	return a < b ? a : b;
}

/// Returns the lesser of its two arguments.
/**
 *	Compares objects using binary predicate functor comp.
 *	@param a - first value.
 *	@param b - second value.
 *	@param comp - binary predicate functor.
 *	@return lesser of a and b.
 */
template <class T, class BinaryPredicate> inline
const T & min( const T & a, const T & b, BinaryPredicate comp )
{
	return comp( a, b ) ? a : b;
}

/// Returns the greater of its two arguments.
/**
 *	Compares objects using operator <.
 *	@param a - first value.
 *	@param b - second value.
 *	@return lesser of a and b.
 */
template <class T> inline
const T & max( const T & a, const T & b )
{
	return b < a ? a : b;
}

/// Returns the greater of its two arguments.
/**
 *	Compares objects using binary predicate functor comp.
 *	@param a - first value.
 *	@param b - second value.
 *	@return lesser of a and b.
 */
template <class T, class BinaryPredicate> inline
const T & max( const T & a, const T & b, BinaryPredicate comp )
{
	return comp( b, a ) ? a : b;
}

/// Returns min_t if t < min_t, max_t if t > max_t.
template <class T>
const T & wrap_value( const T & min_t,  const T & t, const T & max_t )
{
	return  ( max_t < t ) ? max_t : 
			( t < min_t ) ? min_t : t;
}

// Checks if t is >= min_t && t <= max_t.
template <class T>
Bool is_in_range( const T & min_t,  const T & t, const T & max_t )
{
	return 	!(t < min_t) && !(max_t < t);
}

/// Finds the smalles element in the range [first, last).
/**
 *	Compares objects using operator <.
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@return iterator pointing to the smallest element in [first; last) 
 *			or last if [first; last) is an empty range.
 */
template <class ForwardIterator>
ForwardIterator min_element( ForwardIterator first, ForwardIterator last )
{
	ForwardIterator i = first;
	if( first++ != last )
	{
		for( ; first != last; ++first )
		{
			if( *first < *i )
				i = first;
		}
	}
	return i;
}


/// Finds the smalles element in the range [first, last).
/**
 *	Compares objects using binary predicate functor comp.
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@param comp - binary predicate functor.
 *	@return iterator pointing to the smallest element in [first; last) 
 *			or last if [first; last) is an empty range.
 */
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator min_element( ForwardIterator first, ForwardIterator last,
                             BinaryPredicate comp )
{
	ForwardIterator i = first;
	if( first++ != last )
	{	
		for( ; first != last; ++first )
		{
			if( comp(*first,*i) )
				i = first;
		}
	}
	return i;
}

/// Finds the largest element in the range [first, last).
/**
 *	Compares objects using operator <.
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@return iterator pointing to the largest element in [first; last) 
 *			or last if [first; last) is an empty range.
 */
template <class ForwardIterator>
ForwardIterator max_element( ForwardIterator first, ForwardIterator last )
{
	ForwardIterator i = first;
	if( first++ != last )
	{	
		for( ; first != last; ++first )
		{
			if( *i < *first )
				i = first;
		}
	}
	return i;
}

/// Finds the largest element in the range [first, last).
/**
 *	Compares objects using binary predicate functor comp.
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@param comp - binary predicate functor.
 *	@return iterator pointing to the largest element in [first; last) 
 *			or last if [first; last) is an empty range.
 */
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator max_element( ForwardIterator first, ForwardIterator last,
                             BinaryPredicate comp )
{
	ForwardIterator i = first;
	if( first++ != last )
	{
		for( ; first != last; ++first )
		{
			if( comp( *i, *first ) )
				i = first;
		}
	}
	return i;	
}


///////////////////////////////////////////////////////////
// Swap
///////////////////////////////////////////////////////////

/// Swaps value of it's two arguments.
/**
 *	Assigns the contents of a to b and the contents of b to a. 	
 *	@param a - first arguments.
 *	@param b - second arguments.
 */
template <class Assignable> inline
void swap( Assignable & a, Assignable & b )
{
	Assignable temp( a );
	a = b;
	b = temp;
}

/// Equivalent to swap(*a, *b).
template <class ForwardIterator1, class ForwardIterator2> inline 
void iter_swap( ForwardIterator1 a, ForwardIterator2 b )
{
	swap( *a, *b );
}

/// Swaps elements of two ranges.
/**
 *	@param first1 - iterator pointing to the begining of the first range. 
 *	@param last1 - second range past the end iterator.
 *	@param first2 - iterator pointing to the begining of the second range.
 *	@return first2 + (last1 - first1).
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges( ForwardIterator1 first1, 
		ForwardIterator1 last1, ForwardIterator2 first2)
{
	for( ; first1 != last1; ++first1, ++first2 )
		iter_swap( first1, first2 );
	return first2;
}



///////////////////////////////////////////////////////////
// Fill
///////////////////////////////////////////////////////////

/// Fills the range with given value.
/**
 *	For every iterator i in [first, last), it performs the 
 *	assignment *i = t.
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@param t - calue to assign.
 */
template <class ForwardIterator, class T> inline
void fill( ForwardIterator first, ForwardIterator last, const T & t )
{
	for( ; first != last; ++first )
		*first = t;
}


/// Fills the range with given value.
/** 
 *	For every iterator i in the range [result;result + n) it performs the
 *	assignment *i = t.
 *	@param first - iterator pointing to the begining of range.
 *	@param n - number of elements to assign.
 *	@return result + n.
 */
template <class OutputIterator, class Size_t, class T> inline
OutputIterator fill_n( OutputIterator result, Size_t n, const T & t )
{
	for( ; n; --n, ++result )
		*result = t;
	return result;
}

/// Equal to fill(container.begin(), container.end(), value) .
template <class Container> inline
void fill( Container &container, const typename Container::value_type & t )
{
	fill( container.begin(), container.end(), t );
}

// Remove removes from the range [first, last) all elements that are equal 
// to value. That is, remove returns an iterator new_last such that the 
// range [first, new_last) contains no elements equal to value. 
// The iterators in the range [new_last, last) are all still 
// dereferenceable, but the elements that they point to are unspecified. 
// Remove is stable, meaning that the relative order of elements that 
// are not equal to value is unchanged.
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last,
                       const T & value)
{
	for( ; first != last;  )
	{
		if( *first == value )
		{
			copy( first + 1, last, first );
			--last;
		}
		else
			++first;
	}
	return last;
}

///////////////////////////////////////////////////////////
// Generate
///////////////////////////////////////////////////////////

/// Assigns to the range the result of invoking generator functor.
/**
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@param gen - generator functor.
 */
template <class ForwardIterator, class Generator>
void generate( ForwardIterator first, ForwardIterator last, Generator gen )
{
	for( ; first != last; ++first )
		*first = gen();
}

/// Assigns to the range the result of invoking generator functor.
/**
 *	@param first - iterator pointing to the begining of range.
 *	@param last - past the end range iterator.
 *	@param gen - generator functor.
 */
template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n( OutputIterator first, Size n, Generator gen )
{
	for ( ; n ; --n, ++first )
		*first = gen();
	return first;
}


///////////////////////////////////////////////////////////
// Copy
///////////////////////////////////////////////////////////

/// Copies elements from one range to another.
/**
 *	It copies every element from the range [first, last) to the range 
 *	[result, result + (last - first)) performing the assignment
 *	*(result + n) = *(first + n) for every n from 0 to last - first.
 *	@param first - iterator pointing to the begining of the source range .
 *	@param second - source range past the end iterator.
 *	@param result - iterator pointing to the begining of the destination
 *			range.
 *	@return result + ( last - first ).
 */
template <class InputIterator, class OutputIterator>
OutputIterator copy( InputIterator first, InputIterator last,
                     OutputIterator result )
{
	for ( ; first != last; ++first, ++result )
		*result = *first;
	return result;
}

/// Copies elements from one range to another.
/**
 *	It copies every element from the range [first, first + n) to the range 
 *	[result, result + n) performing the assignment
 *	*(result + i) = *(first + i) for every i from 0 to n.
 *	@param first - iterator pointing to the begining of the source range .
 *	@param n - number of elements to copy.
 *	@param result - iterator pointing to the begining of the destination
 *			range.
 *	@return result + n.
 */
template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n( InputIterator first, Size n, 
                       OutputIterator result )
{
	for ( ; n; --n, ++first, ++result )
		*result = *first;
	return result;
}

/// Copies elements from on range to another in reverse order.
/**
 *	It copies elements from the range [first, last) to the range
 *	[result - (last - first), result) performing the assignments 
 *	*(result - n - 1) = *(last - n - 1) for every n from 0 to last - first.
 *	@param fist - iterator pointing to the begining of the source range.
 *	@param last - source range past the end iterator.
 *	@param result - destination range past the end iterator.
 *	@return result - ( last - first ).
 */
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward( BidirectionalIterator1 first, 
                                      BidirectionalIterator1 last, 
                                      BidirectionalIterator2 result )
{
	if( first != last )
	{
		for ( --first, --last, --result; last != first; --last, --result )
			*result = *last;
	}
	return result;
}


///////////////////////////////////////////////////////////
// Lexicographical_compare
///////////////////////////////////////////////////////////

/// Performs dictionary comparison of two ranges.
/**
 *	Elements compared using operator <.
 *	@param first1 - iterator pointing to the begining of the first range.
 *	@param last1 - first range past the end iterator
 *	@param first2 - iterator pointing to the begining of the second range.
 *	@param last2 - second range past the end iterator.
 *	@return True if the range [first1, last1) is lexicographically less
 *			than the range [first2, last2), False otherwise.
 */
template <class InputIterator1, class InputIterator2>
Bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2 )
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (*first1 < *first2)
			return True;
		if (*first2 < *first1)
			return False;
	}
	return first2 != last2;
}

/// Performs dictionary comparison of two ranges.
/**
 *	Elements compared using binary predicate comp.
 *	@param first1 - iterator pointing to the begining of the first range.
 *	@param last1 - first range past the end iterator.
 *	@param first2 - iterator pointing to the begining of the second range.
 *	@param last2 - second range past the end iterator.
 *	@param comp - binary predicate functor.
 *	@return True if the range [first1, last1) is lexicographically less
 *			than the range [first2, last2), False otherwise.
 */
template <class InputIterator1, class InputIterator2, 
		class BinaryPredicate>
Bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, BinaryPredicate comp )
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if ( comp(*first1, *first2) )
			return True;
		if ( comp(*first2, *first1) )
			return False;
	}
	return first2 != last2;
}


/// Generalization of strcmp function.
/**
 *	Performs dictionary comparison of two ranges.
 *	@param first1 - iterator pointing to the begining of the first range.
 *	@param last1 - first range past the end iterator.
 *	@param first2 - iterator pointing to the begining of the second range.
 *	@param last2 - second range past the end iterator.
 *	@return negative number if the range [first1, last1) is lexicographically 
 *			less than the range [first2, last2),
 *			positive number if [first2, last2) is lexicographically less 
 *			than [first1, last1),
 *			zero if ranges are lexicographically equal.
 */
template <class InputIterator1, class InputIterator2>
Int lexicographical_compare_3way( InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2 )
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if( *first1 != *first2 )
			return *first1 - *first2;
	}
	return ( first1 != last1 ) ? 1 : ( first2 != last2 ) ? -1 : 0;
}



///////////////////////////////////////////////////////////
// Count
///////////////////////////////////////////////////////////

/// Counts number of elements in the range that are equal to value t.
/**
 *	It adds to n the number of iterators i in [first, last) such that *i == t.
 *	@param first - iterator pointing to the begining of the range.
 *	@param last - range past the end iterator.
 *	@param t - value to compare.
 *	@param n - reference to counter.
 */
template <class InputIterator, class EqualityComparable, class Size_t>
void count( InputIterator first, InputIterator last, 
		   const EqualityComparable & t, Size_t & n )
{
	for( ; first != last; ++first )
		if( *first == t )
			++n;
}


/// Counts number of elements in the range that satisfy the predicate pred.
/**
 *	It adds to n the number of iterators i in [first, last) such that pred(*i)
 *	is true.
 *	@param first - iterator pointing to the begining of the range.
 *	@param last - range past the end iterator.
 *	@param pred - predicate functor.
 *	@param n - reference to counter.
 */
template <class InputIterator, class Predicate, class Size_t>
void count_if( InputIterator first, InputIterator last, Predicate pred, 
				Size_t & n )
{
	for( ; first != last; ++first )
		if( pred( *first ) )
			++n;
}



///////////////////////////////////////////////////////////
// Find
///////////////////////////////////////////////////////////

/// Finds matching element in the range.
/**
 *	Returns the first iterator i from range [first, last) such that ( *i == t ).
 *	@return iterator pointing to matching element or last.
 */
template<class InputIterator, class EqualityComparable> inline
InputIterator find( InputIterator first, InputIterator last,
                    const EqualityComparable & t)
{ 
	for ( ; first != last; ++first )
	{
		if( *first == t )
			break;
	}
	return first;
}

template <class InputIterator, class ForwardIterator>
InputIterator find_first_of( InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2 )
{
	for( ; first1 != last1; ++first1 )
	{
		if( find( first2, last2, *first1 ) != last2 )
			return first1;
	}
	return last1;
}

template <class InputIterator, class ForwardIterator>
InputIterator find_first_not_of( InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2 )
{
	for( ; first1 != last1; ++first1 )
	{
		if( find( first2, last2, *first1 ) == last2 )
			return first1;
	}
	return last1;
}


template <class InputIterator, class ForwardIterator>
InputIterator find_last_of( InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2 )
{
	InputIterator result = last1;
	for( ; first1 != last1; ++first1 )
	{
		if( find( first2, last2, *first1 ) != last2 )
			result = first1;
	}
	return result;
}


template <class InputIterator, class ForwardIterator>
InputIterator find_last_not_of( InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2 )
{
	InputIterator result = last1;
	for( ; first1 != last1; ++first1 )
	{
		if( find( first2, last2, *first1 ) == last2 )
			result = first1;
	}
	return result;
}



//////////////////////////////////////////////////////////////////////////
// Search
//////////////////////////////////////////////////////////////////////////

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search( ForwardIterator1 first1, ForwardIterator1 last1,
                         ForwardIterator2 first2, ForwardIterator2 last2 )
{
	for( ForwardIterator1 end = first1 + (last2 - first2), 
			begin_last = last1 - (last2 - first2); 
			first1 <= begin_last; ++first1, ++end )
	{
		if( lexicographical_compare_3way( first1, end, first2, last2 ) 
				== 0 )
			return first1;
	}
	return last1;
}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 find_end( ForwardIterator1 first1, 
		ForwardIterator1 last1, ForwardIterator2 first2, 
		ForwardIterator2 last2 )
{
	ForwardIterator1 result = last1;
	for( ForwardIterator1 end = first1 + (last2 - first2), 
			begin_last = last1 - (last2 - first2); 
			first1 <= begin_last; ++first1, ++end )
	{
		if( lexicographical_compare_3way( first1, end, first2, last2 ) 
				== 0 )
			result = first1;
	}
	return result;
}

template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n( ForwardIterator first, ForwardIterator last,
						  Integer n, const T & t)
{
	for( Integer found_n = 0; first != last; ++first )
	{
		if(found_n == n)
			return first - n;
		if( *first == t )
			++found_n;
		else
			found_n = 0;
	}
	return last;
}

template <class ForwardIterator, class Integer, 
          class T, class BinaryPredicate>
ForwardIterator search_n( ForwardIterator first, ForwardIterator last,
		Integer n, const T & t, BinaryPredicate binary_pred)
{
	for( Integer found_n = 0; first != last; ++first )
	{
		if( found_n == n )
			return first - n;
		if( binary_pred( *first, t ) )
			++found_n;
		else
			found_n = 0;
	}
	return last;
}


template <class InputIterator, class T>
T accumulate( InputIterator first, InputIterator last, T init )
{
	for( ; first != last; ++first )
		init += *first;
	return init;
}

template <class InputIterator, class T, class BinaryFunction>
T accumulate( InputIterator first, InputIterator last, T init,
              BinaryFunction binary_op )
{
	for( ; first != last; ++first )
		init = binary_op( init, *first );
	return init;
}



} //namespace mdragon

#endif //__MD_ALGORITHM_H__
