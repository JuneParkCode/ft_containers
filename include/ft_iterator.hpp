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


/** tree iterator */
namespace ft
{
	template <class NodeType>
	class bst_iterator
	{
		private:
			typedef NodeType									node_type;
			typedef bst_iterator<NodeType>						_Self;
		public:
			node_type* 											mCurrent;
			typedef NodeType									value_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t									difference_type;
			typedef typename node_type::value_type*				pointer;
			typedef typename node_type::value_type&				reference;
		public:
			bst_iterator() : mCurrent(NULL) {};
			bst_iterator(node_type* node) : mCurrent(node) {}
			template<typename U> // const iterator conversion
			bst_iterator(const bst_iterator<U>& it) : mCurrent(it.mCurrent) {}
			template<typename U> // const iterator conversion
			node_type&					operator=(const bst_iterator<U>& it) { mCurrent = it.mCurrent; return (*this); }
		protected:
			/** NOTE: BELOW FUNCTIONS MUST BE TESTED */
			FT_INLINE  void				increment() FT_NOEXCEPT
			{
				// find next larger element
				if (mCurrent->right)
				{
					mCurrent = mCurrent->right;
					// children is larger than previous node 
					while (mCurrent->left)
					{
						mCurrent = mCurrent->left;
					}
				}
				// children is not larger than previous node.
				else
				{
					// go to parent until parent > current
					node_type* parent = mCurrent->parent;
					while (parent && mCurrent == parent->right && parent->parent != mCurrent) // parent < current // if root case, it not works....
					{
						mCurrent = parent;
						parent = mCurrent->parent;
					}
					mCurrent = parent;
				}
			}
			FT_INLINE  void				decrement() FT_NOEXCEPT
			{
				if (mCurrent->value.first == 7)
				{
					(void) mCurrent;
					int i = 0;
					(void) i;
				}
				if (mCurrent->left) // find maximum node in subtree
				{
					if (mCurrent->left->parent != mCurrent) // end() case
					{
						mCurrent = mCurrent->right; // goto max node of tree
					}
					else
					{
						node_type* subMaxNode = mCurrent->left->maxNode();
						mCurrent = subMaxNode;
					}
				}
				else
				{
					if (!mCurrent->parent)
						return;
					// if node is left child of parent, go to parent
					while (mCurrent->parent && mCurrent == mCurrent->parent->left && mCurrent->parent->parent != mCurrent)
					{
						mCurrent = mCurrent->parent;
					}
					mCurrent = mCurrent->parent;
				}
			}
		public:
		  	// forward iterator requirements
			FT_INLINE  reference		operator*()		const FT_NOEXCEPT
			{
				return (mCurrent->value);
			}
			FT_INLINE  pointer			operator->()	const FT_NOEXCEPT
			{
				return (&(mCurrent->value));
			}
			FT_INLINE  _Self&			operator++()	FT_NOEXCEPT		
			{
				increment();
				return (*this);
			}
			FT_INLINE  _Self			operator++(int)	FT_NOEXCEPT		
			{
				_Self tmp(*this);

				increment();
				return (tmp);
			}
			// bidirectional iterator requirements
			FT_INLINE  _Self&			operator--()	FT_NOEXCEPT		
			{
				decrement();
				return *this;
			}
			FT_INLINE  _Self			operator--(int)	FT_NOEXCEPT		
			{
				_Self tmp(*this);

				decrement();
				return (tmp);
			}
			FT_INLINE  bool				operator==(const _Self& iter)	const FT_NOEXCEPT	{ return (mCurrent == iter.mCurrent); }
			FT_INLINE  bool				operator!=(const _Self& iter)	const FT_NOEXCEPT	{ return (mCurrent != iter.mCurrent); }
			FT_INLINE  const node_type& base()							const FT_NOEXCEPT	{ return (mCurrent); }
	};

	template <class NodeType>
	class const_bst_iterator
	{
		private:
			typedef NodeType									node_type;
			typedef const_bst_iterator<NodeType>				_Self;
		public:
			typedef NodeType									value_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t									difference_type;
			typedef	const typename node_type::value_type*		pointer;
			typedef const typename node_type::value_type&		reference;
		public:
			NodeType* 											mCurrent;
			const_bst_iterator() : mCurrent() {};
			const_bst_iterator(node_type* node) : mCurrent(node) {}
			template<typename U> // const iterator conversion
			const_bst_iterator(const const_bst_iterator<U>& it) : mCurrent(it.mCurrent) {}
			template<typename U> // const iterator conversion
			const_bst_iterator(const bst_iterator<U>& it) : mCurrent(it.mCurrent) {}
			template<typename U> // const iterator conversion
			node_type&					operator=(const const_bst_iterator<U>& it) { mCurrent = it.mCurrent; return (*this); }
			template<typename U> // const iterator conversion
			node_type&					operator=(const bst_iterator<U>& it) { mCurrent = it.mCurrent; return (*this); }
		protected:
			/** NOTE: BELOW FUNCTIONS MUST BE TESTED */
			FT_INLINE  void				increment() FT_NOEXCEPT
			{
				// find next larger element
				if (mCurrent->right)
				{
					mCurrent = mCurrent->right;
					// children is larger than previous node 
					while (mCurrent->left)
					{
						mCurrent = mCurrent->left;
					}
				}
				// children is not larger than previous node.
				else
				{
					// go to parent until parent > current
					node_type* parent = mCurrent->parent;
					while (parent && mCurrent == parent->right && parent->parent != mCurrent) // parent < current // if root case, it not works....
					{
						mCurrent = parent;
						parent = mCurrent->parent;
					}
					mCurrent = parent;
				}
			}
			FT_INLINE  void				decrement() FT_NOEXCEPT
			{
				if (mCurrent->value.first == 7)
				{
					(void) mCurrent;
					int i = 0;
					(void) i;
				}
				if (mCurrent->left) // find maximum node in subtree
				{
					if (mCurrent->left->parent != mCurrent) // end() case
					{
						mCurrent = mCurrent->right; // goto max node of tree
					}
					else
					{
						node_type* subMaxNode = mCurrent->left->maxNode();
						mCurrent = subMaxNode;
					}
				}
				else
				{
					if (!mCurrent->parent)
						return;
					// if node is left child of parent, go to parent
					while (mCurrent->parent && mCurrent == mCurrent->parent->left && mCurrent->parent->parent != mCurrent)
					{
						mCurrent = mCurrent->parent;
					}
					mCurrent = mCurrent->parent;
				}
			}
		public:
		  	// forward iterator requirements
			FT_INLINE  reference		operator*()		const FT_NOEXCEPT
			{
				return (mCurrent->value);
			}
			FT_INLINE  pointer			operator->()	const FT_NOEXCEPT
			{
				return (&(mCurrent->value));
			}
			FT_INLINE  _Self&			operator++()	FT_NOEXCEPT		
			{
				increment();
				return (*this);
			}
			FT_INLINE  _Self			operator++(int)	FT_NOEXCEPT		
			{
				_Self tmp(*this);

				increment();
				return (tmp);
			}
			// bidirectional iterator requirements
			FT_INLINE  _Self&			operator--()	FT_NOEXCEPT		
			{
				decrement();
				return *this;
			}
			FT_INLINE  _Self			operator--(int)	FT_NOEXCEPT		
			{
				_Self tmp(*this);

				decrement();
				return (tmp);
			}
			FT_INLINE  bool				operator==(const _Self& iter)	const FT_NOEXCEPT	{ return (mCurrent == iter.mCurrent); }
			FT_INLINE  bool				operator!=(const _Self& iter)	const FT_NOEXCEPT	{ return (mCurrent != iter.mCurrent); }
			FT_INLINE  const node_type& base()							const FT_NOEXCEPT	{ return (mCurrent); }
	};
}

/** bidrection iterator */
namespace ft
{
	template <class Iter>
	class bidirectional_iterator
	{
		private:
			Iter mCurrent;
			typedef bidirectional_iterator<Iter>								_Self;
		public:
			typedef Iter														iterator_type;
			typedef typename std::bidirectional_iterator_tag					iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type				value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type			difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer					pointer;
			typedef typename ft::iterator_traits<Iter>::reference				reference;
		public:
			bidirectional_iterator() : mCurrent() {};
			bidirectional_iterator(const Iter& it) : mCurrent(it) {}
			template<typename U> // const iterator conversion
			bidirectional_iterator(const bidirectional_iterator<U>& it) : mCurrent(it.base()) {}
			template<typename U> // const iterator conversion
			iterator_type&				operator=(const bidirectional_iterator<U>& it) { mCurrent = it.base(); return (*this); }
		public:
		  	// forward iterator requirements
			FT_INLINE  reference		operator*()		const FT_NOEXCEPT		{ return (*mCurrent); }
			FT_INLINE  pointer			operator->()	const FT_NOEXCEPT		{ return (mCurrent); }
			FT_INLINE  _Self&			operator++()	FT_NOEXCEPT				{ ++mCurrent; return (*this); }
			FT_INLINE  _Self			operator++(int)	FT_NOEXCEPT				{ return (_Self(mCurrent++)); }
			// bidirectional iterator requirements
			FT_INLINE  _Self&			operator--()	FT_NOEXCEPT				{ --mCurrent; return *this; }
			FT_INLINE  _Self			operator--(int)	FT_NOEXCEPT				{ return (_Self(mCurrent--)); }
			FT_INLINE  bool				operator==(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent == iter.mCurrent); }
			FT_INLINE  bool				operator!=(const _Self& iter)			const FT_NOEXCEPT	{ return (mCurrent != iter.mCurrent); }
			FT_INLINE  const Iter& 		base()									const FT_NOEXCEPT	{ return (mCurrent); }
	};
}


#endif
