/** \file
 *	Dynamic 3d object class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ROBOT3D_H__
#define __MD_ROBOT3D_H__

namespace mdragon
{

/// 3d objects with own (local) and relative transformations.
/**
 *   This class provides entire control functionality for playing 3d robot animation.
 *   Robot3D has hierarchic tree of 3d objects.
 */
class Robot3D : public Object3D
{
protected:
	
	/// Default constructor.
	Robot3D();

	/// Constructor with given render pointer value.
	/** 
	 * @param render_ - pointer to the Render3D class object.
 	 */
	Robot3D(Render3D* render_);

	/// Destructor.
	~Robot3D();

public:

	///  Creates new Robot3D.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Robot3D.
	 */
	static ObjRef<Robot3D> New()
	{
		return ObjRef<Robot3D>( new Robot3D );
	}

	/// Creates new Robot3D.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Robot3D.
 	 */
	static ObjRef<Robot3D> New( Render3D* render_ )
	{
		return ObjRef<Robot3D>( new Robot3D(render_) );
	}
	
	/// Sends VertexBuffers of this object and its children to the draw queue.
	void Draw();

	/// Updates result transform matrices of object and its children.
	/**
	 * Need to call after object matrix transform update. 
	 */
	void UpdateTransform();

	/// Returns object's result transform matrix.
	/**
	 * @return Returns object's result transform matrix. 
	 */
	Matrix4fx GetResultTransform();

	/// Returns Object3D class id.
	/**
	 * @return Returns Object3D class id.
	 */
	Int GetClassID();

	/// Builds hierarchic tree of 3d objects from specified Object3D object.
	/**
	 * Need to call once time at beginning of creation of Robot3D object.
	 * After this any new calls of Create() are not allowed.
	 * @param o3d - pointer to Object3D class object.
	 */
	void Create( ObjRef<Object3D> o3d );

	/// Sets object's result transform matrix.
	/**
	 * @param rm - new object's result transform matrix.
	 */
	inline void SetResultTransform(const Matrix4fx& rm) { result_transform = rm; }

	/// Local transformation matrix.
	Matrix4fx transform;
};

} //namespace mdragon

#endif // __MD_ROBOT3D_H__