#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
#include <iostream>
using namespace std;


//链式栈的物理实现
template <class T>
class Stacknode //链式栈的结点类
{
	public:
		T data;//数据域
		Stacknode<T> *prev;//前驱指针域
		//构造函数，因为不含头结点，所以只用以个构造函数
		Stacknode (T const info,Stacknode<T> *newprev = NULL)
		{
			data = info;
			prev = newprev;
		}
		Stacknode(Stacknode<T> *newprev=NULL)//此构造函数主要用于创建带有头结点的单链表的头结点
		{
	
			prev = newprev;
		}

};


template <class T>
class LinkStack : public Stacknode<T>
{
	private:
		Stacknode<T> *top;//头指针
	public:
		LinkStack()
		{
			top = NULL;//构造函数，标准化的初始数据成员的方法
		}

		~LinkStack()//析构函数，调用置空函数得到
		{
			makeEmpty();
		}

		bool makeEmpty()//置空函数
		{
			Stacknode<T> *current = top;//动态申请一个新的指针，将原来栈的头指针赋值给新的指针
			Stacknode<T> *temp;//创建一个临时的动态指针
			while(current!=NULL)//循环结束的条件
			{
				temp = current;
				current = current->prev;
				delete temp;
			}
			return true;
		}

		bool Push(T value);
		bool Pop(T &value);
		bool getTop(T &value);
		bool isEmpty()
		{
			if (top == NULL)//判断链式栈是否为空的条件 
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};


//进栈分两种情况
template <class T>
bool LinkStack<T> :: Push(T value)
{
	if (top == NULL)
	{
		Stacknode<T> *p;
		p = new Stacknode<T>(value);//动态申请一个节点，并且将用户需要的数值赋值给新结点的数据域
		top = p;//栈顶指针指向新申请的结点
		return true;
	}

	else
	{
		Stacknode<T> *p;
		p = new Stacknode<T>(value);//动态申请一个节点，并且将用户需要的数值赋值给新结点的数据域
		p->prev = top;//新申请的结点的前驱指针域指向当前top指针
		top = p;//并将top指针指向新申请的结点，从而实现每个新节点接到链上，并且保证top始终指向当前的结点
		return true;
	}
}


//出栈
template <class T>
bool LinkStack<T> :: Pop(T &value)
{
	if (top == NULL)//如果栈为空，返回错误
	{
		return false;
	}

	else
	{
		Stacknode<T> *current = top;
		value = current->data;
		top = current->prev;
		delete current;
		return true;
	}
}


template <class T> 
bool LinkStack<T> :: getTop(T &value)
{
	if (top == NULL)
	{
		return false;
	}
	else
	{
		value = top->data;
		return true;
	}
}

#endif 