/** \file
 *	2d sprite animation actor. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ACTOR2D_H__
#define __MD_ACTOR2D_H__

namespace mdragon
{

/// Actor2D represents 2d sprite actor class.
/**
 *	This class provides control over 2d sprites animation playback.
 */
class Actor2D : public SpriteTransform
{
public:

	/// Actor2D class constructor.
	Actor2D();

	/// Actor2D class destructor.
	/**
	 *	Please note that any sprite transform frames will be not deleted.
	 */
	 ~Actor2D();
	
	/// Performs the complete initialization of Actor2D class object.
	/**
	 * This function must be called before any operations on Actor2D class object.
	 * @param frames - pointer to SpriteTransform class objects array. 
	 *                  This array represents all frames for animation. 
	 *                  See class Animation.
	 * @param loop_play - if zero animation will be stop in the end of playing 
	 *                  on last frame else continue playing from first frame.
	 */
	void Set( SpriteTransform** frames, Bool loop_play = False );

	/// Plays animation specified time in frames
	/**
	 * If animation is stopped than do not play any time.
	 * @param time_step define playtime in frames.
	 * Call this function per one AI run.
	 */
	void Play( Int time_step = 1 );

	/// Stops to play animation 
	/**
	 * To continue play animation call Start().
	 */
	void Stop();	

	/// Starts or continues to play animation from specified time in frames.
	/**
	 * @param start_time - define new playtime in frames. If equal to -1 
	 *			continues playback animation from stop time.
	 */
	void Start( Int start_time = -1 );

	/// Returns pointer to the frame playing.
	SpriteTransform* GetFrame() { return frame;	}

	/// Returns animation time length for all frames.
	/**
	 * @return animation time length for all frames.
	 */
	Int GetEndTime() { return end_time; }

	/// Returns animation length in frames.
	/**
	 * @return Returns animation length in frames.
	 */
	Int GetFramesCount() { return frames_count;	}

	/// Returns pointer to the specified animation frame.
	/**
	 * @return Returns pointer to the specified animation frame.
	 */
	SpriteTransform* GetFrame(Int i);

private:

	SpriteTransform** frames;
	SpriteTransform* frame;

	Int frames_count;

	Int end_time;
};

} //namespace mdragon

#endif // __MD_ACTOR2D_H__