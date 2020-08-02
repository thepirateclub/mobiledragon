/** \file
 *	Tweening 3d animation. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ACTOR3D_H__
#define __MD_ACTOR3D_H__

namespace mdragon
{

class Actor3DAnimation;
class Actor3DAnimationNode;

/// 3d morphing animation object.
/**
 *	This class provides control control over 3d character animation playback. 
 *	Actor3D need to have minimum one node or more for
 *  representing 3d actor character.
 *  See Actor3DNode class.
 */
class Actor3D : public Basic3D
{
protected:

	/// Default constructor.
	Actor3D();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Actor3D(Render3D* render_);

	/// Destructor.
	~Actor3D();

public:

	/// Creates new Actor3D.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Actor3D.
	 */
	static ObjRef<Actor3D> New()
	{
		return ObjRef<Actor3D>( new Actor3D );
	}

	/// Creates new Actor3D.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Actor3D.
	 */
	static ObjRef<Actor3D> New( Render3D* render_ )
	{
		return ObjRef<Actor3D>( new Actor3D(render_) );
	}

	/// Sends all Actor3D nodes to draw queue.
	void Draw();

	/// Updates Actor3D and all nodes result transform matrix.
	/**
	 * Need to call after Actor3D matrix transform update. 
	 */	
	void UpdateTransform();

	/// Returns Actor3D result transform matrix.
	/**
	 * @return Actor3D result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Returns Actor3D class id.
	/**
	 * @return Actor3D class id.
	 */
	Int GetClassID();
	
	/// Builds all nodes from specified Actor3DAnimation object.
	/**
	 * Need to call once time at beginning of creation of Actor3D object.
	 * Any new calls of Create() will clear nodes list and build it again.
	 * One Actor3D object should use to play and show only one specified 
	 * 3d object animation like character.
	 * @param a3danim pointer to Actor3DAnimation class object.
	 */
	void Create(ObjRef<Actor3DAnimation> a3danim);

	/// Attaches specified node from Actor3DAnimation to the common model.
	/**
	 * @param a3danim - pointer to Actor3DAnimation class object.
	 * @param node_name - name of node to attach.
	 * @return Returns True, if node was found and attached, else - False.
	 */ 
	Bool Attach(ObjRef<Actor3DAnimation> a3danim, const Char* node_name);

	/// Attaches specified Actor3DAnimationNode node.
	/**
	 * @param a3danim_node_ - Actor3DAnimationNode class object.
	 * @return Returns True, if node was attached, else - False.
	 */ 
	Bool Attach(ObjRef<Actor3DAnimationNode> a3danim_node_);

	/// Detaches specified node from model.
	/**
	 * @param node_name - name of node to detach.
	 * @return Returns True if successful, else - False.
	 */
	Bool Detach(const Char* node_name);

	/// Sets specified Actor3DAnimation object to play and animation show time.
	/**
	 * Should use only with Actor3DAnimation objects relative to one 
	 * character that have been specified and used in Create().	In other 
	 * words You can set one Actor3D object to play and show only one type 
	 * character for any animations like go, jump, die etc. 
	 * Don't use one Actor3D object to play different characters as all 
	 * Actor3DAnimation object should have identical nodes for specified character.
	 * @param a3danim_ - pointer to Actor3DAnimation class object.
	 * @param time_ - define start animation time.
	 * @param loop_play_  - if zero, animation will be stop in the end 
	 *		  of playing on last frame else continue playing from first frame.
	 */
	void Set(ObjRef<Actor3DAnimation> a3danim_,Int time_,Int loop_play_=0);

	/// Continues play animation with specified time step.
	/**
	 * Call this function per one AI run.
	 * @param time_step define play time.
	 */
	void Play( Int time_step = 160 );

	/// Returns current animation full time length.
	/**
	 * @return Returns current animation full time length.
	 */
	Int GetTimeLength();

	/// Returns current animation time.
	/**
	 * @return Returns current animation time.
	 */
	inline Int GetTime() { return time; }

	/// Returns current animation set.
	/**
	 * @return Returns current animation set.
	 */
	inline ObjRef<Actor3DAnimation> GetActor3DAnimation() { return a3danim; }

	/// Sets Actor3D result transform matrix.
	inline void SetResultTransform(const Matrix4fx& rm) { result_transform = rm; }

	/// Returns the play directions state. 
	/**
	 * @return Returns 1, if play direction is "forward", 
	 *         returns 0, if play direction is "stop",
	 *		   returns -1, if play direction is "backward".
	 */
	inline Int GetPlayDirection() { return play_direction; }

	/// Transformation matrix of all model.
	Matrix4fx transform;

	/// List of model's nodes.
	vector< ObjRef<Basic3D> > nodes;

protected:

	/// Current animation time.
	Int time;
	
	/// Result transformation matrix.
	Matrix4fx result_transform;
	
	/// Animation increment factor.
	Fixed li;

	/// Pointer to animation.
	ObjRef<Actor3DAnimation> a3danim;

	/// If animation loop play.
	Int loop_play;

	/// Play direction.
	/**
	 * This variable updates by calling Play() function. 
	 * If parameter (time_step) of this function > 0, than play_direction is "forward" (value = 1). 
	 * If parameter (time_step) of this function == 0, than play_direction is "stop" (value = 0).
	 * If parameter (time_step) of this function < 0, than play_direction is "backward" (value = -1). 
	 */
	Int play_direction;

};



/// Actor3DNode represents 3d actor node.
/**
 * This class used to represent one part of 3d actor character like head, 
 * trunk, hand, leg and etc.
 * Also nodes can be used for helper objects to represent gadgets, weapons.
 */
class Actor3DNode : public Basic3D
{
protected:

	/// Default constructor.
	Actor3DNode();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Actor3DNode(Render3D* render_);

	/// Destructor.
	~Actor3DNode();

public:

	/// Creates new Actor3DNode.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Actor3DNode.
	 */
	static ObjRef<Actor3DNode> New()
	{
		return ObjRef<Actor3DNode>( new Actor3DNode );
	}

	/// Create new Actor3DNode.
	/**
	 *	Call this function instead constructor calling.
	 *	@param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Actor3DNode.
	 */
	static ObjRef<Actor3DNode> New( Render3D* render_ )
	{
		return ObjRef<Actor3DNode>( new Actor3DNode(render_) );
	}

	/// Sends node to draw queue.
	void Draw();

	/// Updates node result transform matrix.
	/**
	 * Need to call after node matrix transform update. 
	 */	
	void UpdateTransform();

	/// Returns result transform matrix.
	/**
	 *  @return Returns result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Returns Actor3DNode class id.
	/**
	 * @return Returns Actor3DNode class id.
	 */
	Int GetClassID();

	/// Returns node bounding sphere center in model coordinate.
	/**
	 * @return Returns node bounding sphere center in model coordinate.
	 */
	Vector3fx GetCenter() { return center; }

	/// Returns node bounding sphere radius.
	/**
	 * @return Returns node bounding sphere radius.
	 */
	Fixed GetRadius() { return radius; }

	/// Transformation matrix of node.
	Matrix4fx transform;

	/// Material.
	Material material;

	/// Link object.
	ObjRef<Basic3D> link;

	friend class Actor3D;

protected:

	/// Result transform matrix.
	Matrix4fx result_transform;

	// VBs for animation morphing.
	ObjRef<VertexBuffer> vb_base;
	ObjRef<VertexBuffer> vb_0;
	ObjRef<VertexBuffer> vb_1;	

	// Parameters for animation morphing.
	Fixed li;
	Vector3fx center;
	Fixed radius;

private:

	// VBs for LOD drawing
	ObjRef<VertexBuffer> draw_vb_base;
	ObjRef<VertexBuffer> draw_vb_0;
	ObjRef<VertexBuffer> draw_vb_1;
	
};



/// Actor3DAnimationNode represents 3d actor animation node store.
/**
 *	This class store one 3d actor animation node.
 */
class Actor3DAnimationNode : public Object
{
protected:
	
	/// Default constructor.
	Actor3DAnimationNode();

	/// Destructor.
	~Actor3DAnimationNode();

public:

	/// Creates new Actor3DAnimationNode.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Actor3DAnimationNode.
	 */
	static ObjRef<Actor3DAnimationNode> New()
	{
		return ObjRef<Actor3DAnimationNode>( new Actor3DAnimationNode );
	}
	
	/// Returns name for this animation node.
	/**
	 * @return Returns name for this animation node.
	 */
	const string & GetName() { return name; }

	/// Material.
	Material material;

	friend class Actor3D;
	friend class MDMLoad;
	friend class Render3D;

protected:

	/// Node ID.
	Int node_id;

	/// Name.
	string name;

	/// List of transformation matrices.
	vector<Matrix4fx> transform;

	/// List of VertixBuffers of node.
	vector< ObjRef<VertexBuffer> > vb;

};


/// Actor3DAnimation represents 3d actor animation store.
/**
 *   This class store one 3d actor character animation.
 */
class Actor3DAnimation : public Object
{
protected:

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to render.
	 */
	Actor3DAnimation(Render3D* render_);

	/// Destructor.
	~Actor3DAnimation();

public:

	/// Creates new Actor3DAnimation.
	/**
	 * Call this function instead constructor calling.
	 * @param render_ - pointer to the Render3D class object.
	 * @return Returns object reference to new Actor3DAnimation.
	 */
	static ObjRef<Actor3DAnimation> New( Render3D* render_ )
	{
		return ObjRef<Actor3DAnimation>( new Actor3DAnimation(render_) );
	}

	/// Returns animation full time length.
	/**
	 * @return Returns animation full time length.
	 */
	inline Int GetTimeLength() { return key_frames[key_frames.size()-1].time + key_frames[key_frames.size()-1].duration; }

	/// Returns ASCII name for this animation.
	/**
	 * @return Returns ASCII name for this animation.
	 */
	inline const string & GetName() { return name; }

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }

	friend class Actor3D;
	friend class MDMLoad;
	friend class Render3D;

protected:
	
	/// Name.
	string name;

	/// List of key frames.
	vector<KeyFrame> key_frames;

	/// List of animation nodes.
	vector< ObjRef<Actor3DAnimationNode> > nodes;

	/// Pointer to the render.
	Render3D* render;

};

} //namespace mdragon

#endif // __MD_ACTOR3D_H__
