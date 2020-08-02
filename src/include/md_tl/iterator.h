/** \file
 *	Basic template iterators. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_ITERATOR_H__
#define __MD_ITERATOR_H__

namespace mdragon
{

template <class BackInsertionSequence>
class back_insert_iterator
{
public:
	typedef back_insert_iterator<BackInsertionSequence> self;

	inline back_insert_iterator ( BackInsertionSequence & sequence_ ) :
		sequence(sequence_) { ; }

	inline back_insert_iterator ( self & src ) :
		sequence(src.sequence) { ; }

	inline self & operator = ( const self & src)
	{ sequence = src.sequence; }

	inline self & operator * ()
	{ return *this; }

	inline self & operator = ( 
		const typename BackInsertionSequence::value_type & t )
	{ sequence.push_back( t ); return *this; }

	inline self & operator ++ (){ return *this; }

	inline self & operator ++ ( int) { return *this; }

private:
	BackInsertionSequence & sequence;
};

template<class BackInsertionSequence> inline
back_insert_iterator<BackInsertionSequence>
back_inserter( BackInsertionSequence & sequence )
{
	return back_insert_iterator<BackInsertionSequence>( sequence );
}

template <class T> inline T* value_type( const T* )
{
	return (T*)NULL;
}

} // namespace mdragon

#endif // __MD_ITERATOR_H__
