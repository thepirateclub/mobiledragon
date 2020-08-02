#include "../mdconfig.h"
#include "mdragon.h"
#include "policies.h"
#include "particle_drawer.h"


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

	/**
	 * Switch particles system and init particle drawer by it.
	 */
	void ParticleDrawerInit();

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

	// Scene objects list.
	vector< ObjRef<Basic3D> > room;

	// Particles system with Smoke policy.
	PSmoke smoke;

	// Particles system with Sparks policy.
	PSparks sparks;

	// Particles system with twister policy.
	PTwister twister;

	// Particles system with Explosion policy.
	PExplosion explosion;

	// Particles drawer. It draws particles as the sprites.
	ParticleDrawer particle_drawer;

	// Current particles system:
	// 0 - smoke; 1 - sparks; 2 - twister; 3 - explosion.
	Int curr_ps;

	// Time increment in one tick. By default = 1/30.
	Fixed delta_t;

	// Camera
	Camera camera;

	// View matrix for objects.
	Matrix4fx view_mx;

	// Light.
	ObjRef<Light> omni;

	// Help message visibility flag.
	Bool help_visible;

};


