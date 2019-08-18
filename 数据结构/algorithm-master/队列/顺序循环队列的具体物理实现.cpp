//˳��ѭ�����еľ�������ʵ�֣����������ʵ�ַ�ʽ
#include <iostream>
using namespace std;
template <class T>
class Queue
{
	public:
		int front;
		int rear;
		T *arrQueue;
		int maxSize;
		Queue(int sz)
		{
			front = rear = 0;
			maxSize = sz;
			arrQueue = new T[maxSize];
			if (arrQueue == NULL)
			{
				cout<<"����洢�ռ����\n"<<endl;
				exit(1);
			}
		}
		~Queue()
		{
			delete[] arrQueue;
		}
		bool inQueue(const T &value);
		bool outQueue(T &value);
		bool getQueuetop(T &value);
		bool isEmpty();
		bool isFull();
};


template <class T>
bool Queue<T> :: isEmpty()
{
	if (front == rear)
	{
		cout<<"ѭ������Ϊ��"<<endl;
		return true;
	}
	else 
	{
		return false;
	}
}


template <class T >
bool Queue<T> :: isFull()
{
	if (front == (rear+1)%maxSize)
		return true;
	else return false;
}


template <class T>
bool Queue<T> :: inQueue(const T&value)
{
	if (isFull())
	{
		cout<<"������"<<endl;
		return false;
	}
	else
	{
		arrQueue[rear] = value;
		rear = (rear+1)%maxSize;
		return true;
	}
}



template <class T>
bool Queue<T> :: outQueue(T &value)
{
	if (isEmpty())
	{
		cout<<"����Ϊ��"<<endl;
		return false;
	}
	else
	{
		value=arrQueue[front];
		front = (front+1)%maxSize;
		return true;
	}
}

template <class T>
bool Queue<T> :: getQueuetop(T&value)
{
	if (isEmpty())
	{
		cout<<"����Ϊ��"<<endl;
		return false;
	}
	else
	{
		value=arrQueue[front];
		return true;
	}
}


void main ()
{
	int size;
	cout<<"�����봴�����е�Ԥ�����ռ�:";
	cin>>size;
	Queue<int> a(size);


	a.isEmpty();
	cout<<endl;

	a.isFull();
	cout<<endl;

	int value;
	cout<<"���������Ԫ�ص�����ֵ��";
	cin>>value;
	a.inQueue(value);
	cout<<endl;
	int x;
	a.outQueue(x);
	cout<<"x��ֵΪ��"<<x;
}
