#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

# define RED '1'
# define BLACK '2'

namespace ft
{
	template <class T>
	class node
	{
	public:

		// typedef class node<T>	node_type;
		// typedef class node<T>*	node_pnt;
		// typedef T				value_type;

		char	color;
		bool	nil;
		T		value; //maybe need pointer for the key here??
		node*	left;
		node*	right;
		node*	p;

		node(T value = (T)0)
		{
			this->color = RED;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
			this->p = nullptr;
			char nil = false;
		}
		~node() {};
	};

	template <class iter>
	class rbTreeIterator
	{
		typedef node<iter>*	node_pnt;
		node_pnt			_iter;

	public:

		typedef iter											iterator_type;
		typedef typename iterator_traits<iter>::difference_type	difference_type;
		typedef typename iterator_traits<iter>::value_type		value_type;
		typedef typename iterator_traits<iter>::pointer			pointer;
		typedef typename iterator_traits<iter>::reference		reference;
		typedef std::bidirectional_iterator_tag					iterator_category;

		rbTreeIterator(_iter it = nullptr) : _iter(it) {}
		template <class U>
		rbTreeIterator(const rbTreeIterator<U>& it) { this->_iter = it.base(); }
		~rbTreeIterator() {}
		rbTreeIterator& operator=(const rbTreeIterator& other)
		{
			_iter = other.base();
			return *this;
		}

		node_pnt base() const
		{
			return _iter;
		}
		reference operator*() const
		{
			return *_iter->value;
		}
		pointer operator->() const
		{
			return &**this;
		}
		rbTreeIterator& operator++()
		{
			if (_iter->right->nil == false)
				_iter = tree_min(_iter->right);
			else
			{
				node_pnt y = _iter->p;
				while (y->nil == false && _iter == y->right)
				{
					_iter = y;
					y = y->p;
				}
				_iter = y;
			}
			return *this;
		}
		rbTreeIterator operator++(int)
		{
			rbTreeIterator tmp(*this);

			// if (_iter->right->nil == false)
			// 	_iter = tree_min(_iter->right);
			// else
			// {
			// 	node_pnt y = _iter->p;
			// 	while (y->nil == false && _iter == y->right)
			// 	{
			// 		_iter = y;
			// 		y = y->p;
			// 	}
			// 	_iter = y;
			// }
			++(*this);
			return tmp;
		}
		rbTreeIterator& operator--()
		{
			if (_iter->left->nil == false)
				_iter = tree_max(_iter->left);
			else
			{
				node_pnt y = _iter->p;
				while (y->nil == false && _iter == y->left)
				{
					_iter = y;
					y = y->p;
				}
				_iter = y;
			}
			return *this;
		}
		rbTreeIterator operator--(int)
		{
			rbTreeIterator tmp(*this);

			// if (_iter->left->nil == false)
			// 	_iter = tree_max(_iter->left);
			// else
			// {
			// 	node_pnt y = _iter->p;
			// 	while (y->nil == false && _iter == y->left)
			// 	{
			// 		_iter = y;
			// 		y = y->p;
			// 	}
			// 	_iter = y;
			// }
			--(*this);
			return tmp;
		}

	private:

		node_pnt tree_min(node_pnt x)
		{
			while (x->left->nil == false)
				x = x->left;
			return x;
		}
		node_pnt tree_max(node_pnt x)
		{
			while (x->right->nil == false)
				x = x->right;
			return x;
		}
	};

	template <class Iterator>
	bool operator==(const rbTreeIterator<Iterator>& lhs,
					const rbTreeIterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator>
	bool operator!=(const rbTreeIterator<Iterator>& lhs,
					const rbTreeIterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
}

#endif