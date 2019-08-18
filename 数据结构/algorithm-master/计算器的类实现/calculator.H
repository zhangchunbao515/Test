#ifndef _calculator_H_
#define _calculator_H_
#include <iostream>
using namespace std;


template <class T>
class Calculator
{
	public:
		
		void infixTopostfix();//中缀转后缀，并且在转的过程中实现计算，分别调用下列两个函数实现
		bool getOperands(T &operands1,T &operands2);//获取操作数的函数
		void Compute(char op);//计算

	public:
		Stack<T> s1;

		//构造函数，用于初始化数据成员
		Calculator(int size):s1(size)//此句语法非常关键，是利用顺序栈的一个必要方法；类中套类的构造函数的实现
		{};//构造函数
		
		~Calculator()//析构函数
		{}
		void clear();
};

template <class T>
void Calculator<T> :: infixTopostfix()
{
	int size;
	cout<<"请输入字符栈的预计最大长度：";
	cin>>size;
	Stack<char>s(size);
	
	//用于中缀转后缀存放操作符
	char ch='#',ch1,op;
	s.Push(ch);//将#号入栈，用于做为循环结束的标志
	
	cin>>ch;//输入表达式的一个字符
	while( !s.isEmpty() &&ch!='#' )//循环结束的条件
	{
		if (isdigit(ch))//判断是否为操作数，如果是操作数，直接输出，然后输入下一个表达式的字符
		{
			T newoperands;
			cin.putback(ch);//退回刚读到的字符
			cin>>newoperands;//重新读入，而不是重新输入
			s1.Push(newoperands);//将操作数进栈
			//T x;
			//s1.getTop(x);
			//cout<<"栈顶元素的值为："<<x<<endl;//检查性语句，程序做成后删除
			cin>>ch;
		}

		else
		{
			s.getTop(ch1);//如果不是操作数，将栈顶元素取出，与即将输入的字符比较优先级
			if(icp(ch)>isp(ch1))//如果即将输入的字符的优先级比栈顶元素的优先级大，则直接将输入的元素进栈，然后输入下一个字符
			{
				s.Push(ch);
				cin>>ch;
			}

			else
			{
				if (isp(ch1)>icp(ch))//如果即将输入的字符的优先级比栈顶元素的优先级，则将栈顶元素重复弹出，直至当前输入的元素可以进栈或者遇到相同的优先级从而抵消
				{
					s.Pop(op);
					Compute(op);


				}
				else
				{
					s.Pop(op);
					if (op == '(')
					{
						cin>>ch;
					}
				}
			}
		}
	}
	while(!s.isEmpty())//此时可能栈中除#号外还有其他的操作符，需要将其全部弹出，摊入到后缀表达式中
	{
		s.Pop(op);
		if (op=='#') break;//如果栈中的元素是#，则不输入到后缀表达式中，因为#仅仅是一个结束的标志
		Compute(op);

	}
	cout<<endl;
	T res;//存放结果的变量
	if (s1.Pop(res))//出栈获得最终的结果
		cout<<"表达式的计算结果为："<<res<<endl;

}


template <class T>
bool Calculator<T> :: getOperands(T &operands1,T &operands2)
{
	if (s1.isEmpty())
	{
		cout<<"缺少右操作数";
		return false;
	}
	else
	{
		s1.Pop(operands2);//出栈得到又操作数
		//cout<<"右操作数为："<<operands2;
		//return true;//此句不能有，否则得到有操作数立即结束程序的执行，得不到左操作数，从而使程序终止
	}
	if(s1.isEmpty())
	{
		cout<<"缺少左操作数";
		return false;
	}
	else
	{
		s1.Pop(operands1);//出栈得到做操作数
		//cout<<"左操作数为："<<operands1;
		return true;
	}
	cout<<endl;
}


template <class T>
void Calculator<T> :: Compute(char op)
{
	bool result;
	T ope1,ope2;
	result = getOperands (ope1,ope2);
	if (result == true)
	{
		switch(op)
		{
		case'+':
			s1.Push(ope1 + ope2);
			break;
		case'-':
			s1.Push(ope1 - ope2);
			break;
	    case'*':
			s1.Push(ope1 * ope2);
			break;
	    case'/':
			s1.Push(ope1 / ope2);
			break;
		}
	}
	else
	{
		s1.makeEmpty();//如果没有两个操作数，则清栈退出
	}
}

template <class T>
void Calculator<T> ::clear()
{
	s1.makeEmpty();
}

#endif
