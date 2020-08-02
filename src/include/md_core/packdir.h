/** \file
 *	Packed directory image support. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_PACKDIR_H__
#define __MD_PACKDIR_H__

namespace mdragon
{

class PackDirFatInfo;

class System;

/// Packed directory storage system.
/**
 *	Provides methods for finding and retriving data files from packed 
 *	directory image file.
 */
class PackDir
{
public:

	/// Constructor.
	/**
	 *	Opens a specified packed directory image file. 
	 *	@param name pointer to pack directory image ASCIIZ name. Do not add any extensions to this name.
	 *	@param system valid pointer to System class object.
	 */
	PackDir( const Char * name, System* system );

	/// Destructor.
	/**
	 *	Closes pack directory image file and frees memory occupied by file storage system.
	 */
	~PackDir();

	/// Finds specified file by its ASCIIZ name in this packed directory image.
	/**
	 *	@param name - pointer to file ASCII name. Use only lowercase string. 
	 *	@param log_not_found - if True will write message to sytem log if specified file not found.
	 *	@return index of found specified file. If file not found return -1.
	 */
	Int FindItem( const Char* name, Bool log_not_found = True );

	/// Returns file size. 
	/**
	 *	@param item index of file in pack directory image.
	 *	@return Return file size in bytes. See FindItem() for getting file index.
	 */	
	DWord GetItemSize( Int item );

	/// Loads file content to buffer.
	/**
	 * @param item - index of file in this packed directory image.
	 *	@param buffer - pointer to memory buffer where file data will be loaded. 
	 *			You need allocate enough memory before call this function to store 
	 *			the whole file as it will be loaded at once. See GetItemSize() to 
	 *			determine amount of required buffer size.
	 *	@return True if file loaded successfully otherwise False.
	 */
	Bool LoadItem( Int item, Byte * buffer );

	/// Loads file file content to Resource object.
	/**
	 *	@param item - index of file in packed directory image.
	 *	@param resource - reference to Resource object that will be used to store file content.
	 *	@return True if file loaded successfully otherwise False.
	 */
	Bool LoadItem( Int item, Resource & resource );


	/// Loads file content to Resource object.
	/**
	 *	@param name - name of file.
	 *	@param resource - reference to Resource object where the data will be loaded.
	 *	@return Return True if file loaded successfully otherwise False.
	 */
	Bool LoadFile( const Char * name, Resource & resource );


	/// Returns name for this packed directory image.
	/**
	 *	GetName() returns name for this packed directory image.
	 */
	const string & GetName() const { return name; }

private:

	string name;

	SVector<PackDirFatInfo> packdirfatinfo;

	Int PackDirDatSize;

	void* ziper;

	System* system;

public:

#if defined(MD_OS_PALM)
	void* PackDirHandle;
#endif

#if defined(MD_OS_WINCE) || defined(MD_OS_WIN32)
	Char cinstalldir[256];
	void* PackDirHandle;
#endif

#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)
	void* file_io;
#endif

};

} //namespace mdragon

#endif // __MD_PACKDIR_H__
