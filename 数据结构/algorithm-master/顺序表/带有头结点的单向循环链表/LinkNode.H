#ifndef _LINKNODE_H_
#define _LINKNODE_H_

#include <iostream>
using namespace std;
template <class T>
class Linknode
{
	public:
		T data;
		Linknode<T> *next;
		Linknode(T const info,Linknode<T> *newnext=NULL)
		{
			data=info;
			next=newnext;
		}
		Linknode(Linknode<T> *newnext=NULL)
		{
			next=newnext;
		}
};

#endif