//˳��ջ������ʵ�ַ��������а���һ��������������˺���Ϊ���˽�г�Ա,���������������׺ת��׺�Ĳ���
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
void postfix(char expression[]);
int icp(char ch);
int isp(char ch);
bool isdigit(char ch);
const int stackIncreament = 20;//ȫ�ֱ����������������ʱ��̬��������Ҫ�Ĵ洢��Ԫ��
template <class T>
class Stack
{
	private:
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


int main()
{
	int size ;
	cout<<"��������Ҫ����ջ��Ԥ����󳤶�";
	cin>>size;
	Stack<char> s(size);

	char ch='#',ch1,op;
	s.Push(ch);//��#����ջ��������Ϊѭ�������ı�־

	//������׺���ʽ�Ĵ洢����
	const int maxsize = 50;
	char postfix[maxsize];//���ڴ�ź�׺���ʽ���������󳤶ȱ���Ҫ�̶�

	cin.get(ch);//������ʽ��һ���ַ�
	int i=0;//��׺���ʽ��ѭ������������Ҫ��ʼ������������ȷִ��
	while( !s.isEmpty() &&ch!='#' )//ѭ������������
	{
		if (isdigit(ch))//�ж��Ƿ�Ϊ������������ǲ�������ֱ�������Ȼ��������һ�����ʽ���ַ�
		{
			cout<<ch;
			postfix[i++] = ch;
			cin.get(ch);

		}

		else
		{
			s.getTop(ch1);//������ǲ���������ջ��Ԫ��ȡ�����뼴��������ַ��Ƚ����ȼ�
			if(icp(ch)>isp(ch1))//�������������ַ������ȼ���ջ��Ԫ�ص����ȼ�����ֱ�ӽ������Ԫ�ؽ�ջ��Ȼ��������һ���ַ�
			{
				s.Push(ch);
				cin.get(ch);
			}

			else
			{
				if (isp(ch1)>icp(ch))//�������������ַ������ȼ���ջ��Ԫ�ص����ȼ�����ջ��Ԫ���ظ�������ֱ����ǰ�����Ԫ�ؿ��Խ�ջ����������ͬ�����ȼ��Ӷ�����
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
	while(!s.isEmpty())//��ʱ����ջ�г�#���⻹�������Ĳ���������Ҫ����ȫ��������̯�뵽��׺���ʽ��
	{
		s.Pop(op);
		if (op=='#') break;//���ջ�е�Ԫ����#�������뵽��׺���ʽ�У���Ϊ#������һ�������ı�־
		cout<<op;
		postfix[i++] = op;
	}
	for(int j=0;j<i;j++)
	{
		cout<<postfix[j];//����׺���ʽ���
	}

	return 0;
}


bool isdigit(char ch)//�ж��ǲ��ǲ������ĺ���
{
	if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '#' && ch != '('&& ch !=')' )
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
	case'+':return 2;break;
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
	case'*': return 5;break;
    case'/': return 5;break;
	case'(':return 1;break;
	default:return -1;break;
	}
}


