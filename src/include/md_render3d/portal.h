/** \file
 *	Portal system. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_PORTAL_H__
#define __MD_PORTAL_H__

namespace mdragon 
{


/// Maximal room height.
#define MAX_ROOM_HEIGHT  Fixed(300);


//////////////////////////////////////////////////////////////////////////

class Room;


/// Portal class.
/**
 * Objects of this class are used in room-portal system to determine
 * visibility of rooms. These objects can not be drew, they are used 
 * only for computing, but portals may contain list of 3D objects, 
 * which belong to the two rooms simultaneously and can be drew. 
 * Generally portals are placed into passageway between rooms. 
 */
class Portal : public Object
{
protected:

	/// Constructor with given render pointer value and name.
	/**
	 *  @param render_ - pointer to Render3D class object.
	 *  @param name_ - name of portal.
	 */
	Portal(Render3D* render_, const Char* name_);

	/// Destructor.
	~Portal();

public:

	/// Creates new Portal.
	/**
	 *	Call this function instead constructor calling.
	 *  @param render_ - pointer to Render3D class object.
	 *  @param name_ - name of portal.
	 *  @return Returns object reference to new Portal.
	 */
	static ObjRef<Portal> New( Render3D* render_, const Char* name_ )
	{
		return ObjRef<Portal>( new Portal(render_, name_) );
	}
	
	/// Projects portal for clipping detection.
	void Project();

	/// Clips portal by another portal.
	/**
	 *  @param portal - portal, by which calculate clipping.
	 */
	void Clip(ObjRef<Portal> portal);

	/// Checks if portal is visible.
	/**
	 *  @return Returns True, if portal is visible, else - False.
	 */
	Bool IsVisible() { return is_visible; }
	
	/// Sends portal's object list to the draw queue. 
	void Draw();

	/// Sets portal's name.
	/**
	 *  @param name_ - portal's name.
	 */
	void SetName(const Char* name_) { name = name_; }
	
	/// Returns name of portal.
	/**
	 *  @return Returns name of portal.
	 */
	const string & GetName() { return name; }

	/// Sets node ID for the portal.
	/**
	 *  @param node_id_ - portal's node ID.
	 */
	void SetNodeID(Int node_id_) { node_id = node_id_; }

	/// Returns portal's node ID.
	/**
	 *  @return Returns portal's node ID.
	 */
	Int GetNodeID() { return node_id; }

	/// Sets first (À) linked room.
	/**
	 *  @param room_a_ - first (A) linked room.
	 */
	void SetRoomA(ObjRef<Room> room_a_) { room_a = room_a_; }
	
	/// Sets second (B) linked room.
	/**
	 *  @param room_b_ - second (B) linked room.
	 */
	void SetRoomB(ObjRef<Room> room_b_) { room_b = room_b_; }

	/// Returns first (À) linked room.
	/**
	 *  @return Returns first (À) linked room.
	 */
	ObjRef<Room> GetRoomA() { return room_a; }
	
	/// Returns second (B) linked room.
	/**
	 *  @return Returns second (B) linked room.
	 */
	ObjRef<Room> GetRoomB() { return room_b; }

	/// Sets portal's border.
	/**
	 * Portal's border consist of four vertexes.
	 * @param border_ - vertex coordinates array. This array have to 
	 *                  include 12 elements (4 vert. * 3 coord.)
	 */
	void SetBorder(const Fixed * border_);

	/// Returns Min value of portal's BoundingBox.
	/**
	 * @return Returns Min value of portal's BoundingBox.
	 */
	inline Vector3fx GetMin(void) { return min; }

	/// Returns Max value of portal's BoundingBox.
	/**
	 * @return Returns Max value of portal's BoundingBox.
	 */
	inline Vector3fx GetMax(void) { return max; }

	/// Sets checking flag for portal.
	/**
	 *  This flag used by recurring search.
	 *  @param checked_ - is portal checked.
	 */
	void SetChecked(const Bool & checked_) { checked = checked_; }

	/// Returns checking flag for portal.
	/**
	 *  This flag used by recurring search.
	 *	@return Returns True, if portal is checked, else - False.
	 */
	Bool IsChecked() { return checked; };

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }

	/// List of linked objects.
	vector< ObjRef<Basic3D> > b3d_list;
	
private:

	/// Portal's name.
	string name;

	/// Portals's node ID.
	Int node_id;

	/// Min portal' Bounding Box value.
	Vector3fx min;

	/// Max portal' Bounding Box value.
	Vector3fx max;

	/// Portal's border.
	Vector3fx border[4];

	/// Is portal visible.
	Bool is_visible;

	/// Is portal checked.
	Bool checked;	

	/// First (À) linked room.
	ObjRef<Room> room_a;

	/// Second (B) linked room.
	ObjRef<Room> room_b;

	/// Pointer to Render3D Class object.
	Render3D* render; 

	Int* xborder;
	Int* xborder_clip;

};

//////////////////////////////////////////////////////////////////////////

/// Room class.
/**
 * Objects of this class are used in room-portal system. 
 * These objects can not be drew, they are used only for computing, but room
 * contain list of 3D objects, which belong to this room and can be drew. 
 */
class Room : public Object
{
protected:
	
	///  Constructor with given render pointer value and room's name.
	/**
	 *	@param render_ - pointer to the Render3D class object.
	 *  @param name_ - rooms's name.
	 */
	Room(Render3D* render_, const Char* name_);

	/// Destructor.
	~Room();

public:

	/// Creates new Room.
	/**
	 *	Call this function instead constructor calling.
	 *  @param render_ - pointer to Render3D class object.
	 *  @param name_ - name of room.
	 *  @return Returns object reference to new Room.
	 */
	static ObjRef<Room> New( Render3D* render_, const Char* name_ )
	{
		return ObjRef<Room>( new Room(render_, name_) );
	}

	/// Sends objects, which are linked to this room to the draw queue.
	void Draw();

	/// Sets room's name.
	/**
	 *  @param name_ - room's name.
	 */
	void SetName(const Char* name_) { name = name_; }

	/// Returns name of room.
	/**
	 *  @return Returns name of room.
	 */
	const string & GetName() { return name; }

	/// Sets node ID for the room.
	/**
	 *  @param node_id_ - room's node ID.
	 */
	void SetNodeID(Int node_id_) { node_id = node_id_; }

	/// Returns room's node ID.
	/**
	 *  @return Returns room's node ID.
	 */
	Int GetNodeID() { return node_id; }

	/// Sets room's checked flag.
	/**
	 *  This flag is used by recurring search.
	 *  @param checked_ - is room checked.
	 */
	void SetChecked(const Bool & checked_) { checked = checked_; }
	
	/// Checks, if room is already checked.
	/**
	 *  This flag is used by recurring search.
	 *  @return Returns True, if room is already checked, else - False. 
	 */
	Bool IsChecked() { return checked; };

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }
	
	/// List of room's grounds.
	vector < ObjRef<VertexBuffer> > grounds;

	/// List of room's portals.
	vector < ObjRef<Portal> > portals;

	/// List of room's objects.
	vector < ObjRef<Basic3D> > b3d_list;

private:

	/// Pointer to the render.
	Render3D* render;

	/// Room's name.
	string name;
	
	/// Room's node ID.
	Int node_id;
	
	/// Is room checked.
	Bool checked;
};

///////////////////////////////////////////////////////////////////////////

/// Checks visibility of rooms from given room.
/** \relates Room
 *	All visible rooms will add to the list of visible rooms and will check their "checked" flag.
 *	@param room - first given room.
 *	@param clip_portal - clipping portal (for first call may be NULL)
 *	@param vis_rooms - list of visible rooms.
 */
void CheckNearRooms(ObjRef<Room> room, ObjRef<Portal> clip_portal, vector< ObjRef<Room> > &vis_rooms);

/// Draws all visible rooms in given list of rooms.
/** \relates Room
 *	Searching start from given start room.
 *	@param start_room - start room.
 *	@param rooms - list of rooms for searching.
 */
void DrawFromRoom(ObjRef<Room> start_room, vector< ObjRef<Room> >rooms);

/// Draws all visible rooms in given list of rooms.
/** \relates Room
 *	Searching start from rooms linked to the given start portal.
 *	@param start_room - start portal.
 *	@param rooms - list of rooms for searching.
 */
void DrawPortal(ObjRef<Portal> portal, vector< ObjRef<Room> >rooms);

/// Finds room in given list of rooms, that contains given point.
/** \relates Room
 *  @param pos - given point for searching.
 *	@param rooms - list of rooms for searching.
 *  @return Returns pointer to found room. If room is not found, return NULL.
 */
ObjRef<Room> FindStartRoom(Vector3fx pos, vector< ObjRef<Room> >& rooms);

/// Finds room from list of rooms linked to given start room, that contains given point.
/** \relates Room
 *  @param pos - given point for searching.
 *	@param room - given start room for searching.
 *  @return Returns pointer to found room. If room is not found, return NULL.
 */
ObjRef<Room> FindRoomAround(Vector3fx pos, ObjRef<Room> room);

/// Finds portal, that is in given radius from given point in given room.
/** \relates Room
 *	@param room - room for portal searching.
 *	@param pos - point (sphere center).
 *	@param radius - radius (sphere center).
 *	@return Returns pointer to found portal. If portal is not found, return NULL.
 */
ObjRef<Portal> FindCrossPortal(ObjRef<Room> room, const Vector3fx &pos, const Fixed &radius);


void SortAndBuildLightMap(Render3D *render, vector< ObjRef<Basic3D> >& b3d_list, const Char *file_name_prefix);

} //namespace mdragon

#endif // __MD_PORTAL_H__