#ifndef ft_iterator
#define ft_iterator

#include <iterator>
#include <memory>
#include <vector>
#include <map>

namespace ft
{
	
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class Iter>
	class reverse_iterator : public std::iterator<
								typename std::iterator_traits<Iter>::iterator_category,
								typename std::iterator_traits<Iter>::iterator_category,
								typename std::iterator_traits<Iter>::iterator_category,
								typename std::iterator_traits<Iter>::iterator_category,
								typename std::iterator_traits<Iter>::iterator_category>
	{
		private:
			typedef typename ft::iterator_traits<Iter>	ftIter;
		public:
			typedef Iter								iterator_type;
			typedef typename ftIter::iterator_category	iterator_category;
			typedef typename ftIter::value_type			value_type;
			typedef typename ftIter::difference_type	difference_type;
			typedef typename ftIter::pointer			pointer;
			typedef typename ftIter::reference			reference;
		protected:
			iterator_type								current;
		public:
			/** Contructors */
			reverse_iterator() : current() {} 
			explicit reverse_iterator(iterator_type x) : current(x) {}
			template <class U>
			explicit reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}
			/** operators */
			template <class U>
			reverse_iterator&	operator=(const reverse_iterator<U>& iter)	{ current = iter.base(); return (*this); }
			reference			operator*() const							{ return (*(--Iter(current))); }
			pointer				operator->() const							{ return (std::addressof(operator*())); }
			value_type			operator[](difference_type n) const			{ return (base()[-n - 1]); }
			reverse_iterator&	operator++()								{ --this->current; return (*this); }
			reverse_iterator&	operator--()								{ ++this->current; return (*this); }
			reverse_iterator	operator++(int) 							{ reverse_iterator it = *this; --this->current; return (it); }
			reverse_iterator	operator--(int) 							{ reverse_iterator it = *this; ++this->current; return (it); }
			reverse_iterator	operator+(difference_type n) const			{ return (reverse_iterator(base() -n)); }
			reverse_iterator	operator-(difference_type n) const			{ return (reverse_iterator(base() + n)); }
			reverse_iterator	operator+=(difference_type n) const			{ *this = *this + n; return (*this); }
			reverse_iterator	operator-=(difference_type n) const			{ *this = *this - n; return (*this); }
			/** return underlying iterator */
			iterator_type		base() const								{ return (current); }
	};
	/** operators for reverse_iterator */
	template <class Iterator1, class Iterator2>
	bool	operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() == rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() != rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() <= rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() >= rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() > rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() < rhs.base()); }
	template <class Iter>
	reverse_iterator<Iter>
			operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)		{ return (it.base() - n); }
	template <class Iter>
	reverse_iterator<Iter>
			operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)		{ return (it.base() + n); }
}

#endif
