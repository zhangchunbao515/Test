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

typedef struct Link 
{
	ElemType data;
	struct Link *next;
}*LinkStack,Link;