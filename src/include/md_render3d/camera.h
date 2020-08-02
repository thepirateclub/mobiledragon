/** \file
 *	3d camera. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_CAMERA_H__
#define __MD_CAMERA_H__

namespace mdragon
{

///  Morphing frame for camera animation.
struct CamFrame 
{
	/// Frame time stamp	
	Int time;		

	/// Frame duration
	Int duration;	
	
	/// Position of camera
	Vector3fx pos;	
	
	/// Target point of camera
	Vector3fx target; 

	/// "Up" vector
	Vector3fx vWorldUp;
};


/// Camera state.
enum CamState	{
				/// Camera is in animation.
				CAM_ANIM,

				/// Manual camera control
				CAM_MANUAL
				};


/// 3d Camera.
/**
 *	Camera uses UVN-model.
 *	Control camera by setting it's position and target point.
 */

class Camera
{

public:

	/// Default constructor.
	Camera();

	/// Destructor.
	~Camera();
	
	/// Initializes camera. 
	/**
	 *	Have to be called before using Camera.
	 *  @param system_ - pointer to System class object.
	 */
	void Init(System *system_);

	/// Sets position and target point of camera.
	/**
	 *  @param pos_ - position of camera.
	 *  @param target_ - target point of camera.
	 *  @param vUp_ - Default "Up" vector for calculating U,V,N vectors. 
	 */
	inline void Set(const Vector3fx& pos_, const Vector3fx& target_, const Vector3fx& vUp_);

	/// Returns position of camera.
	/**
	 *  @return Returns position of camera.
	 */
	inline Vector3fx GetPos();

	/// Returns target point of camera.
	/**
	 *  @return Returns target point of camera.
	 */
	inline Vector3fx GetTarget();

	/// Returns normalized camera's direction vector.
	/**
	 *  @return Returns normalized camera's direction vector.
	 */
	inline Vector3fx GetDir();

	/// Returns normalized camera's "Left" vector.
	/**
	 *  @return Returns normalized camera's "Left" vector.
	 */
	inline Vector3fx GetLeft();

	/// Returns normalized camera's "Up" vector.
	/**
	 *  @return Returns normalized camera's "Up" vector.
	 */
	inline Vector3fx GetUp();

	/// Returns camera's state.
	/**
	 *  @return Returns camera's state
	 */
	inline CamState GetState();

	/// Moves camera between two positions and directions.
	/**
	 *  @param pos1_ - source position.
	 *  @param target1_ - source target point.
	 *	@param vWorldUp1_ - source "Up" vector.
	 *  @param pos2_ - destination position.
	 *  @param target2_ - destination target point.
	 *  @param vWorldUp2_ - destination "Up" vector.
	 *  @param msec_ - time interval for moving.
	 */
	void Move(const Vector3fx& pos1_, const Vector3fx& target1_, const Vector3fx& vWorldUp1_, const Vector3fx& pos2_, const Vector3fx& target2_, const Vector3fx& vWorldUp2_, Int msec_);

	/// Moves camera to destination position and target point from current state.
	/**
	 *  @param pos_ - destination position.
	 *  @param target_ - destination target point.
	 *  @param vWorldUp_ - default "Up" vector for calculating U,V,N vectors.
	 *  @param factor_ - approaching factor (in interval from 0.0 to 1.0). Used for smooth moving.
	 */
	void Follow(const Vector3fx& pos_, const Vector3fx& target_, const Vector3fx& vWorldUp_, const Fixed& factor_);
	
	/// Computes view matrix by camera's orientation and position.
	/**
	 *  @return Returns view matrix.
	 */
	Matrix4fx GetViewMatrix();

protected:

private:

	/// Recalculate UVN vector system.
	void UpdateUVN();

	/// Update animation for moving.
	void UpdateAnimation();

	/// View matrix
	Matrix4fx matrix;

	/// State of camera
	CamState state;	

	/// If position or target point was changed.
	Bool was_changed;

	/* Orientation of camera */

	/// Calculated "Left" vector
	Vector3fx u;	

	/// Calculated "Up" vector
	Vector3fx v;	

	/// Calculated "Dir" vector
	Vector3fx n;	
	
	/// Camera's position
	Vector3fx pos; 
	
	/// Camera's target point
	Vector3fx target;	

	/// Vector Up for calculating UVN
	Vector3fx vWorldUp;

	/// Rotation matrix.
	Matrix4fx rm;

	/* Animation */

	/// Current animation time
	Int time;	

	/// Last ticks value
	Int last_ticks;	

	/// Time increment by one tick
	Int delta_time; 

	/// FPS value (update count in one second)
	Int fps;	
	
	/// Animation frames
	vector<CamFrame> frames;

	/// Pointer to System object for access to ticks.
	System *system;	
};

////////////////////////////INLINES////////////////////////////////////////

inline void Camera::Set(const Vector3fx& pos_, const Vector3fx& target_, const Vector3fx& vWorldUp_)
{
	pos = pos_;

	target = target_;

	vWorldUp = Normalize(vWorldUp_);

	was_changed = True;
}

inline Vector3fx Camera::GetPos() 
{ 
	return pos; 
}

inline Vector3fx Camera::GetTarget() 
{ 
	return target; 
}	

inline Vector3fx Camera::GetDir() 
{ 
	if(was_changed) 
		UpdateUVN(); 
	
	return -n; 
}

inline Vector3fx Camera::GetLeft()
{
	if(was_changed) 
		UpdateUVN(); 

	return -u; 
}

inline Vector3fx Camera::GetUp()
{
	if(was_changed) 
		UpdateUVN(); 

	return v; 
}

inline CamState Camera::GetState() 
{ 
	return state; 
}

///////////////////////////////////////////////////////////////////////////

} //namespace mdragon

#endif // __MD_CAMERA_H__
