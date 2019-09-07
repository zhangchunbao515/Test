/*
2015��10��9��20:03:43
ջ����ʽ�洢(һ�㲻��ͷ���)
*/
# include "comdef.h"

using namespace std;



//��ʼ������
Status InitStack(LinkStack &S)
{
	S = NULL;
	return OK;
}

//ѹջ
Status Push(LinkStack &S,ElemType e)
{
	/*------�½�һ���ڵ�,�����ݷŽ�ȥ-------*/
	LinkStack p; 
	p = (LinkStack)malloc( sizeof(Link) );
	if(!p)
		return ERROR;
	p->data = e;  

	p->next = S;
	S = p;
	return OK;
}

//��ջ
Status Pop(LinkStack &S,ElemType &e)
{
	if(S==NULL)
		return ERROR;
	e = S->data;
	cout<<e<<endl;
	S = S->next;
	return OK;
}

//ȡջ��Ԫ��
Status GetTop(LinkStack &S,ElemType &e)
{
	if(S==NULL)
		return ERROR;
	e = S->data;
	cout<<e<<endl;
	return OK;
}

//ջ�ĳ���
int GetLength(LinkStack S)
{
	int len=0;
	LinkStack p = S;
	while(p)
	{
		p = p->next;
		len++;
	}
	return len;
}

//����ջ
Status ClearStack(LinkStack &S)
{
	if(S==NULL)
		return ERROR;
	LinkStack p;
	while(S)
	{
		p = S;
		S = S->next;
		free(p);
	}
	return OK;
}

int main(void)
{
	LinkStack S;
	InitStack(S);
	Push(S,1);
	Push(S,2);
	Push(S,3);
	Push(S,4);
	int e;
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	int len = GetLength(S);
	cout<<len<<endl;
	ClearStack(S);

	system("pause");
	return 0;
}