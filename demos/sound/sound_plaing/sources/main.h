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
	 * You need here create Render2D class object and set pointer to it in system_->render2d.
	 * Also store 'system_' pointer to System class object in 'system' data member of GameProject.
	 */
	GameProject(System* system_);

	/**
	 * ~GameProject() GameProject class destructor.
	 * Free all game data created in InitGame() here.
	 * Also please do not delete Render2D  class object created in GameProject() class constructor here. 
	 * System class destructor do it for You automatically.
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

	// Render2D class object pointer.
	Render2D* render;

	// Game AI last ticks run.
	DWord ai_ticks;
	
	// Game FPS start ticks count.
	DWord fps_start_ticks;

	//Game FPS frame count.
	DWord fps_frame_count;

    //Game FPS count.
	Int game_fps;

	// Font
	Font2D font;

/////////////////////////////////////////////////////////////////////////

	// SoundSystem class object pointe. 
	// Don't create and delete data by this pointer. 
	// Take it from system->sound_system
	SoundSystem * sound_system;

	// Music and Sound class pointers
	Sound * sound1;
	Sound * sound2;
	Music * music1;

	DWord volume_parametr;
	

};
