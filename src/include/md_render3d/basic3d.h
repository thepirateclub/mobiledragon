/** \file
 *	Basic 3d object class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_BASIC3D_H__
#define __MD_BASIC3D_H__

///////////////////////////////////////////////////////////////////////////


namespace mdragon
{

/* Control Basic3D object flags. Sixteen low bits reserved for system. */

/// Is object static.
#define Basic3D_Flag_Static (1<<0)

/// Is object visible.
#define Basic3D_Flag_Visible (1<<1)

/// Object detect collisions.
#define Basic3D_Flag_Collide (1<<2)

/// Is object locked.
#define Basic3D_Flag_Lock (1<<3)


class CustomData;


/// Basic 3d object.
class Basic3D : public Object
{
protected:
	
	/// Default constructor.
	Basic3D();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Basic3D(Render3D* render_);

	/// Destructor.
	virtual ~Basic3D();

public:

	/// Creates new Basic3D.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Basic3D.
	 */
	static ObjRef<Basic3D> New()
	{
		return ObjRef<Basic3D>( new Basic3D );
	}

	/// Creates new Basic3D.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Basic3D.
	 */
	static ObjRef<Basic3D> New( Render3D* render_ )
	{
		return ObjRef<Basic3D>( new Basic3D(render_) );
	}

	/// Sends object to draw queue.
	virtual void Draw();

	/// Update object result transform matrix.
	/**
	 * Need to call after object matrix transform update. 
	 */
	virtual void UpdateTransform();

	/// Returns object result transform matrix.
	/**
	 * @return Returns object result transform matrix.
	 */
	virtual Matrix4fx GetResultTransform();

	/// Returns Basic3D class id.
	/**
	 * @return Returns Basic3D class id.
	 */
	virtual Int GetClassID();

	/// Returns control Basic3D object flags.
	/**
	 * By default only Visible flag is set.
	 * @return Returns control Basic3D object flags.
	 */
	inline DWord GetFlags() { return flags; }

	/// Sets control Basic3D object flags.
	/**
	 * Warning! Sixteen low bits reserved for system.
	 * @param flags_ define control Basic3D object flags.
	 */
	inline void SetFlags(DWord flags_) { flags = flags_; }

	/// Checks one specified control Basic3D object flag.
	/**
	 * @param f define specified control Basic3D object flag to check.
	 * @return Returns True if flag is set else False.
	 */
	inline Bool CheckFlag(Int f) { return flags & f;	}

	/// Set one specified control Basic3D object flag.
	/**
	 * @param f define specified control Basic3D object flag to set.
	 */
	inline void SetFlag(Int f) { flags |= f; }

	/// Clears one specified control Basic3D object flag.
	/**
	 * @param f define specified control Basic3D object flag to clear.
	 */
	inline void ClearFlag(Int f) { flags &= ~f;	}

	/// Check is object visible. Not visible object will be not rendered.
	/**
	 * @return Returns True if object visible flag is set else False.
	 */
	inline Bool IsVisible() { return CheckFlag( Basic3D_Flag_Visible ); }

	/// Set object visible flag.
	/**
	 * @param visible - define new value for object visible flag. 
	 *                  If True than object visible flag will be 
	 *                  set else clear it.
	 */
	inline void SetVisible(Bool visible) { if( visible ) SetFlag( Basic3D_Flag_Visible ); else	ClearFlag( Basic3D_Flag_Visible ); }

	/// Returns ASCII name for this object.
	/**
	 * @return Returns ASCII name for this object.
	 */
	inline const string & GetName() { return name; }

	/// Returns pointer to parent object.
	/**
	 * @return Returns pointer to parent object.
	 */
	inline ObjRef<Basic3D> GetParent() { return parent; }

	/// Returns object node id.
	/**
	 * @return Returns object node id.
	 */
	inline Int GetNodeID() { return node_id; }

	/// Sets ASCII name for this object.
	/**
	 * @param name_ - object's name.
	 */
	inline void SetName(const Char* name_) { name = name_; }

	/// Sets pointer to parent object.
	/**
	 * @param parent_ - pointer to the parent object.
	 */
	inline void SetParent(ObjRef<Basic3D> parent_) { parent = parent_; }

	/// Set object node id.
	/**
	 * @param node_id_ - object node id.
	 */
	inline void SetNodeID(Int node_id_) { node_id = node_id_; }

	/// Sets object's result transform matrix.
	/**
	 * @param rm - new object's result transform matrix.
	 */
	virtual void SetResultTransform(const Matrix4fx& rm);

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }

	/// Store custom data exported from 3D Max.
	CustomData* cd;

protected:

	/// Control Basic3D object flags
	DWord flags;

	/// Object's name.
	string name;

	/// Parent object.
	ObjRef<Basic3D> parent;
	
	/// Node ID exported from 3D Max.
	Int node_id;

	/// Pointer to the Render3D class object.
	Render3D * render;
	
};

} //namespace mdragon

#endif // __MD_BASIC3D_H__