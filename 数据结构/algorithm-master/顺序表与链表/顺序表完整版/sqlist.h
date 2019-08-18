typedef int elemtype;
typedef int status;

#define OK     1
#define ERROR  0
#define SIZE   50    // ԭ��С
#define INC    10    // ����

typedef struct
{
	elemtype *elem;
	int length;
	int size;
}sqlist;


// main_inter.cpp ��
extern sqlist list;				// list ȫ�ֱ�������
void   display();				// ������
void   wait();					// �ȴ�����
int    getnum(char str[]);		// ����û�����Ĳ���
void   back();					// ��������
void   exe_createlist();
void   exe_input();				// ������������
void   exe_destorylist();
void   exe_insert();
void   exe_update();
void   exe_remove();
void   exe_showlist();
void   exe_clearlist();
void   exe_delall();			// ɾ��ȫ��Ԫ��
void   exe_getelem();
void   exe_listlen();


// list_inter.cpp ��
void   init(sqlist *p);				// ��ʼ����
status createlist(sqlist *p);		// ����˳���
status destorylist(sqlist *p);		// �������Ա�
status insert(sqlist *p, int pos, elemtype *data);	// ��������
status update(sqlist *p, int pos, elemtype *data);	// �޸�����
status remove(sqlist *p, int pos);					// ɾ������
status showlist(sqlist *p);							// ��ʾ��������Ԫ��
status clearlist(sqlist *p);						// ���ñ���Ԫ�� д0
status getelem(sqlist *p, int pos, elemtype *back);	// ���ʵ�N��Ԫ��
status listlen(sqlist *p, int *back);				// ��ñ�

