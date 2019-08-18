//˳��ջ������ʵ�ַ��������а���һ��������������˺���Ϊ���˽�г�Ա,���������������׺ת��׺�Ĳ���,����ʵ�ּ�������
#include <iostream>
#include <string>
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
		void print()
		{
			int i;
			for(i=0;i<=top;i++)
				cout<<elements[i];
			cout << endl;
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


void main()
{
	int size ;
	cout<<"��������Ҫ����ջ��Ԥ����󳤶�:";
	cin>>size;
	Stack<char> s(size);
	
	char ch='#',ch1,op;
	s.Push(ch);//��#����ջ��������Ϊѭ�������ı�־

	//������׺���ʽ�Ĵ洢����
	const int maxsize = 50;
	char postfix[maxsize];//���ڴ�ź�׺���ʽ���������󳤶ȱ���Ҫ�̶�
	
	cin>>ch;//������ʽ��һ���ַ�
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
			postfix[i++] = ' ';

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
					//postfix[i++] = ' ';
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
		postfix[i++] = ' ';
		postfix[i++] = op;
	}

	cout<<endl<<"postfix:";
	for(int j=0;j<i;j++)
	{
		cout<<postfix[j];//����׺���ʽ���
	}
	cout<<endl;



	//���������ʵ�ִ��룬����ʵ�ּ򵥵��������㣬Ŀ�����Ϊ��׺���ʽ����postfix[maxsize]�洢Ŀ����롣
	int Size;
	cout<<"��������Ҫ����ջԤ����󳤶ȣ���ջ���ڴ�ź�׺���ʽ������������";
	cin>>Size;
	Stack <int> s1(Size);//����һ��������ջ�������׺���ʽ��ɨ��ʱ��������ջ
	
	int left;//�������
	int right;//�Ҳ�����

	for(int k=0;k<j;k++)
	{
		int temp=0;
		bool flag=false;
		cout << "postfix["<<k<<"]="<<postfix[k]<<endl;
		while(isdigit(postfix[k]))
		{
			temp=temp*10+postfix[k]-48;
			flag = true;
			k++;
		}
		cout << "temp="<<temp<<endl;
		if (flag)
		{
			s1.Push(temp);//�ж������׺���ʽ��ĳ���ַ��ǲ�����ֱ�ӽ�ջ��������һ��ѭ��
			cout<<"push:";
			s1.print();
		}
		else
		{
			if (postfix[k]==' ') continue;
			//����������
			if (s1.isEmpty())
			{
				cout<<"ȱ���Ҳ�����";
				return;
			}

			else
			{
				s1.Pop(right);
				cout<<"�Ҳ�����Ϊ��"<<right;
				cout<<endl<<"pop:";
				s1.print();
			}


			//����Ҳ�����
			if(s1.isEmpty())
			{
				cout<<"ȱ���������";
				return;
			}
			else
			{
				s1.Pop(left);
				cout<<"�������Ϊ��"<<left;
				cout<<endl<<"pop:";
				s1.print();
			}
			cout<<endl;
			
			
		    int value=0;
			int temp;
			switch(postfix[k])
			{
				case'+': 
					value = (left) + (right);
					s1.Push(value);
					s1.getTop(temp);/*���ջ��,�����ٴ������ջʱջ��Ԫ��ֵ������ͬ*/
					cout<<"ջ��Ԫ��Ϊ��"<<temp;
					cout<<endl; break;
				case'-': 
					value = (left) - (right);
					s1.Push(value);
					s1.getTop(temp);
					cout<<"ջ��Ԫ��Ϊ��"<<temp;
					cout<<endl;  break;
				case'*': 
					value = (left) * (right);
					s1.Push(value);
					s1.getTop(temp);
					cout<<"ջ��Ԫ��Ϊ��"<<temp;
					cout<<endl;  break;
				case'/':
					value = (left) / (right);s1.Push(value);s1.getTop(temp);cout<<"ջ��Ԫ��Ϊ��"<<temp;cout<<endl; break;
			}
			cout<<endl<<"PUSH:";
			s1.print();
		}
	}
	int result;
	s1.Pop(result);
	cout<<"���ʽ�Ľ��Ϊ��"<<result;
	cout<<endl;
}
	


bool isdigit(char ch)//�ж��ǲ��ǲ������ĺ���
{
	//if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '#' && ch != '('&& ch !=')' )
	if(ch>='0'&&ch<='9')
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


	