#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <class iter> //iter - pointerType
	class vectorIterator
	{
		iter	_iter;

	public:

		typedef iter												iterator_type;
		typedef typename iterator_traits<iter>::difference_type		difference_type;
		typedef typename iterator_traits<iter>::value_type			value_type;
		typedef typename iterator_traits<iter>::pointer				pointer;
		typedef typename iterator_traits<iter>::reference			reference;
		typedef typename iterator_traits<iter>::iterator_category	iterator_category;

		vectorIterator(iter it = 0) : _iter(it) {}
		template <class U>
		vectorIterator(const vectorIterator<U>& it) { this->_iter = it.base(); }
		~vectorIterator() {}
		vectorIterator& operator=(const vectorIterator& other)
		{
			_iter = other.base();
			return *this;
		}

		iter base() const
		{
			return _iter;
		}
		reference operator*() const
		{
			return *_iter;
		}
		pointer operator->() const
		{
			return &**this;
		}
		vectorIterator& operator++()
		{
			++_iter;
			return *this;
		}
		vectorIterator operator++(int)
		{
			vectorIterator tmp(*this);

			++_iter;
			return tmp;
		}
		vectorIterator& operator--()
		{
			--_iter;
			return *this;
		}
		vectorIterator operator--(int)
		{
			vectorIterator tmp(*this);

			--_iter;
			return tmp;
		}
		vectorIterator& operator+=(difference_type n)
		{
			_iter += n;
			return *this;
		}
		vectorIterator operator+(difference_type n) const
		{
			return vectorIterator(_iter + n);
		}
		vectorIterator& operator-=(difference_type n)
		{
			_iter -= n;
			return *this;
		}
		vectorIterator operator-(difference_type n) const
		{
			return vectorIterator(_iter - n);
		}
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template <class A, class B>
	bool operator==(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class A, class B>
	bool operator!=(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class A, class B>
	bool operator<(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class A, class B>
	bool operator<=(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class A, class B>
	bool operator>(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class A, class B>
	bool operator>=(const vectorIterator<A>& lhs,
					const vectorIterator<B>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	typename vectorIterator<Iterator>::difference_type operator-(
		const vectorIterator<Iterator>& lhs,
		const vectorIterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	};

	template <class Iterator>
	vectorIterator<Iterator> operator+(
		typename vectorIterator<Iterator>::difference_type n,
		const vectorIterator<Iterator>& rev_it)
	{
		return vectorIterator<Iterator>(rev_it.base() + n);
	};
}

#endif