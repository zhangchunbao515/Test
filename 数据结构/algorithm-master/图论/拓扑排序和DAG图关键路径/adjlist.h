// ͼ���ڽӱ�Ĵ��漰��ز���

typedef char elemtype;
typedef char infotype;
typedef int status;
#define ERROR 0
#define OK 1
#define NUM 30		// �������
#define NO -1		// û�ҵ�

// ͼ������
typedef enum {DG, DN} gkind;

// �ڽӱ���ṹ  |�±�|next|
typedef struct vnode
{
	int wight;			// Ȩֵ
	int adj;			// �ɵ��Ķ���
	vnode *nextarc;		// ��һ����
	infotype *info;		// ������Ϣ
}vnode;

// �ڽӱ�ͷ�ṹ  |����|ָ����|
typedef struct 
{
	elemtype data;		// ��������
	vnode *first;		// ��һ����
}adjlist;

// �ڽӱ�
typedef struct 
{
	adjlist vex[NUM];	// ͷ�ṹ
	int vexnum;			// ������
	int arcnum;			// ����
	gkind kind;
}algraph;

// ------------------�ڽӱ�洢, ͼ����ز���----------------------
status create(algraph *graph, int kind, elemtype *vexs, int n);
status destory(algraph *graph);			// ����ͼ
void input(algraph *graph);				// ��������
int find_vex(algraph *graph, elemtype *data);		// ���ҽ���ַ
status insert_arc(algraph *graph, elemtype *st, elemtype *end, int wight);
