/** \file
 *	Software 3d rasterizer utilities. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SOFTWARE3D_H__
#define __MD_SOFTWARE3D_H__

namespace mdragon
{


#ifndef Fixed


inline void TRANSFORM_VECTOR(Vector3fx& v_in,Vector3fx& v_out,Int RenderXPerspective, Int RenderYPerspective)
{
	{
		v_out.z.value = FDiv14x2( (1<<16) , v_in.z.value );

		v_out.x.value = FMul8x0( v_in.x.value , v_out.z.value );
		v_out.y.value = FMul8x0( v_in.y.value , v_out.z.value );
	}

	v_out.x.value = FMul8x8( v_out.x.value , RenderXPerspective );
	v_out.y.value = FMul8x8( v_out.y.value , RenderYPerspective );
}

#endif


#define PROJECT_VERTEX(v_in,v_out,RenderWidth2,RenderX,RenderHeight2,RenderY) \
	v_out.sx = ROUND( ( - v_in.x + I2F(1) ) * RenderWidth2 ) + RenderX; \
	v_out.sy = ROUND( ( v_in.y + I2F(1) ) * RenderHeight2 ) + RenderY;

//////////////////////////////////////////////////////////////////////////


inline void TRANSFORM_VERTEXf(Vertex& v_in,Vertex& v_out,Int RenderXPerspective, Int RenderYPerspective)
{
	{
		v_out.z = FDiv14x2( (1<<16) , v_in.z );

		v_out.x = FMul8x0( v_in.x , v_out.z );
		v_out.y = FMul8x0( v_in.y , v_out.z );
	}

	v_out.x = FMul8x8( v_out.x , RenderXPerspective );
	v_out.y = FMul8x8( v_out.y , RenderYPerspective );
}

#define PROJECT_VERTEXf(v_in,v_out,RenderWidth2,RenderX,RenderHeight2,RenderY) \
	v_out.sx = F2I( ( - v_in.x + I2F(1) ) * RenderWidth2 ) + RenderX; \
	v_out.sy = F2I( ( v_in.y + I2F(1) ) * RenderHeight2 ) + RenderY;


} //namespace mdragon

#endif // __MD_SOFTWARE3D_H__