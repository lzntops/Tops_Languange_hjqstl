/*
 * HJQSTL 1.5
 * 作者：hujiaqi364
 * 禁止搬运而未说明
 * 此为UTF-8字符集版本，不兼容ANSI！！！
*/
#ifndef _HJQ_STL
#define _HJQ_STL
#define HJQ_STL_VERSION 1.5
#define _HJQ_STL_VERSION 1.5
#include<stddef.h>
#include<iostream>
#define cout std::cout
#define cerr std::cerr
/**********报告**********/
void Throw(const char* s="数组越界",int ret=0xc0000005)
{
	cerr<<s<<'\n';
	exit(ret);
}
void Version()
{
	cout<<HJQ_STL_VERSION<<'\n';
}
/**********比较器**********/
template<class T>
class Greater
{
	public:
		bool operator()(T x,T y)
		{
			return x>y;
		}
		void help()
		{
			cout<<"Greater说明书\n";
			cout<<"（函数类）判断x是否大于y。\n";
		}
};
template<class T>
class Less
{
	public:
		bool operator()(T x,T y)
		{
			return x>y;
		}
		void help()
		{
			cout<<"Less说明书\n";
			cout<<"（函数类）判断x是否小于y。\n";
		}
};
template<class T>
class Greater_equal
{
	public:
		bool operator()(T x,T y)
		{
			return x>=y;
		}
		void help()
		{
			cout<<"Greater_equal说明书\n";
			cout<<"（函数类）判断x是否大于或等于y。\n";
		}
};
template<class T>
class Less_equal
{
	public:
		bool operator()(T x,T y)
		{
			return x<=y;
		}
		void help()
		{
			cout<<"Less_equal说明书\n";
			cout<<"（函数类）判断x是否小于或等于y。\n";
		}
};
template<class T>
class Equal_to
{
	public:
		bool operator()(T x,T y)
		{
			return x==y;
		}
		void help()
		{
			cout<<"Equal_to说明书\n";
			cout<<"（函数类）判断x是否等于y。\n";
		}
};
template<class T>
class Not_equal_to
{
	public:
		bool operator()(T x,T y)
		{
			return x>=y;
		}
		void help()
		{
			cout<<"Not_equal_to说明书\n";
			cout<<"（函数类）判断x是否不等于y。\n";
		}
};
/**********数据结构**********/
template<class T>
class Iterator//迭代器
{
	protected:
		T* value;
	public:
		Iterator(T* val=nullptr)//指针转
		{
			value=val;
		}
		operator T*()const//转指针
		{
			return value;
		}
		operator *()const//引用
		{
			return *value;
		}
		operator -(const Iterator it)const//相减
		{
			return value-it.value;
		}
		//比较
		operator <(const Iterator it)const
		{
			return value<it.value;
		}
		operator >(const Iterator it)const
		{
			return value>it.value;
		}
		operator ==(const Iterator it)const
		{
			return value==it.value;
		}
		operator >=(const Iterator it)const
		{
			return value>=it.value;
		}
		operator <=(const Iterator it)const
		{
			return value<=it.value;
		}
		operator !=(const Iterator it)const
		{
			return value!=it.value;
		}
		static Iterator next(Iterator it)
		{
			return it+1;
		}
		static Iterator prev(Iterator it)
		{
			return it-1;
		}
		static void help()
		{
			cout<<"Iterator说明书\n";
			cout<<"可用函数:\n";
			cout<<"next prev\n";
			cout<<"next(p):返回p的下一个。\n";
			cout<<"prev(p):返回p的上一个。\n";
		}
};
template<class T>
class Array//动态数组
{
	protected:
		T *datas;
		size_t siz;
	public:
		//这4个是适配priority_queue的
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		Array(size_t insiz=0,T indat=T())//初始化
		{
			siz=insiz;
			datas=new T[siz];
			for(size_t i=0;i<siz;i++)
				datas[i]=indat;
		}
		Array(Iterator<T> b,Iterator<T> e)
		{
			siz=e-b;
			datas=new T[siz];
			for(Iterator<T> it=b;it<e;it=Iterator<T>::next(it))
				datas[it-b]=*it;
		}
		~Array()//析构
		{
			if(datas)
				delete[] datas;
		}
		T& operator[](const size_t&idx)const//[]下标访问
		{
			if(idx>=siz)
				Throw();
			return datas[idx];
		}
		Array<T> operator+(const Array<T>&x)const//连接
		{
			Array<T>ret(siz+x.size());
			for(int i=0;i<siz;i++)
				ret[i]=datas[i];
			for(int i=siz;i<siz+x.size();i++)
				ret[i]=x[i-siz];
			return ret;
		}
		void operator+=(const Array<T>&x)
		{
			*this=(*this)+x;
		}
		Array<T> operator*(const size_t&x)const//重复
		{
			Array<T>ret(siz*x);
			for(int i=0;i<x;i++)
				for(int j=0;j<siz;j++)
					ret[x*i+j]=datas[j];
			return ret;
		}
		void operator*=(const size_t&x)
		{
			*this=(*this)*x;
		}
		//判等
		bool operator==(const Array<T>&x)const
		{
			if(siz!=x.size())
				return 0;
			for(int i=0;i<siz;i++)
				if(datas[i]!=x[i])
					return 0;
			return 1;
		}
		bool operator!=(const Array<T>&x)const
		{
			if(siz!=x.size())
				return 1;
			for(int i=0;i<siz;i++)
				if(datas[i]==x[i])
					return 0;
			return 1;
		}
		//这4个对标deque/vector
		void push_back(T val)
		{
			T *newdatas=new T[siz+1];
			for(size_t i=0;i<siz;i++)
				newdatas[i]=datas[i];
			newdatas[siz]=val;
			delete datas;
			datas=newdatas;
			siz++;
		}
		void pop_back()
		{
			if(siz==0)
				Throw();
			T *newdatas=new T[siz-1];
			for(size_t i=0;i<siz-1;i++)
				newdatas[i]=datas[i];
			delete datas;
			datas=newdatas;
			siz--;
		}
		void push_front(T val)
		{
			T *newdatas=new T[siz+1];
			newdatas[0]=val;
			for(size_t i=1;i<=siz;i++)
				newdatas[i]=datas[i-1];
			delete datas;
			datas=newdatas;
			siz++;
		}
		void pop_front()
		{
			if(siz==0)
				Throw();
			T *newdatas=new T[siz-1];
			for(size_t i=0;i<siz-1;i++)
				newdatas[i]=datas[i+1];
			delete datas;
			datas=newdatas;
			siz--;
		}
		void insert(T val,size_t pos)//插入
		{
			if(pos>siz)
				Throw();
			T *newdatas=new T[siz+1];
			for(size_t i=0;i<pos;i++)
				newdatas[i]=datas[i];
			newdatas[pos]=val;
			for(size_t i=pos+1;i<=siz;i++)
				newdatas[i]=datas[i-1];
			delete datas;
			datas=newdatas;
			siz++;
		}
		void erase(size_t pos)//删除
		{
			if(siz==0||pos>=siz)
				Throw();
			T *newdatas=new T[siz-1];
			for(size_t i=0;i<pos;i++)
				newdatas[i]=datas[i];
			for(size_t i=pos+1;i<siz;i++)
				newdatas[i-1]=datas[i];
			delete datas;
			datas=newdatas;
			siz--;
		}
		void reset(size_t insiz=0,T indat=NULL)//重设
		{
			delete datas;
			siz=insiz;
			datas=new T[siz];
			for(size_t i=0;i<siz;i++)
				datas[i]=indat;
		}
		//经典4件套
		size_t size()
		{
			return siz;
		}
		bool empty()
		{
			return siz==0;
		}
		Iterator<T> begin()
		{
			return datas;
		}
		Iterator<T> end()
		{
			return datas+siz;
		}
		//也是适配priority_queue
		T front()const
		{
			return datas[0];
		}
		T back()const
		{
			return datas[siz-1];
		}
		static void help()
		{
			cout<<"Array说明书\n";
			cout<<"可用函数:\n";
			cout<<"Array[] Array+Array Array+=Array Array*size_t Array*=size_t\n";
			cout<<"push_back pop_back push_front pop_front insert\n";
			cout<<"erase reset size empty begin\n";
			cout<<"end front back help\n";
			cout<<"Array[x]:访问第x项。\n";
			cout<<"Array+Array Array+=Array:将两个Array相连接。\n";
			cout<<"Array*size_t Array*=size_t:将Array重复size_t次。\n";
			cout<<"push_back(x):将x加入Array的尾部。\n";
			cout<<"pop_back(x):删除Array尾部的一个值。\n";
			cout<<"push_front(x):将x加入Array的开头。\n";
			cout<<"pop_front(x):删除Array开头的一个值。\n";
			cout<<"insert(x,y):在y位置插入x。\n";
			cout<<"erase(y):删除y位置的值。\n";
			cout<<"reset(x,y)/初始化函数(x,y):重置Array为x个y。\n";
			cout<<"size():返回Array元素个数。\n";
			cout<<"empty():返回Array是否为空。\n";
			cout<<"front():获取Array开头的值。\n";
			cout<<"front():获取Array尾部的值。\n";
			cout<<"help():输出说明书。\n";
		}
};
template<class T>
class Stack:protected Array<T>//栈
{
	public:
		//四件套
		T top()
		{
			return Array<T>::datas[0];
		}
		void pop()
		{
			Array<T>::pop_front();
		}
		T toppop()
		{
			T p=Array<T>::datas[0];
			Array<T>::pop_front();
			return p;
		}
		void push(T val)
		{
			push_front(val);
		}
		void reset()//重设
		{
			Array<T>::reset();
		}
		size_t size()//同Array
		{
			return Array<T>::siz;
		}
		static void help()
		{
			cout<<"Stack说明书\n";
			cout<<"可用函数:\n";
			cout<<"top pop toppop push reset\n";
			cout<<"size help\n";
			cout<<"top():返回栈顶。\n";
			cout<<"pop():弹出栈顶。\n";
			cout<<"toppop():返回并弹出栈顶。\n";
			cout<<"push(x):将x加入栈顶。\n";
			cout<<"reset():清空栈。\n";
			cout<<"size():返回栈元素个数。\n";
			cout<<"help():输出说明书。\n";
		}
};
template<class T>
class Queue:protected Array<T>//队列
{
	public:
		//同Stack栈
		T front()
		{
			return Array<T>::datas[0];
		}
		void pop()
		{
			Array<T>::pop_front();
		}
		T frontpop()
		{
			T p=Array<T>::datas[0];
			Array<T>::pop_front();
			return p;
		}
		void push(T val)
		{
			push_back(val);
		}
		void reset()
		{
			Array<T>::reset();
		}
		size_t size()
		{
			return Array<T>::siz;
		}
		static void help()
		{
			cout<<"Queue说明书\n";
			cout<<"可用函数:\n";
			cout<<"front pop frontpop push reset\n";
			cout<<"size help\n";
			cout<<"front():返回队头。\n";
			cout<<"pop():弹出队头。\n";
			cout<<"frontpop():返回并弹出队头。\n";
			cout<<"push(x):将x加入队尾。\n";
			cout<<"reset():清空队。\n";
			cout<<"size():返回队元素个数。\n";
			cout<<"help():输出说明书。\n";
		}
};
template<class T1,class T2>
class Pair
{
	public:
		T1 first=NULL;
		T2 second=NULL;
		Pair(T1 f=NULL,T2 s=NULL)
		{
			first=f;
			second=s;
		}
		static void help()
		{
			cout<<"Pair说明书\n";
			cout<<"可用函数:\n";
			cout<<"first second\n";
			cout<<"first:变量，左值。\n";
			cout<<"second:变量，右值。\n";
		}
};
/**********函数**********/
//查找（官方STL也行的……吧）
template<class T>
class _Find
{
	public:
		static void help()
		{
			cout<<"Find说明书\n";
			cout<<"顺序查找begin到end中第一次出现val的位置，若无则返回end。\n";
		}
};
template<class T>
Iterator<T> Find(Iterator<T> begin,Iterator<T> end,T val)
{
	for(Iterator<T> i=begin;i!=end;i=Iterator<T>::next(i))
		if(*i==val)
			return i;
	return end;
}
template<class T>
class _Lower_bound
{
	public:
		static void help()
		{
			cout<<"Lower_bound说明书\n";
			cout<<"二分查找begin到end中第一个大于等于val的位置，若无则返回end。\n";
		}
};
template<class T>
Iterator<T> Lower_bound(Iterator<T> begin,Iterator<T> end,T val)
{
	while(begin<end)
	{
		Iterator<T> mid=(begin+end)/2;
		if(*mid<val)
			begin=mid;
		else
			end=mid;
	}
	return end;
}
template<class T>
class _Upper_bound
{
	public:
		static void help()
		{
			cout<<"Upper_bound说明书\n";
			cout<<"二分查找begin到end中第一个大于val的位置，若无则返回end。\n";
		}
};
template<class T>
Iterator<T> Upper_bound(Iterator<T> begin,Iterator<T> end,T val)
{
	while(begin<end)
	{
		Iterator<T> mid=(begin+end)/2;
		if(*mid>val)
			end=mid;
		else
			begin=mid;
	}
	return end;
}
template<class T>
class _Equal_range
{
	public:
		static void help()
		{
			cout<<"Equal_range说明书\n";
			cout<<"返回Pair<x,y>，将val插入[x,y)的范围内仍然能使数组有序。\n";
		}
};
template<class T>
Pair<Iterator<T>,Iterator<T>> Equal_range(T* begin,T* end,T val)
{
	return Pair<T,T>(Lower_bound(begin,end,val),Upper_bound(begin,end,val));
}
/**********说明类**********/
template<class T>
class Manual
{
	public:
		Manual()
		{
			T::help();
		}
		static void help()
		{
			cout<<"Manual说明书 说明书的说明书，套娃呢（划掉）\n";
			cout<<"使用Manual<type/function<anytype>>，获取对应帮助。（函数须在名字前加\"_\"）\n";
		}
};
#endif
/*
       /-/    /-/           /-/   /--------\    /--------\   /---------/   /-/              /-/          /--------/
      /-/    /-/           /-/   /-/     /-/   /-/     \-/       /-/      /-/            /---/          /-/
     /-/    /-/           /-/   /-/     /-/   /-/               /-/      /-/              /-/          /-/
    /--------/           /-/   /-/     /-/    \--------\       /-/      /-/              /-/           \--------\
   /-/    /-/           /-/   /-/     /-/            /-/      /-/      /-/              /-/                    \-\
  /-/    /-/   /-\     /-/   /-/     /-/    /-\     /-/      /-/      /-/              /-/       /-/   /-\     /-/
 /-/    /-/    \--------/    \-------\-\    \--------/      /-/      /---------/    /------/    /-/    \--------/

b                 h               j i             i 3333   6666   4 4
b                 h                                     3 6      4  4
b                 h               j i             i     3 6     4   4
b bb  y   y       h hh  u   u     j i  aa    qqqq i  333  6666  4   4
bb  b y   y       hh  h u   u     j i a  a  q   q i     3 6   6 44444
b   b  y  y       h   h u   u     j i a  a  q   q i     3 6   6     4
bbbb    yyy       h   h  uuuu     j i  aaaa  qqqq i 3333   666      4
          y                       j             q                    
         y                    j   j             q                    
      yyy                      jjj              q                    

代码都是手敲的，查阅过各种资料，还请支持
*/
