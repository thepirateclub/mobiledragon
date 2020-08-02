///////////////////////////////////////////////////////////////////////////
//   # Mobile Dragon Demo Project #
//   # 2d Test #
//
//	 This demo shows:
//	 How to load sprite's and TileMaps from GameData
//	 How to use features of render2D such a scaling
//	 How to work with parameters of SpriteTransform Such a x, y position
//	 and Rotating
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
	/**
	* Do here deleting of all created game data.
	*/	
	delete st_table;
	delete cd_table;
}

GameProject::GameProject(System* system_)
{
	// Remember pointer to System object.
	system = system_;
	
	// Create instance of Render2D class.
	system->render2d = render = new Render2D;

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
	animation_type = 0;

	// Get display width and height.
	Fixed w = render->GetScreenWidth();
	Fixed h = render->GetScreenHeight();
	
	// Set render viewport to whole display.
	render->SetViewport(0,0,w,h);

	// Create game font.
	font.Create(render,"arial_black");

	// Create vectors for store SpriteTransform and CustomData
	st_table = new SVector<SpriteTransform>;
	cd_table = new SVector<CustomData>;

	// Load tile maps GameData
	tile_map_gd.Init(render,"set1_l");       
	tile_map_gd.EnterNode();
	tile_map_gd.GoToNextByNameNode("palette");
	tile_map_gd.ExportNode( &tile_map_palette, st_table, cd_table, tokens.begin() );
	tile_map_gd.GoToTopNode();
	tile_map_gd.GoToNextByNameNode("level0");
	tile_map_gd.EnterNode();

	// Load "floor" tile map
	tile_map_gd.GoToNextByNameNode("floor");
	tile_map_gd.ExportNode( &floor );
	floor.SetPalette( &tile_map_palette );
	floor.SetCellSize(24,24);

	// Load "objects" tile map
	tile_map_gd.GoToNextByNameNode("objects");
	tile_map_gd.ExportNode( &objects );
	objects.SetPalette( &tile_map_palette );
	objects.SetCellSize(24,24);

	// Load animation game data
	animation_gd.Init(render,"player01");
	animation_gd.EnterNode();
	animation_gd.GoToNextByNameNode("animation");
	// Export data to animation
	ani.ExportNode( &animation_gd, st_table, cd_table, tokens.begin() );
	
	// Set actor to SpriteTransform[] of animation "walk-face"
	actor.Set(ani.Find("walk-face"), True);

	// Translate help SpriteTransform to point(width screen, height screen);
	help_st.Translate(w/2,h/2);

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

	// Set new SpriteTransform form animation if delay end 
	actor.Play();

	// Rotate help sprite transform clockwise 
	if (system->input.KeyPressed(KEY_LEFT))
		help_st.Rotate(30);
	else
	// Rotate help sprite transform counterclockwise
	if (system->input.KeyPressed(KEY_RIGHT))
		help_st.Rotate(-30);
	// Update help sprite, it needed after all SpriteTransform changhes
	help_st.UpDate();

	/* Changhe animation in actor*/
	if (system->input.KeyPressed(KEY_B))
	{
		if (++animation_type == 4)
			animation_type = 0;
		if (animation_type == 0)
			actor.Set(ani.Find("walk-face"), True);
		else
		if (animation_type == 1)
			actor.Set(ani.Find("walk-left"), True);
		else
		if (animation_type == 2)
			actor.Set(ani.Find("walk-back"), True);
		else
		if (animation_type == 3)
			actor.Set(ani.Find("walk-right"), True);
	}

	// Rescale window
	if (system->input.KeyDown( KEY_UP ))
	{
		Fixed x_scale,y_scale;
		render->GetScale(&x_scale,&y_scale);
		x_scale+=F_ONE/100;
		y_scale+=F_ONE/100;
		render->SetScale(x_scale,y_scale);
	}
	else if (system->input.KeyDown( KEY_DOWN ))
	{
		Fixed x_scale,y_scale;
		render->GetScale(&x_scale,&y_scale);
		x_scale-=F_ONE/100;
		y_scale-=F_ONE/100;
		render->SetScale(x_scale,y_scale);
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

//////////////////////////////////////////////////////////////////////////

	/* Drawing TileMap's*/
	DrawTileMap(&floor);
	DrawTileMap(&objects);
	
	// sort draw queue by z order and draw it.
	render->Flush();
	
	// draw SpriteTransform from actor with help SpriteTransform parameters
	render->Draw(&help_st, actor.GetFrame());


//////////////////////////////////////////////////////////////////////////

	/**
	 * Display game text.
	 */
	system->user_string0 = "FPS: ";
	system->user_string0 << ( game_fps / 100 ) << "." << ( game_fps % 100 );
	font.Draw( system->user_string0.data(), 10, 10 );
	
	system->user_string0.clear();
	system->user_string0 = "Render2D Test"; 
	font.Draw( system->user_string0.data(), 10, 20 );
	
	system->user_string0.clear();
	system->user_string0 = "KEY_UP-Zoom +"; 
	font.Draw( system->user_string0.data(), 10, 30 );
	
	system->user_string0.clear();
	system->user_string0 = "KEY_DOWN-Zoom -"; 
	font.Draw( system->user_string0.data(), 10, 40 );
	
	system->user_string0.clear();
	system->user_string0 = "KEY_LEFT-rotate +"; 
	font.Draw( system->user_string0.data(), 10, 50 );
	
	system->user_string0.clear();
	system->user_string0 = "KEY_RIGHT-rotate -"; 
	font.Draw( system->user_string0.data(), 10, 60 );

	system->user_string0.clear();
	system->user_string0 = "KEY_B-changhe animation"; 
	font.Draw( system->user_string0.data(), 10, 70 );
	
	system->user_string0.clear();
	system->user_string0 = "KEY_A-exit"; 
	font.Draw( system->user_string0.data(), 10, 80 );

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

void GameProject::DrawTileMap(TileMap* tile_map)
{
	SpriteTransform cell;
	Short x_s, y_s;

	// Get dimensions of one square in tile map
	tile_map->GetSize( &x_s, &y_s );

	for( Int y = 0; y < tile_map->GetYDiv(); ++y )
	{
		for( Int x = 0; x < tile_map->GetXDiv(); ++x )
		{
			SpriteTransform* tile = tile_map->GetTile(x,y);

			if( tile )
			{
				cell.Translate( x * x_s, y * y_s );
				cell.SetZOrder( tile_map->GetZOrder() + y * 10 + x );
				render->Draw( &cell, tile );
			}
		}
	}

}

