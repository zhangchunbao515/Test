
//计算器类的实现，其中用到了链式栈存储操作数，用到顺序栈存储中缀表达式的符号。时间2012.11.15

#include <iostream>
using namespace std;
const int stackIncreament = 20;//全局变量，用于顺序栈溢出时的处理
int icp(char ch);//非主函数的函数声明
int isp(char ch);//非主函数的函数声明
bool isdigit(char ch);//非主函数的函数声明

//顺序栈的物理实现
template <class T>
class Stack
{
	public:
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
		bool makeEmpty()
		{
			delete []elements;
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


//链式栈的物理实现
template <class T>
class Stacknode //链式栈的结点类
{
	public:
		T data;//数据域
		Stacknode<T> *prev;//前驱指针域
		//构造函数，因为不含头结点，所以只用以个构造函数
		Stacknode (T const info,Stacknode<T> *newprev = NULL)
		{
			data = info;
			prev = newprev;
		}
		Stacknode(Stacknode<T> *newprev=NULL)//此构造函数主要用于创建带有头结点的单链表的头结点
		{
	
			prev = newprev;
		}

};


template <class T>
class LinkStack : public Stacknode<T>
{
	private:
		Stacknode<T> *top;//头指针
	public:
		LinkStack()
		{
			top = NULL;//构造函数，标准化的初始数据成员的方法
		}

		~LinkStack()//析构函数，调用置空函数得到
		{
			makeEmpty();
		}

		bool makeEmpty()//置空函数
		{
			Stacknode<T> *current = top;//动态申请一个新的指针，将原来栈的头指针赋值给新的指针
			Stacknode<T> *temp;//创建一个临时的动态指针
			while(current!=NULL)//循环结束的条件
			{
				temp = current;
				current = current->prev;
				delete temp;
			}
			return true;
		}

		bool Push(T value);
		bool Pop(T &value);
		bool getTop(T &value);
		bool isEmpty()
		{
			if (top == NULL)//判断链式栈是否为空的条件 
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};


//进栈分两种情况
template <class T>
bool LinkStack<T> :: Push(T value)
{
	if (top == NULL)
	{
		Stacknode<T> *p;
		p = new Stacknode<T>(value);//动态申请一个节点，并且将用户需要的数值赋值给新结点的数据域
		top = p;//栈顶指针指向新申请的结点
		return true;
	}

	else
	{
		Stacknode<T> *p;
		p = new Stacknode<T>(value);//动态申请一个节点，并且将用户需要的数值赋值给新结点的数据域
		p->prev = top;//新申请的结点的前驱指针域指向当前top指针
		top = p;//并将top指针指向新申请的结点，从而实现每个新节点接到链上，并且保证top始终指向当前的结点
		return true;
	}
}


//出栈
template <class T>
bool LinkStack<T> :: Pop(T &value)
{
	if (top == NULL)//如果栈为空，返回错误
	{
		return false;
	}

	else
	{
		Stacknode<T> *current = top;
		value = current->data;
		top = current->prev;
		delete current;
		return true;
	}
}


template <class T> 
bool LinkStack<T> :: getTop(T &value)
{
	if (top == NULL)
	{
		return false;
	}
	else
	{
		value = top->data;
		return true;
	}
}


template <class T>
class Calculator
{
	public:
		
		void infixTopostfix();//中缀转后缀，并且在转的过程中实现计算，分别调用下列两个函数实现
		bool getOperands(T &operands1,T &operands2);//获取操作数的函数
		void Compute(char op);//计算

	public:
		//构造函数，用于初始化数据成员
		Calculator(){};//构造函数

		LinkStack<T> s1;//链式栈，用于保存用于计算的操作数
		
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


void main ()
{
	Calculator<double> CALC;//创建计算器类的对象
	CALC.infixTopostfix();//计算器类的对象调用函数实现计算
}

bool isdigit(char ch)//判断是不是操作数的函数
{
	if (ch>=48&&ch<=57)
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
	case'+':
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
	case'*':
    case'/': return 5;break;
	case'(':return 1;break;
	default:return -1;break;
	}
}






