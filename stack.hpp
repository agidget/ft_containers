#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <deque>
# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T								value_type;
		typedef Container						container_type;
		typedef typename Container::size_type	size_type;

	private:
		container_type		_container;

	public:
		explicit stack(const container_type& ctnr = container_type()) :_container(ctnr) {}
		stack(const stack& x) : _container(x._container) {}
		stack& operator= (const stack& x)
		{
			_container = x._container;
			return *this;
		}
		~stack() {}

		bool empty() const
		{
			return _container.empty();
		}
		size_type size() const
		{
			return _container.size();
		}
		value_type& top()
		{
			return _container.back();
		}
		const value_type& top() const
		{
			return _container.back();
		}
		void push(const value_type& val)
		{
			_container.push_back(val);
		}
		void pop()
		{
			_container.pop_back();
		}


		template <class Tt, class C>
		friend bool operator== (const stack<Tt, C>& lhs, const stack<Tt, C>& rhs);
		template <class Tt, class C>
		friend bool operator< (const stack<Tt, C>& lhs, const stack<Tt, C>& rhs);
	};

	template <class T, class Container>
	bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container == rhs._container;
	}

	template <class T, class Container>
	bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container < rhs._container;
	}

	template <class T, class Container>
	bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif