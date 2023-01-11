#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include <cstddef>
#include <memory>
#include <iostream>
#include <set>

namespace ft
{
	enum _rb_tree_color { RED, BLACK };

	template <class T>
	class _rb_tree_node
	{
		private:
			typedef _rb_tree_node<T>	_Self;
		public:
			typedef T					value_type;
			T							value;
			_Self*						parent;
			_Self*						left;
			_Self*						right;
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
				if (node == NULL)
					return (NULL);
				while (node->left)
				{
					node = node->left;
				}
				return (node);
			}
			_Self*	maxNode()
			{
				_Self* node = this;
				if (node == NULL)
					return (NULL);
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
		public:
			typedef Key												key_type;
			typedef Value											value_type;
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
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;

		private:
			link_type		mHeader;
			size_type		mCurrentSize;
			allocator_type	mAllocator;
			key_compare		mCompare;
		public:
			_rb_tree() : 
				mHeader(), mCurrentSize(0), mAllocator(Allocator()), mCompare()
			{
				mHeader = getNode();
			}
			_rb_tree(const _Self& other) : 
				mHeader(), mCurrentSize(other.size()), mAllocator(other.mAllocator), mCompare()
			{
				mHeader = getNode();
				*this = other;
			}
			_rb_tree(key_compare comp, allocator_type& alloc) : 
				mHeader(), mCurrentSize(0), mAllocator(alloc), mCompare(comp)
			{
				mHeader = getNode();
			}
			template <class InputIt>
			_rb_tree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()):
				mHeader(), mCurrentSize(0), mAllocator(alloc), mCompare(comp)
			{
				mHeader = getNode();
				for (; first != last; ++first)
				{
					insert(*first);
				}
			}
			_rb_tree& operator=(const _rb_tree& other)
			{
				mAllocator = other.mAllocator;
				mCompare = other.mCompare;
				if (size())
					clear();
				for (_Self::const_iterator it = other.begin(); it != other.end(); ++it)
				{
					insert(*it);
				}
				return (*this);
			}
			~_rb_tree()
			{
				clear();
				destroy(mHeader);
			}
		private:
			void check(link_type node, bool& res, std::set<int>& path)
			{
				if (node == NULL)
					return;
				if (res == false)
					return ;
				if (node->parent->color == RED && node->color == RED)
				{
					res = false;
					return ;	
				}
				if (node->left == NULL || node->right == NULL)
				{
					// calculate black node numbers to go there..
					int pathBlack = 0;
					link_type temp = node;
					while (temp != mHeader)
					{
						pathBlack += (temp->color == BLACK);
						temp = temp->parent;
					}
					path.insert(pathBlack);
					if (path.size() > 1)
					{
						res = false;
						return ;
					}
				}
				check(node->left, res, path);
				check(node->right, res, path);
			}
			void destroy(link_type node)
			{
				node->~node_type();
				putNode(node);
			}
			link_type	getNode()
			{
				link_type node = mAllocator.allocate(1);

				node->left = NULL;
				node->right = NULL;
				node->parent = NULL;
				return (node);
			}
			link_type	createNode(const value_type& value)
			{
				link_type tmp = getNode();
				try
				{
					new (tmp) value_type(value);
				}
				catch (...)
				{
					putNode(tmp);
				}
				return (tmp);
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
			link_type	leftMost() const
			{
				return (mHeader->left);
			}
			link_type	rightMost() const
			{
				return (mHeader->right);
			}
			link_type	findNodeParent(iterator hint, const value_type& val)
			{
				link_type node = hint.mCurrent->parent == mHeader ? root() : hint.mCurrent->parent;
				
				while (node)
				{
					if (mCompare(val.first, node->value.first)) // val < node
					{
						if (node->left)
							node = node->left;
						else
							return (node);
					}
					else if (mCompare(node->value.first, val.first)) // val > node
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
				if (hint.mCurrent != root())
					return (findNodeParent(iterator(root()), val)); // find from root
				return (mHeader);
			}
			// TODO: UNDERSTAND THIS CODE!!!
			void rotateLeft(link_type node)
			{
				link_type child = node->right;
				link_type parent = node->parent;

				if (child->left != NULL)
					child->left->parent = node;

				node->right = child->left;
				node->parent = child;
				child->left = node;
				child->parent = parent;

				if (parent == mHeader)
					mHeader->parent = child;
				else if (parent != NULL)
				{
					if (parent->left == node)
						parent->left = child;
					else
						parent->right = child;
				}
			}
			void rotateRight(link_type node)
			{
				link_type child = node->left;
				link_type parent = node->parent;

				if (child->right != NULL)
					child->right->parent = node;

				node->left = child->right;
				node->parent = child;
				child->right = node;
				child->parent = parent;

				if (parent == mHeader)
					mHeader->parent = child;
				else if (parent != NULL)
				{
					if (parent->right == node)
						parent->right = child;
					else
						parent->left = child;
				}
			}
			link_type grandparent(link_type node)
			{
				if ((node != NULL) && (node->parent != NULL) && (node->parent != mHeader))
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
				if (node->parent == mHeader)
					return (NULL);
				else if (node == node->parent->left)
					return node->parent->right;
				else
					return node->parent->left;
			}
			// case 1 if node is root -> just exit
			ft::pair<iterator, bool> insertCase1(link_type node)
			{
				if (node->parent == mHeader) // is root
				{
					mHeader->left = root()->minNode();
					mHeader->right = root()->maxNode();
					node->color = BLACK;
					return (ft::pair<iterator, bool>(iterator(node), true));
				}
				return (insertCase2(node));
			}
			// case 2 if parent is black -> just exit
			ft::pair<iterator, bool> insertCase2(link_type node)
			{
				if (node->parent->color == BLACK)
				{
					mHeader->left = root()->minNode();
					mHeader->right = root()->maxNode();
					return (ft::pair<iterator, bool>(iterator(node), true));
				}
				return (insertCase3(node));
			}
			// case 3 if parent is red and uncle is red
			ft::pair<iterator, bool> insertCase3(link_type node)
			{
				link_type u = uncle(node);

				if (u && u->color == RED)
				{
					link_type granParent = grandparent(node);
					node->parent->color = BLACK;
					u->color = BLACK;
					granParent->color = RED;
					return (insertCase1(granParent));
				}
				else
				{
					return (insertCase4(node));
				}
			}
			// case 4 if parent is red and uncle is black
			ft::pair<iterator, bool> insertCase4(link_type node)
			{
				link_type grandParent = grandparent(node);

				if ((node == node->parent->right) && (node->parent == grandParent->left))
				{
					rotateLeft(node->parent);
					node = node->left;
				}
				else if ((node == node->parent->left) && (node->parent == grandParent->right))
				{
					rotateRight(node->parent);
					node = node->right;
				}
				return (insertCase5(node));
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
				mHeader->left = root()->minNode();
				mHeader->right = root()->maxNode();
				return (ft::pair<iterator, bool>(iterator(node), true));
			}
			ft::pair<iterator, bool> insertRoot(const value_type& value)
			{
				link_type newNode = createNode(value);
				link_type parent = mHeader;

				newNode->color = BLACK;
				newNode->parent = parent;
				mHeader->parent = newNode;
				mHeader->left = newNode;
				mHeader->right = newNode;
				++mCurrentSize;
				return (ft::pair<iterator, bool>(iterator(newNode), true));
			}
			// insertion node
			ft::pair<iterator, bool> insertUnique(iterator hint, const value_type& value)
			{
				iterator findPos;
				if ((findPos = find(value.first)) != end())
					return (ft::pair<iterator, bool>(findPos, false));
				// first, add node to leaf node
				link_type newNode = createNode(value);
				link_type parent = findNodeParent(iterator(hint), value);

				newNode->color = RED;
				newNode->parent = parent;
				++mCurrentSize;
				if (mCompare(parent->value.first, value.first)) // node < parent
					parent->right = newNode;
				else // right child
					parent->left = newNode;
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

			bool isBlack(link_type node)
			{
				return (!node || node->color == BLACK);
			}
			// delete node and rebalance
			// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
			void eraseRebalance(link_type node)
			{
				// node is delete target.
				(void) node;
			}
			void clearTree(link_type root)
			{
				if (root == NULL || root == mHeader)
					return ;
				clearTree(root->left);
				clearTree(root->right);
				if (isLeaf(root))
				{
					if (root->parent && root->parent != mHeader)
					{
						link_type&	parentChildPointer = root->parent->left == root ? root->parent->left : root->parent->right;
						parentChildPointer = NULL;
					}
					destroy(root);
				}
			}
		public:
			//  iterators
			iterator								begin()		FT_NOEXCEPT			{ return (size() ? iterator(leftMost()) : end()); }
			const_iterator							begin()		const FT_NOEXCEPT	{ return (size() ? const_iterator(leftMost()) : end()); }
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
				if (!size())
					return ;
				clearTree(root());
				mHeader->parent = NULL;
				mHeader->left = NULL;
				mHeader->right = NULL;
				mCurrentSize = 0;
			}
			ft::pair<iterator, bool>				insert(const value_type& value)
			{
				if (size())
					return (insertUnique(iterator(root()), value));
				else
					return (insertRoot(value));
			}
			// ignore hint
			iterator								insert(iterator hint, const value_type& value)
			{
				if (!size())
					return (insertRoot(value).first);
				else
					return (insertUnique(hint, value).first);
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
				eraseRebalance(pos.mCurrent);
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
				erase(it);
				return (1);
			}
			void									swap(_Self& other)
			{
				allocator_type tempAloc = mAllocator;
				link_type tempHead = mHeader;
				size_type tempSize = mCurrentSize;
				key_compare tempComp = mCompare;
				// swap to this
				mAllocator = other.mAllocator;
				mHeader = other.mHeader;
				mCurrentSize = other.mCurrentSize;
				mCompare = other.mCompare;
				// swap to other
				other.mAllocator = tempAloc;
				other.mHeader = tempHead;
				other.mCurrentSize = tempSize;
				other.mCompare = tempComp;
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
					if (mCompare(key, node->value.first)) // key < node
					{
						node = node->left;
					}
					else if (mCompare(node->value.first, key)) // key > node
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
				link_type node = mHeader->parent;

				if (node == mHeader)
					return (end());
				while (node)
				{
					if (mCompare(key, node->value.first)) // key < node
					{
						node = node->left;
					}
					else if (mCompare(node->value.first, key)) // key > node
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
			bool isRbTree()
			{
				if (size() == 0)
					return (true);
				if (root()->color == RED)
					return (false);
				bool res = true;
				std::set<int> path;
				std::cout << "HEADER ADDRESS : " << mHeader << " : ";
				check(root(), res, path);
				return (res);
			}
	};
}

#endif
