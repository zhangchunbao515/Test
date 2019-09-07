//˳��ջ,����ջ��ָ��ָ��ǰԪ��
#include <iostream>
#include <cstdlib>
using namespace std;
template <class T>
class arrStack
{
	public:
		int top;
		int msize;
		T *st;
		arrStack(int size)
		{
			msize = size;
			top = -1;
			st =new T[msize];
			if ( st == NULL)
			{
				cerr<<"����ռ����"<<endl;
				exit(1);
			}
		}
		~arrStack()
		{
			delete []st;
		}
		bool push(const T value);
		bool pop(T &value);
};
template <class T>
bool arrStack<T> :: push(const T value)
{
	if ( top == msize-1 )
	{
		cout<<"The stack is overflow";
		return false;
	}
	else
	{
		top++;
		st[top] = value;
		return true;
	}
}
template <class T>
bool arrStack<T> :: pop(T&value)
{
	if ( top == -1 )
	{
		{
			cout<<"The stack is empty";
			return false;
		}

	}
	else
	{
		value = st[top];
		top--;
		return true;
	}
}
int main()
{
	int n;
	cout<<"��������Ҫ����ջ����󳤶ȣ�";
	cin>>n;
	arrStack<int> stack(n);


	int value;
	cout<<"��������Ҫ��ջԪ�ص�ֵ";
	cin>>value;
	stack.push(value);
	cout<<endl;

	int item=0;
	if ( stack.pop(item) )
	{
		cout<<"��ջԪ�ص�ֵΪ��"<<item;
	}
	else
	{
		cout<<"ջΪ��û�г�ջ��Ԫ��";
	}
	return 0;
}



