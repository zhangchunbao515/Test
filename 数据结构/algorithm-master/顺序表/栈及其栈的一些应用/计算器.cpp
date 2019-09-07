#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Stack                                    //栈的抽象数据类型定义
{
public:
	void clear();                               //清空栈
	bool push(const T item);                    //入栈
	bool pop(T & item);                         //出栈
	bool top(T & item);                         //获取栈顶元素
	bool isEmpty();                             //判断栈是否为空
	bool isFull();                              //判断栈是否为满溢出
};
template <class T>
class arrStack:public Stack<T>                 //顺序栈
{
private:
	int maxSize;                               //栈中最多可存放的元素个数
	int top;                                   //栈顶指针，一个整型变量，可以计算出栈的当前元素个数
	T *st;                                     //指向栈连续的存储空间的一个指针
public:
	arrStack(int size);                        //顺序栈的有参构造函数
	arrStack();                                //顺序栈的无参构造函数
	~arrStack();                               //顺序栈的析构函数
	void clear();                              //清空顺序栈
	bool push(const T item);                   //顺序栈的入栈
	bool pop(T  & item);                       //顺序栈的出栈
	bool gettop(T & item);                     //获取顺序栈的栈顶元素
	bool isEmpty();                            //判断顺序栈是否为空
	bool isFull();                             //判断顺序栈是否为满
	void print()
	{
		for(int i=0;i<=top;i++)
			cout << st[i] << "   ";
		cout <<endl;
	}
};
template <class T>arrStack<T>::arrStack(int size=30)
{
	maxSize=size;
	top=-1;
	st=new T[maxSize];                         //申请空间
}
template <class T>arrStack<T>::arrStack()
{
	top=-1;
	maxSize=0;
	st=NULL;
}
template <class T>arrStack<T>::~arrStack()
{
	delete [] st;
}
template <class T>void arrStack<T>::clear()
{
	top=-1;
}
template <class T>bool arrStack<T>::push(const T item)
{
	if(top==maxSize-1)                        // 判断栈能否入栈
	{                                        // 栈顶元素最大下标为 maxSize-1
		cout<<"栈满，无法入栈"<<endl;
		return false;
	}
	top++;
	st[top]=item;
	return true;
}
template <class T>bool arrStack<T>::pop(T & item)      //判断能否出栈
{
	if(top==-1)
	{
		cout<<"栈为空，无法执行出栈操作"<<endl;
		return false;
	}
	item=st[top--];
	return true;
}
template <class T>bool arrStack<T>::gettop(T & item)
{
	if(top==-1)
	{
		cout<<"栈为空，无法获取栈顶元素"<<endl;
		return false;
	}
	item=st[top];
	return true;
}
template <class T>bool arrStack<T>::isEmpty()
{
	if(top==-1)
		return true;
	else
		return false;
}
template <class T>bool arrStack<T>::isFull()
{
	if(top==maxSize-1)
		return true;
	else
		return false;
}

class InfixtoPostfix                 //中缀转后缀的类
{
	private:
		char string1[50];               //存储中缀表达式
		arrStack <char>  ops;           //存运算符的一个栈
		bool Precede(char opr1,char opr2);        //比较两个运算符的优先级
        char  string2[50];                       //存储后缀表达式
	public:
		InfixtoPostfix(char  st[50],int size):ops(size)            //构造函数，初始化中缀表达式
		{
			strcpy(string1,st);
		}
    	~InfixtoPostfix()
		{
			clear();
		}
		void clear()
		{
			ops.clear();
		}
		void Conversion();                       //中缀转后缀的函数
		char visit(int i);                       //访问后缀表达式
};

bool InfixtoPostfix::Precede(char opr1,char opr2)
{
	switch(opr1)
	{
		case'*':
		case'/':
			return true;
		case'+':
		case'-':
			switch(opr2)
			{
				case'*':
				case'/':
					return false;
				case'+':
				case'-':
					return true;
			}
	}
}

void InfixtoPostfix::Conversion()
{
	int i=0,j=0;
	char op;
	char c;
	while(c=string1[i++],c!='=')
	{
		switch(c)
		{
		case'(':
			ops.push(c);
			break;
		case')':
			if(ops.isEmpty())
			{
				cout<<"MIssing parenthsis"<<endl;
				return;
			}

			ops.gettop(op);
			while(!ops.isEmpty()&&op!='(')
			{
				string2[j++]=' ';
				string2[j++]=op;
				ops.pop(op);
				ops.gettop(op);

			}
			if(op!='(')
			{
				cout<<"Missing parenthsis"<<endl;
			    return ;
			}
			else
				ops.pop(op);
			break;

		case'*':case'/':case'+':case'-':
			ops.gettop(op);
			while( !ops.isEmpty() && op!='(' && Precede(op,c) )
			{
				string2[j++]=' ';
				string2[j++]=op;
				ops.pop(op);
				ops.gettop(op);
			}
			//if (op=='(') ops.pop(op);
			string2[j++]=' ';
			ops.push(c);
			break;
		case'.':
			string2[j++]='.';
		default:
			string2[j++]=c;
			break;
		}

		ops.print();
	}

	while(!ops.isEmpty())
	{
		if(ops.gettop(op)&&op=='(')
		{
			cout<<"Missing parenthsis"<<endl;
			return;
		}
		string2[j++]=' ';
		string2[j++]=op;
		ops.pop(op);
	}

	string2[j++]='=';
	string2[j]='\0';
	//cout << "********************" <<endl;
	//cout << string1 <<endl <<string2;
	cout<<endl;
}

char InfixtoPostfix::visit(int i)
{
	return  string2[i];
}

template<class ELEM>
class Calculator                //后缀表达式求值
{
	private:
		InfixtoPostfix cal;                    //对象成员
		arrStack<ELEM> s;                      //放操作数的一个栈
		bool GetTwoOperands(ELEM & opnd1,ELEM & opnd2);           //从栈中得到两个操作数
		void Compute(char op);                                    //计算
	public:
		Calculator(char st[50],int size,int asize):cal(st,size),s(asize){};
		~Calculator()
		{
			clear();
		}
		void clear()
		{
			s.clear();
		}
		void Run();
};
template<class ELEM>
bool Calculator<ELEM>::GetTwoOperands(ELEM & opnd1,ELEM & opnd2)
{
	if(s.isEmpty())
	{
		cout<<"Missing operand"<<endl;
		return false;
	}
	s.pop( opnd1);
	if(s.isEmpty())
	{
		cout<<"Missing operand"<<endl;
		return false;
	}
	s.pop( opnd2);
	return true;
}
template<class ELEM>
void Calculator<ELEM>::Compute(char op)
{
	bool result;
	ELEM operand1,operand2;
	if(result=GetTwoOperands(operand1,operand2)==true)
		switch(op)
	{
		case'+':
			s.push(operand2+operand1);
			break;
		case'-':
			s.push(operand2-operand1);
			break;
		case'*':
			s.push(operand2*operand1);
			break;
		case'/':
			if(operand1==0.0)
			{
				cout<<"Divide bu 0!"<<endl;
				s.clear();
			}
			else
				s.push(operand2/operand1);
			break;
	}
	else
		s.clear();
}
template<class ELEM>
void Calculator<ELEM>::Run()
{
	cal.Conversion();
	int i=0;
	double item=0.1;
	char c,a;
	ELEM newoperand=0,res;
	while(c=cal.visit(i++),c!='=')
	{
		switch(c)
		{
		case' ':
			break;
		case'+':case'-':case'*':case'/':
			Compute(c);
			break;
		default:
			if(c<'9'&&c>'0')
			{
			  newoperand=c-48;
			  while( a=cal.visit(i), a<'9'&&a>'0')
			  {
			   	newoperand=newoperand*10+a-48;
				i++;
			  }
			  if(cal.visit(i)=='.')
				  while(a=cal.visit(i++),a<'9'&&a>'0')
				  {
					  newoperand+=(a-48)*item;
				      item*=item;
				  }
			  s.push(newoperand);
		      break;
			}
			else
				return;
		}
		s.print();

	}
	if( !s.isEmpty() && s.pop(res) && s.isEmpty() )
		cout<<res<<endl;
	else
		cout<<"Expression Error"<<endl;
}

int main ()
{
	char st[50]="23+(34*45)/(5+6+7)=";
	Calculator<double>  str(st,30,30);
	str.Run();
}
