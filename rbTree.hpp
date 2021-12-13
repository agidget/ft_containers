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

		typedef T											value_type;
		typedef Compare										value_compare;
		typedef A											allocator_type;

		typedef typename A::template rebind<node<T>>::other	node_allocator;
		typedef typename node_allocator::pointer			node_pointer;

		typedef typename A::pointer							pointer;
		typedef typename A::const_pointer					const_pointer;
		typedef typename A::reference						reference;
		typedef typename A::const_reference					const_reference;
		typedef typename A::size_type						size_type;
		typedef typename A::difference_type					difference_type;

		typedef rbTreeIterator<pointer>						iterator;
		typedef rbTreeIterator<const_pointer>				const_iterator;

	};
}

#endif