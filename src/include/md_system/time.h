/** \file
 *	Time functions. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TIME_H__
#define __MD_TIME_H__

namespace mdragon
{

/**
 *	GetTime() returns current system time.
 *	@param hours pointer to Word receiving current hours value.
 *	@param minutes pointer to Word receiving current minutes value.
 *	@param seconds pointer to Word receiving current day of seconds value.
 */
void GetTime(Word* hours, Word* minutes, Word* seconds);


/**
 *	GetDate() returns current system date.
 *	@param year pointer to Word receiving current year value.
 *	@param month pointer to Word receiving current month value.
 *	@param day pointer to Word receiving current day of month value.
 */
void GetDate(Word* year, Word* month, Word* day);

/**
 *	GetSystemTickCount() returns current system ticks.
 *	@return current system ticks in miliseconds.
 */
DWord GetSystemTickCount();

} //namespace mdragon

#endif // __MD_TIME_H__
