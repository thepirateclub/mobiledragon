/** \file
 *	Sound management. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SOUNDSYSTEM_H__
#define __MD_SOUNDSYSTEM_H__

namespace mdragon
{

struct SoundResource
{
	Int	id;
	Byte* buffer;
	size_type size;
	size_type references;

#ifdef MD_OS_PALM
	Word feature_num;
#endif

};


/// Provides control over MobileDragon sound system.
/**
 *	You don't create instances of SoundSystem by yourself, use
 *	sound_system member of System class instance.
 */
class SoundSystem
{
public:

	/// Initializes SoundSystem.
	/**
	 *	Init() performs the complete initialization of SounSystem.
	 *	Must be called before any other use of SoundSystem.
	 *	@param freq - output rate in hz( on Symbian limit this to 8000 or 16000).
	 *	@param bps - 16 or 8 bits output.
	 *	@param stereo - True for stereo output, False for mono.
	 *	@param q_mod_channels - maximum number of ProTracker channels available.
	 *	@param q_wav_channels - maximum number of Wave channels available.
	 *	@param pack_dir - pointer to PackDir object.
	 *	@return True on success, False on failure.
	 */
	Bool Init( DWord freq, DWord bps, Bool stereo, 
				DWord n_mod_chanels, DWord n_wav_chanels, PackDir* pack_dir );
	
	/// Shuts down the sound system.
	/**
	 *	Calls Cleanup() and closes system sound output device.
	 */
	void Shutdown();


	/// Stops all sounds, musics, releases all resources.
	/**
	 *	System sound output device remains open. There is no need
	 *	to make call to Init() after Cleanup().
	 */
	void Cleanup();

	/// Loads new .wav sound from PackDir.
	/**
	 *	@param - file_name sound  file name in PackDir.
	 *	@return pointer to new created Sound object, or NULL on failure.
	 */
	Sound* LoadSound( const Char* file_name );

	/// Loads new .mod music from PackDir.
	/**
	 *	@param file_name - music file name in PackDir.
	 *	@return pointer to new created Music object, or NULL on failure.
	 */
	Music* LoadMusic( const Char* file_name );

	/// Releases specified sound object.
	/**
	 *	@param sound - pointer to sound object to release.
	 */
	void FreeSound( Sound* sound );

	/// Releases specified music object.
	/**
	 *	@param music - pointer to music object to release.
	 */
	void FreeMusic( Music* music );

	/// Stops playback of all sounds and musics.
	void StopAll();

	///	Pauses playback of all sounds and musics.
	void PauseAll();

	/// Resumes playback of all paused sounds and musics.
	void ResumeAll();


	/// Starts playback of specified sound.
	/**
	 *	For paused sound resumes playback.
	 *	@param sound - pointer to sound object to play.
	 */
	void Play( Sound* sound );

	/// Stops playback of specified sound.
	/**
	 *	@param sound - pointer to sound object to stop.
	 */
	void Stop( Sound* sound );

	/// Pauses playback of specified sound.
	/**
	 *	@param sound - pointer to sound object to pause.
	 */
	void Pause( Sound * sound );

	/// Checks if SoundSystem currently plays the sound.
	/**
	 *	@param sound - pointer to sound object to check.
	 *	@return True if sound is playing, False otherwise.
	 */
	Bool IsPlaying( Sound* sound );

	/// Checks if playback of the sound is paused
	/**
	 *	@param sound - pointer to sound object to check.
	 *	@return True if sound is paused, False otherwise.
	 */
	Bool IsPaused( Sound* sound );	


	/// Starts playback of specified music.
	/**
	 *	For paused music resumes playback.
	 *	@param music - pointer to music object to play.
	 */
	void Play( Music* music );

	/// Stops playback of specified music
	/**
	 *	@param music - pointer to music object to stop.
	 */
	void Stop( Music* music );

	/// Pauses playback of specified music
	/**
	 *	Pause() pauses playback of specified music.
	 *	@param music - pointer to music object to pause.
	 */
	void Pause( Music* music );

	/// Checks if SoundSystem currently plays the music.
	/**
	 *	@param music - pointer to music object to check.
	 *	@return True if music is playing, False otherwise.
	 */
	Bool IsPlaying( Music * music );

	/// Checks if playback of the music is paused.
	/**
	 *	@param music - pointer to music object to check.
	 *	@return True if music is paused, False otherwise.
	 */
	Bool IsPaused( Music * music );

	/// Sets volume for all sounds.
	/**
	 *	This affects all sounds. Value ranges from 0 to 64.
	 *	0 is total silence. 64 maximum volume.
	 *	@param sound_volume new volume value to set.
	 */
	void SetGlobalSoundVolume( DWord sound_volume );

	/// Sets volume for all musics.
	/**
	 *	This affects all musics. Value ranges from 0 to 64.
	 *	0 is total silence. 64 maximum volume.
	 *	@param music_volume new volume value to set.
	 */
	void SetGlobalMusicVolume( DWord music_volume );

	/// Gets current sound volume.
	/**
	 *	@return current system volume for sounds.
	 */
	DWord GetGlobalSoundVolume();

	/// Gets current music volume.
	/**
	 *	@return current system volume for musics.
	 */
	DWord GetGlobalMusicVolume();


private:
	SoundSystem();

	~SoundSystem();

	SoundResource* LoadResource( const Char* filename );
	void ReleaseResource( SoundResource & sound_resource );

	vector<Sound*> all_sounds; 
	vector<Music*> all_music;

	vector<SoundResource> resources;

	vector<void*> channels;

	PackDir* pack_dir;

	void* speaker;

	Bool init_ok;

	friend class System;
};

} //namespace mdragon

#endif // __MD_SOUNDSYSTEM_H__
