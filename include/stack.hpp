#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>
#include <exception>
#include <memory>
#include "ft_iterator.hpp"
#include "ft_config.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include <stack>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack : protected Container
	{
		private:
			typedef Container				_Container_type;
			typedef stack<T, Container>		_Self;
			_Container_type&				mContainer;
			using typename _Container_type::iterator;
			using typename _Container_type::const_iterator;
			using typename _Container_type::reverse_iterator;
			using typename _Container_type::const_reverse_iterator;
		public:
			using typename _Container_type::allocator_type;
			using typename _Container_type::difference_type;
			using typename _Container_type::size_type;
			using typename _Container_type::value_type;
			using typename _Container_type::reference;
			using typename _Container_type::const_reference;
			using typename _Container_type::pointer;
			using typename _Container_type::const_pointer;
		/* constructor. destructors */
		public:
			stack() : Container(), mContainer(*this) {}
			explicit stack(const Container& cont) : Container(cont), mContainer(*this) {}
			stack(const stack& other) : Container(), mContainer(*this)
			{
				*this = other;
			}
			stack& operator=( const stack& other )
			{
				for (stack::const_iterator it = other.begin(); it != other.end(); ++it)
				{
					this->push(*it);
				}
				return (*this);
			}
		public:
			/** capacity  */
			using _Container_type::size;
			using _Container_type::empty;
			/** element access (NOEXCEPT!!) */
			FT_INLINE reference				top()		FT_NOEXCEPT			{ return (this->back()); }
			FT_INLINE const_reference		top()		const FT_NOEXCEPT	{ return (this->back()); }
			/** modifiers  */
			void							push(const value_type& val)		{ this->push_back(val); }
			void							pop()							{ this->pop_back(); }
			/** friend operators  */
			template <class T1, class Container1>
			friend bool operator==(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
			template <class T1, class Container1>
			friend bool operator!=(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
			template <class T1, class Container1>
			friend bool operator>=(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
			template <class T1, class Container1>
			friend bool operator<=(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
			template <class T1, class Container1>
			friend bool operator<(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
			template <class T1, class Container1>
			friend bool operator>(const stack<T1, Container1>& first, const stack<T1, Container1>& second);
	};
	/** compare operator definition */
	template <class T, class Container>
	bool operator==(const stack<T, Container>& first, const stack<T, Container>& second)	{ return (first.mContainer == second.mContainer); }
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& first, const stack<T, Container>& second)	{ return (first.mContainer != second.mContainer); }
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& first, const stack<T, Container>& second)	{ return (first.mContainer >= second.mContainer); }
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& first, const stack<T, Container>& second)	{ return (first.mContainer <= second.mContainer); }
	template <class T, class Container>
	bool operator>(const stack<T, Container>& first, const stack<T, Container>& second)		{ return (first.mContainer > second.mContainer); }
	template <class T, class Container>
	bool operator<(const stack<T, Container>& first, const stack<T, Container>& second)		{ return (first.mContainer < second.mContainer); }
}

#endif
