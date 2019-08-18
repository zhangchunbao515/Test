
#include <iostream>
using namespace std;
template <class T>//创建单链表的结点模板类
class Linknode
{
	public:
		T data;
		Linknode<T> *next;
		Linknode(T const info,Linknode<T> *newnext=NULL)//此构造函数主要用来创建除头结点以外的其它结点
		{
			data=info;
			next=newnext;
		}
		Linknode(Linknode<T> *newnext=NULL)//此构造函数主要用于创建带有头结点的单链表的头结点
		{
			next=newnext;
		}
};
template <class T>//创建单链表类
class InkLink:public Linknode<T>//链表类继承上面的结点类，并且是公有继承
{
	private:
		Linknode<T> *head,*tail;//私有的头尾指针
	public:
		InkLink()
		{
			head=tail=NULL;
		}//构造函数，标准化的给数据成员初始化的方法
		void create(T endTag);//创建一个单链表，形式参数为循环结束的标志，此标志位由用户自定义
		bool output();//输出单链表的每一个结点的数据值
		bool makeEmpty();//置空单链表，释放空间
		~InkLink()
		{
			Linknode<T> *temp;//创建一个临时变量，用来释放空间
			while(head!=NULL)//条件为单链表不为空的条件
			{
				temp=head;
				head=head->next;//先将下一个结点的值赋值给头指针
				delete temp;//释放结点空间
			}
		}//析构函数，用来释放结点空间
		Linknode<T> *setPos(int i);//根据用户输入的相对位置查找值，并返回该结点的指针
		bool insert(int i);//根据用户的需要插入新的结点
		int length();//求单链表的长度
		bool getpos( int &p,const T	value);//根据用户的需要输入要查找的数据值，从而实现在单链表中查找是否存在该数据，如果存在返回其相对地址
};
template <class T>
void InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *p1,*p2;//创建两个临时变量
	cout<<"请输入a的值，当值与标志结束数据值相同时停止输入:";
	for(;;)
	{
		cin>>a;
		if (a==endTag) break;//循环结束的标志
		p1=new Linknode<T>(a);//动态申请空间赋值给p1
		if(head==NULL)
		{
			head=p1;
			p2=p1;//将第一个结点用p2关联
		}//如果头指针为空时先将动态申请的结点接在头指针上面
		else
		{
			p2->next=p1;
			p2=p1;
		}
		tail=p2;
		tail->next=head;
	}
};
/*此函数的时间复杂度为O（n），循环次数由标志位决定*/
template <class T>
bool InkLink<T> :: output()
{
	Linknode<T> *current = head;//尽量避免使用头指针直接输出，所以将其赋值给一个临时的局部变量
	while(current != NULL)
	{
		cout<<current->data<<"->";
		current = current->next;
	}
	return true;
};
/*此函数的时间复杂度为O（n）,循环次数由标志位决定*/
template <class T>
Linknode<T> *InkLink<T> :: setPos(int i)
{
	if (i<0)
	{
		cout<<"The location is illgal"<<endl;
		return NULL;
	}//健壮性的判断
	if (head!=NULL)
	{
		int count=0;
		Linknode<T> *current=head;
		for(;;)
		{
			if(count==i)
			{
				return current;
				break;
			}
	current=current->next;
	count++;
		}
	}
	if (head==NULL)
	{
		cout<<"The location is illgal"<<endl;
		return false;
	}
};
/*该函数最坏情况下的时间复杂度为O（n），最坏情况下循环次数由标志位决定*/
template <class T>
bool InkLink<T> :: insert(int i) //实现在指定位置之后的插入，人为规定链表第一个结点的相对位置为0
{
	if (i<0)
	{
		cout<<"The location is illgal"<<endl;
		return false;
	}
	if (head!=NULL)
	{
		Linknode<T> *current=setPos(i);
		T a;
		cout<<"请输入要插入结点的数据值a:";
		cin>>a;
		Linknode<T> *newnode=new Linknode<T>(a);
		newnode->next=current->next;
		current->next=newnode;
		return true;
	}
	if (head==NULL)
	{
		T a;
		cout<<"请输入要插入结点的数据值：";
		cin>>a;
		Linknode<T> *current=new Linknode<T> (a);
		head=tail=current;
		return true;
	}
};
/*该函数最坏情况下的时间复杂度为O（n），最坏情况下循环次数由标志位决定,在调用setPos（int i）时涉及到循环*/
template <class T>
int InkLink<T> :: length()
{
	if(head==NULL)
	{
		cout<<"The list is empty";
		return 0;
	}
	int count=0;
	Linknode<T> *current=head;
	while(current!=NULL)
	{
		count++;
		current=current->next;
	}
	return count;
};
/*此函数的时间复杂度为O（n）,循环次数由标志位决定*/
//实现单链表的置空（2012.10.13）
template <class T>
bool InkLink<T> :: makeEmpty()
{

	if (head==NULL)
	{
		cout<<"The list is empty"<<endl;
		return false;
	}
	else
	{
		while(head!=NULL)
		{
			Linknode <T> *current=head;
			head=head->next;
			delete current;
		}
		return true;
	}
};
/*此函数的时间复杂度为O（n）,循环次数由标志位决定*/
//此函数实现根据用户的需要输入要查找的值，然后再链表中查找值的位置，并返回该结点的相对位置（2012.10.14），此函数的健壮性不好，许改进
template <class T>
bool InkLink<T> :: getpos (int &p,const T value)
{
	int i=0;
	Linknode<T>  *current =head;
	for(;current !=NULL;)
	{
		if (current->data == value)
		{
			p=i;
			break;
		}
		current =current->next;
		i++;
	}
	return true;
};
/*此函数的时间复杂度为O（n）,循环次数由标志位决定*/
int main()
{
	int n=0;int value;
	InkLink <int> list;
	int m;
	cout<<"请输入标志位，只能实现键盘上单字符的输入，提示字符的结束标志为\0:";
	cin>>m;
	int i;
	cout<<"please iuput find location i:";
	cin>>i;
	list.create(m);
	cout<<endl;
	list.output();
	cout<<"The long of list is:"<<list.length()<<endl;
	list.setPos(i);
	list.insert(i);
	list.output();
	cout<<endl;
	cout<<"The long of list is:"<<list.length()<<endl;
	cout<<"请输入要查询结点的值：";
	cin>>value;
	list.getpos(n,value);
	cout<<"要查询的值得位置为："<<n;
	list.makeEmpty();
	cout<<endl;
	cout<<"The long of list is:"<<list.length()<<endl;
    return 0;
}
