/** \file
 *	2d software rasterizer. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SOFTWARE2D_H__
#define __MD_SOFTWARE2D_H__

//////////////////////////////////////////////////////////////////////////

namespace mdragon
{

class SpriteXScanLineInfo
{
public:

	Int x_s;
	Int u_s,v_s;

	Int x_e;
	Int u_e,v_e;
};

#define Sprite_Transform_Sprite 1
#define Sprite_Transform_Point 2
#define Sprite_Transform_Line 3
#define Sprite_Transform_SpriteNoAngle 4

#define Sprite_Transform_Flag_SetShadow 1
#define Sprite_Transform_Flag_AddShadow 2
#define Sprite_Transform_Flag_SubShadow 4

#define Sprite_Transform_Flag_SwapU 8
#define Sprite_Transform_Flag_SwapV 16

#define Sprite_Transform_Flag_ColorRep 32

#define Sprite_Transform_Flag_NoClip 64

#define Sprite_Transform_Flag_Stencil 128

class SpriteTransformR
{
public:

	Int z_order;

	Byte type;
	Byte flags;

	Byte alpha;
	Char shadow;

	Sprite2D* sprite;

	Short xy[4][2];

	Pixel color_mask;

	Word reserved;

	void Draw(Render2D* render);
	void DrawNoAngle(Render2D* render);
};

} //namespace mdragon

//////////////////////////////////////////////////////////////////////////
#endif // __MD_SOFTWARE2D_H__