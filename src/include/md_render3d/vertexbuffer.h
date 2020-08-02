/** \file
 *	Vertex buffer class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_VERTEXBUFFER_H__
#define __MD_VERTEXBUFFER_H__

namespace mdragon
{

/// QuadIndex class represents set of indexes to describe square polygon.
class QuadIndex
{
public:

	/// Indexes
	Word i0,i1,i2,i3;
};


/*	Flags to describe VB contents (VB format). */

/// VB has vertex X,Y,Z.
#define VertexBuffer_Format_Vxyz (1<<0)

/// VB has vertex Normal X,Y,Z.
#define VertexBuffer_Format_Nxyz (1<<1)

/// VB has triangle Normal X,Y,Z.
#define VertexBuffer_Format_TriNxyz (1<<2)

/// VB has UV for diffuse texture.
#define VertexBuffer_Format_UV0 (1<<3)

/// VB has UV for lightmap or some else.
#define VertexBuffer_Format_UV1 (1<<4)

/// VB has vertex light intensity.
#define VertexBuffer_Format_Intensity (1<<5)

/// VB has linked LOD VB.
#define VertexBuffer_Format_LOD (1<<6)

/// VB stores index.
#define VertexBuffer_Format_Index (1<<10)

/// VB is packed.
#define VertexBuffer_Format_Packed (1<<15)


/* Access flags. */

/// Lock VB for reading.
#define VertexBuffer_LockType_Read 1

/// Lock VB for writing.
#define VertexBuffer_LockType_Write 2


class Object3D;
class Light;
class CollisionManager;


/// VertexBuffer (farther VB) represents geometry container.
/**
 * VB may contain various geometry data: vertex coordinates, vertex normals, 
 * triangle normals, two levels of UV coordinates (UV0 and UV1), vertex light
 * intensity, indexes. VB may link to another VB with different Level of Detail.
 * To access to VB, you need to lock it before.
 * There is three types of locking: for reading only, for writing only and
 * for reading and writing at the same time.
 */
class VertexBuffer : public Object
{
	////////////////////////COMMON//////////////////////////
protected:

	/// Default constructor.
	/**
	 *	Create empty VB.
	 */
	VertexBuffer();

	/// Copy constructor.
	/**
	 *	Creates copy of another VB.
	 *	@param vb - source VB.
	 */
	VertexBuffer( VertexBuffer& vb);

	/// Destructor.
	/**
	 *	Free all memory used by VB. Delete all geometry data.
	 */
	~VertexBuffer();

public:

	/// Creates new Vertex Buffer.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Return object reference to new Vertex Buffer.
	 */
	static ObjRef<VertexBuffer> New()
	{
		return ObjRef<VertexBuffer>( new VertexBuffer );
	}

	/// Creates copy of another Vertex Buffer.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Return object reference to new Vertex Buffer.
	 */
	static ObjRef<VertexBuffer> New( VertexBuffer & vb )
	{
		return ObjRef<VertexBuffer>( new VertexBuffer( vb ) );
	}

	/// Sets ASCII name for this object.
	/**
	 *  @param name_ - object's name.
	 */
	inline void SetName(const Char* name_) { name = name_; }
	
	/// Returns name for this object.
	/**
	 *	@return Return name for this object.
	 */
	inline const string & GetName() { return name; }
	

	/////////////////////INITIALIZATION/////////////////////

	/// Initializes VB.
	/**
	 *	Sets format, vertex_count and index count.
	 *	Computes and allocate necessary memory.
	 *  Calling this function don't clear memory allocated before for VB, 
	 *	so you should call it only once.
	 *	This function don't create linked LOD VB! 
	 *	You may create and link it manually. 
	 *  @param format_ - VB format.
	 *  @param vertex_count_ - necessary vertex count.
	 *  @param index_count_ - necessary index count
	 *  @return Return True, if initialization successful, else - False.
	 */
	Bool Init(Int format_,Word vertex_count_,Word index_count_);


	/////////////////////GEOMETRY INFO//////////////////////

	/// Return current vertex count.
	/**
	 *  @return Return current vertex count.
	 */
	inline Word GetVertexCount() { return vertex_count; }

	/// Return current index count.
	/**
	 *  @return Return current index count.
	 */
	inline Word GetIndexCount() { return index_count; }
	
	/// Return max vertex count.
	/**
	 *  @return Return max vertex count.
	 */
	inline Word GetMaxVertexCount() { return max_vertex_count; }

	/// Return max index count.
	/**
	 *  @return Return max index count.
	 */
	inline Word GetMaxIndexCount() { return max_index_count; }

	/// Sets current vertex count.
	/**
	 *  @param count - vertex count.
	 */
	inline void SetVertexCount(Word count) { vertex_count = count; if(vertex_count > max_vertex_count) vertex_count = max_vertex_count; }

	/// Sets current index count.
	/**
	 *  @param count - index count.
	 */
	inline void SetIndexCount(Word count) { index_count = count; if(index_count > max_index_count) index_count = max_index_count; }


	//////////////////////////FORMAT////////////////////////

	/// Return VB format.
	/**
	 *  @return Return VB format.
	 */
	inline Int GetFormat() { return format; }

	/// Checks if VB format flag is set.
	/**
	 *  @param format_ - format flag for checking.
	 *  @return Return True, if format flag is set, else - False.
	 */
	inline Bool CheckFormat(Int format_) { return format & format_; }

	
	//////////////////////BOUNDING BODIES///////////////////

	/// Return Axis Aligned Bounding Box (AABB) for VB.
	/**
	 *  @return Return Axis Align Box (AABB) for VB.
	 */
	inline AABB GetAAB() { return AABB(min,max); }

	/// Return Min value of Axis Align Bounding Box for VB.
	/**
	 *  @return Return Min value of Axis Align Bounding Box for VB.
	 */
	inline Vector3fx GetMin() { return min; }

	/// Return Max value of Axis Align Bounding Box for VB.
	/**
	 *  @return Return Min value of Axis Align Bounding Box for VB.
	 */
	inline Vector3fx GetMax() { return max; }

	/// Return center of Bounding Sphere of VB.
	/**
	 *  @return Return center of Bounding Sphere of VB.
	 */
	inline Vector3fx GetCenter() { return center; }

	/// Return radius of Bounding Sphere of VB.
	/**
	 *  @return Return radius of Bounding Sphere of VB.
	 */
	inline Fixed GetRadius() { return radius; }

	
	////////////////////////ACCESS CONTROL//////////////////

	/// Locks VB.
	/**
	 *  Call this function before acces to VB.
	 *  @param lock_type - access flag (for reading, writing, reading & writing).
	 */
	void Lock(Int lock_type);

	/// Unlocks VB. 
	/**
	 *  Call this function after all VB changes will made.
	 */
	void UnLock();


	/////////////////////READING DATA ACCESS////////////////
	
	/// Reads X, Y, Z values for one vertex.
	/**
	 *  @param i - vertex index.
	 *  @param v_xyz_ - buffer to store X, Y and Z values of vertex (array of 3 elements).
	 */
	inline void ReadVxyz(Word i,Fixed *v_xyz_) { Int n=i*v_xyz_stride; v_xyz_[0]=v_xyz[n]; v_xyz_[1]=v_xyz[n+1]; v_xyz_[2]=v_xyz[n+2]; }
	
	/// Reads X, Y, Z values for one vertex normal.
	/**
	 *  @param i - vertex normal index.
	 *  @param n_xyz_ - buffer to store X, Y and Z values of vertex normal (array of 3 elements).
	 */
	inline void ReadNxyz(Word i,Fixed *n_xyz_)  { Int n=i*n_xyz_stride; n_xyz_[0]=n_xyz[n]; n_xyz_[1]=n_xyz[n+1]; n_xyz_[2]=n_xyz[n+2]; }

	/// Reads X, Y, Z values for one triangle normal.
	/**
	 *  @param i - triangle normal index.
	 *  @param tri_n_xyz_ - buffer to store X, Y and Z values of tringle normal (array of 3 elements).
	 */
	inline void ReadTriNxyz(Word i,Fixed *tri_n_xyz_)  { Int n=i*tri_n_xyz_stride; tri_n_xyz_[0]=tri_n_xyz[n]; tri_n_xyz_[1]=tri_n_xyz[n+1]; tri_n_xyz_[2]=tri_n_xyz[n+2]; }

	/// Reads U, V values for one UV vertex of 0 channel.
	/**
	 *  @param i - UV vertex index.
	 *  @param uv_0_ - buffer to store U and V values of UV vertex of 0 channel (array of 2 elements).
	 */
	inline void ReadUV0(Word i,Fixed *uv_0_)  { Int n=i*uv_0_stride; uv_0_[0]=uv_0[n]; uv_0_[1]=uv_0[n+1]; }

	/// Reads U, V values for one UV vertex of 1 channel.
	/**
	 *  @param i - UV vertex index.
	 *  @param uv_1_ - buffer to store U and V values of UV vertex of 1 channel (array of 2 elements).
	 */
	inline void ReadUV1(Word i,Fixed *uv_1_)  { Int n=i*uv_1_stride; uv_1_[0]=uv_1[n]; uv_1_[1]=uv_1[n+1]; }

	/// Reads intensity value for one vertex.
	/**
	 *  @param i - vertex intensity index.
	 *  @param intensity_ - buffer to store intensity value.
	 */
	inline void ReadIntensity(Word i,Int *intensity_)  { Int n=i*intensity_stride; *intensity_=intensity[n]; }

	/// Reads X, Y, Z values for one packed vertex.
	/**
	 *  @param i - packed vertex index.
	 *  @param v_xyz_ - buffer to store X, Y and Z values of packed vertex (array of 3 elements).
	 */
	inline void ReadVxyzPacked(Word i,Short *v_xyz_) { Int n=i*v_xyz_stride; Short* v_xyz_p=(Short*)v_xyz; v_xyz_[0]=v_xyz_p[n]; v_xyz_[1]=v_xyz_p[n+1]; v_xyz_[2]=v_xyz_p[n+2]; }

	/// Reads X, Y, Z values for one packed vertex normal.
	/**
	 *  @param i - packed vertex normal index.
	 *  @param n_xyz_ - buffer to store X, Y and Z values of packed vertex normal (array of 3 elements).
	 */
	inline void ReadNxyzPacked(Word i,Short *n_xyz_)  { Int n=i*n_xyz_stride; Short* n_xyz_p=(Short*)n_xyz; n_xyz_[0]=n_xyz_p[n]; n_xyz_[1]=n_xyz_p[n+1]; n_xyz_[2]=n_xyz_p[n+2]; }

	/// Reads X, Y, Z values for one packed triangle normal.
	/**
	 *  @param i - packed triangle normal index.
	 *  @param tri_n_xyz_ - buffer to store X, Y and Z values of packed tringle normal (array of 3 elements).
	 */
	inline void ReadTriNxyzPacked(Word i,Short *tri_n_xyz_)  { Int n=i*tri_n_xyz_stride; Short* tri_n_xyz_p=(Short*)tri_n_xyz; tri_n_xyz_[0]=tri_n_xyz_p[n]; tri_n_xyz_[1]=tri_n_xyz_p[n+1]; tri_n_xyz_[2]=tri_n_xyz_p[n+2]; }
	
	/// Reads U, V values for one packed UV vertex of 0 channel.
	/**
	 *  @param i - packed UV vertex index.
	 *  @param uv_0_ - buffer to store U and V values of packed UV vertex of 0 channel (array of 2 elements).
	 */
	inline void ReadUV0Packed(Word i,Short *uv_0_)  { Int n=i*uv_0_stride; Short* uv_0_p=(Short*)uv_0; uv_0_[0]=uv_0_p[n]; uv_0_[1]=uv_0_p[n+1]; }

	/// Reads U, V values for one packed UV vertex of 1 channel.
	/**
	 *  @param i - packed UV vertex index.
	 *  @param uv_1_ - buffer to store U and V values of packed UV vertex of 1 channel (array of 2 elements).
	 */
	inline void ReadUV1Packed(Word i,Short *uv_1_)  { Int n=i*uv_1_stride; Short* uv_1_p=(Short*)uv_1; uv_1_[0]=uv_1_p[n]; uv_1_[1]=uv_1_p[n+1]; }


	/////////////////////WRITING DATA ACCESS////////////////

	/// Writes X, Y, Z values for one vertex.
	/**
	 *  @param i - vertex index.
	 *  @param v_xyz_ - X, Y and Z values of vertex (array of 3 elements).
	 */
	inline void WriteVxyz(Word i,Fixed *v_xyz_) { Int n=i*v_xyz_stride; v_xyz[n]=v_xyz_[0]; v_xyz[n+1]=v_xyz_[1]; v_xyz[n+2]=v_xyz_[2]; }

	/// Writes X, Y, Z values for one vertex normal.
	/**
	 *  @param i - vertex normal index.
	 *  @param n_xyz_ - X, Y and Z values of vertex normal (array of 3 elements).
	 */
	inline void WriteNxyz(Word i,Fixed *n_xyz_) { Int n=i*n_xyz_stride; n_xyz[n]=n_xyz_[0]; n_xyz[n+1]=n_xyz_[1]; n_xyz[n+2]=n_xyz_[2]; }

	/// Writes X, Y, Z values for one triangle normal.
	/**
	 *  @param i - triangle normal index.
	 *  @param tri_n_xyz_ - X, Y and Z values of tringle normal (array of 3 elements).
	 */
	inline void WriteTriNxyz(Word i,Fixed *tri_n_xyz_) { Int n=i*tri_n_xyz_stride; tri_n_xyz[n]=tri_n_xyz_[0]; tri_n_xyz[n+1]=tri_n_xyz_[1]; tri_n_xyz[n+2]=tri_n_xyz_[2]; }
	
	/// Writes U, V values for one UV vertex of 0 channel.
	/**
	 *  @param i - UV vertex index.
	 *  @param uv_0_ - U and V values of UV vertex of 0 channel (array of 2 elements).
	 */
	inline void WriteUV0(Word i,Fixed *uv_0_) { Int n=i*uv_0_stride; uv_0[n]=uv_0_[0]; uv_0[n+1]=uv_0_[1]; }
	
	/// Writes U, V values for one UV vertex of 1 channel.
	/**
 	 *  @param i - UV vertex index.
 	 *  @param uv_1_ - U and V values of UV vertex of 1 channel (array of 2 elements).
	 */
	inline void WriteUV1(Word i,Fixed *uv_1_) { Int n=i*uv_1_stride; uv_1[n]=uv_1_[0]; uv_1[n+1]=uv_1_[1]; }
	
	/// Writes intensity value for one vertex.
	/**
	 *  @param i - vertex intensity index.
	 *  @param intensity_ - intensity value.
	 */
	inline void WriteIntensity(Word i,Int intensity_) { Int n=i*intensity_stride; intensity[n]=intensity_; }

	/// Writes X, Y, Z values for one packed vertex.
	/**
	 *  @param i - packed vertex index.
	 *  @param v_xyz_ - X, Y and Z values of packed vertex (array of 3 elements).
	 */
	inline void WriteVxyzPacked(Word i,Short *v_xyz_) { Int n=i*v_xyz_stride; Short* v_xyz_p=(Short*)v_xyz; v_xyz_p[n]=v_xyz_[0]; v_xyz_p[n+1]=v_xyz_[1]; v_xyz_p[n+2]=v_xyz_[2]; }
	
	/// Writes X, Y, Z values for one packed vertex normal.
	/**
	 *  @param i - packed vertex normal index.
	 *  @param n_xyz_ - X, Y and Z values of packed vertex normal (array of 3 elements).
	 */
	inline void WriteNxyzPacked(Word i,Short *n_xyz_) { Int n=i*n_xyz_stride; Short* n_xyz_p=(Short*)n_xyz; n_xyz_p[n]=n_xyz_[0]; n_xyz_p[n+1]=n_xyz_[1]; n_xyz_p[n+2]=n_xyz_[2]; }
	
	/// Writes X, Y, Z values for one packed triangle normal.
	/**
	 *  @param i - packed triangle normal index.
	 *  @param tri_n_xyz_ - X, Y and Z values of packed tringle normal (array of 3 elements).
	 */
	inline void WriteTriNxyzPacked(Word i,Short *tri_n_xyz_) { Int n=i*tri_n_xyz_stride; Short* tri_n_xyz_p=(Short*)tri_n_xyz; tri_n_xyz_p[n]=tri_n_xyz_[0]; tri_n_xyz_p[n+1]=tri_n_xyz_[1]; tri_n_xyz_p[n+2]=tri_n_xyz_[2]; }
	
	/// Writes U, V values for one packed UV vertex of 0 channel.
	/**
	 *  @param i - packed UV vertex index.
	 *  @param uv_0_ - U and V values of packed UV vertex of 0 channel (array of 2 elements).
	 */
	inline void WriteUV0Packed(Word i,Short *uv_0_) { Int n=i*uv_0_stride; Short* uv_0_p=(Short*)uv_0; uv_0_p[n]=uv_0_[0]; uv_0_p[n+1]=uv_0_[1]; }

	/// Writes U, V values for one paked UV vertex of 1 channel.
	/**
	 *  @param i - packed UV vertex index.
	 *  @param uv_1_ - U and V values of packed UV vertex of 1 channel (array of 2 elements).
	 */
	inline void WriteUV1Packed(Word i,Short *uv_1_) { Int n=i*uv_1_stride; Short* uv_1_p=(Short*)uv_1; uv_1_p[n]=uv_1_[0]; uv_1_p[n+1]=uv_1_[1]; }


	////////////////READING & WRITING DATA ACCESS///////////

	/// Provides access to index value.
	/**
	 *  @param i - index for indexes array.
	 *  @return Return reference to index value in the indexes array.
	 */
	inline Word& Index(Word i) { return index[i]; }

	/// Provides access to index value for first (A) vertex of triangle.
	/**
	 *  @param i - index of triangle.
	 */
	inline Word& IndexA(Word i) { return index[i*3]; }
	
	/// Provides access to index value for second (B) vertex of triangle.
	/**
	 *  @param i - index of triangle.
	 */
	inline Word& IndexB(Word i) { return index[i*3+1]; }
	
	/// Provides access to index value for third (C) vertex of triangle.
	/**
	 *  @param i - index of triangle.
	 */
	inline Word& IndexC(Word i) { return index[i*3+2]; }
	
	///////////////////////LOD MANAGEMENT///////////////////

	/// Links LOD VB to this VB.
	/**
	 *	This function will add LOD VB into chain linked VBs by LOD radius 
	 *  increment.
	 *	@param lod_vb_ - pointer to linking LOD VB.
	 */
	void AddLODVB(ObjRef<VertexBuffer> lod_vb_);

	/// Detaches child LOD VB and all its children from this VB.
	void RemoveLODVB();

	/// Return pointer to child LOD VB of this VB.
	/**
	 *	@return Return pointer to child LOD VB of this VB.
	 */
	inline ObjRef<VertexBuffer> GetLODVB() { return vb_lod; }

	/// Sets LOD switch radius.
	/**
	 *  @param radius_ - middle LOD switch radius.
	 */
	inline void SetLODSwitchRadius(const Fixed& radius_) { lod_switch_radius = (radius_ < F_ZERO) ? F_ZERO : radius_; }

	/// Return LOD switch radius.
	/**
	 *  @return Return LOD switch radius.
	 */
	inline Fixed GetLODSwitchRadius() { return lod_switch_radius; }

	//////////////////////////UTILITY///////////////////////

	/// Transforms VB by transformation matrix.
	/**
	 *	Transformation matrix transforms vertexes (Vxyz), 
	 *  vertex normals (Nxyz) and triangle normals (TriNxyz).
	 *  @param transform - transformation matrix.
	 */
	void Transform(Matrix4fx* transform);

	/// Computes new vertex and triangle normals for VB.
	void UpdateNormal();

	/// Computes Weld vertex array.
	void BuildXYZ();

	/// Copies data of given source VB to this VB.
 	/**
 	 *  @param src_vb_ - source VB.
 	 *  @param format_ - format. Describe which data will be copied.
 	 *	                 If this parameter value is negative (by default), 
	 *                   then all source VB data will be copied.
	 *	                 If format_ has VertexBuffer_Format_LOD flag, 
	 *                   than function will copy data from LOD VBs of 
	 *                   source VB to LOD VBs of this VB (if it has their).
 	 *  @return Return True, if VB copied successful, else - False.
	 */
	Bool Copy( VertexBuffer & src_vb_, Int format_ = -1);


	friend class Object;
	friend class Render3D;
	friend class Object3D;
	friend class CollisionManager;

private:

	/// Compute Bounding Box for VB.
	void ComputeBoundingBox();

	friend void BuildLightMap(ObjRef<Object3D> o3d,vector< ObjRef<Object3D> >& o3d_list,vector< ObjRef<Light> >& light_list);

	////////////////////////COMMON//////////////////////////
	
	/// Name of VB.
	string name;

	/////////////////////GEOMETRY INFO//////////////////////

	/// Current Vertex count
	Word vertex_count;

	/// Max vertex count.
	Word max_vertex_count;

	/// Current index count
	Word index_count;

	/// Max index count.
	Word max_index_count;

	//////////////////////////FORMAT////////////////////////
	
	/// Format of VB.
	Int format;
	
	//////////////////////BOUNDING BODIES///////////////////

	/// Min value of Bounding Box of VB.
	Vector3fx min;
	
	/// Max value of Bounding Box of VB.
	Vector3fx max;
	
	/// Center of Bounding Sphere of VB.
	Vector3fx center;
	
	/// Radius of Bounding Sphere of VB.
	Fixed radius;

	////////////////////////ACCESS CONTROL//////////////////
	
	/// Current Lock Type.
	Int lock_type;
	
	/// Locks counter.
	Int lock_counter;

	/// If was write lock.
	Bool was_write_lock;

	////////////////////////GEOMETRY DATA///////////////////
	
	/// Stride for vertex X, Y, Z array.
	Int v_xyz_stride;

	/// Stride for vertex Normal X, Y, Z array.
	Int n_xyz_stride;

	/// Stride for triangle Normal X, Y, Z array.
	Int tri_n_xyz_stride;

	/// Stride for vertex U, V (0 channel) array.
	Int uv_0_stride;

	/// Stride for vertex U, V (1 channel) array.
	Int uv_1_stride;

	/// Stride for vertex intensity array.
	Int intensity_stride;

	/// Indexes array.
	Word* index;

	/// Vertex X, Y, Z array.
	Fixed *v_xyz;

	/// Vertex Normal X, Y, Z array.
	Fixed *n_xyz;

	/// Vertex U, V (0 channel) array.
	Fixed *uv_0;

	/// Vertex U, V (1 channel) array.
	Fixed *uv_1;

	/// Vertex intensity array.
	Int *intensity;

	/// Triangles normals array.
	Fixed *tri_n_xyz;

	/// Square polygons indexes array.
	QuadIndex* quad;

	/// Square polygons count.
	Int quad_count;

	/// Weld vertex X, Y, Z array.  
	Fixed *xyz;

	/// Weld vertex count.
	Int xyz_count;

	/// Weld vertex indexes array.
	Word *xyz_index;

	///////////////////////LOD MANAGEMENT///////////////////
	
	/// Child LOD VB.
	ObjRef<VertexBuffer> vb_lod;

	/// Switch radius for VB in LOD system.
	Fixed lod_switch_radius;

};

} //namespace mdragon

///////////////////////////////////////////////////////////////////////////
#endif // __MD_VERTEXBUFFER_H__