///////////////////////////////////////////////////////////////////////////
//   # Mobile Dragon Demo Project #
//   # Portal Scene + Tweening Animation #
//
//   This demo shows how to load and display scene with
//   portal technology and tweening animation.
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

	rooms.clear();

	portals.clear();

	out_of_portals.clear();

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
	Fixed zFar = 500;

	render->SetPerspective(fovy,aspect,zNear,zFar);

	// Set render viewport to whole display.
 	render->SetViewport(0,0,w,h);

	// Create game font.
	font.Create(render,"Arial");


	/* Load Scene */

	// 3D data loader.
	MDMLoad loader;

	// Load static portal scene.
	loader.Init(render,"portals\\portals");
 	loader.Load(render, o3dlist);

	// Get portals, rooms and out_of_portals lists.
	portals = loader.portals;
	rooms = loader.rooms;
	out_of_portals = loader.out_of_portals;

	// Zero rooms variable.
	current_room = NULL;
	previous_room = NULL;

	// Create list of waypoints by dummy objects list.
	CreatePositionList(loader.dummies);


	/* Load Animation */

	// Construct new animation objects to store animation 
	actor_animation = Actor3DAnimation::New(render);

	// Load animation.
	loader.Init(render, "tweening\\tweening");
	loader.Load(render, actor_animation); 


	// Create and initialize actor object.
	actor = Actor3D::New(render);
	actor->Create(actor_animation);
	actor->Set(actor_animation,0,1);

	// Set start values for actor moving.
	curr_waypoint = 0;	// index of current target waypoint.
	actor_speed = 0.5;  // actor's moving speed.
	curr_dir = Vector3fx(0,0,1);	// actor's start direction (equal direction in 3D Max model).

	/* Init Camera */

	camera.Init(system);

	// Set orientation for camera.
	camera.Set(Vector3fx(0,20,30), Vector3fx(0,20,0), Vector3fx(0,1,0));

	// Set camera to the render.
	render->SetCamera(&camera);

	
	/* Lights */

	omni = Light::New();
	
	omni->type = Light_Type_Directional;
	
	omni->radius = 1000;
	
	omni->direction = Normalize(Vector3fx(-1,-1,-1));
	
	render->AddLight( omni );

 

	/* Fog */

	// Disable Fog.
	render->ClearMode(Render_Fog_Mode);

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
		Fixed cam_trans_incr = 1.3; // translation increment.

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

		// Update actor position.
		UpdateActorPosition();

		// Play actor animation.
		actor->Play();	

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

	/* Draw scene. */

	// Set normal view matrix.
	render->SetView(&view_mx);


	// Find the current room from portal system.

	if(current_room)
		current_room = FindRoomAround(camera.GetPos(), current_room);	

	if(!current_room)
		current_room = FindStartRoom(camera.GetPos(),rooms);

	if(current_room)   // if we find the room
	{
		previous_room = current_room;
	}

	if(previous_room)
	{
		Fixed radius = 10; // radius of sphere to check collision with portals. 
		Portal *cross_portal = FindCrossPortal(previous_room, camera.GetPos(), radius);

		if(cross_portal)
			DrawPortal(cross_portal,rooms);
		else
			DrawFromRoom(previous_room, rooms);
	}


	for(Int i = 0; i < out_of_portals.size(); i++)
		out_of_portals[i]->Draw();


	actor->Draw();
 

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

void GameProject::CreatePositionList(vector< ObjRef<Basic3D> > &dummies_)
{
	// Sort DummyBox object list by object's name.
	sort(dummies_.begin(), dummies_.end(), GameProject::ComparePositions);

	// Create waypoints list from positions of the DummyBox objects.
	for(Int i = 0;  i < dummies_.size(); i++)
	{
		if(dummies_[i]->GetClassID() == ClassID_DummyBox)
		{
			Vector3fx p = GetTranslation(dummies_[i].cast((DummyBox*) NULL)->relative);
			position_list.push_back(p);
		}
	}
}

void GameProject::UpdateActorPosition()
{
	// Get current actor position.
	Vector3fx curr_pos = GetTranslation(actor->transform);
	
	// Compute new actor direction - direction from current position 
	// to the current target waypoint.
	Vector3fx dir = position_list[curr_waypoint] - curr_pos;

	// Get distance from current actor position to the target waypoint. 
	Fixed distance = GetLength(dir);
	
	// If actor is near from current target waypoint, switch current target 
	// waypoint to the next waipoint from list.
	if ( distance < actor_speed )
	{
		curr_waypoint ++;
		curr_waypoint %= position_list.size();

		// Compute new direction.
		dir = position_list[curr_waypoint] - curr_pos;
	}
	
	dir = Normalize(dir);
	
	// Interpolate direction between current and new direction for smooth rotating.
	dir = Normalize( curr_dir + (dir - curr_dir) * 0.15);
	
	// Save new direction.
	curr_dir = dir;
	
	// Compute new actor position by new direction.
	Vector3fx new_pos = curr_pos + dir * actor_speed;

	// Compute left vector for actor orientation.
	Vector3fx left = Normalize(CrossProduct(Vector3fx(0,1,0),dir));

	// Compute up vector for actor orientation.
	// If actor stay always vertical, we can simply use vector (0,1,0) 
	// in optimization purpose.
	// For example:
	//		Vector3fx up = Vector3fx(0,1,0); 
	Vector3fx up = Normalize(CrossProduct(dir,left));

	// Set the new transformation matrix to the actor.

	// Orientation part of matrix.
	actor->transform._11 = left.x;	actor->transform._21 = left.y;	actor->transform._31 = left.z;
	actor->transform._12 = up.x;	actor->transform._22 = up.y;	actor->transform._32 = up.z;
	actor->transform._13 = dir.x;	actor->transform._23 = dir.y;	actor->transform._33 = dir.z;

	// Translate part of matrix.
	actor->transform._14 = new_pos.x;	
	actor->transform._24 = new_pos.y;
	actor->transform._34 = new_pos.z;

}

Bool GameProject::ComparePositions(ObjRef<Basic3D> first_, ObjRef<Basic3D> second_)
{
	return first_->GetName() < second_->GetName();
}