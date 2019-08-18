// �����޻�ͼ - ��������͹ؼ�·��
// ��Ҫ����
// tsort()     ��������
// cpath()     �ؼ��
// DFS_show()  ����,����ؼ�·��

#include <stdio.h>
#include <malloc.h>
#include "adjlist.h"	// �ڽӱ���ͼ


// ��ø���������, ���浽 back
void init_degree(algraph *graph, int back[])
{
	int i;
	vnode *cur;
	for (i=0; i<graph->vexnum; i++) back[i] = 0;

	for (i=0; i<graph->vexnum; i++)		// �����ڽӱ����н��
	{
		cur = graph->vex[i].first;		// ��ǰ���ڽӵ�
		while (cur)
		{
			back[cur->adj]++;		// �ɴ������� +1
			cur = cur->nextarc;
		}
	}
}

// ---------------------��������------------------------
// ��¼���Ϊ 0 �Ľ��, ����Щ���ȥ���������ڽӵ�����
// ֱ�����п���, �����û��ȫ������, ����ڻ�, 
// ����û�����Ϊ 0 �Ľ��
status tsort(algraph *graph, char *back)
{
	int *indegree;		// ��¼ÿ���������
	int count = 0;		// ��¼���ʵĽ����
	int queue[40];		// ���м�¼
	int rear = 0;
	int front = 0;
	vnode *cur;
	int i, tmp;

	indegree = (int *)malloc(graph->vexnum * sizeof(int));
	init_degree(graph, indegree);		// ��ʼ��ÿ���������

	for (i=0; i<graph->vexnum; i++)		// ��¼���Ϊ 0 �Ľ��
	{
		if (!indegree[i]) 
		{
			queue[rear] = i;
			rear = (rear + 1) % 40;
		}
	}
	while (rear != front)
	{
		tmp = queue[front];
		front = (front + 1) % 40;
		count++;		// ���ʸ���++
		*back++ = graph->vex[tmp].data;		// ��¼һ����������
		cur = graph->vex[tmp].first;
		while (cur)		// �����ڽӵ�
		{
			indegree[cur->adj]--;	// �����ڽӵ�����
			if (indegree[cur->adj] == 0)	// ���� 0 ��Ҳ��ջ
			{
				queue[rear] = cur->adj;
				rear = (rear + 1) % 40;
			}
			cur = cur->nextarc;
		}
	}
	// û�з��ʵ�ȫ�����, ˵���л�
	if (count < graph->vexnum) return ERROR;
	*back = '\0';
	return OK;
}
// -----------------end ��������---------------------


// -------------------�ؼ�·��-----------------------
void output(char *str)
{
	int i;
	printf("(");
	for (i=0; str[i]!='\0'; i++)
	{
		printf("%c", str[i]);
		if (str[i+1] != '\0') printf(", ");
	}
	printf("), ");
}

// �ؼ�·���ݹ鲿��, path ��һ���ؼ�·��, flag �ǹؼ��
void DFS(algraph *graph, 
		 char *path,	// �ؼ�·��
		 char *flag,	// �ؼ����־
		 int start,		// ��ʼ��
		 int top,		// top �� path ��¼λ��
		 int lens,		// lens �ǹؼ�·������
		 int len)		// len Ŀǰ�ĳ���
{	
	vnode *cur = graph->vex[start].first;

	path[top] = graph->vex[start].data;		// ��¼һ����

	// ���û���ڽӵ�, ��ʾ������ɵ�, �����ݹ�, �����
	if (!cur)
	{
		if (len == lens)		// ���·�����ǹؼ�·��, ������
		{
			path[top + 1] = '\0';
			output(path);		// ��һ�ű�������Ҳ��
		}
	}
	else 
	{
		while (cur)		// ����״̬��
		{
			if (flag[cur->adj])		// ��ǵĻ�ǹؼ��
			{
				top += 1;   len += cur->wight;
				DFS(graph, path, flag, cur->adj, top, lens, len);
				top -= 1;   len -= cur->wight;
				// ���ݵ�ʱ��, Ҫ�ָ�ԭ����ֵ, ������һ��·��
			}
			cur = cur->nextarc;
		}
	}
}

// ����, ������йؼ�·��, 
// �ؼ�·���ϵĻ�ǹؼ��,
// ���ؼ����ɵ�·����һ���ǹؼ�·��, 
// Ҫ��� n �����ǹؼ�·��, ������ max_path ���Ǳ�׼������
void DFS_show(algraph *graph, char *flag, int max_path)
{
	int indegree[NUM];
	int i;
	char path[NUM + 10];
	
	init_degree(graph, indegree);
	for (i=0; i<graph->vexnum; i++)
	{ if (!indegree[i]) break; }
	// ��ʱ i �ǿ�ʼ��, ��ʼ��ֻ��һ��
	DFS(graph, path, flag, i, 0, max_path, 0);
}

// ���˼�⻷, ˳���������緢��ʱ�� ve, ������������
status tsort_early(algraph *graph, int *ve, int *stack, int *top)
{
	int indegree[NUM];	// ��¼���
	int queue[60];
	int rear = 0;
	int front = 0;
	int count = 0;	// ͳ�Ʒ��ʶ������
	int i, tmp;
	vnode *cur;

	init_degree(graph, indegree);	// ��ø����������
	for (i=0; i<graph->vexnum; i++)
	{
		ve[i] = 0;			// ��ʼ�����緢��ʱ��
		if (!indegree[i])	// ���Ϊ 0 �ļ�¼
		{	
			queue[rear] = i;
			rear = (rear + 1) % 60;
		}
	}
	while (rear != front)
	{
		tmp = queue[front];
		front = (front + 1) % 60;
		count++;
		stack[(*top)++] = tmp;		// ��¼��������
		cur = graph->vex[tmp].first;
		while (cur)
		{
			// ��ʱ�ߵķ����� tmp �� cur->adj
			indegree[cur->adj]--;	// �����ɴ�������
			if (indegree[cur->adj] == 0)
			{
				queue[rear] = cur->adj;
				rear = (rear + 1) % 60;
			}
			// �����緢��ʱ��, �� v -> w �� wight ʱ��
			// ���ƹ�ʽ ve[w] = max{ ve[v] + wight }
			if (ve[cur->adj] < ve[tmp] + cur->wight) 
				ve[cur->adj] = ve[tmp] + cur->wight;
			cur = cur->nextarc;
		}
	}
	if (count < graph->vexnum) return ERROR;	// �л�
	return OK;
}

// ����ؼ���� flag
// Ҫ�ҹؼ��, �ͱ����ҳ�������ٷ���ʱ����ȵĽ��
status cpath(algraph *graph, char *flag)
{
	int *early;		// ���緢��ʱ��
	int *later;		// ��ٷ���ʱ�� (��Ӱ��ؼ�·��ʱ,��ٵķ���ʱ��)
	int stack[100];   // ��¼����������, ����ٷ���ʱ��
	int top = 0;
	int max = -1;
	int i, tmp;
	vnode *cur;

	early = (int *)malloc(graph->vexnum * sizeof(int));
	later = (int *)malloc(graph->vexnum * sizeof(int));
	if (!(early && later)) return ERROR;

	// ��⻷, �����緢��ʱ�䵽 early
	if (!tsort_early(graph, early, stack, &top)) 
	{
		free(early);   free(later);
		return ERROR;
	}
	// ��ɵ�ֻ��һ��, �ҵ����緢��ʱ�������Ǹ�����ɵ�,
	for (i=graph->vexnum-1; i>=0; i--) 
	{ if (early[i] > max) max = early[i]; }
	for (i=0; i<graph->vexnum; i++) later[i] = max;	// ��ʼ�����ʱ��

	// ����ٷ���ʱ��, ��ʱ early, ���������
	// w <- v ʱ���� wight, ���ƹ�ʽ vl[w] = min{ vl[v] - wight }		
	while (top)
	{
		tmp = stack[--top];
		cur = graph->vex[tmp].first;
		// �����ڽӵ�, Ѱ�ұ��ɳڵĶ���, ��ʱ tmp ���ڽӵ� cur �� wight
		// ���õ��� vl[tmp] û�����, �����������������
		// vl[cur->adj] �� vl[tmp] ֮ǰ�����
		while (cur)
		{
			// ��Ϊ�������������, ����ǰ�෴
			// tmp �ǳ�����, Ҳ��Ҫ�� later �ĵ�, tmp -> cur
			// ���� cur �������Լ�
			if (later[tmp] > later[cur->adj] - cur->wight)
				later[tmp] = later[cur->adj] - cur->wight;
			cur = cur->nextarc;
		}
	}
	// ���������ʱ����ȵĻ���ǹؼ��, ���Ϊ 1
	for (i=0; i<graph->vexnum; i++)
	{
		if (early[i] == later[i]) flag[i] = 1;
		else flag[i] = 0;
	}
	free(early);   free(later);
	return max;
}

int main(void)
{
	algraph graph;		// �ڽӱ�
	char str[70];
	elemtype vexs[NUM];
	char flag[NUM + 5];   // ��¼�ؼ��
	int max_path;		  // �ؼ�·������
	short int kind;
	int n, i;

	printf("�����޻�ͼ - ��������͹ؼ�·��\n");
	printf("������ͼ������ (0.����ͼ, 1.������): ");
	scanf("%d", &kind);
	printf("�����붥�㼯: ");
	scanf("%d", &n);   fflush(stdin);
	for (i=0; i<n; i++) scanf("%1c", vexs + i);
	create(&graph, kind, vexs, n);		// ����ͼ
	printf("������߼�: ");
	input(&graph);		// ��������

	if (graph.kind == DG)	// ������������
	{
		if (tsort(&graph, str))
		{
			printf("\n��������: ");
			for (i=0; str[i]!='\0'; i++)
				printf("%c, ", str[i]);
		}
		else printf("����: ��ͼ���ڻ�!");
	}
	else	// ���йؼ�·��
	{
		max_path = cpath(&graph, flag);
		if (max_path)
		{
			printf("\n�ؼ��: ");
			for (i=0; i<graph.vexnum; i++)
			{	if (flag[i])  printf("%c, ", graph.vex[i].data); }
			printf("\n�ؼ�·��: ");
			DFS_show(&graph, flag, max_path);	// ����ؼ�·��
			printf("\n·������: %d", max_path);
		}
		else printf("����: ��ͼ���ڻ�!");
	}
	printf("\n");
	destory(&graph);
	return 0;
}
