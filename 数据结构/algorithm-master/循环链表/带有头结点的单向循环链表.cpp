//带有头结点的循环链表
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
template <class T>
class InkLink:public Linknode<T>
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
	for(i=0;i<(2*curlen+1);i++)
	{
		cout<<current->next->data<<"->";
		current=current->next;
	}
	return true;
};
int main()
{
	InkLink<int> list;

	int m;
	cout<<"请输入标志位:";
	cin>>m;
	list.create(m);
	list.output();
	return 0;
}
