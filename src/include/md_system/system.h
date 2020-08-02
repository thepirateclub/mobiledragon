/** \file
 *	MobileDragon system management. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_SYSTEM_H__
#define __MD_SYSTEM_H__

namespace mdragon
{

class PackDir;
class Render3D;
class Render2D;

/// Basic MobileDragon system management.
/**
 *	This instance of System object created by MobileDragon core, and
 *	pointer to it is passed to user defined MDGameCreate funtion.
 *	Don't delete this object .
 *	It stores pointers to render2d, render3d objects,
 *	and instances of BtNetwork, Input, SoundSystem classes.
 */
class System
{
public:

	/// Constructor. .
	/**
	 *	Do not create instances of System object, it is automatically 
	 *	created by MobileDragon core.
	 */
	System( const Char * program_name_, Int system_memory_pool_size_ );

	/// Destructor.
	~System();

	/// Sets system exit flag. 
	/**
	 *	After returning from MDGame::Update() the MobileDragon core will 
	 *	return controlto the host OS if this flag is set.
	 */
	void Exit();

	Bool IsExit();

	Bool Init( PackDir* packdir_ );

	/**
	 *	Get system PackDir class object.
	 *	@return pointer to PackDir class object.
	 */
	PackDir* GetPackDir() { return packdir; }


	inline Byte* GetPool(Int size_);

	inline Int FreePoolSize();

	inline Int PoolSize();

	inline void SavePool( Int *used_, Int *free_ );

	inline void RestorePool( Int used_, Int free_ );

	/// Reads application persistent data to Resource object.
	Bool ReadFlashData( Resource& flashdata );

	/// Writes application persistent data.
	/**
	 *	@param flashdata - Resource object containing data to save.
	 *	@return True if write completed successfully else False.
	 */
	void WriteFlashData(Resource& flashdata);

	/// Writes string to system log file.
	/**
	 *	@param str - pointer to ASCIIZ string.
	 */
	void LOG( const Char *str );

	/// Writes string to system log file.
	/**
	 *	@param str - string to write.
	 */
	inline void LOG( const string& str ) { *log << str;  }

	/// Writes memory dump to system log.
	/**
	 *	@param buffer - pointer to memory hex dump.
	 *	@param size - define size of memory hex dump.
	 */
	inline void LOGHexDump(const void* buffer, Int size);
	
	/// Returns system ticks in microseconds.
	DWord GetTicks() { return ticks; }

	/// Returns program name.
	const string & GetProgramName() { return program_name; }

//////////////////////////////////////////////////////////////////////////

	/// Instance of Input class oject.
	Input input;
	
	/// Instance of BtNetwork class object.
	BtNetwork btnet;

	/// Instance of SoundSystem class object.
	SoundSystem sound_system;

	Render2D* render2d;	
	Render3D* render3d;
	
//////////////////////////////////////////////////////////////////////////

	string user_string0;
	string user_string1;
	string user_string2;
	string user_string3;
	string user_string4;
	string user_string5;
	string user_string6;
	string user_string7;
	string user_string8;
	string user_string9;

//////////////////////////////////////////////////////////////////////////

	friend class PackDir;
	friend class Render3D;
	friend class Render2D;
	friend class Image;
	friend class Texture;
	friend class LightMap;
	friend class MDMLoad;
	friend class Font2D;

//////////////////////////////////////////////////////////////////////////

	DWord ticks;

#ifdef MD_OS_PALM
	DWord DeviceID;
#endif

	int debug_level;

private:

	string system_string0;
	string system_string1;
	string system_string2;
	string system_string3;
	string system_string4;

	Bool is_exit;

	string program_name;

	PackDir* packdir;

//	Float32* div_table;

	Byte* system_memory_pool;
	Int system_memory_pool_size;
	Int system_memory_pool_used_size;
	Int system_memory_pool_free_size;

	Log* log;

};

#define SAVE_SYSTEM_POOL_LEVEL(system,x) Int system_pool_used_##x, system_pool_free_##x; (system)->SavePool(&system_pool_used_##x,&system_pool_free_##x);
#define RESTORE_SYSTEM_POOL_LEVEL(system,x) (system)->RestorePool(system_pool_used_##x,system_pool_free_##x);

#ifndef Fixed

#define DIV_TABLE8(r,x) ( (r) = div_table[ ( (x) >> 8 ) & 0xFFFF ] )

//#define DIV_TABLE(r,x) ( (r) = FDiv( (1<<16), (x) ) )

/*
inline void DIV_TABLE( Int& r, Int x )
{
	if( x )
		r = FDiv( (1<<16), x );
	else
		r = 0;
}
*/

/*
#define DIV_TABLE(r,x) \
{ \
	if( (x) > 0 ) \
	{ \
		(r) = (x) >> 8; \
		if( (r) < ( 1 << ( 16 ) ) ) \
			r = div_table[ (r) ]; \
		else \
		if( (r) < ( 1 << ( 16 + 2) ) ) \
			r = div_table[ (r) >> ( 2 ) ] >> ( 2 ); \
		else \
		if( (r) < ( 1 << ( 16 + 4) ) ) \
			r = div_table[ (r) >> ( 4 ) ] >> ( 4 ); \
		else \
		if( (r) < ( 1 << ( 16 + 6) ) ) \
			r = div_table[ (r) >> ( 6 ) ] >> ( 6 ); \
		else \
			r = div_table[ (r) >> ( 8 ) ] >> ( 8 ); \
	} \
	else \
	{ \
		(r) = ( -(x) ) >> 8; \
		if( (r) < ( 1 << ( 16 ) ) ) \
			r = div_table[ (r) ]; \
		else \
		if( (r) < ( 1 << ( 16 + 2) ) ) \
			r = div_table[ (r) >> ( 2 ) ] >> ( 2 ); \
		else \
		if( (r) < ( 1 << ( 16 + 4) ) ) \
			r = div_table[ (r) >> ( 4 ) ] >> ( 4 ); \
		else \
		if( (r) < ( 1 << ( 16 + 6) ) ) \
			r = div_table[ (r) >> ( 6 ) ] >> ( 6 ); \
		else \
			r = div_table[ (r) >> ( 8 ) ] >> ( 8 ); \
		(r) = - (r); \
	} \
}
*/

#endif

#ifdef Fixed

/*
#define DIV_TABLE8(r,x) ( (r) = 1.0f / (x) )

#define DIV_TABLE(r,x) ( (r) = 1.0f / (x) )
*/

#endif

#ifndef Fixed

/*
inline void System::DivideOne( Fixed& divider, Fixed& result )
{
	DIV_TABLE( result.value , divider.value );
}
*/

#endif

#ifdef Fixed

/*
inline void System::DivideOne( Fixed& divider, Fixed& result )
{
	DIV_TABLE( result , divider );
}
*/

#endif

/*
inline Float32 System::DivideOne( Float32 divider )
{
	DIV_TABLE( divider, divider );
	return divider;
}
*/

inline Byte* System::GetPool(Int size_)
{
	size_ = size_ + ( 4 - (size_&3) );

	if( system_memory_pool_used_size + size_ < system_memory_pool_size )
	{
		Byte* ret_pool = system_memory_pool + system_memory_pool_used_size;

		system_memory_pool_used_size += size_;
		system_memory_pool_free_size += size_;

		return ret_pool;
	}

	return NULL;
}

/*
inline Int System::FreePool(Int size_)
{
	size_ = size_ + ( 4 - (size_&3) );

	system_memory_pool_free_size -= size_;

	if( system_memory_pool_free_size <= 0 )
	{
		system_memory_pool_used_size = 0;
		system_memory_pool_free_size = 0;
	}

	return system_memory_pool_used_size;
}
*/

inline Int System::FreePoolSize()
{
	return system_memory_pool_size - system_memory_pool_used_size;
}

inline Int System::PoolSize()
{
	return system_memory_pool_size;
}

inline void System::SavePool( Int *used_, Int *free_ )
{
	*used_ = system_memory_pool_used_size;
	*free_ = system_memory_pool_free_size;
}

inline void System::RestorePool( Int used_, Int free_ )
{
	system_memory_pool_used_size = used_;
	system_memory_pool_free_size = free_;
}

inline void System::LOG( const Char *buffer_ )
{
	log->Write( buffer_ );
}           

inline void System::LOGHexDump(const void* buffer_, Int size_)
{
	log->WriteHexDump( buffer_, size_ );
}           

#ifdef MD_OS_PALM

// Palm device id's :

// Intel XScale PXA CPU's

#define sonyHwrOEMDeviceIDCordoba	'crdb'
#define sonyHwrOEMDeviceIDGranada	'grnd'
#define sonyHwrOEMDeviceIDVerona	'vrna'
#define sonyHwrOEMDeviceIDMadrid	'mdrd'
#define sonyHwrOEMDeviceIDToledo	'tldo'

/* PEG-NX70(V) & NX60 */
#define sonyHwrOEMDeviceID_NX70		sonyHwrOEMDeviceIDCordoba
/* PEG-NZ90 */
#define sonyHwrOEMDeviceID_NZ90		sonyHwrOEMDeviceIDGranada
/* PEG-TG50 */
#define sonyHwrOEMDeviceID_TG50		sonyHwrOEMDeviceIDVerona
/* PEG-NX73 */
#define sonyHwrOEMDeviceID_NX73		sonyHwrOEMDeviceIDToledo
/* PEG-NX80 */
#define sonyHwrOEMDeviceID_NX80		sonyHwrOEMDeviceIDMadrid
/* Tungsten|C*/
#define palmDeviceID_TC			'MT64'
/* Tungsten|T3*/
#define palmDeviceID_T3			'Arz1'

#define palmDeviceID_T5	'TnT5'

// Texas Instruments OMAP CPU's
#define palmDeviceID_TT			'Frg1'
#define palmDeviceID_T2			'Frg2'
#define palmDeviceID_TE			'CCt1'

#define palmDeviceID_TE2		'Zir4'

#define palmDeviceID_LifeDrive	'TunX'

#define palmDeviceID_Zire21		'Zi21' 
#define palmDeviceID_Zire71		'Zpth'

#define palmDeviceID_Treo600	'H101'

#define palmDeviceID_Treo650	'H102'

#define palmDeviceID_Zodiac	'Rdog'

// Motorola MXL CPU's
#define sonyHwrOEMDeviceIDGoku		'goku'
#define sonyHwrOEMDeviceIDGohan		'goha'
/* PEG-TJ35 */
#define sonyHwrOEMDeviceID_TJ35		sonyHwrOEMDeviceIDGoku
/* PEG-TJ25 */
#define sonyHwrOEMDeviceID_TJ25		sonyHwrOEMDeviceIDGohan
#define palmDeviceID_iQ3600		'3600'

#endif	

} //namespace mdragon

#endif // __MD_SYSTEM_H__
