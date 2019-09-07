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
	cout<<"ѹջ:"<<e<<endl;
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
	cout<<"��ջ:"<<e<<endl;
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