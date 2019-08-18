//顺序栈,并且栈顶指针指向当前元素
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
				cerr<<"分配空间错误"<<endl;
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
	cout<<"请输入需要创建栈的最大长度：";
	cin>>n;
	arrStack<int> stack(n);


	int value;
	cout<<"请输入需要入栈元素的值";
	cin>>value;
	stack.push(value);
	cout<<endl;

	int item=0;
	if ( stack.pop(item) )
	{
		cout<<"出栈元素的值为："<<item;
	}
	else
	{
		cout<<"栈为空没有出栈的元素";
	}
	return 0;
}



