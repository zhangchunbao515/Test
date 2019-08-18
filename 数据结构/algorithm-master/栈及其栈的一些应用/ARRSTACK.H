#ifndef _ARRSTACK_H_
#define _ARRSTACK_H_


//顺序栈的物理实现方法，其中包含一个衣橱处理函数，此函数为类的私有成员
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int stackIncreament = 20;//全局变量，用于溢出处理时动态的增加需要的存储单元数
template <class T>
class Stack
{
	private:
		T *elements;
		int maxSize;
		int top;//栈顶指针
		void overflowprocess();//溢出处理函数
	public:
		Stack ( int size )
		{
			maxSize = size;
			elements = new T[maxSize];
			//此函数不能使用，系统提示不提供，assert( elements != NULL );//使用了断言语句，当参数表达式成立时，程序继续执行；否则进入中断处理程序，程序终止其代替语句如下
			if ( elements == NULL)
			{
				cout<<"分配存储空间错误\n"<<endl;
				exit(1);
			}//判断动态申请空间是否成功，标注化的语句
			top = -1;
		}
		~Stack()
		{
			delete []elements;//析构数组类的指针对象时用的标注化方法
		}
		bool Push( const T &x );//压入栈顶
		bool Pop( T &x );//出栈
		bool getTop(T &x);//获得栈顶元素的值
bool isEmpty()
		{
			if ( top == -1)
			{
				cout<<"栈为空"<<endl;
				return true;
			}
			else
				return false;
		}
};

//此函数为溢出处理函数，当分配的空间不足时，动态重新为其分配存储空间
template <class T>
void Stack<T> :: overflowprocess()
{
	T *arrStack = new T[maxSize + stackIncreament];//动态重新申请一个更大的存储空间，用于溢出处理
	if (arrStack == NULL)
	{
		cout<<"分配存储空间错误\n"<<endl;
		exit(1);
	}//标准化的判断动态申请的空间是否成功的申请
	int i=0;
	for ( i = 0;i <=top;i++ )
	{
		arrStack[i] = elements[i];//将原来数组的每一个元素分别赋值给新创建的数组
	}
	delete []elements;//析构旧数组
	elements = arrStack;//将新创建的更大的数组命名为前数组的名字，便于操作
}


template <class T>
bool Stack<T> :: Push( const T &x )//压栈函数，带一个引用型参数
{
	if (top == maxSize - 1) //判断栈是否为满，如果满，则调用溢出处理函数重新分配空间
	{
		cout<<"分配空间不足，调用类函数重新为其分配空间";
		cout<<endl;
		overflowprocess();
	}
	top++;
	elements[top] = x;//现将栈顶指针上移，然后将用户需要的数值压入栈顶
	return true;//返回语句，无条件的转移语句，执行return之后，后面的语句将不再执行，因为已回到程序断点
}


template <class T>
bool Stack<T> :: Pop( T &x )//出栈函数
{
	if ( top == -1)//判断栈是否为空，如果为空直接返回；否则执行下面的语句
	{
		cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		top--;
		return true;
	}
}


template <class T>
bool Stack<T> :: getTop( T &x )//获得栈顶指针的值，用引用型参数向外传递栈顶元素的值
{
	if ( top == -1 )//判断栈是否为空
	{
		cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		return true;
	}
}

/*void main()//主函数分段测试类成员函数的正确性
{
	int size=0;
	cout<<"请输入栈空间的预计最大值:";
	cin>>size;
	Stack<int> s(size);

	int value=0;
	cout<<"请输入要压入栈顶的元素值:";
	cin>>value;
	s.Push(value);


	int n;
	s.Pop(n);
	cout<<"栈顶元素的值为："<<n;
	cout<<endl;


	int x=0;
	s.getTop(x);
	if ( s.getTop(x) )
	{
		cout<<"栈顶元素的值为："<<x;
		cout<<endl;
	}
	else
	{
		cout<<"栈为空，无法获得栈顶元素值";
	}
}*/
#endif
