/** \file
 *	Dummy 3d object. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_DUMMY_H__
#define __MD_DUMMY_H__

namespace mdragon
{

/// Dummy box objects class.
class DummyBox : public Basic3D
{
protected:

	/// Default constructor.
	DummyBox();

	/// Constructor with given min and max values of Bounding Box.
	/**
	 *	Creates dummy box object and set Bounding Box values.
	 *	@param min_ - Min value of Bounding Box
	 *	@param max_ - Max value of Bounding Box
	 */
	DummyBox(const Vector3fx & min_, const Vector3fx & max_);

	/// Constructor with given Bounding Box value.
	/**
	 *	Creates dummy box object and set Bounding Box values.
	 *	@param aab_ - Bounding Box
	 */
	DummyBox(const AABB & aab_);

	/// Destructor.
	~DummyBox();

public:
	
	/// Creates new DummyBox.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new DummyBox.
	 */
	static ObjRef<DummyBox> New()
	{
		return ObjRef<DummyBox>( new DummyBox );
	}

	/// Creates new DummyBox.
	/**
	 *	Call this function instead constructor calling.
	 *	@param min_ - Min value of Bounding Box
	 *	@param max_ - Max value of Bounding Box
	 *  @return Returns object reference to new DummyBox.
	 */
	static ObjRef<DummyBox> New( const Vector3fx & min_, const Vector3fx & max_ )
	{
		return ObjRef<DummyBox>( new DummyBox(min_, max_) );
	}

	/// Creates new DummyBox.
	/**
	 *	Call this function instead constructor calling.
	 *	@param aab_ - Bounding Box
	 *  @return Returns object reference to new DummyBox.
	 */
	static ObjRef<DummyBox> New( const AABB & aab_ )
	{
		return ObjRef<DummyBox>( new DummyBox(aab_) );
	}

	/// Returns DummyBox class id.
	/**
	 *  @return Returns DummyBox class id.
	 */
	Int GetClassID();

	/// Returns object's result transform matrix.
	/**
	 * @return Returns object's result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Builds and returns Bounding Box of this object.
	/**
	 *  @return Returns Bounding Box of this object.
	 */
	AABB GetBoundingBox();

	/// Sets Min value of Bounding Box for this dummy object.
	/**
	 *  @param min_ - Min value of Bounding Box.
	 */
	void SetMin(const Vector3fx & min_) { min = min_; }

	/// Sets Max value of Bounding Box for this dummy object
	/**
	 *  @param max_ - Max value of Bounding Box
	 */
	void SetMax(const Vector3fx & max_) { max = max_; }

	/// Returns Min value of Bounding Box for this dummy object
	/**
	 *  @return Returns Min value of Bounding Box
	 */
	Vector3fx GetMin() { return min; }

	/// Returns Max value of Bounding Box for this dummy object
	/**
	 *  @return Returns Max value of Bounding Box.
	 */
	Vector3fx GetMax() { return max; }

	/// Returns Position of this dummy object.
	/**
	 *  @return Returns Position of this dummy object.
	 */
	Vector3fx GetPosition();

	/// Relative transformation matrix
	Matrix4fx relative;

private:

	/// Bounding Box Min value
	Vector3fx min;

	/// Bounding Box Max value
	Vector3fx max;

};


/// DummySphere represents dummy sphere objects class.
class DummySphere : public Basic3D
{
protected:

	/// Default constructor.
	DummySphere();

	/// Constructor with given sphere radius.
	/**	
	 *	Creates dummy sphere object and set radius values.
	 *  @param radius_ - sphere radius.
	 */
	DummySphere(const Fixed & radius_);

	/// Destructor
	~DummySphere();

public:
	
	/// Creates new DummySphere.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new DummySphere.
	 */
	static ObjRef<DummySphere> New()
	{
		return ObjRef<DummySphere>( new DummySphere );
	}

	/// Creates new DummySphere.
	/**
	 *	Call this function instead constructor calling.
	 *  @param radius_ - sphere radius.
	 *  @return Returns object reference to new DummySphere.
	 */
	static ObjRef<DummySphere> New( const Fixed & radius_ )
	{
		return ObjRef<DummySphere>( new DummySphere(radius_) );
	}

	/// Returns DummySphere class id.
	/**
	 *  @return Returns DummySphere class id.
	 */
	Int GetClassID();

	/// Returns object's result transform matrix.
	/**
	 * @return Returns object's result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Sets dummy sphere radius.
	/**
	 *  @param radius_ - dummy sphere radius.
	 */
	void SetRadius(const Fixed & radius_) { radius = radius_; }

	/// Returns dummy sphere radius.
	/**
	 *  @return Returns dummy sphere radius.
	 */
	Fixed GetRadius() { return radius; }

	/// Returns position of this dummy object.
	/**
	 *  @return Returns position of this dummy object.
	 */
	Vector3fx GetPosition();

	/// Relative transformation matrix.
	Matrix4fx relative;

private:

	/// Dummy Sphere's radius.
	Fixed radius;

};

} //namespace mdragon

#endif  //__MD_DUMMY_H__
