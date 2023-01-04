#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <exception>
#include <iterator>
#include <memory>
#include <vector>
#include "ft_iterator.hpp"
#include "ft_config.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			/** type define */
			typedef T			value_type;
			typedef Allocator	allocator_type;
			/** type define related with allocator */
			typedef typename allocator_type::size_type 			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			/** iterator types */
			typedef pointer_iterator<pointer, vector<T, Allocator> >		iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef pointer_iterator<const_pointer, vector<T, Allocator> >	const_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		/** member variables  */
		private:
			iterator 		mStartData;
			iterator		mFinishData;
			iterator		mEndOfStorage;
			allocator_type	mAllocator;
		/* constructor. destructors */
		public:
			vector():
				mStartData(0),
				mFinishData(0),
				mEndOfStorage(0),
				mAllocator(allocator_type())
			{
			}
			explicit vector(const Allocator& alloc):
				mStartData(0),
				mFinishData(0),
				mEndOfStorage(0),
				mAllocator(alloc)
			{
			}
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()):
				mStartData(0),
				mFinishData(0),
				mEndOfStorage(0),
				mAllocator(alloc)
			{
				mStartData = mAllocator.allocate(count);
				mFinishData = mStartData + count;
				mEndOfStorage = mStartData + count;
				std::uninitialized_fill_n(mStartData, count, value);
			}
			// FIXME: vector<int> v (1, 2) -> goes here!!
			template< class InputIt >
			vector(InputIt first,
				typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type last,
				const Allocator& alloc = Allocator()):
					mStartData(0),
					mFinishData(0),
					mEndOfStorage(0),
					mAllocator(alloc)
			{
				mStartData = mAllocator.allocate(std::distance(first, last));
				mFinishData = mStartData + std::distance(first, last);
				mEndOfStorage = mFinishData;
				std::uninitialized_copy(first, last, begin());
			}
			vector(const vector& other):
					mStartData(0),
					mFinishData(0),
					mEndOfStorage(0),
					mAllocator(other.get_allocator())
			{
				mStartData = mAllocator.allocate(other.capacity());
				mFinishData = mStartData + other.size();
				mEndOfStorage = mFinishData;
				std::uninitialized_copy(other.begin(), other.end(), begin());	
			}
			~vector()
			{
				if (mStartData.base())
					mAllocator.deallocate(mStartData.base(), capacity());
			}
			vector& operator=(const vector<T>& rhs)
			{
				this->clear();
				this->reserve(rhs.capacity());
				for (size_type idx = 0; idx < rhs.size(); ++idx)
					this->push_back(rhs[idx]);
				return (*this);
			}
			FT_INLINE allocator_type get_allocator() const FT_NOEXCEPT	{ return (mAllocator); }
		/* iterators */
			iterator				begin()		FT_NOEXCEPT			{ return (iterator(mStartData)); }
			const_iterator			begin()		const FT_NOEXCEPT	{ return (const_iterator(mStartData)); }
			iterator				end()		FT_NOEXCEPT			{ return (iterator(mFinishData)); }
			const_iterator			end()		const FT_NOEXCEPT	{ return (const_iterator(mFinishData)); }
			reverse_iterator		rbegin()						{ return (reverse_iterator(mFinishData)); }
			const_reverse_iterator	rbegin()	const				{ return (const_reverse_iterator(mFinishData)); }
			reverse_iterator		rend()		FT_NOEXCEPT			{ return (reverse_iterator(mStartData)); }
			const_reverse_iterator	rend()		const FT_NOEXCEPT	{ return (const_reverse_iterator(mStartData)); }
			const_iterator			cbegin()	const FT_NOEXCEPT	{ return (const_iterator(mStartData)); }
			const_iterator			cend()		const FT_NOEXCEPT	{ return (const_iterator(mFinishData)); }
			const_reverse_iterator	crbegin()	const FT_NOEXCEPT	{ return (const_reverse_iterator(mStartData)); }
			const_reverse_iterator	crend()		const FT_NOEXCEPT	{ return (const_reverse_iterator(mStartData)); }
		private:
			/** helper */
			template <class Iter>
			void destroy(Iter first, Iter last)
			{
				for (; first != last; ++first)
				{
					first->~value_type();
				}
			}
		/** member functions */
		public:
			/** capacity  */
			FT_INLINE size_type		size() 		const FT_NOEXCEPT	{ return (mFinishData - mStartData); }
			FT_INLINE size_type		max_size()	const FT_NOEXCEPT	{ return (std::min(size_type(-1) / sizeof(value_type), (size_type)std::numeric_limits<difference_type>::max())); }
			FT_INLINE size_type		capacity()	const FT_NOEXCEPT	{ return (mEndOfStorage - mStartData); }
			FT_INLINE bool			empty()		const FT_NOEXCEPT	{ return (size() == 0); }
			void					resize(size_type n, value_type val = value_type()) // it destroy stored data
			{
				if (n < size())
				{
					destroy(mStartData + n, mFinishData);
					mFinishData = mStartData + n;
				}
				else
				{
					if (n > capacity())
					{
						pointer newData = mAllocator.allocate(n);
						std::uninitialized_copy(mStartData, mFinishData, newData);
						std::uninitialized_fill_n(newData + size(), n - size(), val);
						mAllocator.deallocate(mStartData.base(), capacity());
						mStartData = newData;
						mFinishData = mStartData + n;
						mEndOfStorage = mStartData + n;
					}
					else
					{
						std::uninitialized_fill_n(mFinishData, mFinishData + n, val);
						mFinishData += n;
					}
				}
			}
			void					reserve(size_type n)
			{
				if (n > capacity())
				{
					pointer newData = mAllocator.allocate(n);
					std::uninitialized_copy(mStartData, mFinishData, newData);
					if (mStartData.base())
						mAllocator.deallocate(mStartData.base(), capacity());
					mFinishData = newData + size();
					mStartData = newData;
					mEndOfStorage = mStartData + n;
				}
			}
			/** element access (NOEXCEPT!!) */
			FT_INLINE reference				operator[](int idx)	FT_NOEXCEPT			{ return (mStartData[idx]); }
			FT_INLINE const_reference		operator[](int idx) const FT_NOEXCEPT	{ return (mStartData[idx]); }
			FT_INLINE reference				front()				FT_NOEXCEPT			{ return (mStartData[0]); }
			FT_INLINE const_reference		front() 			const				{ return (mStartData[0]); }
			FT_INLINE reference				back()				FT_NOEXCEPT			{ return (*(mFinishData - 1)); }
			FT_INLINE const_reference		back()				const				{ return (*(mFinishData - 1)); }
			FT_INLINE const pointer			data()				const FT_NOEXCEPT	{ return (mStartData); }
			FT_INLINE pointer				data()				FT_NOEXCEPT			{ return (mStartData); }
			/** at() throws exception...  */
			reference						at(size_type n)
			{
				if (n > capacity() || n < 0)
					throw (std::out_of_range("out of range : vector::at()"));
				return (mStartData[n]);
			}
			const_reference					at(size_type n) const
			{
				if (n > size() || n < 0)
					throw (std::out_of_range("out of range : vector::at()"));
				return (mStartData[n]);
			}
			/** modifiers */
			template <class InputIterator>
			void							assign(InputIterator first, typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type last)
			{
				// if overlapped in memory, it will be undefined behavior
				const size_type SIZE = std::distance(first, last); 
				this->clear();
				this->reserve(SIZE);
				std::uninitialized_copy(first, last, mStartData);
				mFinishData = mStartData + SIZE;
			}
			void							assign(size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				std::uninitialized_fill_n(mStartData, n, val);
				mFinishData = mStartData + n;
			}
			void							push_back(const value_type& val)
			{
				if (size() == capacity())
					this->reserve(capacity() == 0 ? 1 : capacity() * 2);
				*(mFinishData++) = val;
			}
			void							pop_back() // check empty before use it.
			{
				this->destroy(mFinishData - 1, mFinishData);
				--mFinishData;
			}
			iterator						insert(iterator position, const value_type& val)
			{
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type NEW_SIZE = size() + 1;

				if (NEW_SIZE > capacity())
				{
					if (capacity() == 0)
					{
						this->reserve(NEW_SIZE);
						this->push_back(val);
					}
					else // reallocation
					{
						const size_type NEW_CAPACITY = capacity() * 2;
						pointer newData = mAllocator.allocate(NEW_CAPACITY);

						std::uninitialized_copy(mStartData, position, newData);
						newData[BEGIN_IDX] = val;
						std::uninitialized_copy(position, mFinishData, newData + BEGIN_IDX);
						if (mStartData.base())
							mAllocator.deallocate(mStartData.base(), capacity());
						mStartData = newData;
						mFinishData = mStartData + NEW_SIZE;
						mEndOfStorage = mStartData + NEW_CAPACITY;
					}
				}
				else
				{
					std::copy_backward(position, mFinishData, position + 1);
					mStartData[BEGIN_IDX] = val;
					++mFinishData;
				}
				return (mStartData + BEGIN_IDX);
			}
			iterator						insert(iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return (position);
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type NEW_SIZE = size() + n;

				if (NEW_SIZE > capacity())
				{
					if (capacity() == 0)
					{
						this->reserve(NEW_SIZE);
						std::uninitialized_fill_n(mStartData, n, val);
					}
					else // reallocation
					{
						const size_type NEW_CAPACITY = capacity() * 2;
						pointer newData = mAllocator.allocate(NEW_CAPACITY);

						std::uninitialized_copy(mStartData, position, newData);
						std::uninitialized_fill_n(newData + BEGIN_IDX, n, val);
						std::uninitialized_copy(position, mFinishData, newData + BEGIN_IDX + n);
						if (mStartData.base())
							mAllocator.deallocate(mStartData.base(), capacity());
						mStartData = newData;
						mEndOfStorage = mStartData + NEW_CAPACITY;
					}
				}
				else
				{
					std::copy_backward(position, mFinishData, position + n);
					std::uninitialized_fill_n(position, n, val);
				}
				mFinishData = mStartData + NEW_SIZE;
				return (mStartData + BEGIN_IDX);
			
			}
			template <class InputIterator>
			iterator						insert(iterator position, InputIterator first, InputIterator last)
			{
				if (first == last)
					return (position);
				const size_type BEGIN_IDX = std::distance(begin(), position);
				const size_type INSERT_SIZE = std::distance(first, last);
				const size_type NEW_SIZE = size() + INSERT_SIZE;

				if (NEW_SIZE > capacity())
				{
					if (capacity() == 0)
					{
						this->reserve(NEW_SIZE);
						std::uninitialized_copy(first, last, mStartData);
					}
					else // reallocation
					{
						const size_type NEW_CAPACITY = capacity() * 2;
						pointer newData = mAllocator.allocate(NEW_CAPACITY);

						std::uninitialized_copy(mStartData, position, newData);
						std::uninitialized_copy(first, last, newData + INSERT_SIZE);
						std::uninitialized_copy(position, mFinishData, newData + BEGIN_IDX + INSERT_SIZE);
						if (mStartData.base())
							mAllocator.deallocate(mStartData.base(), capacity());
						mStartData = newData;
						mEndOfStorage = mStartData + NEW_CAPACITY;
					}
				}
				else
				{
					std::copy_backward(position, mFinishData, position + INSERT_SIZE);
					std::uninitialized_copy(first, last, position);
				}
				mFinishData = mStartData + NEW_SIZE;
				return (mStartData + BEGIN_IDX);
			}
			iterator						erase(iterator position)
			{
				std::copy(position + 1, end(), position);
				--mFinishData;
				return (position);
			}
			iterator						erase(iterator first, iterator last)
			{
				if (first == last)
					return (first);
				const size_type ERASE_SIZE = last - first;
				
				std::copy(last, end(), first);
				destroy(first, last);
				mFinishData -= ERASE_SIZE;
				return (first);
			}
			FT_INLINE void					swap(vector& x) FT_NOEXCEPT
			{ // if allocator is different, it will be undefined behavior
				if (x.mStartData == mStartData)
					return ;
				std::swap(x.mStartData, mStartData);
				std::swap(x.mFinishData, mFinishData);
				std::swap(x.mEndOfStorage, mEndOfStorage);
			}
			void							clear()
			{
				destroy(begin(), end());
				mFinishData = mStartData;
			}
	};
	template <class T, class Allocator>
	void swap(vector<T, Allocator>& first, vector<T, Allocator>& second)
	{
		first.swap(second);
	}
	template <class T, class Allocator>
	bool operator==(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		if (first.size() != second.size())
			return (false);
		typename vector<T, Allocator>::const_iterator firstIt = first.begin();
		typename vector<T, Allocator>::const_iterator secondIt = second.begin();

		for (; firstIt != first.end() && secondIt != second.end(); ++firstIt, ++secondIt)
		{
			if (*firstIt != *secondIt)
				return (false);
		}
		return (true);
	}
	// below functions use std::lexicographical_compare.
	template <class T, class Allocator>
	bool operator!=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		return (first.empty() == second.empty());
	}
	template <class T, class Allocator>
	bool operator<(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		return (first.empty() == second.empty());
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		return (first.empty() == second.empty());
	}
	template <class T, class Allocator>
	bool operator>(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		return (first.empty() == second.empty());
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& first, const vector<T, Allocator>& second)
	{
		return (first.empty() == second.empty());
	}
}


#endif
