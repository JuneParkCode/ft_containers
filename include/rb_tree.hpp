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
			_Self*						lChild;
			_Self						rChild;
			_rb_tree_color				color;
		public:
			_rb_tree_node():
				 value(), parent(0), lChild(0), rChild(0), color(RED) {} 
			_rb_tree_node(const T& value):
				 value(value), parent(0), lChild(0), rChild(0), color(RED) {} 
			_rb_tree_node(const _Self& node)
				: value(node.value), parent(node.parent), lChild(node.lChild), rChild(node.rChild), color(node.color) {}
			_Self& operator=(const _Self& node)
			{
				value = node.value;
				parent = node.parent;
				lChild = node.lChild;
				rChild = node.rChild;
				color = node.color;
			}
	};
}

#endif