#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include <cstddef>
#include <memory>
#include <iostream>
#include <set>

/**
 * NOTE: NOT COMPARISION UNARY FUNCTION TEMPLATE IS NOT EQUAL WITH STD::RB_TREE!
 * REASON 1 : CAN NOT FIND KEY IF COMPARE TEMPLATE IS NOT COMPARISION (LIKE STD::PLUS, STD::MINUS ... )
 * REASON 2 : BY THE REASON 1, THAT TREE IS NOT USABLE IN MAP
 * REASON 3 : BUT, STILL IT WORKS TO SET SO, IT'S VALID TREE!!
 */

namespace ft
{
	enum _rb_tree_color { RED, BLACK };

	// select1st and select2nd are extensions: they are not part of the standard.
	template <class _Pair>
	struct _Select1st : public std::unary_function<_Pair, typename _Pair::first_type> {
	inline const typename _Pair::first_type& operator()(const _Pair& __x) const {
		return __x.first;
	}
	};

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

	template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
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
			typedef _rb_tree<Key, Value,
								 KeyOfValue, Compare, Allocator>	_Self;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;

		private:
			typedef typename allocator_type::template rebind<_rb_tree_node<value_type> >::other alloc_rebind_node;
			link_type			mHeader;
			size_type			mCurrentSize;
			allocator_type		mAllocator;
			alloc_rebind_node	mAllocatorRebind;
			key_compare			mCompare;
		public:
			_rb_tree() : 
				mHeader(), mCurrentSize(0), mAllocator(Allocator()), mAllocatorRebind(), mCompare()
			{
				mHeader = getNode();
			}
			_rb_tree(const _Self& other) : 
				mHeader(), mCurrentSize(other.size()), mAllocator(other.mAllocator), mAllocatorRebind(other.mAllocatorRebind), mCompare()
			{
				mHeader = getNode();
				*this = other;
			}
			_rb_tree(key_compare comp, allocator_type& alloc) : 
				mHeader(), mCurrentSize(0), mAllocator(alloc), mAllocatorRebind(), mCompare(comp)
			{
				mHeader = getNode();
			}
			template <class InputIt>
			_rb_tree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()):
				mHeader(), mCurrentSize(0), mAllocator(alloc), mAllocatorRebind(), mCompare(comp)
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
			static const key_type& _S_key(link_type __x)	{ return KeyOfValue()(__x->value); }
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
				link_type node = mAllocatorRebind.allocate(1);

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
				mAllocatorRebind.deallocate(node, 1);
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
				link_type node = hint.mCurrent->parent == mHeader ? mHeader->parent : hint.mCurrent->parent;
				link_type parent = mHeader; // y > node

				while (node)
				{
					if (!mCompare(_S_key(node), KeyOfValue()(val))) // comp(node.key, value.key) == false
					{
						parent = node;
						node = node->left;
					}
					else
					{
						parent = node;
						node = node->right;
					}
				} 
				return (parent);
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
			bool isLeaf(link_type node) // leaf node -> not object...
			{
				return (node->left == NULL && node->right == NULL);
			}
			bool isRed(link_type node)
			{
				if (node == NULL)
					return (false);
				return (node->color == RED);
			}
			bool isBlack(link_type node)
			{
				if (node == NULL)
					return (true);
				return (node->color == BLACK);
			}
			// case 1 if node is root -> just exit
			ft::pair<iterator, bool> insertCase1(link_type node)
			{
				if (node->parent == mHeader) // is root
				{
					mHeader->left = mHeader->parent->minNode();
					mHeader->right = mHeader->parent->maxNode();
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
					mHeader->left = mHeader->parent->minNode();
					mHeader->right = mHeader->parent->maxNode();
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
				mHeader->left = mHeader->parent->minNode();
				mHeader->right = mHeader->parent->maxNode();
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
				if ((findPos = find(KeyOfValue()(value))) != end())
					return (ft::pair<iterator, bool>(findPos, false));
				// first, add node to leaf node
				link_type newNode = createNode(value);
				link_type parent = findNodeParent(iterator(hint), value);

				newNode->color = RED;
				newNode->parent = parent;
				++mCurrentSize;
				if (!mCompare(_S_key(parent), KeyOfValue()(value))) // node < parent
					parent->left = newNode;
				else // right child
					parent->right = newNode;
				return (insertCase1(newNode));
			}
			void treeRebalanceErase(link_type node)
			{
				// node is delete target
				link_type __z = node;
				link_type __y = __z;
				link_type __x = 0;
				link_type __x_parent = 0;
				
				if (__y->left == 0)     // __z has at most one non-null child. y == z.
					__x = __y->right;     // __x might be null.
				else
					if (__y->right == 0)  // __z has exactly one non-null child. y == z.
					__x = __y->left;    // __x is not null.
					else {                   // __z has two non-null children.  Set __y to
					__y = __y->right;   //   __z's successor.  __x might be null.
					while (__y->left != 0)
						__y = __y->left;
					__x = __y->right;
				}
				
				if (__y != __z) {          // relink y in place of z.  y is z's successor
					__z->left->parent = __y; 
					__y->left = __z->left;
					if (__y != __z->right) {
						__x_parent = __y->parent;
						if (__x)
							__x->parent = __y->parent;
						__y->parent->left = __x;      // __y must be a child of left
						__y->right = __z->right;
						__z->right->parent = __y;
					}
					else
						__x_parent = __y;  
					if (mHeader->parent == __z)
						mHeader->parent = __y;
					else if (__z->parent->left == __z)
						__z->parent->left = __y;
					else 
						__z->parent->right = __y;
					__y->parent = __z->parent;
					std::swap(__y->color, __z->color);
					__y = __z;
					// __y now points to node to be actually deleted
				}
				else {                        // __y == __z
					__x_parent = __y->parent;
					if (__x) __x->parent = __y->parent;   
					if (mHeader->parent == __z)
						mHeader->parent = __x;
					else
					{
						if (__z->parent->left == __z)
							__z->parent->left = __x;
						else
							__z->parent->right = __x;
					}
					if (mHeader->left == __z) 
					{
						if (__z->right == 0)        // __z->left must be null also
							mHeader->left = __z->parent;
						// makes mHeader->left == _M_header if __z == mHeader->parent
						else
							mHeader->left = __x->minNode();
					}
					if (mHeader->right == __z)  
					{
						if (__z->left == 0)         // __z->right must be null also
							mHeader->right = __z->parent;  
						// makes mHeader->right == _M_header if __z == mHeader->parent
						else                      // __x == __z->left
							mHeader->right = __x->maxNode();
					}
				}
				if (__y->color != RED)
				{ 
					while (__x != mHeader->parent && (__x == 0 || __x->color == BLACK))
					{
						if (__x == __x_parent->left)
						{
							link_type __w = __x_parent->right;
							if (__w->color == RED)
							{
								__w->color = BLACK;
								__x_parent->color = RED;
								rotateLeft(__x_parent);
								__w = __x_parent->right;
							}
							if ((__w->left == 0 || 
								__w->left->color == BLACK) &&
								(__w->right == 0 || 
								__w->right->color == BLACK))
							{
								__w->color = RED;
								__x = __x_parent;
								__x_parent = __x_parent->parent;
							}
							else
							{
								if (__w->right == 0 || __w->right->color == BLACK)
								{
									if (__w->left)
										__w->left->color = BLACK;
									__w->color = RED;
									rotateRight(__w);
									__w = __x_parent->right;
								}
								__w->color = __x_parent->color;
								__x_parent->color = BLACK;
								if (__w->right) __w->right->color = BLACK;
								rotateLeft(__x_parent);
								break;
							}
						}
						else
						{                  // same as above, with right <-> left.
							link_type __w = __x_parent->left;
							if (__w->color == RED)
							{
								__w->color = BLACK;
								__x_parent->color = RED;
								rotateRight(__x_parent);
								__w = __x_parent->left;
							}
							if ((__w->right == 0 || __w->right->color == BLACK) && (__w->left == 0 || __w->left->color == BLACK))
							{
								__w->color = RED;
								__x = __x_parent;
								__x_parent = __x_parent->parent;
							}
							else
							{
								if (__w->left == 0 || __w->left->color == BLACK)
								{
									if (__w->right)
										__w->right->color = BLACK;
									__w->color = RED;
									rotateLeft(__w);
									__w = __x_parent->left;
								}
								__w->color = __x_parent->color;
								__x_parent->color = BLACK;
								if (__w->left)
									__w->left->color = BLACK;
								rotateRight(__x_parent);
								break;
							}
						}
					}
					if (__x)
						__x->color = BLACK;
				}
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
				clearTree(mHeader->parent);
				mHeader->parent = NULL;
				mHeader->left = NULL;
				mHeader->right = NULL;
				mCurrentSize = 0;
			}
			ft::pair<iterator, bool>				insert(const value_type& value)
			{
				if (size())
					return (insertUnique(iterator(mHeader->parent), value));
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
				if (size())
				{
					treeRebalanceErase(pos.mCurrent);
					destroy(pos.mCurrent);
					--mCurrentSize;
				}
			}
			void									erase(iterator first, iterator last)
			{
				if (first == begin() && last == end())
 				   clear();
				while (first != last)
					erase(first++); // using for loop access erased object
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
				std::swap(other.mAllocator, this->mAllocator);
				std::swap(other.mHeader, this->mHeader);
				std::swap(other.mCompare, this->mCompare);
				std::swap(other.mCurrentSize, this->mCurrentSize);
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
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (!mCompare(_S_key(node), key)) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true -> not left...
					{
						node = node->right;
					}
				}
				iterator res(parent);
				return ((res == end() || mCompare(key, _S_key(parent))) ?  end() : res);
			}
			const_iterator							find(const Key& key) const
			{
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (!mCompare(_S_key(node), key)) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true
					{
						node = node->right;
					}
				}
				const_iterator res(parent);
				return ((res == end() || mCompare(key, _S_key(parent))) ?  end() : res);
			}
			iterator lower_bound(const key_type& key)
			{
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (!mCompare(_S_key(node), key)) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true
					{
						node = node->right;
					}
				}
				return (iterator(parent));
			}
			const_iterator lower_bound( const Key& key ) const
			{
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (!mCompare(_S_key(node), key)) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true
					{
						node = node->right;
					}
				}
				return (const_iterator(parent));
			}
			iterator upper_bound(const key_type& key)
			{
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (mCompare(key, _S_key(node))) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true
					{
						node = node->right;
					}
				}
				return (iterator(parent));
			}
			const_iterator upper_bound( const Key& key ) const
			{
				link_type node = mHeader->parent; // root
				link_type parent = mHeader;

				while (node)
				{
					if (mCompare(key, _S_key(node))) // comp(node, key) == false
					{
						parent = node;
						node = node->left;
					}
					else // comp(node, key) == true
					{
						node = node->right;
					}
				}
				return (const_iterator(parent));
			}
			ft::pair<iterator, iterator> equal_range(const key_type& key)
			{
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}
			Compare key_comp() const { return (mCompare); }
			/** TO VALIDATE THIS TREE IS RB TREE */
			bool isRbTree()
			{
				if (size() == 0)
					return (true);
				if (mHeader->parent->color == RED)
					return (false);
				bool res = true;
				std::set<int> path;
				std::cout << "HEADER ADDRESS : " << mHeader << " : ";
				check(mHeader->parent, res, path);
				return (res);
			}
	};
}

#endif
