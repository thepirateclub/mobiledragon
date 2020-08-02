/** \file
 *	2d sprite animation. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ANIMATION_H__
#define __MD_ANIMATION_H__

namespace mdragon
{

/// Animation represents 2d sprite animation storage class.
class Animation
{
public:

	/// Animation class constructor.
	Animation();

	/// Animation class destructor.
	/**
	 * Free all memory used to store sprite animation data. Please note any sprite transform frames will be not deleted.
	 */
	 ~Animation();

	/// Exports animation from current node of GameData class object.
	/**
	 * @param gd pointer to GameData class object.
	 * @param st_table pointer to SVector class object. All exported SpriteTransform class objects will be created in this unmovable vector. Animation class object will be store only pointers on it.
	 * @param cd_table pointer to SVector class object. All exported CustomData class objects will be created in this unmovable vector.
	 * @param tokens pointer to ASCII names identifications for CustomData class objects tokens.
	 * @return Return True if export success else False.
	 */
	Bool ExportNode( GameData* gd, SVector<SpriteTransform>* st_table, SVector<CustomData>* cd_table, Char** tokens );

	/// Find specified animation by ASCII name.
	/**
	 * @param name_ pointer to ASCII name for specified animation .
	 * @return Return pointer to array of SpriteTransform class objects if find complete successfully else NULL pointer.
	 */
	SpriteTransform** Find( const Char* ani_name );

private:

	vector<SpriteTransform*> frames;

};


} //namespace mdragon

#endif // __MD_ANIMATION_H__