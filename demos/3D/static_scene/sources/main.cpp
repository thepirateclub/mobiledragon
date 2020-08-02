///////////////////////////////////////////////////////////////////////////
//   # Mobile Dragon Demo Project #
//   # Static Scene #
//
//   This demo shows how to load and display static scene with
//   LOD (levels of detail) technology.
//   Also this demo show how to process input events,
//   display FPS and control the camera.
///////////////////////////////////////////////////////////////////////////

#include "main.h"


MDGame* MDGameCreate( System * system )
{
	// Call constructor of GameProject here.
	return new GameProject( system );
}

void MDGameSetPreferences( MDGamePreferences & p )
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

GameProject::GameProject(System* system_)
{
	/**
	 * Store pointer to System class object.
	 */

	system = system_;
 
	/**
	 * Create and store new 3D Render class object. Only one Render2D or Render3D class object can be.
	 */

	system->render3d = render = new Render3D;
}

GameProject::~GameProject()
{
	/**
	* Do here deleting of all created game data.
	*/

	o3dlist.clear();

	sky.clear();

	font.Free();
}

Bool GameProject::Init()
{
	/**
	 * Do initialization of game here.
	 */

	// Zero counters.
	ai_ticks = 0;
	fps_start_ticks = 0;
	fps_frame_count = 0;
	game_fps = 0;

	// Help message is visible.
	help_visible  = True;

	// Get display width and height.
	Int w = render->GetScreenWidth();
	Int h = render->GetScreenHeight();

	
	// Set perspective.
	Fixed fovy = DegToRad(70);
	Fixed aspect = Fixed(w)/h;
	Fixed zNear = F_ONE;
	Fixed zFar = 150;

	render->SetPerspective(fovy,aspect,zNear,zFar);

	// Set render viewport to whole display.
 	render->SetViewport(0,0,w,h);

	// Create game font.
	font.Create(render,"Arial");


	/* Load Landscape */
	
	// List of objects one level of details.
	vector< ObjRef<Basic3D> > lod_o3dlist;

 	// 3D data loader.
 	MDMLoad mdm_arena_h;
 
 	// Load scene in high LOD.
  	mdm_arena_h.Init(render,"arena-01\\arena-01_h");
  	mdm_arena_h.Load(render, lod_o3dlist);
 
 	// Add list of objects of high LOD to the common list of objects.
 	o3dlist.push_back(lod_o3dlist);
 
 	// Prepare list to the next loading.
 	lod_o3dlist.clear();
 	
 	// 3D data loader.
 	MDMLoad mdm_arena_m;
 
 	// Load scene in middle LOD.
  	mdm_arena_m.Init(render,"arena-01\\arena-01_m");
  	mdm_arena_m.Load(render, lod_o3dlist);
 
 	// Add list of objects of middle LOD to the common list of objects.
 	o3dlist.push_back(lod_o3dlist);
 
 	lod_o3dlist.clear();
 	
 	// Load and apply LOD settings for this arena.
 	render->LoadLODSettings(o3dlist, "arena-01\\arena-01");



	/* Load Sky */

	// 3D data loader.
	MDMLoad mdm_sky;

	// Load sky box.
	mdm_sky.Init(render,"sky\\sky");
	mdm_sky.Load(render,sky);


	/* Init Camera */

	camera.Init(system);

	// Set position for camera.
	camera.Set(Vector3fx(0,5,0),Vector3fx(0,5,5), Vector3fx(0,1,0));

	// Send camera's reference to render.
	// Render use current camera to compute current LOD to draw objects.
	render->SetCamera(&camera);

	
	/* Lights */

	omni = Light::New();
	
	omni->type = Light_Type_Directional;
	
	omni->radius = 1000;
	
	omni->direction = Normalize(Vector3fx(-1,-1,-1));
	
	render->AddLight( omni );


	/* Fog */

	render->SetFogMode( Render_FogMode_Exp );

	render->SetFogDensity( F_HALF );

	render->SetFogStart( 20 );

	render->SetFogEnd( 250 );

	render->SetFogColor( Color( 255, 255, 255, 255 )  );

	render->UpdateFog();

	return True;

}

Bool GameProject::Update()
{
	// Get current ticks.
	DWord ticks = system->GetTicks();

	// Zero AI run count per this LoopGame() call.
	Int is_ai_run = 0;

	// Do AI run if first time (ai_ticks=0) or if we have time for new AI run.
	{
		// Count this AI run.
		is_ai_run++;

		/**
		 * We need to have exit from our game. 
		 * This do it if gamer press key 0 or clik in first 20 top lines of display by stylus.
		 */

		Short pen_x,pen_y;
		system->input.PenState( &pen_x, &pen_y );

		if( ( system->input.PenClicked() && pen_y < 20 ) || system->input.KeyDown(KEY_FIRE) )
		{
			system->Exit();
			return False;
		}

		/**
		 * Game AI run need to be implemented here.
		 */
		
		// Camera movement increments.
		Fixed cam_vert_incr = 0.3;	// vertical rotating increment.
		Fixed cam_horiz_incr = 0.3; // horizontal rotating increment.
		Fixed cam_trans_incr = 0.7; // translation increment.

		// Get orientation of camera. 
		Vector3fx cam_dir = camera.GetDir();	// direction
		Vector3fx cam_left = camera.GetLeft();  // vector "Left"
		Vector3fx cam_up = camera.GetUp();		// vector "Up"

		/**
		 * Compute new position and target point for camera.
		 */

		if( system->input.KeyDown(KEY_UP) )
		{
			camera.Set(camera.GetPos(), camera.GetPos() + cam_dir * 5 + cam_up * cam_vert_incr,Vector3fx(0,1,0));

			help_visible = False;
		}

		if( system->input.KeyDown(KEY_DOWN) )
		{
			camera.Set(camera.GetPos(), camera.GetPos() + cam_dir * 5 - cam_up * cam_vert_incr,Vector3fx(0,1,0));

			help_visible = False;
		}

		if( system->input.KeyDown(KEY_RIGHT) )
		{
			camera.Set(camera.GetPos(), camera.GetPos() + cam_dir * 5 - cam_left * cam_horiz_incr,Vector3fx(0,1,0));

			help_visible = False;
		}

		if( system->input.KeyDown(KEY_LEFT) )
		{
			camera.Set(camera.GetPos(), camera.GetPos() + cam_dir * 5 + cam_left * cam_horiz_incr,Vector3fx(0,1,0));

			help_visible = False;
		}

		if( system->input.KeyDown(KEY_A) )
		{
			camera.Set(camera.GetPos() + cam_dir * cam_trans_incr, camera.GetTarget() + cam_dir * cam_trans_incr,Vector3fx(0,1,0));

			help_visible = False;
		}

		if( system->input.KeyDown(KEY_B) )
		{
			camera.Set(camera.GetPos() - cam_dir * cam_trans_incr, camera.GetTarget() - cam_dir * cam_trans_incr,Vector3fx(0,1,0));

			help_visible = False;
		}


		// Get view matrix from camera.
		view_mx = camera.GetViewMatrix();
	}

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

	render->Clear(Render_ClearType_ClearColor|Render_ClearType_ClearDepth);


	/**
	 * Do all game game scene drawing here.
	 */

	/* Draw sky. */

	// Zero translation portion of view matrix.
	view_sky_mx = view_mx;
	view_sky_mx(0, 3) = F_ZERO;
	view_sky_mx(1, 3) = F_ZERO;
	view_sky_mx(2, 3) = F_ZERO;
	
	// Set view matrix.
	render->SetView(&view_sky_mx);

	// Switch necessary modes for render.
	render->SetMode(Render_BackToFront_Mode);
	render->SetMode(Render_NoZ_Mode);
		  
	// Draw sky.
	sky[0]->Draw();

	render->Flush();
	
	// Return switched modes for render.
	render->ClearMode(Render_BackToFront_Mode);
	render->ClearMode(Render_NoZ_Mode);

	/* Draw scene. */

	// Set normal view matrix.
	render->SetView(&view_mx);

	// Draw objects from High LOD objects list.
	Int i = o3dlist[0].size();
	while ( --i >= 0 )
	{
		o3dlist[0][i]->Draw();
	}
 
	render->Flush();


	/**
	 * Display game FPS.
	 */

	// Set identity world transformation matrix.
	render->SetWorldIdentityMatrix();

	// Set view matrix for drawing FPS.
	view_mx = TranslationMatrix4(Vector3fx(0,0,-0.4));
	render->SetView(&view_mx);

	// Draw FPS.
	system->user_string0 = "FPS: ";
	system->user_string0 << ( game_fps / 100 ) << "." << ( game_fps % 100 );
	font.Draw(system->user_string0.data(),&Vector3fx(-(1-F_ONE/3),1,-1-F_ONE/2),&Vector3fx(2,2,0),Color(255,0,0,0));

	/* Draw Help message. */
	if (help_visible)
	{

		system->user_string0 = "Up - turn Up:";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.7,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "Down - turn Down";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.6,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "Left - turn Left";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.5,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "Right - turn Right";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.4,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "A key - move Forward";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.3,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "B key - move Backward";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0.2,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));

		system->user_string0 = "FIRE - to Exit";
		font.Draw(system->user_string0.data(),&Vector3fx(-0.75,0,-1-F_ONE/2),&Vector3fx(1.1,1.1,0),Color(255,255,255,0));
	}

	/**
	 * As font only send text to draw queue we need to process draw queue again.
	 */

	render->Flush();

//////////////////////////////////////////////////////////////////////////

	/**
	 * Only now copy backbuffer to video memory on display.
	 */

	render->Show();

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

}