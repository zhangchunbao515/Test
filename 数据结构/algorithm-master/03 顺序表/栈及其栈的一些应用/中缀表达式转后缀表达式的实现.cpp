//顺序栈的物理实现方法，其中包含一个溢出处理函数，此函数为类的私有成员,在主函数中完成中缀转后缀的操作
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
void postfix(char expression[]);
int icp(char ch);
int isp(char ch);
bool isdigit(char ch);
const int stackIncreament = 20;//全局变量，用于溢出处理时动态的增加需要的存储单元数
template <class T>
class Stack
{
	private:
		T *elements;
		int maxSize;
		int top;//栈顶指针
		void overflowprocess();//溢出处理函数
	public:
		Stack ( int size )
		{
			maxSize = size;
			elements = new T[maxSize];
			//此函数不能使用，系统提示不提供，assert( elements != NULL );//使用了断言语句，当参数表达式成立时，程序继续执行；否则进入中断处理程序，程序终止其代替语句如下
			if ( elements == NULL)
			{
				cout<<"分配存储空间错误\n"<<endl;
				exit(1);
			}//判断动态申请空间是否成功，标注化的语句
			top = -1;
		}
		~Stack()
		{
			delete []elements;//析构数组类的指针对象时用的标注化方法
		}
		bool Push( const T &x );//压入栈顶
		bool Pop( T &x );//出栈
		bool getTop(T &x);//获得栈顶元素的值
		bool isEmpty()
		{
			if ( top == -1)
			{
				cout<<"栈为空"<<endl;
				return true;
			}
			else
				return false;
		}
};

//此函数为溢出处理函数，当分配的空间不足时，动态重新为其分配存储空间
template <class T>
void Stack<T> :: overflowprocess()
{
	T *arrStack = new T[maxSize + stackIncreament];//动态重新申请一个更大的存储空间，用于溢出处理
	if (arrStack == NULL)
	{
		cout<<"分配存储空间错误\n"<<endl;
		exit(1);
	}//标准化的判断动态申请的空间是否成功的申请
	int i=0;
	for ( i = 0;i <=top;i++ )
	{
		arrStack[i] = elements[i];//将原来数组的每一个元素分别赋值给新创建的数组
	}
	delete []elements;//析构旧数组
	elements = arrStack;//将新创建的更大的数组命名为前数组的名字，便于操作
}


template <class T>
bool Stack<T> :: Push( const T &x )//压栈函数，带一个引用型参数
{
	if (top == maxSize - 1) //判断栈是否为满，如果满，则调用溢出处理函数重新分配空间
	{
		cout<<"分配空间不足，调用类函数重新为其分配空间";
		cout<<endl;
		overflowprocess();
	}
	top++;
	elements[top] = x;//现将栈顶指针上移，然后将用户需要的数值压入栈顶
	return true;//返回语句，无条件的转移语句，执行return之后，后面的语句将不再执行，因为已回到程序断点
}


template <class T>
bool Stack<T> :: Pop( T &x )//出栈函数
{
	if ( top == -1)//判断栈是否为空，如果为空直接返回；否则执行下面的语句
	{
		//cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		top--;
		return true;
	}
}


template <class T>
bool Stack<T> :: getTop( T &x )//获得栈顶指针的值，用引用型参数向外传递栈顶元素的值
{
	if ( top == -1 )//判断栈是否为空
	{
		//cout<<"栈为空"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		return true;
	}
}


int main()
{
	int size ;
	cout<<"请输入需要创建栈的预计最大长度";
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

	return 0;
}


bool isdigit(char ch)//判断是不是操作数的函数
{
	if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '#' && ch != '('&& ch !=')' )
		return true;
	else
		return false;
}



int icp(char ch)//栈外优先级的比较函数
{
	switch(ch)
	{
	case'#': return 0;break;
	case')': return 1;break;
	case'+':return 2;break;
    case'-':return 2;break;
	case'*':
	case'/': return 4;break;
	case'(':return 6;break;
	default:return -1;break;
	}
}




int isp(char ch)//栈内优先级的比较函数
{
	switch(ch)
	{
	case'#': return 0;break;
	case')': return 6;break;
	case'+':
	case'-':return 3;break;
	case'*': return 5;break;
    case'/': return 5;break;
	case'(':return 1;break;
	default:return -1;break;
	}
}


