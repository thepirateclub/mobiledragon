///////////////////////////////////////////////////////////////////////////
//   # Mobile Dragon Demo Project #
//   # Sound Test #
//
//	 This demo shows:
//	 How to load and play sound data.
//	 How to control the plaing volume.
//
///////////////////////////////////////////////////////////////////////////

#include "main.h"


MDGame* MDGameCreate( System * system )
{
	// Call constructor of GameProject here.
	return new GameProject(system);
}

void MDGameSetPreferences( MDGamePreferences & p)
{
	// Fill all data field of MDGamePreferences structure here.
	p.name = MD_GAME_NAME;						// Project name.
	p.title = MD_GAME_TITLE;					// Project title.
	p.log_level = MD_LOG_LEVEL;					// Log level.
	p.log_name = MD_LOG_NAME;					// Log name.
	p.runs_per_second = MD_AI_RUNS_PER_SECOND;	// Runs per second
	p.pack_dir_name = MD_PACKDIR_NAME;			// Name of resource file.
	p.system_pool_size = MD_SYSTEM_POOL_SIZE;	// System pool size.
	p.symbian_uid = MD_SYMBIAN_UID;				// IUD for Symbian OS.
	p.palm_creator_id = MD_PALM_CREATOR_ID;		// Creator ID for Palm OS.
}


GameProject::~GameProject()
{
}

GameProject::GameProject(System* system_)
{
	/**
	* Do here deleting of all created game data.
	*/
	system = system_;
	system->render2d = render = new Render2D;
	
	// Take pointer of SoundSystrem
	sound_system = &system->sound_system;

}

Bool GameProject::Init()
{
	/**
	 * Do initialization of game here.
	 */

	// Zero counters.
	game_fps = 0;
	ai_ticks = 0;
	fps_frame_count = 0;

	// Get display width and height.
	Fixed w = render->GetScreenWidth();
	Fixed h = render->GetScreenHeight();
	
	// Set render viewport to whole display.
	render->SetViewport(0,0,w,h);

	// Create game font.
	font.Create(render,"arial_black");

	
//////////////////////////////////////////////////////////////////////////

	// SoundSystem object initialization
	#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)
		system->sound_system.Init(16000, 16, False, 2, 8, system->GetPackDir());
	#endif

	#if defined(MD_OS_WINCE) || defined(MD_OS_WIN32)
		system->sound_system.Init(22050, 16, False, 2, 8, system->GetPackDir());
	#endif

	#if defined(MD_OS_PALM)
		system->sound_system.Init(22050, 16, False, 2, 4, system->GetPackDir());
	#endif

	// Load sound and music
	sound1 = sound_system->LoadSound("sound1.wav");
	sound2 = sound_system->LoadSound("sound2.wav");
	music1 = sound_system->LoadMusic("music1.mod");

	// Set loop mode for playing music1
	music1->SetLoop(True);

	// Set music volume
	volume_parametr = 40;
	sound_system->SetGlobalMusicVolume(volume_parametr);

//////////////////////////////////////////////////////////////////////////

	return True;
}


Bool GameProject::Update()
{
	/**
	 * Get current ticks.
	 */
	DWord ticks = system->GetTicks();

	/**
	 * Zero AI run count per this LoopGame() call.
	 */
	Int is_ai_run = 0;

	
	/**
	 * Count this AI run.
	 */
	is_ai_run++;

	/**
	 * We need to have exit from our game. This do it if gamer press key 0 or clik in first 10 top lines of display by stylus.
	 */
	Short pen_x,pen_y;
	system->input.PenState( &pen_x, &pen_y );
	if( ( system->input.PenClicked() && pen_y < 10 ) || system->input.KeyDown( KEY_A ))
	{
		system->Exit();
		return False;
	}

//////////////////////////////////////////////////////////////////////////

	// Play/Pause music1
	if (system->input.KeyPressed(KEY_B))
	{
		if (!sound_system->IsPlaying(music1))
			sound_system->Play(music1);
		else
			sound_system->Pause(music1);
	}

	// PLaying sound1, sound2
	if (system->input.KeyPressed(KEY_LEFT))
		sound_system->Play(sound1);
	if (system->input.KeyPressed(KEY_RIGHT))
		sound_system->Play(sound2);

	//Changhe music1 volume
	if (system->input.KeyDown(KEY_UP) && volume_parametr < 64)
	{
		volume_parametr ++;
		sound_system->SetGlobalMusicVolume(volume_parametr);
	}
	if (system->input.KeyDown(KEY_DOWN) && volume_parametr > 0 )
	{
		volume_parametr --;
		sound_system->SetGlobalMusicVolume(volume_parametr);
	}
	

//////////////////////////////////////////////////////////////////////////

	/**
	 * Update game frame counters and FPS. We use 30 frames to calculate FPS.
	 */

	fps_frame_count++;

	if( fps_frame_count == 30 )
	{
		DWord ticks = system->GetTicks();

		game_fps = ( 30 * 100 * 1000 ) / ( ticks - fps_start_ticks );

		fps_start_ticks = ticks;
		fps_frame_count = 0;
	}

///////////////////////////////////////////////////////////////////////////

	if( is_ai_run )
	{
		/**
		 * If we have one or more AI runs than we need to update visible game scene and return here True to say system call DrawGame() else False to do not any draw.
		 */
		return True;
	}

	/**
	 * At this time LoopGame() do not any AI runs and we don't want do any draw. 
	 */
	return False;
}

void GameProject::Draw()
{
	/**
	 * First we need to clear viewport.
	 */
	render->SetClearColor(Color(0,0,128,0));
	render->Clear(Render2D_Clear_Color);

	/**
	 * Display game text.
	 */
	system->user_string0 = "FPS: ";
	system->user_string0 << ( game_fps / 100 ) << "." << ( game_fps % 100 );
	font.Draw( system->user_string0.data(), 10, 10 );
	
	system->user_string0.clear();
	system->user_string0 = "Sound Test"; 
	font.Draw( system->user_string0.data(), 10, 20 );
	
	system->user_string0.clear();
	system->user_string0 = "UP-Volume music +"; 
	font.Draw( system->user_string0.data(), 10, 30 );
	
	system->user_string0.clear();
	system->user_string0 = "DOWN-Volume music -"; 
	font.Draw( system->user_string0.data(), 10, 40 );
	
	system->user_string0.clear();
	system->user_string0 = "LEFT-Play sound1"; 
	font.Draw( system->user_string0.data(), 10, 50 );
	
	system->user_string0.clear();
	system->user_string0 = "RIGHT-Play sound2"; 
	font.Draw( system->user_string0.data(), 10, 60 );

	system->user_string0.clear();
	system->user_string0 = "B- Play/Pause music"; 
	font.Draw( system->user_string0.data(), 10, 70 );
	
	system->user_string0.clear();
	system->user_string0 = "A-exit"; 
	font.Draw( system->user_string0.data(), 10, 80 );

	system->user_string0.clear();
	system->user_string0 = "Music volume: "; 
	system->user_string0 << volume_parametr;

	font.Draw( system->user_string0.data(), 10, 90 );

	/**
	 * As font only send text to draw queue we need to process draw queue again.
	 */
	render->Flush();

//////////////////////////////////////////////////////////////////////////

	/**
	 * Only now copy backbuffer to video memory on display.
	 */
	render->Show();
}
