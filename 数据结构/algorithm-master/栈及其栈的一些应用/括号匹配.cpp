#include <iostream>
#include "ARRSTACK.H"
using namespace std;

int main()//�������ֶβ������Ա��������ȷ��
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

	return 0;
}
