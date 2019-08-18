#include <stdio.h>
#include <stdlib.h>
#include "adjlist.h"


// ����ͼ
status create(algraph *graph, 
			  int kind, 
			  elemtype *vexs, 
			  int n)
{
	int i;

	if (!graph || n >= NUM) return ERROR;

	graph->arcnum = 0;
	graph->kind = (gkind)kind;
	graph->vexnum = n;
	for (i=0; i<n; i++)
	{
		graph->vex[i].data = vexs[i];
		graph->vex[i].first = NULL;
	}
	return OK;
}

// ����ͼ
status destory(algraph *graph)
{
	int i;
	vnode *del;

	if (!graph) return ERROR;

	// ����ͷ�ṹ
	for (i=0; i<graph->vexnum; i++)
	{
		// ����ÿ�����
		del = graph->vex[i].first;
		while (del)
		{
			graph->vex[i].first = del->nextarc;
			free(del);
			del = graph->vex[i].first;
		}
	}
	graph->arcnum = 0;
	graph->vexnum = 0;
	return OK;
}

void input(algraph *graph)		// ����
{
	char st, end;
	int wight;

	if (!graph) return ;
	if (graph->kind == DG)   // ��Ȩͼ
	{
		while (1)
		{
			fflush(stdin);
			scanf("%c %c", &st, &end);
			if (st == '0' && end == '0') break;
			insert_arc(graph, &st, &end, 0);
		}
	}
	else
	{
		while (1)
		{
			fflush(stdin);
			scanf("%c %c %d", &st, &end, &wight);
			if (st == '0' && end == '0' && !wight) break;
			insert_arc(graph, &st, &end, wight);
		}
	}
	fflush(stdin);
}

inline int find_vex(algraph *graph, elemtype *data)   // ���ҽ���ַ
{
	int i;

	if (!graph) return NO;
	
	for (i=0; i<graph->vexnum; i++)
		if (graph->vex[i].data == *data) return i;
	return NO;
}

// ����һ����, �����������һ�����
status insert_arc(algraph *graph, 
				  elemtype *st, 
				  elemtype *end, 
				  int wight)
{
	int addr, addr2;
	vnode *cur;

	if (!graph) return ERROR;

	addr = find_vex(graph, st);			// �ҵ�����ַ
	addr2 = find_vex(graph, end);		// �ҵ��յ��ַ
	if (addr == NO || addr2 == NO) return ERROR;

	cur = graph->vex[addr].first;
	while (cur)		// ������иñ�, ���ظ�����,
	{
		if (cur->adj == addr2) return ERROR;
		cur = cur->nextarc;
	}

	// Ϊ�˷���, ����ͷ�巨
	cur = (vnode *)malloc(sizeof(vnode));
	cur->adj = addr2;
	cur->wight = wight;
	cur->info = NULL;
	cur->nextarc = graph->vex[addr].first;
	graph->vex[addr].first = cur;
	graph->arcnum++;

	return OK;
}
