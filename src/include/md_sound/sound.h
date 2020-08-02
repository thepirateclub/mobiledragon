/** \file
 *	.wav file music support. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MTL_SOUND_H__
#define __MTL_SOUND_H__

namespace mdragon
{

struct SoundResource;

/// Represents .wav sound.
class Sound
{
public:

	/// Sets this sound volume.
	/**
	 *	Volume ranges from 0( total silence ) to 64( max volume ).
	 *	@param volume - new desired volume for this sound.
	 */
	void SetVolume( DWord volume ); 

	/// Get this sound current volume.
	/**
	 *	@return current volume.
	 */
	DWord GetVolume();

	/// Sets this sound pan value.
	/**
	 *	Pan value ranges from 0 ( left ) to 255 ( right ), 
	 *	default is 128( normal ).
	 *	@param pan - new desired pan value.
	 */
	void SetPan( DWord pan );

	/// Get this sound pan value.
	/**
	 *	@return current pan value.
	 */
	DWord GetPan();

	/// Select looping playback mode for this sound.
	/**
	 *	@param loop - True for looping playback, False for one time only.
	 */
	void SetLoop( Bool loop );

	/// Checks current looping playback mode for this sound.
	/**
	 *	@return current loop flag.
	 */
	Bool GetLoop();

	/// Sets this sound playback speed.
	/**
	 *	@param speed - new desired speed. 128 is normal speed.
	 */
	void SetSpeed( DWord speed );

	/// Get this sound playback speed.
	/**
	 *	@return current sound playback speed.
	 */
	DWord GetSpeed();
	
	/// Sets this sound priority.
	/**
	 *	@param priority - new sound priority.
	 */
	void SetPriority( Int priority );

	/// Get this sound priority.
	/**
	 *	@return current sound priority.
	 */
	Int GetPriority();


private:
	Sound( SoundResource * resource_ );

	~Sound();

	friend class SoundSystem;
	
	void* ptr_sound;
	Int channel_number;

	SoundResource * resource;

	Int priority;
};

} //namespace mdragon

#endif // __MTL_SOUND_H__
