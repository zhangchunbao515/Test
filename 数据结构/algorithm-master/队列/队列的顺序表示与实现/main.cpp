# include "comdef.h"
# include <iostream>

using namespace std;

//��ʼ��
Status InitQueue(SqQueue &Q)
{
	Q.base = (ElemType *)malloc( sizeof(ElemType)*MAXQSIZE );  //��ʼ�������С4
	if(!Q.base)  //�ж��Ƿ����ɹ�
		return ERROR;
	Q.front = 0;   //��ʼʱ,�����Ŷ�
	Q.rear = 0;
	return OK;
}

//����
Status EnQueue(SqQueue &Q,ElemType e)  //����ʱֻ�ܲ���MAXQSIZE-1��
{
	if( Q.front==(Q.rear+1)%MAXQSIZE )  //2�����   rear�ڶ�ͷ,���м�
		return ERROR;   //��������
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear+1)%MAXQSIZE;  
	//�������鳤��Ϊ4,�±��ѵ���3ʱ,��Q.rear������+1���4,���������,�����ַ��ص�����λ��,
	//ģ�⻷״
	cout<<"���"<<e<<endl;
	return OK;
}

//ɾ��
Status DeQueue(SqQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;  //�ж��Ƿ�ǿ�
	e = Q.base[Q.front];
	cout<<"����"<<e<<endl;
	Q.front = (Q.front+1)%MAXQSIZE;
	return OK;
}

//����
int QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;   //2�����
	return OK;
}

//���ٶ���
Status DestroyQueue(SqQueue &Q)
{
	if(Q.front==Q.rear)
		return ERROR;  //��ջ
	free(Q.base);
	return OK;
}

//���ض�ͷ
Status GetHead(SqQueue Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	e = Q.base[Q.front];
	cout<<"��ͷ��"<<e<<endl;
	return OK;
}

int main(void)
{
	SqQueue Q;
	InitQueue(Q);
	ElemType e=0;
	EnQueue(Q,1);
	DeQueue(Q,e);

	EnQueue(Q,2);
	EnQueue(Q,3);
	GetHead(Q,e);
	system("pause");
	return OK;
}