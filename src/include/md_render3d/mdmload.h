/** \file
 *	MDM model loader class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MDMLOAD_H__
#define __MD_MDMLOAD_H__

namespace mdragon
{

class TNode;
class TGround;

/// Loader of Mobile Dragon Model (MDM) file class.
class MDMLoad
{
public:

	/// Default constructor.
	MDMLoad();

	/// Destructor.
	~MDMLoad();

	/// Initializes loader.
	/**
	 * @param render - pointer to the Render class object.
	 * @param file_name_ - name of MDM file.
	 * @return Returns True, if initializing was successful, else - False. 
	 */
	Bool Init(Render3D* render, const Char* file_name_);

	/// Initializes loader.
	/**
	 * @param render - pointer to the Render class object.
	 * @param file_name_ - name of MDM file.
	 * @param mdm_ - Resource class object.
	 * @return Returns True, if initializing was successful, else - False. 
	 */
	Bool Init(Render3D* render, const Char* file_name_, Resource& mdm_);

	/// Loads static scene or simple animation scene from MDM file. 
	/**
	 * @param render - pointer to the Render class object.
	 * @param o3dlist - list of Basic3D objects to add loaded objects.
	 * @return Returns True, if loading was successful, else - False. 
	 */
	Bool Load(Render3D* render, vector< ObjRef<Basic3D> >& o3dlist);

	/// Loads tweening animation scene from MDM file. 
	/**
	 * @param render - pointer to the Render class object.
	 * @param a3danim - pointer to the Actor3DAnimation class object.
	 * @return Returns True, if loading was successful, else - False. 
	 */
	Bool Load(Render3D* render, ObjRef<Actor3DAnimation> a3danim);

	/// Loads joint animation scene from MDM file. 
	/**
	 * @param render - pointer to the Render class object.
	 * @param j3danim - pointer to the Joint3DAnimation class object.
	 * @return Returns True, if loading was successful, else - False. 
	 */
	Bool Load(Render3D* render, ObjRef<Joint3DAnimation> j3danim);

	/// Loads joint animation scene from MDM file. 
	/**
	 * @param render - pointer to the Render class object.
	 * @param j3dcoll - list of Joint3DNode objects.
	 * @return Returns True, if loading was successful, else - False. 
	 */
	Bool Load(Render3D* render, vector< ObjRef<Joint3DNode> > &j3dcoll);

	/// Checks if file has Static scene format.
	/**
	 * @return Returns True, if file has Static scene format, else - False.
	 */
	Bool IsStatic() { return is_static;	}
	
	/// Checks if file has Simple animation scene format.
	/**
	 * @return Returns True, if file has Simple animation scene format, else - False.
	 */
	Bool IsSimpleAnim() { return is_robot; }
	
	/// Checks if file has Tweening animation scene format.
	/**
	 * @return Returns True, if file has Tweening animation scene format, else - False.
	 */
	Bool IsTweeningAnim() { return is_actor; }

	/// Checks if file has Compact format.
	/**
	 * @return Returns True, if file has Compact format, else - False.
	 */
	Bool IsCompact() { return is_compact; }

	/// Checks if file has Joint animation scene format.
	/**
	 * @return Returns True, if file has Joint animation scene format, else - False.
	 */
	Bool IsJointAnimation() { return is_robo_animation; }

	/// Returns name of Loader. Name is equal of MDM file name.
	/**
	 * @return Returns name of Loader.
	 */
	const string & GetName() { return mdm_name; }

	/// List of Room objects. 
	/** 
	 * If scene is static and has portal system, this list will contain 
	 * all Room objects from this scene.
	 */
	vector< ObjRef<Room> > rooms;
	
	/// List of Portal objects. 
	/** 
	 * If scene is static and has portal system, this list will contain
	 * all Portal objects from this scene.
	 */
	vector< ObjRef<Portal> > portals;

	/// List of objects, that not linked to the rooms and portals. 
	/** 
	 * If scene is static and has portal system, this list will contain all
	 * objects which are not linked to the Room and Portal objects.
	 */
	vector< ObjRef<Basic3D> > out_of_portals;

	/// List of Dummy Objects.
	vector< ObjRef<Basic3D> > dummies;

private:
	
	

	Render3D* render;

	Bool StaticModelLoadGeomNode();
	Bool StaticModelLoadLightNode();
	Bool DummyNodeLoad();
	Bool AnimModelLoadGeomNode();
	Bool AnimModelLoadLightNode();
	Bool AnimActorModelLoadGeomNode();
	Bool RoboAnimationLoad();
	Bool RoboCollectionLoad();

	Bool StaticModelLoadRoom();
	Bool StaticModelLoadPortal();
	Bool StaticModelLoadGround();

	Bool SetRoomPortalAssociation(vector< ObjRef<Room> > &rooms_, vector< ObjRef<Portal> > &portals_, vector<TGround *> &grounds_);

	Int FindNodePointer(DWord nodeID);

	Bool LoadContent();

	// Reset all loader date to load new scene.
	void ResetLoader();
	
	string mdm_name;

	Resource mdm;

	Bool is_static;
	Bool is_robot;
	Bool is_actor;
	Bool is_compact;
	Bool is_robo_animation;
	Bool is_robo_collection;

	vector<DWord> content_node_id;
	vector<Int> content_node_pointer;

	vector<TNode*> nodes;

	vector<TGround *> grounds;

	Int frame_count;
	Int* time;
	Int* duration;

};

} //namespace mdragon

#endif // __MD_MDMLOAD_H__