//顺序循环队列的具体物理实现，基与数组的实现方式
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
				cout<<"分配存储空间错误\n"<<endl;
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
		cout<<"循环队列为空"<<endl;
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
		cout<<"队列满"<<endl;
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
		cout<<"队列为空"<<endl;
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
		cout<<"队列为空"<<endl;
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
	cout<<"请输入创建队列的预计最大空间:";
	cin>>size;
	Queue<int> a(size);


	a.isEmpty();
	cout<<endl;

	a.isFull();
	cout<<endl;

	int value;
	cout<<"请输入入队元素的数据值：";
	cin>>value;
	a.inQueue(value);
	cout<<endl;
	int x;
	a.outQueue(x);
	cout<<"x的值为："<<x;
}
