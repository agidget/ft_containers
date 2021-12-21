#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

# define RED '1'
# define BLACK '2'

namespace ft
{
	template <class T>
	struct noConst
	{
		typedef T type;
	};
	template <class T>
	struct noConst<const T>
	{
		typedef T type;
	};

	template <class T>
	class node
	{
	public:

		char	color;
		bool	nil;
		T		*value;
		node*	left;
		node*	right;
		node*	p;

		node(T *value = nullptr) : color(RED), nil(false), value(value),
								left(nullptr), right(nullptr), p(nullptr) {}
		node(const node& other)
		{
			this->color = other.color;
			this->nil = other.nil;
			this->value = other.value;
			this->left = other.left;
			this->right = other.right;
			this->p = other.p;
		}
		node& operator=(const node& other)
		{
			this->color = other.color;
			this->nil = other.nil;
			this->value = other.value;
			this->left = other.left;
			this->right = other.right;
			this->p = other.p;
			return *this;
		}
		~node() {}
	};

	template <class iter>
	class rbTreeIterator
	{
		typedef node<typename ft::noConst<iter>::type >*	node_pnt;
		node_pnt			_iter;

	public:

		typedef iter												iterator_type;
		typedef typename iterator_traits<iter*>::difference_type	difference_type;
		typedef typename iterator_traits<iter*>::value_type			value_type;
		typedef typename iterator_traits<iter*>::pointer			pointer;
		typedef typename iterator_traits<iter*>::reference			reference;
		typedef std::bidirectional_iterator_tag						iterator_category;

		explicit rbTreeIterator(node_pnt it = nullptr) : _iter(it) {}
		rbTreeIterator(const rbTreeIterator<typename ft::noConst<value_type>::type >& it)
		{
			this->_iter = it.base();
		}
		~rbTreeIterator() {}
		rbTreeIterator& operator=(const rbTreeIterator<typename ft::noConst<value_type>::type >& other)
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
			if (_iter->right && _iter->right->nil == false)
				_iter = treeMin(_iter->right);
			else
			{
				node_pnt y = _iter->p;
				while (y && y->nil == false && _iter == y->right)
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

			++(*this);
			return tmp;
		}
		rbTreeIterator& operator--()
		{
			if (_iter->left && _iter->left->nil == false)
				_iter = treeMax(_iter->left);
			else
			{
				node_pnt y = _iter->p;
				while (y && y->nil == false && _iter == y->left)
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

			--(*this);
			return tmp;
		}

	private:

		node_pnt treeMin(node_pnt x)
		{
			while (x->left && x->left->nil == false)
				x = x->left;
			return x;
		}
		node_pnt treeMax(node_pnt x)
		{
			while (x->right && x->right->nil == false)
				x = x->right;
			return x;
		}
	};

	template <class A, class B>
	bool operator==(const rbTreeIterator<A>& lhs,
					const rbTreeIterator<B>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class A, class B>
	bool operator!=(const rbTreeIterator<A>& lhs,
					const rbTreeIterator<B>& rhs)
	{
		return lhs.base() != rhs.base();
	}
}

#endif