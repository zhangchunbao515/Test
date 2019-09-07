# include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //���ص�״̬
typedef int ElemType ;       //��������
#define LIST_INIT_SIZE 100    //��ʼ��ʱ����Ĵ�С
#define LISTINCREMENT 10      //���Դ洢�ռ�ķ�������

typedef struct  QNode      //��ʽ��
{
	ElemType data;          //������
	struct QNode *next;    //ָ����,ָ����һ���ڵ�
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;   //��ͷָ��
	QueuePtr rear;    //��βָ��
}LinkQueue;


typedef struct Link   //ջ
{
	ElemType data;
	struct Link *next;
}*LinkStack,Link;
