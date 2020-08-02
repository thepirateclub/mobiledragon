///////////////////////////////////////////////////////////////////////////
//   # Mobile Dragon Demo Project #
//   # Tweening Animation #
//
//   This demo shows how to load and display animated model 
//   with tweening (morphing) animation with different Levels Of Detail.
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

	//animations_list.clear();

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


	/* Load Animation */

	// Construct new animation objects to store animation.
	actor_animation = Actor3DAnimation::New(render);
		
	// Load animation.
	MDMLoad mdm_anim_high;
	mdm_anim_high.Init(render, "tweening\\tweening");
	mdm_anim_high.Load(render, actor_animation); 

	// Create and initialize actor object.
	actor = Actor3D::New(render);
	actor->Create(actor_animation);
	
	// Define current animation phase for the actor.
	// Set animation into 0 key frame and set animation loop_play flag on.
	actor->Set(actor_animation,0,1);

	/* Init Camera */

	camera.Init(system);

	// Set orientation for camera.
	camera.Set(Vector3fx(15,15,15), GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0), Vector3fx(0,1,0));

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
	Fixed cam_vert_incr = 0.1;	// vertical rotating increment.
	Fixed cam_horiz_incr = 0.1; // horizontal rotating increment.
	Fixed cam_trans_incr = 0.7; // translation increment.

	// Get orientation of camera. 
	Vector3fx cam_dir = camera.GetDir();	// direction
	Vector3fx cam_left = camera.GetLeft();  // vector "Left"
	Vector3fx cam_up = camera.GetUp();		// vector "Up"

	// New Pos and Target vectors.
	Vector3fx pos, target;

	/**
	* Compute new position and target point for camera.
	*/

	if( system->input.KeyDown(KEY_UP) )
	{
		pos = camera.GetTarget() + RotateVector3(camera.GetPos()-camera.GetTarget(),RotationMatrix4(camera.GetLeft(),cam_vert_incr));
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target, camera.GetUp());				

		help_visible = False;
	}

	if( system->input.KeyDown(KEY_DOWN) )
	{
		pos = camera.GetTarget() + RotateVector3(camera.GetPos()-camera.GetTarget(),RotationMatrix4(camera.GetLeft(),-cam_vert_incr));
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target, camera.GetUp());		

		help_visible = False;
	}

	if( system->input.KeyDown(KEY_RIGHT) )
	{
		pos = camera.GetTarget() + RotateVector3(camera.GetPos()-camera.GetTarget(),RotationMatrix4(camera.GetUp(),cam_horiz_incr));
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target ,camera.GetUp());

		help_visible = False;
	}

	if( system->input.KeyDown(KEY_LEFT) )
	{
		pos = camera.GetTarget() + RotateVector3(camera.GetPos()-camera.GetTarget(),RotationMatrix4(camera.GetUp(),-cam_horiz_incr));
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target ,camera.GetUp());

		help_visible = False;
	}

	if( system->input.KeyDown(KEY_A) )
	{
		pos = camera.GetPos() + cam_dir * cam_trans_incr;
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target, camera.GetUp());

		help_visible = False;
	}

	if( system->input.KeyDown(KEY_B) )
	{
		pos = camera.GetPos() - cam_dir * cam_trans_incr;
		target = GetTranslation(actor->GetResultTransform())+Vector3fx(0,10,0);

		camera.Set(pos, target, camera.GetUp());

		help_visible = False;
	}

	// Get view matrix from camera.
	view_mx = camera.GetViewMatrix();
 
	// Play animation.
	actor->Play();

	return True;
}

void GameProject::Draw()
{
	/**
	 * First we need to clear viewport.
	 */

	render->SetClearColor(Color(128,128,128,0));

	render->Clear(Render_ClearType_ClearColor|Render_ClearType_ClearDepth);


	/**
	 * Do all game game scene drawing here.
	 */

	/* Draw scene. */

	// Set normal view matrix.
	render->SetView(&view_mx);

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