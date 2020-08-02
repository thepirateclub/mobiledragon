
/** \file
 *	2d image class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_IMAGE_H__
#define __MD_IMAGE_H__

namespace mdragon
{

class Sprite2D;
class SpriteTransform;
class SpriteTransformMS;
class SpriteTransformR;
class Render2D;


/// Store images.
/**
 *   Create new objects of this class via Render2D::LoadImage().
 *   Only PCX 256 palette graphics format supported and only square size 8x8, 16x16, 32x32, 64x64, 128x128 and 256x256.
 *   Image can have transparent pixels. Pixels with value R=255,G=0,B=255 are always transparent and not drawable.
 *   For storing alpha values of image pixels use the same file name with suffix "+a" for file image with alpha only values. 
 *   As for example let say that You store rgb bits of image in file with name "test.pcx" and than store alpha values in file "test+a.pcx".
 *   To store alpha values in PCX file format You need to copy alpha in RGB first in any image editor and than save new image as PCX 256 palette graphics format.
 *   Just for more understanding if You have pixel with 128 value for alpha than copy 128 to each R,G,B color layers to get R=128,G=128,B=128.
 */
class Image : public Object
{
public:
	
	/// Creates new Image object.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Return object reference to new Image object.
	 */
	static ObjRef<Image> New() 
	{ 
		return ObjRef<Image>( new Image );  
	}

	/// Return image width.
	/**
	 * @return Return image width.
	 */
	Short GetWidth() { return width; }

	/// Return image height.
	/**
	 * @return Return image height.
	 */
	Short GetHeight() { return height; }

	/// Return image ASCII name.
	/**
	 * @return Return image ASCII name.
	 */
	const string& GetName() const { return name; }

	/// Return control image flags.
	/**
	 * @return Return control image flags.
	 */
	DWord GetFlags() { return flags; }

	/// Set control image flags.
	/**
	 * Warning! Sixteen hi bits reserved for system.
	 * @param flags_ define new control image flags.
	 */
	void InitFlags(DWord flags_) { flags = flags_; }

///////////////////Possible Image flags////////////////////////////////////

	/// Image transparent flag.
	/** 
	 *  If it set than image have transparent pixels with value R=255,G=0,B=255.
	 */
	#define Image_Flag_Transparent 31

	/// Image alpha flag.
	/** 
	 *  If it set than image have alpha value for pixels.
	 */
	#define Image_Flag_Alpha 30

	/// Image shadow flag.
	/** 
	 *  If it set than image store shadow pixels only.
	 */
	#define Image_Flag_Shadow 29

///////////////////////////////////////////////////////////////////////////

	/// Check one specified control image flag.
	/**
	 * @param f define specified control image flag to check.
	 * @return Return True if flag is set else False.
	 */
	Bool CheckFlag(Int f) { return flags & (1 << f);	}

	/// Set one specified control image flag.
	/**
	 * @param f define specified control image flag to set.
	 */
	void SetFlag(Int f) { flags |= (1 << f); }

	/// Clear one specified control image flag.
	/**
	 * @param f define specified control image flag to clear.
	 */
	void ClearFlag(Int f) { flags &= ~(1 << f);	}


	friend class Render2D;
	friend class Sprite2D;
	friend class SpriteTransform;
	friend class SpriteTransformMS;
	friend class SpriteTransformR;

private:

	Image();

	 ~Image();

	Bool Load(Render2D* render,const Char* name_);

	Pixel* pixels;

	Short width,height;

	DWord UMask,VMask;
	Int texture_shift;

	string name;

	DWord flags;


#ifdef MD_OS_PALM
	Word feature_n;
#endif	

};


/// Rect class stores the upper-left and lower-right corners coordinates of rectangle.
/**
 *   Rect class object in most keys used to store bounding box coordinates.
 */
class Rect
{

public:

	/// Default constructor.
	Rect() {}

	/// Constructor with given upper-left and lower-right corners coordinates.
	/**
	 * Initialize Rect by the upper-left and lower-right corners coordinates.
	 * @param x1_ define x value for upper-left corner coordinate of rectangle.
	 * @param y1_ define y value for upper-left corner coordinate of rectangle.
	 * @param x2_ define x value for lower-right corner coordinate of rectangle.
	 * @param y2_ define y value for lower-right corner coordinate of rectangle.
	 */
	Rect( Short x1_, Short y1_, Short x2_, Short y2_ )
	{
		x1 = x1_; 
		x2 = x2_; 
		y1 = y1_; 
		y2 = y2_;
	}

	/// Move upper-left and lower-right corners coordinates of rectangle.
	/**
	 * @param x define x move for upper-left and lower-right corner coordinates of rectangle.
	 * @param y define y move for upper-left and lower-right corner coordinates of rectangle.
	 */
	void Move( Short x, Short y )
	{
		x1 += x; 
		y1 += y;
		x2 += x; 
		y2 += y;
	}

	/// Scale upper-left and lower-right corners coordinates of rectangle.
	/**
	 * @param x define x scale for upper-left and lower-right corner coordinates of rectangle.
	 * @param y define y scale for upper-left and lower-right corner coordinates of rectangle.
	 */
	void Scale( Fixed x, Fixed y )
	{
		x1 = x * x1; 
		y1 = y * y1;
		x2 = x * x2; 
		y2 = y * y2;
	}
	
	/// x value for upper-left corner coordinate of rectangle. 
	Short x1; 
	
	/// y value for upper-left corner coordinate of rectangle.  
	Short y1; 
	
	/// x value for lower-right corner coordinate of rectangle.
	Short x2; 
	
	/// y value for lower-right corner coordinate of rectangle. 
	Short y2; 
};

/// Check one specified point is it in or out of border rectangle.
/**
 * @param border pointer to border rectangle.
 * @param x define x value for x check point coordinate.
 * @param y define y value for y check point coordinate.
 * @return Return True if check point is in border rectangle else False.
 */
inline Int TestXY2Rectangle(const Rect *border,Short x,Short y)
{
	return ( ( x >= border->x1 ) &&
			 ( y >= border->y1 ) &&
			 ( x < border->x2 )  &&
			 ( y < border->y2 ) );
}

/// Check one specified rectangle is it in or out of border rectangle.
/**
 * @param border pointer to border rectangle.
 * @param r pointer to test rectangle.
 * @return Return True if test rectangle is in or collide border rectangle else False.
 */
inline Int TestRectangle2Rectangle(const Rect *border,const Rect *r)
{
	return ( ( r->x1 < border->x2 ) &&
			 ( r->y1 < border->y2 ) &&
			 ( r->x2 > border->x1 ) &&
			 ( r->y2 > border->y1 ) );
}

/// Clip one specified rectangle by border rectangle.
/**
 * @param border pointer to border rectangle.
 * @param r pointer to clip rectangle. Clipped rectangle will be stored in rectangle by this pointer. If border rectangle have not clip rectangle or even not collided with it than clip rectangle with have all coordinates with 0 value.
 */
inline void ClipRectangle2Rectangle(const Rect *border,Rect *r)
{
	if( r->x1 < border->x1 )
		r->x1 = border->x1;
	if( r->y1 < border->y1 )
		r->y1 = border->y1;
	if( r->x2 > border->x2 )
		r->x2 = border->x2;
	if( r->y2 > border->y2 )
		r->y2 = border->y2;

	if( r->x1 >= r->x2 || r->y1 >= r->y2 )
		r->x1 = r->x2 = r->y1 = r->y2 = 0;
}

/// Clip one specified rectangle by border rectangle and try to make result clipped rectangle size equal to input rectangle for clip.
/**
 * @param border pointer to border rectangle.
 * @param r pointer to clip rectangle. Clipped rectangle will be stored in rectangle by this pointer. If border rectangle have not clip rectangle or even not collided with it than clip rectangle with have all coordinates with 0 value.
 */
inline void ClipMaxRectangle2Rectangle(const Rect *border,Rect *r)
{
	if( r->x1 < border->x1 )
	{
		Short offs = border->x1 - r->x1;

		r->x1 += offs;
		r->x2 += offs;
	}

	if( r->y1 < border->y1 )
	{
		Short offs = border->y1 - r->y1;

		r->y1 += offs;
		r->y2 += offs;
	}

	if( r->x2 > border->x2 )
	{
		Short offs = border->x2 - r->x2;

		r->x1 += offs;
		r->x2 += offs;
	}

	if( r->y2 > border->y2 )
	{
		Short offs = border->y2 - r->y2;

		r->y1 += offs;
		r->y2 += offs;
	}

	ClipRectangle2Rectangle( border, r );
}

} //namespace mdragon

#endif // __MD_IMAGE_H__