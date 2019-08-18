//带有头结点的单链表


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
//创建单链表类
template <class T>
class InkLink:public Linknode<T>//继承单链表的头结点类
{
	public:
		Linknode<T> *head,*tail;//创建头指针
		InkLink()
		{
			head = tail = new Linknode<T>(NULL);//创建头结点
		}
		void create(T endTag);//endTag为标志结束位，由用户自定义
		bool output();//输出函数
		void length();//求单链表的长度
		Linknode<T> *setPos(int i);//确定位置并返回此节点的指针值
	    bool makeEmpty()
		{
			Linknode<T> *temp;
			while(head->next!=NULL)
			{
				temp=head;
				head=head->next;
				delete temp;
			}
			return true;
		}//置空单链表
		bool insert(int i);//按位置插入
		~InkLink()
		{
			makeEmpty();
		}
};
template <class T>
void InkLink<T> :: create(T endTag)//endTag为循环结束的标志，由用户自己定义，此类只能实现输入键盘上的字符，更复杂的不能实现
{
	T a;
	Linknode<T>  *p=NULL;
	for(;;)
	{
		cout<<"请输入结点的数据值，当输入endTag时创建链表工作结束";
		cin>>a;
		if (a==endTag)  break;
		p=new Linknode<T>(a);//动态申请结点
		tail->next = p;
		tail = p;//接在头结点上面
	}
};
template <class T>
bool InkLink<T> :: output()
{
	Linknode<T> *p=head;
	if (p->next==NULL)//带有头结点的单链表是否为空的判断方法
	{
		cout<<"The list is empty"<<endl;
		return false;
	}//健壮性的判断
	else
	{
		while(p->next!=NULL)
		{
			cout<<p->next->data<<"->";
			p->next=p->next->next;
		}
		cout<<"The list is not empty"<<endl;
		return true;
	}
};
template <class T>
void InkLink<T> :: length()
{
	int count=0;
	Linknode<T> *current = head->next;
	while(current!=NULL)
	{
		count++;
		current = current->next;
	}
	cout<<"The lengthes of list is:"<<count<<endl;
};
template <class T>
Linknode<T>  *InkLink<T> :: setPos(int i)
{
	Linknode<T> *current=head;
	int count=0;
	if(i<0)
	{
		cout<<"The locate is illgal"<<endl;
		return NULL;
	};
	while(current!=NULL&&count<i)
	{
			current=current->next;
			count++;
			cout<<"The locate is right:"<<endl;
	}
	return current;
};
template <class T>
bool InkLink<T> ::insert(int i)
{
	if(i<0)
	{
		cout<<"The locate is illgal"<<endl;
		return NULL;
	}//健壮性的判断
	T a;
	cout<<"请输入要插入的结点的数据值:";
	cin>>a;
	Linknode<T> *p=setPos(i);

	Linknode<T> *newnode=new Linknode<T>(a);//动态申请一个新的结点用作插入
	newnode->next=p->next;/*如果这句和下面一句反过来执行就会发生错误*/
	p->next=newnode;
	//newnode->next=p->next;
	return true;
};
int main()
{
	InkLink<int> list;
	cout<<"请输入标志位，由用户自定义,输入在键盘上能敲入的字符:";
	int m;//标志位，由用户自定义
	cin>>m;

	list.create(m);
	list.output();
	list.length();

	int i;
	cout<<"请输入要插入结点的位置:";
	cin>>i;
	list.setPos(i);
	list.insert(i);
	list.output();

	list.makeEmpty();
	list.output();
	return 0;
}
