/** \file
 *	SpriteTransformMap class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_STMAP_H__
#define __MD_STMAP_H__

namespace mdragon
{


class SpriteTransformMap
{
public:

	SpriteTransformMap();
	~SpriteTransformMap();

	Bool Init( const Char* name_, Short x_, Short y_, Short x_size_, Short y_size_, Int x_div_, Int y_div_ );


	inline void GetCellXY( Short xp, Short yp, Int& X, Int& Y );
	inline void GetCellXY( const Rect& border, Int& sX, Int& sY, Int& eX, Int& eY );


	inline void GetCellXYNoClip( Short xp, Short yp, Int& X, Int& Y );


	inline vector<SpriteTransform*>* GetCell( Int X, Int Y ) { return &cell[ Y*x_div + X ]; }


	inline void Add( SpriteTransform* st );
	inline void Remove( SpriteTransform* st );


	inline void BeginCollide( vector<SpriteTransform*>* found );
	inline void Collide( vector<SpriteTransform*>* found, const Rect& border );
	inline void EndCollide( vector<SpriteTransform*>* found );


	void GetStart( Short* x_, Short* y_ )
	{
		*x_ = x;
		*y_ = y;
	}

	void GetSize( Short* x_s, Short* y_s )
	{
		*x_s = x_size;
		*y_s = y_size;
	}

	Int GetXDiv() { return x_div; }
	Int GetYDiv() { return y_div; }

	const Rect& GetBorder() const
	{
		return border;
	}

	const string& GetName() const { return name; }

private:

	string name;

	vector<SpriteTransform*> *cell;

	Short x,y;
	Short x_size,y_size;
	Int x_div,y_div;

	Rect border;

};


} //namespace mdragon

#endif // __MD_STMAP_H__