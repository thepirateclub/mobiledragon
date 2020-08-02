/** \file
 *	2d sprite class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SPRITE2D_H__
#define __MD_SPRITE2D_H__

namespace mdragon
{

class Image;
class SpriteTransform;
class SpriteTransformMS;
class SpriteTransformR;
class Render2D;


/// 2d sprite class.
/**
 *	Sprite2D represents rectangular portion of Image.
 */
class Sprite2D
{
public:

	/// Sprite2D class constructor.
	Sprite2D();

	/// Sprite2D class destructor.
	/**
	 * Free all memory used to store sprite data. 
	 * Please note image object that store sprite pixels will be not deleted.
	 */
	~Sprite2D();

	/// Performs the complete initialization of Sprite2D class object. 
	/**
	 * This function must be called before any operations on Sprite2D class object.
	 * @param image_ Image class object pointer. This image store sprite pixels.
	 * @param x_offs_ define x value for upper-left corner coordinate of sprite on image.
	 * @param y_offs_ define y value for upper-left corner coordinate of sprite on image.
	 * @param width_ define width of sprite.
	 * @param height_ define height of sprite.
	 * @param copy_image_direct if not zero than while init do check sprite part of image for transparent or alpha pixels and set sprite alpha or transparent flags else copy image flags direct.
	 * Please note Sprite2D class object do not copy or store any pixels direct. All sprite pixels stored in image.
	 */
	void Init(ObjRef<Image> image_,Short x_offs_,Short y_offs_,Short width_,Short height_,Int copy_image_direct=1);

	/// Return sprite width.
	/**
	 * @return Return sprite width.
	 */
	Short GetWidth() { return width; }

	/// Return sprite height.
	/**
	 * @return Return sprite height.
	 */
	Short GetHeight() { return height; }

	/// Return pointer to the next sprite mipmap.
	/**
	 * @return Return pointer to the next sprite mipmap.
	 */
	Sprite2D* GetMipMap() { return mipmap; }

	/// Return control sprite flags.
	/**
	 * @return Return control sprite flags.
	 */
	DWord GetFlags() { return flags; }

	/// Set control sprite flags.
	/**
	 * Warning! Sixteen hi bits reserved for system.
	 * @param flags_ define new control sprite flags.
	 */
	void InitFlags(DWord flags_) { flags = flags_; }

///////////////////Possible Sprite2D flags/////////////////////////////////

	/// Sprite2D transparent flag.
	/** 
	 *  If it set than sprite have transparent pixels with value R=255,G=0,B=255.
	 */
	#define Sprite_Flag_Transparent 31

	/// Sprite2D alpha flag. 
	/** 
	 * If it set than sprite have alpha value for pixels.
	 */
	#define Sprite_Flag_Alpha 30

	/// Sprite2D shadow flag.
	/** 
	 * If it set than sprite store shadow pixels only.
	 */
	#define Sprite_Flag_Shadow 29

///////////////////////////////////////////////////////////////////////////

	/// Check one specified control sprite flag.
	/**
	 * @param f define specified control sprite flag to check.
	 * @return Return True if flag is set else False.
	 */
	Bool CheckFlag(Int f) { return flags & (1 << f);	}

	/// Set one specified control sprite flag.
	/**
	 * @param f define specified control sprite flag to set.
	 */
	void SetFlag(Int f) { flags |= (1 << f); }

	/// Clear one specified control sprite flag.
	/**
	 * @param f define specified control sprite flag to clear.
	 */
	void ClearFlag(Int f) { flags &= ~(1 << f);	}


	friend class SpriteTransform;
	friend class SpriteTransformMS;
	friend class SpriteTransformR;
	friend class Render2D;
	friend class GameData;

private:

	ObjRef<Image> image;

	Sprite2D* mipmap;

	Short x_offs,y_offs;
	Short width,height;

	DWord flags;

};

} // namespace mdragon

#endif // __MD_SPRITE2D_H__
