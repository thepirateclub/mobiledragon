/** \file
 *	Template sort function. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SORT_H__
#define __MD_SORT_H__

namespace mdragon
{

/// Sorts range [first, last) ordering elements using operator <.
template <class RandomAccessIterator> inline
void sort( RandomAccessIterator first, RandomAccessIterator last )
{
	quick_sort___( first, last, value_type( first ) );
}

/// Sorts range [first, last) ordering elements using binary predicate functor comp.
template <class RandomAccessIterator, class StrictWeakOrdering>
void sort( RandomAccessIterator first, RandomAccessIterator last,
           StrictWeakOrdering comp )
{
	quick_sort___( first, last, value_type( first ), comp );
}


template <class ForwardIterator>
Bool is_sorted( ForwardIterator first, ForwardIterator last )
{
	if( first != last )
	{
		for( ++first ; first != last; ++first )
		{
			if( *first < *(first - 1) )
				return False;
		}
	}
	return True;
}


template <class ForwardIterator, class StrictWeakOrdering>
Bool is_sorted( ForwardIterator first, ForwardIterator last,
			    StrictWeakOrdering comp )
{
	if( first != last )
	{	
		for( ++first ; first != last; ++first )
		{
			if( comp( *first, *(first - 1) ) )
				return False;
		}
	}
	return True;
}


template <class RandomAccessIterator, class T>
void quick_sort___ ( RandomAccessIterator first, 
					 RandomAccessIterator last, T* )
{
	quick_sort___ ( first, last, static_cast<T*>(NULL), less<T>() );
}


template <class RandomAccessIterator, class T, class StrictWeakOrdering>
void quick_sort___ ( RandomAccessIterator first, 
		RandomAccessIterator last, T * x, StrictWeakOrdering comp )
{
	ptrdiff_t n = last - first;

	if(n < 2)
		return;

	if(n == 2)
	{
		if( comp( *(--last),  *first) )
			iter_swap( first, last );
		return;
	}

	RandomAccessIterator scan_down = last - 1;
	RandomAccessIterator scan_up = first;

	{
		T pivot = *( first + n / 2 );

		do
		{
			while( comp( *scan_up, pivot ) )
				++scan_up;
			while( comp( pivot, *scan_down) )
				--scan_down;

			if( scan_up < scan_down)
			{
				iter_swap( scan_up, scan_down );
				++scan_up;
				--scan_down;
			}

		} while ( scan_up < scan_down );
	}

	if( first < scan_down )
		quick_sort___( first, scan_down + 1, static_cast<T*>(NULL), comp );
	if( scan_up < last )
		quick_sort___( scan_up, last, static_cast<T*>(NULL), comp );
}


template <class RandomAccessIterator, class Key>
RandomAccessIterator binary_find( RandomAccessIterator first, 
		RandomAccessIterator last, const Key & key )
{
	RandomAccessIterator high = last;
	RandomAccessIterator middle;
	while( high - first )
	{
		middle = first + ( ( high - first ) / 2 );
		if( *middle < key )
			first = middle + 1;
		else if( key < *middle  )
			high = middle;
		else
			return middle;
	}
	return last;
}


template <class RandomAccessIterator, class Key, class StrictWeakOrdering>
RandomAccessIterator binary_find( RandomAccessIterator first, 
		RandomAccessIterator last, const Key & key, 
		StrictWeakOrdering comp )
{
	RandomAccessIterator high = last;
	RandomAccessIterator middle;
	while( high - first )
	{
		middle = first + ( ( high - first ) / 2 );
		if( comp( *middle, key ) )
			first = middle + 1;
		else if( comp( key, *middle ) )
			high = middle;
		else
			return middle;
	}
	return last;
}

} //namespace mdragon

#endif // __MD_SORT_H__