//����ͷ����ѭ��������2012-10-18 �����



#include <iostream>
#include <stdlib.h>
using namespace std;

//ͷ�����
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



//ѭ����������
template <class T>
class InkLink:public Linknode<T>
{
	private:
		Linknode<T> *head,*tail;
	public:
		int curlen;//������˾�ĳ�int curlen=0���ᵼ�´���ֻ���ڹ��캯���ж�����г�ʼ��


		InkLink()
		{
			head=tail=NULL;
			curlen = 0;
		}


		~InkLink()
		{
			makeEmpty();
		}


		int create(T endTag);//����һ��ѭ��������������־λ


		bool output();//���ѭ��������


		bool setPos(int i,T &x);//����λ�ò����û���Ҫ������ֵ�������ظ�ֵ


		bool insert(int i);//���û�ָ����λ��֮������µĽڵ�


		bool makeEmpty();//�ÿ�ѭ��������

};




template <class T>
int InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *newnode;
	for(;;)
	{
		cout<<"����������Ľ��ֵ:";
		cin>>a;
		if (a == endTag)  break;
		else
		{
			curlen++;
			newnode = new Linknode<T> (a);
			if (newnode == NULL)
			{
				cerr<<"����洢�ռ����"<<endl;
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
		cout<<"������Ҫ�����������ֵ��";
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
	cout<<"����Ϊ��"<<endl;
	curlen = 0;
	return true;
}





int main()
{
	InkLink<int> list;


    //����ѭ����������������������Ƿ񴴽��ɹ�
	int m;
	cout<<"���û����봴������ʱ�����ı�־λ��";
	cin>>m;
	list.create(m);
	list.output();


    //���Ը���λ�ò�������ֵ�������ظ�ֵ
	int i;
	int value=0;
	cout<<"������Ҫ���ҵ�λ��i:";
	cin>>i;
	list.setPos(i,value);
	cout<<endl;
	if(list.setPos(i,value))
	{
		cout<<"�û���Ҫ������ֵΪ��"<<value<<endl;
	}
	else
	{
		cout<<"λ�ò��Ϸ�,û���û���Ҫ������"<<endl;
	}

    //���Բ��벢������
	int k;
	cout<<"������Ҫ����Ľ���λ�ã�";
	cin>>k;
	list.insert(k);
	list.output();


    //�ÿ���������������Ƿ���ȷ
	list.makeEmpty();
	list.output();
    return 0;
}






