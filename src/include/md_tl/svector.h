/** \file
 *	SVector class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_S_VECTOR_H__
#define __MD_S_VECTOR_H__

namespace mdragon
{

/// Template vector-like storage with non movable memory.
/**
 *	Memory allocated for stored objects never reallocates, so
 *	pointers to stored object are valid until svector is cleared.
 *	@param T type of stored objects.
 */
template <class T>
class SVector
{
public:

	/// Constructor.
	/**
	 *	@param increment_power_of_two - data block size power of two.
	 */
	SVector(Int increment_power_of_two = 8);

	/// Destructor.
	~SVector();

	/// Destroys stored objects & releases memory.
	void Clear();

	/// Returns number of elements.
	Int Size();

	/// Resizes vector to hold size elements.
	void Resize( Int size );

	/// Returns reference to element at specified index.
	const T& ElementAt(Int index) const;
	
	/// Returns reference to element at specified index.
	T& ElementAt(Int index);

	/// Returns reference to element at specified index.
	const T& operator [](Int index) const;

	/// Returns reference to element at specified index.
	T& operator [](Int index);

	/// Adds element at the end of SVector.
	void Add( const T & t );

	/// Return index of element in SVector, -1 if there is no match
	Int IndexOf( const T & element ) const;


private:
	Int size;

	Int increment;

	vector<T*> blocks;

	Int offset_mask;
	
	Int increment_power_of_two;
	
};


template<class T>
SVector<T>::SVector(Int increment_power_of_two_)
{
	size = 0;
	increment_power_of_two = increment_power_of_two_;
	increment = 1 << increment_power_of_two;
	offset_mask = increment - 1;
	T* new_block = new T[increment];
	blocks.push_back(new_block);
}


template<class T>
void SVector<T>::Clear()
{
	for (size_type i = 0; i < blocks.size(); i++)
		delete [] blocks[i];
	
	blocks.clear();
	size = 0;
}


template<class T>
SVector<T>::~SVector()
{
	Clear();
}


template<class T>
int SVector<T>::Size()
{
	return size;
}


template<class T>
void SVector<T>::Resize(Int size_)
{
	Int blocks_need = (size_ >> increment_power_of_two) + 
		((size_ & offset_mask) ? 1 : 0);

	for(Int i = blocks.size(); i < blocks_need; i++)
	{
		T* new_block = new T[increment];
		blocks.push_back(new_block);
	}
	
	size = size_;
}


template<class T>
inline const T& SVector<T>::ElementAt(Int index) const
{
	Int block = index >> increment_power_of_two;
	Int offset = index & offset_mask;
	
	return blocks[block] [offset];	
}


template<class T>
inline T& SVector<T>::ElementAt(Int index)
{
	Int block = index >> increment_power_of_two;
	Int offset = index & offset_mask;
	
	return blocks[block] [offset];
}


template<class T>
inline const T& SVector<T>::operator [](Int index) const
{
	return ElementAt(index);
}


template<class T>
inline T& SVector<T>::operator [](Int index)
{
	return ElementAt(index);
}


template<class T>
void SVector<T>::Add(const T& x)
{
	Int index = size;
	Resize(size + 1);
	Int block = index >> increment_power_of_two;
	Int offset = index & offset_mask;
	blocks[block][offset] = x;
}


template<class T>
Int SVector<T>::IndexOf(const T & element) const
{
	for(Int i = 0; i < Size(); ++i)
	{
		if(ElementAt(i) == element)
			return i;
	}
	return -1;
}

} //namespace mdragon

#endif //__MD_S_VECTOR_H__
