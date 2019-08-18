# include <iostream>
# include "function.h"
using namespace std;

Status Test(string str)
{
	LinkStack S;
	InitStack(S);
	char ch;
	ElemType t1=-1,t2=-1;
	
	for(int i=0; i<str.length(); i++)
	{
		ch=str[i];
		if(ch>=48 && ch<59)    //0-48  9-58     ���������
		{
			Push(S,ch-'0');
		}
		else          //�����+-*/
		{
			Pop(S,t1);
			Pop(S,t2);
			switch(ch)
			{
			    case '+':
					Push(S,t2+t1);
					break;
				case '-':
					Push(S,t2-t1);
					break;
				case '*':
					Push(S,t2*t1);
					break;
				case '/':
					Push(S,t2/t1);
					break;
				default:
					cout<<"�ַ����д�!"<<endl;
			}
		}
	}
	Pop(S,t1);
	cout<<"���Ϊ:"<<t1<<endl;
	return OK;
}

int main(void)
{
	                               //ԭʽ:
	string str = "1234-*+56/-";    //�����Ѿ�֪�� ���������� �ַ���
	Test(str);
	system("pause");
	return 0;
}