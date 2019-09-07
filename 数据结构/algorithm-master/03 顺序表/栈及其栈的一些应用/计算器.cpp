#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Stack                                    //ջ�ĳ����������Ͷ���
{
public:
	void clear();                               //���ջ
	bool push(const T item);                    //��ջ
	bool pop(T & item);                         //��ջ
	bool top(T & item);                         //��ȡջ��Ԫ��
	bool isEmpty();                             //�ж�ջ�Ƿ�Ϊ��
	bool isFull();                              //�ж�ջ�Ƿ�Ϊ�����
};
template <class T>
class arrStack:public Stack<T>                 //˳��ջ
{
private:
	int maxSize;                               //ջ�����ɴ�ŵ�Ԫ�ظ���
	int top;                                   //ջ��ָ�룬һ�����ͱ��������Լ����ջ�ĵ�ǰԪ�ظ���
	T *st;                                     //ָ��ջ�����Ĵ洢�ռ��һ��ָ��
public:
	arrStack(int size);                        //˳��ջ���вι��캯��
	arrStack();                                //˳��ջ���޲ι��캯��
	~arrStack();                               //˳��ջ����������
	void clear();                              //���˳��ջ
	bool push(const T item);                   //˳��ջ����ջ
	bool pop(T  & item);                       //˳��ջ�ĳ�ջ
	bool gettop(T & item);                     //��ȡ˳��ջ��ջ��Ԫ��
	bool isEmpty();                            //�ж�˳��ջ�Ƿ�Ϊ��
	bool isFull();                             //�ж�˳��ջ�Ƿ�Ϊ��
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
	st=new T[maxSize];                         //����ռ�
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
	if(top==maxSize-1)                        // �ж�ջ�ܷ���ջ
	{                                        // ջ��Ԫ������±�Ϊ maxSize-1
		cout<<"ջ�����޷���ջ"<<endl;
		return false;
	}
	top++;
	st[top]=item;
	return true;
}
template <class T>bool arrStack<T>::pop(T & item)      //�ж��ܷ��ջ
{
	if(top==-1)
	{
		cout<<"ջΪ�գ��޷�ִ�г�ջ����"<<endl;
		return false;
	}
	item=st[top--];
	return true;
}
template <class T>bool arrStack<T>::gettop(T & item)
{
	if(top==-1)
	{
		cout<<"ջΪ�գ��޷���ȡջ��Ԫ��"<<endl;
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

class InfixtoPostfix                 //��׺ת��׺����
{
	private:
		char string1[50];               //�洢��׺���ʽ
		arrStack <char>  ops;           //���������һ��ջ
		bool Precede(char opr1,char opr2);        //�Ƚ���������������ȼ�
        char  string2[50];                       //�洢��׺���ʽ
	public:
		InfixtoPostfix(char  st[50],int size):ops(size)            //���캯������ʼ����׺���ʽ
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
		void Conversion();                       //��׺ת��׺�ĺ���
		char visit(int i);                       //���ʺ�׺���ʽ
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
class Calculator                //��׺���ʽ��ֵ
{
	private:
		InfixtoPostfix cal;                    //�����Ա
		arrStack<ELEM> s;                      //�Ų�������һ��ջ
		bool GetTwoOperands(ELEM & opnd1,ELEM & opnd2);           //��ջ�еõ�����������
		void Compute(char op);                                    //����
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
