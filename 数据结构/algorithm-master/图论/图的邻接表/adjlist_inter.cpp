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
	if (graph->kind == DG || graph->kind == UDG)   // ��Ȩͼ
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

void show(algraph *graph)		// ����ڽӱ�
{
	int i;
	vnode *cur;

	if (!graph) return ;
	for (i=0; i<graph->vexnum; i++)
	{
		printf("[%d][%c]", i, graph->vex[i]);
		cur = graph->vex[i].first;
		while (cur)
		{
			printf(" -> [%d]", cur->adj);
			if (graph->kind == DN || graph->kind == UDN)
				printf("[%d]", cur->wight);
			cur = cur->nextarc;
		}
		printf("\n");
	}
}

inline int find_vex(algraph *graph, elemtype *data)   // ���ҽ���ַ
{
	int i;

	if (!graph) return NO;
	
	for (i=0; i<graph->vexnum; i++)
		if (graph->vex[i].data == *data) return i;
	return NO;
}

inline char *getname(algraph *graph, int addr)		// ���ҽ������
{
	if (!graph || addr < 0 || addr > graph->vexnum) 
		return NULL;
	return &(graph->vex[addr].data);
}

status insert_arc(algraph *graph, 
				  elemtype *st, 
				  elemtype *end, 
				  int wight)
{
	int flag;

	flag = insert_arc_s(graph, st, end, wight);

	// ���������ͼ, ��Ҫ�Ӷ�һ����,
	if (graph->kind == UDG || graph->kind ==UDN)
		insert_arc_s(graph, end, st, wight);
	return flag;
}

// ����һ����, �����������һ�����
status insert_arc_s(algraph *graph, 
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

status remove_arc(algraph *graph, 
				  elemtype *st, 
				  elemtype *end)
{
	int flag;

	flag = remove_arc_s(graph, st, end);
	// ���������ͼ, ��Ҫ��ɾһ����
	if (graph->kind == UDG || graph->kind == UDN)
		remove_arc_s(graph, end, st);
	return flag;
}

status remove_arc_s(algraph *graph, 
				  elemtype *st, 
				  elemtype *end)
{
	vnode *cur;
	vnode *pre;		// ǰ����� [pre] -> [cur]
	int addr, addr2;

	if (!graph) return ERROR;
	addr = find_vex(graph, st);
	addr2 = find_vex(graph, end);
	if (addr == NO || addr2 == NO) return ERROR;

	pre = graph->vex[addr].first;
	cur = graph->vex[addr].first;
	while (cur)
	{
		// ���Ʊ�������, ���� addr2
		if (cur->adj == addr2) 
		{
			// ��ʱҪ�ͷ� cur
			if (pre == cur)		// ��һ�����
			{
				graph->vex[addr].first = cur->nextarc;
				free(cur);
			}
			else	// ���ǵ�һ�����
			{
				pre->nextarc = cur->nextarc;
				free(cur);
			}
			return OK;
		}
		pre = cur;
		cur = cur->nextarc;
	}
	return ERROR;
}

// ����һ����
status insert_vex(algraph *graph, elemtype *name)
{
	if (graph->vexnum >= NUM) return ERROR;
	graph->vex[graph->vexnum].data = *name;
	graph->vex[graph->vexnum].first = NULL;
	graph->vexnum++;
	return OK;
}

// ɾ��һ����
status remove_vex(algraph *graph, elemtype *name)
{
	int i;
	vnode *cur;
	int addr = find_vex(graph, name);

	if (addr == NO) return ERROR;

	// �����ڽӱ�, �ѿɵ��ҵı�, ȫ��ɾ��
	for (i=0; i<graph->vexnum; i++)
	{
		cur = graph->vex[i].first;
		while (cur)
		{
			if (cur->adj == addr)
			{
				cur = cur->nextarc;		// �Ȱ� cur �߹�ȥ, ��ɾ��
				remove_arc(graph, &(graph->vex[i].data), name);
			}
			else cur = cur->nextarc;
		}
	}

	// ���ҿɵ���ı�, ȫ��ɾ��
	cur = graph->vex[addr].first;
	while (cur)
	{
		graph->vex[addr].first = cur->nextarc;
		free(cur);
		cur = graph->vex[addr].first;
	}

	// ��ͷ�ṹ��ɾ����, ����˳����ɾ��
	for (i=addr; i<graph->vexnum; i++)
	{
		graph->vex[i].data = graph->vex[i+1].data;
		graph->vex[i].first = graph->vex[i+1].first;
	}
	graph->vexnum--;

	return OK;
}

// ���ص�һ���ڽӵ�
int first_vex(algraph *graph, elemtype *name)
{
	int addr;

	if (!graph) return NO;

	addr = find_vex(graph, name);	// �ҵ��õ��ַ
	if (addr == NO) return NO;
	if (graph->vex[addr].first) 
		return graph->vex[addr].first->adj;
	else 
		return NO;
}

// ��������� pos ����һ���ڽӵ�
int next_vex(algraph *graph, elemtype *name, elemtype *pos)
{
	int addr, addr2;
	vnode *cur;

	if (!graph) return NO;

	addr = find_vex(graph, name);
	addr2 = find_vex(graph, pos);
	if (addr == NO || addr2 == NO) return NO;

	cur = graph->vex[addr].first;
	while (cur)
	{
		// [addr2] -> [?]
		if (cur->adj == addr2)
		{
			if (cur->nextarc)
				return cur->nextarc->adj;
			else return NO;
		}
		cur = cur->nextarc;
	}
	return NO;
}

char used[NUM];		// ���ʱ������

// �����������
status BFS(algraph *graph, 
		   void (*visit)(algraph *graph, int n))
{
	int i;
	for (i=0; i<NUM; i++) used[i] = 0;   // ��ʼ������

	for (i=0; i<graph->vexnum; i++)
		if (!used[i]) BFS_s(graph, i, visit);
	return OK;
}

// ��ͨ������֧
status BFS_s(algraph *graph, int i, 
			 void (*visit)(algraph *graph, int n))
{
	int queue[NUM];
	int rear = 0;
	int front = 0;
	int tmp;
	vnode *cur;

	// ��������
	queue[rear] = i;
	rear = (rear + 1) % NUM;
	used[i] = 1;		// ��Ƿ�����
	while (rear !=  front)		// �����в���
	{
		// ����, ����, 
		tmp = queue[front];
		front = (front + 1) % NUM;
		visit(graph, tmp);

		// ���� tmp �йص�ȫ�����, �����
		cur = graph->vex[tmp].first;
		while (cur)
		{
			if (!used[cur->adj])
			{
				queue[rear] = cur->adj;
				rear = (rear + 1) % NUM;
				used[cur->adj] = 1;
			}
			cur = cur->nextarc;
		}
	}
	return OK;	
}


// �����������
status DFS(algraph *graph, 
		   void (*visit)(algraph *graph, int n))
{
	int i;
	for (i=0; i<NUM; i++) used[i] = 0;   // ��ʼ������
	
	for (i=0; i<graph->vexnum; i++)
		if (!used[i]) DFS_s(graph, i, visit);
	return OK;
}

// ����, ��ͨ������ͨ��֧
status DFS_s(algraph *graph, int i, 
			 void (*visit)(algraph *graph, int n))
{
	vnode *cur;

	visit(graph, i);	// ���ʺ�, ��������
	used[i] = 1;
	cur = graph->vex[i].first;
	while (cur)			// ��������, �ݹ�����
	{
		if (!used[cur->adj])	// ���û���ʹ�
		{
			used[cur->adj] = 1;		// ���ʹ��
			DFS_s(graph, cur->adj, visit);	// �����ݹ�����
		}
		cur = cur->nextarc;
	}
	return OK;
}


// ����, �ǵݹ�
status DFS2(algraph *graph, 
			void (*visit)(algraph *graph, int n))
{
	int i;
	for (i=0; i<NUM; i++) used[i] = 0;
	
	for (i=0; i<graph->vexnum; i++)		// �ǵݹ��ͨÿ����ͨ��֧
		if (!used[i]) DFS2_s(graph, i, visit);
	return OK;
}

// ��ͨ��ͨ��֧
// ����ÿһ�����, �����������ڽӵ�, �ҵ�һ��û���ʹ� k ����ջ
// ���� k Ҳ���, ֱ����·����,
// ��ջ���ó�һ��, �����������̽
status DFS2_s(algraph *graph, int f,
			void (*visit)(algraph *graph, int n))
{
	int stack[NUM + 10];
	int top = 0;
	char *name;

	stack[top++] = f;			// �������ջ
	while (top || f != NO)		// ��ջ����, ����·��
	{
		while (f != NO)		// ��һ��·���ߵ���
		{
			if (!used[f])
			{
				visit(graph, f);	// ���ʲ����
				used[f] = 1;
			}
			name = getname(graph, f);	// ��õ�ǰ�������
			// �������ڽӵ�̽��
			for (f = first_vex(graph, name);	// �ӵ�һ���ڽӵ�,
				f != NO;
				f = next_vex(graph, name, getname(graph, f)))	
			{
				if (!used[f])	// ֱ���ҵ�һ�����ߵ�, ���˳�
				{
					stack[top++] = f;
					break;
				}
			}
		}
		// ��ʱ f == NO, ��·����, ��ջ�����ó�һ��
		if (top) f = stack[--top];
	}
	return OK;
}
