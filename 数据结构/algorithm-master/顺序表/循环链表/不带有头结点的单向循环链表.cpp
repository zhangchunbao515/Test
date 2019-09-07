//不带头结点的循环单链表，2012-10-18 朱君鹏



#include <iostream>
#include <stdlib.h>
using namespace std;

//头结点类
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



//循环单链表类
template <class T>
class InkLink:public Linknode<T>
{
	private:
		Linknode<T> *head,*tail;
	public:
		int curlen;//如果将此句改成int curlen=0将会导致错误，只能在构造函数中对其进行初始化


		InkLink()
		{
			head=tail=NULL;
			curlen = 0;
		}


		~InkLink()
		{
			makeEmpty();
		}


		int create(T endTag);//创建一个循环单链表，引进标志位


		bool output();//输出循环单链表


		bool setPos(int i,T &x);//根据位置查找用户需要的数据值，并返回该值


		bool insert(int i);//在用户指定的位置之后插入新的节点


		bool makeEmpty();//置空循环单链表

};




template <class T>
int InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *newnode;
	for(;;)
	{
		cout<<"请输入链表的结点值:";
		cin>>a;
		if (a == endTag)  break;
		else
		{
			curlen++;
			newnode = new Linknode<T> (a);
			if (newnode == NULL)
			{
				cerr<<"分配存储空间错误"<<endl;
				exit(1);
			}
			if (head == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail -> next = newnode;
				tail = newnode;
			}
		}
	}
		tail -> next = head;
		return  curlen;
}



template <class T>
bool InkLink<T> :: output()
{
	int i = 1;
	Linknode<T> *current = head;
	for(i = 1;i <= (3*curlen);i++)
	{
		cout<<current -> data<<"->";
		current = current -> next;
	}
	return true;
}




template <class T>
bool InkLink<T> :: setPos(int i,T &x)
{
	if (i <= 0 || i > curlen)
	{
		cout<<"The location is illgal";
		return false;
	}
	Linknode<T> *current=head;
	int k = 1 ;
	for(k = 1;k <= curlen;k++)
	{
		if(k == i)
		{
			cout<<"The location is right";
			x = current -> data;
			break;
		}
		current = current -> next;
	}
	return true;
}




template <class T>
bool InkLink<T> :: insert (int i)
{
	if (i < 1 || i > curlen)
	{
		cout<<"The location is illgal";
		return false;
	}
	else
	{
		Linknode<T> *current = head;
		int k = 1;
		for(k = 1;k <i&&k <= curlen;k++)
		{
			if(k == i) break;
			else current = current -> next;
		}
		Linknode<T> *newnode;
		T a;
		cout<<"请输入要插入结点的数据值：";
		cin>>a;
		newnode = new Linknode<T> (a);
		newnode -> next = current -> next;
		current -> next = newnode;
		curlen++;
		return true;
	}
}



template <class T>
bool InkLink<T> :: makeEmpty()
{

	int i = 1;
	for(i = 1;i <= curlen;i++)
	{
		Linknode<T> *current = head;
		head = head -> next;
		delete current;
	}
	cout<<"链表为空"<<endl;
	curlen = 0;
	return true;
}





int main()
{
	InkLink<int> list;


    //创建循环单链表，并输出测试链表是否创建成功
	int m;
	cout<<"请用户输入创建链表时结束的标志位：";
	cin>>m;
	list.create(m);
	list.output();


    //测试根据位置查找数据值，并返回该值
	int i;
	int value=0;
	cout<<"请输入要查找的位置i:";
	cin>>i;
	list.setPos(i,value);
	cout<<endl;
	if(list.setPos(i,value))
	{
		cout<<"用户需要的数据值为："<<value<<endl;
	}
	else
	{
		cout<<"位置不合法,没有用户需要的数据"<<endl;
	}

    //测试插入并输出结果
	int k;
	cout<<"请输入要插入的结点的位置：";
	cin>>k;
	list.insert(k);
	list.output();


    //置空链表，并输出测试是否正确
	list.makeEmpty();
	list.output();
    return 0;
}






