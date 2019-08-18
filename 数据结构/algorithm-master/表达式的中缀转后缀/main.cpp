//顺序栈的物理实现方法，其中包含一个溢出处理函数，此函数为类的私有成员,在主函数中完成中缀转后缀的操作
#include <iostream>
#include <string>
#include "stack.H"
#include "icp.H"
#include "isp.H"
#include "isdigit.H"
using namespace std;
void postfix(char expression[]);
int icp(char ch);
int isp(char ch);
bool isdigit(char ch);
void main()
{
	int size ;
	cout<<"请输入需要创建栈的预计最大长度:";
	cin>>size;
	Stack<char> s(size);
	
	char ch='#',ch1,op;
	s.Push(ch);//将#号入栈，用于做为循环结束的标志

	//创建后缀表达式的存储数组
	const int maxsize = 50;
	char postfix[maxsize];//用于存放后缀表达式，数组的最大长度必须要固定
	
	cin.get(ch);//输入表达式的一个字符
	int i=0;//后缀表达式的循环变量，必须要初始化，否则不能正确执行
	while( !s.isEmpty() &&ch!='#' )//循环结束的条件
	{
		if (isdigit(ch))//判断是否为操作数，如果是操作数，直接输出，然后输入下一个表达式的字符
		{
			cout<<ch;
			postfix[i++] = ch;
			cin.get(ch);

		}

		else
		{
			s.getTop(ch1);//如果不是操作数，将栈顶元素取出，与即将输入的字符比较优先级
			if(icp(ch)>isp(ch1))//如果即将输入的字符的优先级比栈顶元素的优先级大，则直接将输入的元素进栈，然后输入下一个字符
			{
				s.Push(ch);
				cin.get(ch);
			}

			else
			{
				if (isp(ch1)>icp(ch))//如果即将输入的字符的优先级比栈顶元素的优先级，则将栈顶元素重复弹出，直至当前输入的元素可以进栈或者遇到相同的优先级从而抵消
				{
					s.Pop(op);
					cout<<op;
					postfix[i++] = op;
				}
				else
				{
					s.Pop(op);
					if (op == '(')
					{
						cin.get(ch);
					}
				}
			}
		}
	}
	while(!s.isEmpty())//此时可能栈中除#号外还有其他的操作符，需要将其全部弹出，摊入到后缀表达式中
	{
		s.Pop(op);
		if (op=='#') break;//如果栈中的元素是#，则不输入到后缀表达式中，因为#仅仅是一个结束的标志
		cout<<op;
		postfix[i++] = op;
	}
	for(int j=0;j<i;j++)
	{
		cout<<postfix[j];//将后缀表达式输出
	}
}


/*============================================================================================
                          请输入需要栈的预计最大长度：100
                          5+3*(4+6)-9/3#
                          5346+*+93/-
                          5346+*+93/-
                          Press any key to continue

                                                              
=============================================================================================*/
