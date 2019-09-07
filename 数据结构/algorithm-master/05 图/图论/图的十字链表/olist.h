/* -------------------------------------------
// ͼ��ʮ�������漰��ز���
//
//
// ʮ�������ֹ�ϵ��ͼ: 
// [0][A] -> [0][1] -> [0][3] -> [0][4]
// [1][B] -> [1][0]
// [2][C]
// [3][D] -> [3][2]
// [4][E] => [4][0] -> [4][1]
//
// ʮ�������ʺ�����ͼ�Ĵ洢, ֻ��������ͼ
// ʮ�������µĹ������Ѻ��ڽӱ���ͬ, ����д
// �ڽӶ��ر�Ĳ�����ʮ�����������ͬ, ����д
-------------------------------------------- */

typedef char elemtype;
typedef char infotype;
typedef int status;
#define ERROR 0
#define OK 1
#define NUM 30		// �������
#define NO -1		// û�ҵ�


// ʮ��������ṹ  |from|to|fromarc|toarc|
typedef struct vnode
{
	int from;			// ���ҵĶ���
	int to;				// �ɵ��Ķ���
	vnode *fromarc;		// ͷ��ͬ���ڽӵ�
	vnode *toarc;		// β��ͬ���ڽӵ�
	infotype *info;		// ������Ϣ
}vnode;

// ʮ������ͷ�ṹ  |����|fromarc|toarc|
typedef struct 
{
	elemtype data;		// ��������
	vnode *fromarc;		// ��һ������
	vnode *toarc;		// ��һ�����
}olist;

// ʮ������
typedef struct 
{
	olist vex[NUM];		// ͷ�ṹ
	int vexnum;			// ������
	int arcnum;			// ����
}olgraph;


// ------------------ʮ������洢, ͼ����ز���----------------------

status create(olgraph *graph, elemtype *vexs, int n);
status destory(olgraph *graph);			// ����ͼ
void input(olgraph *graph);				// ��������
void show(olgraph *graph);				// ���ʮ������
int find_vex(olgraph *graph, elemtype *data);		// ���ҽ���ַ
status insert_arc(olgraph *graph, elemtype *st, elemtype *end);
status remove_arc(olgraph *graph, elemtype *st, elemtype *end);
int first_vex(olgraph *graph, elemtype *name);
int next_vex(olgraph *graph, elemtype *name, elemtype *pos);
