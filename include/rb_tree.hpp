#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include <cstddef>
#include <memory>

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
			key_compare		mCompare;
		public:
			_rb_tree() : 
				mHeader(), mCurrentSize(0), mAllocator(std::allocator<value_type>()), mCompare()
			{
				mHeader = getNode();
				mCompare = key_compare();
			}
			_rb_tree(const _Self& other) : 
				mHeader(), mCurrentSize(other.size()), mAllocator(other.mAllocator), mCompare()
			{
				*this = other;
			}
			_rb_tree(key_compare comp, allocator_type& alloc) : 
				mHeader(), mCurrentSize(0), mAllocator(alloc), mCompare(comp)
			{
				mHeader = getNode();
			}
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
			link_type	findNodeParent(iterator hint, const value_type& val)
			{
				link_type node = (--hint).base();
				
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
						return (mHeader);
					}
				}
				if (hint != begin())
					return (++begin(), val); // find from root
			}
			// TODO: UNDERSTAND THIS CODE!!!
			static void rotateLeft(_Self* node)
			{
				_Self* child = node->right;
				_Self* parent = node->parent;

				if (child->left != NULL)
					child->left->parent = node;

				node->right = child->left;
				node->parent = child;
				child->left = node;
				child->parent = parent;

				if (parent != NULL)
				{
					if (parent->left == node)
						parent->left = child;
					else
						parent->right = child;
				}
			}
			static void rotateRight(_Self* node)
			{
				_Self* child = node->left;
				_Self* parent = node->parent;

				if (child->right != NULL)
					child->right->parent = node;

				node->left = child->right;
				node->parent = child;
				child->right = node;
				child->parent = parent;

				if (parent != NULL)
				{
					if (parent->right == node)
						parent->right = child;
					else
						parent->left = child;
				}
			}
			link_type grandparent(link_type node)
			{
				if ((node != NULL) && (node->parent != NULL))
					return (node->parent->parent);
				else
					return (NULL);
			}
			link_type uncle(link_type node)
			{
				link_type grandParent = grandparent(node);
				if (grandParent == NULL)
					return (NULL); // No grandparent means no uncle
				if (node->parent == grandParent->left)
					return (grandParent->right);
				else
					return (grandParent->left);
			}
			link_type sibling(link_type node)
			{
				if (node == node->parent->left)
					return node->parent->right;
				else
					return node->parent->left;
			}
			// case 1 if parent is root
			ft::pair<iterator, bool> insertCase1(link_type node)
			{
				if (node->parent == mHeader)
					return (ft::pair<iterator, bool>(iterator(node), true));
				insertCase2(node);
			}
			// case 2 if parent is black
			ft::pair<iterator, bool> insertCase2(link_type node)
			{
				if (node->parent->color == BLACK)
					return (ft::pair<iterator, bool>(iterator(node), true));
				insertCase3(node);
			}
			// case 3 if parent is red and uncle is red
			ft::pair<iterator, bool> insertCase3(link_type node)
			{
				link_type uncle = uncle(node);
				link_type granParent;

				if (uncle && uncle->color == RED)
				{
					node->parent->color = BLACK;
					uncle->color = BLACK;
					granParent = grandparent(node);
					granParent->color = RED;
					insert_case1(granParent);
				}
				else
				{
					insertCase4(node);
				}
			}
			// case 4 if parent is red and uncle is black
			ft::pair<iterator, bool> insertCase4(link_type node)
			{
				link_type *grandParent = grandparent(node);

				if ((node == node->parent->right) && (node->parent == grandParent->left))
				{
					rotate_left(node->parent);
					node = node->left;
				}
				else if ((node == node->parent->left) && (node->parent == grandParent->right))
				{
					rotate_right(node->parent);
					node = node->right;
				}
				insertCase5(node);
			}
			// case 5 if parent is right of grand parent -> left rotaion
			ft::pair<iterator, bool> insertCase5(link_type node)
			{
				link_type grandParent = grandparent(node);

				node->parent->color = BLACK;
				grandParent->color = RED;
				if (node == node->parent->left)
					rotateRight(grandParent);
				else
					rotateLeft(grandParent);
			}
			// insertion node
			ft::pair<iterator, bool> insertUnique(iterator hint, const value_type& value)
			{
				// first, add node to leaf node
				link_type newNode = getNode(hint);
				link_type parent = findNodeParent(value);

				newNode->color = RED;
				newNode->value = value;
				newNode->parent = parent;
				if (parent == mHeader || key_compare(parent->value, value)) // root case or left child
					parent->left = newNode;
				else // right child
					parent->right = newNode;
				return (insertCase1(newNode));
			}
			bool isLeaf(link_type node) { return (!node->left && !node->right); }
			void replaceNode(link_type node, link_type child)
			{
				child->parent = node->parent;
				if (node->parent == mHeader)
					node->parent->parent = child; // set to root
				else if (node->parent->left == node)
					node->parent->left = child;
				else if (node->parent ->right == node)
					node->parent->right = child;
			}
			// delete node and rebalance
			// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
			void eraseRebalance(iterator pos)
			{
				link_type node = pos.base();

				if (!node->left && !node->right) // node is leaf
				{
					if (node == root())
					{
						mHeader->parent = NULL;
						mHeader->left = NULL;
						mHeader->right = NULL;
					}
					else if (node->parent->left == node)
					{
						node->parent->left = NULL;
					}
					else
					{
						node->parent->right = NULL;
					}
					destroy(node);
					--mCurrentSize;
					return ;
				}
				else
				{
					
				}
			}
		public:
			//  iterators
			iterator								begin()		FT_NOEXCEPT			{ return (iterator(leftMost())); }
			const_iterator							begin()		const FT_NOEXCEPT	{ return (const_iterator(leftMost())); }
			iterator								end()		FT_NOEXCEPT			{ return (iterator(mHeader)); }
			const_iterator							end()		const FT_NOEXCEPT	{ return (iterator(mHeader)); }
			reverse_iterator						rbegin()	FT_NOEXCEPT			{ return (reverse_iterator(end())); }
			const_reverse_iterator					rbegin()	const FT_NOEXCEPT	{ return (const_reverse_iterator(end())); }
			reverse_iterator						rend()		FT_NOEXCEPT			{ return (reverse_iterator(begin())); }
			const_reverse_iterator					rend()		const FT_NOEXCEPT	{ return (const_reverse_iterator(begin())); }
			//  capacity
			FT_INLINE bool							empty()		const FT_NOEXCEPT	{ return (mCurrentSize == 0); }
			FT_INLINE size_type						size()		const FT_NOEXCEPT	{ return (mCurrentSize); }
			//  modifiers
			void									clear()
			{
				mCurrentSize = 0;
			}
			ft::pair<iterator, bool>				insert(const value_type& value)
			{
				return (insertUnique(++root(), value));
			}
			// ignore hint
			iterator								insert(iterator hint, const value_type& value)
			{
				insertUnique(hint, value);
			}
			template< class InputIt >
			void									insert(InputIt first, InputIt last)
			{
				for (; first != last; ++first)
				{
					insertUnique(++root(), *first);
				}
			}
			void									erase(iterator pos)
			{
				eraseRebalance(pos);
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
				if (find(key) == end())
					return (0);
				else
					return (1);
			}
			iterator								find(const Key& key)
			{
				link_type node = root();

				if (node == mHeader)
					return (end());
				while (node)
				{
					if (key_compare(key, node->value.first)) // key < node
					{
						node = node->left;
					}
					else if (key_compare(node->value.first, key)) // key > node
					{
						node = node->right;
					}
					else
					{
						return (iterator(node));
					}
				}
				return (end());
			}
			const_iterator							find(const Key& key) const
			{
				link_type node = root();

				if (node == mHeader)
					return (end());
				while (node)
				{
					if (key_compare(key, node->value.first)) // key < node
					{
						node = node->left;
					}
					else if (key_compare(node->value.first, key)) // key > node
					{
						node = node->right;
					}
					else
					{
						return (const_iterator(node));
					}
				}
				return (end());
			}
	};
}

#endif