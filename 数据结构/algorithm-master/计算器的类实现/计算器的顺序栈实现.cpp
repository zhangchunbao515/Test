//���������ʵ�֣������õ�����ʽջ�洢���������õ�˳��ջ�洢��׺���ʽ�ķ��š�ʱ��2012.11.15

#include <iostream>
using namespace std;
const int stackIncreament = 20;//ȫ�ֱ���������˳��ջ���ʱ�Ĵ���
int icp(char ch);//���������ĺ�������
int isp(char ch);//���������ĺ�������
bool isdigit(char ch);//���������ĺ�������

//˳��ջ������ʵ��
template <class T>
class Stack
{
	public:
		T *elements;
		int maxSize;
		int top;//ջ��ָ��
		void overflowprocess();//���������
	public:
		Stack ( int size )
		{
			maxSize = size;
			elements = new T[maxSize];
			//�˺�������ʹ�ã�ϵͳ��ʾ���ṩ��assert( elements != NULL );//ʹ���˶�����䣬���������ʽ����ʱ���������ִ�У���������жϴ�����򣬳�����ֹ������������
			if ( elements == NULL)
			{
				cout<<"����洢�ռ����\n"<<endl;
				exit(1);
			}//�ж϶�̬����ռ��Ƿ�ɹ�����ע�������
			top = -1;
		}
		~Stack()
		{
			delete []elements;//�����������ָ�����ʱ�õı�ע������
		}
		bool Push( const T &x );//ѹ��ջ��
		bool Pop( T &x );//��ջ
		bool getTop(T &x);//���ջ��Ԫ�ص�ֵ
		bool isEmpty()
		{
			if ( top == -1)
			{
				cout<<"ջΪ��"<<endl;
				return true;
			}
			else 
				return false;
		}
		bool makeEmpty()
		{
			delete []elements;
			return true;
		}
};

//�˺���Ϊ�����������������Ŀռ䲻��ʱ����̬����Ϊ�����洢�ռ�
template <class T>
void Stack<T> :: overflowprocess()
{
	T *arrStack = new T[maxSize + stackIncreament];//��̬��������һ������Ĵ洢�ռ䣬�����������
	if (arrStack == NULL)
	{
		cout<<"����洢�ռ����\n"<<endl;
		exit(1);
	}//��׼�����ж϶�̬����Ŀռ��Ƿ�ɹ�������
	int i=0;
	for ( i = 0;i <=top;i++ )
	{
		arrStack[i] = elements[i];//��ԭ�������ÿһ��Ԫ�طֱ�ֵ���´���������
	}
	delete []elements;//����������
	elements = arrStack;//���´����ĸ������������Ϊǰ��������֣����ڲ���
}


template <class T>
bool Stack<T> :: Push( const T &x )//ѹջ��������һ�������Ͳ���
{
	if (top == maxSize - 1) //�ж�ջ�Ƿ�Ϊ����������������������������·���ռ�
	{
		cout<<"����ռ䲻�㣬�����ຯ������Ϊ�����ռ�";
		cout<<endl;
		overflowprocess();
	}
	top++;
	elements[top] = x;//�ֽ�ջ��ָ�����ƣ�Ȼ���û���Ҫ����ֵѹ��ջ��
	return true;//������䣬��������ת����䣬ִ��return֮�󣬺������佫����ִ�У���Ϊ�ѻص�����ϵ�
}



template <class T>
bool Stack<T> :: Pop( T &x )//��ջ����
{
	if ( top == -1)//�ж�ջ�Ƿ�Ϊ�գ����Ϊ��ֱ�ӷ��أ�����ִ����������
	{
		//cout<<"ջΪ��"<<endl;
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
bool Stack<T> :: getTop( T &x )//���ջ��ָ���ֵ���������Ͳ������⴫��ջ��Ԫ�ص�ֵ
{
	if ( top == -1 )//�ж�ջ�Ƿ�Ϊ��
	{
		//cout<<"ջΪ��"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		return true;
	}
}
template <class T>
class Calculator
{
	public:
		
		void infixTopostfix();//��׺ת��׺��������ת�Ĺ�����ʵ�ּ��㣬�ֱ����������������ʵ��
		bool getOperands(T &operands1,T &operands2);//��ȡ�������ĺ���
		void Compute(char op);//����

	public:
		Stack<T> s1;

		//���캯�������ڳ�ʼ�����ݳ�Ա
		Calculator(int size):s1(size)//�˾��﷨�ǳ��ؼ���������˳��ջ��һ����Ҫ��������������Ĺ��캯����ʵ��
		{};//���캯��
		
		~Calculator()//��������
		{}
		void clear();
};

template <class T>
void Calculator<T> :: infixTopostfix()
{
	int size;
	cout<<"�������ַ�ջ��Ԥ����󳤶ȣ�";
	cin>>size;
	Stack<char>s(size);
	
	//������׺ת��׺��Ų�����
	char ch='#',ch1,op;
	s.Push(ch);//��#����ջ��������Ϊѭ�������ı�־
	
	cin>>ch;//������ʽ��һ���ַ�
	while( !s.isEmpty() &&ch!='#' )//ѭ������������
	{
		if (isdigit(ch))//�ж��Ƿ�Ϊ������������ǲ�������ֱ�������Ȼ��������һ�����ʽ���ַ�
		{
			T newoperands;
			cin.putback(ch);//�˻ظն������ַ�
			cin>>newoperands;//���¶��룬��������������
			s1.Push(newoperands);//����������ջ
			//T x;
			//s1.getTop(x);
			//cout<<"ջ��Ԫ�ص�ֵΪ��"<<x<<endl;//�������䣬�������ɺ�ɾ��
			cin>>ch;
		}

		else
		{
			s.getTop(ch1);//������ǲ���������ջ��Ԫ��ȡ�����뼴��������ַ��Ƚ����ȼ�
			if(icp(ch)>isp(ch1))//�������������ַ������ȼ���ջ��Ԫ�ص����ȼ�����ֱ�ӽ������Ԫ�ؽ�ջ��Ȼ��������һ���ַ�
			{
				s.Push(ch);
				cin>>ch;
			}

			else
			{
				if (isp(ch1)>icp(ch))//�������������ַ������ȼ���ջ��Ԫ�ص����ȼ�����ջ��Ԫ���ظ�������ֱ����ǰ�����Ԫ�ؿ��Խ�ջ����������ͬ�����ȼ��Ӷ�����
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
	while(!s.isEmpty())//��ʱ����ջ�г�#���⻹�������Ĳ���������Ҫ����ȫ��������̯�뵽��׺���ʽ��
	{
		s.Pop(op);
		if (op=='#') break;//���ջ�е�Ԫ����#�������뵽��׺���ʽ�У���Ϊ#������һ�������ı�־
		Compute(op);

	}
	cout<<endl;
	T res;//��Ž���ı���
	if (s1.Pop(res))//��ջ������յĽ��
		cout<<"���ʽ�ļ�����Ϊ��"<<res<<endl;

}


template <class T>
bool Calculator<T> :: getOperands(T &operands1,T &operands2)
{
	if (s1.isEmpty())
	{
		cout<<"ȱ���Ҳ�����";
		return false;
	}
	else
	{
		s1.Pop(operands2);//��ջ�õ��ֲ�����
		//cout<<"�Ҳ�����Ϊ��"<<operands2;
		//return true;//�˾䲻���У�����õ��в������������������ִ�У��ò�������������Ӷ�ʹ������ֹ
	}
	if(s1.isEmpty())
	{
		cout<<"ȱ���������";
		return false;
	}
	else
	{
		s1.Pop(operands1);//��ջ�õ���������
		//cout<<"�������Ϊ��"<<operands1;
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
		s1.makeEmpty();//���û������������������ջ�˳�
	}
}

template <class T>
void Calculator<T> ::clear()
{
	s1.makeEmpty();
}


void main ()
{
	int size;
	cout<<"�����������ջ��Ԥ����󳤶ȣ�";
	cin>>size;
	Calculator<double> CALC(size);//������������Ķ���
	CALC.infixTopostfix();//��������Ķ�����ú���ʵ�ּ���
}

bool isdigit(char ch)//�ж��ǲ��ǲ������ĺ���
{
	if (ch>=48&&ch<=57)
		return true;
	else 
		return false;
}



int icp(char ch)//ջ�����ȼ��ıȽϺ���
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




int isp(char ch)//ջ�����ȼ��ıȽϺ���
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

