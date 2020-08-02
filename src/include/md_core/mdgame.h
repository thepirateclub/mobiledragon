/** \file
 *	Base class for MobileDragon application class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MDGAME_H__
#define __MD_MDGAME_H__

namespace mdragon
{

/// Base class for MobileDragon application class.
/**
 *	Derive your game application class from this class.
 */
class MDGame
{
public:

	/// Virtual destructor.
	virtual ~MDGame();

	/// Implement your game initialization here.
	/**
	 *	@return True if initialization completed successfully.
	 */
	virtual Bool Init() = 0;

	/// Implement to perform update your game state.
	/**
	 *	@return False to skip this frame drawing, True to no skip.
	 */
	virtual Bool Update() = 0;

	/// Implement to draw your game screen.
	virtual void Draw() = 0;
};

/// Structure to hold application preferences.
struct MDGamePreferences
{
	/// Game name.
	string name;

	/// Game title.
	string title;

	/// Name of system log file.
	string log_name;

	/// name of PackDir image file without any extensions.
	string pack_dir_name;

	/// size of mobile dragon' internal memory pool.
	DWord system_pool_size;

	/// mobile dragon system log detail level ( 0 - 5 ).
	DWord log_level;

	/// how many times per second MDGame->Update() will be called.
	DWord runs_per_second;

	/// your application's symbian uid.
	DWord symbian_uid;

	/// your application' palm CREATORID.
	DWord palm_creator_id;
};

} // namespace mdragon


/// User implemented function to create application instance.
extern mdragon::MDGame* MDGameCreate( mdragon::System * );

/// User implemented function to pass application preferences to MobileDragon core.
extern void MDGameSetPreferences( mdragon::MDGamePreferences & );


#endif // __MD_MDGAME_H__
