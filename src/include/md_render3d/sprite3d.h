/** \file
 *	3d sprite class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SPRITE3D_H__
#define __MD_SPRITE3D_H__

namespace mdragon
{

/* Sprite3D draw mode types. */

/// Sprites VB will build world model basis X axis aligned ( billboard by X axis).
/**
 * VB will contain vertex in world coordinates.
 */ 
#define Sprite3D_Draw_Mode_Axis_X		1  

/// Sprites VB will build world model basis Y axis aligned ( billboard by Y axis).
/**
 * VB will contain vertex in world coordinates.
 */
#define Sprite3D_Draw_Mode_Axis_Y		2

/// Sprites VB will build world model basis X and Y axises aligned ( billboard by X and Y axis).
/**
 * VB will contain vertex in world coordinates.
 */
#define Sprite3D_Draw_Mode_Axis_XY		3

/// Sprites VB will build without world model basis alignment.
/**
 * VB will contain vertex in model local coordinates.
 */
#define Sprite3D_Draw_Mode_Axis_No		4

///////////////////////////////////////////////////////////////////////////

/// 3D sprite class.
class Sprite3D : public Basic3D
{

protected:

	/// Default constructor.
	Sprite3D();

	/// Constructor with given render pointer value.
	/**
	 *	@param render_ - pointer to the Render3D class object.
	 */
	Sprite3D(Render3D* render_);

	/// Destructor.
	~Sprite3D();

public:
	
	/// Creates new Sprite3D.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Sprite3D.
	 */
	static ObjRef<Sprite3D> New()
	{
		return ObjRef<Sprite3D>( new Sprite3D );
	}

	/// Create new Sprite3D.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Sprite3D.
	 */
	static ObjRef<Sprite3D> New( Render3D* render_ )
	{
		return ObjRef<Sprite3D>( new Sprite3D(render_) );
	}
	
	/// Sends Sprite3D object to the draw queue. 
	void Draw();

	/// Returns Sprite3D class id.
	/**
	 * @return Returns Sprite3D class id.
	 */
	Int GetClassID();

	/// Sets sprite's source pixel position in the sprite's center.
	inline void Centering() { spx.value = width.value >> 1; spy.value = height.value >> 1; }

	/// Sets sprite's draw mode.
	/**
	 * @param draw_mode_ - draw mode value. 
	 *                     See "Sprite3D draw mode types" defines for more info.
	 */
	inline void SetDrawMode (Int draw_mode_) { draw_mode = draw_mode_; }

	/// Returns sprite's draw mode.
	/**
	 * @return Returns sprite's draw mode. 
	 *         See "Sprite3D draw mode types" defines for more info.
	 */
	inline Int GetDrawMode() { return draw_mode; }

	/// Sprite position (x,y,z values).
	Vector3fx pos;

	/// Sprite Width.
	Fixed width;

	/// Sprite Height.
	Fixed height;

	/// Material.
	Material material;

	/// UV coordinates.
	Fixed uv[8];

	/// Source pixel's X coordinate (in sprite coordinate system).
	Fixed spx; 

	/// Source pixel's X coordinate (in sprite coordinate system).
	Fixed spy;

	friend class Render3D;

private:

	/// Sprite's draw mode.
	Int draw_mode;
};

} //namespace mdragon

#endif  //__MD_SPRITE3D_H__
