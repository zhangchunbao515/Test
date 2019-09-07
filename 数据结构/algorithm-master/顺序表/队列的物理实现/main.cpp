#include <iostream>
#include "Queue.H"
using namespace std;
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

//运行结果为：
/*======================================================================================
                     请输入创建队列的预计最大空间：100
					 循环队列为空
					 请输入入队元素的数据值：1
					 栈顶元素为：x=1
					 Press any key to continue

=======================================================================================*/
