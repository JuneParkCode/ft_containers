#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <typeinfo>
#include <iterator>
#include <memory>

/*
 *	ARRAY CLASS FOR BASE CONTAINER STRUCTURE
 * */

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class array
	{
		public:
			array(const Allocator& allocator = std::allocator<T>());
			array(size_t size, const Allocator& allocator = std::allocator<T>());
			~array();
			size_t		size() const { return (mDataStoreSize); }
			bool		empty() const { return (mDataStoreSize == 0); }
			const T*	data() const { return (mData); }
			T&			operator[](int idx) const { return (mData[idx]); }
		/* iterators */
		private:
			class iterator
			{
				typedef std::forward_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T* pointer_type;
				typedef T& reference_type;
			private:
				pointer_type mPtr;
			public:
				iterator(pointer_type ptr): mPtr(ptr) {}
				reference_type operator*()  { return (*mPtr); }
				pointer_type operator->() { return (mPtr); }
				iterator& operator++()
				{
					++mPtr;
					return (*this);
				}
				iterator& operator++(int)
				{
					iterator it = *this;
					++mPtr;
					return (it);
				}
				iterator& operator--()
				{
					--mPtr;
					return (*this);
				}
				iterator& operator--(int)
				{
					iterator it = *this;
					--mPtr;
					return (it);
				}
				iterator& operator=(const iterator& it)
				{
					iterator temp(it.mPtr);
					return (temp);
				}
				bool operator==(const iterator& it) { return (mPtr == it.mPtr); }
				bool operator!=(const iterator& it) { return (mPtr != it.mPtr); }
			};

			class const_iterator
			{
				typedef std::forward_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T* pointer_type;
				typedef T& reference_type;
			private:
				pointer_type mPtr;
			public:
				const_iterator(pointer_type ptr): mPtr(ptr) {}
				const value_type& operator*()  { return (*mPtr); }
				const value_type* operator->() { return (mPtr); }
				const_iterator& operator++()
				{
					++mPtr;
					return (*this);
				}
				const_iterator& operator++(int)
				{
					const_iterator it = *this;
					++mPtr;
					return (it);
				}
				const_iterator& operator--()
				{
					--mPtr;
					return (*this);
				}
				const_iterator& operator--(int)
				{
					const_iterator it = *this;
					--mPtr;
					return (it);
				}
				const_iterator& operator=(const const_iterator& it)
				{
					const_iterator temp(it.mPtr);
					return (temp);
				}
				bool operator==(const const_iterator& it) { return (mPtr == it.mPtr); }
				bool operator!=(const const_iterator& it) { return (mPtr != it.mPtr); }
			};

			class reverse_iterator
			{
				typedef std::forward_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T* pointer_type;
				typedef T& reference_type;
			private:
				pointer_type mPtr;
			public:
				reverse_iterator(pointer_type ptr): mPtr(ptr) {}
				reference_type operator*()  { return (*mPtr); }
				pointer_type operator->() { return (mPtr); }
				reverse_iterator& operator++()
				{
					--mPtr;
					return (*this);
				}
				reverse_iterator& operator++(int)
				{
					reverse_iterator it = *this;
					--mPtr;
					return (it);
				}
				reverse_iterator& operator--()
				{
					++mPtr;
					return (*this);
				}
				reverse_iterator& operator--(int)
				{
					reverse_iterator it = *this;
					++mPtr;
					return (it);
				}
				reverse_iterator& operator=(const reverse_iterator& it)
				{
					reverse_iterator temp(it.mPtr);
					return (temp);
				}
				bool operator==(const reverse_iterator& it) { return (mPtr == it.mPtr); }
				bool operator!=(const reverse_iterator& it) { return (mPtr != it.mPtr); }
			};

			class const_reverse_iterator
			{
				typedef std::forward_iterator_tag iterator_category;
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T* pointer_type;
				typedef T& reference_type;
			private:
				pointer_type mPtr;
			public:
				const_reverse_iterator(pointer_type ptr): mPtr(ptr) {}
				const value_type& operator*()  { return (*mPtr); }
				const value_type* operator->() { return (mPtr); }
				const_reverse_iterator& operator++()
				{
					--mPtr;
					return (*this);
				}
				const_reverse_iterator& operator++(int)
				{
					const_reverse_iterator it = *this;
					--mPtr;
					return (it);
				}
				const_reverse_iterator& operator--()
				{
					++mPtr;
					return (*this);
				}
				const_reverse_iterator& operator--(int)
				{
					const_reverse_iterator it = *this;
					++mPtr;
					return (it);
				}
				const_reverse_iterator& operator=(const const_reverse_iterator& it)
				{
					const_reverse_iterator temp(it.mPtr);
					return (temp);
				}
				bool operator==(const const_reverse_iterator& it) { return (mPtr == it.mPtr); }
				bool operator!=(const const_reverse_iterator& it) { return (mPtr != it.mPtr); }
			};
		public:
			iterator begin() { return (iterator(&mData[0])); }
			iterator end() { return (iterator(&mData[mDataStorageSize])); }
			const_iterator cbegin() const { return (const_iterator(&mData[0])); }
			const_iterator cend() const { return (const_iterator(&mData[mDataStorageSize])); }
			reverse_iterator rbegin() { return (reverse_iterator(&mData[mDataStorageSize - 1])); }
			reverse_iterator rend() { return (reverse_iterator(&mData[-1])); }
			const_reverse_iterator crbegin() const { return (const_reverse_iterator(&mData[mDataStorageSize - 1])); }
			const_reverse_iterator crend() const { return (const_reverse_iterator(&mData[-1])); }
		/* member variables */
		private:
			T* 		mData;
			size_t	mDataStorageSize;
			size_t	mDataStoreSize; // array 에는 필요X 
			const Allocator& mAllocator;
	};
}

#endif
