/** \file
 *	Input management. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_INPUT_H__
#define __MD_INPUT_H__

namespace mdragon
{

typedef struct
{
  Byte KeyPressed[256]; /* !< 1 if key[n] pressed, else 0 */
} TKeyboard;




/* Key codes. Used with KeyPressed() and KeyDown() functions. */

#define KEY_NONE 0
#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_UP 3
#define KEY_DOWN 4
#define KEY_FIRE 5
#define KEY_A 6
#define KEY_B 7



/// Provides support for input devices.
/**
 *	You don't have to create instances of this by yourself, use
 *	input member of System class instance instead.
 */
class Input
{

public:

	void Update(TKeyboard* keyboard_, Short* pen_x_, Short* pen_y_, Bool* pen_down_);

	/// Checks if specified keyboard key was pressed since last update.
	Bool KeyPressed(Int key);

	/// Checks if specified keyboard key is down.
	Bool KeyDown(Int key);
	
	/// Check if stylus is down.
	Bool PenDown();

	/// Check if stylus was clicked since last update.
	Bool PenClicked();

	/// Get state of stylus.
	/**
	 *	@param x - pointer to variable to store pen x coordinate.
	 *	@param y - pointer to variable to store pen y coordinate.
	 *	@return True if pen is down, False otherwise.
	 */
	Bool PenState(Short* x, Short* y);

	/// Clears input key & pend down/pressed states.
	void Clear();
	
	Int key_commands[256];
private:

	Input();

	Bool key_pressed[256];
	Bool key_down[256];

	TKeyboard keyboard;


	TKeyboard old_keyboard;

	Bool pen_down;
	Bool old_pen_down;
	Short pen_x, pen_y;

	Bool need_clear_pen;

	friend class System;

};


} //namespace mdragon

#endif // __MD_INPUT_H__
