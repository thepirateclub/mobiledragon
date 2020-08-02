/** \file
 *	2d tile map class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_TILEMAP_H__
#define __MD_TILEMAP_H__

namespace mdragon
{

/// 2d tile map class.
/**
 *	This class used to store 2d indexed tile map.
 */
class TileMap
{
public:

	/// Constructor.
	TileMap();

	/// TileMap class destructor.
	~TileMap();

	/// Performs the complete initialization of tile map class object. 
	/**
	 * This function must be called before any operations on TileMap class object.
	 * @param name pointer to ASCII tile map name.
	 * @param palette_name pointer to ASCII tile map palette name.
	 * @param x_ define x value for upper-left corner coordinate of tile map on global screen map.
	 * @param y_ define y value for upper-left corner coordinate of tile map on global screen map.
	 * @param x_size_ define tile width.
	 * @param y_size_ define tile height.
	 * @param x_div_ define tile map columns count.
	 * @param y_div_ define tile map rows count.
	 * @return Return True if tile map init complete successfully else False.
	 */	
	Bool Init( const Char* name, const Char* palette_name, Short x_, Short y_, Short x_size_, Short y_size_, Int x_div_, Int y_div_ );

	/// Set new tile size.
	/**
	 * @param x_size_ define tile width.
	 * @param y_size_ define tile height.
	 */	
	void SetCellSize( Short x_size_, Short y_size_ );

	/// Get tile column and row by specified x and y coordinates.
	/**
	 * @param xp define x value of specified coordinates.
	 * @param yp define y value of specified coordinates.
	 * @param X store tile column for specified coordinates.
	 * @param Y store tile row for specified coordinates.
	 */	
	void GetCellXY( Short xp, Short yp, Int& X, Int& Y );

	/// Get tiles columns and rows by specified border rectangle.
	/**
	 * @param border specified border rectangle.
	 * @param sX store tile upper-left corner column for specified border rectangle.
	 * @param sY store tile upper-left corner row for specified border rectangle.
	 * @param eX store tile lower-right corner column for specified border rectangle.
	 * @param eY store tile lower-right corner row for specified border rectangle.
	 */	
	void GetCellXY( const Rect& border, Int& sX, Int& sY, Int& eX, Int& eY );

	/// Get tile column and row by specified x and y coordinates without clipping. 
	/**
	 * Can provide with negative values for column and row.
	 * @param xp define x value of specified coordinates.
	 * @param yp define y value of specified coordinates.
	 * @param X store tile column for specified coordinates.
	 * @param Y store tile row for specified coordinates.
	 */	
	void GetCellXYNoClip( Short xp, Short yp, Int& X, Int& Y );

	/// Return pointer to SpriteTransform class object from palette for specified column and row.
	/**
	 * @return Return pointer to SpriteTransform class object from palette 
	 *         for specified column and row. Return NULL for empty tile 
	 *         ( with negative index to palette ).
	 */
	SpriteTransform* GetTile( Int X, Int Y );

	/// Return tile index in palette for specified column and row.
	/**
	 * @param X specified tile column.
	 * @param Y specified tile row.
	 * @return Return tile index in palette or -1 or any negative value empty tile.
	 */
	inline Int GetCellTileIndex( Int x, Int y ) { return map[y*x_div + x]; }

	/// Get tile map position on global screen map.
	/**
	 * Default value is (0,0).
	 * @param x_ pointer to store tile map x upper-left corner position on global screen map.
	 * @param y_ pointer to store tile map y upper-left corner position on global screen map.
	 */
	void GetStart( Short* x, Short* y )
	{
		*x = this->x;
		*y = this->y;
	}

	/// Get tile size.
	/**
	 *	@param x_s pointer to store tile width.
	 *	@param y_s pointer to store tile height.
	 */
	void GetSize( Short* x_s, Short* y_s )
	{
		*x_s = x_size;
		*y_s = y_size;
	}

	/// Return tile map columns count.
	/**
	 *	@return Return tile map columns count.
	 */
	Int GetXDiv() { return x_div; }

	/// Return tile map rows count.
	/**
	 *	@return Return tile map rows count.
	 */
	Int GetYDiv() { return y_div; }

	/// Return tile map bounding box Rect on global screen map.
	/**
	 *	@return Return tile map bounding box Rect on global screen map.
	 */
	const Rect& GetBorder() const
	{
		return border;
	}

	/// Return pointer to tile map palette.
	/**
	 *	@return Return pointer to tile map palette.
	 */
	vector<SpriteTransform*>* GetPalette() { return palette; }

	/// Set pointer to tile map palette.
	/**
	 * @param palette_ pointer to tile map palette as a vector class object 
	 *        that store pointers to SpriteTransform class objects. 
	 *        Tile map index 0 point to first element of this vector, index 
	 *        1 point to the next element and and so on.
	 */
	void SetPalette(vector<SpriteTransform*>* palette_) { palette = palette_; }

	/// Return tile map name.
	/**
	 * @return Return tile map name.
	 */
	const string & GetName() const { return name; }

	/// Return tile map palette name.
	/**
	 * @return Return tile map palette name.
	 */
	const string & GetPaletteName() const { return palette_name; }

	/// Return base z order for tile map.
	/**
	 * @return Return base z order for tile map.
	 */
	Int GetZOrder()
	{
		return z_order;
	}

	/// Set new base z order for tile map.
	/**
	 * @param z_order_ define new base z order for sprite.
	 */
	void SetZOrder(Int z_order_)
	{
		z_order = z_order_;
	}

	friend class GameData;

private:

	Int z_order;

	string name;
	string palette_name;

	vector<SpriteTransform*>* palette;

	Short* map;

	Short x,y;
	Short x_size,y_size;
	Int x_div,y_div;

	Rect border;
};


} //namespace mdragon

#endif // __MD_TILEMAP_H__