/** \file
 *	Joint 3d animation. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_JOINT3D_H__
#define __MD_JOINT3D_H__


namespace mdragon
{

class Joint3DNode;
class Joint3DAnimation;


/// Joint Model.
/**
 * It's possible to attach some nodes from different collections to this model.
 */
class Joint3D : public Basic3D
{
protected:

	/// Default Constructor.
	Joint3D();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Joint3D(Render3D* render_);

	/// Destructor.
	~Joint3D();

public:

	/// Creates new Joint3D.
	/**
	 *  Call this function instead constructor calling.
 	 *  @param render_ - pointer to the Render3D class object.
	 *  @return Returns object reference to new Joint3D.
	 */
	static ObjRef<Joint3D> New( Render3D* render_ )
	{
		return ObjRef<Joint3D>( new Joint3D(render_) );
	}

	/// Sends model to the draw queue.
	void Draw();

	/// Updates result transform matrices of Joint3D and all nodes.
	/**
	 * Need to call after Joint3D matrix transform update. 
	 */	
	void UpdateTransform();

	/// Returns Joint3D's result transform matrix.
	/**
	 * @return Returns Joint3D's result transform matrix.
	 */
	Matrix4fx GetResultTransform();

	/// Returns Joint3D class ID.
	/**
	 * @return Returns Joint3D class ID.
	 */
	Int GetClassID();
	
	/// Sets specified Joint3DAnimation object to play and animation show time.
	/**
	 * @param j3danim_ - pointer to Joint3DAnimation class object.
	 * @param time_ - define start animation time.
	 * @param loop_play_ - if zero animation will be stop in the end of playing on last frame else continue playing from first frame.
	 */
	void Set(ObjRef<Joint3DAnimation> j3danim_,Int time_, Int loop_play_=0);

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
	inline ObjRef<Joint3DAnimation> GetJoint3DAnimation() { return j3danim; }

	/// Sets Joint3D result transform matrix.
	/**
	 * @param rm - new result transform matrix.
	 */
	inline void SetResultTransform(const Matrix4fx& rm) { result_transform = rm; }

	/// Creates Joint3D model from specified Joint3DNode list.
	/**
	 * All nodes from this list will be attached to the model.
	 * Every time you call Create, current model will be cleared. 
 	 * You don't need to call RefreshLinks() function after calling this function.
	 * @param j3dcoll - list of Joint3DNode nodes.
	 */ 
	void Create(vector< ObjRef<Joint3DNode> > &j3dcoll);
	
	/// Attaches specified node from list of Joint3DNode nodes to the common model.
	/**
	 * @param j3dcoll - list of Joint3DNode nodes.
	 * @param node_name - name of node to attach.
	 * @return Returns True, if node was found and attached, else - False.
	 */ 
	Bool Attach(vector< ObjRef<Joint3DNode> > &j3dcoll, const Char* node_name);

	/// Attaches specified node from list of Joint3DNode nodes to the common model.
	/**
	 * @param j3dcoll_node_ - Joint3DNode node.
	 * @return Returns True, if node was attached, else - False.
	 */ 
	Bool Attach(ObjRef<Joint3DNode> j3dcoll_node_);
	
	/// Detaches specified node from model.
	/**
	 * @param node_name - name of node to detach.
	 * @return Returns True if successful, else - False.
	 */
	Bool Detach(const Char* node_name);

	/// Refresh links of model.
	/**
	 * You should call this function every time after 
	 * calling Attach() or Detach() functions.
	 */
	Bool RefreshLinks();

	/// Returns the play directions state.
	/**
	 * @return Returns 1, if play direction is "forward", 
	 *         returns 0, if play direction is "stop",
	 *		   returns -1, if play direction is "backward".
	 */
	inline Int GetPlayDirection() { return play_direction; }

	/// Transformation matrix of all model.
	Matrix4fx transform;
	
	/// List of model nodes.
	vector< ObjRef<Robot3D> > robos;

protected:

	/// Current animation time.
	Int time;
	
	/// Result transformation matrix.
	Matrix4fx result_transform;

	/// Animation increment factor.
	Fixed li;

	/// Pointer to animation.
	ObjRef<Joint3DAnimation> j3danim;

	/// List of collection nodes.
	vector< ObjRef<Joint3DNode> > nodes;

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


/// KeyFrame represents one key frame in animation.
struct KeyFrame
{
	/// Key Frame activation time.
	Int time;

	/// Key Frame duration.
	Int duration;
};


/// Node in Joint Joint3DAnimation.
/** 
 * It contains name of node and list of transformation matrices in all key frames of animation.
 */
class Joint3DAnimationNode : public Object
{
protected:

	/// Default constructor.
	Joint3DAnimationNode();

	/// Destructor.
	~Joint3DAnimationNode();

public:

	/// Creates new Joint3DAnimationNode.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Joint3DAnimationNode.
	 */
	static ObjRef<Joint3DAnimationNode> New()
	{
		return ObjRef<Joint3DAnimationNode>( new Joint3DAnimationNode );
	}

	/// Returns name for this animation node.
	/**
	 * @return Returns name for this animation node.
	 */
	const string & GetName() { return name; }

	friend class Joint3D;
	friend class MDMLoad;

protected:

	/// Node's name.
	string name;

	/// Node's ID.
	Int node_id;

	/// List of transformation matrices.
	vector<Matrix4fx> matrices;
};


/// Joint3DAnimation represents animation of joint model.
/** 
 * It contains list of Joint3DAnimationNode 
 */
class Joint3DAnimation : public Object
{
protected:

	/// Constrictor with given render pointer value.
	/**
	 * @param render_ - pointer to render.
	 */
	Joint3DAnimation(Render3D* render_);

	/// Destructor.
	~Joint3DAnimation();

public:

	/// Creates new Joint3DAnimation.
	/**
	 * Call this function instead constructor calling.
	 * @param render_ - pointer to the Render3D class object.
	 * @return Returns object reference to new Joint3DAnimation.
	 */
	static ObjRef<Joint3DAnimation> New( Render3D* render_ )
	{
		return ObjRef<Joint3DAnimation>( new Joint3DAnimation(render_) );
	}

	/// Returns animation full time length.
	/**
	 * @return Returns animation full time length.
	 */
	inline Int GetTimeLength() { return key_frames[key_frames.size()-1].time + key_frames[key_frames.size()-1].duration; }

	/// Returns name for this animation.
	/**
	 * @return Returns name for this animation.
	 */
	inline const string & GetName() { return name; }

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }

	friend class Joint3D;
	friend class MDMLoad;

protected:

	/// Animation's name (file name).
	string name;

	/// List of key frames.
	vector<KeyFrame> key_frames;

	/// List of animation nodes.
	vector< ObjRef<Joint3DAnimationNode> > nodes;

	/// Pointer to the render.
	Render3D* render;
};

/// Joint represents joint object in Joint3DAnimation.
/**
 * Object of this class used by set relative transformation of Robot3D nodes.
 */
class Joint
{
public:

	/// Default constructor.
	Joint();

	/// Destructor.
	~Joint();

	/// ID of linked node (stored in 3D Max).
	Int node_id;

	/// Relative Transformation matrix of linked node.
	Matrix4fx relative; 

};


/// Joint3DNode represents an 3d object (Object3D) with list of joints.
/**
 * These joints are used by linking another nodes to this.
 */
class Joint3DNode : public Object3D
{
protected:

	///  Default constructor.
	Joint3DNode();

	/// Constructor with given render pointer value.
	/**
	 * @param render_ - pointer to the Render3D class object.
	 */
	Joint3DNode(Render3D* render_);

	/// Destructor.
	~Joint3DNode();

public:

	/// Creates new Joint3DNode.
	/**
	 * Call this function instead constructor calling.
	 * @return Returns object reference to new Joint3DNode.
	 */
	static ObjRef<Joint3DNode> New()
	{
		return ObjRef<Joint3DNode>( new Joint3DNode );
	}

	/// Creates new Joint3DNode.
	/**
	 * Call this function instead constructor calling.
	 * @param render_ - pointer to the Render3D class object.
	 * @return Returns object reference to new Joint3DNode.
	 */
	static ObjRef<Joint3DNode> New(Render3D* render_)
	{
		return ObjRef<Joint3DNode>( new Joint3DNode(render_) );
	}

	/// Returns Object3D class id.
	/**
	 * @return Returns Object3D class id.
	 */
	Int GetClassID();

	/// List of joints.
	vector<Joint> joints;
};

} //namespace mdragon

#endif // __MD_JOINT3D_H__