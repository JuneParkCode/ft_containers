#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include <cstddef>

namespace ft
{
	enum _rb_tree_color { RED, BLACK };

	template <class T>
	class _rb_tree_node
	{
		private:
			typedef _rb_tree_node<T>	_Self;
		public:
			T							value;
			_Self*						parent;
			_Self*						left;
			_Self						right;
			_rb_tree_color				color;
		public:
			_rb_tree_node():
				 value(), parent(0), left(0), right(0), color(RED) {} 
			_rb_tree_node(const T& value):
				 value(value), parent(0), left(0), right(0), color(RED) {} 
			_rb_tree_node(const _Self& node)
				: value(node.value), parent(node.parent), left(node.left), right(node.right), color(node.color) {}
			~_rb_tree_node(){}
			_Self& operator=(const _Self& node)
			{
				value = node.value;
				parent = node.parent;
				left = node.left;
				right = node.right;
				color = node.color;
			}
			_Self*	minNode()
			{
				_Self* node = this;
				while (node->left)
				{
					node = node->left;
				}
				return (node);
			}
			_Self*	maxNode()
			{
				_Self* node = this;
				while (node->right)
				{
					node = node->right;
				}
				return (node);
			}
	};

	template <class Key, class Value, class Compare, class Allocator>
	class _rb_tree
	{
		private:
			typedef ft::pair<Key, Value>							value_type;
			typedef Key												key_type;
			typedef Value											mapped_type;
			typedef std::size_t						 				size_type;
			typedef _rb_tree_node<value_type>						node_type;
			typedef bst_iterator<node_type>							iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef const_bst_iterator<node_type>					const_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef node_type*										link_type;
			typedef _rb_tree<Key, Value, Compare, Allocator>		_Self;
		private:
			link_type		mHeader;
			size_type		mCurrentSize;
			allocator_type	mAllocator;
		private:
			void destroy(link_type node)
			{
				~(*node);
				putNode(node);
			}
			link_type	getNode()
			{
				return (mAllocator.allocate(1));
			}
			allocator_type	getAllocator()
			{
				return (mAllocator);
			}
			void		putNode(link_type node)
			{
				mAllocator.deallocate(node, 1);
			}
			link_type	root()
			{
				return (mHeader->parent);
			}
			link_type	leftMost()
			{
				return (mHeader->left);
			}
			link_type	rightMost()
			{
				return (mHeader->right);
			}
			link_type	findNodePosition(const value_type& val)
			{
				link_type node = root();
				
				while (node)
				{
					if (key_compare(val, node->first))
					{
						if (node->left)
							node = node->left;
						else
							return (node);
					}
					else if (key_compare(node->first, val))
					{
						if (node->right)
							node = node->right;
						else
							return (node);
					}
					else
					{
						return (NULL);
					}
				}
			}
			link_type grandparent(link_type n)
			{
				if ((n != NULL) && (n->parent != NULL))
					return n->parent->parent;
				else
					return NULL;
			}
			link_type uncle(link_type n)
			{
				link_type g = grandparent(n);
				if (g == NULL)
					return NULL; // No grandparent means no uncle
				if (n->parent == g->left)
					return g->right;
				else
					return g->left;
			}
			ft::pair<iterator, bool> insert_unique(const value_type& value)
			{
			}
		public:
			_rb_tree();
			_rb_tree(const _Self& other);
			_rb_tree(key_compare comp, allocator_type& alloc);
		public:
			//  iterators
			iterator								begin()		FT_NOEXCEPT							{ return (iterator(leftMost())); }
			const_iterator							begin()		const FT_NOEXCEPT					{ return (const_iterator(leftMost())); }
			iterator								end()		FT_NOEXCEPT							{ return (iterator(mHeader)); }
			const_iterator							end()		const FT_NOEXCEPT					{ return (iterator(mHeader)); }
			reverse_iterator						rbegin()	FT_NOEXCEPT							{ return (reverse_iterator(end())); }
			const_reverse_iterator					rbegin()	const FT_NOEXCEPT					{ return (const_reverse_iterator(end())); }
			reverse_iterator						rend()		FT_NOEXCEPT							{ return (reverse_iterator(begin())); }
			const_reverse_iterator					rend()		const FT_NOEXCEPT					{ return (const_reverse_iterator(begin())); }
			//  capacity
			FT_INLINE bool							empty()		const FT_NOEXCEPT					{ return (mCurrentSize == 0); }
			FT_INLINE size_type						size()		const FT_NOEXCEPT					{ return (mCurrentSize); }
			//  modifiers
			void									clear()
			{
				mCurrentSize = 0;
			}
			ft::pair<iterator, bool>				insert(const value_type& value)
			{
				link_type node = findNodePosition(value);
				if (node == NULL) // has equal content
					return (ft::pair<iterator, bool>(iterator(value), false));
				return (insert_unique(value));
			}
			// ignore hint
			iterator								insert(iterator hint, const value_type& value)
			{
				(void) hint;
				insert(value);
			}
			template< class InputIt >
			void									insert(InputIt first, InputIt last)
			{
				for (; first != last; ++first)
				{
					insert(*first);
				}
			}
			void									erase(iterator pos)
			{
				link_type node = &(*pos);
				// TODO
			}
			void									erase(iterator first, iterator last)
			{
				for (; first != last; ++first)
				{
					erase(first);
				}
			}
			size_type								erase(const Key& key)
			{
				iterator it = find(key);

				if (it == end())
					return (0);
				erasse(it);
				return (1);
			}
			void									swap(_Self& other)
			{
				allocator_type tempAloc = mAllocator;
				link_type tempHead = mHeader;
				size_type tempSize = mCurrentSize;
				// swap to this
				mAllocator = other.mAllocator;
				mHeader = other.mHeader;
				mCurrentSize = other.mCurrentSize;
				// swap to other
				other.mAllocator = tempAloc;
				other.mHeader = tempHead;
				other.mCurrentSize = tempSize;
			}
			//  lookup
			size_type								count(const Key& key) const
			{
			}
			iterator								find(const Key& key)
			{
			}
			const_iterator							find(const Key& key) const
			{
			}
	};
}

#endif