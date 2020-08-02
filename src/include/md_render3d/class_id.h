/** \file
 *	List of class ID's. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_CLASS_ID_H__
#define __MD_CLASS_ID_H__

namespace mdragon
{

/**
 *  List of Class ID's
 */

// Class ID for unknown class
#define ClassID_Unknown 0

// Class ID for rendered classes
#define ClassID_Basic3D (ClassID_Unknown+1)
#define ClassID_Object3D (ClassID_Basic3D+1)
#define ClassID_Light (ClassID_Object3D+1)
#define ClassID_Robot3D (ClassID_Light+1)
#define ClassID_Actor3D (ClassID_Robot3D+1)
#define ClassID_Actor3DNode (ClassID_Actor3D+1)
#define ClassID_Joint3D (ClassID_Actor3DNode+1)
#define ClassID_Joint3DNode (ClassID_Joint3D+1)

// Class ID for dummy classes
#define ClassID_DummyBox (ClassID_Joint3DNode+1)
#define ClassID_DummySphere (ClassID_DummyBox+1)

// Class ID for 3D sprite class
#define ClassID_Sprite3D (ClassID_DummySphere+1)

} //namespace mdragon

#endif // __MD_CLASS_ID_H__