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

//////////////////////////////////////////////////////////////////////////////////////////
// For TileMap drawing
//////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * DrawTileMap() drawing TileMap
	 */
	void DrawTileMap(TileMap * tile_map);

	// TileMaps GameData object ;
	GameData tile_map_gd;
	// Tile map pallete. Contain SpriteTransform pointer for drawing "floor"
	// and "object" tilemap
	vector<SpriteTransform*> tile_map_palette;

	// Tilemaps
	TileMap floor;
	TileMap objects;

//////////////////////////////////////////////////////////////////////////////////////////
// For Animation drawing
//////////////////////////////////////////////////////////////////////////////////////////

	// Animations GameData
	GameData animation_gd;
	// Animation object
	Animation ani;
	// Actor2d object
	Actor2D actor;
	// Help SpriteTransform for position and rotation of animation 
	// SpriteTransform without animation SpriteTransform changhes
	// see Render2d->Draw(SpiteTransform*,SpiteTransform*);
	SpriteTransform help_st;
	// For select animation_type (up,right,down,left)
	Int animation_type;

	// Custom Data attributes
	vector<Char*> tokens;
	SVector<CustomData>* cd_table;

	// Contain all game SpriteTransforms
	SVector<SpriteTransform>* st_table;

	// Font
	Font2D font;

};
