/** \file
 *	3d render class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_RENDER3D_H__
#define __MD_RENDER3D_H__

namespace mdragon
{

/////////////////////////////RENDER FLAGS//////////////////////////////////

/* Clear Types. Are used in Clear() function. */ 

/// Clear color buffer.
#define Render_ClearType_ClearColor		  (1 << 0)	

/// Clear depth buffer.
#define Render_ClearType_ClearDepth		  (1 << 1) 

/// Clear stencil buffer.
#define Render_ClearType_ClearStencil     (1 << 2)

///////////////////////////////////////////////////////////////////////////

/* Draw Mode Flags. Are used in SetMode(), ClearMode(), CheckMode() functions. */

/// Drawing triangles from back to front.
/**
 * By default is OFF.
 */
#define Render_BackToFront_Mode           (1 << 0) 

/// Drawing without writing and checking Z-buffer. 
/**
 * By default is OFF.
 */
#define Render_NoZ_Mode					  (1 << 1)

/// Drawing texture with perspective correction. 
/**
 * By default is ON.
 */
#define Render_PerspectiveCorrection_Mode (1 << 2)

/// Fast drawing mode, with lower quality. 
/**
 * Defined for future OpenGL compatibility. 
 * By default is OFF.
 */
#define Render_Fast_Mode				  (1 << 3)

/// Drawing with lighting mode. 
/**
 * By default is ON.
 */
#define Render_Light_Mode				  (1 << 4)

/// Drawing with fog mode.
/**
 * By default is ON.
 */
#define Render_Fog_Mode					  (1 << 5)

/// Logical pixel operation - COPY. 
/**
 * By default is ON.
 */
#define Render_Copy_LogicOp_Mode		  (1 << 6) 

/// Logical pixel operation - OR. 
/**
 * By default is OFF.
 */
#define Render_Or_LogicOp_Mode			  (1 << 7)

///////////////////////////////////////////////////////////////////////////

/* Fog Modes. Are used in SetFogMode(), GetFogMode() functions. */

/// Linear fog mode.
#define Render_FogMode_Linear			  (1 << 0)

/// Exponential fog mode.
#define Render_FogMode_Exp				  (1 << 1)

/// Exponential squared fog.
#define Render_FogMode_Exp2				  (1 << 2)

///////////////////////////////////////////////////////////////////////////

/**
 * Flags of intersection with camera view frustum planes.
 * Using in IsVisible() function, that return flag of sphere 
 * visibility by current camera view frustum.
 */

/// Sphere intersect Near plane of view frustum.
#define Render_Near_Plane				  (1 << 1)

/// Sphere intersect Far plane of view frustum.
#define Render_Far_Plane				  (1 << 2)

/// Sphere intersect Right plane of view frustum.
#define Render_Right_Plane				  (1 << 3)

/// Sphere intersect Left plane of view frustum.
#define Render_Left_Plane				  (1 << 4)

/// Sphere intersect Top plane of view frustum.
#define Render_Top_Plane				  (1 << 5)

/// Sphere intersect Bottom plane of view frustum.
#define Render_Bottom_Plane				  (1 << 6)

///////////////////////////////////////////////////////////////////////////

class Camera;

///////////////////////////////////////////////////////////////////////////

/// 3D render class.
class Render3D
{
public:
	
	////////////////////////////COMMON/////////////////////////////////////

	/// Default constructor.
	Render3D();

	/// Destructor.
	/**
	 * Unlock the screen video memory and frees entire memory occupied under 
	 * the 3d graphics render.
	 */
	~Render3D();

	/// Performs the complete initialization of Render3D. 
	/**
	 * This function must be called at the beginning of the initialization 
	 * of program before any operations with 3d drawing.
	 * @param system_ System class object pointer.
	 * @param width The specified width dimension of display.
	 * @param height The specified height dimension of display.
	 * @param bpp The specified bit per pixel dimension of display.
	 * @param redbits The specified red bits per pixel.
	 * @param greenbits The specified green bits per pixel.
	 * @param bluebits The specified blue bits per pixel.
	 * @see System class for more info about System.
	 * @return Returns True if Render3D init complete successfully else False.
	 */
	Bool Init(System* system_,Int width,Int height,Int bpp,Int redbits,Int greenbits,Int bluebits);

	/// Returns PackDir class object that was obtained from System class object.
	/**
	 * @return Returns pointer to PackDir class object.
	 */
	PackDir* GetPackDir() { return packdir; }

	///  Returns System class object.
	/**
	 * @return Returns pointer to System class object.
	 */
	System* GetSystem() { return system; }

	/// Releases all unreferenced resources.
	/**
	 * Call this after releasing references to Texture or LightMap objects.
	 */
	void UpdateResources();

	////////////////////////////BACKBUFFER/////////////////////////////////

	/// Copies backbuffer to video memory on display. 
	/**
	 * Only part of backbuffer defined by last call of SetViewport() will be copied.
	 */	
	void Show();

	/// Defines clear color for Clear().
	/**
	 * @param color - clear color value. See class Color.
	 */
	void SetClearColor(Int color);

	/// Defines clear depth for Clear().
	/**
	 * @param depth - clear depth value.
	 */
	void SetClearDepth(Fixed depth);

	/// Performs clearing of color, depth or stencil backbuffer. 
	/**
	 * Only part of backbuffer defined by last call of SetViewport() will be cleaned. 
	 * Call Clear() at the beginning of new frame drawing.
	 * @param type - see Render_ClearType_ClearXXXXX defines for more info.
	 */
	void Clear(Int type);

	///////////////////////////SCREEN & VIEWPORT///////////////////////////

	/// Returns specified width dimension of display.
	/**
	 * @return Returns specified width dimension of display.
	 */
	Int GetScreenWidth();

	/// Returns specified height dimension of display.
	/**
	 * @return Returns specified height dimension of display.
	 */	
	Int GetScreenHeight();

	/// Sets current viewport position and size.
	/**
	 * @param x - define x top left position of viewport on display.
	 * @param y - define y top left position of viewport on display.
	 * @param width - define width dimension of viewport.
	 * @param height - define height dimension of viewport.
	 * SetViewport() can be called only one per Flush() call.
	 */
	void SetViewport(Int x,Int y,Int width,Int height);

	/// Returns specified width dimension of viewport.
	/**
	 * @return Returns specified width dimension of viewport.
	 */
	Int GetViewportWidth();

	/// Returns specified height dimension of viewport.
	/**
	 * @return Returns specified height dimension of viewport.
	 */	
	Int GetViewportHeight();

	/// Returns specified X top left position of viewport on display.
	/**
	 * @return Returns specified X top left position of viewport on display.
	 */
	Int GetViewportXTopLeftPosition();

	/// Returns specified Y top left position of viewport on display.
	/**
	 * @return Returns specified Y top left position of viewport on display.
	 */
	Int GetViewportYTopLeftPosition();

	///////////////////////////MATRICES////////////////////////////////////

	/// Returns camera view matrix for current viewport.
	/**
	 * @return Returns camera view matrix for current viewport.
	 */		
	Matrix4fx GetView();

	/// Returns world matrix for current viewport.
	/**
	 * @return Returns world matrix for current viewport.
	 */	
	Matrix4fx GetWorld();

	/// Returns view * world result matrix for current viewport.
	/**
	 * @return Returns view * world result matrix for current viewport.
	 */	
	Matrix4fx GetViewWorld();

	/// Sets camera view matrix for current viewport.
	/**
	 * @param v - pointer to new camera view matrix.
	 */
	void SetView(Matrix4fx* v);

	/// Sets world matrix for current viewport.
	/**
	 * @param w - pointer to new world matrix.
	 */
	void SetWorld(Matrix4fx* w);

	/// Set world matrix to identity matrix for current viewport.
	void SetWorldIdentityMatrix();
	
	/// Sets current texture matrix.
	/**
	 * @param t - pointer to new texture matrix.
	 */
	void SetTextureMatrix(Matrix4fx* t);

	/// Returns current texture matrix.
	/**
	 * @return Returns current texture matrix.
	 */
	Matrix4fx GetTextureMatrix();

	/// Sets current texture matrix to identity matrix.
	void SetTextureIdentityMatrix();

	/// Sets perspective matrix for current viewport.
	/**
	 * @param fovy - field of view in radians.
	 * @param aspect - value.
	 * @param zNear - distance to near view plane.
	 * @param zFar - distance to far view plane.
	 */
	void SetPerspective(Fixed fovy,Fixed aspect,Fixed zNear,Fixed zFar);

	///////////////////////////MATERIAL////////////////////////////////////
	
	/// Sets current material.
	/**
	 * @param m - pointer to new material.
	 */
	void SetMaterial(Material* m);

	/// Returns current material.
	/**
	 * @return Returns current material.
	 */
	Material GetMaterial();

	////////////////////////////LIGHT//////////////////////////////////////

	/// Adds new light source to scene.
	/**
	 * @param light - pointer Light object.
	 */
	void AddLight(ObjRef<Light> light);

	/// Removes light source from scene.
	/**
	 * @param light - pointer Light object.
	 */
	void RemoveLight(ObjRef<Light> light);

	/// Finds and sets all lights located in specified volume by sphere.
	/**
	 * @param pos - sphere position in world coordinate.
	 * @param radius - sphere radius.
	 */
	void SetLight( Vector3fx& pos, Fixed radius );

	/// Computes vertex colors for drawing specified VertexBuffer object. 
	/**
	 * SetLight() need to call first before this function. 
	 * Also after ComputeLightColor() should be call Draw() to send specified 
	 * vertex buffer geometry with light colors to draw queue.
	 * @param vb - pointer to specified VertexBuffer object for lighting.
	 */
	void ComputeLightColor( ObjRef<VertexBuffer> vb );

	/// Sets ambient light color.
	/**
	 * @param ambient - color value. See class Color.
	 */
	void SetAmbientLight( Color ambient );

	/// Returns ambient light color.
	/**
	 * @return Returns ambient light color.
	 */
	Color GetAmbientLight();

	////////////////////////////DRAWING////////////////////////////////////

	/// Sends vertex buffer geometry to draw queue.
	/**
	 * @param vb - pointer to VertexBuffer object.
	 * @param object3d_clip - cliping flags for VertexBuffer object returned by IsVisible().
	 */
	void Draw(ObjRef<VertexBuffer> vb,Int object3d_clip);
	
	/// Performs morphing one vertex buffer to another.
	/**
	 * Performs morphing one vertex buffer to another using base
	 * vertex buffer for getting all need components not present in morphing 
	 * vertex buffer and send result vertex buffer geometry to draw queue.
	 * @param vb_base - pointer to base VertexBuffer object.
	 * @param vb_0 - pointer to start VertexBuffer object.
	 * @param vb_1 - pointer to end VertexBuffer object.
	 * @param li - morphing interpolation value from 0 to 1 in Fixed.
	 * @param object3d_clip - clipping flags for VertexBuffer object returned by IsVisible().
	 */
	void Draw(ObjRef<VertexBuffer> vb_base,ObjRef<VertexBuffer> vb_0,ObjRef<VertexBuffer> vb_1,Fixed li,Int object3d_clip);

	/// Sends Sprite3D object to the draw queue.
	/**
	 * @param sprite_ - pointer to the Sprite3D class object.
	 */
	inline void Draw( ObjRef<Sprite3D> sprite_);

	/// Sends point list to draw queue.
	/**
	 * @param v3 - pointer to Vector3fx points array.
	 * @param color - pointer to points color array.
	 * @param count - number of points to draw.
	 */
	void DrawPointList(Vector3fx* v3,Int* color,Int count);

	/// Sends line list to draw queue.
	/**
	 * @param v0 - pointer to Vector3fx line start points array.
	 * @param v1 - pointer to Vector3fx line end points array.
	 * @param color - pointer to lines color array.
	 * @param count - number of lines to draw.
	 */
	void DrawLineList(Vector3fx* v0,Vector3fx* v1,Int* color,Int count);

	/// Flushes all draw queue for drawing. After drawing clear draw queue. 
	/**
	 * You can call Flush() several times per one frame as for example 
	 * first draw all background and flush it to backbuffer and than draw 
	 * foreground scene on it. 
	 */
	void Flush();

	/// Checks and return sphere visibility by current camera view frustum.
	/**
	 * @param pos - define sphere position in model coordinate. Will be updated by world matrix. 
	 * @param radius - define sphere radius.
	 * @return Returns non zero value if sphere located in current camera view frustum or have intersection with it. 
	 *         See Render_XXXXX_Plane defines for more info.
	 */
	Int IsVisible(Vector3fx& pos,Fixed radius);

	////////////////////////DRAWING MODES//////////////////////////////////

	/// Sets one render mode.
	/**
	 * @param mode - mode to set. 
	 *               See Render_XXXXX_Mode defines for details.
	 */
	inline void SetMode(Int mode);

	/// Clears one render mode.
	/**
	 * @param mode - mode to clear. 
	 *               See Render_XXXXX_Mode defines for details.
	 */
	inline void ClearMode(Int mode);

	/// Checks one render mode.
	/**
	 * @param mode - mode to check. 
	 *               See Render_XXXXX_Mode defines for details.
	 * @return Returns True if mode set else False. 
	 */
	inline Bool CheckMode(Int mode);

	////////////////////////////////FOG////////////////////////////////////

	/// Updates fog.
	/**
	 * Need to call one time after all calls of SetFogColor(), SetFogMode(), 
	 * SetFogDensity(), SetFogStart(), SetFogEnd().
	 */
	void UpdateFog();

	/// Sets fog color.
	/**
	 * @param fog - color value. See class Color.
	 */
	void SetFogColor( Color fog );

	/// Returns fog color.
	/**
	 * @return Returns fog color.
	 */
	Color GetFogColor();

	/// Sets fog mode.
	/**
	 * @param mode - mode to set. 
	 *        See Render_FogMode_XXXXX defines for details.
	 */
	void SetFogMode( Int mode );

	/// Returns fog mode.
	/**
	 *  @return Returns fog mode. 
	 *          See Render_FogMode_XXXXX defines for details.
	 */
	Int GetFogMode();

	/// Sets fog density.
	/**
	 * @param density - density to set.
	 */
	void SetFogDensity( Fixed density );

	/// Returns fog density.
	/**
	 * @return Returns fog density.
	 */
	Fixed GetFogDensity();

	/// Sets fog start distance.
	/**
	 * @param start - start distance.
	 */
	void SetFogStart( Fixed start );

	/// Returns fog start distance.
	/**
	 * @return Returns fog start distance.
	 */
	Fixed GetFogStart();

	/// Sets fog end distance.
	/**
	 * @param end - fog end distance.
	 */
	void SetFogEnd( Fixed end );

	/// Returns fog end distance.
	/**
	 * @return Returns fog end distance.
	 */
	Fixed GetFogEnd();


	//////////////////////////LIGHTMAP/////////////////////////////////////

	/// Finds specified light map by ASCII name.
	/**
	 * @param name_ - pointer to ASCII name for specified light map.
	 * @param type_ - light map type.See class LightMap.
	 * @return Returns pointer to LightMap class object if find complete successfully else NULL pointer.
	 */
	ObjRef<LightMap> FindLightMap(const Char* name_,Int type_);

	/// Finds specified light map by ASCII name and if not found than load it from resource.
	/**
	 * @param name_ - pointer to ASCII name for specified light map.
	 * @param type_ - light map type.See class LightMap.	 
	 * @return Returns pointer to LightMap class object if find or load complete successfully else NULL pointer.
	 */	
	ObjRef<LightMap> LoadLightMap(const Char* name_,Int type_);

	/// Frees all memory used to store all LightMap class objects.
	void FreeAllLightMaps();

	/// Sets current light map.
	/**
	 * @param lmp - pointer to LightMap object.
	 */
	void SetLightMap(ObjRef<LightMap> lmp);

	//////////////////////////TEXTURES/////////////////////////////////////

	/// Finds specified texture by ASCII name in texture queue.
	/**
	 * @param name_ - pointer to ASCII name for specified texture.
	 * @return Returns pointer to Texture class object if find complete successfully else NULL pointer.
	 */
	ObjRef<Texture> FindTexture(const Char* name_);

	/// Finds specified texture by ASCII name in texture queue and if not found than load it from resource. 
	/**
	 * @param name_ - pointer to ASCII name for specified texture. Do not add file extension to this name.
	 * @return Returns pointer to Texture class object if find or load complete successfully else NULL pointer. Also increase found Texture class object reference count by one. 
	 *         See Texture class for more info about supported texture.
	 */	
	ObjRef<Texture> LoadTexture(const Char* name_);

	/// Frees all memory used to store all Texture class objects and all texture queue.
	void FreeAllTextures();

	/// Loads texture animations from texture animation settings file.
	/**
	 *	This function reads the file of texture animation settings and 
	 *	creates new TextureAnimation objects. It stores them to the given list.
	 *  @param ta_list_ - list of texture animation objects to store loaded animations.
	 *	@param file_name_ - name of texture animation settings file.
	 *  @return Returns True, if load successful, else - False.
	 */
	Bool LoadTextureAnimation(vector< ObjRef<TextureAnimation> > & ta_list_, const Char* file_name_);

////////////////////////LOD MANAGEMENT////////////////////////////////////

	/// Loads and apply LOD settings for objects delivered from Object3D class.
	/**
	 *	lod_list_ - lists of objects with different LODs. 
	 *  @param file_name_ - name of file of LOD settings.
	 *  @return Returns True, if loading success, else - False .
	 */
	Bool LoadLODSettings(vector< vector< ObjRef<Basic3D> > > &lod_list_, const Char* file_name_); 

	/// Loads and apply LOD settings for Actor3DAnimation objects list.
	/**
	 *	lod_list_ - list of Actor3DAnimation objects lists with different LODs. 
	 *  @param file_name_ - name of file of LOD settings.
	 *  @return Returns True, if loading success, else - False .
	 */
	Bool LoadLODSettings(vector< ObjRef<Actor3DAnimation> > &lod_list_, const Char* file_name_); 

	/// Selects LOD VB for drawing by using position of camera.
	/**
	 *	Set correct World matrix before you call this function
	 *	It's used to calculate center of VB in the world coordinates.
	 *  @param base_vb_ - pointer to High LOD VB (Base VB).
	 *  @return Returns pointer to the selected VB.
	 */
	ObjRef<VertexBuffer> SelectLODVB(ObjRef<VertexBuffer> base_vb_);

	/// Set camera.
	/**
	 * Render3D need camera access to select LOD levels.
	 * @param camera_ - pointer to the Camera class object.
	 */
	inline void SetCamera(Camera* camera_);

	///////////////////////////////////////////////////////////////////////

	friend class Portal;
	friend class Texture;
	friend class Font3D;
	friend class LightMap;

	friend void SortAndBuildLightMap(Render3D *render, vector< ObjRef<Basic3D> >& b3d_list, const Char *file_name_prefix);

	///////////////////////////////////////////////////////////////////////

	void* display_memory;
	void* cengine;

	///////////////////////////////////////////////////////////////////////

private:

//////////////////////////////////////////////////////////////////////////

	void Draw(ObjRef<Object3D> o3d, ObjRef<VertexBuffer> vb,Material* material,ObjRef<LightMap> lmp,Int object3d_clip);

//////////////////////////////////////////////////////////////////////////

	Int CheckRayObject3D(ObjRef<Object3D> o3d,Vector3fx& p,Vector3fx& d,Fixed& t);
	Int CheckRay(Vector3fx& p,Vector3fx& d,Fixed& t);
	Fixed CheckRayNearObject3D(ObjRef<Object3D> o3d,Vector3fx& p,Vector3fx& d,Fixed& t);
	Fixed CheckRay(Vector3fx& p,Vector3fx& d,vector< ObjRef<Basic3D> >& o3d_list);

//////////////////////////////////////////////////////////////////////////

	void BuildLightMap(ObjRef<Object3D> o3d,vector< ObjRef<Object3D> >& o3d_list,vector< ObjRef<Light> >& light_list,const Char *file_name_prefix);
	void BuildDynamicLightMap(Vector3fx& A,Vector3fx& B,Vector3fx& C,Vector3fx& n,Light& L,vector<Vertex>& vdlm,vector<Word>& indxdlm);

//////////////////////////////////////////////////////////////////////////

	void Intersection(Point& p1,Point& p2, Point& p);
	int Visible(Point& p);
	void Clipping(vector<Point>& P,vector<Point>& W,vector<Point>& Q);

	Int ClipPolygon(Int numPoints,Vertex** poly,Int plane_clip);

	Int TestClip(Vector3fx& min,Vector3fx& max,Int plane_clip);

	Int GetClipFlag(Vector3fx& pos,Fixed radius,Int plane_clip);

//////////////////////////////////////////////////////////////////////////

	void MakeLightColorTable();

//////////////////////////////////////////////////////////////////////////

	void Transform(Vector3fx* v3,Vector3fx* v4,Int count,Int v3_stride=3,Int v4_stride=3);

	Bool DrawTriangle(Triangle* tri);

	Bool DrawClippedTriangle(TriangleS* tri);
	
	void DrawPoint(Vector3fx* v3,Int color);
	void DrawLine(Vector3fx* v0,Vector3fx* v1,Int color);


//////////////////////////////////////////////////////////////////////////

	System *system;

//////////////////////////////////////////////////////////////////////////

//	Vector3fx frustum_vertex[8];
	
	Plane frustum[6];

	Vector3fx frustum_vertex[8];

	Vertex polygon1[ 16 ];
	Vertex polygon2[ 16 ];

//////////////////////////////////////////////////////////////////////////

	//XScanLineInfo* xscanline;

	Float32* cache_z;
	Byte* cache_flag; 
	Int* cache_sx;
	Int* cache_sy;

//////////////////////////////////////////////////////////////////////////

	int SCR_X;
	int SCR_Y;
	int SCR_BPP;

	int WINDOW_X1;
	int WINDOW_Y1;
	int WINDOW_X2;
	int WINDOW_Y2;

	int SCR_REDBITS, SCR_GREENBITS, SCR_BLUEBITS;

	DWord* DISPLAY;
	DWord* DISPLAY4x;

	DWord* COLOR_TABLE_LIGHT;

	Vector3fx* vb_out;
//	TriangleS* triangle_alpha;

	int BlitGDMode;

	Int RenderClearColor;

	Int RenderClearDepth;

	Matrix4fx RenderViewMatrix;
	Matrix4fx RenderWorldMatrix;
	Matrix4fx RenderModelMatrix;

	Float32 RenderZNear,RenderZFar;
	Float32 RenderXPerspective,RenderYPerspective;

	Int RenderX,RenderY,RenderWidth,RenderWidth2,RenderHeight,RenderHeight2;

	//Int DrawVBCount=0;
	//Int DrawVBZClipCount=0;
	//Int DrawVBXYClipCount=0;


//	Int triangle_alpha_count;

	vector< ObjRef<Light> > RenderLightList;

	ObjRef<LightMap> light_lightmap;
	

	vector< ObjRef<LightMap> > lightmap_list;

	vector< ObjRef<Object3D> >* light_o3d_list;
	vector< ObjRef<Light> >* light_light_list;
	vector<Int>* light_triangle_offset;
	vector<Word>* light_triangle_colors;
	ObjRef<Object3D> light_o3d;
	Int light_triangle_number;
	Word light_tri_sub_div;
	Vector3fx light_tri_n_xyz;

#define LIGHTMAPSIZE 256

	Int LightMapXBorder[LIGHTMAPSIZE][2];

	vector<Point> P;
	vector<Point> W;
	vector<Point> Q;


	Fixed w1x,w1y,w2x,w2y,w2x_minus_w1x,w2y_minus_w1y;


	vector< ObjRef<Texture> > texture_list;
	Texture xtx[2];
	DWord xtxst;
	DWord xtxstl;
	Fixed xfovy, xaspect, xzNear, xzFar;


	PackDir* packdir;


	Material material;

	ObjRef<LightMap> lmp;

	string str_name;


	ObjRef<Light> light[8];
	Fixed light_dist[8];
	Fixed light_A[8];
	Int light_count;

	Int* intensity;

	ObjRef<VertexBuffer> rvb;

	Byte* raster;
	Int *div32;

	TriangleS* tri_heap;
	TriangleS** tri_heap_sort;
	Int tri_heap_size;
	Int tri_heap_count;

//////////////////////////////////////////////////////////////////////////

	DWord modes;

//////////////////////////////////////////////////////////////////////////

	Color ambient_light;

	Bool world_matrix_is_identity;

	Matrix4fx InverseRenderWorldMatrix;

//////////////////////////////////////////////////////////////////////////

	Pixel* COLORS_TABLE_FOG;

	Int fog_mode;

	Color fog_color;

	Fixed fog_density;

	Fixed fog_start;
	Fixed fog_end;

	DWord fog_z_s;
	DWord fog_z_e;
	Int fog_z_shift;

//////////////////////////////////////////////////////////////////////////

	Matrix4fx texture_matrix;

	Bool is_texture_matrix_identity;

//////////////////////////////////////////////////////////////////////////

////////////////////////SETTINGS LOADING//////////////////////////////////
	
	/// Header size in bytes.
	#define ID_HEADER_SIZE			 4 

	/// Group header.
	#define ID_HEADER_GROUP 0xAAAAAAAA 

	/// Resource to load settings.
	Resource sett;

	/// block Header in settings file.
	Int header;

	/// next block pointer in settings file
	Int next_block_pointer;

	string str_sett1;
	string str_sett2;

////////////////////////LOD MANAGEMENT////////////////////////////////////

	
	/// LOD radiuses
	vector<Fixed> lod_radiuses;

	ObjRef<VertexBuffer> lod_vb;

	vector< ObjRef<Basic3D> > separate_nodes;

	Camera* camera;

	Vector3fx at_point;
	Vector3fx to_point;

////////////////////////////SPRITES///////////////////////////////////////

	void DrawSprites();

	void BuildSpriteVB(ObjRef<Sprite3D>spr_, const Vector3fx& axis_x_, const Vector3fx& axis_y_);

	vector< ObjRef<Sprite3D> > spr_draw_list;

	/// Array of indices.
	Word* spr_indices;

	/// Current indices count.
	Word spr_indices_count;

	/// Max indices count.
	Word spr_indices_max_count;

	/// Basis vectors.
	Vector3fx axis_x;
	Vector3fx axis_y;

//////////////////////////////////////////////////////////////////////////

};

/////////////////////////////INLINES///////////////////////////////////////

inline void Render3D::SetMode(Int mode)
{
	modes |= mode;
}

inline void Render3D::ClearMode(Int mode)
{
	modes &= ~mode;
}

inline Bool Render3D::CheckMode(Int mode)
{
	return modes & mode;
}

inline void Render3D::SetCamera(Camera* camera_)
{ 
	camera = camera_; 
}

inline void Render3D::Draw( ObjRef<Sprite3D> sprite_) 
{ 
	spr_draw_list.push_back(sprite_); 
}
///////////////////////////////////////////////////////////////////////////

} //namespace mdragon

#endif // __MD_RENDER3D_H__