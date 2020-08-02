/** \file
 *	Pseudo-random number sequence generator. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_RANDOMIZE_H__
#define __MD_RANDOMIZE_H__

namespace mdragon
{

/// Simple pseudo-random number sequence generator.
class Randomize
{
public:

	/// Default constructor.
	/**
	 *	Initiates random number sequnse based on system tick value.
	 */
	Randomize();

	/// Constructor with given seed value.
	/**
	 * Randomize() class constructor.
	 * @param seed - init generator sequence with initial value seed.
	 */
	Randomize( DWord seed );

	/// Init generator sequence with given seed value.
	/**
	 * @param seed - init generator with given value seed.
	 */
	void Init( DWord seed );

	/// Init generator sequence with value based on system time.
	void Shuffle();


	/// Returns next number in this sequence.
	/**
	 *	@return next number in the sequence.
	 */
	DWord Next();

	/// Equalent to Next().
	/**
	 *	@return next number in the sequence.
	 */
	inline DWord operator() () { return Next(); }

private:
	DWord random;
};

} //namespace mdragon

#endif // __MD_RANDOMIZE_H__
