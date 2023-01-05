#ifndef ft_iterator
#define ft_iterator

#include <iterator>
#include <memory>
#include <vector>
#include <map>
#include "ft_config.hpp"

namespace ft
{
	/** iterator_traits */
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

/** pointer_iterator */
namespace ft
{
	template <class Iter, class Container>
	class pointer_iterator
	{
		private:
			Iter mCurrent;
			typedef pointer_iterator<Iter, Container>						_Self;
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
		public:
			pointer_iterator() : mCurrent() {};
			pointer_iterator(const Iter& it) : mCurrent(it) {}
			template<typename U> // const iterator conversion
			pointer_iterator(const pointer_iterator<U, Container>& it) : mCurrent(it.base()) {}
			template<typename U> // const iterator conversion
			iterator_type&				operator=(const pointer_iterator<U, Container>& it) { mCurrent = it.base(); return (*this); }
		public:
		  	// forward iterator requirements
			FT_INLINE  reference		operator*()		const FT_NOEXCEPT	{ return (*mCurrent); }
			FT_INLINE  pointer			operator->()	const FT_NOEXCEPT	{ return (mCurrent); }
			FT_INLINE  _Self&			operator++()	FT_NOEXCEPT			{ ++mCurrent; return (*this); }
			FT_INLINE  _Self			operator++(int)	FT_NOEXCEPT			{ return (_Self(mCurrent++)); }
			// bidirectional iterator requirements
			FT_INLINE  _Self&			operator--()	FT_NOEXCEPT			{ --mCurrent; return *this; }
			FT_INLINE  _Self			operator--(int)	FT_NOEXCEPT			{ return (_Self(mCurrent--)); }
			// random access iterator requirements
			FT_INLINE  reference		operator[](const difference_type& n)	const FT_NOEXCEPT	{ return (mCurrent[n]); }
			FT_INLINE  _Self&			operator+=(const difference_type& n)	FT_NOEXCEPT			{ mCurrent += n; return (*this); }
			FT_INLINE  _Self			operator+(const difference_type& n)		const FT_NOEXCEPT	{ return (_Self(mCurrent + n)); }
			FT_INLINE  _Self&			operator-=(const difference_type& n)	FT_NOEXCEPT			{ mCurrent -= n; return (*this); }
			FT_INLINE  _Self			operator-(const difference_type& n)		const FT_NOEXCEPT	{ return (_Self(mCurrent - n)); }
			FT_INLINE  difference_type	operator-(const _Self& iter)			const				{ return (mCurrent - iter.mCurrent); }
			FT_INLINE  bool				operator==(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent == iter.mCurrent); }
			FT_INLINE  bool				operator!=(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent != iter.mCurrent); }
			FT_INLINE  bool				operator<=(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent <= iter.mCurrent); }
			FT_INLINE  bool				operator>=(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent >= iter.mCurrent); }
			FT_INLINE  bool				operator<(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent < iter.mCurrent); }
			FT_INLINE  bool				operator>(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent > iter.mCurrent); }
			FT_INLINE  const Iter& 		base()									const FT_NOEXCEPT	{ return (mCurrent); }
			
	};
	template <class Iter, class Container>
	FT_INLINE  pointer_iterator<Iter, Container>	operator+(const pointer_iterator<Iter, Container>& iter, const typename ft::iterator_traits<Iter>::difference_type& n)	FT_NOEXCEPT
	{ return (pointer_iterator<Iter, Container>(iter.base() + n)); }
	template <class Iter, class Container>
	FT_INLINE  pointer_iterator<Iter, Container>	operator-(const pointer_iterator<Iter, Container>& iter, const typename ft::iterator_traits<Iter>::difference_type& n)	FT_NOEXCEPT
	{ return (pointer_iterator<Iter, Container>(iter.base() - n)); }
	template <class Iter, class Container>
	FT_INLINE  pointer_iterator<Iter, Container>	operator+(const typename ft::iterator_traits<Iter>::difference_type& n, const pointer_iterator<Iter, Container>& iter)	FT_NOEXCEPT
	{ return (pointer_iterator<Iter, Container>(iter.base() + n)); }
	template <class Iter, class Container>
	FT_INLINE  pointer_iterator<Iter, Container>	operator-(const typename ft::iterator_traits<Iter>::difference_type& n, const pointer_iterator<Iter, Container>& iter)	FT_NOEXCEPT
	{ return (pointer_iterator<Iter, Container>(iter.base() - n)); }
}
/** reverse iterator */
namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
		private:
			typedef typename ft::iterator_traits<Iter>		_IterTraits;
			typedef reverse_iterator<Iter>					_Self;
		public:
			typedef Iter									iterator_type;
			typedef typename _IterTraits::iterator_category	iterator_category;
			typedef typename _IterTraits::value_type		value_type;
			typedef typename _IterTraits::difference_type	difference_type;
			typedef typename _IterTraits::pointer			pointer;
			typedef typename _IterTraits::reference			reference;
		protected:
			iterator_type									current;
		public:
			/** Contructors */
			reverse_iterator() : current() {} 
			explicit reverse_iterator(iterator_type x) : current(x) {}
			template <class U>
			explicit reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}
			template <class U>
			_Self& 				operator=(const reverse_iterator<U>& other)	{ current = other.base(); return (*this); }
			/** return underlying iterator */
			iterator_type		base()							const				{ return (current); }
			/** operators */
			FT_INLINE reference	operator*()						const FT_NOEXCEPT	{ return (*(--Iter(current))); }
			FT_INLINE pointer	operator->()					const FT_NOEXCEPT	{ return (std::addressof(operator*())); }
			FT_INLINE reference	operator[](difference_type n)	const FT_NOEXCEPT	{ return (base()[-n - 1]); }
			FT_INLINE _Self&	operator++()					FT_NOEXCEPT			{ --this->current; return (*this); }
			FT_INLINE _Self&	operator--()					FT_NOEXCEPT			{ ++this->current; return (*this); }
			FT_INLINE _Self		operator++(int) 				FT_NOEXCEPT			{ _Self it = *this; --this->current; return (it); }
			FT_INLINE _Self		operator--(int) 				FT_NOEXCEPT			{ _Self it = *this; ++this->current; return (it); }
			FT_INLINE _Self		operator+(difference_type n)	const FT_NOEXCEPT	{ return (_Self(base() - n)); }
			FT_INLINE _Self		operator-(difference_type n)	const FT_NOEXCEPT	{ return (_Self(base() + n)); }
			FT_INLINE _Self		operator+=(difference_type n)	FT_NOEXCEPT			{ current -= n; return (*this); }
			FT_INLINE _Self		operator-=(difference_type n)	FT_NOEXCEPT			{ current += n; return (*this); }
	};
	/** operators for reverse_iterator */
	template <class Iterator1, class Iterator2>
	bool	operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() == rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() != rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() >= rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() <= rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() < rhs.base()); }
	template <class Iterator1, class Iterator2>
	bool	operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)	{ return (lhs.base() > rhs.base()); }
	template <class Iter>
	reverse_iterator<Iter>
			operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)		{ return (reverse_iterator<Iter>(it.base() - n)); }
	template <class Iter>
	reverse_iterator<Iter>
			operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)		{ return (reverse_iterator<Iter>(it.base() + n)); }
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type
			operator-(const reverse_iterator<Iter>& first, const reverse_iterator<Iter>& second)				{ return (second.base() - first.base()); }

}

#endif
