/** \file
 *	3d font class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_FONT3D_H__
#define __MD_FONT3D_H__

namespace mdragon
{

/// 3d font created from one texture.
class Font3D
{
public:

	/// Default constructor.
	Font3D();

	/// Destructor.
	~Font3D();

	/// Creates 3d font object from specified texture.
	/**
	 * Need to call before any 3d font drawing operations.
	 * After this any new calls of Create() are not allowed.
	 * @param render - pointer to Render3D class object.
	 * @param name - pointer to ASCII name for specified font texture.
	 */	 
	void Create(Render3D* render, const Char* name);

	/// Frees all memory used to store 3d font.
	/**
	 * However this function don't delete 3d font object. 
	 * You can call Create() function to create new 3d font.
	 */
	void Free();
		  
	/// Send 3d font text to draw queue.
	/**
	 * @param text string Char buffer with 0-termenated byte in the end of string.
	 * @param v pointer to Vector3fx point from where 3d text start in model coordinates.
	 * @param size pointer to Vector3fx point that specify size of 3d font.
	 * @param color define 3d text font color. See class Color.
	 * @param dir define 3d text direction. 1 for horizontal drawing, 0 for vertical.
	 * @return Returns Vector3fx point that specify full size of drawing 3d text.
	 */
	Vector3fx Draw(const Char* text,Vector3fx* v,Vector3fx* size,Int color,Int dir=1);

	/// Returns Vector3fx point that specify full size of 3d text.
	/**
	 * @param text string Char buffer with 0-termenated byte in the end of string.
	 * @param v pointer to Vector3fx point from where 3d text start in model coordinates.
	 * @param size pointer to Vector3fx point that specify size of 3d font.
	 * @param dir define 3d text direction. 1 for horizontal drawing, 0 for vertical.
	 * @return Returns Vector3fx point that specify full size of drawing 3d text.
	 */
	Vector3fx GetSize(const Char* text,Vector3fx* v,Vector3fx* size,Int dir);

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }

private:

	/// Font's VertexBuffer.
	ObjRef<VertexBuffer> vb;

	/// Font's material.
	Material material;

	/// Font's name.
	string name;

	/// Texture size.
	Short texture_size;

	/// First char index.
	Short first_char;

	/// Last char index.
	Short last_char;

	Fixed* uv01;

	Render3D* render;
};

} //namespace mdragon

#endif // __MD_FONT3D_H__
