/*
 * Basic Thing 
 * Author: hujiaqi
 * Editor: liuzinuo
*/
#define _TOPS_LANG
#define TOPS_LANG_VERSION "1.5.1"
#define _TOPS_LANG_VERSION "1.5.1"
#include <stddef.h>
#include <iostream>
#define cout std::cout
#define cerr std::cerr
void Throw(const char* s = "Size Error: Size of array is too big",int ret = 0xc0000005)
{
	cerr << s << '\n';
	exit(ret);
}
void Version()
{
	cout << TOPS_LANG_VERSION << '\n';
}
template <class T>
class Greater
{
public:
	bool operator()(T x,T y)
	{
		return x > y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is greater than y or not.";
	}
};
template <class T>
class Less
{
public:
	bool operator()(T x,T y)
	{
		return x < y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is less than y or not.";
	}
};
template <class T>
class Greater_equal
{
public:
	bool operator()(T x,T y)
	{
		return x >= y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is greater than y or x is as same as y or not.";
	}
};
template <class T>
class Less_equal
{
public:
	bool operator()(T x,T y)
	{
		return x <= y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is less than y or x is as same as y or not.";
	}
};
template <class T>
class Equal_to
{
public:
	bool operator()(T x,T y)
	{
		return x == y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is equal to y or not.";
	}
};
template <class T>
class Not_equal_to
{
public:
	bool operator()(T x,T y)
	{
		return x != y;
	}
	void help()
	{
		cout << "It is a function. It can check whether x is not equal to y or not.";
	}
};
template <class T>
class Iterator
{
protected:
	T* value;
public:
	Iterator (T* val = nullptr)
	{
		value = val;
	}
	operator T*()const
	{
		return value;
	}
	operator *()const
	{
		return *value;
	}
	operator -(const Iterator it)const
	{
		return value - it.value;
	}
	operator +(const Iterator it)const
	{
		return value + it.value;
	}
	operator <(const Iterator it)const
	{
		return value < it.value;
	}
	operator >(const Iterator it)const
	{
		return value > it.value;
	}
	operator ==(const Iterator it)const
	{
		return value == it.value;
	}
	operator >=(const Iterator it)const
	{
		return value >= it.value;
	}
	operator <=(const Iterator it)const
	{
		return value <= it.value;
	}
	operator !=(const Iterator it)const
	{
		return value != it.value;
	}
	static Iterator next(Iterator it)
	{
		return it + 1;
	}
	static Iterator prev(Iterator it)
	{
		return it - 1;
	}
	static void help()
	{
		cout << "Other thing like C++. You can use function next(it)/prev(it) to search the iterator next to it or prev to it.";
	}
};
