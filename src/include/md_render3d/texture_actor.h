/** \file
 *	Texture animation. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TEXTURE_ACTOR_H__
#define __MD_TEXTURE_ACTOR_H__

namespace mdragon
{

class Render3D;

struct KeyFrame;


/// Texture animation storage.
/**
 * One TextureAnimation object can store only one texture animation.
 */
class TextureAnimation : public Object
{
protected:

	/// Default constructor.
	TextureAnimation();

	/// Destructor.
	~TextureAnimation(){};

public:

	/// Creates new TextureAnimation object.
	/**
	 *  Call this function instead constructor calling.
	 *  @return Return object reference to new TextureAnimation object.
	 */
	static ObjRef<TextureAnimation> New()
	{
		return ObjRef<TextureAnimation>( new TextureAnimation );
	}

	/// Return name of texture animation.
	/**
	 *  @return Return name of texture animation.
	 */
	inline const string & GetName() const { return name; }

	/// List of textures for animation.
	vector< ObjRef<Texture> > textures;

	/// List of key frames.
	vector<KeyFrame> key_frames;

	/// friends
	friend class Render3D;

private:

	/// Name of texture animation.
	string name;
};



/// TextureActor represents texture actor object, that control texture animation.
class TextureActor 
{	
public:

	/// Default constructor.
	TextureActor();

	/// Destructor.
	~TextureActor();

	/// Set texture animation for playing.
	/**
	 * @param texture_animation_ - texture animation for playing.
	 */
	inline void SetAnimation(ObjRef<TextureAnimation> texture_animation_) { texture_animation = texture_animation_; }

	/// Get current texture animation.
	/**
	 * @return Return current texture animation.
	 */
	inline ObjRef<TextureAnimation> GetAnimation() { return texture_animation; }

	/// Continues play animation with specified time step.
	/**
	 * Call this function per one AI run.
	 * @param time_step - define play time.
	 */
	ObjRef<Texture> Play(Int time_step_ = 160);

	/// Sets current animation time value and select current active texture from list of textures.
	/**
	 * @param time_ - define start animation time.
	 * @param loop_play - if zero animation will be stop in the end of playing 
	 *                    on last frame else continue playing from first frame.
	 */
	ObjRef<Texture> Set(Int time_,Int loop_play_=0);

	/// Return pointer to the current active texture.
	/**
	 * @return Return pointer to the current active texture.
	 */
	inline ObjRef<Texture> GetActiveTexture() { return active_texture; }

	/// Return current animation full time length.
	/**
	 * @return Return current animation full time length.
	 */
	Int GetTimeLength();

	/// Return current animation time.
	/**
	 * @return Return current animation time.
	 */
	inline Int GetTime() { return time; }

	/// Return the play directions state.
	/**
	 * @return Return 1, if play direction is "forward", 
	 *         returns 0, if play direction is "stop",
	 *		   returns -1, if play direction is "backward".
	 */
	inline Int GetPlayDirection() { return play_direction; }

private:

	/// Current texture animation.
	ObjRef<TextureAnimation> texture_animation;

	/// Current animation time.
	Int time;

	/// Pointer to the current active texture.
	ObjRef<Texture> active_texture;

	/// If animation loop play.
	Int loop_play;

	/// Play direction.
	/**
	 * This variable updates by calling Play() function. 
	 * If parameter (time_step) of this function > 0, than play_direction is "forward" (value = 1). 
	 * If parameter (time_step) of this function == 0, than play_direction is "stop" (value = 0).
	 * If parameter (time_step) of this function < 0, than play_direction is "backward" (value = -1). 
	 */
	Int play_direction;
};

} //namespace mdragon

#endif // __MD_TEXTURE_ACTOR_H__