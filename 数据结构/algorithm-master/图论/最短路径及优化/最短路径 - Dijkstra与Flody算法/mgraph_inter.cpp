#include <stdio.h>
#include "mgraph.h"

// ������
status create(mgraph *graph, int kind, int n, nametype *vex)
{
	int i, j;

	// �Ϸ����
	if (!graph) return ERROR;
	if (n >= MAX_NUM || n <= 0) return ERROR;

	// ��ʼ����Ա
	graph->arcnum = 0;
	graph->kind = (graphkind)kind;
	graph->vexnum = n;
	for (i=0; i<n; i++) graph->vexs[i] = vex[i];

	// ���Ǵ�Ȩͼ, ��ͨ������� INF
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
		{
			// һ��ʼ�ǲ�ͨ��
			graph->arcs[i][j].adj = INF;
			graph->arcs[i][j].info = NULL;
		}
	return OK;
}

// �����߼�
status input(mgraph *graph)
{
	nametype a, b;
	int quan;	// Ȩֵ

	if (!graph) return ERROR;
	while (1)   // ���컡��
	{
		fflush(stdin);
		scanf("%c %c %d", &a, &b, &quan);
		if (a == '0' && b == '0') break;
		insertarc(graph, &a, &b, quan);
		if (graph->kind == UDN) insertarc(graph, &b, &a, quan);
	}
	fflush(stdin);
	return OK;
}

// Ѱ�� data ��λ��
int find_vex(mgraph *graph, nametype *data)
{
	int i;

	for (i=0; i<graph->vexnum; i++)
	{
		if (graph->vexs[i] == *data)
			return i;
	}
	return NO;
}

// �����
status insertarc(mgraph *graph, nametype *a, nametype *b, int quan)
{
	int x, y;

	if (!graph) return ERROR;
	x = find_vex(graph, a);
	y = find_vex(graph, b);
	if (x == NO || y == NO) return ERROR;

	graph->arcs[x][y].adj = quan;
	if (graph->kind == UDN) graph->arcs[y][x].adj = quan;
	return OK;
}
