/**
 * \class SharedPtr
 *
 * \ingroup LibToolChain
 *
 * \brief A smart pointer which auto-deletes the embedded ptr when all references are gone
 *
 * This smart pointer counts all the copies of itself that exist, and when all copies are destroyed, then the ptr is deleted.
 * 
 * 
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/11/10
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/types.h>

namespace tc
{
	template <class T>
	class SharedPtr
	{
	public:
		/// Default constructor
		SharedPtr();

		// Initialising constructor with pointer to own
		SharedPtr(T* ptr);

		/// Copy constructor
		SharedPtr(const SharedPtr<T>& other);

		/// Destructor
		~SharedPtr();

		/// Operator to own pointer
		void operator=(T* ptr);

		/// Operator to duplicate another SharedPtr
		void operator=(const SharedPtr<T>& other);

		/// Direct const access to pointer
		const T* operator*() const;

		/// Direct access to pointer
		T* operator*();

	private:
		T* mPtr;
		size_t* mRefCnt;

		void deletePtr();
	};

	template <class T>
	inline SharedPtr<T>::SharedPtr() :
		mPtr(nullptr),
		mRefCnt(new size_t)
	{
		*mRefCnt = 0;
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
			mRefCnt = new size_t;
			*mRefCnt = 0;
		}
		
	}

	template <class T>
	inline void SharedPtr<T>::operator=(const SharedPtr<T>& other)
	{
		deletePtr();

		mPtr = other.mPtr;
		mRefCnt = other.mRefCnt;
		*mRefCnt += 1;
	}

	template <class T>
	inline const T* SharedPtr<T>::operator*() const
	{
		return mPtr;
	}

	template <class T>
	inline T* SharedPtr<T>::operator*()
	{
		return mPtr;
	}

	template <class T>
	inline void SharedPtr<T>::deletePtr()
	{
		// if this is not the last reference
		if (*mRefCnt > 1)
		{
			// decrement reference count
			*mRefCnt -= 1;

			// make ptrs null
			mPtr = nullptr;
			mRefCnt = nullptr;
		}
		// if this is the last refeference
		else if (*mRefCnt == 1)
		{
			// delete memory
			delete mPtr;
			delete mRefCnt;

			// make ptrs null
			mPtr = nullptr;
			mRefCnt = nullptr;
		}
		// else if this is an empty refernce
		else if (*mRefCnt == 0)
		{
			delete mRefCnt;

			mPtr = nullptr;
			mRefCnt = nullptr;
		}
	}
}