/** \file
 *	Basic template functors. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_FUNCTION_H__
#define __MD_FUNCTION_H__

namespace mdragon
{

///////////////////////////////////////////////////////////
// Adaptable unary Function
///////////////////////////////////////////////////////////
template<class Arg, class Result>
struct unary_function
{
	typedef Arg argument_type;
	typedef Result result_type;
};


///////////////////////////////////////////////////////////
// Adaptable binary function
///////////////////////////////////////////////////////////
template<class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


///////////////////////////////////////////////////////////
// Adaptable generator function
///////////////////////////////////////////////////////////
template<class Result>
struct generator_function
{
	typedef Result result_type;
};

template<class T>
struct negate : unary_function<T, T>
{
	inline T operator () (const T & t) const { return -t; }
};


template<class T>
struct identity : unary_function<T, T>
{
	inline const T & operator () (const T & t) const { return t; }
};


template<class T>
struct less : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return a < b; }
};

template<class T>
struct less_equal : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return a <= b; }
};


template<class T>
struct greater : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return b < a; }
};


template<class T>
struct greater_equal : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return b <= a; }
};


template<class T>
struct equal_to : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return b == a; }
};


template<class T>
struct not_equal_to : binary_function<T, T, Bool>
{
	inline Bool operator () (const T & a, const T & b) const { return b != a; }
};


template<class T>
struct minus : binary_function<T, T, T>
{
	inline T operator () (const T & a, const T & b) const { return a - b; }
};


template<class T>
struct plus : binary_function<T, T, T>
{
	inline T operator () (const T & a, const T & b) const { return a + b; }
};

template<class T>
struct multiplies : binary_function<T, T, T>
{
	inline T operator () (const T & a, const T & b) const { return a * b; }
};

template<class T>
struct divides : binary_function<T, T, T>
{
	inline T operator () (const T & a, const T & b) const { return a / b; }
};

template<class T>
struct modulus : binary_function<T, T, T>
{
	inline T operator () (const T & a, const T & b) const { return a % b; }
};


template <class InputIterator1, class InputIterator2>
Int lexicographical_compare_3way( InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2 );

struct eqstr : binary_function<const Char *, const Char *, Bool>
{
	inline Bool operator() (const Char * a, const Char * b) const
	{
		return lexicographical_compare_3way( a, a + strlen(a),
				b, b + strlen(b) ) == 0;
	}
};

} //namespace mdragon

#endif // __MD_FUNCTION_H__
