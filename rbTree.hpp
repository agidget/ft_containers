#ifndef rbTree_HPP
# define rbTree_HPP

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

		typedef rbTreeIterator<value_type>						iterator;
		typedef rbTreeIterator<const value_type>				const_iterator;
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

		//Coplien form
		explicit rbTree(const Compare &comp,
						const allocator_type& alloc = allocator_type()) :
			_val_alloc(alloc), _node_alloc(node_allocator()), _comp(comp), _size(0)
		{
			initStart();
		}
		template <class InputIterator>
		rbTree(InputIterator first, InputIterator last,
				const Compare& comp = value_compare(), const A& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
			_val_alloc(alloc), _node_alloc(node_allocator()), _comp(comp), _size(0)
		{
			initStart();
			insert(first, last);
		}
		rbTree(const rbTree& other) :
			_val_alloc(other._val_alloc), _comp(other._comp), _root(nullptr)
		{
			*this = other;
		}
		rbTree& operator= (const rbTree& other)
		{
			node_pointer	maxNode;

			if (this != &other)
			{
				if (_root)
					clearAll(_root);
				else
					initStart();
				_val_alloc = other._val_alloc;
				_node_alloc = node_allocator();
				_comp = other._comp;

				if (other._root != other._end)
					_root = copyTree(other._root, other._nil, other._end, _nil);
				_size = other._size;
				_nil->left = treeMin(_root);
				_nil->right = treeMax(_root);
				_nil->p = _root;
				maxNode = treeMax(_root);
				maxNode->right = _end;
				_end->p = maxNode;
			}
			return *this;
		}
		~rbTree()
		{
			clearAll(_root);
			_val_alloc.destroy(_end->value);
			_val_alloc.deallocate(_end->value, 1);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			_node_alloc.destroy(_nil);
			_node_alloc.deallocate(_nil, 1);
			_size = 0; 
		}

		//member functions

		//iterators

		iterator begin()
		{
			if (_size)
				return iterator(treeMin(_root));
			return iterator(_end);
		}
		const_iterator begin() const
		{
			if (_size)
				return const_iterator(treeMin(_root));
			return const_iterator(_end);
		}
		iterator end()
		{
			return iterator(_end);
		}
		const_iterator end() const
		{
			return const_iterator(_end);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//capacity

		bool empty() const
		{
			return _size == 0;
		}
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _node_alloc.max_size();
		}
		allocator_type get_allocator() const
		{
			return _val_alloc;
		}

		//modifiers

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			node_pointer	newNode;
			node_pointer	maxNode;
			node_pointer	minNode;

			newNode = treeSearch(val);
			if (newNode)
				return ft::pair<iterator, bool>(iterator(newNode), false);
			newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, node<T>());
			newNode->value = _val_alloc.allocate(1);
			_val_alloc.construct(newNode->value, val);
			newNode->left = _nil;
			newNode->right = _nil;
			rbInsert(newNode);
			_size++;
			_nil->left = treeMin(_root);
			_nil->right = treeMax(_root);
			_nil->p = _root;
			if (_size != 1)
			{
				maxNode = treeMax(_root);
				minNode = treeMin(_root);
			}
			else
			{
				maxNode = _root;
				minNode = _root;
			}
			maxNode->right = _end;
			_end->p = maxNode;
			_nil->right = maxNode;
			_nil->left = minNode;
			return ft::pair<iterator, bool>(iterator(newNode), true);
		}
		iterator insert(iterator position, const value_type& val)
		{
			node_pointer	newNode;
			node_pointer	maxNode;
			node_pointer	minNode;
			iterator		pos;

			pos = position;
			newNode = treeSearch(val);
			if (newNode)
				return iterator(newNode);
			newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, node<T>());
			newNode->value = _val_alloc.allocate(1);
			_val_alloc.construct(newNode->value, val);
			newNode->left = _nil;
			newNode->right = _nil;
			rbInsert(newNode);
			_size++;
			_nil->p = _root;
			if (_size != 1)
			{
				maxNode = treeMax(_root);
				minNode = treeMin(_root);
			}
			else
			{
				maxNode = _root;
				minNode = _root;
			}
			maxNode->right = _end;
			_end->p = maxNode;
			_nil->right = maxNode;
			_nil->left = minNode;
			return iterator(newNode);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			for (; first != last; first++)
				insert(*first);
		}

		void erase(iterator position)
		{
			node_pointer	del;
			node_pointer	tmp;
			node_pointer	maxNode;
			node_pointer	minNode;

			del = position.base();
			tmp = del;
			rbDelete(del);
			clearNode(tmp);
			_size--;
			if (_size == 0)
				_root = _end;
			else
			{
				if (_size != 1)
				{
					maxNode = treeMax(_root);
					minNode = treeMin(_root);
				}
				else
				{
					maxNode = _root;
					minNode = _root;
				}
				maxNode->right = _end;
				_end->p = maxNode;
				_nil->right = maxNode;
				_nil->left = minNode;
			}
		}
		size_type erase(const value_type& val)
		{
			node_pointer	node;

			node = treeSearch(val);
			if (node)
			{
				erase(iterator(node));
				return 1;
			}
			return 0;
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap(rbTree& x)
		{
			ft::swap(_val_alloc, x._val_alloc);
			ft::swap(_node_alloc, x._node_alloc);
			ft::swap(_comp, x._comp);
			ft::swap(_root, x._root);
			ft::swap(_nil, x._nil);
			ft::swap(_end, x._end);
			ft::swap(_size, x._size);
		}
		void clear()
		{
			clearAll(_root);
			_root = _end;
			_end->left = _nil;
			_end->right = _nil;
			_end->p = _nil;
			_size = 0;
		}

		//observer

		value_compare value_comp() const
		{
			return _comp;
		}

		//operations

		iterator find(const value_type& val)
		{
			node_pointer	x;

			x = treeSearch(val);
			return  x != NULL ? iterator(x) : end();
		}
		const_iterator find(const value_type& val) const
		{
			node_pointer	x;

			x = treeSearch(val);
			return  x != NULL ? const_iterator(x) : end();
		}
		size_type count(const value_type& val) const
		{
			node_pointer	x;

			x = treeSearch(val);
			return  x != NULL ? 1 : 0;
		}
		iterator lower_bound(const value_type& val)
		{
			node_pointer	x;
			node_pointer	res;

			x = _root;
			res = _end;
			while (!isNil(x))
			{
				if (!_comp(*x->value, val))
				{
					res = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(res);
		}
		const_iterator lower_bound(const value_type& val) const
		{
			node_pointer	x;
			node_pointer	res;

			x = _root;
			res = _end;
			while (!isNil(x))
			{
				if (!_comp(*x->value, val))
				{
					res = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(res);
		}
		iterator upper_bound(const value_type& val)
		{
			node_pointer	x;
			node_pointer	res;

			x = _root;
			res = _end;
			while (!isNil(x))
			{
				if (_comp(val, *x->value))
				{
					res = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(res);
		}
		const_iterator upper_bound(const value_type& val) const
		{
			node_pointer	x;
			node_pointer	res;

			x = _root;
			res = _end;
			while (!isNil(x))
			{
				if (_comp(val, *x->value))
				{
					res = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(res);
		}
		ft::pair<iterator, iterator> equal_range(const value_type& val)
		{
			ft::pair<iterator, iterator>	pair;

			pair.first = lower_bound(val);
			pair.second = upper_bound(val);
			return pair;
		}
		ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
		{
			ft::pair<const_iterator, const_iterator>	pair;

			pair.first = lower_bound(val);
			pair.second = upper_bound(val);
			return pair;
		}

	//my methods (helpers)
	private:

		node_pointer treeMin(node_pointer x) const
		{
			while (x && !isNil(x->left) && x != x->left)
				x = x->left;
			return x;
		}
		node_pointer treeMax(node_pointer x) const
		{
			while (x && !isNil(x->right) && x != x->right)
				x = x->right;
			return x;
		}
		void leftRotation(node_pointer x)
		{
			node_pointer y;
			
			y = x->right;
			x->right = y->left;
			if (!isNil(y->left))
				y->left->p = x;
			y->p = x->p;
			if (!x->p)
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
			if (!isNil(y->right))
				y->right->p = x;
			y->p = x->p;
			if (!x->p)
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

			if (_root == _end)
				_root = z;
			else
			{
				y = _nil;
				x = _root;
				while (!isNil(x))
				{
					y = x;
					if (_comp(*z->value, *x->value))
						x = x->left;
					else
						x = x->right;
				}
				z->p = y;
				if (isNil(y))
					_root = z;
				else if (_comp(*z->value, *y->value))
					y->left = z;
				else
					y->right = z;
				z->left = _nil;
				z->right = _nil;
				z->color = RED;
			}
			rbInsertFix(z);
		}
		void rbInsertFix(node_pointer z)
		{
			node_pointer y; //uncle

			while (z != _root && z->p->color == RED)
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
		void initStart()
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
		void rbTransplant(node_pointer u, node_pointer v)
		{
			if (u == _root)
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

			origColor = z->color;
			if (isNil(z->left))
			{
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (isNil(z->right))
			{
				x = z->left;
				rbTransplant(z, z->left);
			}
			else
			{
				y = treeMin(z->right);
				origColor = y->color;
				x = y->right;
				if (y->p != z)
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

			while (x != _root && x->color == BLACK)
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
					else
					{
						//case 3 (uncle is BLACK, left child is RED, right child is BLACK)
						if (w->right->color == BLACK)
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
					else
					{
						//case 7 (uncle is BLACK, left child is BLACK, right child is RED)
						if (w->left->color == BLACK)
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
				}
			}
			x->color = BLACK;
		}
		node_pointer treeSearch(const value_type& val) const
		{
			node_pointer	x;

			x = _root;
			while (x && !isNil(x) && (_comp(*x->value, val) || _comp(val, *x->value)))
			{
				if (_comp(val, *x->value))
					x = x->left;
				else
					x = x->right;
			}
			if (!x || isNil(x))
				return NULL;
			return x;
		}

		void clearNode(node_pointer x)
		{
			_val_alloc.destroy(x->value);
			_val_alloc.deallocate(x->value, 1);
			_node_alloc.destroy(x);
			_node_alloc.deallocate(x, 1);
		}
		void clearAll(node_pointer	node)
		{
			if (!isNil(node))
			{
				if (!isNil(node->right))
					clearAll(node->right);
				if (!isNil(node->left))
					clearAll(node->left);
				clearNode(node);
			}
		}
		node_pointer copynode(node_pointer copy)
		{
			node_pointer	newNode;

			newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, node<T>());
			if (copy->value)
			{
				newNode->value = _val_alloc.allocate(1);
				_val_alloc.construct(newNode->value, *copy->value);
			}
			newNode->color = copy->color;
			newNode->nil = copy->nil;
			return newNode;
		}
		node_pointer copyTree(node_pointer copy, node_pointer copyNil,
								node_pointer copyEnd, node_pointer p)
		{
			node_pointer	newNode;

			newNode = copynode(copy);
			newNode->p = p;
			if (copy->left != copyNil)
				newNode->left = copyTree(copy->left, copyNil, copyEnd, newNode);
			else
				newNode->left = _nil;
			if (copy->right != copyEnd && copy->right != copyNil)
				newNode->right = copyTree(copy->right, copyNil, copyEnd, newNode);
			else if (copy->right == copyEnd)
				newNode->right = _end;
			else if (copy->right == copyNil)
				newNode->right = _nil;
			return newNode;
		}
		bool isNil(node_pointer node) const
		{
			return node == _nil || node == _end;
		}
	};
		
	template <class T, class Compare, class Alloc>
	bool operator==(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator<(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end());
	}

	template <class T, class Compare, class Alloc>
	bool operator>(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(const rbTree<T, Compare, Alloc>& lhs,
					const rbTree<T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Compare, class Alloc>
	void swap(rbTree<T, Compare, Alloc>& x, rbTree<T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}


#endif