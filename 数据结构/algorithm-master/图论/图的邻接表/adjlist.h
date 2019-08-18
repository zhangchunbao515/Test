/* -----------------------------
// ͼ���ڽӱ�Ĵ��漰��ز���
//
//
// �ڽӱ���ͼ: 
// [0][A] -> [1] -> [3] -> [4]
// [1][B] -> [0]
// [2][C]
// [3][D] -> [2]
// [4][E] => [0] -> [1]
------------------------------ */

typedef char elemtype;
typedef char infotype;
typedef int status;
#define ERROR 0
#define OK 1
#define NUM 30		// �������
#define NO -1		// û�ҵ�

// ����ͼ������
typedef enum {DG, UDG, DN, UDN} gkind;

extern char used[NUM];


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
void show(algraph *graph);				// ����ڽӱ�
int find_vex(algraph *graph, elemtype *data);		// ���ҽ���ַ
char *getname(algraph *graph, int addr);			// ���ҽ������
status insert_arc(algraph *graph, elemtype *st, elemtype *end, int wight);
status insert_arc_s(algraph *graph, elemtype *st, elemtype *end, int wight);
status remove_arc(algraph *graph, elemtype *st, elemtype *end);
status remove_arc_s(algraph *graph, elemtype *st, elemtype *end);
status insert_vex(algraph *graph, elemtype *name);
status remove_vex(algraph *graph, elemtype *name);
int first_vex(algraph *graph, elemtype *name);
int next_vex(algraph *graph, elemtype *name, elemtype *pos);

status BFS(algraph *graph, void (*visit)(algraph *graph, int n));	// �����������
status BFS_s(algraph *graph, int i, 
			 void (*visit)(algraph *graph, int n));			// ����, ��ͨ������ͨ��֧
status DFS(algraph *graph, void (*visit)(algraph *graph, int n));	// �����������
status DFS_s(algraph *graph, int i, 
			 void (*visit)(algraph *graph, int n));			// ����, ��ͨ������ͨ��֧
status DFS2(algraph *graph, void (*visit)(algraph *graph, int n));	// ����, �ǵݹ�
status DFS2_s(algraph *graph, int f,						// �ǵݹ��ͨÿ����ͨ��֧
			void (*visit)(algraph *graph, int n));			