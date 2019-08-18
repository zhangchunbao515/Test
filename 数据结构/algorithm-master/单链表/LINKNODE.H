#ifndef _LINKNODE_H_
#define _LINKNODE_H_


#include <iostream>
using namespace std;
//创建单链表的头结点类
template <class T>
class Linknode
{
	public:
		T data;
		Linknode<T>  *next;
		Linknode(const T info,Linknode<T>  *newnext=NULL)
		{
			data=info;
			next=newnext;
		}
		Linknode(Linknode<T>  *newnext=NULL)
		{
			next=newnext;
		}
};

#endif