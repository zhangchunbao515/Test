#include <stdio.h>
#include <stdlib.h>
#include "adjlist.h"

int used[NUM];		// ���ʱ������, �Ƶ���������Ҳ��
int low[NUM];		// ��¼�ɴ���С���
int count;			// ͳ�ƽ�����

// ����ؽڵ㵽 back
// ���ҹؽڵ��㷨, 
// 1, ���в�ֹһ������, ���ǹؽڵ�
// 2. �Ǹ����, ����һ������û�лر�, �ǹؽڵ�
// �� 1. ���ж�, �ӵ�һ����������, û��ȫ�����ʵ�, ˵�����ڶ������
// �� 2. ���ж�, ��η��ֻر�?
// �� used[] ����, ������ȱ���˳����С������,
// ����������������, ��ô�����κ������ı��, ������С�ڸ�
// ��Ҫ��С�ڸ���, ˵���лر�,
// �� low[] ����. ��¼�ɴ�Ľ�����С���,
// ��Ȼ, ����һ���Ӹ� pos, ������һ������ v, ʹ�� low[v] >= used[pos]
// �� pos �ǹؽڵ�
status DFS_node(algraph *graph, char *back)
{
	int i;
	vnode *cur;

	for (i=0; i<graph->vexnum; i++) used[i] = NO;
	used[0] = count = 0;	// �� 0 �Ž����Ϊ�������ĸ�

	cur = graph->vex[0].first;
	back = DFS_node_s(graph, cur->adj, back);	// ��ͨ��������
	if (count < graph->vexnum - 1)		// ˵��û�з�����ȫ
	{
		*back++ = graph->vex[0].data;		// ��ʱ��ʱ�ؽڵ�
		cur = cur->nextarc;
		while (cur)
		{
			if (!used[cur->adj])		// ����û���ʵĽ��
				DFS_node_s(graph, cur->adj, back);
			cur = cur->nextarc;
		}
	}
	*back = '\0';
	return OK;
}

char *DFS_node_s(algraph *graph, int pos, char *back)
{
	vnode *cur;
	int min;	// ��ǰ���Ŀɴ���С���

	// ���� pos �Ľ����, ��Сֻ�ܻص��Լ�
	min = used[pos] = ++count;
	cur = graph->vex[pos].first;
	while (cur)
	{
		if (used[cur->adj] == NO)
		{
			back = DFS_node_s(graph, cur->adj, back);
			// ��Ҫ��� low[cur->adj], ������ݲ���, ���ƶ������ĺ������

			// ���� cur ���ڽӵ�, ��һ����С�ɴ��� min
			if (low[cur->adj] < min) min = low[cur->adj];

			// pos �൱��������, cur �����ڽӵ�
			// ���ն���, ����һ������, pos ���ǹؽڵ�
			if (low[cur->adj] >= used[pos]) 
				*back++ = graph->vex[pos].data;
		}
		else if (used[cur->adj] < min) min = used[cur->adj];
		// ���ڷ��ʹ��ı�, ͬ�����лر�̽��
		cur = cur->nextarc;
	}
	low[pos] = min;		// ���ݵ�ʱ��, �޸�low[pos]
	return back;
}


status BFS(algraph *graph, tree **t)	// �������������
{
	int i;
	cnode *n;
	cnode *p = NULL;	// �����޸� t, �� p ���� t

	*t = NULL;
	for (i=0; i<NUM; i++) used[i] = 0;

	for (i=0; i<graph->vexnum; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			// �Ƚ��ø����, �ڸ�����Ͻ������ӽ��
			n = (cnode *)malloc(sizeof(cnode));
			if (!n) return ERROR;
			n->brother = n->child = NULL;
			n->data = graph->vex[i].data;
			if (p)
			{
				p->brother = n;		// �Ѿ��и���, ���ֵ��Ͻ���
				p = p->brother;
			}
			else p = *t = n;		// ��һ�ν�����
			BFS_s(graph, i, &p);	// ��ͨһ����ͨ��֧
		}
	}
	return OK;
}

status BFS_s(algraph *graph, int i, tree **t)
{
	vnode *cur;		// ͼ�ĵ�ǰ���
	cnode *now;		// ���ĵ�ǰ���
	cnode *pre;		// now ��ǰ�����
	int queue[60];
	int rear = 0;
	int front = 0;
	int first = 1;
	int tmp;

	queue[rear] = i;	// ��������
	rear = (rear + 1) % 60;
	while (rear != front)
	{
		tmp = queue[front];
		front = (front + 1) % 60;
		cur = graph->vex[tmp].first;
		while (cur)		// ���������ڽӵ�
		{
			if (!used[cur->adj])
			{
				used[cur->adj] = 1;
				// �����¿ռ�
				now = (cnode *)malloc(sizeof(cnode));
				now->brother = now->child = NULL;
				now->data = graph->vex[cur->adj].data;
				if (first)		// ������״�, �ں����Ͻ���
				{
					first = 0;				//    t
					(*t)->child = now;		//   /
					pre = (*t)->child;		// child (pre) -> ...
				}
				else	// �����״����ֵ��Ͻ���
				{
					pre->brother = now;
					pre = now;
				}
				queue[rear] = cur->adj;		// ���м�¼
				rear = (rear + 1) % 60;
			}
			cur = cur->nextarc;
		}
	}
	return OK;
}

status DFS(algraph *graph, tree **t)	// �������������
{
	int i;
	cnode *n;
	cnode *p = NULL;

	for (i=0; i<NUM; i++) used[i] = 0;
	for (i=0; i<graph->vexnum; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			// ���������
			n = (cnode *)malloc(sizeof(cnode));
			n->brother = n->child = NULL;
			n->data = graph->vex[i].data;

			if (p)		// ���ǵ�һ�ν���, �Ǿ����ֵܽ��
			{
				p->brother = n;
				p = n;
			}
			else p = *t = n;
			DFS_s(graph, i, &p);
		}
	}
	return OK;
}

status DFS_s(algraph *graph, int i, tree **t)
{
	vnode *cur;
	cnode *n;
	static cnode *now;	// �����ڵݹ��иı�
	static char f = 1;	// ִֻ��һ��

	cur = graph->vex[i].first;
	while (cur)		// ����״̬��
	{
		if (!used[cur->adj])	// ��֦
		{
			used[cur->adj] = 1;
			// �������ӽ��
			n = (cnode *)malloc(sizeof(cnode));
			n->child = n->brother = NULL;
			n->data = graph->vex[cur->adj].data;
			if (f)
			{
				f = 0;
				(*t)->child = n;
				now = n;	// now == �׺���
			}
			else
			{
				now->brother = n;
				now = n;
			}
			DFS_s(graph, cur->adj, &now);
		}
		cur = cur->nextarc;
	}
	return OK;
}

status DFS2(algraph *graph, tree **t)	// �������������(�ǵݹ�)
{
	int i;
	cnode *n;
	cnode *p = NULL;

	for (i=0; i<NUM; i++) used[i] = 0;
	for (i=0; i<graph->vexnum; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			n = (cnode *)malloc(sizeof(cnode ));
			n->child = n->brother = NULL;
			n->data = graph->vex[i].data;
			if (p)
			{
				p->brother = n;
				p = n;
			}
			else p = *t = n;
			DFS2_s(graph, i, &p);
		}
	}
	return OK;
}

status DFS2_s(algraph *graph, int i, tree **t)
{
	vnode *cur;
	int stack[60];
	int top = 0;
	char f = 1;
	int tmp;
	cnode *n;
	cnode *now;

	stack[top++] = i;	// �������ջ
	cur = graph->vex[i].first;
	while (top || cur)
	{
		// �����ڽӵ�, �ҵ�һ�������ߵ�·
		while (cur)
		{
			if (!used[cur->adj])	// �ҵ���
			{
				used[cur->adj] = 1;
				n = (cnode *)malloc(sizeof(cnode));
				n->brother = n->child = NULL;
				n->data = graph->vex[cur->adj].data;
				if (f)		// ��һ�ξ������׺���
				{
					f = 0;
					(*t)->child = n;
					now = n;
				}
				else	// ���ǵ�һ�ξ������ֵ���
				{
					now->brother = n;
					now = n;
				}
				// ��ջ��¼, ��ȥ���ڽӵ�
				// �� cur->adj ��Ϊ���, ��������
				stack[top++] = cur->adj;
				cur = graph->vex[cur->adj].first;
			}
			else cur = cur->nextarc;
		}
		if (top) 
		{
			tmp = stack[--top];		// ������һ��, ��������
			cur = graph->vex[tmp].first;
		}
	}

	return OK;
}


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

	if (!graph) return ;
	while (1)
	{
		fflush(stdin);
		scanf("%c %c", &st, &end);
		if (st == '0' && end == '0') break;
		insert_arc(graph, &st, &end);
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

status insert_arc(algraph *graph, elemtype *st, elemtype *end)
{
	int flag;

	flag = insert_arc_s(graph, st, end);

	// ���������ͼ, ��Ҫ�Ӷ�һ����,
	if (graph->kind == UDG)
		insert_arc_s(graph, end, st);
	return flag;
}

// ����һ����, �����������һ�����
status insert_arc_s(algraph *graph, elemtype *st, elemtype *end)
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
	cur->info = NULL;
	cur->nextarc = graph->vex[addr].first;
	graph->vex[addr].first = cur;
	graph->arcnum++;

	return OK;
}
