#include "ft_stl_util.hpp"
#include "ft_config.hpp"
#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Tp>
	struct comp
	{
		inline const Tp& operator()(const Tp& __x) const
		{
			return __x;
		}
	};
	template <class T, class Compare = std::less<T>,  class Allocator = std::allocator<T> >
	class set
	{
private:
			typedef set<T, Compare, Allocator>						_Self;
		public:
			typedef T												data_type;
			typedef T												value_type;
			typedef T												key_type;
			typedef Compare											key_compare;
			typedef _rb_tree<value_type, value_type,
						ft::comp<value_type>,
						key_compare, Allocator>						tree_type;
			typedef typename tree_type::size_type			 		size_type;
			typedef typename tree_type::difference_type				difference_type;
			typedef Allocator										allocator_type;
			typedef typename tree_type::reference					reference;
			typedef typename tree_type::const_reference				const_reference;
			typedef typename tree_type::reference					pointer;
			typedef typename tree_type::const_reference				const_pointer;
			//  iterator types
			typedef typename tree_type::iterator					iterator;
			typedef typename tree_type::reverse_iterator			reverse_iterator;
			typedef typename tree_type::const_iterator				const_iterator;
			typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;
		private:
			tree_type		mTree;
		public:
			//  constructors
			set():
				mTree()
			{
			}
			explicit set(const Compare& comp, const Allocator& alloc = Allocator()):
				mTree(comp, alloc)
			{
			}
			set(const set& other):
				mTree(other.mTree)
			{
			}
			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()):
				mTree(first, last, comp, alloc)
			{
			}
			set& operator=(const set& other)
			{
				this->mTree = other.mTree;
				return (*this);
			}
			allocator_type&							getAllocator() const	{ return (mTree.getAllocator()); }
		public:
			//  iterators
			iterator								begin()		FT_NOEXCEPT							{ return (mTree.begin()); }
			const_iterator							begin()		const FT_NOEXCEPT					{ return (mTree.begin()); }
			iterator								end()		FT_NOEXCEPT							{ return (mTree.end()); }
			const_iterator							end()		const FT_NOEXCEPT					{ return (mTree.end()); }
			reverse_iterator						rbegin()	FT_NOEXCEPT							{ return (reverse_iterator(mTree.end())); }
			const_reverse_iterator					rbegin()	const FT_NOEXCEPT					{ return (const_reverse_iterator(mTree.end())); }
			reverse_iterator						rend()		FT_NOEXCEPT							{ return (reverse_iterator(mTree.begin())); }
			const_reverse_iterator					rend()		const FT_NOEXCEPT					{ return (const_reverse_iterator(mTree.begin())); }
			//  capacity
			FT_INLINE bool							empty()		const FT_NOEXCEPT					{ return (mTree.empty()); }
			FT_INLINE size_type						size()		const FT_NOEXCEPT					{ return (mTree.size()); }
			FT_INLINE size_type						max_size()	const FT_NOEXCEPT					{ return (std::min(size_type(-1) / sizeof(value_type), (size_type)std::numeric_limits<difference_type>::max())); }
			//  modifiers
			void									clear()											{ mTree.clear(); }
			ft::pair<iterator, bool>				insert(const value_type& value)					{ return (mTree.insert(value)); }
			iterator								insert(iterator hint, const value_type& value)	{ return (mTree.insert(hint, value));	}
			template< class InputIt >
			void									insert(InputIt first, InputIt last)				{ mTree.insert(first, last); }
			void									erase(iterator pos)								{ mTree.erase(pos); }
			void									erase(iterator first, iterator last)			{ mTree.erase(first, last); }
			size_type								erase(const key_type& key)						{ return (mTree.erase(key)); }
			void									swap(set& other)								{ mTree.swap(other.mTree); }
			//  lookup
			size_type								count(const key_type& key) const				{ return (mTree.count(key)); }
			iterator								find(const key_type& key)						{ return (mTree.find(key)); }
			const_iterator							find(const key_type& key) const					{ return (mTree.find(key)); }
			ft::pair<iterator,iterator>				equal_range(const key_type& key)				{ return (mTree.equal_range(key));}
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& key) const			{ return (mTree.equal_range(key));}
			iterator								lower_bound(const key_type& key)				{ return (mTree.lower_bound(key));}
			const_iterator							lower_bound(const key_type& key) const			{ return (mTree.lower_bound(key));}
			iterator								upper_bound(const key_type& key)				{ return (mTree.upper_bound(key));}
			const_iterator							upper_bound(const key_type& key) const			{ return (mTree.upper_bound(key));}
			//  observers
			key_compare								key_comp() const								{ return (mTree.key_comp());}
			Compare 								value_comp() const								{ return (value_compare(mTree.key_comp()));}
			bool									isRbTree()  {return (mTree.isRbTree()); }
	};
	template <class T, class Compare, class Alloc>
	bool operator==(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		if (lhs.empty() && rhs.empty())
			return (true);
		else if (lhs.empty() || rhs.empty())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Compare, class Alloc>
	bool operator!=(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		if (lhs.empty() && rhs.empty())
			return (false);
		else if (lhs.empty() || rhs.empty())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Compare, class Alloc>
	bool operator<(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Compare, class Alloc>
	bool operator<=(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator>(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator>=(const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}