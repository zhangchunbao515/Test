//����ͷ����ѭ������
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
		bool setPos(int i ,T &value);//����λ����Ԫ��
		bool find(T value,int &i);
};
template <class T>
void InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *newnode;
	for(;;)
	{
		cout<<"�������������ֵ:";
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


int main()
{
	InkLink<int> list;

	int m;
	cout<<"�������־λ:";
	cin>>m;
	list.create(m);
	list.output();
	cout<<endl;


	int i;
	cout<<"������Ҫ���ҵĺϷ�λ��i:";
	cin>>i;
	int n;
	list.setPos(i,n);
	if (list.setPos(i,n))
	{
		cout<<"Ҫ���ҵ�λ�õ�����ֵΪ"<<"n="<<n;
	}
	else
	{
		cout<<"�����λ�ò��Ϸ����޷�������Ҫ�Ĳ���";
	}
	cout<<endl;


	int k;
	cout<<"������Ҫ���ҵ�����ֵk=";
	cin>>k;
	int j;//���ص�λ�ñ���
	if( list.find(k,j))
	{
		cout<<"Ҫ���ҵ�λ��j="<<j;
	}
	else
	{
		cout<<"�����λ�ò��Ϸ����޷������û���Ҫ�Ĳ���";
	}
	cout<<endl;
    return 0;
}
