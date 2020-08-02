/** \file
 *	Lightmap class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_LIGHTMAP_H__
#define __MD_LIGHTMAP_H__

namespace mdragon
{

/* Type of Lightmap. */

/// Lightmap from vertex.
#define LightMap_Type_Vertex 1

/// Lightmap from texture.
#define LightMap_Type_Texture 2

/// Lightmap object.
class LightMap : public Texture
{
protected:

	/// Constructor.
	LightMap();

	/// Destructor.
	~LightMap();

public:
	
	/// Create new Lightmap object.
	/**
	 * Call this function instead constructor calling.
	 * @return Returns object reference to new Lightmap object.
	 */
	static ObjRef<LightMap> New()
	{
		return ObjRef<LightMap>( new LightMap );
	}
	
	/// Load lightmap from file.
	/**
	 * @param render_ - pointer to Render3D object.
	 * @param name_ - name of ligthmap file.
	 * @param type_ - type of lightmap.
	 * @return Returns True, if load successful, else - False.
	 */
	Bool Load(Render3D* render_,const Char* name_,Int type_);

	/// Returns type of lightmap object.
	/**
	 * @return Returns type of lightmap object.
	 */
	inline Int GetType() { return type; }


private:

	/// Lightmap type.
	Int type;

	/// Triangle offsets array in the Vertex Lightmap.
	Int* triangle_offset;

	/// Triangle colors array in the Vertex Lightmap.
	Word* triangle_colors;

};

} //namespace mdragon

#endif // __MD_LIGHTMAP_H__