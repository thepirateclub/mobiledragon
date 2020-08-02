/** \file
 *	Material class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_MATERIAL_H__
#define __MD_MATERIAL_H__

namespace mdragon
{

/// Contains object's material information.
class Material
{
public:
	
	/////////////////////////////COMMON////////////////////////////////////

	/// Default constructor.
	Material();

	/// Destructor.
	~Material();

	/// Equality comparison operator.
	inline Bool operator == ( const Material& material ) const 
	{
		return	diffuse == material.diffuse && 
				specular == material.specular &&
				ambient == material.ambient &&
				emissive == material.emissive &&
				power == material.power &&
				transparency == material.transparency &&
				two_sided == material.two_sided &&
				wireframe == material.wireframe &&
				untextured == material.untextured &&
				diffuse_texture == material.diffuse_texture; 
	}


	//////////////////////////////COLOR////////////////////////////////////

	/// Diffuse multiplier of material color.
	Color diffuse;

	/// Specular multiplier of material color.
	Color specular;

	/// Ambient multiplier of material color.
	Color ambient;

	/// Emissive multiplier of material color.
	Color emissive;

	/// Power multiplier of material color.
	Fixed power;
	
	/// Transparency multiplier of material color.
	Int transparency;
	
	//////////////////////////////TEXTURE//////////////////////////////////

	/// Is material two-sided.
	Bool two_sided;
	
	/// Is this wireframe material.
	Bool wireframe;

	/// Is this material untextured.
	Bool untextured;

	/// Pointer to texture used by material.
	ObjRef<Texture> diffuse_texture;

};

} //namespace mdragon

#endif // __MD_MATERIAL_H__