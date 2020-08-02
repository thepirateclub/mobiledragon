/** \file
 *	.mod file music support. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MUSIC_H__
#define __MD_MUSIC_H__

namespace mdragon
{

struct SoundResource;

/// Represents .mod music.
class Music
{
public:

	/// Sets this music volume.
	/**
	 *	Volume ranges from 0( total silence ) to 64( max volume ).
	 *	@param volume - new desired volume for this music.
	 */
	void SetVolume( DWord volume );

	/// Get this music current volume.
	/**
	 *	@return current volume.
	 */
	DWord GetVolume();

	/// Sets this music pan value.
	/**
	 *	Pan value ranges from 0 ( left ) to 255 ( right ), 
	 *	default is 128( normal ).
	 *	@param pan - new desired pan value.
	 */
	void SetPan (DWord pan);

	/// Get this music pan value.
	/**
	 *	@return current pan value.
	 */
	DWord GetPan ();

	/// Select looping playback mode for this music.
	/**
	 *	@param loop - True for looping playback, False for one time only.
	 */
	void SetLoop (Bool loop);

	/// Checks current looping playback mode for this music.
	/**
	 *	@return current loop flag.
	 */
	Bool GetLoop ();

	/// Sets this music playback speed.
	/**
	 *	@param speed - new desired speed. 128 is normal speed.
	 */
	void SetSpeed (DWord Speed);

	/// Get this music playback speed.
	/**
	 *	@return current music playback speed.
	 */
	DWord GetSpeed ();

	
private:
	Music( SoundResource * resource );

	~Music();

	friend class SoundSystem;

	SoundResource * resource;

	void* ptr_music;
	Int channel_number;
};

} //namespace mdragon

#endif // __MD_MUSIC_H__
