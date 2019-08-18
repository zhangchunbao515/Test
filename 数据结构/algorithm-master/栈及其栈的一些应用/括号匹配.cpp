#include <iostream>
#include "ARRSTACK.H"
using namespace std;

int main()//主函数分段测试类成员函数的正确性
{//输入一个字符串，检查其中的括号是否匹配,如果遇到左括号，将其入栈；如果遇见右括号判断其栈顶内容是否为左括号，如果是将其出栈
	int size=0;
	cout<<"请输入栈空间的预计最大值:";
	cin>>size;
	Stack< int > st(size);//创建栈，用于存放表达式数组的下标



	int i = 0;//循环控制变量
	const int maxsize = 50;
	char a;//临时变量，用于给字符串赋值
	char expression[maxsize];//建立字符数组
	char endTag = '#';
	for ( i=0;i<maxsize-1 ;i++ )
	{
		cout<<"请输入字符数组的一个元素值，按enter键继续：";
		cin>>a;
		if ( a == endTag ) break;
		expression[i] = a;
	}
	int length ;
	length = strlen(expression);
	int j;
	for (i = 0;i<length;i++)
	{
		if (expression[i] == '(')
			st.Push( i );
		if (expression[i] == ')')
			if( st.Pop(j) )
			{
				cout<<"第"<<j<<"个位置的左括号与第"<<i<<"个位置的右括号匹配";
			}
			else
			{
				cout<<"没有与第"<<i<<"个右括号匹配的左括号";
			}

	}
	while ( st.isEmpty() == false )
	{
		st.Pop(i);
		cout<<"没有与第"<<i<<"个左括号匹配的右括号";
	}

	return 0;
}
