#include "mdragon.h"

using namespace mdragon;


/**
 * Class: ParticleDrawer.
 * Simply class for particles drawing as 3D sprites.
 */
class ParticleDrawer
{
public:

	/**
	 * Constructor.
	 */
	ParticleDrawer();
	

	/**
	 * Destructor.
	 */
	~ParticleDrawer();

	/**
	 * Init() initializes drawer.
	 * @param render_ - pointer to the Render3D class object.
	 * @param particle_manager_ - pointer to the particle manager that presents concrete particles system.
	 * @param text_name_ - texture file name. Sprites will be draw with this texture.
	 * @param transparency_ - sprite's material transparency.
	 * @param lighting_ - define if we need draw particles with lighting or without it.
	 */
	void Init(Render3D * render_, BasicParticleManager * particle_manager_, const Char* text_name_, Int transparency_, Bool lighting_);

	/**
	 * Draw() draws all particles.
	 */
	void Draw();
	
	/**
	 * GetTextureName() return texture file name.
	 * @return Return texture file name.
	 */
	inline const string & GetTextureName() 
	{
		return texture_name; 
	}

	/**
	 * GetParticleManager() return current particle manager (particle system).
	 * @return Return current particle manager (particle system).
	 */
	inline BasicParticleManager * GetParticleManager() 
	{
		return particle_system; 
	}

private:

	// Current particle manager.
	BasicParticleManager * particle_system; 
	
	// Texture file name.
	string texture_name;

	// List of sprites.
	vector< ObjRef<Sprite3D> > sprites;

	// Pointer to the Render3D class objects.
	Render3D * render;

	// Lighting flag. 
	Bool lighting;
};
