/** \file
 *	Fixed point class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_FIXED_H__
#define __MD_FIXED_H__

namespace mdragon
{


#ifndef Fixed

	#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)

	inline Int FixedMul(Int x,Int y)
	{
		return ( ( Long(x) * (y) ) >> 16 ) . GetTInt();
	}

	inline Int FixedDiv(Int x,Int y)
	{
		return ( ( Long(x) << 16 ) / (y) ) . GetTInt();
	}

	#endif // MD_OS_SYMBIAN_S60

	#if defined(MD_OS_WINCE) || defined(MD_OS_WIN32) || defined(MD_OS_PALM) || defined(PSP)
	#undef FixedMul
	#undef FixedDiv
	#define FixedMul(x,y) ( (Int) ( ( (Long)(x) * (y) ) >> 16 ) )
	#define FixedDiv(x,y) ( (Int) ( ( ( ( (Long)(x) ) << 16 ) / (y) ) ) )
	#endif // MD_OS_WINCE



/// Fixed point real number.
/**
 *	This class represents fixed point real number stored as 32bit integer
 *	in 16.16 bit notation.
 */
class Fixed 
{
public:

	/// Default constructor.
	inline Fixed() {};

	/// Copy constructor.
	inline Fixed(const Fixed & a) { value = a.value; }

	/// Construct from Short value.
	inline Fixed(Short a) { value = ((Int)a)<<16; }

	/// Construct from Int value.
	inline Fixed(Int a) { value = a<<16; }

	/// Construct from Float value.
	inline Fixed(Float a) { value = (Int)(a*65536); }

	/// Construct from Double value.
	inline Fixed(Double a) { value = (Int)(a*65536); }

	/// Construct from integer fixed value.
	/**
	 *	@param a - fixed integer value
	 *	@param fictional - fictional parameter.
	 */	
	inline Fixed( Int a, Byte fictional ) : value(a) {}

	/// Conversion to Byte.
	inline operator Byte () { return (Byte)(value >> 16); }

	/// Conversion to Word.
	inline operator Word () { return (Word)(value >> 16); }	

	/// Conversion to DWord.
	inline operator DWord () { return value >> 16; }

	/// Conversion to Char.
	inline operator Char () { return (Char)(value >> 16); }

	/// Conversion to Short.
	inline operator Short () { return (Short)(value >> 16); }

	/// Conversion to Int.
	inline operator Int () { return value >> 16; }

	/// Conversion to Long.
	inline operator Long () { return value >> 16; }

	/// Conversion to Float.
	inline operator Float () { return Float(value) / 65536; }

	/// Conversion to Double.
	inline operator Double () { return Double(value) / 65536; }

	/// Round to neares value.
	inline Int Round() { return ( value > 0 ) ? (( value + ( 65536 >> 1 ) ) >> 16) : (( value - ( 65536 >> 1 ) ) >> 16) ; }


	/// Assign from Fixed.
	inline Fixed & operator = ( Fixed const& a ) {value = a.value; return *this;}

	/// Assign from Short.
	inline Fixed & operator = ( Short a ) { value = ((Int)a)<<16; return *this;}	

	/// Assign from Int.
	inline Fixed & operator = ( Int a ) { value = a<<16; return *this;}

	/// Assign from Float.
	inline Fixed & operator = ( Float a ) { value = (Int)(a*65536); return *this;}

	/// Assign from Double.
	inline Fixed & operator = ( Double a ) { value = (Int)(a*65536); return *this;}


	/// Addition assignment with Fixed.
	inline Fixed & operator += ( const Fixed & a) {value += a.value; return *this;}

	/// Addition assignment with Short.
	inline Fixed & operator += ( Short a) {value += ((Int)a)<<16; return *this;}

	/// Addition assignment with Int.
	inline Fixed & operator += ( Int a) {value += a<<16; return *this;}

	/// Addition assignment with Float.
	inline Fixed & operator += ( Float a) {value += (Int)(a*65536); return *this;}

	/// Addition assignment with Double.
	inline Fixed & operator += ( Double a) {value += (Int)(a*65536); return *this;}


	/// Subtraction assignment with Fixed.
	inline Fixed & operator -= ( const Fixed & a) {value -= a.value; return *this;}

	/// Subtraction assignment with Short.
	inline Fixed & operator -= ( Short a) {value -= ((Int)a)<<16; return *this;}

	/// Subtraction assignment with Int.
	inline Fixed & operator -= ( Int a) {value -= a<<16; return *this;}

	/// Subtraction assignment with Float.
	inline Fixed & operator -= ( Float a) {value -= (Int)(a*65536); return *this;}

	/// Subtraction assignment with Double.
	inline Fixed & operator -= ( Double a) {value -= (Int)(a*65536); return *this;}


	/// Multiplication assignment with Fixed.
	inline Fixed & operator *= ( const Fixed & a) {value = FixedMul(value,a.value); return *this;}

	/// Multiplication assignment with Short.
	inline Fixed & operator *= ( Short a) {value = FixedMul(value,((Int)a)<<16); return *this;}

	/// Multiplication assignment with Int.
	inline Fixed & operator *= ( Int a) {value = FixedMul(value,a<<16); return *this;}

	/// Multiplication assignment with Float.
	inline Fixed & operator *= ( Float a) {value = FixedMul(value,(Int)(a*65536)); return *this;}

	/// Multiplication assignment with Double.
	inline Fixed & operator *= ( Double a ) {value = FixedMul(value,(Int)(a*65536)); return *this;}


	/// Division assignment with Fixed
	inline Fixed & operator /= ( const Fixed & a) {value = FixedDiv(value,a.value); return *this;}

	/// Division assignment with Short.
	inline Fixed & operator /= ( Short a ) {value = FixedDiv(value,((Int)a)<<16); return *this;}

	/// Division assignment with Int.
	inline Fixed & operator /= ( Int a ) {value = FixedDiv(value,a<<16); return *this;}

	/// Division assignment with Float.
	inline Fixed & operator /= ( Float a ) {value = FixedDiv(value,(Int)(a*65536)); return *this;}

	/// Division assignment with Double.
	inline Fixed & operator /= ( Double a ) {value = FixedDiv(value,(Int)(a*65536)); return *this;}

	/// Subtraction operator.
	inline Fixed operator - () const { Fixed temp; temp.value = -value; return temp;}

	/// Stored fixed value.
	Int value;
};


///////////////////////////////////////////////////////////////////
// Operator +
///////////////////////////////////////////////////////////////////

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( const Fixed & a, const Fixed & b )
{
	  return Fixed( a.value + b.value, 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( const Fixed & a, Short b ) 
{
	return Fixed( a.value + (((Int)b)<<16), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( const Fixed & a, Int b )
{
	return Fixed( a.value + ( b << 16 ), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( const Fixed & a, Float b )
{
	return Fixed( a.value + (Int)(b*65536), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( const Fixed & a, Double b )
{
	return Fixed( a.value + (Int)(b*65536), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( Short a, const Fixed & b )
{
	return Fixed( b.value + (((Int)a)<<16), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( Int a, const Fixed & b )
{
	return Fixed( b.value + ( a << 16 ), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( Float a, const Fixed & b )
{
	return Fixed( b.value + (Int)(a*65536), 0 );
}

///	Global addition operator.
/** \relates Fixed */
inline Fixed operator + ( Double a, const Fixed & b )
{
	return Fixed( b.value + (Int)(a*65536), 0 );
}

///////////////////////////////////////////////////////////////////
// Operator -
///////////////////////////////////////////////////////////////////

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( const Fixed& a, const Fixed& b ) 
{
	return Fixed( a.value - b.value, 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( const Fixed & a, Short b ) 
{
	return Fixed( a.value - (((Int)b)<<16), 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( const Fixed & a, Int b ) 
{
	return Fixed( a.value - (b<<16), 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( const Fixed & a, Float b ) 
{
	return Fixed( a.value - (Int)(b*65536), 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( const Fixed & a, Double b )
{
	return Fixed( a.value - (Int)(b*65536), 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( Short a, const Fixed & b ) 
{
	return Fixed( ((Int(a)) << 16 ) - b.value, 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( Int a, const Fixed & b )
{
	return Fixed( (a << 16 ) - b.value, 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( Float a, const Fixed & b )
{
	return Fixed( (Int)(a*65536) - b.value, 0 );
}

/// Global subtraction operator.
/** \relates Fixed */
inline Fixed operator - ( Double a, const Fixed & b )
{
	return Fixed( (Int)(a*65536) - b.value, 0 );
}

///////////////////////////////////////////////////////////////////
// Operator *
///////////////////////////////////////////////////////////////////

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator *( const Fixed& a, const Fixed& b ) 
{
	return Fixed( FixedMul(a.value,b.value), 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( const Fixed & a, Short b ) 
{
	return Fixed( FixedMul(a.value,(Int(b))<<16) , 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( const Fixed & a, Int b ) 
{
	return Fixed( FixedMul(a.value, ( b << 16 ) ), 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( const Fixed & a, Float b ) 
{
	return Fixed( FixedMul(a.value,(Int)(b*65536)), 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( const Fixed & a, Double b ) 
{
	return Fixed( FixedMul(a.value,(Int)(b*65536)), 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( Short a, const Fixed & b )
{
	return Fixed( FixedMul(b.value,(Int(a)) << 16) , 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( Int a, const Fixed & b )
{
	return Fixed( FixedMul(b.value, a << 16) , 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( Float a, const Fixed & b )
{
	return Fixed( FixedMul(b.value,(Int)(a*65536)), 0 );
}

/// Global multiplication operator.
/** \relates Fixed */
inline Fixed operator * ( Double a, const Fixed & b )
{
	return Fixed( FixedMul(b.value,(Int)(a*65536)), 0 );
}

///////////////////////////////////////////////////////////////////
// Operator /
///////////////////////////////////////////////////////////////////

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( const Fixed& a, const Fixed& b )
{
	return Fixed( FixedDiv(a.value,b.value), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( const Fixed & a, Short b )
{
	return Fixed( FixedDiv(a.value, (Int(b)) << 16), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( const Fixed & a, Int b ) 
{
	return Fixed( FixedDiv(a.value, b << 16), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( const Fixed & a, Float b ) 
{
	return Fixed( FixedDiv(a.value,(Int)(b*65536)), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( const Fixed & a, Double b ) 
{
	return Fixed( FixedDiv(a.value,(Int)(b*65536)), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( Short a, const Fixed & b ) 
{
	return Fixed( FixedDiv( Int(a) << 16, b.value ), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( Int a, const Fixed & b )
{
	return Fixed( FixedDiv( a << 16, b.value ), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( Float a, const Fixed & b )
{
	return Fixed( FixedDiv((Int)(a*65536), b.value ), 0 );
}

/// Global division operator.
/** \relates Fixed */
inline Fixed operator / ( Double a, const Fixed & b )
{
	return Fixed( FixedDiv((Int)(a*65536), b.value ), 0 );
}


///////////////////////////////////////////////////////////////////
// Operator ==
///////////////////////////////////////////////////////////////////

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( const Fixed & a, const Fixed & b ) 
{
	return a.value == b.value;
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( const Fixed & a, Short b ) 
{
	return a.value == ( Int(b) << 16 );
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( const Fixed & a, Int b )
{
	return a.value == ( b << 16 );
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( const Fixed & a, Float b ) 
{
	return a.value == ( Int(b) * 65536 );
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( const Fixed & a, Double b )
{
	return a.value == ( Int(b) * 65536 );
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( Short a, const Fixed & b )
{
	return b == a;
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( Int a, const Fixed & b )
{
	return b == a;
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( Float a, const Fixed & b )
{
	return b == a;
}

/// Global equality comparison operator.
/** \relates Fixed */
inline Int operator == ( Double a, const Fixed & b )
{
	return b == a;
}

///////////////////////////////////////////////////////////////////
// Operator !=
///////////////////////////////////////////////////////////////////

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( const Fixed & a, const Fixed & b )
{
	return a.value != b.value;
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( const Fixed & a, Short b)
{
	return a.value != ( Int(b) << 16 );
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( const Fixed & a, Int b)
{
	return a.value != ( b << 16 );
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( const Fixed & a, Float b)
{
	return a.value != ( Int(b) * 65536 );
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( const Fixed & a, Double b)
{
	return a.value != ( Int(b) * 65536 );
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( Short a, const Fixed & b )
{
	return b != a;
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( Int a, const Fixed & b )
{
	return b != a;
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( Float a, const Fixed & b )
{
	return b != a;
}

/// Global inequality comparison operator.
/** \relates Fixed */
inline Int operator != ( Double a, const Fixed & b )
{
	return b != a;
}

///////////////////////////////////////////////////////////////////
// operator >
///////////////////////////////////////////////////////////////////

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( const Fixed & a, const Fixed & b )
{
	return a.value > b.value;
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( const Fixed & a, Short b )
{
	return a.value > ( Int(b) << 16 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( const Fixed & a, Int b )
{
	return a.value > b << 16;
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( const Fixed & a, Float b )
{
	return a.value > ( Int(b) * 65536 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( const Fixed & a, Double b )
{
	return a.value > ( Int(b) * 65536 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( Short a, const Fixed & b )
{
	return b.value < ( Int(a) << 16 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( Int a, const Fixed & b )
{
	return b.value < ( a << 16 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( Float a, const Fixed & b )
{
	return b.value < ( Int(a) * 65536 );
}

/// Global greater than comparison operator.
/** \relates Fixed */
inline Int operator > ( Double a, const Fixed & b )
{
	return b.value < ( Int(a) * 65536 );
}

///////////////////////////////////////////////////////////////////
// Operator <
///////////////////////////////////////////////////////////////////

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( const Fixed & a, const Fixed & b )
{
	return a.value < b.value;
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( const Fixed & a, Short b )
{
	return a.value < ( Int(b) << 16 );
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( const Fixed & a, Int b )
{
	return a.value < ( b << 16 );
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( const Fixed & a, Float b )
{
	return a.value < ( Int(b) * 65536 );
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( const Fixed & a, Double b )
{
  return a.value < ( Int(b) * 65536 );
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( Short a, const Fixed & b )
{	
	return b > a;
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( Int a, const Fixed & b )
{
	return b > a;
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( Float a, const Fixed & b )
{
	return b > a;
}

/// Global lesser than comparison operator.
/** \relates Fixed */
inline Int operator < ( Double a, const Fixed & b )
{
	return b > a;
}

///////////////////////////////////////////////////////////////////
// Operator >=
///////////////////////////////////////////////////////////////////

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( const Fixed & a, const Fixed & b )
{
	return a.value >= b.value;
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( const Fixed & a, Short b )
{
	return a.value >= ( Int(b) << 16 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( const Fixed & a, Int b )
{
	return a.value >= ( b << 16 );
}

/// Global greater or equal comparison operator.
inline Int operator >= ( const Fixed & a, Float b )
{
	return a.value >= ( Int(b) * 65536 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( const Fixed & a, Double b )
{
	return a.value >= ( Int(b) * 65536 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( Short a, const Fixed & b )
{	
	//return  b <= a;
	return b.value <= ( Int(a) << 16 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( Int a, const Fixed & b )
{	
	//return b <= a;
	return b.value <= ( a << 16 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( Float a, const Fixed & b )
{	
	//return b <= a;
	return b.value <= ( Int(a) * 65536 );
}

/// Global greater or equal comparison operator.
/** \relates Fixed */
inline Int operator >= ( Double a, const Fixed & b )
{	
	//return b <= a;
	return b.value <= ( Int(a) * 65536 );
}


///////////////////////////////////////////////////////////////////
// Operator <=
///////////////////////////////////////////////////////////////////

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( const Fixed & a, const Fixed & b )
{
	return a.value <= b.value;
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( const Fixed & a, Short b )
{
	return a.value <= ( Int(b) << 16 );
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( const Fixed & a, Int b )
{
	return a.value <= ( b << 16 );
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( const Fixed & a, Float b )
{
	return a.value <= ( Int(b) * 65536 );
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( const Fixed & a, Double b )
{
	return a.value <= ( Int(b) * 65536 );
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( Short a, const Fixed & b )
{ 
	return b >= a;
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( Int a, const Fixed & b ) 
{	
	return b >= a;
}


/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( Float a, const Fixed & b )
{	
	return b >= a;
}

/// Global lesser or equal comparison operator.
/** \relates Fixed */
inline Int operator <= ( Double a, const Fixed & b ) 
{	
	return b >= a;
}


#endif


} //namespace mdragon

#endif // __MD_FIXED_H__
