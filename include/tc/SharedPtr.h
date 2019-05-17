	/**
	 * @file SharedPtr.h
	 * @brief Declaration of tc::SharedPtr
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2018/12/30
	 */
#pragma once
#include <tc/types.h>

namespace tc {

	/**
	 * @class SharedPtr
	 * @brief A smart pointer which auto-deletes the embedded ptr when all references are gone
	 *
	 * This smart pointer counts all the copies of itself that exist, and when all copies are destroyed, then the ptr is deleted.
	 */
template <class T>
class SharedPtr
{
public:
		/** 
		 * @brief Default constructor
		 * 
		 * @post
		 * - The managed pointer shall be null
		 */
	SharedPtr();

		/** 
		 * @brief Parameterized Constructor
		 * @return T& Derefenced pointer
		 * 
		 * @note This has undefined behavour when the managed pointer is null.
		 */
	SharedPtr(T* ptr);

		/// Copy constructor
	SharedPtr(const SharedPtr<T>& other);

		/// Move constructor
	SharedPtr(SharedPtr<T>&& other);

		/// Destructor
	~SharedPtr();

		/// Claim ownership of raw pointer
	void operator=(T* ptr);

		/// Copy operator
	SharedPtr<T>& operator=(const SharedPtr<T>& other);

		/// Move operator
	SharedPtr<T>& operator=(SharedPtr<T>&& other);

		/** 
		 * @brief Dereference the managed pointer
		 * @return T& Derefenced pointer
		 * 
		 * @note This has undefined behavour when the managed pointer is null.
		 */
	T& operator*() const;

		/** 
		 * @brief Access members of the managed pointer
		 * @return T* raw pointer
		 * 
		 * @note This has undefined behavour when the managed pointer is null.
		 */
	T* operator->() const;

		/** 
		 * @brief Access the managed pointer
		 * @return T* raw pointer
		 */
	T* get() const;

		/** 
		 * @brief Determine if the managed pointer is null
		 * @return bool true if the managed ptr is nullptr
		 */
	bool isNull() const;

		/** 
		 * @brief Release the managed pointer
		 * 
		 * Only if this is the last instance of SharedPtr managing this pointer, will the pointer be deleted.
		 * 
		 * @post
		 * - After calling this method, the managed pointer shall become null.
		 */
	void release();
private:
	T* mPtr;
	size_t* mRefCnt;

	void deletePtr();
};

template <class T>
inline SharedPtr<T>::SharedPtr() :
	mPtr(nullptr),
	mRefCnt(nullptr)
{
}

template <class T>
inline SharedPtr<T>::SharedPtr(T* ptr) :
	SharedPtr()
{
	*this = ptr;
}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) :
	SharedPtr()
{
	*this = other;
}

template <class T>
inline SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) :
	SharedPtr()
{
	*this = std::move(other);
}


template <class T>
inline SharedPtr<T>::~SharedPtr()
{
	deletePtr();
}

template <class T>
inline void SharedPtr<T>::operator=(T* ptr)
{
	deletePtr();
	if (ptr != nullptr)
	{
		mPtr = ptr;
		mRefCnt = new size_t;
		*mRefCnt = 1;
	}
	else
	{
		mPtr = nullptr;
		mRefCnt = nullptr;
	}
	
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	deletePtr();

	if (other.mPtr != nullptr)
	{
		mPtr = other.mPtr;
		mRefCnt = other.mRefCnt;
		*mRefCnt += 1;
	}
	else
	{
		mPtr = nullptr;
		mRefCnt = nullptr;
	}
	
	return *this;
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other)
{
	deletePtr();

	// re-assign members
	mPtr = other.mPtr;
	mRefCnt = other.mRefCnt;

	// set source members to nullptrs
	other.mPtr = nullptr;
	other.mRefCnt = nullptr;
	
	return *this;
}

template <class T>
inline T& SharedPtr<T>::operator*() const
{
	return *mPtr;
}

template <class T>
inline T* SharedPtr<T>::operator->() const
{
	return mPtr;
}

template <class T>
inline T* SharedPtr<T>::get() const
{
	return mPtr;
}

template <class T>
inline bool SharedPtr<T>::isNull() const
{
	return mPtr == nullptr;
}

template <class T>
inline void SharedPtr<T>::release()
{
	deletePtr();
}

template <class T>
inline void SharedPtr<T>::deletePtr()
{
	// if this is an empty refernce
	if (mRefCnt == nullptr)
	{
		mPtr = nullptr;
		mRefCnt = nullptr;
	}
	// else if this is the last reference
	else if (*mRefCnt == 1)
	{
		// delete memory
		delete mPtr;
		delete mRefCnt;

		// make ptrs null
		mPtr = nullptr;
		mRefCnt = nullptr;
	}
	// else if this is not the last reference
	else if (*mRefCnt > 1)
	{
		// decrement reference count
		*mRefCnt -= 1;

		// make ptrs null
		mPtr = nullptr;
		mRefCnt = nullptr;
	}
}

} // namespace tc