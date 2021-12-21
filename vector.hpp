#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include "iterator.hpp"
# include "vectorIterator.hpp"
# include <stdexcept>
# include "type_traits.hpp"
# include "algorithm.hpp"

namespace	ft
{
	template <class T, class A = std::allocator<T> >
	class vector
	{
	public:
	
		//member_types
		typedef A										allocator_type;
		typedef typename A::value_type					value_type;
		typedef typename A::pointer						pointer;
		typedef typename A::const_pointer				const_pointer;
		typedef typename A::reference					reference;
		typedef typename A::const_reference				const_reference;
		typedef typename A::size_type					size_type;
		typedef typename A::difference_type				difference_type;
		typedef vectorIterator<pointer>					iterator;
		typedef vectorIterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:

		pointer			_arr;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:

		//Coplien form
		explicit vector(const allocator_type& alloc = allocator_type()) :
						_arr(0), _size(0), _capacity(0), _alloc(alloc) {}
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :
						_size(n), _capacity(n), _alloc(alloc)
		{
			_arr = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_arr + i, val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				_size(0), _alloc(alloc)
		{
			_size = static_cast<size_type>(last - first);
			_arr = _alloc.allocate(_size);
			for (size_type i = 0; first != last; first++, i++)
				_alloc.construct(_arr + i, *first);
			_capacity = _size;
		}
		vector(const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
		{
			_arr = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_arr + i, x._arr[i]);
		};
		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_arr + i);
			_alloc.deallocate(_arr, _capacity);
		}
		vector& operator= (const vector& x)
		{
			if (this != &x)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _size);
				_size = x._size;
				_capacity = x._capacity;
				_arr = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_arr + i, x._arr[i]);
			}
			return *this;
		}

		//iterators
		iterator begin()
		{
			return iterator(_arr);
		}
		const_iterator begin() const
		{
			return const_iterator(_arr);
		}
		iterator end()
		{
			return iterator(_arr + _size);
		}
		const_iterator end() const
		{
			return const_iterator(_arr + _size);
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
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _alloc.max_size();
		}
		void resize(size_type n, value_type val = value_type())
		{
			if (_size < n)
				insert(end(), n - _size, val);
			else if (_size > n)
				erase(begin() + n, end());
		}
		size_type capacity() const
		{
			return _capacity;
		}
		bool empty() const
		{
			return _size == 0;
		}
		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector");
			if (n > _capacity)
			{
				try
				{
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _arr[i]);
					this->~vector();
					_capacity = n;
					_arr = tmp;
				}
				catch(...)
				{
					this->~vector();
					throw;
				}
			}
		}

		//element access
		reference operator[](size_type n)
		{
			return *(begin() + n);
		}
		const_reference operator[](size_type n) const
		{
			return *(begin() + n);
		}
		reference at(size_type n)
		{
			if (n < 0 || n > _size)
				throw std::out_of_range("vector");
			return *(begin() + n);
		}
		const_reference at(size_type n) const
		{
			if (n < 0 || n > _size)
				throw std::out_of_range("vector");
			return *(begin() + n);
		}
		reference front()
		{
			return *_arr;
		}
		const_reference front() const
		{
			return *_arr;
		}
		reference back()
		{
			return _arr[_size - 1];
		}
		const_reference back() const
		{
			return _arr[_size - 1];
		}

		//modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			clear();
			insert(begin(), first, last);
		}
		void assign(size_type n, const value_type& val)
		{
			clear();
			insert(begin(), n, val);
		}
		void push_back(const value_type& val)
		{
			insert(end(), val);
		}
		void pop_back()
		{
			if (_size)
				_alloc.destroy(&_arr[--_size]);
		}
		iterator insert(iterator position, const value_type& val)
		{
			difference_type	idx = position - begin();
			insert(position, 1, val);
			return iterator(&_arr[idx]);
		}
		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			else if (max_size() - size() < n)
				throw std::length_error("vector");
			else
			{
				try
				{
					insertElements(position, n, val);
				}
				catch(...)
				{
					this->~vector();
					throw;
				}
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			if (first < last)
			{
				for (; first != last; first++, position++)
					position = insert(position, *first);
			}
		}
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}
		iterator erase(iterator first, iterator last)
		{
			difference_type dif = last - first;
			if (first < last && first != end())
			{
				iterator tmp = last;
				for (; first != end(); first++, tmp++)
				{
					_alloc.destroy(first.base());
					if (first < last)
						_alloc.construct(first.base(), *tmp);
				}
				_size -= dif;
			}
			return first;
		}
		void swap(vector& x)
		{
			ft::swap(_alloc, x._alloc);
			ft::swap(_capacity, x._capacity);
			ft::swap(_size, x._size);
			ft::swap(_arr, x._arr);
		}
		void clear()
		{
			for (iterator it = begin(); it != end(); it++)
				_alloc.destroy(it.base());
			_size = 0;
		}

		//allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}

	//my methods (helpers)
	private:

		void	enoughCapacity(iterator position, size_type n, const value_type& val)
		{
			for (size_type count = _size - 1, i = n; i; count--, i--)
				_alloc.construct(&_arr[count + n], _arr[count]);
			if (position + n < end())
			{
				for (iterator pos = end(); pos != position + n; --pos)
				{
					_alloc.destroy(pos.base());
					_alloc.construct(pos.base(), *(pos - n));
				}
			}
			for (iterator pos = position; pos != position + n; pos++)
			{
				_alloc.destroy(pos.base());
				_alloc.construct(pos.base(), val);
			}
			_size += n;
		}
		void	moreCapacity(iterator position, size_type n, const value_type& val)
		{
			size_t	newCapacity;
			difference_type	dif = position - begin();
			difference_type	dif2 = position - end();
			if (_size + n <= _capacity * 2)
				newCapacity = _capacity * 2;
			else
				newCapacity = _size + n;
			pointer tmp = _alloc.allocate(newCapacity);
			size_type i = 0;
			for (; i < dif; i++)
				_alloc.construct(&tmp[i], _arr[i]);
			for (size_type j = i; j < i + n; j++)
				_alloc.construct(&tmp[j], val);
			for (; i < _size; i++)
				_alloc.construct(&tmp[i + n], _arr[i]);
			this->~vector();
			_size += (dif2 > 0) ? n + dif2 : n;
			_capacity = newCapacity;
			_arr = tmp;
		}
		void	insertElements(iterator position, size_type n, const value_type& val)
		{
			if (_size + n <= _capacity)
				enoughCapacity(position, n, val);
			else 
				moreCapacity(position, n, val);
		}
	};


	//relational operations
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	//swap
	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif