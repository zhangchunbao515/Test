#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //���ص�״̬
typedef int ElemType ;       //��������

typedef struct LNODE   //���Ա�ĵ�����洢�ṹ
{
	ElemType data;   //������
	struct LNODE *next; //ָ����
}LNODE,*LinkList;