/* -----------------------------------
// ��С�������������㷨
// �����ڽӾ��󴢴������Ȩͼ
// 
// ��Ҫ����:
// prim();       ����ķ (prim)
// kruskal();    ��³˹���� (kruskal)
-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int status;
typedef char elemtype;
typedef char ntype;
#define ERROR 0
#define OK 1
#define NUM 30			// �������
#define INF 0xFFFFFFF	// ��ʾ�����
#define NO -1			// û�ҵ�

// kruakal �ĸ����ռ�
// ��ʵ kruskal �㷨���ڽӱ����
typedef struct		// ��¼ȫ���ı�
{
	int from;		// ���
	int to;			// �յ�
	int wight;		// Ȩֵ
}recond2;


// �ڽӾ����һ�����
typedef struct 
{
	int wight;		// Ȩֵ
	char *info;		// ������Ϣ
}arc;

// ----------�ڽӾ���-----------
typedef struct
{
	arc arcs[NUM][NUM];		// �߼�
	ntype name[NUM];		// �㼯
	int vexnum;			// ������
	int arcnum;			// ����
}mgraph;

void init(mgraph *graph)		// ��ʼ��ͼ
{
	int i, j;

	for (i=0; i<NUM; i++)
	{
		for (j=0; j<NUM; j++)
		{
			// Ȩֵ�����, ��ʾ��ͨ
			graph->arcs[i][j].wight = INF;
			graph->arcs[i][j].info = NULL;
		}
		graph->name[i] = '\0';
		graph->arcnum = 0;
		graph->vexnum = 0;
	}
}

// ���� data ���±��Ƕ���
short int find_addr(mgraph *graph, elemtype *data)
{
	short int i;
	for (i=0; i<graph->vexnum; i++)
		if (graph->name[i] == *data) return i;
	return NO;
}

// -----------kruskai �Ĳ��鼯-------------
int parent[NUM];		// ָʾ˫�׽��

void init_set(int n)
{
	int i;
	for (i=0; i<n; i++) parent[i] = i;
}

int root(int a)		// �ݹ�ѹ��Ч�ʽϵ�
{
	if (parent[a] != a)
		parent[a] = root(parent[a]);
	return parent[a];
}

int root2(int a)
{
	int i = a, tmp;
	while (parent[a] != a) a = parent[a];	// ����
	while (i != a)		// �ǵݹ�ѹ��·��
	{
		tmp = parent[i];
		parent[i] = a;
		i = tmp;
	}
	return a;
}

void union_set(int a, int b)
{
	a = root2(a);	// �����ϴ�
	b = root2(b);
	if (a != b) parent[a] = b;
	// �ϴ�һ���ͺϲ�
	// parent[b] = a;  Ҳ��
	// ��Ϊ·��ѹ����ʱ��, �ή�����
}

void sort(recond2 *re, int n)		// ð������
{
	int i, j;
	recond2 tmp;
	char flag;

	for (i=0; i<n-1; i++)
	{
		flag = 1;
		for (j=0; j<n-2; j++)
		{
			if (re[j].wight > re[j+1].wight)
			{
				tmp = re[j];
				re[j] = re[j+1];
				re[j+1] = tmp;
				flag = 0;
			}
		}
		if (flag) break;
	}
}

void input(mgraph *graph)		// ����ģ��
{
	char vex[NUM + 2];
	int len, i;
	int wight;
	char a, b;
	short int addr1, addr2;

	printf("�����붥�㼯: ");
	scanf("%s", vex);   fflush(stdin);
	len = strlen(vex);
	graph->vexnum = len;
	for (i=0; i<len; i++)
		graph->name[i] = vex[i];
	printf("������߼�: ");
	while (1)
	{
		fflush(stdin);
		scanf("%c %c %d", &a, &b, &wight);
		if (a == '0' && b == '0' && wight == 0) break;
		addr1 = find_addr(graph, &a);
		addr2 = find_addr(graph, &b);
		if (!(addr1 == NO || addr2 == NO) && wight > 0)
		{
			graph->arcs[addr1][addr2].wight = wight;
			graph->arcs[addr2][addr1].wight = wight;
			graph->arcnum++;
		}
	}
	fflush(stdin);
}

// ���ص�һ���ڽӵ�
inline int first_vex(mgraph *graph, int addr)
{
	int i;
	if (addr < 0 || addr >= graph->vexnum) return NO;

	for (i=0; i<graph->vexnum; i++)
		if (graph->arcs[addr][i].wight != INF)
			return i;
	return NO;
}

// ������һ���ڽӵ�
inline int next_vex(mgraph *graph, int addr, int pos)
{
	int i;
	if (addr < 0 || addr >= graph->vexnum) return NO;
	if (pos < 0 || pos >= graph->vexnum) return NO;

	for (i=pos+1; i<graph->vexnum; i++)
		if (graph->arcs[addr][i].wight != INF) 
			return i;
	return NO;
}

void output(mgraph *graph, int a, int b)	// ���һ����
{
	printf("(%c, %c), ", graph->name[a], graph->name[b]);
	// ����ֱ���������Ļ
	// Ҳ������һ�����鱣��߼�
	// �������ڽӾ���, �ڽӱ���߼�
	// ���������Ĵ洢��������
	// ����...
}


// ---------------��С������ - ����ķ�㷨--------------------
// 
// �㷨:  ÿ�δ� 0 ����ѡһ��Ȩֵ��С�Ľ�� cur
// �� cur ���� 1 ��, �� cur ���������ڽӵ�, ���ɳڲ���
// ֱ�� n ����㶼���� 1 ��, ��ִ�� n �β���
// ����ķ�㷨������޹�, �ʺϳ���ͼ, 
status prim(mgraph *graph)
{
	typedef struct		// �����ռ俪��������Ҳ��
	{
		int pre;		// ��¼ǰ�����, Ҳ����˭���µ��ҵĽ��
		int wight;		// ��¼��СȨֵ
		char set;		// ��¼���ڼ���
	}recond;
	recond *re;
	int i, j;
	int start;
	int min, cur;
	int result = 0;		// ����Ȩֵ
	
	// �����ռ�, ����ʼ��
	re = (recond *)malloc(graph->vexnum * sizeof(recond));
	if (!re) return ERROR;
	for (i=0; i<graph->vexnum; i++)
	{
		re[i].pre = i;			// ��ʼû��ǰ�����
		re[i].set = 0;			// ��ʼ���� 0 ����
		re[i].wight = INF;		// �������㲻ͨ
	}
	start = 0;			// �����һ�������, start = 1,2,3...����
	re[start].wight = 0;		// �Լ����Լ��ľ����� 0

	for (i=0; i<graph->vexnum; i++)		// ѡ�� n ����
	{
		// �� 0 ������, ѡ��һ��Ȩֵ��С��
		min = INF;   cur = NO;
		for (j=0; j<graph->vexnum; j++)
		{
			if (re[j].set == 0 && re[j].wight < min)
			{
				min = re[j].wight;	// �ҵ���С��
				cur = j;			// ��¼λ��
			}
		}
		if (cur == NO) return result;	 // ����: ����һ����ͨͼ
		else if (start != cur)			 // ���һ����, �ۼ�Ȩֵ
		{
			// re[cur].pre �� cur ��ǰ�����, �������� parent
			output(graph, re[cur].pre, cur);
			result += graph->arcs[ re[cur].pre ][cur].wight;
		}
		re[cur].set = 1;	// ʹ�ù��ĵ�, ���� 1 ����

		// ���� cur ���ڽӵ�, ����Ȩֵ, �������·���ɳڲ���,
		// ��ǰ����� cur, cur �� j ������̽, 
		for (j = first_vex(graph, cur);
			j != NO;
			j = next_vex(graph, cur, j))
		{
			// cur �� j ��Ȩֵ��ԭ��С, �͸���
			if (graph->arcs[cur][j].wight < re[j].wight)
			{
				re[j].pre = cur;		// ����ǰ�����
				re[j].wight = graph->arcs[cur][j].wight;
			}
		}
	}
	free(re);
	return result;
}


// ---------------��С������ - ��³˹�����㷨----------------
// 
// ÿ��ȥ��Ȩֵ��С���Ҳ��γɻ�·�ı�, ��ͨ������֧
// ֱ������ n - 1 ��
// ���鼯�жϻ�·,  [from][to][wght] ����߼�
// ��³˹�����㷨������й�, �ʺ�ϡ��ͼ
int kruskal(mgraph *graph)
{
	recond2 *re;
	int i, j;
	int cur = 0;
	int result = 0;
	int count = 0;
	int a, b;

	re = (recond2 *)malloc(graph->vexnum * sizeof(recond2));
	if (!re) return ERROR;

	// ���ڽӾ�������ȡ���бߵ� re ��
	// ����ͼ����Գ�, ֻ��ȡ������
	for (i=0; i<graph->vexnum; i++)
		for (j=0; j<i; j++)
			if (graph->arcs[i][j].wight != INF)
			{
				re[cur].wight = graph->arcs[i][j].wight;
				re[cur].from = i;
				re[cur++].to = j;
			}
	sort(re, cur);		// ��Ȩֵ����ð������

	init_set(graph->vexnum);	// Ҫ�ǵó�ʼ�����鼯
	for (i=0; i<cur; i++)
	{
		a = re[i].from;   b = re[i].to;		// ��������˵�
		if (root2(a) != root2(b))
		{
			union_set(a, b);		// �ϲ�
			output(graph, a, b);	// �����
			result += re[i].wight;
			count++;
			// n ��������Ҫ n-1 ���߼�����ͨ
			if (count == graph->vexnum - 1) break;
		}
	}
	return result;
}

int main(void)
{
	mgraph graph;	// ͼ���ڽӾ���
	int wight;

	init(&graph);
	printf("������һ�������Ȩͼ: \n");
	input(&graph);

	printf("\nprim �㷨:\n��С�������߼�: ");
	wight = prim(&graph);					// ����ķ�㷨
	printf("\n��Ȩֵ: %d\n", wight);

	printf("\n\nkruskal �㷨:\n��С�������߼�: ");
	wight = kruskal(&graph);				// ��³˹�����㷨
	printf("\n��Ȩֵ: %d\n\n", wight);

	return 0;
}
