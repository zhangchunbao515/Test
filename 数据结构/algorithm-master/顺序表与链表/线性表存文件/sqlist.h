typedef int status;
typedef int elemtype;	// ��������������

#define OK    1
#define ERROR 0
#define SIZE  10	// ��ʼ��С
#define INC   10	// ����

// ���Ա�洢�ṹ
typedef struct 
{
	elemtype *base;	// ָ��һ���Լ��ĵط�
	int lenth;		// ��ǰʹ����
	int size;		// ������
}sqlist;

// ��������ṹ
typedef struct node
{
	elemtype data;
	node *next;
}node;

// ������ͷ�ṹ
typedef struct head
{
	node *first;
	node *end;
	int lenth;
}head;

// --------main_inter��Ҫ����--------
void display(void);		// ��ʾ����
void wait(void);		// �ȴ�����
void exe_writefile();	// ˳���д�ļ�
void exe_writefile2();	// ����д�ļ�
void exe_readfile();	// ���ļ���ȡ˳���
void exe_readfile2();	// ���ļ���ȡ����
void back();			// ��������
status existfile(const char *path);	// ����ļ�����

// --------list_inter��Ҫ����--------
status createlist(sqlist *p, int size);
status destorylist(sqlist *p);
status insertlist(sqlist *p, int pos, elemtype *data);
status showlist(sqlist *p);

// ˳����ļ���д����
status writefile(sqlist *p, const char *path);
status readfile(sqlist *p, const char *path);

// --------node_inter��Ҫ����--------
status createnode(head *p);
status destorynode(head *p);
status shownode(head *p);
status append(head *p, elemtype *data);

// �����ļ���д����
status writefile2(head *p, const char *path);
status readfile2(head *p, const char *path);
