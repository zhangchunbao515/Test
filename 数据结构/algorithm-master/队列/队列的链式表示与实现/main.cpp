# include "comdef.h"
# include <iostream>

using namespace std;

//����һ���ն���
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc( sizeof(QNode) );
	Q.front->next = NULL;
	return OK;
}

//����Ԫ��eΪQ���µĶ�βԪ��
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

//�����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ
//ɾ��
Status DeQueue(LinkQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	QueuePtr p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if(p==Q.rear)   //�������ֻ��һ��Ԫ��,��ɾ���˵�һ��Ԫ��֮��,Q.front��ָ��NULL,���Ҳ���Q.rear��,Q.rear��ָ���λ�ò�������
		Q.rear = Q.front;   //��ֹQ.rear��ʧ
	free(p);
	//cout<<e<<endl;
	return OK;
}

//���ٶ���
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

//�ж��Ƿ�Ϊ�ն���
Status QueueEmpty(LinkQueue Q)
{
	//if(ͷ����β),���,�򷵻�OK    �����෴
	return ( Q.front==Q.rear ); 
}

//���ض���Ԫ�ظ���
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

//���ض��ж�ͷԪ��
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
	LinkQueue Q;
	InitQueue(Q);
	int e=0;
	EnQueue(Q,1);
	EnQueue(Q,2);
	EnQueue(Q,3);
	EnQueue(Q,4);
	QueueLength(Q);
	//DestroyQueue(Q);

	/*DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);*/

	/*if( QueueEmpty(Q) )
		cout<<"�ն���"<<endl;*/
	GetHead(Q,e);
	system("pause");
	return 0;
}