/** \file
 *	Fixed point mathematic. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_FIXEDMATH_H__
#define __MD_FIXEDMATH_H__

namespace mdragon
{

#ifndef Fixed

#define PI 205887
#define PI_OVER_2 (PI/2)
#define PI_UP_2 (PI*2)
#define E 178145
#define HALF (1<<15)
#define ONE (1<<16)
#define ZERO (0)

#define F_PI Fixed(PI,0)
#define F_PI_OVER_2 Fixed(PI_OVER_2,0)
#define F_PI_UP_2 Fixed(PI_UP_2,0)
#define F_E Fixed(E,0)
#define F_HALF Fixed(HALF,0)
#define F_ONE Fixed(1)
#define F_ZERO Fixed(0)


Fixed Sin (const Fixed& f);
Fixed Cos (const Fixed& f);
Fixed Tan (const Fixed& f);
Fixed ArcTan (const Fixed& f);
Fixed ArcSin (const Fixed& f);
Fixed ArcCos (const Fixed& f);
Fixed Ln (const Fixed& x);
Fixed Sqrt (const Fixed& n);
Fixed Round (const Fixed& n);


#define Float32 Int

#define FIXED_DIGIT 16
#define FIXED_MULTIPLIER (1<<FIXED_DIGIT)

#define I2F(x) (((Int)(x))<<FIXED_DIGIT)
#define F2I(x) ((x)>>FIXED_DIGIT)
#define F2F(x) ( (Float32) ((x)*FIXED_MULTIPLIER) )

//#define FMul(x,y) ( (Float32) ((((__int64)(x))*(y))>>FIXED_DIGIT) )
//#define FDiv(x,y) ( (Float32) ((((__int64)(x))<<FIXED_DIGIT)/(y)) )

#define FMul16x0(x,y) ( ( (x) >> 16 ) * (y) )

#define FMul8x8(x,y) ( ( (x) >> 8 ) * ( (y) >> 8 ) )

#define FMul0x0(x,y) ( ( (x) * (y) ) >> 16 )

#define FMul8x0(x,y) ( ( ( (x) >> 8 ) * (y) ) >> 8 )

#define FMul4x0(x,y) ( ( ( (x) >> 4 ) * (y) ) >> 12 )

#define FMul10x0(x,y) ( ( ( (x) >> 10 ) * (y) ) >> 6 )

#define FMul4x4(x,y) ( ( ( (x) >> 4 ) * ( (y) >> 4 ) ) >> 8 )

#define FMul8x4(x,y) ( ( ( (x) >> 8 ) * ( (y) >> 4 ) ) >> 4 )

#define FMul4x8(x,y) ( ( ( (x) >> 4 ) * ( (y) >> 8 ) ) >> 4 )


#define FDiv14x2(x,y) ( ( ( (x) << 14 ) / ( (y) >> 2 ) ) )

#define FDiv0x16(x,y) ( ( (x) / ( (y) >> 16 ) ) )

#define FDiv0x8(x,y) ( ( (x) / ( (y) >> 8 ) ) << 8 )

#define FDiv8x0(x,y) ( ( ( (x) << 8 ) / (y) ) << 8 )

#define FDiv8x8(x,y) ( ( (x) << 8 ) / ( (y) >> 8 ) )

#define FDiv7x9(x,y) ( ( (x) << 7 ) / ( (y) >> 9 ) )

#define FDiv8x4(x,y) ( ( ( (x) << 8 ) / ( (y) >> 4 ) ) << 4 )

#define FDiv4x8(x,y) ( ( ( (x) << 4 ) / ( (y) >> 8 ) ) << 4 )

#define FDiv4x4(x,y) ( ( ( (x) << 4 ) / ( (y) >> 4 ) ) << 8 )

#define FDiv0x0(x,y) ( ( (x) / (y) ) << 16 )


#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)

#define FMul(x,y) (  (((Long(x))*(y))>>FIXED_DIGIT) . GetTInt() )
#define FDiv(x,y) (  ( ( ( ( Long(x) ) << 16 ) / (y) ) ) . GetTInt() )

#else

#define FMul(x,y) ( (Float32) ((((Long)(x))*(y))>>FIXED_DIGIT) )
#define FDiv(x,y) ( (Float32) ( ( ( ( (Long)(x) ) << 16 ) / (y) ) ) )

#endif



#define LS(x,s) ((x)<<(s))
#define RS(x,s) ((x)>>(s))

// #define HALF (RS(FIXED_MULTIPLIER,1))

#define SIGN(x) (((x)>=0)?1:-1)

//#define ROUND(x) ( ((x)>=0) ? F2I((x)+HALF) : F2I((x)-HALF) )
//#define ROUND(x) F2I(x)

inline Int ROUND(Float32 x)
{
	return ( (x>=0) ? F2I(x+HALF) : F2I(x-HALF) );
}

#endif

#ifdef Fixed

#ifdef MD_OS_WIN32
#include <math.h>
#endif

#define F_PI (3.14159265f)
#define F_PI_OVER_2 (F_PI/2)
#define F_E  (2,71828183f)
#define F_HALF (0.5f)
#define F_ONE (1.0f)
#define F_ZERO (0.0f)

#define Sin(f) sin(f)
#define Cos(f) cos(f)
#define Tan(f) tan(f)
#define ArcTan(f) atan(f)
#define ArcSin(f) asin(f)
#define ArcCos(f) acos(f)
#define Ln(f) log(f)
#define Sqrt(f) sqrt(f)

inline Int Round(Fixed f) 
{
	if( f > 0 )
		return (Int)(f+0.5f);
	else
		return (Int)(f-0.5f);
}

#define Float32 float

#define FIXED_DIGIT 16
#define FIXED_MULTIPLIER (1<<FIXED_DIGIT)

#define FMul(x,y) ((x)*(y))
#define FDiv(x,y) ((x)/(y))

#define I2F(x) ((Float)(x))
#define F2I(x) ((Int)(x))
#define F2F(x) ((Float)(x))

#define LS(x,s) ((x)*(1<<(s)))
#define RS(x,s) ((x)/(1<<(s)))

//#define Sqrt(n) ((Float)sqrt(n))

#define HALF F2F(0.5)

#define SIGN(x) (((x)>=0)?1:-1)

//#define ROUND(x) ( ((x)>=0) ? F2I((x)+HALF) : F2I((x)-HALF) )
#define ROUND(x) F2I(x)

#define FMul16x0(x,y) ((x)*(y))

#define FMul8x8(x,y) ((x)*(y))

#define FMul0x0(x,y) ((x)*(y))

#define FMul8x0(x,y) ((x)*(y))

#define FMul4x0(x,y) ((x)*(y))

#define FMul10x0(x,y) ((x)*(y))

#define FMul4x4(x,y) ((x)*(y))

#define FMul8x4(x,y) ((x)*(y))

#define FMul4x8(x,y) ((x)*(y))


#define FDiv0x16(x,y) ((x)/(y))

#define FDiv0x8(x,y) ((x)/(y))

#define FDiv8x0(x,y) ((x)/(y))

#define FDiv8x8(x,y) ((x)/(y))

#define FDiv7x9(x,y) ((x)/(y))

#define FDiv8x4(x,y) ((x)/(y))

#define FDiv4x8(x,y) ((x)/(y))

#define FDiv4x4(x,y) ((x)/(y))

#define FDiv0x0(x,y) ((x)/(y))

#endif

double MDSqrt(double x);

} //namespace mdragon

#endif // __MD_FIXEDMATH_H__
