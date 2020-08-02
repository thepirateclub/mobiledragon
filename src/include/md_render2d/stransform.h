/** \file
 *	2d sprite transformation class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_STRANSFORM_H__
#define __MD_STRANSFORM_H__

namespace mdragon
{


class Image;
class Sprite2D;
class GameData;
class Render2D;


/// 2d sprite render's transformations.
/**
 *	Stores transformation parameters for rendering Sprite2D objects.
 */
class SpriteTransform
{
public:

	/// SpriteTransform class constructor.
	SpriteTransform();

	/// SpriteTransform class destructor.
	~SpriteTransform();

	/// Performs the complete initialization of SpriteTransform class object. 
	/**
	 * This function must be called before any operations on Sprite2D render transformations.
	 * Please don't delete or change Sprite2D class object while sending this 
	 * SpriteTransform class object to draw queue. Only after Render2D::Flush() 
	 * you can safely delete Sprite2D class object.
	 * @param sprite_ Sprite2D class object pointer. 
	 * @param SpriteCenterEqualRotateCenter if True for rotate operation will 
	 *        be used sprite center else top left sprite point will be center of rotation.
	 */
	void Set(Sprite2D* sprite_,Int SpriteCenterEqualRotateCenter=1);

	/// Get user defined type value.
	/**
	 * @return Return user defined type value. Default value is 0.
	 */
	Int GetType()
	{
		return type;
	}

	/// Set user defined type value.
	/**
	 * @param type_ define new user defined type value.
	 */
	void SetType( Int type_ )
	{
		type = type_;
	}

	/// Get Sprite2D class object.
	/**
	 * @return Return pointer to Sprite2D class object.
	 */
	Sprite2D* GetSprite()
	{
		return sprite;
	}

	/// Set new sprite position on global screen map.
	/**
	 * @param x define x top left new sprite position on global screen map.
	 * @param y define y top left new sprite position on global screen map.
	 */
	void Translate(Short x,Short y)
	{
		x_translate=x; y_translate=y;
	}

	/// Get sprite position on global screen map. 
	/**
	 * Default value is (0,0).
	 * @param x pointer to store x top left sprite position on global screen map.
	 * @param y pointer to store y top left sprite position on global screen map.
	 */
	void GetTranslate(Short *x,Short *y)
	{
		*x = x_translate; *y = y_translate;
	}

	/// Move sprite position on global screen map.
	/**
	 * @param x define x move for top left sprite position on global screen map.
	 * @param y define y move for top left sprite position on global screen map.
	 */
	void Move(Short x,Short y)
	{
		x_translate+=x; y_translate+=y;
	}

	/// Set new sprite scale on global screen map. 
	/**
	 * Default value is (1,1).
	 * Set scale value for x or y to negative value equivalents to flip 
	 * sprite image by x or y direction with positive scaling.
	 * @param x define x new sprite scale on global screen map.
	 * @param y define y new sprite scale on global screen map.
	 */
	void Scale(Fixed x,Fixed y)
	{
		x_scale = x;
		y_scale = y;
	}

	/// Get sprite scale on global screen map.
	/**
	 * @param x pointer to store x sprite scale on global screen map.
	 * @param y pointer to store y sprite scale on global screen map.
	 */
	void GetScale(Fixed *x,Fixed *y)
	{
		*x = x_scale;
		*y = y_scale;
	}

	/// Set new sprite rotate angle on global screen map. 
	/**
	 * Default value is 0.
	 * @param angle define new rotate angle in Fixed degrees.
	 */
	void SetAngle(Fixed angle)
	{
		z_rotate = angle;
	}

	/// Get sprite rotate angle on global screen map.
	/**
	 * @param angle pointer to store rotate angle in Fixed degrees.
	 */
	void GetAngle(Fixed *angle)
	{
		*angle = z_rotate;
	}

	/// Add new rotation to sprite rotate angle on global screen map.
	/**
	 * @param angle define new additional rotate angle in Fixed degrees.
	 */
	void Rotate(Fixed angle)
	{
		z_rotate += angle;
	}

	/// Set new sprite rotate center in sprite coordinates.
	/**
	 * @param x define x new sprite rotate center position.
	 * @param y define y new sprite rotate center position.
	 */
	void SetRotateCenter(Short x,Short y)
	{
		x_rotate_center = x;
		y_rotate_center = y;
	}

	/// Get sprite rotate center in sprite coordinates.
	/**
	 * @param x pointer to store x sprite rotate center position.
	 * @param y pointer to store y sprite rotate center position.
	 */
	void GetRotateCenter(Short *x,Short *y)
	{
		*x = x_rotate_center;
		*y = y_rotate_center;
	}

	/// Set new alpha transparent value for sprite. 
	/**
	 * Default value is 255.
	 * @param alpha_ define alpha value from 0 absolute transparent to 255 absolute opaque.
	 */
	void SetAlpha(Byte alpha_)
	{
		alpha = alpha_;
	}

	/// Get alpha transparent value for sprite.
	/**
	 * @param alpha_ pointer to store alpha value from 0 absolute 
	 *        transparent to 255 absolute opaque.
	 */
	void GetAlpha(Byte *alpha_)
	{
		*alpha_ = alpha;
	}

	/// Set new shadow value for sprite. 
	/**
	 *	Default value is 0.
	 *	@param shadow_ define new shadow value.
	 */
	void SetShadow(Byte shadow_)
	{
		shadow = shadow_;
	}

	/// Get shadow value for sprite.
	/**
	 *	@param shadow_ pointer to store shadow value.
	 */
	void GetShadow(Byte *shadow_)
	{
		*shadow_ = shadow;
	}

	// Set new color mask value for sprite. 
	/**
	 *	Default value is white.
	 *	@param color_mask_ define new color mask value.
	 */
	void SetColorMask(Pixel color_mask_)
	{
		color_mask = color_mask_;
	}

	/// GetColorMask() get color mask value for sprite.
	/**
	 * @param color_mask_ pointer to store color mask value.
	 */
	void GetColorMask(Pixel *color_mask_)
	{
		*color_mask_ = color_mask;
	}

	/// Return sprite bounding box Rect on global screen map.
	/**
	 * @return Return sprite bounding box Rect on global screen map.
	 */
	const Rect& GetBorder() const
	{
		return border;
	}

	/// Return z order for sprite.
	/**
	 * @return Return z order for sprite.
	 */
	Int GetZOrder()
	{
		return z_order;
	}

	/// Set new z order for sprite.
	/**
	 * @param z_order_ define new z order for sprite. Sprites with most biggest z order will be displayed on top of all.
	 */
	void SetZOrder(Int z_order_)
	{
		z_order=z_order_;
	}

	/// Update sprite bounding box.
	/**
	 * Need to call after any of Set(), Translate(), Move(), Scale(), 
	 * SetAngle(), Rotate(), SetRotateCenter(). For speed optimization do 
	 * first all transformations and than call only one UpDate().
	 */
	void UpDate(); // Don't forget call at the end of all sprite transforms.

	/// Return control render sprite flags.
	/**
	 * @return Return control render sprite flags. By default only Visible flag is set.
	 */
	DWord GetFlags() { return flags; }

	/// Set control render sprite flags.
	/**
	 *	Warning! Sixteen hi bits reserved for system.
	 *	@param flags_ define new control render sprite flags.
	 */
	void InitFlags(DWord flags_) { flags = flags_; }

	/* Sixteen hi bits reserved for system */
	#define SpriteTransform_Flag_Visible 31
	#define SpriteTransform_Flag_Animation 30
	#define SpriteTransform_Flag_LoopAnimation 29
	#define SpriteTransform_Flag_StopAnimation 28
	#define SpriteTransform_Flag_Lock 27
	#define SpriteTransform_Flag_SetShadow 26
	#define SpriteTransform_Flag_AddShadow 25
	#define SpriteTransform_Flag_SubShadow 24

	/// Check one specified control render sprite flag.
	/**
	 *	@param f define specified control render sprite flag to check.
	 *	@return Return True if flag is set else False.
	 */
	Bool CheckFlag(Int f) { return flags & (1 << f);	}

	/// Set one specified control render sprite flag.
	/**
	 *	@param f define specified control render sprite flag to set.
	 */
	void SetFlag(Int f) { flags |= (1 << f); }

	/// Clear one specified control render sprite flag.
	/**
	 *	@param f define specified control render sprite flag to clear.
	 */
	void ClearFlag(Int f) { flags &= ~(1 << f);	}

	/// Check is sprite visible.
	/**
	 *	Invisible sprites will be not rendered.
	 *	@return Return True if sprite visible flag is set else False.
	 */
	Bool IsVisible()
	{
		return CheckFlag( SpriteTransform_Flag_Visible );
	}

	/// Set sprite visible flag.
	/**
	 *	@param visible define new value for sprite visible flag. 
	 *        If True than sprite visible flag will be set else clear it.
	 */
	void SetVisible(Bool visible)
	{
		if( visible )
			SetFlag( SpriteTransform_Flag_Visible );
		else
			ClearFlag( SpriteTransform_Flag_Visible );
	}

	/// Return sprite animation playtime in frames. 
	/**
	 * Usable for animations only.
	 */
	Short GetTime() { return time; }

	/// Set sprite animation playtime in frames.
	/**
	 * Only usable for animations.
	 * @param time_ define new sprite animation playtime in frames.
	 */
	void SetTime(Short time_) { time=time_; }

	/// Return pointer to the sprite control CustomData class object.
	/**
	 * @return Return pointer to the sprite control CustomData class object. 
	 *         Next CustomData class object will be linked to this data. 
	 *         If no CustomData class object attached than return NULL.
	 */
	CustomData* GetCustomData() { return custom_data; }

	/// Set pointer to sprite control CustomData class object.
	/**
	 * Only pointer will be saved and not any memory will be used to 
	 * store CustomData class object. You should keep CustomData class object 
	 * data alive until this sprite control not be deleted.
	 * @param custom_data pointer to CustomData class object for this sprite control. 
	 */
	void SetCustomData(CustomData* custom_data_) { this->custom_data = custom_data; }

	/// Return ASCII name for this sprite control.
	/**
	 * @return Return ASCII name for this sprite control.
	 */
	const Char* GetName() { return name; }

	/// Set ASCII name for this sprite control. 
	/**
	 * Only pointer will be saved and not any memory will be used to store 
	 * ASCII name. You should keep ASCII name data alive until this sprite 
	 * control not be deleted.
	 * @param name pointer to ASCII name for this sprite control. 
	 */
	void SetName( const Char* name ) { this->name = name; }

	/// Return pointer to next sprite control linked to this sprite control.
	/**
	 * @return Return pointer to next sprite control linked to this sprite control. 
	 *         If no sprite control attached than return NULL.
	 */
	SpriteTransform* GetNext() { return next; }

	/// Set pointer to next sprite control linked to this sprite control.
	/**
	 * Only pointer will be saved and not any memory will be used to store 
	 * next sprite control. You should keep next sprite control data alive 
	 * until this sprite control not be deleted.
	 * @param st pointer to next sprite control linked to this sprite control. 
	 */
	void SetNext(SpriteTransform* st) { next = st; }

	/// Return x or y component of sprite control bounding box on global screen map.
	/**
	 * @param n define one of four bounding box point.
	 * @param x_y define 0 for x or 1 for y component of sprite control bounding box on global screen map.
	 * @return Return x or y component of sprite control bounding box on global screen map.
	 */
	Short GetXY( Int n, Int x_y ) { return xy[n][x_y]; }

	/// Return x component of sprite control bounding box on global screen map.
	/**
	 * @return Return x component of sprite control bounding box on global screen map.
	 */
	Short GetX( Int n ) { return xy[n][0]; }

	/// Return y component of sprite control bounding box on global screen map.
	/**
	 * @return Return y component of sprite control bounding box on global screen map.
	 */
	Short GetY( Int n ) { return xy[n][1]; }

	
	friend class Render2D;
	friend class GameData;
	friend class Animation;
	friend class Actor2D;

private:

	Int type;

	DWord flags;

	Sprite2D* sprite;

	Short x_translate,y_translate;

	Short x_rotate_center,y_rotate_center;

	Int z_order;

	Fixed x_scale,y_scale;

	Fixed z_rotate;

	Rect border;

	Short xy[4][2];

	Byte alpha;

	Char shadow;

	Short time;

	const Char *name;

	CustomData* custom_data;

	SpriteTransform* next;

	Pixel color_mask;

};

} //namespace mdragon

#endif // __MD_STRANSFORM_H__