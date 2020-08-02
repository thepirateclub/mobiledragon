/** \file
 *	Static 3d object class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_OBJECT3D_H__
#define __MD_OBJECT3D_H__

namespace mdragon 
{

/// Common 3d object.
/**
 * This 3d object has one VertexBuffer object and list of child 
 * (Basic3D) objects. 
 */
class Object3D : public Basic3D
{
protected:

	/// Default constructor.
	Object3D();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Object3D(Render3D* render_);

	/// Destructor.
	~Object3D();

public:
	
	/// Creates new Object3D.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Object3D.
	 */
	static ObjRef<Object3D> New()
	{
		return ObjRef<Object3D>( new Object3D );
	}

	/// Creates new Object3D.
	/**  
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Object3D.
	 */
	static ObjRef<Object3D> New( Render3D* render_ )
	{
		return ObjRef<Object3D>( new Object3D(render_) );
	}
	
	/// Sends object and all its children to the draw queue.
	void Draw();

	/// Updates result transform matrices of objects and all its children.
	/**
	 * Need to call after object matrix transform update. 
	 */
	void UpdateTransform();

	/// Returns object result transform matrix.
	/**
	 * @return Returns object result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Returns Object3D class id.
	/**
	 * @return Returns Object3D class id.
	 */
	Int GetClassID();

	/// Transforms object VertexBuffer to the world coordinates using result transform matrix.
	/**
	 * It does the same with all children objects that have class id of Object3D.
	 * Set relative and result transform matrix to identity matrix. 
	 */
	void TransformToWorld();

	/// Finds child node by name.
	/**
	 *	All child nodes in all child levels applies for searching.
	 *  @param name_ - searching node name.
	 *  @return Returns pointer to the first child with given name, else NULL value (if not found).
	 */
	ObjRef<Basic3D> FindChild(const Char * name_ );

	/// Finds child node by name.
	/**
	 *	Child nodes in first (nearest) child level applies for searching.
	 *  @param name_ - searching node name.
	 *  @return Returns pointer to the first found child node with given name, else NULL value (if not found).
	 */
	ObjRef<Basic3D> FindNearChild(const Char * name_);

	/// Finds child nodes by name and add their into the list.
	/**
	 *	All child nodes in all child levels applies for searching.
	 *  @param name_ - searching node name.
	 *	@param children_list_ - list to save founding nodes.
	 */
	void FindChildren(const Char * name_, vector< ObjRef<Basic3D> > &children_list_);

	/// Create list of all nodes in hierarchy of this object.
	/**
	 *  @param object_list_ - list to add all nodes.
	 */
	void BuildSeparateHierarchy(vector< ObjRef<Basic3D> > &object_list_);

	/// Sets object's result transform matrix.
	/**
  	 * @param rm - new object's result transform matrix.
	 */
	inline void SetResultTransform(const Matrix4fx& rm) { result_transform = rm; }
	
	/// Relative transformation matrix.
	Matrix4fx relative;

	/// Object's material.
	Material material;
	
	/// geometry VB (may link to LOD VB)
	ObjRef<VertexBuffer> vb;

	/// Lightmap
	ObjRef<LightMap> lmp;

	/// List of children objects.
	vector< ObjRef<Basic3D> > children;

protected:

	/// Result transform matrix.
	Matrix4fx result_transform;

	/// VB for LOD drawing
	ObjRef<VertexBuffer> draw_vb;
};

} //namespace mdragon

#endif // __MD_OBJECT3D_H__
