#ifndef SET_HPP
# define SET_HPP

# include "rbTree.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>,
				class A = std::allocator<T> >
	class set
	{
	public:

		typedef T													key_type;
		typedef T													value_type;
		typedef Compare												key_compare;
		typedef Compare												value_compare;
		typedef A													allocator_type;

		typedef typename A::pointer									pointer;
		typedef typename A::const_pointer							const_pointer;
		typedef typename A::reference								reference;
		typedef typename A::const_reference							const_reference;
		typedef typename A::size_type								size_type;
		typedef typename A::difference_type							difference_type;

		typedef rbTree<value_type, value_compare, allocator_type>	tree;
		typedef typename tree::iterator								iterator;
		typedef typename tree::const_iterator						const_iterator;
		typedef typename tree::reverse_iterator						reverse_iterator;
		typedef typename tree::const_reverse_iterator				const_reverse_iterator;

	private:

		value_compare	_comp;
		allocator_type	_alloc;
		tree			_tree;

	public:

		explicit set(const value_compare& comp = value_compare(),
			const allocator_type& alloc = allocator_type()) :
				_comp(comp), _alloc(alloc), _tree(comp, alloc) {}
		template <class InputIterator>
		set(InputIterator first, InputIterator last,
			const value_compare& comp = value_compare(),
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				_comp(comp), _alloc(alloc), _tree(first, last, comp, alloc) {}
		set(const set& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}
		set& operator= (const set& x)
		{
			if (this != &x)
				_tree = x._tree;
			return *this;
		}
		~set() {}

		iterator begin()
		{
			return _tree.begin();
		}
		const_iterator begin() const
		{
			return _tree.begin();
		}
		iterator end()
		{
			return _tree.end();
		}
		const_iterator end() const
		{
			return _tree.end();
		}
		reverse_iterator rbegin()
		{
			return _tree.rbegin();
		}
		const_reverse_iterator rbegin() const
		{
			return _tree.rbegin();
		}
		reverse_iterator rend()
		{
			return _tree.rend();
		}
		const_reverse_iterator rend() const
		{
			return _tree.rend();
		}

		bool empty() const
		{
			return _tree.empty();
		}
		size_type size() const
		{
			return _tree.size();
		}
		size_type max_size() const
		{
			return _tree.max_size();
		}
		allocator_type get_allocator() const
		{
			return _tree.get_allocator();
		}

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			return _tree.insert(val);
		}
		iterator insert(iterator position, const value_type& val)
		{
			return _tree.insert(position, val);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			_tree.insert(first, last);
		}

		void erase(iterator position)
		{
			_tree.erase(position);
		}
		size_type erase(const value_type& val)
		{
			return _tree.erase(val);
		}
		void erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
		}
		void swap(set& x)
		{
			_tree.swap(x._tree);
		}
		void clear()
		{
			_tree.clear();
		}

		key_compare key_comp() const
		{
			return value_comp();
		}
		value_compare value_comp() const
		{
			return _tree.value_comp();
		}

		iterator find(const value_type& val)
		{
			return _tree.find(val);
		}
		const_iterator find(const value_type& val) const
		{
			return _tree.find(val);
		}
		size_type count(const value_type& val) const
		{
			return _tree.count(val);
		}
		iterator lower_bound(const value_type& val)
		{
			return _tree.lower_bound(val);
		}
		const_iterator lower_bound(const value_type& val) const
		{
			return _tree.lower_bound(val);
		}
		iterator upper_bound(const value_type& val)
		{
			return _tree.upper_bound(val);
		}
		const_iterator upper_bound(const value_type& val) const
		{
			return _tree.upper_bound(val);
		}
		ft::pair<iterator, iterator> equal_range(const value_type& val)
		{
			return _tree.equal_range(val);
		}
		ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
		{
			return _tree.equal_range(val);
		}


		template <class K, class C, class Al>
		friend bool operator== (const set<K, C, Al>& lhs,
								const set<K, C, Al>& rhs);
		template <class K, class C, class Al>						
		friend bool operator< (const set<K, C, Al>& lhs,
								const set<K, C, Al>& rhs);
		
	};

	template <class T, class Compare, class Alloc>
	bool operator== (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return lhs._tree == rhs._tree;
	}

	template <class T, class Compare, class Alloc>
	bool operator!= (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator< (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return lhs._tree < rhs._tree;
	}

	template <class T, class Compare, class Alloc>
	bool operator> (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
	bool operator<= (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>= (const set<T, Compare, Alloc>& lhs,
					const set<T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Compare, class Alloc>
	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif