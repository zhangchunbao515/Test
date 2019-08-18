//����ͷ���ĵ�����


#include <iostream>
using namespace std;
//�����������ͷ�����
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
//������������
template <class T>
class InkLink:public Linknode<T>//�̳е������ͷ�����
{
	public:
		Linknode<T> *head,*tail;//����ͷָ��
		InkLink()
		{
			head = tail = new Linknode<T>(NULL);//����ͷ���
		}
		void create(T endTag);//endTagΪ��־����λ�����û��Զ���
		bool output();//�������
		void length();//������ĳ���
		Linknode<T> *setPos(int i);//ȷ��λ�ò����ش˽ڵ��ָ��ֵ
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
		}//�ÿյ�����
		bool insert(int i);//��λ�ò���
		~InkLink()
		{
			makeEmpty();
		}
};
template <class T>
void InkLink<T> :: create(T endTag)//endTagΪѭ�������ı�־�����û��Լ����壬����ֻ��ʵ����������ϵ��ַ��������ӵĲ���ʵ��
{
	T a;
	Linknode<T>  *p=NULL;
	for(;;)
	{
		cout<<"�������������ֵ��������endTagʱ��������������";
		cin>>a;
		if (a==endTag)  break;
		p=new Linknode<T>(a);//��̬������
		tail->next = p;
		tail = p;//����ͷ�������
	}
};
template <class T>
bool InkLink<T> :: output()
{
	Linknode<T> *p=head;
	if (p->next==NULL)//����ͷ���ĵ������Ƿ�Ϊ�յ��жϷ���
	{
		cout<<"The list is empty"<<endl;
		return false;
	}//��׳�Ե��ж�
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
	}//��׳�Ե��ж�
	T a;
	cout<<"������Ҫ����Ľ�������ֵ:";
	cin>>a;
	Linknode<T> *p=setPos(i);

	Linknode<T> *newnode=new Linknode<T>(a);//��̬����һ���µĽ����������
	newnode->next=p->next;/*�����������һ�䷴����ִ�оͻᷢ������*/
	p->next=newnode;
	//newnode->next=p->next;
	return true;
};
int main()
{
	InkLink<int> list;
	cout<<"�������־λ�����û��Զ���,�����ڼ�������������ַ�:";
	int m;//��־λ�����û��Զ���
	cin>>m;

	list.create(m);
	list.output();
	list.length();

	int i;
	cout<<"������Ҫ�������λ��:";
	cin>>i;
	list.setPos(i);
	list.insert(i);
	list.output();

	list.makeEmpty();
	list.output();
	return 0;
}
