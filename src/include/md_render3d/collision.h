/** \file
 *	Collision detection. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */


#ifndef __MD_COLLISION_H__
#define __MD_COLLISION_H__

namespace mdragon
{

#define VectorXYZ(v,a,b,c) \
	(v)[0] = (a); \
	(v)[1] = (b); \
	(v)[2] = (c);

/* a = b - c */
#define subVector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];

#define crossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

#define innerProduct(v,q) (	(v)[0] * (q)[0] + (v)[1] * (q)[1] + (v)[2] * (q)[2]	)

#ifndef Fixed

#define Fdiv256(F) { F.value >>= 4; }
#define Vdiv256(V) { Fdiv256(V.x) Fdiv256(V.y) Fdiv256(V.z) }

#define FdivN(F,N) { F.value >>= N; }
#define VdivN(V,N) { FdivN(V.x,N) FdivN(V.y,N) FdivN(V.z,N) }

#define Fmul256(F) { F.value <<= 4; }
#define Vmul256(V) { Fmul256(V.x) Fmul256(V.y) Fmul256(V.z) }

#define FmulN(F,N) { F.value <<= N; }
#define VmulN(V,N) { FmulN(V.x,N) FmulN(V.y,N) FmulN(V.z,N) }

#endif

#ifdef Fixed

#define Fdiv256(F)
#define Vdiv256(V) { /*(V.x) /= 10; (V.y) /= 10; (V.z) /= 10; */ }

#endif

class VertexBuffer;

/// Axis Aligned Bounding Box (farther AABB) class .
class AABB
{
public:
	
	/// Default constructor.
	AABB() {}

	/// Constructor with given MIN and MAX values.
	/**
	 * @param min_ - MIN value of AABB.
	 * @param max_ - MAX value of AABB.
	 */
	AABB(const Vector3fx& min_,const Vector3fx& max_) { min = min_; max = max_; }

	/// Builds AABB for two points.
	/**
	 * This may be for example ray's start and end points.
	 * @param v0 - first point.
	 * @param v1 - second point.
	 */
	inline void Build(const Vector3fx& v0,const Vector3fx& v1)
	{
		if(v0.x>v1.x)
		{
			min.x=v1.x;
			max.x=v0.x;
		}
		else
		{
			min.x=v0.x;
			max.x=v1.x;
		}

		if(v0.y>v1.y)
		{
			min.y=v1.y;
			max.y=v0.y;
		}
		else
		{
			min.y=v0.y;
			max.y=v1.y;
		}

		if(v0.z>v1.z)
		{
			min.z=v1.z;
			max.z=v0.z;
		}
		else
		{
			min.z=v0.z;
			max.z=v1.z;
		}
	}

	/// Builds AABB for three points.
	/**
	 * This may be for example vertexes of triangle.
	 * @param v0 - first point.
	 * @param v1 - second point.
	 * @param v2 - third point.
	 */
	inline void Build(const Vector3fx& v0,const Vector3fx& v1,const Vector3fx& v2)
	{
		Build(v0,v1);
		Add(v2);
	}

	/// Adds given point to the AABB and recompute it.
	/**
	 * @param v - new point.
	 */
	inline void Add(const Vector3fx& v)
	{
		if(min.x>v.x)
			min.x=v.x;

		if(max.x<v.x)
			max.x=v.x;

		if(min.y>v.y)
			min.y=v.y;

		if(max.y<v.y)
			max.y=v.y;

		if(min.z>v.z)
			min.z=v.z;

		if(max.z<v.z)
			max.z=v.z;
	}

	/// Adds another AABB to the current and recompute it.
	/**
	 * @param aabb - another AABB.
	 */
	inline void Add(const AABB& aabb)
	{
		if(min.x>aabb.min.x)
			min.x=aabb.min.x;

		if(max.x<aabb.max.x)
			max.x=aabb.max.x;

		if(min.y>aabb.min.y)
			min.y=aabb.min.y;

		if(max.y<aabb.max.y)
			max.y=aabb.max.y;

		if(min.z>aabb.min.z)
			min.z=aabb.min.z;

		if(max.z<aabb.max.z)
			max.z=aabb.max.z;
	}

	/// Checks if this AABB collides with another AABB. 
	/**
	 * @param aabb - another AABB for checking.
	 * @return Return True, if AABBs collide, else - False.
	 */
	inline Bool IsCollide(const AABB& aabb) const
	{
		return ((min.x <= aabb.max.x) &&
				(min.y <= aabb.max.y) &&
				(min.z <= aabb.max.z) &&
				(max.x >= aabb.min.x) &&
				(max.y >= aabb.min.y) &&
				(max.z >= aabb.min.z));
	}

	/// MIN value of AABB.
	Vector3fx min;

	/// MAX value of AABB.
	Vector3fx max;

};

/// Checks if two AABBs collide.
/** \relates AABB */
inline Bool IsCollide(const AABB& aab1,const AABB& aab2)
{
	return aab1.IsCollide(aab2);
}


/// Sphere represents basic sphere class.
class Sphere
{
public:
	
	/// Default constructor.
	Sphere() {}

	/// Constructor with given center and radius values.
	/**
	 * @param center_ - sphere center value.
	 * @param radius_ - sphere radius value.
	 */
	Sphere(const Vector3fx& center_,const Fixed& radius_)
	{
		center = center_;
		radius = radius_;

		Update();
	}
	
	/// Recalculates sphere's AABB.
	/**
	 * Call this function after any changes of center or radius values.
	 */
	inline void Update()
	{
		aabb.min = center - Vector3fx(radius,radius,radius);
		aabb.max = center + Vector3fx(radius,radius,radius);
	}

	/// Checks if this sphere collides with another sphere.
	/**
	 * @param sphere - another sphere for checking.
	 * @return Return True if this sphere collides with another, else - False.
	 */
	inline Bool IsCollide(const Sphere& sphere) const
	{
		if( ! aabb.IsCollide( sphere.aabb ) )
			return False;

		Vector3fx dc = center - sphere.center;
		Vdiv256(dc)
		Fixed dcs = DotProduct(dc,dc);

		Fixed dr = radius + sphere.radius;
		Fdiv256(dr)
		dr *= dr;

		return ( dcs <= dr );
	}

	/// Center of sphere.
	Vector3fx center;

	/// Radius of sphere.
	Fixed radius;

	/// Sphere's Axis Aligned Bounding Box (AABB).
	AABB aabb;

};

#define CC_FLAG_EDGE				(1<<0)
#define CC_FLAG_IN					(1<<1)
#define CC_FLAG_COLLIDER_RAY		(1<<2)
#define CC_FLAG_COLLIDER_SPHERE		(1<<3)
#define CC_FLAG_CONTACT_TRIANGLE	(1<<4)
#define CC_FLAG_CONTACT_SPHERE		(1<<5)

class Basic3D;

/// CollisionContact represents basic collision contact class.
class CollisionContact
{
public:

	/// Object that was collided.
	ObjRef<Object> object;

	/// Collision point.
	Vector3fx point;

	/// Normal of collided surface in the contact point.
	Vector3fx normal;

	/// Penetration.
	Fixed penetration;

	/// Collision flags.
	DWord flags;
};


/// CollisionManager represents collision manager class.
class CollisionManager
{
public:

	/// Default constructor.
	CollisionManager();

	/// Destructor.
	~CollisionManager();


	Bool Collide(ObjRef<VertexBuffer> vb,AABB* aabb,Vector3fx* p,Vector3fx* d,Fixed* t);

	Bool Collide(ObjRef<VertexBuffer> vb,Sphere* collider,Bool prefer_only_in=True);

	Bool Collide(Sphere* sphere,AABB* aabb,Vector3fx* p,Vector3fx* d,Fixed* t);

	Bool Collide(Sphere* sphere,Sphere* collider);

	Bool Collide(AABB* aabb,Vector3fx* v0,Vector3fx* v1,Vector3fx* v2,Vector3fx* n,Sphere* collider,Bool prefer_only_in=True);

	/// Contacts list.
	vector<CollisionContact> contacts;

	/// Object that is checked.
	ObjRef<Object> object;

private:

	Bool Collide(Vector3fx* sc,Fixed* r2,Vector3fx* p,Vector3fx* n,Vector3fx* N,Fixed* Penetration);
	
};

Int CheckRayVB(ObjRef<VertexBuffer> vb,Vector3fx& p,Vector3fx& d,Fixed& t);
Int CheckRayIntersectsTriangle(Fixed *p, Fixed *d, Fixed *v0, Fixed *v1, Fixed *v2, Fixed* lt);

inline void Axes(Vector3fx& X,Vector3fx& Y,const Vector3fx& Z)
{
	Vector3fx axis;
/*
	if( Z.x > - F_ONE + F_ONE/10 && Z.x < F_ONE - F_ONE/10 )
		axis=Vector3fx(1,0,0);
	else
	if( Z.y > - F_ONE + F_ONE/10 && Z.y < F_ONE - F_ONE/10 )
		axis=Vector3fx(0,1,0);
	else
		axis=Vector3fx(0,0,1);
*/

	if( Z.x >= -1 && Z.x <= 1 )
		axis=Vector3fx(1,0,0);
	else
	if( Z.y >= -1 && Z.y <= 1 )
		axis=Vector3fx(0,1,0);
	else
		axis=Vector3fx(0,0,1);

	X = Normalize( CrossProduct(axis,Z) );
	Y = CrossProduct(Z,X);
}

} // namespace mdragon

#endif // __MD_COLLISION_H__
