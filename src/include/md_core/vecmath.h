/** \file
 *	Vector and matrix mathematics. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_VECMATH_H__
#define __MD_VECMATH_H__

namespace mdragon
{

///////////////////////////////////////////////////////////////////////////

/// Convert degrees angle value to the radians angle value.
/**
 * @param deg - angle value in degrees.
 * @return Returns angle value in radians.
 */
template <class Real>
Real DegToRad(Real deg) { return (deg*F_PI)/180; }


/// Convert radians angle value to the degrees angle value.
/**
 * @param rad - angle value in radians.
 * @return Returns angle value in degrees.
 */
template <class Real>
Real RadToDeg(Real rad) { return (rad*180)/F_PI; }

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// 2D Vector
///////////////////////////////////////////////////////////////////////////


/// Vector2 represents two dimensional template vector class.
/** 
 * @param 'Real' parameter defines vector components numeric type. 
 */
template <class Real>
class Vector2 
{
public:

	/// Default constructor.
	Vector2 () {}

	/// Constructor with given component value.
	/**
	 *	@param xy - value of all vector's components. 
	 */
	Vector2( Real xy ) 
	{
		x = y = xy;
	}

	/// Constructor with given component values.
	/**
	 *	@param x_ - value of X component. 
	 *	@param y_ - value of Y component.
	 */
	Vector2 ( Real x_, Real y_ )
	{
	    x = x;
	    y = y;
	}
  
	/// Casting operator.
	operator Vector2 & () 
	{
		return *this;
	}

    /// Casting operator.
	operator Real* () 
	{
		return (Real *) & x;
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) & x;
	}

    /// Addition assignment operator.
	Vector2<Real> & operator += ( const Vector2<Real> & v )
	{
	    x += v.x;
	    y += v.y;

	    return *this;
	}

	/// Subtraction assignment operator.
	Vector2<Real> & operator -= ( const Vector2<Real> & v ) 
	{
	    x -= v.x;
	    y -= v.y;
	    
		return *this;
	}

	/// Multiplication assignment operator.
	Vector2<Real> & operator *= ( Real f ) 
	{
	    x *= f;
	    y *= f;

	    return *this;
	}

	/// Division assignment operator.
	Vector2<Real> & operator /= ( Real f ) 
	{
	    Real fInv = Real(1) / f;

	    x *= fInv;
	    y *= fInv;

	    return *this;
	}

    /// Unary plus operator.
	Vector2<Real> operator + () const 
	{
	    return *this;
	}

	/// Unary negation operator.
	Vector2<Real> operator - () const 
	{
		return Vector2<Real>(-x,-y);
	}

    /// Binary addition operator.
	Vector2<Real> operator + ( const Vector2<Real> & v ) const 
	{
		return Vector2<Real>( x + v.x, y + v.y );
	}

	/// Binary subtraction operator.
	Vector2<Real> operator - ( const Vector2<Real> & v) const 
	{
		return Vector2<Real>( x - v.x, y - v.y );
	}

	/// Binary multiplication operator.
	Vector2<Real> operator * ( Real f ) const 
	{
		return Vector2<Real>(x * f, y * f);
	}

	/// Binary division operator.
	Vector2<Real> operator / ( Real f ) const 
	{
		Real fInv = Real(1) / f;
		return Vector2<Real>(x * fInv, y * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Vector2<Real> & v ) const 
	{
		return x == v.x && y == v.y;
	}

	/// Inequality comparison operator.
	Bool operator != ( const Vector2<Real> & v ) const 
	{
		return x != v.x || y != v.y;
	}

	/// Normalizes this vector.
	/**
	 * @return Returns normalized vector.
	 */
	Vector2<Real> & Normalize()
	{
		return *this /= GetLength(*this);
	}

	/// X vector's component.
	Real x;

	/// Y vector's component.
	Real y;
};

/// \relates Vector2
typedef Vector2<Fixed> Vector2fx;

/// \relates Vector2
typedef Vector2<Float> Vector2fl;

/// \relates Vector2
typedef Vector2<Double> Vector2dl;

/// Binary multiplication operator.
/** \relates Vector2 */
template <class Real>
Vector2<Real> operator * ( Real f, const Vector2<Real> & v ) 
{
	return Vector2<Real>(v.x * f, v.y * f);
}

/// Binary multiplication operator.
/** \relates Vector2 */
template <class Real>
Vector2<Real> operator * ( const Vector2<Real> & v1, const Vector2<Real> & v2 ) 
{
	return Vector2<Real>(v1.x * v2.x, v1.y * v2.y);
}

/// Computes square length of vector.
/** \relates Vector2 
 * @param v - source vector.
 * @return Returns square length of vector value.
 */
template <class Real>
inline Real GetSquareLength (const Vector2<Real> & v ) 
{
   return v.x * v.x + v.y * v.y;
}

/// Computes length of vector.
/** \relates Vector2 
 * @param v - source vector.
 * @return Returns length of vector value.
 */
template <class Real>
inline Real GetLength (const Vector2<Real> & v ) 
{
   return Sqrt(GetSquareLength(v));
}

/// Normalizes vector. 
/** \relates Vector2 
 * @param v - source vector.
 * @return Returns normalized vector.
 */
template <class Real>
inline Vector2<Real> Normalize ( const Vector2<Real> & v ) 
{
   return v / GetLength(v);
}

/// Finds out a minimal vector's component value.
/** \relates Vector2 
 * @param v - vector.
 * @return Returns minimal vector's component value.
 */
template <class Real>
inline Real Min ( const Vector2<Real> & v ) 
{
	return ( v.x < v.y ) ? v.x : v.y;
}

/// Finds out maximal vector's component value.
/** \relates Vector2 
 * @param v - vector.
 * @return Returns maximal vector's component value.
 */
template <class Real>
inline Real Max ( const Vector2<Real> & v ) 
{
	return ( v.x > v.y ) ? v.x : v.y;
}

/// Creates vector from minimal components of two another vectors.
/** \relates Vector2 
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors
 */
template <class Real>
inline Vector2<Real> Minimize ( const Vector2<Real> & v1, const Vector2<Real> & v2 ) 
{
   return Vector2<Real>( v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y);
}

/// Creates vector from maximal components of two another vectors.
/** \relates Vector2 
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors
 */
template <class Real>
inline Vector2<Real> Maximize ( const Vector2<Real> & v1, const Vector2<Real> & v2 ) 
{
   return Vector2<Real>( v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y);
}

/// Performs dot product of two vectors. 
/** \relates Vector2 
 * @param v1 - first vector.
 * @param v2 - second vector.
 * @return Returns result of dot product of two vectors.
 */
template <class Real>
inline Real DotProduct ( const Vector2<Real> & v1, const Vector2<Real> & v2 ) 
{
   return v1.x * v2.x + v1.y * v2.y;
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector2 
 * This function performs rough computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEquals ( const Vector2<Real> & v1, const Vector2<Real> & v2, const Real radius ) 
{
	return abs(v1.x-v2.x) < radius &&
		   abs(v1.y-v2.y) < radius;
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector2 
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphere ( const Vector2<Real> & v1, const Vector2<Real> & v2, const Real radius ) 
{
	return GetSquareLength(v1-v2) < radius * radius;
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector2 
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius_sq - square radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphereSq ( const Vector2<Real> & v1, const Vector2<Real> & v2, const Real radius_sq ) 
{
	return GetSquareLength(v1-v2) < radius_sq;
}

/// Zeros all vector's components, if they all are lower than given limit.
/** \relates Vector2 
 * @param v - vector.
 * @param limit - limit's value.
 */
template <class Real>
inline void DropToZero( Vector2<Real> & v, const Real limit ) 
{
	if ( abs(v.x) < limit && abs(v.y) < limit )
		v.x = v.y = 0;
}


///////////////////////////////////////////////////////////////////////////
// 3D Vector
///////////////////////////////////////////////////////////////////////////


/// Vector3 represents three dimensional template vector class.
/** 
 * @param 'Real' parameter defines vector components numeric type. 
 */
template <class Real>
class Vector3 
{

public:

	/// Default constructor.
	Vector3() {}

	/// Constructor with given component value.
	/**
  	 *	@param xyz - value of all vector's components. 
	 */
	Vector3( Real xyz ) 
	{
		x = y = z = xyz;
	}

	/// Constructor with given component values.
	/**
	 *	@param x_ - value of X component. 
	 *	@param y_ - value of Y component.
	 *  @param z_ - value of Z component.
	 */
    Vector3( Real x_, Real y_, Real z_ ) 
	{
	    x = x_;
	    y = y_;
	    z = z_;
	}
   
	/// Casting operator.
	operator Vector3 & () 
	{
		return *this;
	}


    /// Casting operator.
	operator Real* () 
	{
		return (Real *) & x;
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) & x;
	}

    /// Addition assignment operator.
	Vector3<Real> & operator += ( const Vector3<Real> & v ) 
	{
	    x += v.x;
	    y += v.y;
		z += v.z;
	
		return *this;
	}

	/// Subtraction assignment operator.
	Vector3<Real> & operator -= ( const Vector3<Real> & v ) 
	{
	    x -= v.x;
	    y -= v.y;
		z -= v.z;
	
		return *this;
	}

	/// Multiplication assignment operator.
	Vector3<Real> & operator *= ( Real f ) 
	{
	    x *= f;
	    y *= f;
	    z *= f;
	
		return *this;
	}

	/// Division assignment operator.
	Vector3<Real> & operator /= ( Real f ) 
	{
	    Real fInv = Real(1) / f;

		x *= fInv;
	    y *= fInv;
	    z *= fInv;

		return *this;
	}

    /// Unary plus operator.
	Vector3<Real> operator + () const 
	{
		return *this;
	}

	/// Unary negation operator.
	Vector3<Real> operator - () const 
	{
		return Vector3<Real>(-x, -y, -z);
	}

    /// Binary addition operator.
	Vector3<Real> operator + ( const Vector3<Real> & v ) const 
	{
		return Vector3<Real>(x + v.x, y + v.y, z + v.z);
	}

	/// Binary subtraction operator.
	Vector3<Real> operator - ( const Vector3<Real> & v ) const 
	{
		return Vector3<Real>(x - v.x, y - v.y, z - v.z);
	}

	/// Binary multiplication operator.
	Vector3<Real> operator * ( Real f ) const 
	{
		return Vector3<Real>(x * f, y * f, z * f);
	}

	/// Binary division operator.
	Vector3<Real> operator / ( Real f ) const 
	{
	    Real fInv = Real(1) / f;
	    return Vector3<Real>(x * fInv, y * fInv, z * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Vector3<Real> & v ) const 
	{
		return x == v.x && y == v.y && z == v.z;
	}

	/// Inequality comparison operator.
	Bool operator != ( const Vector3<Real> & v ) const 
	{
		return x != v.x || y != v.y || z != v.z;
	}

	/// Normalizes this vector.
	/**
	 * @return Returns normalized vector.
	 */
	Vector3<Real> & Normalize()
	{
		return *this /= GetLength(*this);
	}

	/// X vector's component.
	Real x;

	/// Y vector's component.
	Real y;

	/// Z vector's component.
	Real z;

};

/// \relates Vector3 
typedef Vector3<Fixed> Vector3fx;

/// \relates Vector3 
typedef Vector3<Float> Vector3fl;

/// \relates Vector3
typedef Vector3<Double> Vector3dl;

/// Binary multiplication operator.
/** \relates Vector3 */
template <class Real>
Vector3<Real> operator * ( Real f, const Vector3<Real> & v ) 
{
    return Vector3<Real>(f * v.x, f * v.y, f * v.z);
}

/// Binary multiplication operator.
/** \relates Vector3 */
template <class Real>
Vector3<Real> operator * ( const Vector3<Real> & v1, const Vector3<Real> & v2 ) 
{
	return Vector3<Real>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

/// Computes square length of vector.
/** \relates Vector3
 * @param v - source vector.
 * @return Returns square length of vector value.
 */
template <class Real>
inline Real GetSquareLength(const Vector3<Real> & v) 
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/// Computes length of vector.
/** \relates Vector3
 * @param v - source vector.
 * @return Returns length of vector value.
 */
template <class Real>
inline Real GetLength ( const Vector3<Real> & v ) 
{
	return Sqrt(GetSquareLength(v));
}

/// Normalizes vector.
/** \relates Vector3
 * @param v - source vector.
 * @return Returns normalized vector.
 */
template <class Real>
inline Vector3<Real> Normalize ( const Vector3<Real> & v ) 
{
	return v / GetLength(v);
}

/// Finds out minimal vector's component value.
/** \relates Vector3
 * @param v - vector.
 * @return Returns minimal vector's component value.
 */
template <class Real>
inline Real Min ( const Vector3<Real> & v ) 
{
   Real result = v.x;

   if ( v.y < result )
	   result = v.y;
   if ( v.z < result )
	   result = v.z;

   return result;
}

/// Finds out maximal vector's component value.
/** \relates Vector3
 * @param v - vector.
 * @return Returns maximal vector component value.
 */
template <class Real>
inline Real Max ( const Vector3<Real> & v ) 
{
   Real result = v.x;

   if ( result < v.y )
	   result = v.y;
   if ( result < v.z )
	   result = v.z;

   return result;
}

/// Creates vector from minimal components of two another vectors.
/** \relates Vector3
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors
 */
template <class Real>
inline Vector3<Real> Minimize ( const Vector3<Real> & v1, const Vector3<Real> & v2 ) 
{
	return Vector3<Real>( v1.x < v2.x ? v1.x : v2.x,
                          v1.y < v2.y ? v1.y : v2.y,
                          v1.z < v2.z ? v1.z : v2.z );
}

/// Creates vector from maximal components of two another vectors. 
/** \relates Vector3
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors
 */
template <class Real>
inline Vector3<Real> Maximize ( const Vector3<Real> & v1, const Vector3<Real> & v2 ) 
{
	return Vector3<Real>( v1.x > v2.x ? v1.x : v2.x,
                          v1.y > v2.y ? v1.y : v2.y,
                          v1.z > v2.z ? v1.z : v2.z );
}

/// Performs dot product of two vectors. 
/** \relates Vector3
 * @param v1 - first vector.
 * @param v2 - second vector.
 * @return Returns result of dot product of two vectors.
 */
template <class Real>
inline Real DotProduct ( const Vector3<Real> & v1, const Vector3<Real> & v2 ) 
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// Performs cross product of two vectors. 
/** \relates Vector3
 * @param v1 - first vector.
 * @param v2 - second vector.
 * @return Returns result vector.
 */
template <class Real>
inline Vector3<Real> CrossProduct ( const Vector3<Real> & v1, const Vector3<Real> & v2 ) 
{
	Vector3<Real> result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

/// Computes normal for the plane, which contains three given points. 
/** \relates Vector3
 * @param A - first point.
 * @param B - second point.
 * @param C - third point.
 * @return Returns computed normal.
 */
template <class Real>
inline Vector3<Real> BuildNormal(const Vector3<Real> & A, const Vector3<Real> & B, const Vector3<Real> & C)
{
	return Normalize( CrossProduct( B - A, C - A ) );
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector3
 * This function performs rough computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEquals ( const Vector3<Real> & v1, const Vector3<Real> & v2, const Real radius ) 
{
	return abs(v1.x-v2.x) < radius &&
		   abs(v1.y-v2.y) < radius &&
		   abs(v1.z-v2.z) < radius;
}

/// Determines, if two points (vectors) are located within given radius. 
/** \relates Vector3
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphere ( const Vector3<Real> & v1, const Vector3<Real> & v2, const Real radius ) 
{
	return GetSquareLength(v1-v2) < radius * radius;
}

/// Determines, if two points (vectors) are located within given radius. 
/** \relates Vector3
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius_sq - square radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphereSq ( const Vector3<Real> & v1, const Vector3<Real> & v2, const Real radius_sq ) 
{
	return GetSquareLength(v1-v2) < radius_sq;
}

/// Zeros all vector's components, if they all are lower than given limit.
/** \relates Vector3
 * @param v - vector.
 * @param limit - limit's value.
 */
template <class Real>
inline void DropToZero ( Vector3<Real> & v, const Real limit ) 
{
	if ( abs(v.x) < limit && abs(v.y) < limit && abs(v.z) < limit )
		v.x = v.y = v.z = Real(0);
}


///////////////////////////////////////////////////////////////////////////
// 4D Vector
///////////////////////////////////////////////////////////////////////////

/// Vector4 represents four dimensional template vector class.
/** 
 * @param 'Real' parameter defines vector components numeric type. 
 */
template <class Real>
class Vector4 
{

public:

	/// Default constructor.
	Vector4() {}

	/// Constructor with given component value.
	/**
	 *	@param xyzw - value of all vector's components. 
	 */
	Vector4( Real xyzw ) 
	{
		x = y = z = w = xyzw;
	}

	/// Constructor with given component values.
	/**
	 *	@param x_ - value of X component. 
	 *	@param y_ - value of Y component.
 	 *  @param z_ - value of Z component.
	 *  @param w_ - value of W component.
	 */
    Vector4( Real x_, Real y_, Real z_, Real w_ ) 
	{
	    x = x_;
	    y = y_;
	    z = z_;
		w = w_;
	}
    
	/// Casting operator.
	operator Vector4 & () 
	{
		return *this;
	}

    /// Casting operator.
	operator Real* () 
	{
		return (Real *) & x;
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) & x;
	}

    /// Addition assignment operator.
	Vector4<Real> & operator += ( const Vector4<Real> & v ) 
	{
	    x += v.x;
	    y += v.y;
		z += v.z;
		w += v.w;
	
		return *this;
	}

	/// Subtraction assignment operator.
	Vector4<Real> & operator -= ( const Vector4<Real> & v ) 
	{
	    x -= v.x;
	    y -= v.y;
		z -= v.z;
		w -= v.w;
	
		return *this;
	}

	/// Multiplication assignment operator.
	Vector4<Real> & operator *= ( Real f ) 
	{
	    x *= f;
	    y *= f;
	    z *= f;
		w *= f;
	
		return *this;
	}

	/// Division assignment operator.
	Vector4<Real> & operator /= ( Real f ) 
	{
	    Real fInv = Real(1) / f;
	
		x *= fInv;
	    y *= fInv;
	    z *= fInv;
		w *= fInv;

		return *this;
	}

    /// Unary plus operator.
	Vector4<Real> operator + () const 
	{
		return *this;
	}

	/// Unary negation operator.
	Vector4<Real> operator - () const 
	{
		return Vector4<Real>(-x, -y, -z, -w);
	}

    /// Binary addition operator.
	Vector4<Real> operator + ( const Vector4<Real> & v ) const 
	{
		return Vector4<Real>(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	/// Binary subtraction operator.
	Vector4<Real> operator - ( const Vector4<Real> & v ) const 
	{
		return Vector4<Real>(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	/// Binary multiplication operator.
	Vector4<Real> operator * ( Real f ) const 
	{
		return Vector4<Real>(x * f, y * f, z * f, w * f);
	}

	/// Binary division operator.
	Vector4<Real> operator / ( Real f ) const 
	{
	    Real fInv = Real(1) / f;
	
		return Vector4<Real>(x * fInv, y * fInv, z * fInv, w * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Vector4<Real> & v ) const 
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	/// Inequality comparison operator.
	Bool operator != ( const Vector4<Real> & v ) const 
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	/// Normalizes this vector.
	/**
	 * @return reference to this.
	 */
	Vector4<Real> & Normalize()
	{
		return *this / GetLength(*this);
	}

	/// X vector's component.
	Real x;

	/// Y vector's component.
	Real y;
	
	/// Z vector's component.
	Real z;

	/// W vector's component.
	Real w;
};

/// \relates Vector4
typedef Vector4<Fixed> Vector4fx;

/// \relates Vector4
typedef Vector4<Float> Vector4fl;

/// \relates Vector4
typedef Vector4<Double> Vector4dl;

/// Binary multiplication operator.
/** \relates Vector4 */
template <class Real>
Vector4<Real> operator * ( Real f, const Vector4<Real> & v ) 
{
    return Vector4<Real>(f * v.x, f * v.y, f * v.z, f * v.w);
}

/// Binary multiplication operator.
/**  \relates Vector4 */
template <class Real>
Vector4<Real> operator * ( const Vector4<Real> & v1, const Vector4<Real> & v2 ) 
{
	return Vector4<Real>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

/// Computes square length of vector.
/** \relates Vector4
 * @param v - source vector.
 * @return Returns square length of vector value.
 */
template <class Real>
inline Real GetSquareLength ( const Vector4<Real> & v ) 
{
	return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

/// Computes length of vector.
/** \relates Vector4
 * @param v - source vector.
 * @return Returns length of vector value.
 */
template <class Real>
inline Real GetLength ( const Vector4<Real> & v ) 
{
	return Sqrt(GetSquareLength(v));
}

/// Normalizes vector. 
/** \relates Vector4
 * @param v - source vector.
 * @return Returns normalized vector.
 */
template <class Real>
inline Vector4<Real> Normalize ( const Vector4<Real> & v ) 
{
	return v / GetLength(v);
}

/// Finds out minimal vector's component value.
/** \relates Vector4
 * @param v - vector.
 * @return Returns minimal vector component value.
 */
template <class Real>
inline Real Min ( const Vector4<Real> & v ) 
{
   Real result = v.x;

   if ( v.y < result )
	   result = v.y;
   if ( v.z < result )
	   result = v.z;
   if ( v.w < result )
	   result = v.w;
   
   return result;
}

/// Finds out maximal vector's component value.
/** \relates Vector4
 * @param v - vector.
 * @return Returns maximal vector's component value.
 */
template <class Real>
inline Real Max ( const Vector4<Real> & v ) 
{
   Real result = v.x;

   if ( result < v.y )
	   result = v.y;
   if ( result < v.z )
	   result = v.z;
   if ( result < v.w )
	   result = v.w;

   return result;
}

/// Creates vector from minimal components of two another vectors. 
/** \relates Vector4
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors.
 */
template <class Real>
inline Vector4<Real> Minimize ( const Vector4<Real> & v1, const Vector4<Real> & v2 ) 
{
	return Vector4<Real>( v1.x < v2.x ? v1.x : v2.x,
                          v1.y < v2.y ? v1.y : v2.y,
                          v1.z < v2.z ? v1.z : v2.z,
						  v1.w < v2.w ? v1.w : v2.w);
}

/// Creates vector from maximal components of two another vectors.
/** \relates Vector4
 * @param v1 - first source vector.
 * @param v2 - second source vector.
 * @return Returns vector created from minimal components of two another vectors.
 */
template <class Real>
inline Vector4<Real> Maximize ( const Vector4<Real> & v1, const Vector4<Real> & v2 ) 
{
	return Vector4<Real>( v1.x > v2.x ? v1.x : v2.x,
                          v1.y > v2.y ? v1.y : v2.y,
                          v1.z > v2.z ? v1.z : v2.z,
						  v1.w > v2.w ? v1.w : v2.w);
}

/// Performs dot product of two vectors. 
/** \relates Vector4
 * @param v1 - first vector.
 * @param v2 - second vector.
 * @return Returns result of dot product of two vectors.
 */
template <class Real>
inline Real DotProduct ( const Vector4<Real> & v1, const Vector4<Real> & v2 ) 
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector4
 * This function performs rough computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEquals ( const Vector4<Real> & v1, const Vector4<Real> & v2, const Real radius ) 
{
	return abs(v1.x-v2.x) < radius &&
		   abs(v1.y-v2.y) < radius &&
		   abs(v1.z-v2.z) < radius &&
		   abs(v1.w-v2.w) < radius;
}

/// Determines, if two points (vectors) are located within given radius. 
/** \relates Vector4
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius - radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphere ( const Vector4<Real> & v1, const Vector4<Real> & v2, const Real radius ) 
{
	return GetSquareLength(v1-v2) < radius * radius;
}

/// Determines, if two points (vectors) are located within given radius.
/** \relates Vector4
 * This function performs more accurate computing.
 * @param v1 - first point (vector).
 * @param v2 - second point (vector).
 * @param radius_sq - square radius.
 * @return Returns True, if two points are within given radius, else - False.
 */
template <class Real>
inline Bool NearlyEqualsSphereSq ( const Vector4<Real> & v1, const Vector4<Real> & v2, const Real radius_sq ) 
{
	return GetSquareLength(v1-v2) < radius_sq;
}

/// Zeros all vector's components, if they all are lower than given limit.
/** \relates Vector4
 * @param v - vector.
 * @param limit - limit's value.
 */
template <class Real>
inline void DropToZero ( Vector4<Real> & v, const Real limit ) 
{
	if ( abs(v.x) < limit && abs(v.y) < limit && abs(v.z) < limit && abs(v.w) < limit)
		v.x = v.y = v.z = v.w = Real(0);
}

///////////////////////////////////////////////////////////////////////////
// 3D Matrix
///////////////////////////////////////////////////////////////////////////

/// Matrix3  represents template 3 by 3 matrix class.
/** 
 * The content of matrix is in column-major order.
 * @param 'Real' parameter defines matrix components numeric type. 
 */
template<class Real>
class Matrix3 
{

public:

	/// Default constructor.
	Matrix3() {}

	/// Constructor with given component value.
	/**
	 *	@param f11..f33 - values of respective matrix components. 
	 */
	Matrix3(Real f11, Real f21, Real f31,
			Real f12, Real f22, Real f32,
			Real f13, Real f23, Real f33) 
	{
			_11 = f11; _21 = f21; _31 = f31;
			_12 = f12; _22 = f22; _32 = f32;
			_13 = f13; _23 = f23; _33 = f33;
	}

	/// Access grants operator.
	/**
	 * @param Col - column's number (numeration begins from 0).
	 * @param Row - row's number (numeration begins from 0).
	 * @return Returns respective element's value.
	 */
	Real & operator () ( Int Col, Int Row ) 
	{
		return *((&_11)+Col+(Row << 2));
	}

	/// Access grants operator.
	/**
	 * @param Col - column's number (numeration begins from 0).
	 * @param Row - row's number (numeration begins from 0).
	 * @return Returns respective element's value.
	 */
	Real operator () ( Int Col, Int Row ) const 
	{
		return *((&_11)+Col+(Row << 2));
	}

	/// Casting operator.
	operator Real* () 
	{
		return (Real *)&_11;
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) &_11;
	}

	/// Addition assignment operator.
	Matrix3 & operator += ( const Matrix3 & tm ) 
	{
		_11 += tm._11; _21 += tm._21; _31 += tm._31;
		_12 += tm._12; _22 += tm._22; _32 += tm._32; 
		_13 += tm._13; _23 += tm._23; _33 += tm._33; 

		return *this;
	}

	/// Subtraction assignment operator.
	Matrix3 & operator -= ( const Matrix3 & tm ) 
	{
		_11 -= tm._11; _21 -= tm._21; _31 -= tm._31;
		_12 -= tm._12; _22 -= tm._22; _32 -= tm._32;
		_13 -= tm._13; _23 -= tm._23; _33 -= tm._33;

		return *this;
	}

	/// Multiplication assignment operator.
	Matrix3 & operator *= ( const Matrix3 & tm ) 
	{
		return Matrix3Multiply(*this, *this, tm);
	}

	/// Multiplication assignment operator.
	Matrix3 & operator *= ( Real f ) 
	{
		_11 *= f; _21 *= f; _31 *= f; 
		_12 *= f; _22 *= f; _32 *= f; 
		_13 *= f; _23 *= f; _33 *= f;
	
		return *this;
	}

	/// Division assignment operator.
	Matrix3 & operator /= ( Real f ) 
	{
		Real fInv = Real(1) / f;
	
		_11 *= fInv; _21 *= fInv; _31 *= fInv;
		_12 *= fInv; _22 *= fInv; _32 *= fInv;
		_13 *= fInv; _23 *= fInv; _33 *= fInv; 

		return *this;
	}

	/// Unary plus operator.
	Matrix3 operator + () const 
	{
		return *this;
	}

	/// Unary negation operator.
	Matrix3 operator - () const 
	{
		return Matrix3<Real>(-_11, -_21, -_31,
							 -_12, -_22, -_32,
							 -_13, -_23, -_33);
	}

	/// Binary addition operator.
	Matrix3 operator + ( const Matrix3 & tm ) const 
	{
		return Matrix3(_11 + tm._11, _21 + tm._21, _31 + tm._31,
			_12 + tm._12, _22 + tm._22, _32 + tm._32,
			_13 + tm._13, _23 + tm._23, _33 + tm._33);
	}

	/// Binary subtraction operator.	
	Matrix3 operator - ( const Matrix3 & tm ) const 
	{
		return Matrix3<Real>(_11 - tm._11, _21 - tm._21, _31 - tm._31,
			_12 - tm._12, _22 - tm._22, _32 - tm._32,
			_13 - tm._13, _23 - tm._23, _33 - tm._33);
	}

	/// Binary multiplication operator.
	Matrix3 operator * ( const Matrix3 & tm ) const 
	{
		Matrix3 result;
	
		return Matrix3Multiply(result, *this, tm);
	}

	/// Binary multiplication operator.
	Matrix3 operator * ( Real f ) const 
	{
		return Matrix3<Real>(_11 * f, _21 * f, _31 * f,
			_12 * f, _22 * f, _32 * f,
			_13 * f, _23 * f, _33 * f);
	}

	/// Binary division operator.
	Matrix3 operator / ( Real f ) const 
	{
		Real fInv = Real(1) / f;
		return Matrix3<Real>(_11 * fInv, _21 * fInv, _31 * fInv,
			_12 * fInv, _22 * fInv, _32 * fInv,
			_13 * fInv, _23 * fInv, _33 * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Matrix3 & tm ) const 
	{
		return 0 == memcmp(this, &tm, sizeof(Matrix3<Real>));
	}

	/// Inequality comparison operator.
	Bool operator != ( const Matrix3 & tm ) const 
	{
		return 0 != memcmp(this, &tm, sizeof(Matrix3<Real>));
	}

	/// Transposes the matrix.
	/**
	 * @return Returns result matrix.
	 */
	Matrix3<Real> & Matrix3Transpose ()
	{
		swap(_12,_21);
		swap(_13,_31);
		swap(_23,_32);

		return *this;
	}

	/// Zeros the translation portion of matrix.
	/**
	 * @return Returns result transformation matrix with zero translation portion.
	 */
	Matrix3<Real> & NoTranslation() 
	{
		_13 = Real(0); 
		_23 = Real(0);

		return *this;
	}

	/// Matrix element (first digit - column's number, second digit - row's number).
	Real _11, _21, _31,
	     _12, _22, _32,
	     _13, _23, _33;

};

/// \relates Matrix3
typedef Matrix3<Fixed> Matrix3fx;

/// \relates Matrix3
typedef Matrix3<Float> Matrix3fl;

/// \relates Matrix3
typedef Matrix3<Double> Matrix3dl;

/// Binary multiplication operator.
/** \relates Matrix3 */
template <class Real>
Matrix3<Real> operator * ( Real f, const Matrix3<Real> & tm ) 
{
	return Matrix3<Real>(f * tm._11, f * tm._21, f * tm._31, 
		f * tm._12, f * tm._22, f * tm._32, 
		f * tm._13, f * tm._23, f * tm._33);
}

/// Zeros all elements of matrix.
/** \relates Matrix3
 * @param tm - transformation matrix.
 */
template <class Real> 
inline void ZeroMatrix3 ( Matrix3<Real> & tm )
{
	memset(&tm._11, 0, sizeof(Real)*9);
} 

/// Creates Zero matrix (all elements = 0).
/** \relates Matrix3
 * @return Returns Zero matrix.
 */
template <class Real>
inline Matrix3<Real> ZeroMatrix3 () 
{
	Matrix3<Real> result;

	ZeroMatrix3(result);

	return result;
} 

/// Set matrix to the Identity matrix.
/** \relates Matrix3
 * @param tm - source transformation matrix.
 */
template <class Real>
inline void IdentityMatrix3 ( Matrix3<Real> & tm ) 
{
	ZeroMatrix3(tm);

	tm._11 = Real(1);
	tm._22 = Real(1);
	tm._33 = Real(1);
} 

/// Creates Identity matrix.
/** \relates Matrix3
 * @return Returns Identity matrix.
 */
template <class Real>
inline Matrix3<Real> IdentityMatrix3() 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);

	return result;
} 

/// Performs full multiplication of two matrices.
/** \relates Matrix3
 * @param result - matrix to store result. 
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix3<Real> & Matrix3Multiply ( Matrix3<Real> & result, const Matrix3<Real> & a, const Matrix3<Real> & b );

/// Performs full multiplication of two matrices.
/** \relates Matrix3
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix3<Real> Matrix3Multiply ( const Matrix3<Real> & a, const Matrix3<Real> & b );

/// Performs fast multiplication of two matrices. 
/** \relates Matrix3
 * This function doesn't multiply zero portion of matrices 
 * (_31,_32 elements) in optimization purposes.
 * @param result - matrix to store result. 
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix3<Real> & Matrix3MultiplyFast ( Matrix3<Real> & result, const Matrix3<Real> & a, const Matrix3<Real> & b );

/// Performs fast multiplication of two matrices.
/** \relates Matrix3
 * This function doesn't multiply zero portion of matrices 
 * (_31,_32 elements) in optimization purposes.
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix3<Real> Matrix3MultiplyFast ( const Matrix3<Real> & a, const Matrix3<Real> & b );

/// Transposes the matrix.
/** \relates Matrix3
 * @param result - matrix to store result.
 * @param tm - source transformation matrix.
 * @return Returns result matrix.
 */
template <class Real>
inline Matrix3<Real> & Matrix3Transpose ( Matrix3<Real> & result, const Matrix3<Real> & tm )
{
	result._11 = tm._11;	result._21 = tm._12;	result._31 = tm._13;
	result._12 = tm._21;	result._22 = tm._22;	result._32 = tm._23;
	result._13 = tm._31;	result._23 = tm._32;	result._33 = tm._33;

	return result;
}

/// Transposes the matrix.
/** \relates Matrix3
 * @param tm - source transformation matrix.
 * @return Returns result matrix.
 */
template <class Real>
inline Matrix3<Real> Matrix3Transpose ( const Matrix3<Real> & tm )
{
	Matrix3<Real> result;

	result._11 = tm._11;	result._21 = tm._12;	result._31 = tm._13;
	result._12 = tm._21;	result._22 = tm._22;	result._32 = tm._23;
	result._13 = tm._31;	result._23 = tm._32;	result._33 = tm._33;

	return result;
}

/// Transforms vector by matrix.
/** \relates Vector3
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns transformed vector.
 */
template <class Real>
inline Vector3<Real> TransformVector3 ( const Vector3<Real> & v, const Matrix3<Real> & tm ) 
{
	Vector3<Real> result;

	result.x = v.x*tm._11 + v.y*tm._12 + v.z*tm._13;
	result.y = v.x*tm._21 + v.y*tm._22 + v.z*tm._23;
	result.z = v.x*tm._31 + v.y*tm._32 + v.z*tm._33;

	return result;
}

/// Transforms vector by matrix.
/** \relates Vector2
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns transformed vector.
 */
template <class Real>
inline Vector2<Real> TransformVector2 ( const Vector2<Real> & v, const Matrix3<Real> & tm ) 
{
	Vector2<Real> result;

	result.x = v.x*tm._11 + v.y*tm._12 + tm._13;
	result.y = v.x*tm._21 + v.y*tm._22 + tm._23;

	return result;
}

/// Rotates vector by matrix.
/** \relates Vector2
 * This function don't use translation portion of matrix (_13, _23 )
 * to transform vector in optimization purposes.
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns rotated vector.
 */
template <class Real>
inline Vector2<Real> RotateVector2 ( const Vector2<Real> & v, const Matrix3<Real> & tm ) 
{
	Vector2<Real> result;

	result.x = v.x*tm._11 + v.y*tm._12;
	result.y = v.x*tm._21 + v.y*tm._22;

	return result;
}

/// Creates rotation matrix from angle in 2D.
/** \relates Matrix3
 * @param rads - rotation angle.
 * @return Returns rotation matrix.
 */
template <class Real>
inline Matrix3<Real> RotationMatrix3 ( Real rads ) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);

	Real cos_a = Cos( rads );
	Real sin_a = Sin( rads );

	result._11 =  cos_a;
	result._12 =  sin_a;
	result._21 = -sin_a;
	result._22 =  cos_a;
	
	return result;
}

/// Creates translation matrix in 2D.
/** \relates Matrix3
 * @param dx - translation by X axis.
 * @param dy - translation by Y axis.
 * @return Returns translation matrix.
 */
template <class Real>
inline Matrix3<Real> TranslationMatrix3 ( Real dx, Real dy ) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);

	result._13 = dx;
	result._23 = dy;

	return result;
} 

/// Creates translation matrix in 2D.
/** \relates Matrix3
 * @param v - 2D translation vector.
 * @return Returns translation matrix.
 */
template <class Real>
inline Matrix3<Real> TranslationMatrix3 ( const Vector2<Real> & v ) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);

	result._13 = v[0];
	result._23 = v[1];

	return result;
}

/// Zeros the translation portion of matrix.
/** \relates Matrix3
 * @param result - transformation matrix to store result.
 * @param tm - source transformation matrix.
 * @return Returns result transformation matrix with zero translation portion.
 */
template <class Real>
inline Matrix3<Real> & NoTranslation( Matrix3<Real> & result, const Matrix3<Real> & tm ) 
{
	result = tm;

	result._13 = Real(0); 
	result._23 = Real(0);
	
	return result;
} 

/// Zeros the translation portion of matrix.
/** \relates Matrix3
 * @param tm - source transformation matrix.
 * @return Returns result transformation matrix with zero translation portion.
 */
template <class Real>
inline Matrix3<Real> NoTranslation( const Matrix3<Real> & tm ) 
{
	Matrix3<Real> result = tm;

	result._13 = Real(0); 
	result._23 = Real(0);

	return result;
}

/// Creates translation vector from transformation matrix.
/** \relates Matrix3
 * @param tm - transformation matrix.
 * @return Returns translation vector.
 */
template <class Real>
inline Vector2<Real> GetTranslation ( const Matrix3<Real> & tm ) 
{
	return Vector2<Real>(tm._13, tm._23);
}

/// Creates uniform scaling matrix.
/** \relates Matrix3
 * @param size - scaling factor.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix3<Real> ScalingMatrix3 ( Real size ) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);
	
	result._11 = size;
	result._22 = size;
	
	return result;
}

/// Creates scaling matrix.
/** \relates Matrix3
 * @param a - scaling factor by X axis.
 * @param b - scaling factor by Y axis.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix3<Real> ScalingMatrix3 ( Real a, Real b) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);
	
	result._11 = a;
	result._22 = b;
	
	return result;
}

/// Creates scaling matrix.
/** \relates Matrix3
 * @param v - scaling vector.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix3<Real> ScalingMatrix3 ( const Vector2<Real> & v ) 
{
	Matrix3<Real> result;

	IdentityMatrix3(result);
	
	result._11 = v.x;
	result._22 = v.y;
	
	return result;
}



///////////////////////////////////////////////////////////////////////////
// 4D Matrix
///////////////////////////////////////////////////////////////////////////


///  Matrix4 represents template 4 by 4 matrix class.
/** 
 * The content of matrix is in column-major order.
 * @param 'Real' parameter defines matrix components numeric type. 
 */
template<class Real>
class Matrix4 
{

public:

	/// Default constructor.
    Matrix4() {}

	/// Constructor with given component value.
	/**
	 *	@param f11..f44 - values of respective matrix components. 
	 */
    Matrix4(Real f11, Real f21, Real f31, Real f41,
		    Real f12, Real f22, Real f32, Real f42,
			Real f13, Real f23, Real f33, Real f43,
			Real f14, Real f24, Real f34, Real f44) 
	{
	    _11 = f11; _21 = f21; _31 = f31; _41 = f41;
	    _12 = f12; _22 = f22; _32 = f32; _42 = f42;
		_13 = f13; _23 = f23; _33 = f33; _43 = f43;
		_14 = f14; _24 = f24; _34 = f34; _44 = f44;
	}

	/// Access grants operator.
	/**
	 * @param Col - column's number (numeration begins from 0).
	 * @param Row - row's number (numeration begins from 0).
	 * @return Returns respective element's value.
	 */
	Real & operator () ( Int Col, Int Row ) 
	{
		return *((&_11)+Col+(Row << 2));
	}

	/// Access grants operator.
	/**
	 * @param Col - column's number (numeration begins from 0).
	 * @param Row - row's number (numeration begins from 0).
	 * @return Returns respective element's value.
	 */
	Real operator () ( Int Col, Int Row ) const 
	{
		return *((&_11)+Col+(Row << 2));
	}

    /// Casting operator.
	operator Real* () 
	{
		return (Real *)&_11;
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) &_11;
	}

	/// Addition assignment operator.
	Matrix4 & operator += ( const Matrix4 & tm ) 
	{
		_11 += tm._11; _21 += tm._21; _31 += tm._31; _41 = tm._41;
		_12 += tm._12; _22 += tm._22; _32 += tm._32; _42 = tm._42;
		_13 += tm._13; _23 += tm._23; _33 += tm._33; _43 = tm._43;
		_14 += tm._14; _24 += tm._24; _34 += tm._34; _44 = tm._44;

		return *this;
	}

	/// Subtraction assignment operator.
	Matrix4 & operator -= ( const Matrix4 & tm ) 
	{
		_11 -= tm._11; _21 -= tm._21; _31 -= tm._31; _41 -= tm._41;
		_12 -= tm._12; _22 -= tm._22; _32 -= tm._32; _42 -= tm._42;
		_13 -= tm._13; _23 -= tm._23; _33 -= tm._33; _43 -= tm._43;
		_14 -= tm._14; _24 -= tm._24; _34 -= tm._34; _44 -= tm._44;

		return *this;
	}

    /// Multiplication assignment operator.
	Matrix4 & operator *= ( const Matrix4 & tm ) 
	{
		return Matrix4Multiply(*this, *this, tm);
	}

	/// Multiplication assignment operator.
	Matrix4 & operator *= ( Real f ) 
	{
	    _11 *= f; _21 *= f; _31 *= f; _41 *= f;
	    _12 *= f; _22 *= f; _32 *= f; _42 *= f;
	    _13 *= f; _23 *= f; _33 *= f; _43 *= f;
		_14 *= f; _24 *= f; _34 *= f; _44 *= f;
	
		return *this;
	}

	/// Division assignment operator.
	Matrix4 & operator /= ( Real f ) 
	{
	    Real fInv = Real(1) / f;
	
		_11 *= fInv; _21 *= fInv; _31 *= fInv; _41 *= fInv;
	    _12 *= fInv; _22 *= fInv; _32 *= fInv; _41 *= fInv;
	    _13 *= fInv; _23 *= fInv; _33 *= fInv; _41 *= fInv;
		_14 *= fInv; _24 *= fInv; _34 *= fInv; _44 *= fInv;

		return *this;
	}

    /// Unary plus operator.
	Matrix4 operator + () const 
	{
		return *this;
	}

	/// Unary negation operator.
	Matrix4 operator - () const 
	{
	    return Matrix4<Real>(-_11, -_21, -_31, -_41,
	                         -_12, -_22, -_32, -_42,
                             -_13, -_23, -_33, -_43,
							 -_14, -_24, -_34, -_44);
	}

	/// Binary addition operator.
	Matrix4 operator + ( const Matrix4 & tm ) const 
	{
		return Matrix4(_11 + tm._11, _21 + tm._21, _31 + tm._31, _41 + tm._41,
			_12 + tm._12, _22 + tm._22, _32 + tm._32, _42 + tm._42,
			_13 + tm._13, _23 + tm._23, _33 + tm._33, _43 + tm._43,
			_14 + tm._14, _24 + tm._24, _34 + tm._34, _44 + tm._44);

	}

	/// Binary subtraction operator.	
	Matrix4 operator - ( const Matrix4 & tm ) const 
	{
		return Matrix4<Real>(_11 - tm._11, _21 - tm._21, _31 - tm._31, _41 - tm._41,
			_12 - tm._12, _22 - tm._22, _32 - tm._32, _42 - tm._42,
			_13 - tm._13, _23 - tm._23, _33 - tm._33, _43 - tm._43,
			_14 - tm._14, _24 - tm._24, _34 - tm._34, _44 - tm._44);
	}

	/// Binary multiplication operator.
	Matrix4 operator * ( const Matrix4 & tm ) const 
	{
		Matrix4 result;
	
		return Matrix4Multiply(result, *this, tm);
	}

	/// Binary multiplication operator.
	Matrix4 operator * ( Real f ) const 
	{
	    return Matrix4<Real>(_11 * f, _21 * f, _31 * f, _41 * f,
                             _12 * f, _22 * f, _32 * f, _42 * f,
                             _13 * f, _23 * f, _33 * f, _43 * f,
							 _14 * f, _24 * f, _34 * f, _44 * f);
	}

	/// Binary division operator.
	Matrix4 operator / ( Real f ) const 
	{
	    Real fInv = Real(1) / f;
	
		return Matrix4<Real>(_11 * fInv, _21 * fInv, _31 * fInv, _41 * fInv,
                             _12 * fInv, _22 * fInv, _32 * fInv, _42 * fInv,
                             _13 * fInv, _23 * fInv, _33 * fInv, _43 * fInv,
							 _14 * fInv, _24 * fInv, _34 * fInv, _44 * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Matrix4 & tm ) const 
	{
	    return 0 == memcmp(this, &tm, sizeof(Matrix4<Real>));
	}

	/// Inequality comparison operator.
	Bool operator != ( const Matrix4 & tm ) const 
	{
		return 0 != memcmp(this, &tm, sizeof(Matrix4<Real>));
	}
	
	/// Transposes the matrix.
	/**
	 * @return Returns result matrix.
	 */
	Matrix4<Real> & Matrix4Transpose ()
	{
		swap(_12,_21);
		swap(_13,_31);
		swap(_14,_41);
		swap(_23,_32);
		swap(_24,_42);
		swap(_34,_43);

		return *this;
	}

	/// Zeros the translation portion of matrix.
	/**
	 * @return Returns result transformation matrix with zero translation portion.
	 */
	Matrix4<Real> & NoTranslation() 
	{
		_14 = Real(0); 
		_24 = Real(0);
		_34 = Real(0);

		return *this;
	}

	/// Matrix element (first digit - column's number, second digit - row's number).
	Real _11, _21, _31, _41,
		 _12, _22, _32, _42,
		 _13, _23, _33, _43,
		 _14, _24, _34, _44; // <- translate portion in this row.

};

/// \relates Matrix4
typedef Matrix4<Fixed> Matrix4fx;

/// \relates Matrix4
typedef Matrix4<Float> Matrix4fl;

/// \relates Matrix4
typedef Matrix4<Double> Matrix4dl;

/// Binary multiplication operator.
/** \relates Matrix4 */
template <class Real>
Matrix4<Real> operator * ( Real f, const Matrix4<Real> & tm ) 
{
    return Matrix4<Real>(f * tm._11, f * tm._21, f * tm._31, f * tm._41,
						 f * tm._12, f * tm._22, f * tm._32, f * tm._42,
						 f * tm._13, f * tm._23, f * tm._33, f * tm._43,
						 f * tm._14, f * tm._24, f * tm._34, f * tm._44);
}

/// Zeros all elements of matrix.
/** \relates Matrix4
 * @param tm - transformation matrix.
 */
template <class Real>
inline void ZeroMatrix4 ( Matrix4<Real> & tm ) 
{
    memset(&tm._11, 0, sizeof(Real)*16);
}

/// Creates Zero matrix (all elements = 0).
/** \relates Matrix4
 * @return Returns Zero matrix.
 */
template <class Real>
inline Matrix4<Real> ZeroMatrix4 () 
{
	Matrix4<Real> result;

	ZeroMatrix4(result);
	
	return result;
}

/// Set matrix to the Identity matrix.
/** \relates Matrix4
 * @param tm - source transformation matrix.
 */
template <class Real>
inline void IdentityMatrix4 ( Matrix4<Real> & tm ) 
{
	ZeroMatrix4(tm);

	tm._11 = Real(1);
	tm._22 = Real(1);
	tm._33 = Real(1);
	tm._44 = Real(1);
}

/// Creates Identity matrix.
/** \relates Matrix4
 * @return Returns Identity matrix.
 */
template <class Real>
inline Matrix4<Real> IdentityMatrix4() 
{
    Matrix4<Real> result;
	IdentityMatrix4(result);
    return result;
}

/// Performs full multiplication of two matrices.
/** \relates Matrix4
 * @param result - matrix to store result. 
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix4<Real> & Matrix4Multiply ( Matrix4<Real> & result, const Matrix4<Real> & a, const Matrix4<Real> & b );

/// Performs full multiplication of two matrices.
/** \relates Matrix4
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix4<Real> Matrix4Multiply ( const Matrix4<Real> & a, const Matrix4<Real> & b );

/// Performs fast multiplication of two matrices.
/** \relates Matrix4
 * This function doesn't multiply zero portion of matrices 
 * (_41,_42,_43 elements) in optimization purposes.
 * @param result - matrix to store result. 
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix4<Real> & Matrix4MultiplyFast ( Matrix4<Real> & result, const Matrix4<Real> & a, const Matrix4<Real> & b );

/// Performs fast multiplication of two matrices.
/** \relates Matrix4
 * This function doesn't multiply zero portion of matrices 
 * (_41,_42,_43 elements) in optimization purposes.
 * @param a - first matrix. 
 * @param b - second matrix. 
 * @return Returns result matrix.
 */
template <class Real>
Matrix4<Real> Matrix4MultiplyFast ( const Matrix4<Real> & a, const Matrix4<Real> & b );

/// Transposes the matrix.
/** \relates Matrix4
 * @param result - matrix to store result.
 * @param tm - source transformation matrix.
 * @return Returns result matrix.
 */
template <class Real>
inline Matrix4<Real> & Matrix4Transpose ( Matrix4<Real> & result, const Matrix4<Real> & tm )
{
	result._11 = tm._11;	result._21 = tm._12;	
	result._12 = tm._21;	result._22 = tm._22;
	result._13 = tm._31;	result._23 = tm._32;
	result._14 = tm._41;	result._24 = tm._42;

	result._31 = tm._13;	result._41 = tm._14;
	result._32 = tm._23;	result._42 = tm._24;
	result._33 = tm._33;	result._43 = tm._34;
	result._34 = tm._43;	result._44 = tm._44;

	return result;
}

/// Transposes the matrix.
/** \relates Matrix4
 * @param tm - source transformation matrix.
 * @return Returns result matrix.
 */
template <class Real>
inline Matrix4<Real> Matrix4Transpose ( const Matrix4<Real> & tm )
{
	Matrix4<Real> result;

	result._11 = tm._11;	result._21 = tm._12;	
	result._12 = tm._21;	result._22 = tm._22;
	result._13 = tm._31;	result._23 = tm._32;
	result._14 = tm._41;	result._24 = tm._42;

	result._31 = tm._13;	result._41 = tm._14;
	result._32 = tm._23;	result._42 = tm._24;
	result._33 = tm._33;	result._43 = tm._34;
	result._34 = tm._43;	result._44 = tm._44;

	return result;
}

/// Transforms vector by matrix.
/** \relates Vector4
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns transformed vector.
 */
template <class Real>
inline Vector4<Real> TransformVector4 ( const Vector4<Real> & v, const Matrix4<Real> & tm ) 
{
	Vector4<Real> result;

    result.x = v.x*tm._11 + v.y*tm._12 + v.z*tm._13 + v.w*tm._14;
    result.y = v.x*tm._21 + v.y*tm._22 + v.z*tm._23 + v.w*tm._24;
    result.z = v.x*tm._31 + v.y*tm._32 + v.z*tm._33 + v.w*tm._34;
	result.w = v.x*tm._41 + v.y*tm._42 + v.z*tm._43 + v.w*tm._44;
	
	return result;

}

/// Transforms vector by matrix.
/** \relates Vector3
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns transformed vector.
 */
template <class Real>
inline Vector3<Real> TransformVector3 ( const Vector3<Real> & v, const Matrix4<Real> & tm ) 
{
	Vector3<Real> result;

	result.x = v.x*tm._11 + v.y*tm._12 + v.z*tm._13 + tm._14;
    result.y = v.x*tm._21 + v.y*tm._22 + v.z*tm._23 + tm._24;
    result.z = v.x*tm._31 + v.y*tm._32 + v.z*tm._33 + tm._34;

	return result;
}

/// Rotates vector by matrix.
/** \relates Vector3
 * This function don't use translation portion of matrix (_14, _24, _34)
 * to transform vector in optimization purposes.
 * @param v - source vector.
 * @param tm - transformation matrix.
 * @return Returns rotated vector.
 */
template <class Real>
inline Vector3<Real> RotateVector3 ( const Vector3<Real> & v, const Matrix4<Real> & tm ) 
{
	Vector3<Real> result;

	result.x = v.x*tm._11 + v.y*tm._12 + v.z*tm._13;
    result.y = v.x*tm._21 + v.y*tm._22 + v.z*tm._23;
    result.z = v.x*tm._31 + v.y*tm._32 + v.z*tm._33;

	return result;
} 

/// Creates rotation matrix from vector and angle.
/** \relates Matrix4
 * @param vDir - vector about which rotate.
 * @param fRads - rotation angle.
 * @return Returns rotation matrix.
 */
template <class Real>
Matrix4<Real> RotationMatrix4 ( const Vector3<Real> & vDir, Real fRads );

/// Creates rotation matrix about X axis.
/** \relates Matrix4
 * @param rads - rotation angle.
 * @return Returns rotation matrix.
 */
template <class Real>
inline Matrix4<Real> RotationXMatrix4 ( Real rads ) 
{
	Matrix4<Real> result;

	IdentityMatrix4(result);

	Real cos_a = Cos( rads );
	Real sin_a = Sin( rads );

    result._22 =  cos_a;
    result._32 =  sin_a;
    result._23 = -sin_a;
    result._33 =  cos_a;

	return result;
}

/// Creates rotation matrix about Y axis.
/** \relates Matrix4
 * @param rads - rotation angle.
 * @return Returns rotation matrix.
 */
template <class Real>
inline Matrix4<Real> RotationYMatrix4 ( Real rads ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);

	Real cos_a = Cos( rads );
	Real sin_a = Sin( rads );

    result._11 =  cos_a;
    result._31 = -sin_a;
    result._13 =  sin_a;
    result._33 =  cos_a;

	return result;
}
  
/// Creates rotation matrix about Z axis.
/** \relates Matrix4
 * @param rads - rotation angle.
 * @return Returns rotation matrix.
 */
template <class Real>
inline Matrix4<Real> RotationZMatrix4 ( Real rads ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);

	Real cos_a = Cos( rads );
	Real sin_a = Sin( rads );

    result._11  =  cos_a;
    result._21  =  sin_a;
    result._12  = -sin_a;
    result._22  =  cos_a;

	return result;
}

/// Creates translation matrix.
/** \relates Matrix4
 * @param dx - translation by X axis.
 * @param dy - translation by Y axis.
 * @param dz - translation by Z axis.
 * @return Returns translation matrix.
 */
template <class Real>
inline Matrix4<Real> TranslationMatrix4 ( Real dx, Real dy, Real dz ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);

	result._14 = dx;
	result._24 = dy;
	result._34 = dz;

	return result;
}

/// Creates translation matrix.
/** \relates Matrix4
 * @param v - translation vector.
 * @return Returns translation matrix.
 */
template <class Real>
inline Matrix4<Real> TranslationMatrix4 ( const Vector3<Real> & v ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);
	
	result._14 = v[0];
	result._24 = v[1];
	result._34 = v[2];

	return result;
}

/// Zeros the translation portion of matrix.
/** \relates Matrix4
 * @param result - transformation matrix to store result.
 * @param tm - source transformation matrix.
 * @return Returns result transformation matrix with zero translation portion.
 */
template <class Real>
inline Matrix4<Real> & NoTranslation( Matrix4<Real> & result, const Matrix4<Real> & tm ) 
{
	result = tm;

	result._14 = Real(0); 
	result._24 = Real(0);
	result._34 = Real(0);

	return result;
} 

// Zeros the translation portion of matrix.
/** \relates Matrix4
 * @param tm - transformation matrix.
 */
template <class Real>
inline Matrix4<Real> NoTranslation( const Matrix4<Real> & tm ) 
{
	Matrix4<Real> result = tm;

	result._14 = Real(0); 
	result._24 = Real(0);
	result._34 = Real(0);

	return result;
}

/// Creates translation vector from transformation matrix.
/** \relates Matrix4
 * @param tm - transformation matrix.
 * @return Returns translation vector.
 */
template <class Real>
inline Vector3<Real> GetTranslation ( const Matrix4<Real> & tm ) 
{
	return Vector3<Real>(tm._14, tm._24, tm._34);
}

/// Creates uniform scaling matrix.
/** \relates Matrix4
 * @param size - scaling factor.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix4<Real> ScalingMatrix4 ( Real size ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);

	result._11 = size;
	result._22 = size;
	result._33 = size;

	return result;
} 
  
/// Creates scaling matrix.
/** \relates Matrix4
 * @param a - scaling factor by X axis.
 * @param b - scaling factor by Y axis.
 * @param c - scaling factor by Z axis.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix4<Real> ScalingMatrix4 ( Real a, Real b, Real c) 
{
	Matrix4<Real> result;

	IdentityMatrix4(result);

	result._11 = a;
	result._22 = b;
	result._33 = c;

	return result;
}
  
/// Creates scaling matrix.
/** \relates Matrix4
 * @param v - scaling vector.
 * @return Returns scaling matrix.
 */
template <class Real>
inline Matrix4<Real> ScalingMatrix4 ( const Vector3<Real> & v ) 
{
    Matrix4<Real> result;

	IdentityMatrix4(result);

	result._11 = v.x;
	result._22 = v.y;
	result._33 = v.z;

	return result;
}

/// Creates matrix with orthonormalized basis.
/** \relates Matrix4
 * @param tm - source transformation matrix.
 * @return Returns matrix with orthonormalized basis.
 */
template <class Real>
Matrix4<Real> OrthonormalizedBasis4(const Matrix4<Real> & tm);

/// Creates matrix with orthonormalized basis.
/** \relates Matrix4
 * @param tm - source transformation matrix.
 */
template <class Real>
void OrthonormalizedBasis4(Matrix4<Real> & tm);


///////////////////////////////////////////////////////////////////////////
//    Quaternions
///////////////////////////////////////////////////////////////////////////


/// Quaternion represents template quaternion class.
/** 
 * @param 'Real' parameter defines quaternion's components numeric type. 
 */
template <class Real>
class Quaternion
{

public:

	/// Default constructor.
    Quaternion() {}

	/// Constructor with given component value.
	/**
	 *	@param xyzw - value of all quaternion's components. 
	 */
	Quaternion( Real xyzw ) 
	{
		x = y = z = w = xyzw;
	}
	
	/// Constructor with given component value.
	/**
	 *	@param x_ - value of X component. 
	 *	@param y_ - value of Y component.
	 *	@param z_ - value of Z component.
	 *	@param w_ - value of W component.
	 */
	Quaternion ( Real x_, Real y_, Real z_, Real w_ ) 
	{
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

    /// Casting operator.
	operator Real* () 
	{
		return (Real *) &x; 
	}

	/// Casting operator.
	operator const Real* () const 
	{
		return (const Real *) &x;
	}

    /// Addition assignment operator.
	Quaternion & operator += ( const Quaternion & q ) 
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
	
		return *this;
	}

	/// Subtraction assignment operator.
	Quaternion & operator -= ( const Quaternion & q ) 
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
	
		return *this;
	}

	/// Multiplication assignment operator.
	Quaternion & operator *= ( const Quaternion & q ) 
	{
		*this = QuaternionMultiply(*this, q);
	
		return *this;
	}

	/// Multiplication assignment operator.
	Quaternion & operator *= ( Real f ) 
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
	
		return *this;
	}

	/// Division assignment operator.
	Quaternion & operator /= ( Real f) 
	{
		Real fInv = Real(1) / f;
	
		x *= fInv;
		y *= fInv;
		z *= fInv;
		w *= fInv;

		return *this;
	}

    /// Unary plus operator.
	Quaternion  operator + () const 
	{
		return *this;
	}

	/// Unary negation operator.
	Quaternion  operator - () const 
	{
		return Quaternion(-x, -y, -z, -w); 
	}

    /// Binary addition operator.
	Quaternion operator + ( const Quaternion & q ) const 
	{
		return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w); 
	}

	/// Binary subtraction operator.	
	Quaternion operator - ( const Quaternion & q ) const 
	{
		return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w); 
	}

	/// Binary multiplication operator.
	Quaternion operator * ( const Quaternion & q ) const 
	{
		return QuaternionMultiply(*this, q);
	}

	/// Binary multiplication operator.
	Quaternion operator * ( Fixed f ) const 
	{
		return Quaternion(x * f, y * f, z * f, w * f);
	}

	/// Binary division operator.
	Quaternion operator / ( Fixed f ) const 
	{
		Fixed fInv = Real(1) / f;
	
		return Quaternion(x * fInv, y * fInv, z * fInv, w * fInv);
	}

	/// Equality comparison operator.
	Bool operator == ( const Quaternion & q ) const 
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	/// Inequality comparison operator.
	Bool operator != ( const Quaternion & q ) const 
	{
		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	/// Normalizes quaternion.
	/**
	 * @return Returns normalized quaternion.
	 */
	Quaternion<Real> & Normalize () 
	{
		return *this /= GetLength(*this);
	}

	/// X quaternion's component.
	Real x;

	/// Y quaternion's component.
	Real y;

	/// Z quaternion's component.
	Real z;

	/// W quaternion's component.
	Real w;

};

/// \relates Quaternion
typedef Quaternion<Fixed> Quaternionfx;

/// \relates Quaternion
typedef Quaternion<Float> Quaternionfl;

/// \relates Quaternion
typedef Quaternion<Double> Quaterniondl;

/// Binary multiplication operator.
/** \relates Quaternion */
template <class Real>
inline Quaternion<Real> operator * ( Real f, const Quaternion<Real> & q ) 
{
    return Quaternion<Real>(f * q.x, f * q.y, f * q.z, f * q.w);
}

/// Computes square length of quaternion.
/** \relates Quaternion
 * @param q - source quaternion.
 * @return Returns square length of vector value.
 */
template <class Real>
inline Real GetSquareLength ( const Quaternion<Real> & q ) 
{
	return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

/// Ñomputes length of quaternion.
/** \relates Quaternion
 * @param q - source quaternion.
 * @return Returns length of quaternion value.
 */
template <class Real>
inline Fixed GetLength ( const Quaternion<Real> & q ) 
{
	return Sqrt(GetSquareLength(q));
}

/// Normalizes quaternion.
/** \relates Quaternion
 * @param q - source quaternion.
 * @return Returns normalized quaternion.
 */
template <class Real>
inline Quaternion<Real> Normalize ( const Quaternion<Real> & q ) 
{
	return q / GetLength(q);
}

/// Converts a normalized axis and angle to a quaternion.
/** \relates Quaternion
 * @param v - normalized axis.
 * @param fRads - normalized axis.
 * @return Returns result quaternion.
 */
template <class Real>
inline Quaternion<Real> QuaternionFromRotation ( Vector3<Real> & v, Real fRads ) 
{
	Quaternion<Real> q;
    
	Real a = fRads/2;
	Real sin_a = Sin(a);

	q.x = sin_a * v.x;
    q.y = sin_a * v.y;
    q.z = sin_a * v.z;
    q.w = Cos(a);

	return q;
}

/// Converts a quaternion to a normalized axis and angle.
/** \relates Quaternion
 * @param q - quaternion.
 * @param v - vector to store a normalized axis.
 * @param fRads - angle.
 */
template <class Real>
inline void RotationFromQuaternion ( const Quaternion<Real> & q, Vector3<Real> & v, Real & fRads ) 
{
	Real a = ArcCos(q.w); 
	Real sin_a = Sin(a);

    v.x    = q.x / sin_a;
    v.y    = q.y / sin_a;
    v.z    = q.z / sin_a;

	fRads =  a * 2;
}

/// Performs multiplication of two quaternions {Q} = {A} * {B}.
/** \relates Quaternion
 * @param a - first quaternion. 
 * @param b - second quaternion. 
 * @return Returns result quaternion.
 */
template <class Real>
inline Quaternion<Real> QuaternionMultiply ( const Quaternion<Real> & a, const Quaternion<Real> & b ) 
{
	Quaternion<Real> result;
	
	result.w = a.w * b.w - (a.x * b.x + a.y * b.y + a.z * b.z);
	result.x = a.w * b.x + b.w * a.x +(a.y * b.z - b.y * a.z);
	result.y = a.w * b.y + b.w * a.y +(a.z * b.x - b.z * a.x);
	result.z = a.w * b.z + b.w * a.z +(a.x * b.y - b.x * a.y);

	return result;
}

/// Creates quaternion from angles.
/** \relates Quaternion
 * @param fYaw - yaw angle.
 * @param fPitch - pitch angle.
 * @param fRoll - roll angle.
 * @return Returns quaternion.
 */
template <class Real>
Quaternion<Real> QuaternionFromAngles ( Real fYaw, Real fPitch, Real fRoll );

/// Creates transformation matrix from quaternion.
/** \relates Quaternion
 * @param q - source quaternion.
 * @return Returns transformation matrix.
 */
template <class Real>
Matrix4<Real> MatrixFromQuaternion ( const Quaternion<Real> & q );

/// Creates quaternion from transformation matrix.
/** \relates Quaternion
 * @param tm - source transformation matrix.
 * @return Returns quaternion.
 */
template <class Real>
Quaternion<Real> QuaternionFromMatrix ( const Matrix4<Real> & tm );

/// Compute a quaternion which is the spherical linear interpolation between two other quaternions by fraction.
/** \relates Quaternion
 * @param a - first quaternion.
 * @param b - second quaternion.
 * @param fraction - interpolation fraction.
 * @return Returns result quaternion.
 */
template <class Real>
Quaternion<Real> QuaternionSlerp ( Quaternion<Real> a, Quaternion<Real> b, Real fraction );

} //namespace mdragon

#endif // __MD_VECMATH_H__
