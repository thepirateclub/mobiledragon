/** \file
 *	ARGB color class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_COLOR_H__
#define __MD_COLOR_H__

namespace mdragon
{

// 4096 colors total
#define RD_BITS 4 // 4 levels of red in a base color
#define GR_BITS 4 // 4 levels of green in a base color
#define BL_BITS 4 // 4 levels of blue in a base color

#define RD_MASK ((1<<RD_BITS)-1)
#define GR_MASK ((1<<GR_BITS)-1)
#define BL_MASK ((1<<BL_BITS)-1)

// convert RGB 888 to base 8 bits RGB color 
//#define COLOR_RGB(R, G, B) (((B) >> (8 - BL_BITS)) | (((G) >> (8 - GR_BITS)) << BL_BITS) | (((R) >> (8 - RD_BITS)) << (GR_BITS + BL_BITS)))
#define COLOR_RGB(R, G, B) ((((Word)B) >> (8 - BL_BITS)) | ((((Word)G) >> (8 - GR_BITS)) << BL_BITS) | ((((Word)R) >> (8 - RD_BITS)) << (GR_BITS + BL_BITS)))

#define GET_COLOR_RD(c) ( ( (c) >> ( GR_BITS + BL_BITS ) ) & RD_MASK )
#define GET_COLOR_GR(c) ( ( (c) >> ( BL_BITS ) ) & GR_MASK )
#define GET_COLOR_BL(c) ( (c) & GR_MASK )

typedef Word Pixel;

/// RGBA color.
class Color
{
public:
	
	/// Default constructor.
	Color() {}

	/// Constructor with given RED, GREEN, BLUE and ALPHA components.
	/**
	 * @param r_ - Red component's value. This is integer value in the [0..255] intervals.
	 * @param g_ - Green component's value. This is integer value in the [0..255] intervals.
	 * @param b_ - Blue component's value. This is integer value in the [0..255] intervals.
	 * @param a_ - Alpha component's value. This is integer value in the [0..255] intervals.
	 */
	Color(Int r_,Int g_,Int b_,Int a_) { r=r_; g=g_; b=b_; a=a_; }

	/// Constructor with given RED, GREEN, BLUE and ALPHA components.
	/**
	 * @param r_ - Red component's value. This is Fixed value in the [0..1] intervals.
	 * @param g_ - Green component's value. This is Fixed value in the [0..1] intervals.
	 * @param b_ - Blue component's value. This is Fixed value in the [0..1] intervals.
	 * @param a_ - Alpha component's value. This is Fixed value in the [0..1] intervals.
	 */
	Color(Fixed r_,Fixed g_,Fixed b_,Fixed a_) { r=255*r_; g=255*g_; b=255*b_; a=255*a_; }	

	/// Constructor with given color integer value.
	/**
	 * Alpha value sets as 255 by default.
	 * @param color - integer color value.
	 */
	Color(Int color) 
	{ 
		///r=(Byte)((((color&0xF00)>>8)*255)/15);
		r=(Byte)(((color&0xF00)>>8)*17);

		//g=(Byte)((((color&0xF0)>>4)*255)/15);
		g=(Byte)(((color&0xF0)>>4)*17);
		
		//b=(Byte)(((color&0xF)*255)/15);
		b=(Byte)((color&0xF)*17);
		
		a=(255);
	}
	

	/// Returns average component's value. 
	/**
	 * @return Returns average component's value. 
	 */
	Byte Middle() { return (Byte)(((Int)r+(Int)g+(Int)b+(Int)a)>>2); }

	/// Converts color value to the integer.
	inline operator Int() { return COLOR_RGB((Int)r,(Int)g,(Int)b) | ( ( ((Int)a) >> 4 ) << 12 ); }

	/// Converts color value to the Vector4.
	inline operator Vector4fx() { return Vector4fx( Fixed(r)/255, Fixed(g)/255, Fixed(b)/255, Fixed(a)/255 ); }

	/// Equality comparison operator.
	inline Bool operator == ( const Color& color ) const 
	{
		return r == color.r && g == color.g && b == color.b && a == color.a; 
	}

	/// Red color component.
	Byte r;

	/// Green color component.
	Byte g;

	/// Blue color component.
	Byte b;

	/// Alpha component.
	Byte a;
};

/// Binary addition operator.
/** \relates Color */
inline Color operator+ (Color& c1,Color& c2) 
{ 
	Int r,g,b,a;

	r = c1.r+c2.r;
	if(r>255)
		r=255;

	g = c1.g+c2.g;
	if(g>255)
		g=255;

	b = c1.b+c2.b;
	if(b>255)
		b=255;

	a = c1.a+c2.a;
	if(a>255)
		a=255;

	return Color((Byte)r,(Byte)g,(Byte)b,(Byte)a); 
}

/// Binary multiplication operator.
/** \relates Color */
inline Color operator* (Color& c1,Color& c2) 
{ 
	Int r,g,b,a;

	r = c1.r; r *= c2.r; r >>= 8;
	g = c1.g; g *= c2.g; g >>= 8;
	b = c1.b; b *= c2.b; b >>= 8;
	a = c1.a; a *= c2.a; a >>= 8;

	return Color((Byte)r,(Byte)g,(Byte)b,(Byte)a); 
}

inline Int GetLightLevel(Int color)
{
	Int R = (color&0xF00)>>8;
	Int G = (color&0x0F0)>>4;
	Int B = (color&0x00F);

	R = max(R,G);
	return max(R,B);
}

inline Int GetMaxColorBitMask(Int color)
{
	Int mask = 0xF;

	for(Int i=3;i>=0;i--)
	{
		if(color&(1<<i))
			return mask;
		else
			mask>>=1;
	}

	return mask;
}

inline Int GetLightMask(Int color)
{
	Int R = (color&0xF00)>>8;
	Int G = (color&0x0F0)>>4;
	Int B = (color&0x00F);
	
	return (GetMaxColorBitMask(R)<<8)|(GetMaxColorBitMask(G)<<4)|GetMaxColorBitMask(B);
}

inline Int GetLightIntensity(Int color)
{
	Int R = (color&0xF00)>>8;
	Int G = (color&0x0F0)>>4;
	Int B = (color&0x00F);

	return (R+G+B)/3;
}

inline Int GetColorByIntensity(Int color,Int intensity)
{
	Int R = (((color&0xF00)>>8)*intensity)/15;
	Int G = (((color&0x0F0)>>4)*intensity)/15;
	Int B = ((color&0x00F)*intensity)/15;

	return (R<<8)|(G<<4)|B;
}

inline Int GetMidColor(Int a,Int b,Int c)
{
	Int cr = ( ( a & 0xF00 ) >> 8 ) + ( ( b & 0xF00 ) >> 8 ) + ( ( c & 0xF00 ) >> 8 );
	Int cg = ( ( a & 0xF0 ) >> 4 ) + (  ( b & 0xF0 ) >> 4 ) + (  ( c & 0xF0 ) >> 4 );
	Int cb =   ( a & 0xF ) +            ( b & 0xF ) +            ( c & 0xF );

	cr /= 3;
	cg /= 3;
	cb /= 3;

	return (cr<<8)|(cg<<4)|cb;
}

} //namespace mdragon

#endif // __MD_COLOR_H__
