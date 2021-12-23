#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
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
			if (n > max_size())
				throw std::length_error("vector");
			if (_size < n)
				insert(end(), n - _size, val);
			else if (_size > n)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = n;
			}
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
					_alloc.deallocate(_arr, _capacity);
					_capacity = n;
					_arr = tmp;
				}
				catch(...)
				{
					_alloc.deallocate(_arr, _capacity);
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
			if (first > last)
				std::logic_error("vector");
			clear();
			size_type	dif = static_cast<size_type>(last - first);
			size_type	m;
			if (_capacity < dif)
			{
				m = (_capacity * 2 > dif) ? _capacity * 2 : dif;
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(m);
				_capacity = m;
			}
			for (iterator pos = begin(); first != last; pos++, first++)
				_alloc.construct(pos.base(), *first);
			_size = dif;
		}
		void assign(size_type n, const value_type& val)
		{
			size_type	m;
			clear();
			if (_capacity < n)
			{
				m = (_capacity * 2 > n) ? _capacity * 2 : n;
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(m);
				_capacity = m;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_arr[i], val);
			_size = n;
			
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
				size_type	dif = static_cast<size_type>(position - begin());
				if (_size + n > _capacity)
				{
					size_type	newCapacity;
					if (_size + n <= _capacity * 2)
						newCapacity = _capacity * 2;
					else
						newCapacity = _size + n;
					pointer tmp = _alloc.allocate(newCapacity);
					std::uninitialized_copy(begin(), position, iterator(tmp));
					try
					{
						for (size_type i = 0; i < n; i++)
							_alloc.construct(&tmp[dif + i], val);
					}
					catch (...)
					{
						for (size_type i = 0; i < dif + n; i++)
							_alloc.destroy(&_arr[i]);
						_alloc.deallocate(tmp, newCapacity);
						throw;
					}
					std::uninitialized_copy(position, end(), iterator(&tmp[dif + n]));
					_alloc.deallocate(_arr, _capacity);
					_capacity = newCapacity;
					_arr = tmp;
				}
				else
				{
					for (size_type i = _size; i > dif; i--)
					{
						_alloc.destroy(&_arr[i + n - 1]);
						_alloc.construct(&_arr[i + n - 1], _arr[i - 1]);
					}
					for (size_type i = 0; i < n; i++)
					{
						_alloc.destroy(&_arr[dif + i]);
						_alloc.construct(&_arr[dif + i], val);
					}
				}
				_size += n;
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			// if (first < last)
			// {
			// }
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");
			// size_type	dif = static_cast<size_type>(position - begin());
			// size_type	dif2 = static_cast<size_type>(last - first);
			for (; first != last; first++, position++)
				position = insert(position, *first);
			
		}
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}
		iterator erase(iterator first, iterator last)
		{
			if (first > last)
				throw std::logic_error("vector");
			difference_type dif = last - first;
			if (first != end())
			{
				iterator tmp = last;
				for (; first != end(); first++, tmp++)
				{
					_alloc.destroy(first.base());
					if (first < last)
						_alloc.construct(first.base(), *tmp);
				}
				_size -= static_cast<size_type>(dif);
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
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_arr[i]);
			_size = 0;
		}

		//allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}

	//my methods (helpers)
	// private:
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