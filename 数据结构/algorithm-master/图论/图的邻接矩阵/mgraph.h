// ͼ���ڽӾ����ADT

#define OK 1
#define ERROR 0
#define CHARINF '-'		// ���޴�ı�ʾ
#define INF 0x5FFFFFFF	// ���޴�
#define NOT_FOUND -1	// �Ҳ���
#define MAX_NUM 50		// ��󶥵���
#define SIZE 100		// ���У�ջ��С

typedef int elemtype;
typedef int status;
typedef int vrtype;		// �ߵ�Ȩֵ, ����ͼ����bool����
typedef char nametype;	// ��������
typedef char intype;	// ������Ϣ

extern unsigned short int used[MAX_NUM];	// ˵���ⲿ�и� used ����

// D: direction����  G: graphͼ  N: net��
typedef enum {DG, UDG, DN, UDN} graphkind;

// �����߽ṹ
typedef struct arccell
{
	vrtype adj;			// �ߵ�Ȩֵ
	intype *info;		// ������Ϣ
}arccell;

// ͼ���ڽӾ��󴢴�
typedef struct mgraph
{
	nametype vexs[MAX_NUM];				// ���㼯��, ��v1,v2,v3
	arccell  arcs[MAX_NUM][MAX_NUM];	// �ߵļ���
	int vexnum;							// ������
	int arcnum;							// ����
	graphkind kind;						// ͼ������
}mgraph;
// arcs ���Ը��ݶ�������̬����

// �ڽӾ������ز���
status create(mgraph *graph, int kind, int n, nametype *vex);
status create_G(mgraph *graph, graphkind kind, int n, nametype *vex);
status create_N(mgraph *graph, graphkind kind, int n, nametype *vex);
status input(mgraph *graph);				  // ���������
status show(mgraph *graph);					  // ����ڽӾ���
int find_vex(mgraph *graph, nametype *data);  // Ѱ�� data ��λ��
status destory(mgraph *graph);				  // ���ͼ
status getvex(mgraph *graph, int pos, nametype *back);     // ȡ�õ� i ���������
status putvex(mgraph *graph, nametype *old, nametype *data);  // ���¶�������
int firstadjvex(mgraph *graph, nametype *key);				  // ���ص�һ���ڽӵ�
int nextadjvex(mgraph *graph, nametype *old, nametype *key);  // ������һ���ڽӵ�
status insertvex(mgraph *graph, nametype *data);			  // �����½��
status deletevex(mgraph *graph, nametype *data);			  // ɾ�����
status insertarc(mgraph *graph, nametype *a, nametype *b, int quan);	// �����
status deletearc(mgraph *graph, nametype *a, nametype *b);		// ɾ����
status deleteallarc(mgraph *graph, nametype *data);				// ɾ��data�����б�
status graph_DFS(mgraph *graph, status (*visit)(nametype *data));     // ����������ݹ�
status graph_DFS_s(mgraph *graph, status (*visit)(nametype *data));   // �������, ջ
status DFS(mgraph *graph, int addr, status (*visit)(nametype *data)); // ����������ͨ��֧
status graph_BFS(mgraph *graph, status (*visit)(nametype *data));     // �������������
