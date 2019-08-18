#include <iostream>
#include "ARRSTACK.H"
#include "isdigit.H"
#include "icp.H"
#include "isp.H"
using namespace std;

int main()
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
	cout<<endl;
	return 0;
}

/*==================================================================
                ��������Ҫ����ջ��Ԥ����󳤶ȣ�100
				5+3*(3+4)/9-3#
				5634+*9/+3-
				5634+*9/+3-
				press any key to continue
==================================================================*/

