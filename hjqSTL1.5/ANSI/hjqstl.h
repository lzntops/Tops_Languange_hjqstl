/*
 * HJQSTL 1.5
 * ���ߣ�hujiaqi364
 * ��ֹ���˶�δ˵��
 * ��ΪANSI�ַ����汾��������UTF-8������
*/
#ifndef _HJQ_STL
#define _HJQ_STL
#define HJQ_STL_VERSION 1.5
#define _HJQ_STL_VERSION 1.5
#include<stddef.h>
#include<iostream>
#define cout std::cout
#define cerr std::cerr
/**********����**********/
void Throw(const char* s="����Խ��",int ret=0xc0000005)
{
	cerr<<s<<'\n';
	exit(ret);
}
void Version()
{
	cout<<HJQ_STL_VERSION<<'\n';
}
/**********�Ƚ���**********/
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
			cout<<"Greater˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ����y��\n";
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
			cout<<"Less˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ�С��y��\n";
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
			cout<<"Greater_equal˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ���ڻ����y��\n";
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
			cout<<"Less_equal˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ�С�ڻ����y��\n";
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
			cout<<"Equal_to˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ����y��\n";
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
			cout<<"Not_equal_to˵����\n";
			cout<<"�������ࣩ�ж�x�Ƿ񲻵���y��\n";
		}
};
/**********���ݽṹ**********/
template<class T>
class Iterator//������
{
	protected:
		T* value;
	public:
		Iterator(T* val=nullptr)//ָ��ת
		{
			value=val;
		}
		operator T*()const//תָ��
		{
			return value;
		}
		operator *()const//����
		{
			return *value;
		}
		operator -(const Iterator it)const//���
		{
			return value-it.value;
		}
		//�Ƚ�
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
			cout<<"Iterator˵����\n";
			cout<<"���ú���:\n";
			cout<<"next prev\n";
			cout<<"next(p):����p����һ����\n";
			cout<<"prev(p):����p����һ����\n";
		}
};
template<class T>
class Array//��̬����
{
	protected:
		T *datas;
		size_t siz;
	public:
		//��4��������priority_queue��
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		Array(size_t insiz=0,T indat=T())//��ʼ��
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
		~Array()//����
		{
			if(datas)
				delete[] datas;
		}
		T& operator[](const size_t&idx)const//[]�±����
		{
			if(idx>=siz)
				Throw();
			return datas[idx];
		}
		Array<T> operator+(const Array<T>&x)const//����
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
		Array<T> operator*(const size_t&x)const//�ظ�
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
		//�е�
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
		//��4���Ա�deque/vector
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
		void insert(T val,size_t pos)//����
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
		void erase(size_t pos)//ɾ��
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
		void reset(size_t insiz=0,T indat=NULL)//����
		{
			delete datas;
			siz=insiz;
			datas=new T[siz];
			for(size_t i=0;i<siz;i++)
				datas[i]=indat;
		}
		//����4����
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
		//Ҳ������priority_queue
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
			cout<<"Array˵����\n";
			cout<<"���ú���:\n";
			cout<<"Array[] Array+Array Array+=Array Array*size_t Array*=size_t\n";
			cout<<"push_back pop_back push_front pop_front insert\n";
			cout<<"erase reset size empty begin\n";
			cout<<"end front back help\n";
			cout<<"Array[x]:���ʵ�x�\n";
			cout<<"Array+Array Array+=Array:������Array�����ӡ�\n";
			cout<<"Array*size_t Array*=size_t:��Array�ظ�size_t�Ρ�\n";
			cout<<"push_back(x):��x����Array��β����\n";
			cout<<"pop_back(x):ɾ��Arrayβ����һ��ֵ��\n";
			cout<<"push_front(x):��x����Array�Ŀ�ͷ��\n";
			cout<<"pop_front(x):ɾ��Array��ͷ��һ��ֵ��\n";
			cout<<"insert(x,y):��yλ�ò���x��\n";
			cout<<"erase(y):ɾ��yλ�õ�ֵ��\n";
			cout<<"reset(x,y)/��ʼ������(x,y):����ArrayΪx��y��\n";
			cout<<"size():����ArrayԪ�ظ�����\n";
			cout<<"empty():����Array�Ƿ�Ϊ�ա�\n";
			cout<<"front():��ȡArray��ͷ��ֵ��\n";
			cout<<"front():��ȡArrayβ����ֵ��\n";
			cout<<"help():���˵���顣\n";
		}
};
template<class T>
class Stack:protected Array<T>//ջ
{
	public:
		//�ļ���
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
		void reset()//����
		{
			Array<T>::reset();
		}
		size_t size()//ͬArray
		{
			return Array<T>::siz;
		}
		static void help()
		{
			cout<<"Stack˵����\n";
			cout<<"���ú���:\n";
			cout<<"top pop toppop push reset\n";
			cout<<"size help\n";
			cout<<"top():����ջ����\n";
			cout<<"pop():����ջ����\n";
			cout<<"toppop():���ز�����ջ����\n";
			cout<<"push(x):��x����ջ����\n";
			cout<<"reset():���ջ��\n";
			cout<<"size():����ջԪ�ظ�����\n";
			cout<<"help():���˵���顣\n";
		}
};
template<class T>
class Queue:protected Array<T>//����
{
	public:
		//ͬStackջ
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
			cout<<"Queue˵����\n";
			cout<<"���ú���:\n";
			cout<<"front pop frontpop push reset\n";
			cout<<"size help\n";
			cout<<"front():���ض�ͷ��\n";
			cout<<"pop():������ͷ��\n";
			cout<<"frontpop():���ز�������ͷ��\n";
			cout<<"push(x):��x�����β��\n";
			cout<<"reset():��նӡ�\n";
			cout<<"size():���ض�Ԫ�ظ�����\n";
			cout<<"help():���˵���顣\n";
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
			cout<<"Pair˵����\n";
			cout<<"���ú���:\n";
			cout<<"first second\n";
			cout<<"first:��������ֵ��\n";
			cout<<"second:��������ֵ��\n";
		}
};
/**********����**********/
//���ң��ٷ�STLҲ�еġ����ɣ�
template<class T>
class _Find
{
	public:
		static void help()
		{
			cout<<"Find˵����\n";
			cout<<"˳�����begin��end�е�һ�γ���val��λ�ã������򷵻�end��\n";
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
			cout<<"Lower_bound˵����\n";
			cout<<"���ֲ���begin��end�е�һ�����ڵ���val��λ�ã������򷵻�end��\n";
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
			cout<<"Upper_bound˵����\n";
			cout<<"���ֲ���begin��end�е�һ������val��λ�ã������򷵻�end��\n";
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
			cout<<"Equal_range˵����\n";
			cout<<"����Pair<x,y>����val����[x,y)�ķ�Χ����Ȼ��ʹ��������\n";
		}
};
template<class T>
Pair<Iterator<T>,Iterator<T>> Equal_range(T* begin,T* end,T val)
{
	return Pair<T,T>(Lower_bound(begin,end,val),Upper_bound(begin,end,val));
}
/**********˵����**********/
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
			cout<<"Manual˵���� ˵�����˵���飬�����أ�������\n";
			cout<<"ʹ��Manual<type/function<anytype>>����ȡ��Ӧ��������������������ǰ��\"_\"��\n";
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

���붼�����õģ����Ĺ��������ϣ�����֧��
*/
