#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <iterator>
# include <cstddef>
# include "type_traits.hpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	//for iterator type
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	//for pointers
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	//for const pointers
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};



	//reverse_iterator
	template <class Iterator>
	class reverse_iterator : public iterator<
											typename iterator_traits<Iterator>::iterator_category,
											typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference>
	{
	public:

		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::pointer			pointer;
		typedef typename iterator_traits<Iterator>::reference		reference;

	protected:

		Iterator	current;

	public:

		typedef Iterator											iterator_type;

		reverse_iterator() : current() {}
		explicit reverse_iterator(Iterator it) : current(it) {}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& it)
		{
			this->current = it.base();
		}

		//member functions

		Iterator base() const
		{
			return current;
		}
		reference operator*() const
		{
			iterator_type	tmp;

			tmp = current;
			--tmp;
			return *tmp;
		}
		pointer operator->() const
		{
			return &**this;
		}
		reverse_iterator& operator++()
		{
			--current;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);

			--current;
			return tmp;
		}
		reverse_iterator& operator--()
		{
			++current;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);

			++current;
			return tmp;
		}
		reverse_iterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}
		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	//non-member overloads for reverse_iterator

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	};
}

#endif