#ifndef MAP_HPP
# define MAP_HPP

# include "rbTree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
				class A = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:

		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Compare												key_compare;
		typedef A													allocator_type;

		class value_compare
		{
			key_compare	_comp;
		public:
			value_compare(key_compare cmp) : _comp(cmp) {}
			bool operator()(const value_type& x, const value_type& y) const
			{
				return _comp(x.first, y.first);
			}
		};

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

		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;

	public:

		explicit map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
				_comp(comp), _alloc(alloc), _tree(comp, alloc) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				_comp(comp), _alloc(alloc), _tree(first, last, comp, alloc) {}
		map(const map& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}
		map& operator= (const map& x)
		{
			if (this != &x)
				_tree = x._tree;
			return *this;
		}
		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}
		~map() {}

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
		size_type erase(const key_type& key)
		{
			return _tree.erase(ft::make_pair(key, mapped_type()));
		}
		void erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
		}
		void swap(map& x)
		{
			_tree.swap(x._tree);
		}
		void clear()
		{
			_tree.clear();
		}

		key_compare key_comp() const
		{
			return _comp;
		}
		value_compare value_comp() const
		{
			return _tree.value_comp();
		}

		iterator find(const key_type& key)
		{
			return _tree.find(ft::make_pair(key, mapped_type()));
		}
		const_iterator find(const key_type& key) const
		{
			return _tree.find(ft::make_pair(key, mapped_type()));
		}
		size_type count(const key_type& key) const
		{
			return _tree.count(ft::make_pair(key, mapped_type()));
		}
		iterator lower_bound(const key_type& key)
		{
			return _tree.lower_bound(ft::make_pair(key, mapped_type()));
		}
		const_iterator lower_bound(const key_type& key) const
		{
			return _tree.lower_bound(ft::make_pair(key, mapped_type()));
		}
		iterator upper_bound(const key_type& key)
		{
			return _tree.upper_bound(ft::make_pair(key, mapped_type()));
		}
		const_iterator upper_bound(const key_type& key) const
		{
			return _tree.upper_bound(ft::make_pair(key, mapped_type()));
		}
		ft::pair<iterator, iterator> equal_range(const key_type& key)
		{
			return _tree.equal_range(ft::make_pair(key, mapped_type()));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return _tree.equal_range(ft::make_pair(key, mapped_type()));
		}


		template <class Keyy, class Ty, class C, class Al>
		friend bool operator== (const map<Keyy, Ty, C, Al>& lhs,
								const map<Keyy, Ty, C, Al>& rhs);
		template <class Keyy, class Ty, class C, class Al>
		friend bool operator< (const map<Keyy, Ty, C, Al>& lhs,
								const map<Keyy, Ty, C, Al>& rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return lhs._tree == rhs._tree;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return lhs._tree < rhs._tree;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif