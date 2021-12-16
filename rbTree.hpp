#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include "iterator.hpp"
# include "rbTreeIterator.hpp"
# include "utility.hpp"
# include "algorithm.hpp"
# include <memory>

namespace ft
{
	template <class T, class Compare = std::less<T>,
				class A = std::allocator<T> >
	class rbTree
	{
	public:

		typedef T												value_type;
		typedef Compare											value_compare;
		typedef A												allocator_type;

		typedef typename A::template rebind< node<T> >::other	node_allocator;
		typedef typename node_allocator::pointer				node_pointer;

		typedef typename A::pointer								pointer;
		typedef typename A::const_pointer						const_pointer;
		typedef typename A::reference							reference;
		typedef typename A::const_reference						const_reference;
		typedef typename A::size_type							size_type;
		typedef typename A::difference_type						difference_type;

		// typedef rbTreeIterator<pointer>							iterator;
		// typedef rbTreeIterator<const_pointer>					const_iterator;
		typedef rbTreeIterator<T>								iterator;
		typedef rbTreeIterator<const T>							const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:

		allocator_type	_val_alloc;
		node_allocator	_node_alloc;
		value_compare	_comp;
		node_pointer	_root;
		node_pointer	_nil;
		node_pointer	_end;		
		size_type		_size;

	public:

		//delete
		T getRoot()
		{
			return *_root->value;
		}

		//Coplien form
		explicit rbTree(const Compare &comp = value_compare(),
						const allocator_type& alloc = allocator_type()) :
			_val_alloc(alloc), _node_alloc(node_allocator()), _comp(comp), _size(0)
		{
			_nil = _node_alloc.allocate(1);
			_node_alloc.construct(_nil, node<T>());
			_nil->color = BLACK;
			_nil->nil = true;
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, node<T>());
			_end->value = _val_alloc.allocate(1);
			_val_alloc.construct(_end->value, value_type());
			_end->color = BLACK;
			_end->left = _nil;
			_end->right = _nil;
			_root = _end;
		}
		~rbTree()
		{
			clear(); 
		}

		//member functions
		iterator begin()
		{
			if (_size)
				return iterator(treeMin(_root));
			return iterator(_end);
		}
		// const_iterator begin() const
		// {
		// 	return const_iterator(treeMin(_root));
		// }
		//FIXME
		iterator end()
		{
			return iterator(_end);
		}
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			node_pointer	newNode;
			node_pointer	maxNode;

			if (_size == 0)
				return ft::pair<iterator, bool>(init_root(val), true);
			newNode = treeSearch(val);
			if (newNode != _nil && newNode != _end)
				return ft::pair<iterator, bool>(iterator(newNode), false);
			newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, node<T>());
			newNode->value = _val_alloc.allocate(1);
			_val_alloc.construct(newNode->value, val);
			rbInsert(newNode);
			_size++;
			_nil->left = treeMin(_root);
			_nil->right = treeMax(_root);
			_nil->p = _root;
			//changed here
			maxNode = treeMax(_root);
			maxNode->right = _end;
			_end->p = maxNode;
			return ft::pair<iterator, bool>(iterator(newNode), true);
		}
		iterator insert(iterator position, const value_type& val)
		{
			node_pointer	newNode;
			node_pointer	maxNode;

			if (_size == 0)
				return init_root(val);
			newNode = treeSearch(val);
			if (newNode != _nil && newNode != _end)
				return iterator(newNode);
			newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, node<T>());
			newNode->value = _val_alloc.allocate(1);
			_val_alloc.construct(newNode->value, val);
			rbInsert(newNode);
			_size++;
			_nil->left = treeMin(_root);
			_nil->right = treeMax(_root);
			_nil->p = _root;
			//changed here
			maxNode = treeMax(_root);
			maxNode->right = _end;
			_end->p = maxNode;
			return iterator(newNode);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			for (; first != last; first++)
				insert(*first);
		}
		void clear()
		{
			clear_all(_root);
			_val_alloc.destroy(_end->value);
			_val_alloc.deallocate(_end->value, 1);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			_node_alloc.destroy(_nil);
			_node_alloc.deallocate(_nil, 1);
			_size = 0;
		}
		iterator find(const value_type& val)
		{
			node_pointer	x;

			x = treeSearch(val);
			//FIXME maybe return just x????
			return  x != _nil ? iterator(x) : end();
		}
		size_type count(const value_type& val) const
		{
			if (treeSearch(val) != _nil && treeSearch(val) != _end)
				return 1;
			return 0;
		}
		void erase(iterator position)
		{
			node_pointer	del;
			node_pointer	tmp;
			node_pointer	maxNode;

			del = position.base();
			tmp = del;
			rbDelete(del);
			clear_node(tmp);
			_size--;
			_nil->left = treeMin(_root);
			_nil->right = treeMax(_root);
			_nil->p = _root;
			//changed here
			if (_size == 0)
				_root = _end;
			else
			{
				maxNode = treeMax(_root);
				maxNode->right = _end;
				_end->p = maxNode;
			}
		}
		size_type erase(const value_type& val)
		{
			node_pointer	node;

			node = treeSearch(val);
			if (node != _nil && node != _end)
			{
				erase(iterator(node));
				return 1;
			}
			return 0;
		}
		void erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				erase(first);
		}

	//my methods (helpers)
	private:

		node_pointer treeMin(node_pointer x)
		{
			while (x && x->left != _nil)
				x = x->left;
			return x;
		}
		node_pointer treeMax(node_pointer x)
		{
			while (x && x->right != _end && x->right != _nil) //??????
				x = x->right;
			return x;
		}
		void leftRotation(node_pointer x)
		{
			node_pointer y;
			
			y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->p = x;
			y->p = x->p;
			if (x->p == _nil)
				_root = y;
			else if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->left = x;
			x->p = y;
		}
		void rightRotation(node_pointer x)
		{
			node_pointer y;

			y = x->left;
			x->left = y->right;
			if (y->right != _nil)
				y->right->p = x;
			y->p = x->p;
			if (x->p == _nil)
				_root = y;
			else if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->right = x;
			x->p = y;
		}
		void rbInsert(node_pointer z)
		{
			node_pointer y;
			node_pointer x;

			y = _nil;
			x = _root;
			while (x != _nil && x != _end)
			{
				y = x;
				if (_comp(*z->value, *x->value))
					x = x->left;
				else
					x = x->right;
			}
			z->p = y;
			if (y == _nil)
				_root = z;
			else if (_comp(*z->value, *y->value))
				y->left = z;
			else
				y->right = z;
			z->left = _nil;
			z->right = _nil;
			z->color = RED;
			rbInsertFix(z);
		}
		void rbInsertFix(node_pointer z)
		{
			node_pointer y; //uncle

			while (z->p->color == RED)
			{
				if (z->p == z->p->p->left)
				{
					y = z->p->p->right;
					//case 1 (uncle is RED)
					if (y->color == RED)
					{
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else 
					{
						//case 2 (uncle is BLACK, z is a RIGHT child)
						if (z == z->p->right)
						{
							z = z->p;
							leftRotation(z);
						}
						//case 3 (uncle is BLACK, z is a LEFT child)
						z->p->color = BLACK;
						z->p->p->color = RED;
						rightRotation(z->p->p);
					}
				}
				else
				{
					y = z->p->p->left;
					//case 4 (uncle is RED)
					if (y->color == RED)
					{
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else 
					{
						//case 5 (uncle is BLACK, z is a LEFT child)
						if (z == z->p->left)
						{
							z = z->p;
							rightRotation(z);
						}
						//case 6 (uncle is BLACK, z is a RIGHT child)
						z->p->color = BLACK;
						z->p->p->color = RED;
						leftRotation(z->p->p);
					}
				}
			}
			_root->color = BLACK;
		}
		iterator init_root(const value_type& val)
		{
			_root = _node_alloc.allocate(1);
			_node_alloc.construct(_root, node<T>());
			_root->value = _val_alloc.allocate(1);
			_val_alloc.construct(_root->value, val);
			_root->color = BLACK;
			_root->left = _nil;
			_root->right = _end;
			_root->p = _nil;
			_end->p = _root;
			_size++;
			return iterator(_root);
		}
		void rbTransplant(node_pointer u, node_pointer v)
		{
			if (u->p == _nil)
				_root = v;
			else if (u == u->p->left)
				u->p->left = v;
			else
				u->p->right = v;
			v->p = u->p;
		}
		void rbDelete(node_pointer z)
		{
			node_pointer	x;
			node_pointer	y;
			char			origColor;

			y = z;
			origColor = y->color;
			if (z->left == _nil)
			{
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				rbTransplant(z, z->left);
			}
			else
			{
				y = treeMin(z->right);
				origColor = y->color;
				x = y->right;
				if (y->p == z)
					x->p = y;
				else
				{
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->p = y;
				}
				rbTransplant(z, y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
			}
			if (origColor == BLACK)
				rbDeleteFix(x);
		}
		void rbDeleteFix(node_pointer x)
		{
			node_pointer	w; //uncle

			while (x != _nil && x->color == BLACK)
			{
				if (x == x->p->left)
				{
					w = x->p->right;
					//case 1 (uncle is RED)
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						leftRotation(x->p);
						w = x->p->right;
					}
					//case 2 (uncle is BLACK, his children are BLACK)
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					//case 3 (uncle is BLACK, left child is RED, right child is BLACK)
					else if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						rightRotation(w);
						w = x->p->right;
					}
					//case 4 (uncle is BLACK, right child is RED)
					w->color = x->p->color;
					x->p->color = BLACK;
					w->right->color = BLACK;
					leftRotation(x->p);
					x = _root;
				}
				else
				{
					w = x->p->left;
					//case 5 (uncle is RED)
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						rightRotation(x->p);
						w = x->p->left;
					}
					//case 6 (uncle is BLACK, his children are BLACK)
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					//case 7 (uncle is BLACK, left child is BLACK, right child is RED)
					else if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						leftRotation(w);
						w = x->p->left;
					}
					//case 8 (uncle is BLACK, left child is RED)
					w->color = x->p->color;
					x->p->color = BLACK;
					w->left->color = BLACK;
					rightRotation(x->p);
					x = _root;
				}
				x->color = BLACK;
			}
		}
		node_pointer treeSearch(const value_type& val) const
		{
			node_pointer	x;

			x = _root;
			while (x != _nil && x != _end && val != *x->value)
			{
				if (val < *x->value)
					x = x->left;
				else
					x = x->right;
			}
			return x;
		}
		void clear_node(node_pointer x)
		{
			_val_alloc.destroy(x->value);
			_val_alloc.deallocate(x->value, 1);
			_node_alloc.destroy(x);
			_node_alloc.deallocate(x, 1);
		}
		void clear_all(node_pointer	node)
		{
			if (node != _nil && node != _end)
			{
				if (node->right != _nil)
					clear_all(node->right);
				if (node->left != _nil)
					clear_all(node->left);
				clear_node(node);
			}
		}
	};
}

#endif