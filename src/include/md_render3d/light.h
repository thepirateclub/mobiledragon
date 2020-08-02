/** \file
 *	3d light class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_LIGHT_H__
#define __MD_LIGHT_H__

namespace mdragon
{

/* Lights types */

/// Omni light.
#define Light_Type_Omni 1

/// Directional light.
#define Light_Type_Directional 2

/// Spot light.
#define Light_Type_Spot 3

/// 3d light source.
class Light : public Basic3D
{
protected:
	
	/// Default constructor.
	Light();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Light(Render3D* render_);

	/// Destructor.
	~Light();

public:

	/// Creates new Light.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Light.
	 */
	static ObjRef<Light> New()
	{
		return ObjRef<Light>( new Light );
	}

	/// Creates new Light.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Light.
	 */
	static ObjRef<Light> New( Render3D* render_ )
	{
		return ObjRef<Light>( new Light(render_) );
	}
	
	/// This function does not any effect.
	void Draw();

	/// This function does not any effect.
	void UpdateTransform();

	/// Returns light source result transform matrix.
	/**
	 * @return Returns light source result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Returns Light class id.
	/**
	 * @return Returns Light class id.
	 */
	Int GetClassID();

	/// Light's type.
	Int type;

	/// Light's color.
	Color color;

	/// Light's specular color.
	Color specular;

	/// Light's intensity.
	Fixed intensity;

	/// Light's location.
	Vector3fx location;

	/// Ligth's direction.
	Vector3fx direction;

	/// Lght's radius.
	Fixed radius;

	/// Is light turn ON\OFF
	Bool on; 



	Fixed theta; // in radians
	Fixed phi; // in radians
	
};

} //namespace mdragon

#endif // __MD_LIGHT_H__