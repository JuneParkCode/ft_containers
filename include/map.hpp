
#include <algorithm>
#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,  class Allocator = std::allocator<std::pair<const Key, T>>>
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<key_type, mapped_type>					value_type;
			typedef std::size_t						 				size_type;
			typedef _rb_tree_node<T>								node_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			/** iterator types */
			typedef bst_iterator<node_type>							iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef const_bst_iterator<node_type>					const_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			node_type*		root;
			allocator_type	mAllocator;
		public:
			/** member class */
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return (comp(lhs.first, rhs.first)); }
			};
		public:
			/** constructors */
			map();
			explicit map(const Compare& comp, const Allocator& alloc = Allocator());
			map(const map& other);
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
			map& operator=(const map& other);
			allocator_type&	getAllocator() const	{ return (mAllocator); }
		public:
			/** element access  */
			reference					operator[](const Key& key);
			// at throws out of bound
			reference					at(const Key& key);
			const_reference				at(const Key& key) const;
			/** iterators  */
			iterator					begin()		FT_NOEXCEPT;
			const_iterator				begin()		const FT_NOEXCEPT;
			iterator					end()		FT_NOEXCEPT;
			const_iterator				end()		const FT_NOEXCEPT;
			reverse_iterator			rbegin()	FT_NOEXCEPT;
			const_reverse_iterator		rbegin()	const FT_NOEXCEPT;
			reverse_iterator			rend()		FT_NOEXCEPT;
			const_reverse_iterator		rend()		const FT_NOEXCEPT;
			/** capacity  */
			FT_INLINE bool				empty()		const FT_NOEXCEPT;
			FT_INLINE size_type			size()		const FT_NOEXCEPT;
			/** modifiers */
			void						clear();
			ft::pair<iterator, bool>	insert(const value_type& value);
			iterator					insert(iterator pos, const value_type& value);
			template< class InputIt >
			void						insert(InputIt first, InputIt last);
			void						erase(iterator pos);
			void						erase(iterator first, iterator last);
			size_type					erase(const Key& key);
			void						swap(map& other);
			/** lookup */
			size_type								count(const Key& key) const;
			iterator								find(const Key& key);
			const_iterator							find(const Key& key) const;
			ft::pair<iterator,iterator>				equal_range(const Key& key);
			ft::pair<const_iterator,const_iterator>	equal_range(const Key& key) const;
			iterator								lower_bound(const Key& key);
			const_iterator							lower_bound(const Key& key) const;
			iterator								upper_bound(const Key& key);
			const_iterator							upper_bound(const Key& key) const;
			/** observers */
			key_compare					key_comp() const;
			map::value_compare 			value_comp() const;
	};
}