/** \file
 *	Binary resource in memory. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_RESOURCE_H__
#define __MD_RESOURCE_H__

namespace mdragon
{

/// Binary resource in memory.
class Resource
{

public:

	/// Default constructor.
	Resource();


	/// Destructor.
	~Resource();


	/// Return pointer to memory resource data buffer.
	/**
	 * GetData() return pointer to memory resource data buffer.
	 */
	Byte* GetData();


	/// Resizes memory resource data buffer.
	/**
	 * @param n - new size for memory resource data buffer.
	 */
	void Resize( Int n );


	/// Clears content of this resource object.
	/**
	 *	Also sets current read/write position to 0.
	 */
	void Clear();


	/// Return size of this memory resource data buffer.
	Int Size();


	/// Returns current read/write position.
	inline Int GetPosition()
	{
		return position;
	}


	/// Move resource read/write position further by specified value.
	/**
	 *	@param skip - number of bytes to move resource read/write position.
	 *	@return new resource read/write position.
	 */
	Int Skip( Int skip );


	/// Sets resource read/write position.
	/**
	 *	@param position - define new resource read/write position.
	 *	@return old resource read/write position.
	 */
	Int SetPosition( Int position );


	/// Read one POD object from memory resource into specified buffer.
	/**
	 *	@param d - pointer to Data object specified by template class Data.
	 *	@return True if read complete successfully else False.
	 */	
	template <class POD> 
	Bool Read( POD* d )
	{
		Int data_size = sizeof( POD );

		if( position + data_size <= Size() )
		{
			memcpy( d, &resource[position], data_size );
			position += data_size;
			return True;
		}

		return False;
	}


	/// Read specified number of POD objects from memory resource data buffer.
	/**
	 *	@param d - pointer to POD objects array specified by template class Data.
	 *	@param size -  number of POD objects to read.
	 *	@return True if read complete successfully else False.
	 */
	template <class POD> 
	Bool Read( POD* d, Int size )
	{
		Int data_size = sizeof( POD );

		if( position + data_size*size <= Size() )
		{
			for( Int i = 0; i < size; i++, d++, position += data_size )
				memcpy( d, &resource[position], data_size );

			return True;
		}

		return False;
	}


	/// Reads specified number of characters from memory resource to specified buffer.
	/**
	 *	@param d - pointer to Char symbols array.
	 *	@param size - define Char symbols array size.
	 *	@return True if read complete successfully else False.
	 */
	Bool Read( Char* d, Int size )
	{
		if( position + size <= Size() )
		{
			memcpy( d, &resource[position], size );
			position += size;
			return True;
		}
		return False;
	}


	/// Read specified number number of bytes from memory resource to specified buffer. 
	/**
	 *	@param d - pointer to buffer.
	 *	@param size - define bytes array size.
	 *	@return True if read complete successfully else False.
	 */
	Bool Read( Byte* d, Int size )
	{
		if( position + size <= Size() )
		{
			memcpy( d, &resource[position], size );
			position+=size;
			return True;
		}
		return False;
	}	


	/// Read string from memory resource to buffer.
	/**
	 *	ReadString() read string from memory resource data buffer.
	 *	@param string - object.
	 *	@return True if read complete successfully else False.
	 */
	Bool ReadString( string & s );


	/// Read string from memory resource to buffer.
	/**
	 *	ReadString() read string from memory resource data buffer.
	 *	@param s - destinaton buffer.
	 *	@param max_len - max string length.
	 *	@return True if read complete successfully else False.
	 */
	Bool ReadString( Char* s, Int max_len );


	/// Writes POD object to memory resource.
	/**
	 *	@param d - pointer to Data object specified by template class Data.
	 *	@return True if write complete successfully else False.
	 */
	template <class POD> 
	Bool Write( const POD* d )
	{
		Int data_size = sizeof(POD);

		if( position + data_size > Size() )
			resource.resize( position + data_size );

		memcpy( &resource[position], d, data_size );

		position += data_size;
		return True;
	}


	/// Writes POD objects to memory resource.
	/**
	 *	@param d - pointer to POD objects array specified by template class Data.
	 *	@param size - number of POD objects to write.
	 *	@return True if write complete successfully else False.
	 */
	template <class POD> 
	Bool Write( const POD* d, Int size )
	{
		Int data_size = sizeof(POD);

		if(position + data_size * size > Size() )
			resource.Resize( position + data_size * size );

		for( Int i = 0; i < size; i++, d++, position += data_size )
			memcpy( &resource[position], d, data_size );

		return True;
	}

	/// Writes specified number of symbols to memory resource.
	/**
	 *	@param d - pointer to Char array.
	 *	@param size - number of chararcters symbols to write.
	 *	@return True if write complete successfully else False.
	 */
	Bool Write( const Char* d, Int size )
	{
		if( position + size > Size() )
			resource.resize( position + size );
		memcpy( &resource[position], d, size );
		position += size;
		return True;
	}

	/// Writes specified number of bytes to memory resource.
	/**
	 *	@param d - pointer to Byte array.
	 *	@param size - number of bytes to write.
	 *	@return True if write complete successfully else False.
	 */
	Bool Write( const Byte* d, Int size )
	{
		if( position + size > Size() )
			resource.resize( position + size );
		memcpy( &resource[position], d, size );
		position += size;
		return True;
	}

	/// Writes string to memory resource.
	/**
	 *	@param str - pointer to ASCIIZ string.
	 *	@return True if write complete successfully else False.
	 */
	Bool WriteString( const Char* str );

	/// Writes string to memory resource.
	/**
	 *	@param str - string to write.
	 *	@return True if write complete successfully else False.
	 */
	Bool WriteString( const string & str );

	/// Reads one Float object from memory resource data buffer.
	/**
	 *	@param d - pointer to Float object.
	 *	@return True if read complete successfully else False.
	 */
	Bool ReadFloat( Float* d )
	{
		Int data_size = 4;

		if( position + data_size <= Size() )
		{
			Int fixed;
			memcpy( &fixed, &resource[position], data_size );

			*d = Float(fixed) / 65536;

			position += data_size;
			return True;
		}

		return False;
	}

#ifdef Fixed

	Bool Read( Fixed* d )
	{
		return ReadFloat(d);
	}

	Bool Read( Fixed* d, Int size )
	{
		Int data_size = 4;

		if( position + data_size * size <= Size() )
		{
			for( Int i = 0; i < size; i++ )
				ReadFloat( &d[i] );

			return True;
		}

		return False;
	}

#endif

	/// Assigns to this copy of another Resource object.
	/**
	 *	@param src - Resource object to copy from.
	 *	@return this Resource object.
	 */
	Resource & operator = ( const Resource & src );


	friend class PackDir;
	friend class System;

	friend Bool SaveTGA(const Char *filename,Int width,Int height,DWord* pixels);

protected:

	Bool LoadFlashData(const Char* name_);
	void SaveFlashData(const Char* name_);

	Bool Load(const Char* name_);
	void Save(const Char* name_);

private:

	vector<Byte> resource;

	Int position;

	string name;
};

#if defined(MD_OS_SYMBIAN_S60) || defined(MD_OS_SYMBIAN_UIQ)

template <class T>
inline void XAddTChar(T& x, const Char* str)
{
	while(*str)
	{
		x.Append((TChar)(*str));
		str++;
	}
}

#endif

} //namespace mdragon


#if defined(MD_OS_PALM)
unsigned long PDBFileSize(void* pdbfile);
void PDBFileSetOffset(void* vpdbfile,unsigned long offset);
unsigned long PDBFileGetOffset(void* vpdbfile);
void* PDBFileOpen(const char *name);
void PDBFileClose(void* vpdbfile);
unsigned long PDBFileRead( void* vpdbfile, unsigned char *buf, unsigned long size );
unsigned long PDBFileWrite( void* vpdbfile, unsigned char *buf, unsigned long size );
#endif


#endif // __MD_RESOURCE_H__

