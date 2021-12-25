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
#include "rbTree.hpp"
#include <set>
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"

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
	// {
		//try rbTree
		// ft::rbTree<int> a;
		// ft::rbTree<int>::const_iterator it = a.begin();
		// a.insert(it, 30);
		// a.insert(it, 10);
		// a.insert(it, 50);
		// a.insert(it, 20);
		// // // std::cout << *a.insert(it, 30) << std::endl;
		// a.insert(it, 40);
		// a.insert(it, 60);
		// a.insert(it, 70);
		// a.insert(it, 80);
		// a.insert(it, 90);

		// for (ft::rbTree<int>::const_iterator iter = a.begin(); iter != a.end(); iter++)
		// 	std::cout << *iter << std::endl;
		// // // it = a.end();
		// // // it++;
		// // // std::cout << *it << std::endl;

		// std::cout << a.getRoot() << std::endl;

		// std::cout << "--------------------\n";

		// it = a.find(60);
		// std::cout << *it << std::endl;

		// it = a.find(600);
		// std::cout << *it << std::endl;

		// std::cout << a.count(60) << std::endl;
		// std::cout << a.count(600) << std::endl;

		// ft::rbTree<int> a3;
		// a3.insert(5);
		// a3.insert(15);
		// a3.insert(25);
		// a3.insert(-5);
		// for (ft::rbTree<int>::const_iterator it3 = a3.begin(); it3 != a3.end(); it3++)
		// 	std::cout << *it3 << std::endl;

		// std::set<int> a2;
		// a2.insert(5);
		// std::set<int>::const_iterator it2 = a2.begin();
		// a2.insert(it2, 7);
		// std::cout << *it2 << std::endl;
	// }
	// {
	// 	// // std::cout << "--------------------\n\n";

	// 	// std::set<int> myset;
	// 	// std::set<int>::iterator it3;

	// 	// int myints[]= {5,100,15,80,65,30,35,40};
	// 	// myset.insert (myints,myints+8);
	// 	// std::set<int>::iterator it4 = myset.begin();
	// 	// it4++;
	// 	// it4++;
	// 	// myset.erase(it4);
	// 	// it4 = myset.begin();
	// 	// it4++;
	// 	// myset.erase(it4);
	// 	// myset.erase(40);
	// 	// myset.erase(400);
	// 	// it4 = myset.find(65);
	// 	// myset.erase(it4, myset.end());
	// 	// for (it3=myset.begin(); it3!=myset.end(); ++it3)
	// 	// 	std::cout << ' ' << *it3;
	// 	// std::cout << '\n';
	// 	// // it3 = myset.find(80);
	// 	// // std::cout << *it3 << std::endl;
	// 	// // it3 = myset.find(600);
	// 	// // std::cout << *it3 << std::endl;


	// 	std::cout << "--------------------\n";

	// 	ft::rbTree<int> myset3;
	// 	ft::rbTree<int>::iterator it33;

	// 	int myints3[]= {5,100,15,80,65,30,35,40};
	// 	myset3.insert (myints3,myints3+8);
	// 	// myset3.insert(20);
	// 	// myset3.insert(40);
	// 	// myset3.insert(-40);
	// 	// myset3.insert(myset3.begin(), 100);
	// 	// std::cout << "mainRoot: " << *myset3._root->value << std::endl;
	// 	ft::rbTree<int>::iterator it43 = myset3.begin();
	// 	// ft::rbTree<int>::iterator it43aa;
	// 	it43++;
	// 	it43++;
	// 	it43++;
	// 	// std::cout << "it: " << *it43 << std::endl;
	// 	// std::cout << "left " << it43.base()->left->is_nil << std::endl;
	// 	// std::cout << "right " << it43.base()->right->is_nil << std::endl;
	// 	// myset3.erase(it43);
	// 	// myset3.erase(30);
	// 	// std::cout << "BEGIN " << *myset3.begin() << std::endl;


	// 	// myset3.erase(30);
	// 	// myset3.erase(35);
	// 	// myset3.erase(40);
	// 	// myset3.erase(65);
	// 	// myset3.erase(80);
	// 	// myset3.erase(100);


	// 	// std::cout << "mainRoot: " << *myset3.getRoot()->value << std::endl;
	// 	// it43 = myset3.begin();
	// 	// it43++;
	// 	// // std::cout << "del " << *it43 << std::endl;
	// 	// myset3.erase(it43);
	// 	// myset3.erase(40);
	// 	// myset3.erase(400);
	// 	// it43 = myset3.find(65);
	// 	// // myset3.erase(it43);

	// 	ft::rbTree<int>::iterator it433 = myset3.end();
	// 	// it433--;
	// 	// it433--;
	// 	// std::cout << "it433: " << *it433 << std::endl;

	// 	myset3.erase(it43, it433);
	// 	// it43aa = myset3.begin();
	// 	// it43aa++;
	// 	// std::cout << "BEGIN+1 " << *it43aa << std::endl;
	// 	std::cout << "mainRoot: " << *myset3.getRoot()->value << std::endl;
	// 	for (it33=myset3.begin(); it33!=myset3.end(); ++it33)
	// 	{
	// 		std::cout << "Value: " << *it33;
	// 		std::cout << ", Color: " << ((it33.base()->color == '1') ? "RED" : "BLACK");
	// 		// std::cout << ", Color: " << ((it33.base()->is_black == false) ? "RED" : "BLACK");
	// 		std::cout << std::endl;
	// 	}
	// 	std::cout << '\n';



		// ft::set<int> myset2;
		// ft::set<int>::iterator it2;

		// int myints2[]= {5,100,15,80,65,30,35,40};
		// myset2.insert (myints2,myints2+8);
		// ft::rbTree<int>::iterator it44 = myset2.begin();
		// it44++;
		// it44++;
		// std::cout << *it44 << std::endl;
		// // myset2.erase(30);
		// myset2.erase(it44);
		// it44 = myset2.begin();
		// it44++;
		// myset2.erase(it44);
		// myset2.erase(40);
		// myset2.erase(400);
		// it44 = myset2.find(65);
		// std::cout << *it44 << std::endl;
		// myset2.erase(it44, myset2.end());
		// for (it2=myset2.begin(); it2!=myset2.end(); ++it2)
		// 	std::cout << ' ' << *it2;
		// std::cout << '\n';




		// ft::rbTree<int>::iterator it5 = myset2.begin();
		// it5++;
		// it5++;
		// myset2.erase(it5);
		// it5 = myset2.begin();
		// it5++;
		// myset2.erase(it5);
		// myset2.erase(40);
		// myset2.erase(400);
		// std::cout << "size: " << myset2.getSize() << std::endl;
		// it2=myset2.begin();
		// std::cout << ' ' << *it2 << std::endl;
		// it5 = myset2.find(65);
		// // myset2.erase(myset2.begin());
		// // ft::rbTree<int>::iterator it6 = it5;
		// // it6++;
		// // it6++;
		// // it6++;
		// myset2.erase(80);
		// // myset2.erase(it5, myset2.end());
		// // std::cout << "min: " << *myset2.treeMin(myset2._root)->value << std::endl;
		// std::cout << ' ' << *myset2.begin() << std::endl;
		// // for (it2=myset2.begin(); it2!=myset2.end(); ++it2)
		// // 	std::cout << ' ' << *it2;
		// std::cout << '\n';
	// }
	// {
	// 	int my[] = {5,100,15,80,65,30,35,40};
	// 	ft::rbTree<int> a(my, my + 4);
	// 	ft::rbTree<int> b = a;
	// 	b.erase(100);
	// 	std::cout << "a:";
	// 	for (ft::rbTree<int>::iterator it = a.begin(); it != a.end(); it++)
	// 		std::cout << " " << *it;
	// 	std::cout << std::endl;
	// 	std::cout << "b:";
	// 	for (ft::rbTree<int>::iterator it = b.begin(); it != b.end(); it++)
	// 		std::cout << " " << *it;
	// 	std::cout << std::endl;
	// }
	// {
	// 	ft::rbTree<int> myset;

	// 	myset.insert (100);
	// 	myset.insert (200);
	// 	myset.insert (300);

	// 	std::cout << "myset contains:";
	// 	for (ft::rbTree<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
	// 		std::cout << ' ' << *it;
	// 	std::cout << '\n';

	// 	myset.clear();
	// 	myset.insert (1101);
	// 	myset.insert (2202);

	// 	std::cout << "myset contains:";
	// 	for (ft::rbTree<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
	// 		std::cout << ' ' << *it;
	// 	std::cout << '\n';
	// }

		// ft::rbTree<int> myset;
		// ft::rbTree<int>::iterator itlow,itup;

		// for (int i=1; i<10; i++)
		// 	myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

		// itlow=myset.lower_bound(30);
		// std::cout << "itlow " << *itlow << std::endl;
		// // itup = myset.end();
		// itup=myset.upper_bound (60);

		// myset.erase(itlow,itup);                     // 10 20 70 80 90

		// std::cout << "myset contains:";
		// for (ft::rbTree<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		// 	std::cout << ' ' << *it;
		// std::cout << '\n';


		// std::cout << "--------------------\n";

		// std::set<int> myset2;
		// std::set<int>::iterator itlow2,itup2;

		// for (int i=1; i<10; i++)
		// 	myset2.insert(i*10); // 10 20 30 40 50 60 70 80 90

		// itlow2=myset2.lower_bound(30);
		// std::cout << "itlow2 " << *itlow2 << std::endl;
		// // itup2 = myset2.end();
		// itup2=myset2.upper_bound (60);

		// myset2.erase(itlow2,itup2);                     // 10 20 70 80 90

		// std::cout << "myset2 contains:";
		// for (std::set<int>::iterator it=myset2.begin(); it!=myset2.end(); ++it)
		// 	std::cout << ' ' << *it;
		// std::cout << '\n';

		// {
		// 	std::cout << "\n--------------------\n\n";

		// 	ft::rbTree<int> myset;

		// 	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

		// 	ft::pair<ft::rbTree<int>::const_iterator,ft::rbTree<int>::const_iterator> ret;
		// 	ret = myset.equal_range(30);

		// 	std::cout << "the lower bound points to: " << *ret.first << '\n';
		// 	std::cout << "the upper bound points to: " << *ret.second << '\n';
		// }

		{
			// ft::rbTree<int> foo,bar;
			// foo.insert(10);
			// bar.insert(20);
			// bar.insert(30);
			// foo.insert(40);

			// // foo ({10,40}) vs bar ({20,30}):
			// if (foo==bar) std::cout << "foo and bar are equal\n";
			// if (foo!=bar) std::cout << "foo and bar are not equal\n";
			// if (foo< bar) std::cout << "foo is less than bar\n";
			// if (foo> bar) std::cout << "foo is greater than bar\n";
			// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


			// int myints[]={12,75,10,32,20,25};
			// ft::rbTree<int> first (myints,myints+3);     // 10,12,75
			// ft::rbTree<int> second (myints+3,myints+6);  // 20,25,32

			// swap(first,second);

			// std::cout << "first contains:";
			// for (ft::rbTree<int>::iterator it=first.begin(); it!=first.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			// std::cout << "second contains:";
			// for (ft::rbTree<int>::iterator it=second.begin(); it!=second.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';
		}

		{
			// ft::map<char,int> mymap;

			// mymap['b'] = 100;
			// mymap['a'] = 200;
			// mymap['c'] = 300;

			// // show content:
			// for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';



			// ft::map<char,int> foo,bar;

			// foo['x']=100;
			// foo['y']=200;

			// bar['a']=11;
			// bar['b']=22;
			// bar['c']=33;

			// swap(foo,bar);

			// std::cout << "foo contains:\n";
			// for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';

			// std::cout << "bar contains:\n";
			// for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';



			// ft::map<char,int> mymap;

			// // first insert function version (single parameter):
			// mymap.insert ( ft::pair<char,int>('a',100) );
			// mymap.insert ( ft::pair<char,int>('z',200) );

			// ft::pair<ft::map<char,int>::iterator,bool> ret;
			// ret = mymap.insert ( ft::pair<char,int>('z',500) );
			// if (ret.second==false) {
			// 	std::cout << "element 'z' already existed";
			// 	std::cout << " with a value of " << ret.first->second << '\n';
			// }

			// // second insert function version (with hint position):
			// ft::map<char,int>::iterator it = mymap.begin();
			// mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
			// mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

			// // third insert function version (range insertion):
			// ft::map<char,int> anothermap;
			// anothermap.insert(mymap.begin(),mymap.find('c'));

			// // showing contents:
			// std::cout << "mymap contains:\n";
			// for (it=mymap.begin(); it!=mymap.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';

			// std::cout << "anothermap contains:\n";
			// for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';



			// ft::map<char,int> mymap;
			// ft::map<char,int>::iterator it;

			// // insert some values:
			// mymap['a']=10;
			// mymap['b']=20;
			// mymap['c']=30;
			// mymap['d']=40;
			// mymap['e']=50;
			// mymap['f']=60;

			// it=mymap.find('b');
			// mymap.erase (it);                   // erasing by iterator

			// mymap.erase ('c');                  // erasing by key

			// it=mymap.find ('e');
			// mymap.erase ( it, mymap.end() );    // erasing by range

			// // show content:
			// for (it=mymap.begin(); it!=mymap.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';



			// ft::map<char,int> mymap;
			// std::map<char,int> mymap2;
			// std::cout << mymap.max_size() << std::endl;
			// std::cout << mymap2.max_size() << std::endl;



			// ft::map<char,int> mymap;
			// ft::map<char,int>::iterator itlow,itup;

			// mymap['a']=20;
			// mymap['b']=40;
			// mymap['c']=60;
			// mymap['d']=80;
			// mymap['e']=100;

			// itlow=mymap.lower_bound ('b');  // itlow points to b
			// itup=mymap.upper_bound ('d');   // itup points to e (not d!)

			// mymap.erase(itlow,itup);        // erases [itlow,itup)

			// // print content:
			// for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';

		}
		{
			// int myints[] = {75,23,65,42,13};
			// ft::set<int> myset (myints,myints+5);

			// std::cout << "myset contains:";
			// for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			// 	std::cout << ' ' << *it;

			// std::cout << '\n';


			// ft::set<int> myset;
			// ft::set<int>::iterator it;
			// ft::pair<ft::set<int>::iterator,bool> ret;

			// // set some initial values:
			// for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

			// ret = myset.insert(20);               // no new element inserted

			// if (ret.second==false) it=ret.first;  // "it" now points to element 20

			// myset.insert (it,25);                 // max efficiency inserting
			// myset.insert (it,24);                 // max efficiency inserting
			// myset.insert (it,26);                 // no max efficiency inserting

			// int myints[]= {5,10,15};              // 10 already in set, not inserted
			// myset.insert (myints,myints+3);

			// std::cout << "myset contains:";
			// for (it=myset.begin(); it!=myset.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';


			// ft::set<int> myset;
			// ft::set<int>::iterator it;

			// // insert some values:
			// for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

			// it = myset.begin();
			// ++it;

			// myset.erase (it);

			// myset.erase (40);

			// ft::set<int>::iterator it2 = myset.find (60);
			// // ft::set<int>::iterator it2 = myset.end();
			// myset.erase (it2, myset.end());

			// std::cout << "myset contains:";
			// for (it=myset.begin(); it!=myset.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';



			// ft::set<int> myset;
			// ft::set<int>::iterator itlow,itup;

			// for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

			// itlow=myset.lower_bound (30);                //       ^
			// itup=myset.upper_bound (60);                 //                   ^

			// myset.erase(itlow,itup);                     // 10 20 70 80 90

			// std::cout << "myset contains:";
			// for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';


			// ft::set<int> myset;

			// for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

			// ft::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret;
			// ret = myset.equal_range(30);

			// std::cout << "the lower bound points to: " << *ret.first << '\n';
			// std::cout << "the upper bound points to: " << *ret.second << '\n';


			// ft::set<int> foo,bar;
			// foo.insert(10);
			// bar.insert(20);
			// bar.insert(30);
			// foo.insert(40);

			// // foo ({10,40}) vs bar ({20,30}):
			// if (foo==bar) std::cout << "foo and bar are equal\n";
			// if (foo!=bar) std::cout << "foo and bar are not equal\n";
			// if (foo< bar) std::cout << "foo is less than bar\n";
			// if (foo> bar) std::cout << "foo is greater than bar\n";
			// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

			// ft::map<char,int> foo,bar;
			// foo['a']=100;
			// foo['b']=200;
			// bar['a']=10;
			// bar['z']=1000;

			// // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
			// if (foo==bar) std::cout << "foo and bar are equal\n";
			// if (foo!=bar) std::cout << "foo and bar are not equal\n";
			// if (foo< bar) std::cout << "foo is less than bar\n";
			// if (foo> bar) std::cout << "foo is greater than bar\n";
			// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

		}

		{
			// ft::stack<int> mystack;

			// for (int i=0; i<5; ++i) mystack.push(i);

			// std::cout << "Popping out elements...";
			// while (!mystack.empty())
			// {
			// 	std::cout << ' ' << mystack.top();
			// 	mystack.pop();
			// }
			// std::cout << '\n';

			// ft::stack<int> myints;
			// std::cout << "0. size: " << myints.size() << '\n';

			// for (int i=0; i<5; i++) myints.push(i);
			// std::cout << "1. size: " << myints.size() << '\n';

			// myints.pop();
			// std::cout << "2. size: " << myints.size() << '\n';

			// ft::stack<int> mystack;
			// int sum (0);

			// for (int i=1;i<=10;i++) mystack.push(i);

			// while (!mystack.empty())
			// {
			// 	sum += mystack.top();
			// 	mystack.pop();
			// }

			// std::cout << "total: " << sum << '\n';
		}
		{
			// ft::map<char,int> mymap;

			// mymap['x'] = 100;
			// mymap['y'] = 200;
			// mymap['z'] = 300;

			// // show content:
			// ft::map<char,int>::reverse_iterator rit;
			// for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
			// 	std::cout << rit->first << " => " << rit->second << '\n';


			// ft::map<char,int> foo,bar;

			// foo['x']=100;
			// foo['y']=200;

			// bar['a']=11;
			// bar['b']=22;
			// bar['c']=33;

			// foo.swap(bar);

			// std::cout << "foo contains:\n";
			// for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';

			// std::cout << "bar contains:\n";
			// for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			// 	std::cout << it->first << " => " << it->second << '\n';
		}

		{
			//for weird tests

			//map swap
			ft::map<char,int> foo,bar;

			foo['x']=100;
			foo['y']=200;

			bar['a']=11;
			bar['b']=22;
			bar['c']=33;

			foo.swap(bar);

			std::cout << "foo contains:\n";
			for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "bar contains:\n";
			for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			//answer
			// foo contains:
			// a => 11
			// b => 22
			// c => 33
			// bar contains:
			// x => 100
			// y => 200


			//set swap
			// int myints[]={12,75,10,32,20,25};
			// std::set<int> first (myints,myints+3);     // 10,12,75
			// std::set<int> second (myints+3,myints+6);  // 20,25,32

			// first.swap(second);

			// std::cout << "first contains:";
			// for (std::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			// std::cout << "second contains:";
			// for (std::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			//answer
			// first contains: 20 25 32
			// second contains: 10 12 75


			//vector erase
			// std::vector<int> myvector;

			// // set some values (from 1 to 10)
			// for (int i=1; i<=10; i++) myvector.push_back(i);

			// // erase the 6th element
			// myvector.erase (myvector.begin()+5);

			// // erase the first 3 elements:
			// myvector.erase (myvector.begin(),myvector.begin()+3);

			// std::cout << "myvector contains:";
			// for (unsigned i=0; i<myvector.size(); ++i)
			// 	std::cout << ' ' << myvector[i];
			// std::cout << '\n';

			//answer
			// myvector contains: 4 5 7 8 9 10
		}


		// {
		// 	std::vector<int>::iterator it1;
		// 	std::vector<int>::const_iterator it2;

		// 	it1 > it2;
		// }

}