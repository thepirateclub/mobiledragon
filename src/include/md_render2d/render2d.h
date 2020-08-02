/** \file
 *	2d render class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_RENDER2D_H__
#define __MD_RENDER2D_H__

namespace mdragon
{


/* Define clear type masks for Clear(). */

/// Clear color buffer with color set by SetClearColor().
#define Render2D_Clear_Color 1

/// Clear stencil buffer without clearing color buffer.
#define Render2D_Clear_Stencil 2


class SpriteXScanLineInfo;
class SpriteTransformR;


/// 2d graphics render class.
/**
 *  This class provides functionality for rendering 2d 2d graphics.
 */
class Render2D
{
public:

	/// Render2D class destructor.
	/**
	 * Unlock the screen video memory and frees entire memory occupied 
	 * under the 2d graphics render.
	 */
	~Render2D();

	/// Performs the complete initialization of Render2D.
	/**
	 * This function must be called at the beginning of the initialization of program before any operations with 2d drawing.
	 * @param system_ System class object pointer.
	 * @param width The specified width dimension of display.
	 * @param height The specified height dimension of display.
	 * @param bpp The specified bit per pixel dimension of display.
	 * @param redbits The specified red bits per pixel.
	 * @param greenbits The specified green bits per pixel.
	 * @param bluebits The specified blue bits per pixel.
	 * @see System class for more info about System.
	 * @return Return True if Render2D init complete successfully else False.
	 */
	Bool Init(System* system_,Int width,Int height,Int bpp,Int redbits,Int greenbits,Int bluebits);

	/// Copy backbuffer to video memory on display. 
	/**
	 * Only part of backbuffer defined by last call of SetViewport() will be copied.
	 */
	void Show();

	/// Defines clear color for Clear().
	/**
	 * @param color clear color value. See class Color.
	 */
	void SetClearColor(Int color);

	/// Performs clearing of color or stencil backbuffer. 
	/**
	 * Only part of backbuffer defined by last call of SetViewport() will 
	 * be cleaned. Call Clear() at the beginning of new frame drawing.
	 * @param type see Render2D_Clear_xxx defines for more info.
	 */
	void Clear(Int type);

	/// Return specified width dimension of display.
	/**
	 * @return Return specified width dimension of display.
	 */
	Int GetScreenWidth();

	/// Return specified height dimension of display.
	/**
	 * @return Return specified height dimension of display.
	 */
	Int GetScreenHeight();

	/// Set color gamma level.
	/**
	 * @param gamma defines color gamma level in Fixed point.
	 */
	void SetColorGamma( Fixed gamma );

	/// Get color gamma level.
	/**
	 * @return Return current color gamma level in Fixed point.
	 */
	Fixed GetColorGamma();

	/// Set current viewport position and size.
	/**
	 * @param x define x top left position of viewport on display.
	 * @param y define y top left position of viewport on display.
	 * @param width define width dimension of viewport.
	 * @param height define height dimension of viewport.
	 * SetViewport() can be called only one per Flush() call.
	 */
	void SetViewport(Int x,Int y,Int width,Int height);

	/// Set current viewport rectangle.
	/**
	 * @param viewport - rectangle defining viewport.
	 * @param height define height dimension of viewport.
	 * SetViewport() can be called only one per Flush() call.
	 */
	void SetViewport( const Rect & viewport );


	/// Return current viewport Rect.
	/**
	 * This rectangle determine viewport border on display.
	 * @return Return current viewport Rect.
	 */
	const Rect& GetViewport() const { return display_border; }

	/// Return current viewport bounding box Rect on global screen map.
	/**
	 * @return Return current viewport bounding box Rect on global screen map.
	 */
	const Rect& GetViewBorder() const { return display_border_test; }
	
	/// Set origin for current viewport on global screen map.
	/**
	 * @param x define x top left position of viewport on global screen map.
	 * @param y define y top left position of viewport on global screen map.
	 */
	void SetOrigin(Short x,Short y);

	/// Get origin for current viewport on global screen map.
	/**
	 * @param x pointer to store x top left position of viewport on global screen map.
	 * @param y pointer to store y top left position of viewport on global screen map.
	 */
	void GetOrigin(Short *x, Short *y);

	/// Move origin for current viewport on global screen map.
	/**
	 * @param x define x move for viewport on global screen map.
	 * @param y define y move for viewport on global screen map.
	 */
	void MoveOrigin(Short x,Short y);

	/// Scale current viewport on global screen map.
	/**
	 * @param x define x scale of viewport on global screen map.
	 * @param y define y scale of viewport on global screen map.
	 */
	void SetScale(Fixed x,Fixed y);

	/// Get scale of current viewport on global screen map.
	/**
	 * @param x pointer to store x scale of viewport on global screen map.
	 * @param y pointer to store y scale of viewport on global screen map.
	 */
	void GetScale(Fixed *x,Fixed *y);
	
	/// Set alpha transparent value for all drawing operations.
	/**
	 * @param alpha_ define alpha value from 0 absolute transparent to 255 absolute opaque.
	 */
	void SetAlpha(Byte alpha_);

	/// Get alpha transparent value for all drawing operations.
	/**
	 *	@return alpha value from 0 absolute transparent to 255 absolute opaque.
	 */
	Byte GetAlpha();

	/// Set and color mask value for all drawing operations.
	/**
	 * This color will be applied by AND binary logical operation to all drawing pixels.
	 * @param color_mask_ and mask color value. See class Color.
	 */
	void SetAndColorMask(Int color_mask_);

	/// Get and color mask value for all drawing operations. 
	/**
	 * This color will be applied by AND binary logical operation to all drawing pixels.
	 * @return AND mask color value. See class Color.
	 */
	Int GetAndColorMask();

	/// Set color replace table for all drawing operations.
	/**
	 * @param color_rep pointer to 16 Pixels to load. See Pixel.
	 */
	void SetColorReplaceTable(const Pixel * color_rep);

	/// Get color replace table for all drawing operations.
	/**
	 * @param color_rep pointer to 16 Pixels to store. See Pixel.
	 */
	void GetColorReplaceTable(Pixel* color_rep);

	/// Check is color replace turn on for all drawing operations.
	/**
	 * @return Return True if color replace turn on else False.
	 */
	Bool IsColorReplacementEnabled();

	/// Set color replace turn on or off for all drawing operations.
	/**
	 * @param do_color_rep boolean value True to turn on color replace else turn off.
	 */
	void SetColorReplacement(Bool do_color_rep);

	/// Set stencil mode for all drawing operations.
	/**
	 * @param mode 0 - stencil mode off, 
	 *             1 - draw and set stencil mask for all not transparent pixels, 
	 *			   2 - draw only on pixels with stencil mask.
	 */
	void SetStencilMode( Int mode );

	/// Get stencil mode for all drawing operations.
	/**
	 * @return Return 0 - if stencil mode off, 
	 *				  1 - if drawing and set stencil mask for all not transparent pixels mode on, 
	 *				  2 - if drawing only on pixels with stencil mask mode on.
	 */
	Int GetStencilMode();

	/// Send point to draw queue.
	/**
	 * @param x define x point position on global screen map.
	 * @param y define y point position on global screen map.
	 * @param color define point color value. See class Color.
	 * @param z_order define point z order.
	 */
	void DrawPoint( Short x, Short y, Int color, Int z_order=0 );

	/// Send line to draw queue.
	/**
	 * @param x1 define x line first point position on global screen map.
	 * @param y1 define y line first point position on global screen map.
	 * @param x2 define x line second point position on global screen map.
	 * @param y2 define y line second point position on global screen map.
	 * @param color define line color value. See class Color.
	 * @param z_order define line z order.
	 */
	void DrawLine( Short x1, Short y1, Short x2, Short y2, Int color, Int z_order=0 );

	/// Send SpriteTransform class object to draw queue.
	/**
	 * @param st pointer to SpriteTransform class object that contain Sprite2D and all drawing operations for it.
	 * @param z_order define z order that will be add to SpriteTransform class object base z order before sending to draw queue.
	 */
	void Draw(SpriteTransform* st,Int z_order=0);

	/// Apply drawing operations from base SpriteTransform class object to source SpriteTransform class object and send result to draw queue.
	/**
	 * @param st_base pointer to base SpriteTransform class object that contain all base drawing operations.
	 * @param st pointer to source SpriteTransform class object that contain Sprite2D and all drawing operations for it.
	 * @param z_order define z order that will be add to result SpriteTransform class object base z order before sending to draw queue.
	 */
	void Draw(SpriteTransform* st_base,SpriteTransform* st,Int z_order=0);

	/// Sort draw queue by z order and draw it.
	/**
	 *  After drawing clear draw queue. You can call Flush() several times 
	 *	per one frame as for example first draw all background and flush it 
	 *  to backbuffer and than draw foreground scene on it. 
	 */
	void Flush();

	/// Find specified image by ASCII name in image queue.
	/**
	 * @param name_ pointer to ASCII name for specified image.
	 * @return Return pointer to Image class object if find complete successfully else NULL pointer.
	 */
	ObjRef<Image> FindImage(const Char* name_);

	/// Find specified image by ASCII name in image queue and if not found than load it from resource. 
	/**
	 * @param name_ pointer to ASCII name for specified image. Do not add file extension to this name.
	 * @return Return pointer to Image class object if find or load complete successfully else NULL pointer. Also increase found Image class object reference count by one.
	 * @see Look Image class for more info about supported images.
	 */
	ObjRef<Image> LoadImage(const Char* name_);

	/// Free all memory used to store all Image class objects and all image queue.
	void FreeAllImages();

	/// Releases all unreferenced resources.
	/**
	 *	Call this after releasing references to Image objects.
	 */
	void UpdateResources();

	/// Get PackDir class object that was obtained from System class object.
	/**
	 * @return Return pointer to PackDir class object.
	 */
	PackDir* GetPackDir() { return packdir; }

	/// Get System class object.
	/**
	 * @return Return pointer to System class object.
	 */
	System* GetSystem() { return system; }

//////////////////////////////////////////////////////////////////////////

	friend class Image;
	friend class Sprite2D;
	friend class SpriteTransform;

	friend class SpriteTransformR;

//////////////////////////////////////////////////////////////////////////

	void* display_memory;
	void* cengine;

//	Int* div256;

	Pixel* alpha16;
	
//////////////////////////////////////////////////////////////////////////

private:

	void DrawPointDirect( Short x, Short y, Int color );
	void DrawPointDirectSetStencil( Short sx, Short sy, Int color );
	void DrawPointDirectOnStencil( Short sx, Short sy, Int color );

	void DrawLineDirect( Short x1, Short y1, Short x2, Short y2, Int color, Int stencil_mode );

	System *system;

	SpriteXScanLineInfo* xscanline;

	SpriteTransformR* st_r;

	Int** st_msr_z_order;

	Int st_r_size,st_r_count;

	Int st_msr_z_order_size,st_msr_z_order_count;

	Int SCR_X;
	Int SCR_Y;
	Int SCR_BPP;

	Int WINDOW_X1;
	Int WINDOW_Y1;
	Int WINDOW_X2;
	Int WINDOW_Y2;

	Int SCR_REDBITS, SCR_GREENBITS, SCR_BLUEBITS;

	DWord* DISPLAY;

	DWord* COLOR_TABLE_LIGHT;

	int BlitGDMode;

	Int RenderClearColor;

	Int RenderX,RenderY,RenderWidth,RenderWidth2,RenderHeight,RenderHeight2;

	Rect display_border;

	Rect display_border_test;

	Short x_origin,y_origin;
	Fixed x_scale,y_scale;
	
	Fixed x_o_s;
	Fixed y_o_s;
	Float32 x_scale32;
	Float32 y_scale32;
	Short x_o_s16;
	Short y_o_s16;


	DWord alpha;
	Int color_mask;
	Pixel color_rep[16];
	Bool do_color_rep;


	Int stencil_mode;


	vector< ObjRef<Image> > image_list;
	Image xim[2];
	DWord ximst;

	PackDir* packdir;

	Fixed gamma;

};

} //namespace mdragon

#endif // __MD_RENDER2D_H__
