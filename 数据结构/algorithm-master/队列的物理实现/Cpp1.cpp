#include <iostream>
#include "Queue.H"
using namespace std;



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