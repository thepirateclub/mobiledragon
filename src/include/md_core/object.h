/** \file
 *	Base class for Objects that require reference - counting. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_OBJECT_H__ 
#define __MD_OBJECT_H__ 

namespace mdragon
{

/// Base class for Objects that require reference - counting.
/**
 *	Use as base class for your objects if you want to use
 *	smart pointer ObjRef<T>.
 */
class Object
{
public:

	/// Constructor.
	Object()
	{ n_references = 0; }

	/// Destructor.
	virtual ~Object() { ; }

	/// Increments object reference counter.
	void AddRef(){ ++n_references; }

	/// Decrements reference counter. 
	/**
	 *	If reference counter drops to zero, delete this object.
	 */
	void Release()
	{  
		if( --n_references == 0 )
			delete this;
	};

	/// Returns this object reference counter value.
	inline DWord GetRefCount() { return n_references; }

private:
	DWord n_references;
};


/// SmartPointer for Object<T> - derived classes.
template<class T>
class ObjRef
{
public:

	/// Default constructor.
	/**
	 *	ObjRef() default contructor.
	 */
	inline ObjRef() { p_object = NULL; }


	/// Copy constructor.
	/**
	 *	Increases objects' reference counter.
	 *	@param src reference of object to copy.
	 */
	inline ObjRef( const ObjRef<T> & src )
	{
		p_object = src.p_object;
		if( p_object )
			p_object->AddRef();
	}


	/// Construct from plain pointer.
	/**
	 *	ObjRef() constructor from plain pointer.
	 *	@param p_object - pointer to object or NULL.
	 */
	inline ObjRef( T * p_object )
	{
		this->p_object = p_object;
		if( p_object )
			p_object->AddRef();
	}


	/// Destructor. Calls Release() on owned Object.
	inline ~ObjRef()
	{
		if( p_object )
			p_object->Release();
	}


	/// Assignment operator.
	/**
	 *	Makes this a copy of src, increasing owned object reference counter.
	 *	@param src - object to  copy.
	 *	@return reference to this.
	 */
	ObjRef & operator = ( const ObjRef<T> & src );

	/// Conversion to plain T *.
	inline operator T * ()
	{
		return static_cast<T*>( p_object );
	}


	/// Conversion to plain const T *.
	inline operator const T * () const
	{
		return static_cast<const T*>( p_object );
	}


	/// Converts ObjRef<T> to ObjRef<U>.
	/**
	 *	@param ptr fictional pointer of type to cast to. value is not used.
	 *	@return object of ObjRef<U>.
	 */
	template<class U>
	inline ObjRef<U> cast ( const U * ptr = NULL ) const
	{
		return ObjRef<U>( static_cast<U*>(p_object) );
	}


	/// Member access operator.
	/**
	 *	@return stored pointer.
	 */
	T * operator -> ()
	{ 
		assert( p_object != NULL );
		return static_cast<T*>( p_object ); 
	}


	/// Member access operator.
	/**
	 *	@return stored pointer.
	 */
	const T * operator-> () const
    {
		assert( p_object != NULL );
		return static_cast<const T*>( p_object );
	}


	/// Dereference operator.
	/**
	 *	@return reference to this.
	 */
	T & operator * ()
	{
		assert( p_object != NULL );
		return * static_cast<T*>( p_object );
	}

	/// Dereference operator.
	/**
	 *	@return const reference to this.
	 */
	const T & operator * () const
	{
		assert( p_object != NULL );
		return * static_cast<const T*>( p_object );
	}

	/// Equality comparison operator.
	/**
	*	@param src - ObjRef<T> to compare with.
	 *	@return True if two ObjRef<T> reference the same object, False otherwise.
	 */
	Bool operator == ( const ObjRef & src ) const
	{
		return p_object == src.p_object;
	}


	/// Equality comparison operator.
	/**
	 *	@param src - pointer to compare with.
	 *	@return True if this object stores pointer equal to src.
	 */
	Bool operator == ( const T * src ) const
	{
		return static_cast<const T*>( p_object ) == src;
	}


	/// Inequality comparison operator.
	/**
	 *	@param src object to compare with.
	 *	@return False if two ObjRef<T> reference the same object, False otherwise.
	 */
	Bool operator != ( const ObjRef & src ) const
	{
		return p_object != src.p_object;
	}


	/// Inequality comparison operator.
	/**
	 *	@param src pointer to compare with.
	 *	@return False if this object stores pointer equal to src, True otherwise.
	 */
	Bool operator != ( const T * src ) const
	{
		return static_cast<const T*>( p_object ) != src;
	}


private:
	Object * p_object;
};


template<class T> 
ObjRef<T> & ObjRef<T>::operator = ( const ObjRef<T> & src )
{
	if( p_object != src.p_object )
	{
		if( p_object )
			p_object->Release();
		p_object = src.p_object;
		if( p_object )
			p_object->AddRef();
	}
	return *this;
}


} //namespace mdragon

#endif //__MD_OBJECT_H__ 
