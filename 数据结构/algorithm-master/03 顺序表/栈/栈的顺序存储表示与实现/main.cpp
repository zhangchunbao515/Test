# include "comdef.h"
# include"function.h"
# include <string.h>

using namespace std;


//N����ת����(r)����     OK
void Convertion(int N,int r)
{
	SqStack S;
   if( InitStack(S) )
		cout<<"��ʼ��ջ��˳��洢�ṹ�ɹ�!"<<endl;
   while(N)  //ѹջ
   {
	   Push(S,N%r);
	   N /= r;
   }
   int e;
   while(S.base!=S.top)
   {
	   Pop(S,e);
	   if( e<=9 || e>=0)
		   cout<<e;
	   else
		   cout<<'A'+e-10;
   }
   cout<<endl;
}

////����ƥ��ļ���
//Status TestP(string str)
//{
//   SqStack S;
//   if( InitStack(S) )
//		cout<<"��ʼ��ջ��˳��洢�ṹ�ɹ�!"<<endl;
//	char t;
//	int len = str.length();
//	int i=0;
//	//cout<<len<<endl;
//	while(i<len)
//	{
//		switch(str[i])
//		{
//		   case '(':
//		   case '[':
//			   Push(S,str[i]);  //����ѹջ
//			   break;
//		   case ')':
//			   if( Pop(S,t) )  //���ҳ�ջ,��ջʱ�ж��Ƿ������������ƥ��
//			   {
//				   if( t!='(' )
//					   return ERROR;
//			   }
//			   break;
//		   case ']':
//			   if( Pop(S,t) )
//			      if(t!='[')  
//					  return ERROR;
//			   break;
//		}
//		i++;
//	}
//	return OK;
//}

int main(void)
{
	SqStack S;
	if( InitStack(S) )
		cout<<"��ʼ��ջ��˳��洢�ṹ�ɹ�!"<<endl;
	int e=-1;
	cout<<"ѹջ1,2,3,4"<<endl;
	Push(S,1);
	Push(S,2);
	Push(S,3);
	Push(S,4);
	cout<<"��ջ4,3,2,1"<<endl;
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);

	//if( !Pop(S,e) )
		//cout<<"��ջ"<<endl;

	/*int len = StackLength(S);
	cout<<len<<endl;*/

	/*if( !StackEmpty(S) )
		cout<<"���ǿձ�!"<<endl;*/

	//DestroyStack(S);

	//Convertion(22,8);

	/*if( TestP("([]())") )
		cout<<"OK"<<endl;*/
	/*if( TestP("([)]") )
		cout<<"OK"<<endl;*/

	system("pause");
	return 0;
}