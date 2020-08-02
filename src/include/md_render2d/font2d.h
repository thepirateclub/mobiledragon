/** \file
 *	2d sprite font. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_FONT2D_H__
#define __MD_FONT2D_H__

namespace mdragon
{

/// Font2D represents 2D font class.
class Font2D
{
public:

	/// Constructor.
	Font2D();

	/// Destructor.
	 ~Font2D();

	/// Creates 2d font from specified font data file in packdir image by ASCII name.
	/**
	 * @param render pointer to Render2D class object.
	 * @param name_ pointer to ASCII name for specified image. Do not add file extension to this name.
	 */
	void Create(Render2D* render, const Char* name_);

	/// Free user resources.
	void Free();

	/// Send text to draw queue.
	/**
	 * @param text pointer to ASCII text to draw.
	 * @param x define x value for upper-left corner coordinate of text rectangle.
	 * @param y define y value for upper-left corner coordinate of text rectangle.
	 * @param sx pointer to store output text width in pixels.
	 * @param sy pointer to store output text height in pixels.
	 */
	void Draw(const Char* text,Short x,Short y,Short* sx=NULL,Short* sy=NULL);

	/// Send single character to draw queue.
	/**
	 * @param text pointer to ASCII text to draw.
	 * @param x define x value for upper-left corner coordinate of text rectangle.
	 * @param y define y value for upper-left corner coordinate of text rectangle.
	 * @param sx pointer to store output text width in pixels.
	 * @param sy pointer to store output text height in pixels.
	 */
	void Draw(Char c,Short x,Short y,Short* sx=NULL,Short* sy=NULL);

	/// Get text size in pixels.
	/**
	 * @param text pointer to ASCII text.
	 * @param sx pointer to store output text width in pixels.
	 * @param sy pointer to store output text height in pixels.
	 */
	void GetSize(const Char* text,Short* sx=NULL,Short* sy=NULL);

	/// Get character size in pxels.
	/**
	 * @param text pointer to ASCII text.
	 * @param sx pointer to store output text width in pixels.
	 * @param sy pointer to store output text height in pixels.
	 */
	void GetSize(Char c,Short* sx=NULL,Short* sy=NULL);

	/// Set new font scale. Default value is (1,1).
	/**
	 * @param x define new font x scale.
	 * @param y define new font y scale.
	 */
	void Scale(Fixed x,Fixed y)
	{
		x_scale = x;
		y_scale = y;
	}

	/// Get font scale.
	/**
	 * @param x pointer to store font x scale.
	 * @param y pointer to store font y scale.
	 */
	void GetScale(Fixed *x,Fixed *y)
	{
		*x = x_scale;
		*y = y_scale;
	}

	/// Set new font rotate angle.
	/**
	 * Default value is 0.
	 * @param angle define new rotate angle in Fixed degrees.
	 */
	void SetAngle(Fixed angle)
	{
		z_rotate = angle;
	}

	/// Get font rotate angle.
	/**
	 *	@return rotatation angle in Fixed degrees.
	 */
	Fixed GetAngle()
	{
		return z_rotate;
	}

	/// Add new rotation to font.
	/**
	 * @param angle define new additional rotate angle in Fixed degrees.
	 */
	void Rotate(Fixed angle)
	{
		z_rotate += angle;
	}

	/// Set new font color.
	/**
	 * Default value is RGB(255,255,255).
	 * @param color_ define new font color value. See class Color.
	 */
	void SetColor(Int color_)
	{
		color = color_;
	}

	/// Get font color.
	/**
	 * @param color_ pointer to store font color value. See class Color.
	 */
	Int GetColor()
	{
		return color;
	}

	/// Return z order for font.
	/**
	 * @return Return z order for font.
	 */
	Int GetZOrder()
	{
		return z_order;
	}

	/// Set new z order for font.
	/**
	 * @param z_order_ define new z order for font.
	 */
	void SetZOrder(Int z_order_)
	{
		z_order=z_order_;
	}

	/// Set new alpha transparent value for font.
	/**
	 * Default value is 255.
	 * @param alpha_ define alpha value from 0 absolute transparent to 255 absolute opaque.
	 */
	void SetAlpha(Byte alpha_)
	{
		alpha = alpha_;
	}

	/// Get alpha transparent value for font.
	/**
	 * @param alpha_ pointer to store alpha value from 0 absolute transparent to 255 absolute opaque.
	 */
	Byte GetAlpha()
	{
		return alpha;
	}

private:

	Fixed x_scale;
	Fixed y_scale;
	Fixed z_rotate;
	Int color;
	Int z_order;

	Render2D* render;

	ObjRef<Image> image0;

	Sprite2D* sprites;

	string name;

	Short texture_size;
	Short first_char;
	Short last_char;

	Short alpha;

};

} //namespace mdragon

#endif // __MD_FONT2D_H__