# include <iostream>

using namespace std;

#ifndef h1
#define h1
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //���ص�״̬
typedef char TElemType ;       //��������

/*--------------------�������Ķ�������洢��ʾ-----------*/
typedef struct BiTNode
{
	TElemType data;                    //������
	struct BiTNode *lchild, *rchild;   //���Һ���ָ��
}BiTNode,*BiTree;
typedef BiTree ElemType ;       //��������  �ṹ��ָ��
#endif