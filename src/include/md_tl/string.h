/** \file
 *	String class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_STRING_H__
#define __MD_STRING_H__
//////////////////////////////////////////////////////////////////////

namespace mdragon
{

/// String class.
class string
{
public:
	typedef Char value_type;
	typedef Char * iterator;
	typedef const Char * const_iterator;
	typedef Char & reference;
	typedef const Char & const_reference;
	typedef Char * pointer;
	typedef Int difference_type;
	typedef size_type size_type;

	///////////////////////////////////////////////////////////////////
	// Constructors & destructor.
	///////////////////////////////////////////////////////////////////


	/// Default constructor. Creates empty string.
	string();

	/// Copy constructor.
	string( const string & src );

	/// Construct from substring.
	/**
	 *	@param src - string to copy from.
	 *	@param pos - position in src to start copy from.
	 *	@param n - max length to copy. if n == npos (src.size() - pos) assumed.
	 */
	string( const string &src, size_type pos, size_type n = npos );

	/// Construct from an array of characters and a length
	/**
	 *	@param src - pointer to the begining of an array.
	 *	@param n - max length to copy. if n == npos, strlen(src) assumed.
	 */
	string( const Char* src, size_type n = npos );

	/// Construct from single character.
	/**
	 *	@param c character to copy.
	 */
	string( Char c );

	/// Construct with n copies of c.
	/**
	 *	@param n - number of copies of c.
	 *	@param c - character to copy.
	 */
	string( size_type n, Char c );


	/// Construct from a range [first, last) of characters.
	/**
	 *	@param first - start of range.
	 *	@param last - past the end of range.
	 */
	template <class InputIterator>
	string( InputIterator first, InputIterator last )
	{
		init();

		assert( last >= first );
		reserve( last - first );
		string_length = last - first;
		buffer[ string_length ] = NULL;
		mdragon::copy( first, last, begin() );
	}

	// construct form other types

	/// Construct string containing string representation of i.
	string( Short i );

	/// Construct string containing string representation of i.
	string( Int i );

	/// Construct string containing string representation of i.
	string( Long i );

	/// Construct string containing string representation of i.
	string( Byte i );

	/// Construct string containing string representation of i.
	string( Word i );

	/// Construct string containing string representation of i.
	string( DWord i );

	/// Construct string containing string representation of i.
	string( Float i );

	/// Construct string containing string representation of i.
	string( Double i );

	/// Destructor.
	~string();


	///////////////////////////////////////////////////////////////////
	// Iterator access.
	///////////////////////////////////////////////////////////////////

	/// Returns an iterator pointing to the first character of the string.
	inline iterator begin() { return buffer; }


	/// Returns iterator pointing past the end of string.
	inline iterator end() { return buffer + string_length; }

	/// Returns a const iterator pointing to the first character of the string.
	inline const_iterator begin() const { return buffer; };

	/// Returns const iterator pointing past the end of string.
	inline const_iterator end() const { return buffer + string_length; }



	/// Returns number of characters in the string.
	inline size_type size() const { return string_length; }

	/// Returns number of characters in the string.
	inline size_type length() const { return string_length; }

	/// Returns size to which the string can grow before memory must be reallocated
	inline size_type capacity() const { return max_len; }

	/// Checks if string is empty.
	inline Bool empty() const { return string_length == 0; }

	/// Returns pointer to the internal storage buffer.
	inline const Char * data() const { return buffer; }

	/// Returns pointer to the internal storage buffer.
	inline const Char * c_str() const { return buffer; }

	/// Changes string capacity to at least n.
	void reserve( size_type n );

	/// Swaps content with another string.
	void swap( string & dst );

	/// Appends or erases characters to make the string's length equal to n.
	void resize( size_type n, Char c = Char() );

	/// Copies a substring of *this to a buffer.
	/**
	 *	@param dst - target buffer for substring.
	 *	@param n - number of characters to copy.
	 *	@param pos - position to begin from.
	 *	@return number of characters being copied.
	 */
	inline size_type copy( Char* dst, size_type n, size_type pos = 0 ) const
	{
		n = min( length() - pos, n );
		mdragon::copy_n( begin() + pos, n, dst );
		return n;
	}

	/// Returns substring of this string.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@return resulting substring.
	 */
	string substr(size_type pos = 0, size_type n = npos ) const
	{
		return string(*this, pos, n);
	}

	//////////////////////////////////////////////////////////////////////////
	// Inserts
	//////////////////////////////////////////////////////////////////////////

	/// Inserts char c at position pos.
	/**
	 *	@param pos - position to insert char c at.
	 *	@param c - char to insert.
	 *	@return position at which c has been inserted.
	 */
	iterator insert( iterator pos, Char c );

	/// Inserts n copies of c at position pos.
	/**
	 *	@param pos - position to insert chars at.
	 *	@param n - number of copies of c to insert.
	 *	@param c - char to insert.
	 */
	void insert( iterator pos, size_type n, Char c );

	/// Inserts characters from range [first, last) at position pos.
	/**
	 *	@param pos - position to insert chars at.
	 *	@param first - iterator to the begining of chars sequence.
	 *	@param last - iterator to the past-the-end of chars sequence.
	 */
	template <class InputIterator>
	void insert(iterator pos, InputIterator first, InputIterator last)
	{
		assert( last >= first );
		
		if( max_len < ( string_length + (size_type)( last - first ) ) )
		{
			size_type temp_pos = pos - begin();
			reserve( string_length + (last - first) );
			pos = begin() + temp_pos;
		}
		mdragon::copy_backward( pos, end(), end() + ( last - first ) );
		mdragon::copy( first, last , pos );
		string_length += ( last - first );
		buffer[ string_length ] = NULL;
	}

	/// Inserts string src at position pos.
	/**
	 *	@param pos - position to insert string at.
	 *	@param src - string to insert.
	 *	@return reference to *this.
	 */
	string & insert( size_type pos, const string & src );

	/// Inserts a substring of src at position pos.
	/**
	 *	@param pos - position to insert string at.
	 *	@param src - source string to insert.
	 *	@param src_pos - starting postion of substring in src.
	 *	@param n - length of substring in src.
	 *	@return reference to *this.
	 */
	string & insert( size_type pos, const string & src, 
			size_type src_pos, size_type n );

	/// Inserts a string at position pos.
	/**
	 *	@param pos - position to insert string at.
	 *	@param src - source string to insert.
	 *	@return position at which src has been inserted.
	 */
	iterator insert( iterator pos, const Char* src );

	/// Inserts a string at position pos.
	/**
	*	@param pos - position to insert string at.
	*	@param src - source string to insert.
	*	@param n - number of charaters to insert.
	*	@return position at which src has been inserted.
	*/
	string & insert( size_type pos, const Char* src, size_type n );


	//////////////////////////////////////////////////////////////////////////
	// Appends
	//////////////////////////////////////////////////////////////////////////

	/// Appends string src at the end.
	string & append( const string & src);

	/// Appends string src at the end.
	/**
	 *	@param src - string to append.
	 *	@param pos - starting position.
	 *	@paran n - number of characters to append.
	 *	@return
	 */
	string & append( const string & src, size_type pos, size_type n );

	/// Appends string src at the end.
	string & append( const Char* src );

	/// Appends n characters c at the end.
	/**
	*	@param n - number of characters to append.
	*	@param c - caharacter value.
	*	@return reference to this.
	*/
	string & append( size_type n, Char c );

	/// Append charaters from range [first, last) at the end.
	template <class InputIterator>
	string & append( InputIterator first, InputIterator last )
	{
		insert( end(), first, last );
		return *this;
	}

	/// Appends single charater at the end.
	inline void push_back( Char c )
	{
		insert( end(), c );
	}


	//////////////////////////////////////////////////////////////////////////
	// Erasers
	//////////////////////////////////////////////////////////////////////////

	/// Erases character at specified position.
	iterator erase( iterator p );

	// Erases ranged of characters.
	iterator erase( iterator first, iterator last );

	/// Erases n characters starting at position pos.
	string & erase( size_type pos = 0, size_type n = npos );

	/// Erases string content.
	string & clear();


	///////////////////////////////////////////////////////////////////
	// Assignment
	///////////////////////////////////////////////////////////////////

	/// Erases content & assigns substring of src to this string.
	/**
	 *	@param src - source string.
	 *	@param pos - starting position of substring in src.
	 *	@param n - substring length. if n == npos, src.size - pos assumed.
	 *	@return reference to *this.
	 */
	string & assign( const string & src, size_type pos = 0, size_type n = npos);


	/// Erases content & assigns array of characters to this string.
	/**
	 *	@param src - pointer to begining of the array.
	 *	@param n - size of array. if n == npos, strlen(src) assumed.
	 *	@return reference to *this.
	 */
	string & assign( const Char* src, size_type n = npos );

	/// Erases content & assigns n copies of c.
	string & assign( size_type n, Char c );

	/// Erases content and appends characters from range [first, last).
	/**
	 *	@param first - iterator pointing to the first character in the sequence.
	 *	@param last - past-the-end sequence iterator.
	 *	@return reference to *this.
	 */
	template <class InputIterator>
	string & assign( InputIterator first, InputIterator last )
	{
		clear();
		return append( first,last );
	}


	///////////////////////////////////////////////////////////////////
	// Replaces
	///////////////////////////////////////////////////////////////////
	
	/// Replace n characters startring at position pos with content of str.
	inline string & replace(size_type pos, size_type n, const string & str)
	{
		erase( pos, n );
		return insert( pos, str );
	}


	/// Replaces substring of *this with substring of str.
	/**
	 *	@param pos - position of substring in *this.
	 *	@param n - length of substring in *this.
	 *	@param s - string to take replacement substring from.
	 *	@param pos1 - position of substring in s.
	 *	@param n1 - length of substring in s.
	 *	@return reference to this.
	 */
	inline string & replace(size_type pos, size_type n, const string & str,
							size_type pos1, size_type n1)
	{
		erase( pos, n );
		return insert( pos, str, pos1, n1 );
	}

	/// Replaces substring of *this with string str.
	/**
	 *	@param pos - position of substring in *this.
	 *	@param n - length of substring in *this.
	 *	@param s - string to take replace with.
	 *	@param n1 - length of string str.
	 *	@return reference to this.
	 */
	inline string & replace(size_type pos, size_type n, const Char* str, size_type n1)
	{
		erase( pos, n );
		return insert( pos, str, n1 );
	}

	/// Replaces substring of *this with str.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@param str - string to replace with
	 *	@return reference to this.
	 */
	inline string & replace(size_type pos, size_type n, const Char* str)
	{
		erase( pos, n );
		return insert( pos, str, strlen(str) );
	}

	/// Replaces substring of *this with n1 characters c.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@param n1 - number of characters to replace with.
	 *	@param c - character to replace with.
	 *	@return reference to this.
	 */
	inline string & replace(size_type pos, size_type n, size_type n1, Char c)
	{
		erase( pos, n );
		insert( begin() + pos, n1, c );
		return *this;
	}

	/// Replaces substring of *this with string str.
	/**
	 *	@param first - starting iterator of substring.
	 *	@param last - past the end substring iterator.
	 *	@param str - string to replace with.
	 *	@return reference to this.
	 */
	inline string & replace(iterator first, iterator last, const string & str)
	{
		erase( first, last );
		return insert( first - begin(), str );
	}

	/// Replaces substring of *this with string str.
	/**
	 *	@param first - starting iterator of substring.
	 *	@param last - past the end substring iterator.
	 *	@param str - string to replace with.
	 *	@param n - length of str.
	 *	@return reference to this.
	 */
	inline string & replace(iterator first, iterator last, const Char* str, size_type n)
	{
		erase( first, last );
		return insert( first - begin(), str, n );
	}

	/// Replaces substring of *this with string str.
	/**
	 *	@param first - starting iterator of substring.
	 *	@param last - past the end substring iterator.
	 *	@param str - string to replace with.
	 *	@return reference to this.
	 */
	inline string & replace(iterator first, iterator last, const Char* str)
	{
		erase( first, last );
		return insert( first - begin(), str, strlen(str) );
	}

	/// Replaces substring of *this with n copies of c.
	/**
	 *	@param first - starting iterator of substring.
	 *	@param last - past the end substring iterator.
	 *	@param n - number of copies of c.
	 *	@param c - character to replace with.
	 *	@return reference to this.
	 */
	inline string & replace(iterator first, iterator last, size_type n, Char c)
	{
		erase( first, last );
		insert( first, n, c );
		return *this;
	}

	/// Replaces substring of *this with character from range [first, last).
	/**
	 *	@param first - starting iterator of substring.
	 *	@param last - past the end substring iterator.
	 *	@param first1 - iterator pointion to the first character in range.
	 *	@param last1 - character range past the end iterator.
	 *	@return reference to this.
	 */
	template <class InputIterator>
	string & replace(iterator first, iterator last,
                      InputIterator first1, InputIterator last1)
	{
		erase( first, last );
		insert( first , first1, last1 );
		return *this;
	}


	//////////////////////////////////////////////////////////////////////////
	// Finds
	//////////////////////////////////////////////////////////////////////////

	/// Searches first occurence of str substring withing this string starting at position pos.
	/**
	 *	@param str - substring to find.
	 *	@param pos - position to start at.
	 *	@return position of first occurence of str or npos.
	 */
	size_type find(const string & str, size_type pos = 0) const;

	/// Searches first occurence of n characters of str as substring of this starting at position pos.
	/**
	 *	@param str - pointer to first charater.
	 *	@param pos - position to being search at.
	 *	@param n - number of characters in str.
	 *	@return position of first occurence of str as substring of this or npos.
	 */
	size_type find(const Char* str, size_type pos, size_type n) const;

	/// Searches first occurence of ASCIIZ string str as substring of this starting at position pos.
	/**
	 *	@param str - pointer to ASCIIZ string.
	 *	@param pos - position to being search at.
	 *	@return position of first occurence of str as substring of this or npos.
	 */
	size_type find(const Char* str, size_type pos = 0) const;

	/// Searches first occurence of character c in this starting at position pos.
	/**
	 *	@param c - charcter to find.
	 *	@param pos - position to being search at.
	 *	@return position of first occurence of c in this or npos.
	 */
	size_type find(const Char c, size_type pos = 0) const;

	/// Searches backward first occurence of str in this starting from min(pos,size()).
	size_type rfind(const string & str, size_type pos = npos) const;

	/// Searches backward first occurence of str in this starting from min(pos,size()).
	size_type rfind(const Char* str, size_type pos = npos) const;

	/// Searches backward first occurence of n characters of str in this starting from min(pos,size()).
	size_type rfind(const Char* str, size_type pos, size_type n) const;

	size_type find_first_of(const string & s, size_type pos = 0) const;
	size_type find_first_of(const Char* s, size_type pos, size_type n) const;
	size_type find_first_of(const Char* s, size_type pos = 0) const;

	size_type find_first_not_of(const string & s, size_type pos = 0) const;
	size_type find_first_not_of(const Char* s, size_type pos, size_type n) const;
	size_type find_first_not_of(const Char* s, size_type pos = 0) const;

	size_type find_last_of(const string & s, size_type pos = npos) const;
	size_type find_last_of(const Char* s, size_type pos, size_type n) const;
	size_type find_last_of(const Char* s, size_type pos = npos) const;

	size_type find_last_not_of(const string & s, size_type pos = npos) const;
	size_type find_last_not_of(const Char* s, size_type pos, size_type n) const;
	size_type find_last_not_of(const Char* s, size_type pos = npos) const;


	///////////////////////////////////////////////////////////////////
	// Comparison
	///////////////////////////////////////////////////////////////////

	/// Returns result of lexicographical comparison with another string.
	/**
	 *	@param str - string to compare.
	 *	@return negative if this string is lexicographically less than str,
	 *			0 if this string is equal to str,
	 *			positive if this string is lexicographically greater than str.
	 */
	inline Int compare(const string & str) const
	{
		return mdragon::lexicographical_compare_3way( begin(), end(),
				str.begin(), str.end() );
	}

	/// Returns result of lexicographical comparison of substring with another string.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@param str - string to compare.
	 *	@return negative if substring is lexicographically less than str,
	 *			0 if substring is equal to str,
	 *			positive if substring is lexicographically greater than str.
	 */
	inline Int compare(size_type pos, size_type n, const string & s) const
	{
		assert( (pos + n) <= length() );
		return mdragon::lexicographical_compare_3way( begin() + pos,
				begin() + pos + n, s.begin(), s.end() );
	}

	/// Returns result of lexicographical comparison of substring with another string substring.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@param str - string to compare.
	 *	@param pos1 - starting length of str.
	 *	@param n1 - length of str.
	 *	@return negative if substring is lexicographically less than str substring,
	 *			0 if substring is equal to str substring,
	 *			positive if substring is lexicographically greater than str substring.
	 */
	inline Int compare(size_type pos, size_type n, const string & s, size_type pos1, 
				size_type n1) const
	{
		assert ( (pos + n) <= length() );
		assert ( (pos1 + n1) <= s.length() );
		return mdragon::lexicographical_compare_3way( begin() + pos, 
				begin() + pos + n, s.begin() + pos1, s.begin() + pos1 + n1 );
	}

	/// Returns result of lexicographical comparison with another string.
	/**
	 *	@param str - string to compare.
	 *	@return negative if this string is lexicographically less than str,
	 *			0 if this string is equal to str,
	 *			positive if this string is lexicographically greater than str.
	 */
	inline Int compare(const Char* s) const
	{
		return mdragon::lexicographical_compare_3way( begin(), end(), s, 
				s + strlen( s ) );
	}


	/// Returns result of lexicographical comparison of substring with another string.
	/**
	 *	@param pos - starting position of substring.
	 *	@param n - length of substring.
	 *	@param str - string to compare.
	 *	@param len - length of str.
	 *	@return negative if substring is lexicographically less than str,
	 *			0 if substring is equal to str,
	 *			positive if substring is lexicographically greater than str.
	 */
	Int compare( size_type pos, size_type n, const Char* str, size_type len = npos ) const;


	//////////////////////////////////////////////////////////////////////////
	// Operators
	//////////////////////////////////////////////////////////////////////////

	/// Returns reference to n'th character.
	inline reference operator[]( size_type n ) { return buffer[n]; }

	/// Returns const reference to n'th character.
	inline const_reference operator[]( size_type n ) const { return buffer[n]; }

	/// Assigns to this content of src.
	string & operator = ( const string & src );

	/// Assigns to this content of src.
	string & operator = ( const Char * src );

	/// Appends content of src at the end.
	inline string & operator += ( const string & src ){ return append(src); }

	/// Appends content of src at the end.
	inline string & operator += ( const Char * src ){ return append(src); }

	/// Appends content of src at the end.
	string & operator << (const string & src );

	/// Appends content of src at the end.
	string & operator << ( const char * src );

	/// Converts all letters to lowercase.
	inline void to_low() { _strlwr(buffer); }

	/// Converst all characters to uppercase.
	inline void to_high() { _strupr(buffer); }

private:

	void init();

	Char *buffer;
	size_type max_len;
	size_type string_length;
	array<Char, 20> inplace_buffer;
};

/// Equality comparison.
/** \relates string */
Bool operator == ( const string & s1, const string & s2 );

/// Equality comparison.
/** \relates string */
Bool operator == ( const Char* s1, const string & s2 );

/// Equality comparison.
/** \relates string */
Bool operator == ( const string & s1, const Char* s2 );

/// Inequality comparison.
/** \relates string */
Bool operator != ( const string & s1, const string & s2 );

/// Inequality comparison.
/** \relates string */
Bool operator != ( const Char* s1, const string & s2 );

/// Inequality comparison.
/** \relates string */
Bool operator != ( const string & s1, const Char* s2 );

/// Lesser than lexicographical comparison.
/** \relates string */
Bool operator < ( const string & s1, const string & s2 );

/// Lesser than lexicographical comparison.
/** \relates string */
Bool operator < ( const Char* s1, const string & s2 );

/// Lesser than lexicographical comparison.
/** \relates string */
Bool operator < ( const string & s1, const Char* s2 );

/// Greater than lexicographical comparison.
/** \relates string */
Bool operator > ( const string & s1, const string & s2 );

/// Greater than lexicographical comparison.
/** \relates string */
Bool operator > ( const Char* s1, const string & s2 );

/// Greater than lexicographical comparison.
/** \relates string */
Bool operator > ( const string & s1, const Char* s2 );

template<> inline
void swap( string & a, string & b )
{
	a.swap(b);
}

} //namespace mdragon

#endif // __MD_STRING_H__
