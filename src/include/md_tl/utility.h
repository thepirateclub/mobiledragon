/** \file
 *	Template library utilities. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_UTILITY_H__
#define __MD_UTILITY_H__

namespace mdragon
{

template<class T1, class T2>
class pair
{
public:
	typedef T1 first_type;
	typedef T2 second_type;

	inline pair():
		first( first_type() ), second( second_type() ) { ; } 

	inline pair( const first_type & first_, const second_type & second_ ):
		first( first_ ), second( second_ ) { ; }

	inline pair( const pair& src ):
		first( src.first ), second( src.second ) { ; }

	pair & operator = ( const pair & src )
	{
		first = src.first;
		second = src.second;
		return *this;
	}

	first_type first;
	second_type second;
};

template <class T1, class T2> inline
Bool operator == ( const pair<T1, T2> & a, const pair<T1, T2> & b )
{
	return ( a.first == b.first ) && ( a.second == b.second );
}

template <class T1, class T2>
Bool operator < ( const pair<T1, T2> & a, const pair<T1, T2> & b )
{
	return  a.first < b.first ? True : 
			b.first < a.first ? False :
			a.second < b.second;
}

template<class T1, class T2>
pair<T1, T2> make_pair( const T1 & t1, const T2 & t2 )
{
	return pair<T1, T2>( t1, t2 );
}

} //namespace mdragon

#endif // __MTL_UTILITY_H__

