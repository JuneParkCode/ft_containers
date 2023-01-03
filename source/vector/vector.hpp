#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <memory>
#include "ft_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			/** type define */
			typedef size_t		size_type;
			typedef T			value_type;
			typedef Allocator	allocator_type;
			/** type define related with allocator */
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef std::allocator_traits<allocator_type>			__alloc_traits;
			/** iterator types */
			typedef typename std::iterator<pointer, value_type>		iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;

		/** member variables  */
		private:
			pointer 			mData;
			size_type			mDataStorageSize;
			size_type			mDataStoreSize; 
			const Allocator&	mAllocator;
		/* constructor. destructors */
		public:
			explicit vector(const Allocator& allocator = std::allocator<T>()):
				mDataStorageSize(0),
				mDataStoreSize(0),
				mData(NULL),
				mAllocator(allocator)
			{
			}
			explicit vector(size_type size, const Allocator& allocator = std::allocator<T>()):
				mDataStorageSize(size),
				mDataStoreSize(0),
				mData(allocator.allocate(size)),
				mAllocator(allocator)
			{
			}
			explicit vector(size_type count, 
					const reference value = T(),
					const Allocator& allocator = std::allocator<T>()):
				mDataStorageSize(count),
				mDataStoreSize(count),
				mData(allocator.allocate(count)),
				mAllocator(allocator)
			{
				// init values
				for (size_type idx = 0; idx < count; ++idx)
					mData[idx] = value;
			}
			~vector()
			{
				if (mData)
					mAllocator.deallocate(mData, mDataStorageSize);
			}
			vector& operator=(const vector<T>& rhs)
			{
				this->clear();
				this->reserve(rhs.capacity());
				for (size_type idx = 0; idx < rhs.size(); ++idx)
					this->push_back(rhs[idx]);
			}
			allocator_type get_allocator() const		{ return (mAllocator); }
		/* iterators */
			iterator				begin()				{ return (iterator(&mData[0])); }
			iterator				end()				{ return (iterator(&mData[mDataStorageSize])); }
			reverse_iterator		rbegin()			{ return (reverse_iterator(end())); }
			reverse_iterator		rend()				{ return (reverse_iterator(begin())); }
		/** member functions */
		public:
			/** capacity  */
			size_type				size() const		{ return (mDataStoreSize); }
			size_type				max_size() const	{ return (INT32_MAX); }
			void					resize(size_type n, value_type val = value_type()) // it destroy stored data
			{
				if (n < this->mDataStoreSize)
				{
					for (size_type i = mDataStoreSize; i < n; ++i)
					{
						mData[i].~value_type();
					}
					mDataStoreSize = n;
				}
				else
				{
					if (n > this->mDataStorageSize)
					{
						pointer newData = mAllocator.allocate(n);
						::memmove(newData, mData, sizeof(T) * (mDataStoreSize));
						for (size_type i = mDataStoreSize; i < n; ++i)
						{
							newData[i] = val;
						}
						if (mData)
							mAllocator.deallocate(mDataStorageSize);
						mData = newData;
						mDataStorageSize = n;
						mDataStoreSize = n;
					}
					else
					{
						for (size_type i = mDataStoreSize; i < n; ++i)
						{
							mData[i] = val;
						}
						mDataStoreSize = n;
					}
				}
			}
			size_type				capacity() const			{ return (mDataStorageSize); }
			bool					empty() const				{ return (mDataStoreSize == 0); }
			void					reserve(size_type n)
			{
				if (n > mDataStorageSize)
				{
					pointer newData = mAllocator.allocate(n);
					::memmove(newData, mData, sizeof(T) * (mDataStoreSize));
					if (mData)
						mAllocator.deallocate(mDataStorageSize);
					mData = newData;
					mDataStorageSize = n;
				}
			}
			
			/** element access */
			reference				operator[](int idx) const	{ return (mData[idx]); }
			reference				at(size_type n)
			{
				if (n > mDataStoreSize || n < 0)
					throw (std::out_of_range("out of range : at()"));
				return (mData[n]);
			}
			const reference			at(size_type n) const
			{
				if (n > mDataStoreSize || n < 0)
					throw (std::out_of_range("out of range : at()"));
				return (mData[n]);
			}
			reference				front()						 { return (mData[0]); }
			const reference			front() const				 { return (mData[0]); }
			reference				back()						 { return (mData[mDataStoreSize - 1]); }
			const reference			back() const				 { return (mData[mDataStoreSize - 1]); }
			const pointer			data() const				 { return (mData); }
			
			/** modifiers */
			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last)
			{
				const size_type SIZE = std::distance(first, last); 
				this->clear();
				this->reserve(SIZE);
				for (size_type idx = 0; idx < SIZE; ++idx)
				{
					mData[idx] = *first;
				}
				mDataStoreSize = SIZE;
			}
			void					assign(size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				for (size_type idx = 0; idx < n; ++idx)
				{
					mData[idx] = val;
				}
				mDataStoreSize = n;
			}
			void					push_back(const value_type& val)
			{
				if (mDataStoreSize == mDataStorageSize)
					this->reserve(mDataStorageSize == 0 ? 1 : mDataStorageSize * 2);
				mData[mDataStoreSize++] = val;
			}
			void					pop_back(const value_type& val) // check empty before use it.
			{
				mData[--mDataStoreSize].~value_type();
			}
			iterator				insert(iterator position, const value_type& val)
			{
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type NEW_SIZE = mDataStoreSize + 1;

				if (NEW_SIZE > mDataStorageSize)
				{
					if (mDataStorageSize == 0)
					{
						this->reserve(NEW_SIZE);
						this->push_back(val);
					}
					else // reallocation
					{
						const size_type SIZE = mDataStorageSize * 2;
						pointer newData = mAllocator.allocate(SIZE);

						::memmove(newData, mData, sizeof(T) * (BEGIN_IDX));
						newData[BEGIN_IDX] = val;
						::memmove(&newData[BEGIN_IDX + 1], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
						if (mData)
							mAllocator.deallocate(mDataStorageSize);
						mData = newData;
						mDataStorageSize = SIZE;
						mDataStoreSize = NEW_SIZE;
					}
				}
				else
				{
					::memmove(&mData[BEGIN_IDX + 1], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
					mData[BEGIN_IDX] = val;
					++mDataStoreSize;
				}
			}
			void					insert(iterator position, size_type n, const value_type& val)
			{
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type NEW_STORED_SIZE = mDataStoreSize + n;

				if (NEW_STORED_SIZE > mDataStorageSize)
				{
					if (mDataStorageSize == 0)
					{
						this->reserve(NEW_STORED_SIZE);
						for (size_type idx = 0; idx < n; ++idx)
						{
							mData[idx] = val;
						}
					}
					else // reallocation
					{
						const size_type SIZE = mDataStorageSize * 2;
						pointer newData = mAllocator.allocate(SIZE);

						::memmove(newData, mData, sizeof(T) * (BEGIN_IDX));
						for (size_type idx = BEGIN_IDX; idx < BEGIN_IDX + n; ++idx)
						{
							newData[idx] = val;
						}
						::memmove(&newData[BEGIN_IDX + n], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
						if (mData)
							mAllocator.deallocate(mDataStorageSize);
						mData = newData;
						mDataStorageSize = SIZE;
					}
				}
				else
				{
					::memmove(&mData[BEGIN_IDX + n], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
					// insertion
					for (size_type idx = BEGIN_IDX; idx != BEGIN_IDX + n; ++idx)
					{
						mData[idx] = val;
					}
				}
				mDataStoreSize = NEW_STORED_SIZE;
			}
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last)
			{
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type INSERT_SIZE = std::distance(first, last);
				const size_type NEW_STORED_SIZE = mDataStoreSize + INSERT_SIZE;

				if (NEW_STORED_SIZE > mDataStorageSize)
				{
					if (mDataStorageSize == 0)
					{
						this->reserve(NEW_STORED_SIZE);
						for (InputIterator it = first; first != last; ++it)
							this->push_back(*it);
					}
					else // reallocation
					{
						const size_type SIZE = mDataStorageSize * 2;
						pointer newData = mAllocator.allocate(SIZE);

						::memmove(newData, mData, sizeof(T) * (BEGIN_IDX));
						iterator it = first;
						for (size_type idx = BEGIN_IDX; it != last; ++idx, ++it)
						{
							newData[idx] = *it;
						}
						::memmove(&newData[BEGIN_IDX + INSERT_SIZE], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
						if (mData)
							mAllocator.deallocate(mDataStorageSize);
						mData = newData;
						mDataStorageSize = SIZE;
						mDataStoreSize = NEW_STORED_SIZE;
					}
				}
				else
				{
					::memmove(&mData[BEGIN_IDX + INSERT_SIZE], &mData[BEGIN_IDX], sizeof(T) * (mDataStoreSize - BEGIN_IDX));
					// insertion
					iterator it = first;
					for (size_type idx = BEGIN_IDX; it != last; ++idx, ++it)
					{
						mData[idx] = *it;
					}
				}
			}
			iterator				erase(iterator position)
			{
				std::copy(position + 1, end(), position);
				--mDataStoreSize;
			}
			iterator				erase(iterator first, iterator last)
			{
				if (first == last)
					return ;
				std::copy(last, end(), first);
				mDataStoreSize -= last - first;
			}
			void					swap(vector& x)
			{
				if (x.mData == mData)
					return ;
				pointer tmpData = mData;
				size_type tmpStorageSize = mDataStorageSize;
				size_type tmpStoreSize = mDataStoreSize;

				mData = x.mData;
				x.mData = tmpData;
				mDataStorageSize = x.mDataStorageSize;
				x.mDataStorageSize = tmpStorageSize;
				mDataStoreSize = x.mDataStoreSize;
				x.mDataStoreSize = tmpStoreSize;
			}
			void					clear()
			{
				for (size_type idx = 0; idx < mDataStoreSize; ++idx)
				{
					mData[idx].~value_type();
				}
				mDataStoreSize = 0;
			}
	};
	template <class T, class Allocator = std::allocator<T> >
	bool operator==(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		if (first.size() != second.size())
			return (false);
		
		const size_t SIZE = first.size();
		for (size_t idx = 0; idx < SIZE; ++idx)
		{
			if (first[idx] != second[idx])
				return (false);
		}
		return (true);
	}
	// below functions use std::lexicographical_compare.
	template <class T, class Allocator = std::allocator<T> >
	bool operator!=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
	}
	template <class T, class Allocator = std::allocator<T> >
	bool operator<(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
	}
	template <class T, class Allocator = std::allocator<T> >
	bool operator<=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
	}
	template <class T, class Allocator = std::allocator<T> >
	bool operator>(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
	}
	template <class T, class Allocator = std::allocator<T> >
	bool operator>=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
	}
}


#endif
