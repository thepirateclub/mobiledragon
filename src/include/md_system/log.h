/** \file
 *	Log file support. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_LOG_H__
#define __MD_LOG_H__

namespace mdragon
{

/*! \class Log
 *  \brief Log file.
 *
 *	This class provides log file support. Application can have multiple 
 *	log files. File is placed into application directory.
 */

/// Log file.
/**
 *	Provides support for log files. Files are placed intor application
 *	directory.
 */
class Log
{
public:

	/// Constructor.
	/**
	 *	@param name - Log's file name.
	 *	@param flush - If True, file buffers will be flushed after each write.
	 */
	Log(const Char* name, Bool flush_ = True);


	/// Destructor.
	~Log();
	
	/// Erases log file.
	void Erase();

	/// Writes a string to the log file.
	/**
	 *	@param str - pointer to a ASCIIZ.
	 *	@param size - length of a string, if size < 0, strlen( str ) assumed.
	 */
	void Write( const Char *str );

	/// Equal to Write( str );
	Log & operator << (const Char *str);

	/// Equal to Write( str.c_str() );
	Log & operator << (const string & str);

	/// Dumps memory block content.
	/**
	 *	@param buffer - memory block address.
	 *	@param size - memory block size.
	 */
	void WriteHexDump(const void* buffer, Int size);

	/// Get current log file size.
	Int GetSize();

	/// Flushes log file write buffers.
	void Flush();

private:

#ifndef MD_OS_PALM
	Bool flush;
#endif

#ifdef PSP
	int file;
	String file_name;
#endif

#if defined(MD_OS_WINCE) || defined(MD_OS_WIN32)//!!!
	void* file; //HANDLE
#endif

#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)
	void* fs_session; // RFs
	void* file; //RFile
#endif

#ifdef MD_OS_PALM
	string file_name;
#endif

};

} //namespace mdragon

#endif // __MD_LOG_H__
