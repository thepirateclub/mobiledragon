#include "../mdconfig.h"
#include "mdragon.h"

using namespace mdragon;

/*! \class GameProject
 *   \brief Game project class.
 *
 *   This class used to manage game project. Contains game init&finish and main game loop with game scene drawing.
 */

class GameProject : public MDGame
{
public:

	/**
	 * GameProject() GameProject class constructor.
	 * You need here create Render2D or Render3D class object and set pointer to it in system_->render2d or system_->render3d.
	 * Also store 'system_' pointer to System class object in 'system' data member of GameProject.
	 */
	GameProject(System* system_);

	/**
	 * ~GameProject() GameProject class destructor.
	 * Free all game data created in InitGame() here.
	 * Also please do not delete Render2D or Render3D class object created in GameProject() class constructor here. System class destructor do it for You automatically.
	 */
	~GameProject();

	/**
	 * Init() performs the complete initialization of most game data here. This function will be called by system on the game startup.
	 * Please only load game data and create game objects here without drawing and sound playing.
	 */
	Bool Init();

	/**
	 * Update() main game loop. Call all times repeatedly by system without any time constraint. 
	 * So You can always control how many game updates will be per second.
	 * @return Return True if need game scene drawing update else False.
	 */
	Bool Update();

	/**
	 * Draw() do game scene drawing. Only calls by system if last Draw() return True.
	 * Please do all drawing operations only here.
	 */
	void Draw();

	// System class object pointer.
	System* system;

	// 3d Render class object pointer.
	Render3D* render;

	// Game AI last ticks run.
	DWord ai_ticks;

	// Game FPS start ticks count.
	DWord fps_start_ticks;

	// Game FPS frame count.
	DWord fps_frame_count;

	// Game FPS count.
	Int game_fps;

	// Game 3d font Font class object used for example to show FPS.
	Font3D font;

	// List of scene objects.
	vector< ObjRef<Basic3D> > o3dlist;

	// List of rooms.
	vector< ObjRef<Room> > rooms;

	// List of portals.
	vector< ObjRef<Portal> > portals;

	// List of objects not linked to the rooms.
	vector< ObjRef<Basic3D> > out_of_portals;
	
	// Pointer to the current room.
	ObjRef<Room> current_room;

	// Pointer to the previous room.
	ObjRef<Room>  previous_room;

	// List of objects, which store animation in different LOD.
	ObjRef<Actor3DAnimation> actor_animation;
	//vector< ObjRef<Actor3DAnimation> > animations_list;

	// Object to play animation.
	ObjRef<Actor3D> actor;

	// Camera
	Camera camera;

	// View matrix for objects.
	Matrix4fx view_mx;

	// Light.
	ObjRef<Light> omni;

	// Help message visibility flag.
	Bool help_visible;

	///////////////////////////////////////////////////////////////////////
	// Variables below are used for moving actor model along the waypoints.
	///////////////////////////////////////////////////////////////////////

	/**
	 * Sort list of waypoints by name.
	 * In this demo used scene with simply DummyBox objects.
	 * @param dummies_ - list of waypoints (DummyBox objects).
	 */
	void CreatePositionList(vector< ObjRef<Basic3D> > &dummies_);

	/**
	 * Compare two waypoints by name.
	 * Used when we sort list of waypoints.
	 * @param first_ - first waypoint.
	 * @param second_ - second waypoint.
	 * @return Return True, if first waypoint is lower then second by name.
	 */
	static Bool ComparePositions(ObjRef<Basic3D> first_, ObjRef<Basic3D> second_);

	/**
	 * Update actor position. 
	 */
	 void UpdateActorPosition();
	

	// Vaypoints list. Actor moves from one waypoint to the another. 
	// When actor reach the last waypoint it'll follow the first waypoint again. 
	vector<Vector3fx> position_list;

	// Direction from last update.
	Vector3fx curr_dir;

	// Current waypoint index in waypoints list.
	Int curr_waypoint;

	// Actor moving speed.
	Fixed actor_speed;

};


