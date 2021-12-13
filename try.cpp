#include <iostream>
#include <vector>
#include <typeinfo>
#include "type_traits.hpp"
#include <type_traits>
#include "algorithm.hpp"
#include <cctype>
#include <string>
#include "utility.hpp"
#include "vector.hpp"
#include <map>
#include <chrono>

// #define RED '1'
// #define BLACK '2'

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type
	is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
// template < class T,
//            class = typename ft::enable_if<std::is_integral<T>::value>::type>
// bool is_even (T i) {return !bool(i%2);}

bool mypredicate (int i, int j) {
  return (i==j);
}

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

int main()
{
	{
		// int sz = 200;
		// std::vector<int> v1;
	
		// size_t cap = v1.capacity();
		// std::cout << "initial capacity=" << cap << '\n';
	
		// for (int n = 0; n < sz; ++n) {
		// 	v1.push_back(n);
		// 	if (cap != v1.capacity()) {
		// 		cap = v1.capacity();
		// 		std::cout << "size of arr = " << v1.size() << '\n';
		// 		std::cout << "new capacity = " << cap << '\n';
		// 		std::cout << "-----------\n";
		// 	}
		// }
	
		// std::cout << "final size = " << v1.size() << '\n';
		// std::cout << "final capacity = " << v1.capacity() << '\n';

		// wchar_t a;
		// if (strcmp(typeid(a).name(), "w") == 0)
		// 	std::cout << typeid(a).name() << std::endl;

		// short int i = 1;    // code does not compile if type of i is not integral

		// std::cout << std::boolalpha;
		// std::cout << "i is odd: " << is_odd(i) << std::endl;
		// std::cout << "i is even: " << is_even(i) << std::endl;

		// std::cout << std::boolalpha;
		// std::cout << "is_integral:" << std::endl;
		// std::cout << "char: " << ft::is_integral<char>::value << std::endl;
		// std::cout << "int: " << ft::is_integral<int>::value << std::endl;
		// std::cout << "float: " << ft::is_integral<float>::value << std::endl;


		// int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
		// std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

		// // using default comparison:
		// if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		// 	std::cout << "The contents of both sequences are equal.\n";
		// else
		// 	std::cout << "The contents of both sequences differ.\n";

		// myvector[3]=81;                                 // myvector: 20 40 60 81 100

		// // using predicate comparison:
		// if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		// 	std::cout << "The contents of both sequences are equal.\n";
		// else
		// 	std::cout << "The contents of both sequences differ.\n";

		// char foo[]="Apple";
		// char bar[]="apartment";

		// std::cout << std::boolalpha;

		// std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

		// std::cout << "Using default comparison (operator<): ";
		// std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9);
		// std::cout << '\n';

		// std::cout << "Using mycomp as comparison object: ";
		// std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
		// std::cout << '\n';


		// ft::pair <std::string,double> product1;                     // default constructor
		// ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
		// ft::pair <std::string,double> product3 (product2);          // copy constructor
		// ft::pair <std::string,double> product4;

		// // product1 = std::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

		// // product2.first = "shoes";                  // the type of first is string
		// // product2.second = 39.90;                   // the type of second is double

		// product4 = product2;

		// std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
		// std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
		// std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
		// std::cout << "The price of " << product4.first << " is $" << product4.second << '\n';

		// ft::pair<int,char> foo (10,'a');
		// ft::pair<int,char> bar (90,'z');

		// foo.swap(bar);

		// std::cout << "foo contains: " << foo.first;
		// std::cout << " and " << foo.second << '\n';

		// ft::pair <int,int> foo;
		// ft::pair <int,int> bar;

		// foo = ft::make_pair (10, 20);
		// bar = ft::make_pair (10.5, 'A'); // ok: implicit conversion from pair<double,char>

		// std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
		// std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

		// ft::pair<int,char> foo (10,'z');
		// ft::pair<int,char> bar (90,'a');

		// if (foo==bar) std::cout << "foo and bar are equal\n";
		// if (foo!=bar) std::cout << "foo and bar are not equal\n";
		// if (foo< bar) std::cout << "foo is less than bar\n";
		// if (foo> bar) std::cout << "foo is greater than bar\n";
		// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";



		// std::vector<int> a(4, 3);
		// a.insert(a.begin() + 1, 1, 200);
		// a.insert(a.begin() + 1, 2, 200);
		// a.insert(a.begin() + 1, 6, 200);
		// for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// std::cout << a[1] << std::endl;
		// std::vector<int>::iterator it = a.end();
		// std::vector<int>::iterator it2 = a.begin() + 3;
		// std::cout << *it2 << std::endl;
		// std::vector<int>::iterator::difference_type kek = it - it2;
		// std::cout << kek << std::endl;
		// bool lol = it < it2;
		// std::cout << std::boolalpha;
		// std::cout << lol << std::endl;
		// std::vector<int> b(a);
		// a[0] = 2;
		// for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// std::vector<int>::iterator it = a.end();
		// std::cout << *(it) << std::endl;
		// std::cout << "--------------\n";
		// for (std::vector<int>::iterator it = b.begin(); it != b.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::vector<int>::iterator it = b.begin();
		// b.insert(it, 0);
		// b.insert(it, 4611686018427387902, 0);
		// std::cout << b.max_size() << std::endl;
		// std::cout << b.front() << std::endl;
		// std::cout << b.at(2) << std::endl;

		// std::vector<int>::const_iterator it1;
		// std::vector<int>::iterator it2;
		// std::vector<int>::iterator::difference_type it3;
		// std::vector<int>::iterator it4;

		// it1 = a.begin();
		// it2 = b.begin();
		// it3 = it1 - it2;
		// it4 = it3 + it1;

		// bool ab = it1 == it2;
		// std::cout << std::boolalpha;
		// std::cout << ab << std::endl;

		// ft::vector<int> a;
		// ft::vector<int>::iterator it;
		// ft::vector<int>::const_iterator it2;
		// ft::vector<int>::reverse_iterator it3;
		// ft::vector<int>::const_reverse_iterator it4;
		// it = a.begin();
		// a.insert(it, 4611686018427387904, 0);
		// it2 = a.begin();
		// it3 = a.rbegin();
		// it4 = a.rend();
		// std::cout << a.max_size() << std::endl;
		// std::cout << a.front() << std::endl;
		// std::cout << a.at(2) << std::endl;
		// a.clear();
		// std::cout << *it << std::endl;

		// ft::vector<int> a(5, 3);
		// ft::vector<int> c(2, 2);
		// a.insert(a.end() - 3, c.begin(), c.begin() + 1);
		// a.erase(a.begin() + 1, a.begin());
		// a.clear();
		// std::cout << "dif " <<  a.end() - 1 - a.begin() << std::endl;
		// a.erase(a.begin() + 2, a.begin());
		// a.push_back(20);
		// a.push_back(100);
		// a.pop_back();
		// a.assign(3, 20);
		// a.resize(2, 666);
		// for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// std::cout << a.size() << std::endl;
		// std::cout << a.capacity() << std::endl;


		//vector::swap
		// ft::vector<int> foo (3,100);   // three ints with a value of 100
		// ft::vector<int> bar (foo.begin(),foo.end());   // five ints with a value of 200

		// ft::swap(bar, foo);

		// std::cout << "foo contains:";
		// for (unsigned i=0; i<foo.size(); i++)
		// 	std::cout << ' ' << foo[i];
		// std::cout << '\n';
		// std::cout << foo.size() << std::endl;
		// std::cout << foo.capacity() << std::endl;

		// std::cout << "bar contains:";
		// for (unsigned i=0; i<bar.size(); i++)
		// 	std::cout << ' ' << bar[i];
		// std::cout << '\n';
		// std::cout << bar.size() << std::endl;
		// std::cout << bar.capacity() << std::endl;


		// ft::vector<int> foo (3,100);   // three ints with a value of 100
		// ft::vector<int> bar (3,100);   // two ints with a value of 200

		// if (foo==bar) std::cout << "foo and bar are equal\n";
		// if (foo!=bar) std::cout << "foo and bar are not equal\n";
		// if (foo< bar) std::cout << "foo is less than bar\n";
		// if (foo> bar) std::cout << "foo is greater than bar\n";
		// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


		// std::cout << "\n\n";
		// ft::vector<int> a2(5, 3);
		// ft::vector<int> c2(2, 2);
		// a2.insert(a2.end() - 3, c2.begin(), c2.begin() + 1);
		// for (ft::vector<int>::iterator it = a2.begin(); it != a2.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// std::cout << a2.size() << std::endl;
		// std::cout << a2.capacity() << std::endl;


		// std::cout << b.size() << std::endl;
		// std::cout << b.capacity() << std::endl;
		// for (ft::vector<int>::iterator it = b.begin(); it != b.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// std::cout << c.size() << std::endl;
		// std::cout << c.capacity() << std::endl;
		// for (ft::vector<int>::iterator it = c.begin(); it != c.end(); it++)
		// 	std::cout << *it << std::endl;
		// std::cout << "--------------\n";
		// c = a;
		// std::cout << c.size() << std::endl;
		// std::cout << c.capacity() << std::endl;
		// for (ft::vector<int>::iterator it = c.begin(); it != c.end(); it++)
		// 	std::cout << *it << std::endl;
		// a.push_back(7);
		// std::cout << a.size() << std::endl;
		// std::cout << a.capacity() << std::endl;
	}
	{
		// using std::chrono::high_resolution_clock;
		// using std::chrono::duration_cast;
		// using std::chrono::duration;
		// using std::chrono::milliseconds;

		// auto t1 = high_resolution_clock::now();

		// std::map<char,int> first;

		// first['a']=10;
		// first['b']=30;
		// first['c']=50;
		// first['d']=70;

		// first.insert(std::pair<char,int>('a', 100));
		// first.insert(std::pair<char,int>('1', 100));
		// first.insert(std::pair<char,int>('2', 100));
		// first.insert(std::pair<char,int>('3', 100));
		// first.insert(std::pair<char,int>('4', 100));
		// first.insert(std::pair<char,int>('5', 100));
		// first.insert(std::pair<char,int>('6', 100));
		// first.insert(std::pair<char,int>('7', 100));
		// first.insert(std::pair<char,int>('8', 100));
		// for (std::map<char,int>::iterator it = first.begin(); it != first.end(); it++)
		// 	std::cout << "Ключ " << it->first << ", значение " << it->second << std::endl;


		// auto t2 = high_resolution_clock::now();
		// /* Getting number of milliseconds as an integer. */
		// auto ms_int = duration_cast<milliseconds>(t2 - t1);

		// /* Getting number of milliseconds as a double. */
		// duration<double, std::milli> ms_double = t2 - t1;

		// std::cout << ms_int.count() << "ms\n";
		// std::cout << ms_double.count() << "ms" << std::endl;

	}
}