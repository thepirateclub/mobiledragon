/** \file
 *	Polygon clipping. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_POLYCLIP_H__
#define __MD_POLYCLIP_H__

#define POLYCLIP_EPSILON (F_ONE/100)

namespace mdragon
{

/// 2D point class.
class Point
{
public:

	/// Default constructor.
	Point() {}

	/// Constructor with given X and Y coordinates values.
	/**
	 * @param _x - X coordinate value.
	 * @param _y - Y coordinate value.
	 */
	Point(Fixed _x,Fixed _y) { x=_x; y=_y; }
	
	/// X coordinate.
	Fixed x;

	/// Y coordinate.
	Fixed y;

};

void Clipping(vector<Point>& P,vector<Point>& W,vector<Point>& Q);
Bool Clipping(Point& P,vector<Point>& W,vector<Point>& Q);

inline Bool isEqual(Point& p1,Point& p2)
{
	if(abs(p2.x-p1.x)>POLYCLIP_EPSILON)
		return False;

	if(abs(p2.y-p1.y)>POLYCLIP_EPSILON)
		return False;

	return True;
}

inline Int Sign(Fixed a)
{
	return (a>0)?1:(a==0)?0:-1;
}

inline void Save(Point& p,vector<Point>& Q)
{
	if(Q.size())
		if(isEqual(Q[Q.size()-1],p)||
		   isEqual(Q[0],p))
		   return;

	Q.push_back(p);
}

inline Bool isRightPolygon(vector<Point>& r)
{
   if((r[1].x-r[0].x)*(r[2].y-r[1].y)-(r[2].x-r[1].x)*(r[1].y-r[0].y)>0)
		return True;

   return False;
}

inline void RightPolygon(vector<Point>& P,vector<Point>& Q)
{
   if(!isRightPolygon(P))
   {
	   Q=P;

	Int size=P.size()-1;

	   for(Int i=0;i<=size;i++)
		   P[i]=Q[size-i];
   }
}

inline void FindPlane(Vector3fx& n,Int& x,Int& y,Int& z)
{
	Fixed Absnx=abs(n.x);
	Fixed Absny=abs(n.y);
	Fixed Absnz=abs(n.z);

	x=0;
	y=1;
	z=2;

	if(Absnx>Absny)
	{// max x
		if(Absnx>Absnz)
		{// swap x&z
			x=2;
			z=0;
		}
	}
	else
	{// max y
		if(Absny>Absnz)
		{// swap y&z
			y=2;
			z=1;
		}
	}
}

class Plane
{
public:

	Vector3fx N;
	Fixed D;

	Plane() {}
	Plane(const Vector3fx& _N,Fixed _D) { N=_N; D=_D; }

	Plane(const Vector3fx& point0, const Vector3fx& point1, const Vector3fx& point2)
	{
		N = Normalize( CrossProduct( (point1 - point0), (point2 - point0) ) );
		D = DotProduct( N, point0 );
	}

    inline Bool HalfSpaceContain(const Vector3fx& point) const { return DotProduct(N,point) >= D; }
};

void Clipping(vector<Vector3fx>& P,vector<Plane>& W,vector<Vector3fx>& Q,Fixed eps=POLYCLIP_EPSILON,Int Pcount=3);
Bool Clipping(vector<Vector3fx>& P,vector<Plane>& W,Fixed eps=POLYCLIP_EPSILON);
Bool PlaneClipping(vector<Vector3fx>& P,vector<Plane>& W,Fixed eps=POLYCLIP_EPSILON);

} //namespace mdragon

#endif // __MD_POLYCLIP_H__
