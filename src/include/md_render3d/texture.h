/** \file
 *	Texture class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TEXTURE_H__
#define __MD_TEXTURE_H__

namespace mdragon
{

class Render3D;

class Triangle;

struct KeyFrame;

/// Texture class.
class Texture : public Object
{	
protected:

	/// Default constructor.
	Texture();

	/// Destructor.
	~Texture();

public:

	/// Creates new Texture object.
	/**
	 *	Call this function instead constructor calling.
	 *  @return Returns object reference to new Texture object.
	 */
	static ObjRef<Texture> New()
	{
		return ObjRef<Texture>( new Texture );
	}

	/// Loads texture from file.
	/**
	 *  @param render_ - pointer to Render3D object.
	 *	@param name_ - name of texture file.
	 *  @return Returns True, if load successful, else - False.
	 */
	virtual Bool Load(Render3D* render_,const Char* name_);

	/// Returns texture width.
	/**
	 *  @return Returns texture width.
	 */
	inline Int GetWidth() { return width; }

	/// Returns texture height.
	/**
	 *  @return Returns texture height.
	 */
	inline Int GetHeight() { return height; }

	/// Returns name of texture.
	/**
	 *  @return Returns name of texture.
	 */
	inline const string & GetName() const { return name; }

	/// Returns pointer to Render3D object.
	/**
	 * @return Returns pointer to Render3D object.
	 */
	inline Render3D* GetRender() { return render; }



	friend class LightMap;
	friend class Render3D;

private:

	/// Pointer to Render3D object.
	Render3D* render;

	/// Pixel array.
	Pixel* pixels;

	/// Texture Width.
	Int width;
	
	/// Texture Height.
	Int height;

	/// Texture name.
	string name;

	/// Using transparency color key.
	Int color_key; 

	/// For internal optimization.
  	DWord width_mask, height_mask;

#ifdef MD_OS_PALM
	Word featureNum;
#endif	

};


} //namespace mdragon

#endif // __MD_TEXTURE_H__