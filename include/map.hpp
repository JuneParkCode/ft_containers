
#include <algorithm>
#include <stdexcept>
#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include "rb_tree.hpp"


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,  class Allocator = std::allocator<_rb_tree_node<ft::pair<const Key, T> > > >
	class map
	{
		private:
			typedef map<Key, T, Compare, Allocator>					_Self;
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef T												data_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef _rb_tree<Key, value_type,
						ft::_Select1st<value_type>,
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
			//  member class 
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Allocator>;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return (comp(lhs.first, rhs.first)); }
			};
		public:
			//  constructors
			map():
				mTree()
			{
			}
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()):
				mTree(comp, alloc)
			{
			}
			map(const map& other):
				mTree(other.mTree)
			{
			}
			template <class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()):
				mTree(first, last, comp, alloc)
			{
			}
			map& operator=(const map& other)
			{
				this->mTree = other.mTree;
				return (*this);
			}
			allocator_type&							getAllocator() const	{ return (mTree.getAllocator()); }
		public:
			//  element access
			mapped_type&								operator[](const Key& key)	FT_NOEXCEPT
			{
				iterator pos = mTree.find(key);
				
				if (pos == end())
					return ((insert(value_type(key, mapped_type())).first)->second);
				return ((*pos).second);
			}
			// at throws out of bound
			mapped_type&							at(const Key& key)
			{
				iterator pos = mTree.find(key);
				
				if (pos == end())
					throw (std::out_of_range("out of range at : map::at()\n"));
				return ((*pos).second);
			}
			const mapped_type&						at(const Key& key) const
			{
				const_iterator pos = mTree.find(key);
				
				if (pos == end())
					throw (std::out_of_range("out of range at : map::at()\n"));
				return (*(*pos).seconds);
			}
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
			//  modifiers
			void									clear()											{ mTree.clear(); }
			ft::pair<iterator, bool>				insert(const value_type& value)					{ return (mTree.insert(value)); }
			iterator								insert(iterator hint, const value_type& value)	{ return (mTree.insert(hint, value));	}
			template< class InputIt >
			void									insert(InputIt first, InputIt last)				{ mTree.insert(first, last); }
			void									erase(iterator pos)								{ mTree.erase(pos); }
			void									erase(iterator first, iterator last)			{ mTree.erase(first, last); }
			size_type								erase(const Key& key)							{ return (mTree.erase(key)); }
			void									swap(map& other)								{ mTree.swap(other.mTree); }
			//  lookup
			size_type								count(const Key& key) const						{ return (mTree.count(key)); }
			iterator								find(const Key& key)							{ return (mTree.find(key)); }
			const_iterator							find(const Key& key) const						{ return (mTree.find(key)); }
			ft::pair<iterator,iterator>				equal_range(const Key& key);
			ft::pair<const_iterator,const_iterator>	equal_range(const Key& key) const;
			iterator								lower_bound(const Key& key);
			const_iterator							lower_bound(const Key& key) const;
			iterator								upper_bound(const Key& key);
			const_iterator							upper_bound(const Key& key) const;
			//  observers
			key_compare								key_comp() const;
			map::value_compare 						value_comp() const;
			bool									isRbTree()  {return (mTree.isRbTree()); }
	};
}
