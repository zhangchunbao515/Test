
#include <iostream>
using namespace std;
template <class T>//����������Ľ��ģ����
class Linknode
{
	public:
		T data;
		Linknode<T> *next;
		Linknode(T const info,Linknode<T> *newnext=NULL)//�˹��캯����Ҫ����������ͷ���������������
		{
			data=info;
			next=newnext;
		}
		Linknode(Linknode<T> *newnext=NULL)//�˹��캯����Ҫ���ڴ�������ͷ���ĵ������ͷ���
		{
			next=newnext;
		}
};
template <class T>//������������
class InkLink:public Linknode<T>//������̳�����Ľ���࣬�����ǹ��м̳�
{
	private:
		Linknode<T> *head,*tail;//˽�е�ͷβָ��
	public:
		InkLink()
		{
			head=tail=NULL;
		}//���캯������׼���ĸ����ݳ�Ա��ʼ���ķ���
		void create(T endTag);//����һ����������ʽ����Ϊѭ�������ı�־���˱�־λ���û��Զ���
		bool output();//����������ÿһ����������ֵ
		bool makeEmpty();//�ÿյ������ͷſռ�
		~InkLink()
		{
			Linknode<T> *temp;//����һ����ʱ�����������ͷſռ�
			while(head!=NULL)//����Ϊ������Ϊ�յ�����
			{
				temp=head;
				head=head->next;//�Ƚ���һ������ֵ��ֵ��ͷָ��
				delete temp;//�ͷŽ��ռ�
			}
		}//���������������ͷŽ��ռ�
		Linknode<T> *setPos(int i);//�����û���������λ�ò���ֵ�������ظý���ָ��
		bool insert(int i);//�����û�����Ҫ�����µĽ��
		int length();//������ĳ���
		bool getpos( int &p,const T	value);//�����û�����Ҫ����Ҫ���ҵ�����ֵ���Ӷ�ʵ���ڵ������в����Ƿ���ڸ����ݣ�������ڷ�������Ե�ַ
};
template <class T>
void InkLink<T> :: create(T endTag)
{
	T a;
	Linknode<T> *p1,*p2;//����������ʱ����
	cout<<"������a��ֵ����ֵ���־��������ֵ��ͬʱֹͣ����:";
	for(;;)
	{
		cin>>a;
		if (a==endTag) break;//ѭ�������ı�־
		p1=new Linknode<T>(a);//��̬����ռ丳ֵ��p1
		if(head==NULL)
		{
			head=p1;
			p2=p1;//����һ�������p2����
		}//���ͷָ��Ϊ��ʱ�Ƚ���̬����Ľ�����ͷָ������
		else
		{
			p2->next=p1;
			p2=p1;
		}
		tail=p2;
		tail->next=head;
	}
};
/*�˺�����ʱ�临�Ӷ�ΪO��n����ѭ�������ɱ�־λ����*/
template <class T>
bool InkLink<T> :: output()
{
	Linknode<T> *current = head;//��������ʹ��ͷָ��ֱ����������Խ��丳ֵ��һ����ʱ�ľֲ�����
	while(current != NULL)
	{
		cout<<current->data<<"->";
		current = current->next;
	}
	return true;
};
/*�˺�����ʱ�临�Ӷ�ΪO��n��,ѭ�������ɱ�־λ����*/
template <class T>
Linknode<T> *InkLink<T> :: setPos(int i)
{
	if (i<0)
	{
		cout<<"The location is illgal"<<endl;
		return NULL;
	}//��׳�Ե��ж�
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
/*�ú��������µ�ʱ�临�Ӷ�ΪO��n����������ѭ�������ɱ�־λ����*/
template <class T>
bool InkLink<T> :: insert(int i) //ʵ����ָ��λ��֮��Ĳ��룬��Ϊ�涨�����һ���������λ��Ϊ0
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
		cout<<"������Ҫ�����������ֵa:";
		cin>>a;
		Linknode<T> *newnode=new Linknode<T>(a);
		newnode->next=current->next;
		current->next=newnode;
		return true;
	}
	if (head==NULL)
	{
		T a;
		cout<<"������Ҫ�����������ֵ��";
		cin>>a;
		Linknode<T> *current=new Linknode<T> (a);
		head=tail=current;
		return true;
	}
};
/*�ú��������µ�ʱ�临�Ӷ�ΪO��n����������ѭ�������ɱ�־λ����,�ڵ���setPos��int i��ʱ�漰��ѭ��*/
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
/*�˺�����ʱ�临�Ӷ�ΪO��n��,ѭ�������ɱ�־λ����*/
//ʵ�ֵ�������ÿգ�2012.10.13��
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
/*�˺�����ʱ�临�Ӷ�ΪO��n��,ѭ�������ɱ�־λ����*/
//�˺���ʵ�ָ����û�����Ҫ����Ҫ���ҵ�ֵ��Ȼ���������в���ֵ��λ�ã������ظý������λ�ã�2012.10.14�����˺����Ľ�׳�Բ��ã���Ľ�
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
/*�˺�����ʱ�临�Ӷ�ΪO��n��,ѭ�������ɱ�־λ����*/
int main()
{
	int n=0;int value;
	InkLink <int> list;
	int m;
	cout<<"�������־λ��ֻ��ʵ�ּ����ϵ��ַ������룬��ʾ�ַ��Ľ�����־Ϊ\0:";
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
	cout<<"������Ҫ��ѯ����ֵ��";
	cin>>value;
	list.getpos(n,value);
	cout<<"Ҫ��ѯ��ֵ��λ��Ϊ��"<<n;
	list.makeEmpty();
	cout<<endl;
	cout<<"The long of list is:"<<list.length()<<endl;
    return 0;
}
