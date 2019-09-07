//˳��ջ������ʵ�ַ��������а���һ��������������˺���Ϊ���˽�г�Ա,�����������������ƥ��Ĳ���
#include <iostream>
#include <string>
//#include <assert>
using namespace std;
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
			assert( elements != NULL );//ʹ���˶�����䣬���������ʽ����ʱ���������ִ�У���������жϴ�����򣬳�����ֹ������������
			/*if ( elements == NULL)
			{
				cout<<"����洢�ռ����\n"<<endl;
				exit(1);
			}//�ж϶�̬����ռ��Ƿ�ɹ�����ע�������*/
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
		cout<<"ջΪ��"<<endl;
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
		cout<<"ջΪ��"<<endl;
		return false;
	}
	else
	{
		x = elements[top];
		return true;
	}
}

void main()//�������ֶβ������Ա��������ȷ��
{//����һ���ַ�����������е������Ƿ�ƥ��,������������ţ�������ջ����������������ж���ջ�������Ƿ�Ϊ�����ţ�����ǽ����ջ
	int size=0;
	cout<<"������ջ�ռ��Ԥ�����ֵ:";
	cin>>size;
	Stack< int > st(size);//����ջ�����ڴ�ű��ʽ������±�



	int i = 0;//ѭ�����Ʊ���
	const int maxsize = 50;
	char a;//��ʱ���������ڸ��ַ�����ֵ
	char expression[maxsize];//�����ַ�����
	char endTag = '#';
	for ( i=0;i<maxsize-1 ;i++ )
	{
		cout<<"�������ַ������һ��Ԫ��ֵ����enter��������";
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
				cout<<"��"<<j<<"��λ�õ����������"<<i<<"��λ�õ�������ƥ��";
			}
			else 
			{
				cout<<"û�����"<<i<<"��������ƥ���������";
			}

	}
	while ( st.isEmpty() == false )
	{
		st.Pop(i);
		cout<<"û�����"<<i<<"��������ƥ���������";
	}
}









