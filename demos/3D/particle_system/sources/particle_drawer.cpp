#include "particle_drawer.h"


ParticleDrawer::ParticleDrawer()
{
	particle_system = NULL;

	texture_name = "";
	
	render = NULL;

        lighting = False;
}

ParticleDrawer::~ParticleDrawer()
{

}

void ParticleDrawer::Init(Render3D * render_, BasicParticleManager * particle_manager_, 
						  const Char* text_name_, Int transparency_, Bool lighting_)
{
	// Clear list of sprites.
	sprites.clear();

	// Save parameters.
	particle_system = particle_manager_;  
	texture_name = text_name_;
	render = render_;
	lighting = lighting_;


	/* Init sprite's material. */

	Color color(255,255,255,255);

	// Create material.
	Material sprt_mtl; 		

	// Set material color.
	sprt_mtl.ambient = color;
	sprt_mtl.diffuse = color;
	sprt_mtl.specular = color;
	sprt_mtl.emissive = color;

	// Set material power.
	sprt_mtl.power = 1;

	// Set material transparency.
	sprt_mtl.transparency = transparency_;

	// Material is not two sided and not wireframe. 
	sprt_mtl.two_sided = False;
	sprt_mtl.wireframe = False;

	// Set texture to the material.
	sprt_mtl.untextured = False;
	sprt_mtl.diffuse_texture = render->LoadTexture( texture_name.data() );


	/* Create list of sprites. */
	
	for ( Int i = 0; i < particle_system->GetTotalParticlesCount(); i++ )
	{
		// Construct sprite.
		ObjRef<Sprite3D> sprite = Sprite3D::New(render);

		// Set material.
		sprite->material = sprt_mtl;

		// Init size.
		sprite->width = particle_system->pArr[i].size.x;
		sprite->height = particle_system->pArr[i].size.y;
		
		// Set sprite's source pixel in the sprite center.
		sprite->Centering();

		// Set 'Billboard' type for sprite drawing.
		sprite->SetDrawMode(Sprite3D_Draw_Mode_Axis_XY);

		// Set sprite position equal particle position.
		sprite->pos = particle_system->pArr[i].position;

		// Define UV coordinates for the sprite.
		// There are four vertexes in the sprite.
		sprite->uv[0] = 0;
		sprite->uv[1] = 0;

		sprite->uv[2] = 1;
		sprite->uv[3] = 0;
		
		sprite->uv[4] = 1;
		sprite->uv[5] = 1;
		
		sprite->uv[6] = 0;
		sprite->uv[7] = 1;

		// Add new sprite into the sprite list.
		sprites.push_back(sprite);
	}

}


void ParticleDrawer::Draw()
{
	if(!render) return;

        // Flush the draw queue.
	render->Flush();
	
	// If necessary, set lighting OFF.
	if(!lighting)
	{
		render->ClearMode(Render_Light_Mode);
	}
	
	/* Draw all particles. */

	for (Int i = 0; i < particle_system->GetCurrentParticlesCount(); i++)
	{
		// Set sprite's position equal particle's position.
		sprites[i]->pos = particle_system->pArr[i].position;

		// Set sprite's size equal particle's size.
		sprites[i]->width = particle_system->pArr[i].size.x;
		sprites[i]->height = particle_system->pArr[i].size.y;

		// Set sprite's source pixel in the sprite center.
		sprites[i]->Centering();

		// Send sprite to the draw queue.
		sprites[i]->Draw();
	}

	// Flush the draw queue.
	render->Flush();

	// If lighting was disabled, we should enable it.
	if(!lighting)
	{
		render->SetMode(Render_Light_Mode);
	}
	
}