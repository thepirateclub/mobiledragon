/** \file
 *	Memory managament. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MEMORYMAN_H__
#define __MD_MEMORYMAN_H__

namespace mdragon
{

/// Returns current size of free system memory.
/**
 *	@return current system free memory size.
 */
DWord GetFreeMemory();

} //namespace mdragon

#endif // __MD_MEMORYMAN_H__
