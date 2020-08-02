/** \file
 *	MobileDragon main include file. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */
 
#ifndef __MOBILE_DRAGON__
#define __MOBILE_DRAGON__

#if !defined(MD_OS_WIN32) && !defined(MD_OS_WINCE) && !defined(MD_OS_SYMBIAN_S60) && !defined(MD_OS_SYMBIAN_UIQ)
#define MD_OS_PALM
#endif

#include "md_core/types.h"
#include "md_core/memory.h"

#include "md_tl/mtl.h"
#include "md_tl/mtlmemory.h"
#include "md_tl/function.h"
#include "md_tl/utility.h"
#include "md_tl/iterator.h"
#include "md_tl/algorithm.h"
#include "md_tl/sort.h"
#include "md_tl/array.h"
#include "md_tl/vector.h"
#include "md_tl/string.h"
#include "md_tl/vector.h"
#include "md_tl/svector.h"

#include "md_core/fixed.h"
#include "md_core/mdfixedmath.h"
#include "md_core/vecmath.h"
#include "md_core/randomize.h"
#include "md_core/resource.h"
#include "md_core/packdir.h"
#include "md_core/object.h"

#include "md_bluetooth/bluetooth.h"
#include "md_bluetooth/ibtconnection.h"
#include "md_bluetooth/btnetwork.h"

#include "md_sound/Music.h"
#include "md_sound/Sound.h"
#include "md_sound/SoundSystem.h"

#include "md_system/log.h"
#include "md_system/time.h"
#include "md_system/memoryman.h"
#include "md_system/input.h"
#include "md_system/system.h"

#include "md_render3d/class_id.h"
#include "md_render3d/color.h"
#include "md_render3d/collision.h"
#include "md_render3d/polyclip.h"
#include "md_render3d/texture.h"
#include "md_render3d/texture_actor.h"
#include "md_render3d/lightmap.h"
#include "md_render3d/vertexbuffer.h"
#include "md_render3d/material.h"
#include "md_render3d/basic3d.h"
#include "md_render3d/light.h"
#include "md_render3d/object3d.h"
#include "md_render3d/robot3d.h"
#include "md_render3d/joint3d.h"
#include "md_render3d/actor3d.h"
#include "md_render3d/dummy.h"
#include "md_render3d/sprite3D.h"
#include "md_render3d/portal.h"
#include "md_render3d/mdmload.h"
#include "md_render3d/font3d.h"
#include "md_render3d/triangle.h"
#include "md_render3d/software3d.h"
#include "md_render3d/render3d.h"
#include "md_render3d/pcx.h"
#include "md_render3d/camera.h"
#include "md_render3d/particles.h"

#include "md_render2d/image.h"
#include "md_render2d/sprite2d.h"
#include "md_render2d/gamedata.h"
#include "md_render2d/stransform.h"
#include "md_render2d/stmap.h"
#include "md_render2d/tilemap.h"
#include "md_render2d/font2d.h"
#include "md_render2d/animation.h"
#include "md_render2d/actor2d.h"
#include "md_render2d/software2d.h"
#include "md_render2d/render2d.h"

#include "md_core/mdgame.h"

#endif // __MOBILE_DRAGON__
