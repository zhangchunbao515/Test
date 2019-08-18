#ifndef _INKLINK_H_
#define _INKLINK_H_
#include <iostream>
#include "LINKNODE.H"
using namespace std;

template <class T>
class InkLink
{
	private:
		Linknode<T> *head,*tail;
	public:
		int curlen;
		InkLink()
		{
			head=tail=new Linknode<T>(NULL);
			tail->next=head;
			curlen = 0;
		}
		void create(T endTag);
		bool output();
		bool setPos(int i ,T &value);//根据位置找元素
		bool find(T value,int &i);
};
template <class T>
void InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *newnode;
	for(;;)
	{
		cout<<"请输入结点的数据值:";
		cin>>a;
		if (a==endTag)  break;
		else
		{
			curlen++;
			newnode=new Linknode<T>(a);
			tail->next=newnode;
			tail=newnode;
			tail->next=head;
		}
	}
};
template <class T>
bool InkLink<T> :: output()
{
	int i=0;
	Linknode<T> *current=head;
	for(i=0;i<(3*curlen+2);i++)
	{
		cout<<current->next->data<<"->";
		current=current->next;
	}
	return true;
};
template <class T>
bool InkLink<T> :: setPos(int i,T &value)
{
	if (i<=0||i>curlen)
	{
		return false;
	}
	else
	{
		Linknode<T> *current = head->next;
		int k=1;
		for(k=1;k<curlen;k++)
		{
			if( k == i )
			{
				value=current->data;
				return true;
			}
			else
			{
				current = current->next;
			}
		}
	}
	return false;
}
template <class T>
bool InkLink<T> :: find(T value,int &i)
{
	Linknode<T> *current = head->next;
	int k=1;
	while( current !=head&&current->data!=value)
	{
		current = current->next;
		k++;
	}
	if (current->data == value)
	{
		i=k;
		return true;
	}
	else
	{
		return false;
	}

}
#endif