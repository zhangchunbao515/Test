// ͼ���ڽӱ�Ĵ��漰���ĺ����ֵ�����

typedef char elemtype;
typedef char infotype;
typedef int status;
#define ERROR 0
#define OK 1
#define NUM 30		// �������
#define NO -1		// û�ҵ�

// ����ͼ������
typedef enum {DG, UDG} gkind;

extern int used[NUM];

// ---------�����ֵ�����----------
typedef struct tree
{
	elemtype data;
	tree *child;		// �׺���
	tree *brother;		// �ֵ�
}tree, cnode;


// �ڽӱ���ṹ  |�±�|next|
typedef struct vnode
{
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
status insert_arc(algraph *graph, elemtype *st, elemtype *end);
status insert_arc_s(algraph *graph, elemtype *st, elemtype *end);

// -----------------��������������Ҫ����-------------------
status BFS(algraph *graph, tree **t);			// ���������
status BFS_s(algraph *graph, int i, tree **t);
status DFS(algraph *graph, tree **t);			// ���������
status DFS_s(algraph *graph, int i, tree **t);
status DFS2(algraph *graph, tree **t);			// ���������, �ǵݹ�
status DFS2_s(algraph *graph, int i, tree **t);
status DFS_node(algraph *graph, char *back);	// ����ؽڵ㵽 back
char *DFS_node_s(algraph *graph, int pos, char *back);   // �ҵ�����ͨ��֧
