/** \file
 *	3d software rasterizer structures. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

namespace mdragon
{

class Vertex
{
public:
	Float32 x,y,z;
	Float32 u,v;
	Int sx,sy;
	Short color;

	Vertex() {}
	Vertex(Vector3fx& v)
	{

#ifndef Fixed
		x = v.x.value;
		y = v.y.value;
		z = v.z.value;
#endif

#ifdef Fixed
		x = v.x;
		y = v.y;
		z = v.z;
#endif
		
	}

	operator Vector3fx () { return Vector3fx(x,y,z); }
};

inline Vertex FindIntersect(Vertex& V1,Vertex& V2,Float32 Z)
{
	Vertex v;

	Float32 k = FDiv( ( Z - V1.z ) , ( V2.z - V1.z ) );

	v.x = V1.x + FMul8x4( ( V2.x - V1.x ) , k );
	v.y = V1.y + FMul8x4( ( V2.y - V1.y ) , k );
	v.z = Z;

	v.u = V1.u + FMul4x4( ( V2.u - V1.u ) , k );
	v.v = V1.v + FMul4x4( ( V2.v - V1.v ) , k );

	v.color = V1.color + F2I( FMul4x4( I2F( V2.color - V1.color ) , k ) );

/*
	Fixed k = ( Z - V1.z ) / ( V2.z - V1.z );

	v.x = V1.x + ( V2.x - V1.x ) * k;
	v.y = V1.y + ( V2.y - V1.y ) * k;
	v.z = Z;

	v.u = V1.u + ( V2.u - V1.u ) * k;
	v.v = V1.v + ( V2.v - V1.v ) * k;
*/
	
	return v;
}

inline Vector3fx FindIntersect(Vector3fx& V1,Vector3fx& V2,Float32 Z)
{
	Vector3fx v;

#ifndef Fixed

	Float32 k = FDiv( ( Z - V1.z.value ) , ( V2.z.value - V1.z.value ) );

	v.x.value = V1.x.value + FMul8x4( ( V2.x.value - V1.x.value ) , k );
	v.y.value = V1.y.value + FMul8x4( ( V2.y.value - V1.y.value ) , k );
	v.z.value = Z;

#endif

#ifdef Fixed

	Fixed k = ( Z - V1.z ) / ( V2.z - V1.z );

	v.x = V1.x + ( V2.x - V1.x ) * k;
	v.y = V1.y + ( V2.y - V1.y ) * k;
	v.z = Z;

#endif

	return v;
}

#define TWO_SIDE 1
#define DRAW_AND 2
#define DRAW_OR 4
#define DRAW_MASK 8
#define NOCLIP 16
#define CACHED 32
#define QUAD3 64

class Triangle
{
public:

	Texture* texture;

	Vertex a;
	Word color;

	Vertex b;
	Word alpha;

	Vertex c;
	Word flags;

	Int z;

};

class VertexS
{
public:

	Short sx,sy;
	Short u,v;
	Word z;
	Short color;

};

class TriangleS
{
public:

	Texture* texture;

	VertexS a;
	VertexS b;
	VertexS c;

	Word color;
	Byte alpha;
	Byte flags;

	Int z;

};


class Quad
{
public:

	Texture* texture;

	Vertex a;
	Vertex b;
	Vertex c;
	Vertex d;

	Word color;

	Word alpha;
	Word flags;

	Fixed z;

};

inline void FindMiddleVertex(Vertex& V1,Vertex& V2,Vertex& v)
{
#ifdef Fixed	
	v.x = (V1.x + V2.x)/2;
	v.y = (V1.y + V2.y)/2;
	v.z = (V1.z + V2.z)/2;

	v.u = (V1.u + V2.u)/2;
	v.v = (V1.v + V2.v)/2;
#else
	v.x = (V1.x + V2.x)>>1;
	v.y = (V1.y + V2.y)>>1;
	v.z = (V1.z + V2.z)>>1;

	v.u = (V1.u + V2.u)>>1;
	v.v = (V1.v + V2.v)>>1;
#endif

	v.color = (Word)( ( ( V1.color >> 1 ) & 0x7777 ) + ( ( V2.color >> 1 ) & 0x7777 ) );
}

#define SIDE_CLIP (1<<7)

} //namespace mdragon

#endif // __TRIANGLE_H__