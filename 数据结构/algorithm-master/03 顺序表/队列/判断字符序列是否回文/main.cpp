# include "comdef.h"
# include <iostream>

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
	//cout<<e<<endl;
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


/*-------------------------------------------------�����ķֽ���------------------------------------------------------*/

//����һ���ն���    ����
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc( sizeof(QNode) );
	Q.front->next = NULL;
	return OK;
}

//����Ԫ��eΪQ���µĶ�βԪ��   ����
//����
Status EnQueue(LinkQueue &Q,ElemType e)
{
	QueuePtr p = (QueuePtr)malloc( sizeof(QNode) );
	p->next = NULL;  //����βָ��NULL
	p->data = e;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

//�����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ   ����
//ɾ��
Status DeQueue(LinkQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	QueuePtr p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if(p==Q.rear)   //�������ֻ��һ��Ԫ��,��ɾ���˵�һ��Ԫ��֮��,Q.rear��ָ���λ�ò�������
		Q.rear = Q.front;   //��ֹQ.rear��ʧ
	free(p);
	//cout<<e<<endl;
	return OK;
}

//���ٶ���   ����
Status DestroyQueue(LinkQueue &Q)
{
	if(Q.front==Q.rear)
		return ERROR;
	while(Q.front)  //��ͷָ�뿪ʼ,һֱɾ������,ֱ�����һ��
	{
		Q.rear = Q.front->next;   //��rear����Ϊ��������,����������һ������
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

//�ж��Ƿ�Ϊ�ն���  ����
Status QueueEmpty(LinkQueue Q) 
{
	//if(ͷ����β),���,�򷵻�OK    �����෴
	return ( Q.front==Q.rear );  
}

//���ض���Ԫ�ظ���   ����
int QueueLength(LinkQueue Q)
{
	int len=0;
	while(Q.front!=Q.rear)   //��ͷ������β��ʱ��,ֹͣ����
	{
		Q.front = Q.front->next;
		len++;
	}
	//cout<<len<<"��Ԫ��"<<endl;
	return len;
}

//���ض��ж�ͷԪ��  ����
Status GetHead(LinkQueue Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	e = Q.front->next->data;   //Q.front����һ����data
	cout<<e<<endl;
	return OK;
}

int main(void)
{
	LinkQueue L;   //��ʽ  ����
	InitQueue(L);
	LinkStack S;
	InitStack(S);  //��ʽ ջ
	ElemType a[3] = {1,2,2};
	for(int i=0; i<3; i++)
	{
		Push(S,a[i]);   //ѹջ
		EnQueue(L,a[i]);  //���
	}
	ElemType temp1,temp2;
	bool t=true;
	for(int i=0; i<3; i++)
	{
		Pop(S,temp1);
		DeQueue(L,temp2);
		if(temp1!=temp2)
		{
			t=false;
			cout<<"���ǻ�����Ŷ"<<endl;
			break;
		}
	}
	if(t==true)
	   cout<<"�ǻ�����"<<endl;
	system("pause");
	return 0;
}