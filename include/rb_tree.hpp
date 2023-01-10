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
				mHeader(), mCurrentSize(0), mAllocator(Allocator()), mCompare()
			{
				mHeader = getNode();
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
				link_type node = mAllocator.allocate(1);

				node->left = NULL;
				node->right = NULL;
				node->parent = NULL;
				return (node);
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
				link_type node = (--hint).mCurrent;
				
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
					return (findNodeParent(++iterator(root()), val)); // find from root
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
				link_type granParent;

				if (u && u->color == RED)
				{
					node->parent->color = BLACK;
					u->color = BLACK;
					granParent = grandparent(node);
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
				link_type newNode = getNode();
				link_type parent = mHeader;

				newNode->color = BLACK;
				newNode->value = value;
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
				link_type newNode = getNode();
				link_type parent = findNodeParent(hint, value);

				newNode->color = RED;
				newNode->value = value;
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
			link_type bstDelete(link_type node)
			{
				if (node == NULL)
					return (NULL);
				if (isLeaf(node)) // just delete node...
				{
					if (node == root())
					{
						mHeader->parent = NULL;
						mHeader->left = NULL;
						mHeader->right = NULL;
						node->color = RED; // leaf root case doesn't care in rb_tree deletion
					}
					else
					{
						if (node->parent->left == node)
						{
							node->parent->left = NULL;
						}
						else
						{
							node->parent->right = NULL;
						}
					}
					return (node);
				}
				else // swap
				{
					link_type swapNode;

					if (node->right)
						swapNode = node->right.minNode();
					else
						swapNode = node->left->maxNode();
					node->value = swapNode->value; // swap
					return (bstDelete(swapNode));
				}
			}
			bool isBlack(link_type node)
			{
				return (!node || node->color == BLACK);
			}
			void delCase1(link_type node)
			{
				if (node->color == RED)
				{
					destroy(node);
					return ;
				}
			}
			void delCase2(link_type node)
			{
				link_type sib = sibling(node);
				if (sib->color == RED) // parent is black
				{
					sib->color = BLACK;
					node->parent->color = RED;
					if (node == node->parent->left)
						rotateLeft(node->parent);
					else
						rotateRight(node->parent);
				}
				delCase3(node);
			}
			void delCase3(link_type node)
			{
				link_type sib = sibling(node);
				if (sib->color == BLACK && node->parent->color == BLACK && isBlack(sib->left) && isBlack(sib->right))
				{
					sib->color = RED;
					delCase1(node->parent);
				}
				else
					delCase4(node);
			}
			void delCase4(link_type node)
			{
				link_type sib = sibling(node);
				if (node->parent == RED && sib->color == BLACK && isBlack(sib->left) && isBlack(sib->right))
				{
					node->parent->color = RED;
				}
				else
					delCase5(node);
			}
			void delCase5(link_type node)
			{
				link_type sib = sibling(node);
				if (sib->color == BLACK)
				{
					if (node == node->parent->left && isBlack(sib->left) && !isBlack(sib->right))
					{
						sib->color = RED;
						sib->right.color = BLACK;
						rotateRight(sib);
					}
					else if (node == node->parent->right && isBlack(sib->left) && !isBlack(sib->right))
					{
						sib->color = RED;
						sib->right.color = BLACK;
						rotateLeft(sib);
					}
				}
				delCase6(node);
			}
			void delCase6(link_type node)
			{
				link_type sib = sibling(node);
				
				sib->color = node->parent->color;
				node->parent->color = BLACK;
				
				if (node == node->parent->left)
				{
					sib->right.color = BLACK;
					rotateLeft(node->parent);
				}
				else
				{
					sib->left->color = BLACK;
					rotateRight(node->parent);
				}
			}
			// delete node and rebalance
			// https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea
			void eraseRebalance(link_type node)
			{
				node = bstDelete(node); // this node always leaf node
				delCase1(node);
				if (size())
				{
					mHeader->left = root()->minNode();
					mHeader->right = root()->maxNode();
				}
				else
				{
					mHeader->left = NULL;
					mHeader->right = NULL;
					mHeader->parent = NULL;
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
				mCurrentSize = 0;
			}
			ft::pair<iterator, bool>				insert(const value_type& value)
			{
				if (size())
					return (insertUnique(++iterator(root()), value));
				else
					return (insertRoot(value));
			}
			// ignore hint
			iterator								insert(iterator hint, const value_type& value)
			{
				if (!size())
					insertRoot(value);
				else
					insertUnique(hint, value);
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
						return (const_iterator(node));
					}
				}
				return (end());
			}
	};
}

#endif
