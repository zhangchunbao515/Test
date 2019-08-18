// ͼ���ڽӾ����ADT

#define OK 1
#define ERROR 0
#define INF 0x5FFFFFF	// ���޴�
#define NO -1			// �Ҳ���
#define MAX_NUM 30		// ��󶥵���
#define SIZE 100		// ���У�ջ��С

// ���޴�˵��: ���޴��ܶ�̫��, ��Ϊ��Ҫ���� INF + INF ���׷������

typedef int elemtype;
typedef int status;
typedef int vrtype;		// �ߵ�Ȩֵ
typedef char nametype;	// ��������
typedef char intype;	// ������Ϣ

// ������, ������
typedef enum {DN, UDN} graphkind;

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
status input(mgraph *graph);						// ���������
int find_vex(mgraph *graph, nametype *data);		// Ѱ�� data ��λ��
status insertarc(mgraph *graph, nametype *a, nametype *b, int quan);  // �����
