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
		T		*value; //maybe need pointer for the key here??
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
		node& operator=(const node& other) // { *this = other; return *this; }
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
			// std::cout << "lol\n";
			if (_iter->right && _iter->right->nil == false) // && _iter->right->nil == false) // && _iter->right->right->nil == false)
			{
				// std::cout << "lol2\n";
				_iter = treeMin(_iter->right);
				// std::cout << "lol3\n";
			}
			else
			{
				node_pnt y = _iter->p;
				while (y != NULL && y->nil == false && _iter == y->right)
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
				while (y != NULL && y->nil == false && _iter == y->left)
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
		// rbTreeIterator& operator++() {
		// 	if (_iter->right && !_iter->right->nil) {
		// 		_iter = treeMin(_iter->right);
		// 	}
		// 	else {
		// 		node_pnt y = _iter->p;
		// 		while (y != NULL && _iter == y->right) {
		// 			_iter = y;
		// 			y = y->p;
		// 		}
		// 		_iter = y;
		// 	}
		// 	return *this;
		// }

		// rbTreeIterator operator++(int) {
		// 	rbTreeIterator<value_type> temp = *this;
		// 	if (!_iter->right->nil) {
		// 		_iter = treeMin(_iter->right);
		// 	}
		// 	else {
		// 		node_pnt y = _iter->p;
		// 		while (y != NULL && _iter == y->right) {
		// 			_iter = y;
		// 			y = y->p;
		// 		}
		// 		_iter = y;
		// 	}
		// 	return temp;
		// }

		// rbTreeIterator& operator--() {
		// 	if (_iter->left && !_iter->left->nil) {
		// 		_iter = treeMax(_iter->left);
		// 	}
		// 	else {
		// 		node_pnt y = _iter->p;
		// 		while (y != NULL && _iter == y->left) {
		// 			_iter = y;
		// 			y = y->p;
		// 		}
		// 		_iter = y;
		// 	}
		// 	return *this;
		// }

		// rbTreeIterator operator--(int) {
		// 	rbTreeIterator<value_type> temp = *this;
		// 	if (_iter->left && !_iter->left->nil) {
		// 		_iter = treeMax(_iter->left);
		// 	}
		// 	else {
		// 		node_pnt y = _iter->p;
		// 		while (y != NULL && _iter == y->left) {
		// 			_iter = y;
		// 			y = y->p;
		// 		}
		// 		_iter = y;
		// 	}
		// 	return temp;
		// }

	private:

		node_pnt treeMin(node_pnt x)
		{
			// std::cout << "min: " << *x->value << std::endl;
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







// namespace ft{

// 	template<class T> struct remove_const { typedef T type; };

// 	template<class T> struct remove_const <const T> { typedef T type; };

// 	template<class Value>
// 	struct node{
// 		//typedef node*			pointer;
// 		public:
// 		explicit node(Value *srcval = 0) :	value(srcval),
// 											p(0),
// 											left(0),
// 											right(0),
// 											color(RED),
// 											nil(0){}
		
// 		Value	*value;
// 		node*	p;
// 		node*	left;
// 		node*	right;	
// 		char	color;
// 		bool	nil;

// 		node( node const & other) {
// 			this->color = other.color;
// 			this->value = other.value;
// 			this->p = other.p;
// 			this->nil = other.nil;
// 			this->right = other.right;
// 			this->left = other.left;
// 		};

// 		node& operator=(const node& other){
// 			this->color = other.color;
// 			this->value = other.value;
// 			this->nil = other.nil;
// 			this->p = other.p;
// 			this->right = other.right;
// 			this->left = other.left;
// 			return *this;
// 		}	
// 		virtual ~node(){}
// 	};

// 	template<typename T>
// 	class rbTreeIterator {
// 		public:
// 			typedef std::bidirectional_iterator_tag 					iterator_category;
// 			typedef typename ft::iterator_traits<T*>::value_type 		value_type;
// 			typedef typename ft::iterator_traits<T*>::reference 		reference;
// 			typedef typename ft::iterator_traits<T*>::pointer			pointer;
// 			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
// 			typedef node<typename ft::remove_const<value_type>::type >* node_pointer;

// 			//typedef node<T>* node_pointer;

// 		private:
// 			node_pointer _node;

// 			node_pointer tree_min(node_pointer n) const {
// 				while(n->left != NULL && !n->left->nil)
// 					n = n->left;
// 				return n;
// 			}

// 			node_pointer tree_max(node_pointer n) const {
// 				while (!n->right->nil)
// 					n = n->right;
// 				return n;
// 			}

// 		public:
// 			rbTreeIterator() {}

// 			rbTreeIterator(void *node): _node(static_cast<node_pointer>(node)) {}

// 			rbTreeIterator(const rbTreeIterator<typename ft::remove_const<value_type>::type > & other)//: _node(other.node()) {}
// 			{
// 				*this = other;
// 			}

// 			rbTreeIterator& operator=(const rbTreeIterator<typename ft::remove_const<value_type>::type>& other) {
// 				this->_node = other.base();
// 				return *this;
// 			}

// 			reference operator*() const {
// 				return *(_node->value);
// 			}

// 			pointer operator->() const {
// 				return _node->value;
// 			}

// 			rbTreeIterator& operator++() {
// 				if (_node->right && !_node->right->nil) {
// 					_node = tree_min(_node->right);
// 				}
// 				else {
// 					node_pointer y = _node->p;
// 					while (y != NULL && _node == y->right) {
// 						_node = y;
// 						y = y->p;
// 					}
// 					_node = y;
// 				}
// 				return *this;
// 			}

// 			rbTreeIterator operator++(int) {
// 				rbTreeIterator<value_type> temp = *this;
// 				if (!_node->right->nil) {
// 					_node = tree_min(_node->right);
// 				}
// 				else {
// 					node_pointer y = _node->p;
// 					while (y != NULL && _node == y->right) {
// 						_node = y;
// 						y = y->p;
// 					}
// 					_node = y;
// 				}
// 				return temp;
// 			}

// 			rbTreeIterator& operator--() {
// 				if (_node->left && !_node->left->nil) {
// 					_node = tree_max(_node->left);
// 				}
// 				else {
// 					node_pointer y = _node->p;
// 					while (y != NULL && _node == y->left) {
// 						_node = y;
// 						y = y->p;
// 					}
// 					_node = y;
// 				}
// 				return *this;
// 			}

// 			rbTreeIterator operator--(int) {
// 				rbTreeIterator<value_type> temp = *this;
// 				if (_node->left && !_node->left->nil) {
// 					_node = tree_max(_node->left);
// 				}
// 				else {
// 					node_pointer y = _node->p;
// 					while (y != NULL && _node == y->left) {
// 						_node = y;
// 						y = y->p;
// 					}
// 					_node = y;
// 				}
// 				return temp;
// 			}

// 			node_pointer base() const {
// 				return _node;
// 			}
// 		};	

// 	template<typename A, typename B>
// 	bool operator==(const rbTreeIterator<A> & lhs, const rbTreeIterator<B> & rhs){
// 			return (lhs.base() == rhs.base());
// 		}

// 	template<typename A, typename B>
// 	bool operator!=(const rbTreeIterator<A> & lhs, const rbTreeIterator<B> & rhs){
// 			return (lhs.base() != rhs.base());
// 		}
// }

#endif