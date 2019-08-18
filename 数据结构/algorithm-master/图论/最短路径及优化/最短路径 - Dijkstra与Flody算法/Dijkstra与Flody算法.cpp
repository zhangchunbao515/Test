/* -------------------------
// ���·���㷨
// ����
// �Ͻ�˹���� (dijkstra)
// �������� (floyd)
// �������ѷǵݹ�ļ�����
----------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mgraph.h"		// ͼ���ڽӾ���ͷ�ļ�

#define MAX MAX_NUM

// �����������, ���������ٵ�·��, �� pre ��¼·��
status BFS(mgraph *graph, char start, char end, int pre[])
{
	int queue[50];		// �򵥶���
	int rear = 0;
	int front = 0;
	char used[MAX];			// ���ʱ������
	int addr1, addr2;		// ���, �յ�
	int i, tmp;
	int cur = 0;

	for (i=0; i<graph->vexnum; i++) used[i] = 0;
	addr1 = find_vex(graph, &start);	// ���ҵ�ַ
	addr2 = find_vex(graph, &end);
	if (addr1 == NO || addr2 == NO) return ERROR;
	if (addr1 == addr2) return ERROR;	// �Լ����Լ�Ҳ����

	queue[rear] = addr1;		// ��������
	rear = (rear + 1) % 50;
	used[addr1] = 1;
	pre[addr1] = NO;		// ���û��ǰ��
	while (rear != front)
	{
		tmp = queue[front];		// ���� tmp ���ڽӵ�, Ѱ��Ŀ��
		front = (front + 1) % 50;
		for (i=0; i<graph->vexnum; i++)
		{
			// û�з��ʹ����ڽӵ�, ȫ�����
			// �� tmp Ϊ����, i Ϊ�ڽӵ�
			if (!used[i] && graph->arcs[tmp][i].adj != INF)
			{
				pre[i] = tmp;		// ��¼·�� - ǰ�����
				if (addr2 == i) return OK;	// �ҵ��յ���˳�
				used[i] = 1;
				queue[rear] = i;
				rear = (rear + 1) % 50;
			}
		}
	}
	return ERROR;
}

// ���� pre[] ��¼��ǰ�����, ���յ�������, ���·��
void extract(mgraph *graph, char *path, int *pre, int end)
{
	int n;
	char buf[MAX + 5];

	n = MAX_NUM + 5;
	buf[--n] = '\0';
	while (end != NO)		// ���յ�������
	{
		buf[--n] = graph->vexs[end];
		end = pre[end];
	}
	strcpy(path, buf + n);
}

void output(char *str)		// ���·��
{
	while (*str != '\0')
	{
		printf("%c", *str);
		str++;
		if (*str != '\0') printf(" -> ");
	}
	printf("\n");
}

void DFS(mgraph *graph)		// �ǵݹ�����
{
	int stack[MAX + 10];
	int top = 0;
	int used[MAX];
	int i;
	int s = 0;		// ���������Ϊ 0

	for (i=0; i<graph->vexnum; i++) used[i] = 0;

	while (top || s != NO)
	{
		while (s != NO)		// ��һ��·, �ѵ���ͷ
		{
			if (!used[s])	//  û���ʹ��Ĳſ�����ջ
			{
				stack[top++] = s;
				used[s] = 1; 
				printf("%c, ", graph->vexs[s]);
			}
			// �� s Ϊ����, ���� s ���ڽӵ� i
			for (i=0; i<graph->vexnum; i++)
			{
				if (!used[i] && graph->arcs[s][i].adj != INF)
				{
					s = i;   break;   // ����ת�Ƶ� i    
				}
			}
			if (i == graph->vexnum) s = NO;
		}
		if (top) s = stack[--top];
	}
}


// -----------------dijkstra ���·���㷨-------------------
// 
// �㷨˼��: ̰��,  �� f(A, B) ��ʾ A �� B �ľ���
// ����, f(A, B) = 10,   f(A, C) = 1,  f(C, B) = 1
// ������, f(A, C) + f(C, B) < f(A, B), ����� f(A, B)
// ����� f(C, B) ���Ǵ�Ѱ�ҵĶ���
// ÿ��ȥ��Ŀǰ��С, ��û�з��ʹ��Ľ�㵱�� f(C, B) ȥ�ɳ��ڽӵ�
// ������ dis[] ��¼Ŀǰ�����·������,  ��used[] ��¼���ʱ��
// pre[] ��¼ǰ�����, ��¼·��
//
status dij_shortpath(mgraph *graph, char st, int dis[], int pre[])
{
	char used[MAX];		// ���ʱ��
	int add;
	int min, pos;
	int i, j;

	add = find_vex(graph, &st);
	if (add == NO) return ERROR;
	
	for (i=0; i<graph->vexnum; i++)		// ��ʼ������
	{ dis[i] = INF;   used[i] = 0; }

	dis[add] = 0;		// �������
	pre[add] = NO;		// �����ǰ��
	for (i=0; i<graph->vexnum; i++)		// n ����, �ɳ� n ��
	{
		// �ҵ�һ��Ŀǰ��С����, ��û�з��ʹ��Ľ��
		// ÿ�ζ�����С�ľ���ȥ�ɳ�, �������Ȼ��С
		min = INF;
		for (j=0; j<graph->vexnum; j++)
		{
			if (!used[j] && dis[j] < min)
			{ pos = j;   min = dis[j]; }
			// min ��¼Ŀǰ�� pos �ľ���
		}
		if (min == INF) break;		// ��ʱ�Ҳ�����С����
		used[pos] = 1;	// ��� pos ʹ����

		// �� pos Ϊ����, �ɳ�δ���ʵ��ڽӵ� j
		for (j=0; j<graph->vexnum; j++)
		{
			// ���ڷ��ʹ��ĵ�, û��Ҫ���ɳ�, ��Ϊ a + min(����)������С�� a
			if (!used[j] && min + graph->arcs[pos][j].adj < dis[j])
			{
				dis[j] = min + graph->arcs[pos][j].adj;
				pre[j] = pos;		// ͬʱ��¼˭�ɳڵ���
			}
		}
	}
	if (min == INF) return ERROR;
	else return OK;
}

// -------------------floyd ���·-----------------------
// ����һ����, ��ȥ���� n ����̽, �������� n �����ɳ�,
// dis[a][b] �����¼��������ľ���
// pre[a][b] ��ʾ a �� b ��·����, b ǰ�����
status floyd_shortpath(mgraph *g, int (*dis)[MAX], int (*pre)[MAX])
{
	int i, j, k;
	int num = g->vexnum;;

	for (i=0; i<num; i++)	// ��ʼ����һ������
	{
		for (j=0; j<num; j++)
		{
			dis[i][j] = g->arcs[i][j].adj;
			if (dis[i][j] != INF) pre[i][j] = i;
			else pre[i][j] = NO;
		}
	}
	for (k=0; k<num; k++)		// ����һ����
		for (i=0; i<num; i++)	// �ھ����н����ɳ�
			for (j=0; j<num; j++)
				if (i != j && dis[i][k] + dis[k][j] < dis[i][j])
				{
					// i �� j �������, ��Ϊ�Լ����Լ���·��û����
					// �� i �� j ����� k ���г���
					// �緢�� i..k + k..j < i..j, ����и���
					dis[i][j] = dis[i][k] + dis[k][j];
					pre[i][j] = pre[k][j];
					// �� i �� j ��·���Ϸ���, �� k �� j ��С
					// �����·�� i..j Ϊ i..k..j
				}
	return OK;
}

int main(void)
{
	mgraph graph;
	int dis[MAX];			// dijkstra ��̾���
	int pre[MAX];			// dijkstra ��¼·��
	char path[MAX][MAX];	// dijkstra ·�����ַ���
	// path[n] �Ƕ��㵽 n ���ַ�����ַ

	int dis2[MAX][MAX];			// floyd ��̾���
	int pre2[MAX][MAX];			// floyd ��¼·��
	char path2[MAX][MAX][MAX];	// floyd ·���ַ���
	int kind;
	int n, i, j;
	nametype vex[MAX];	// �㼯
	char start, end;
	int add;

	printf("������ͼ�����ͣ�(0.������, 1.������):");
	scanf("%d", &kind); 
	printf("�����붥�����������:");
	scanf("%d", &n);   fflush(stdin);
	for (i=0; i<n; i++) scanf("%1c", vex + i);
	create(&graph, kind, n, vex);	// ����ͼ
	printf("������߼���\n");
	input(&graph);					// ��������
	system("cls");
	printf("\n�����������յ�: ");
	scanf("%c %c", &start, &end);

	add = find_vex(&graph, &end);			// �յ��ַ add
	printf("\n�������ٵ�·��: ");			// �������·
	if (BFS(&graph, start, end, pre))
	{
		// pre ��¼��·��, ��ȡ�� path[0] ��
		extract(&graph, path[0], pre, add);
		output(path[0]);		// ���·��
	}
	else printf("δ�ҵ�!\n");
	printf("������ȱ���: ");   DFS(&graph);
	
	printf("\n\ndijkstra ���·: ");
	if (dij_shortpath(&graph, start, dis, pre))
	{	
		// dis ��¼�� A ���κε����̾���
		// pre ��¼�� A ���κε��·��, �ɽ��ж�β�ѯ
		for (i=0; i<graph.vexnum; i++)
			extract(&graph, path[i], pre, i);
		output(path[add]);
		printf("���·������: %d\n", dis[add]);
	}
	else printf("δ�ҵ�!\n");

	if (floyd_shortpath(&graph, dis2, pre2))
	{
		// dis2 ��¼�����������·������
		// ����һ�� flody �㷨, �Ϳɽ��ж�β�ѯ,  
		n = find_vex(&graph, &start);
		if (dis2[n][add] != INF) 
		{
			printf("\nfloyd ���·: ");
			for (i=0; i<graph.vexnum; i++)	// ö�����
			{
				for (j=0; j<graph.vexnum; j++)	// ö���յ�
				{
					extract(&graph, path2[i][j], pre2[i], j);
				}
			}
			output(path2[n][add]);
			printf("���·������: %d\n", dis2[n][add]);
		}
		else printf("\nfloyd ���·: δ�ҵ�!\n");
	}
	return 0;
}
