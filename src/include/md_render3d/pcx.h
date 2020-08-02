/** \file
 *	PCX loading. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_PCX_H__
#define __MD_PCX_H__

namespace mdragon
{

/// Loads PCX image from file.
/**
 * @param system - pointer to the System class object.
 * @param FileName - image file name.
 * @param SizeX - pointer to the buffer to store image width.
 * @param SizeY - pointer to the buffer to store image height.
 * @param Pixels - pointer to the buffer to store image data.
 * @param ColorKey - pointer to the buffer to store ColorKey value (transparent color).
 * @param y_inverse - specified if image must read with inverse by vertical.
 * @param use_pool - specified if image loading must use pool.
 * @return Returns 1 (True), if loading is successfully, else - 0 (False).
 */
Int LoadPCX(System *system,const Char *FileName, Int *SizeX, Int *SizeY, Word **Pixels, Int* ColorKey, Int y_inverse, Int use_pool);

/// Loads PCX image from file.
/**
 * @param system - pointer to the System class object.
 * @param FileName - image file name.
 * @param SizeX - pointer to the buffer to store image width.
 * @param SizeY - pointer to the buffer to store image height.
 * @param Pixels - pointer to the buffer to store image data.
 * @param ColorKey - pointer to the buffer to store ColorKey value (transparent color).
 * @param y_inverse - specified if image must read with inverse by vertical.
 * @param use_pool - specified if image loading must use pool.
 * @return Returns 1 (True), if loading is successfully, else - 0 (False).
 */
Int LoadPCXRGB(System *system,const Char *FileName, Int *SizeX, Int *SizeY, Byte **Pixels, Int* ColorKey, Int y_inverse, Int use_pool );

} //namespace mdragon

#endif // __MD_PCX_H__