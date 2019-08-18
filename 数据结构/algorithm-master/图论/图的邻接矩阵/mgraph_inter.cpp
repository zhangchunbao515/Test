#include <stdio.h>
#include "mgraph.h"

// ����ͼ
status create(mgraph *graph, int kind, int n, nametype *vex)
{
	switch (kind)
	{
	case DG  : return create_G(graph, DG, n, vex);
	case UDG : return create_G(graph, UDG, n, vex);
	case DN  : return create_N(graph, DN, n, vex);
	case UDN : return create_N(graph, UDN, n, vex);
	default : return ERROR;
	}
}

// ����ͼ
status create_G(mgraph *graph, graphkind kind, int n, nametype *vex)
{
	int i, j;

	// �Ϸ����
	if (!graph) return ERROR;
	if (n >= MAX_NUM || n <= 0) return ERROR;

	// ��ʼ������Ա
	graph->kind = kind;
	graph->arcnum = 0;
	graph->vexnum = n;
	for (i=0; i<n; i++) graph->vexs[i] = vex[i];
	
	// ��ʼ���ڽӾ���
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
		{
			// ͼû��Ȩֵ,0�ǲ�ͨ
			graph->arcs[i][j].adj = 0;
			graph->arcs[i][j].info = NULL;
			// ���踽����Ϣ��
		}
	return OK;
}

// ������
status create_N(mgraph *graph, graphkind kind, int n, nametype *vex)
{
	int i, j;

	// �Ϸ����
	if (!graph) return ERROR;
	if (n >= MAX_NUM || n <= 0) return ERROR;

	// ��ʼ����Ա
	graph->arcnum = 0;
	graph->kind = kind;
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
	if (graph->kind == DG || graph->kind == UDG)
	{
		while (1)   // ����߼�
		{
			fflush(stdin);
			scanf("%c %c", &a, &b);
			// scanf(info)  ���������븽����Ϣ
			if (a == '0' && b == '0') break;   // ͬʱΪ 0
			insertarc(graph, &a, &b, 0);
			if (graph->kind == UDG) insertarc(graph, &b, &a, 0);
			// ����ͼ�ԳƵ�ҲҪ����
		}
	}
	else 
	{
		while (1)   // ���컡��
		{
			fflush(stdin);
			scanf("%c %c %d", &a, &b, &quan);
			if (a == '0' && b == '0') break;
			insertarc(graph, &a, &b, quan);
			if (graph->kind == UDN) insertarc(graph, &b, &a, quan);
		}
	}
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
	return NOT_FOUND;
}

// ����ڽӾ���
status show(mgraph *graph)
{
	int i, j;
	int n;
	
	if (!graph) return ERROR;
	
	// �����������
	n = graph->vexnum;
	printf("%4c", ' ');
	for (i=0; i<n; i++)
		printf("%4c", graph->vexs[i]);
	printf("\n");
	
	// �����ͼ
	if (graph->kind == UDG || graph->kind == DG)
	{
		// �������
		for (i=0; i<n; i++)
		{
			printf("%4c", graph->vexs[i]);
			for (j=0; j<n; j++)
			{
				printf("%4d", graph->arcs[i][j].adj);
			}
			printf("\n");
		}
	}
	else	// ������� 
	{
		for (i=0; i<n; i++)
		{
			printf("%4c", graph->vexs[i]);
			for (j=0; j<n; j++)
			{
				if (graph->arcs[i][j].adj == INF)
					printf("%4c", CHARINF);
				else printf("%4d", graph->arcs[i][j].adj);
			}
			printf("\n");
		}
	}
	return OK;
}

status destory(mgraph *graph)
{
	int i, j;

	if (!graph) return ERROR;
	if (graph->kind == UDG || graph->kind == DG)
	{
		for (i=0; i<graph->vexnum; i++)
			for (j=0; j<graph->vexnum; j++)
			{
				graph->arcs[i][j].adj = 0;
				graph->arcs[i][j].info = NULL;
			}
	}
	else 
	{
		for (i=0; i<graph->vexnum; i++)
			for (j=0; j<graph->vexnum; j++)
			{
				graph->arcs[i][j].adj = INF;
				graph->arcs[i][j].info = NULL;
			}
	}
	graph->arcnum = 0;
	for (i=0; i<graph->vexnum; i++)
		graph->vexs[i] = '\0';
	graph->vexnum = 0;
	graph->kind = DG;
	return OK;
}

// ���ص� pos �����������
status getvex(mgraph *graph, int pos, nametype *back)
{
	if (pos > graph->vexnum || pos <= 0) return ERROR;
	*back = graph->vexs[pos-1];
	return OK;
}

// �� old �����Ƹ�Ϊ data
status putvex(mgraph *graph, nametype *old, nametype *data)
{
	int addr;

	addr = find_vex(graph, old);
	if (addr == NOT_FOUND) return ERROR;
	graph->vexs[addr] = *data;
	return OK;
}

// ����key���ĵ�һ���ڽӵ�
int firstadjvex(mgraph *graph, nametype *key)
{
	int addr;
	int i;

	if (!graph) return NOT_FOUND;
	addr = find_vex(graph, key);   // �ҵ� key ���
	if (addr == NOT_FOUND) return NOT_FOUND;

	// �����ͼ���Ҳ��� 0 �ĵ�
	if (graph->kind == DG || graph->kind == UDG)
	{
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj == 1)
				return i;
	}
	else   // ����������Ҳ���INF�ĵ�
	{
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj != INF)
				return i;
	}
	return NOT_FOUND;
}

// ����key��������data��һ���ڽӵ�
int nextadjvex(mgraph *graph, nametype *key, nametype *data)
{
	int addr;  // key ��λ��
	int pos;   // data ��λ��
	int i;

	// ���ҵ� key ���
	if (!graph) return NOT_FOUND;
	addr = find_vex(graph, key);
	if (addr == NOT_FOUND) return NOT_FOUND;

	// ���ҵ� data �ڽӵ�, �Ҳ���Ҳ����not found
	pos = find_vex(graph, data);
	if (pos == NOT_FOUND) return NOT_FOUND;

	// �����ͼ
	if (graph->kind == DG || graph->kind == UDG)
	{
		// �Ҳ��� data �ӵ�������������һЩ�ж�
		if (graph->arcs[addr][pos].adj == 0) return NOT_FOUND;
		for (i=pos+1; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj == 1)
				return i;
	}
	else 
	{
		if (graph->arcs[addr][pos].adj == INF) return NOT_FOUND;
		for (i=pos+1; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj != INF)
				return i;
	}
	return NOT_FOUND;
}

// �����½��
status insertvex(mgraph *graph, nametype *data)
{
	int i, n;

	if (!graph) return ERROR;

	// ������������û��
	if (graph->vexnum + 1 == MAX_NUM) return ERROR;

	// ���㼯����һ����������Ҳ����һ��
	graph->vexs[graph->vexnum++] = *data;

	// ��ʼ���½��
	n = graph->vexnum;
	if (graph->kind == DG || graph->kind == UDG)
	{
		for (i=0; i<n; i++)
		{
			graph->arcs[i][n-1].adj = 0;
			graph->arcs[i][n-1].info = NULL;
			graph->arcs[n-1][i].adj = 0;
			graph->arcs[n-1][i].info = NULL;
		}
	}
	else 
	{
		for (i=0; i<n; i++)
		{
			graph->arcs[i][n-1].adj = INF;
			graph->arcs[i][n-1].info = NULL;
			graph->arcs[n-1][i].adj = INF;
			graph->arcs[n-1][i].info = NULL;
		}
	}
	return OK;
}

// ɾ���������� data �ı�
status deleteallarc(mgraph *graph, nametype *data)
{
	int addr;
	int i;

	addr = find_vex(graph, data);
	if (addr == NOT_FOUND) return ERROR;

	//  data �ܵ���ȫ��Ĩ��
	// �ܵ� data ��ȫ��Ĩ��
	if (graph->kind == DG || graph->kind == UDG)
	{
		// data �ܵ���
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj == 1)
				graph->arcs[addr][i].adj = 0;

		// �ܵ� data ��
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[i][addr].adj == 1)
				graph->arcs[i][addr].adj = 0;
	}
	else 
	{
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[addr][i].adj != INF)
				graph->arcs[addr][i].adj = INF;
		for (i=0; i<graph->vexnum; i++)
			if (graph->arcs[i][addr].adj != INF)
				graph->arcs[i][addr].adj = INF;
	}
	return OK;
}

// ɾ�����
status deletevex(mgraph *graph, nametype *data)
{
	int addr;
	int i, j;

	if (!graph) return ERROR;
	
	// Ĩ�������ڽӱ�
	addr = find_vex(graph, data);
	if (addr == NOT_FOUND) return ERROR;
	deleteallarc(graph, data);

	// �ھ�����ȥ�� addr
	for (i=addr; i<graph->vexnum; i++)
	{
		graph->vexs[i] = graph->vexs[i+1];   // �ƶ��㼯
		for (j=0; j<graph->vexnum - 1; j++)	 // �ƶ��߼�
			graph->arcs[j][i].adj = graph->arcs[j][i+1].adj;
		for (j=0; j<graph->vexnum - 1; j++)
			graph->arcs[i][j].adj = graph->arcs[i+1][j].adj;
	}
	graph->vexnum--;
	return OK;
}

// �����
status insertarc(mgraph *graph, nametype *a, nametype *b, int quan)
{
	int x, y;

	if (!graph) return ERROR;
	x = find_vex(graph, a);
	y = find_vex(graph, b);
	if (x == NOT_FOUND || y == NOT_FOUND) return ERROR;

	if (graph->kind == DG || graph->kind == UDG)
	{
		graph->arcs[x][y].adj = 1;
		if (graph->kind == UDG) graph->arcs[y][x].adj = 1;
	}
	else 
	{
		graph->arcs[x][y].adj = quan;
		if (graph->kind == UDN) graph->arcs[y][x].adj = quan;
	}
	return OK;
}

// ɾ����
status deletearc(mgraph *graph, nametype *a, nametype *b)
{
	int x, y;

	if (!graph) return ERROR;
	x = find_vex(graph, a);
	y = find_vex(graph, b);
	if (x == NOT_FOUND || y == NOT_FOUND) return ERROR;

	if (graph->kind == DG || graph->kind == UDG)
	{
		graph->arcs[x][y].adj = 0;
		if (graph->kind == UDG) graph->arcs[y][x].adj = 0;
	}
	else 
	{
		graph->arcs[x][y].adj = INF;
		if (graph->kind == UDN) graph->arcs[y][x].adj = INF;
	}
	return OK;
}

// ȫ�ַ��ʱ������
unsigned short int used[MAX_NUM];

// ������� (�ݹ�)
// ����һ��ͼ���������ÿһ����ͨ��֧��
status graph_DFS(mgraph *graph, status (*visit)(nametype *data))
{
	int i;

	for (i=0; i<graph->vexnum; i++) 
		used[i] = 0;		// ��ʼ���������, 0 δ��

	for (i=0; i<graph->vexnum; i++)		// ����ÿһ����ͨ��֧
		if (!used[i]) DFS(graph, i, visit);
	return OK;
}

// ����������ͨ��֧
// �����
// ��� addr �Ϸ������з���
status DFS(mgraph *graph, int addr, status (*visit)(nametype *data))
{
	int i;
	nametype data;

	if (!graph) return ERROR;
	if (addr >= 0 && addr < graph->vexnum)
	{
		data = graph->vexs[addr];
		used[addr] = 1;		// �����ʹ��
		visit(&data);		// ����
		
		// ���� i �ĵ�һ���ڽӵ�k, ��������� k ����һ���ڽӵ�
		for (i = firstadjvex(graph, &data);
			i != NOT_FOUND;
			i = nextadjvex(graph, &data, &(graph->vexs[i])))
		{
			// ����������һ��δ���ڽӵ�
			if (!used[i]) DFS(graph, i, visit);
		}
	}
	else return ERROR;
	return OK;
}

// �ǵݹ��������, ջ
// 1. ��һ��δ���ʽ����ջ
// 2. ���ջ���գ��Ѻ�ջ���йص�Ҳѹ��ջ��ֱ��û�÷���
// 3. ��ջһ����ִ�� 2, ֱ��ջ��
status graph_DFS_s(mgraph *graph, status (*visit)(nametype *data))
{
	nametype *stack[SIZE];
	nametype *addr;
	nametype *back;
	int top = 0;
	int i;

	// ��ʼ�� used ����
	for (i=0; i<graph->vexnum; i++) used[i] = 0;
	
	// �����㼯����һ��û�з��ʵĽ��
	for (i=0; i<graph->vexnum; i++)
	{
		if (!used[i])
		{
			// i ����, ��ջ
			addr = &(graph->vexs[i]);
			visit(addr);
			used[i] = 1;
			stack[top++] = addr;   // ��ջ��¼·��

			// ���ջ����
			while (top != 0)
			{
				// һֱ����ȥ��ֱ��û·��Ϊֹ
				while (top != 0)
				{
					// �Ѻ�ջ���йصĽ��ѹ��ջ
					addr = stack[top - 1];
					// ���� addr ���ڽӵ㣬Ѱ��һ��δ���ڽӵ�
					for (i = firstadjvex(graph, addr); 
						i != NOT_FOUND; 
						i = nextadjvex(graph, addr, graph->vexs+i))
					{
						if (!used[i])
						{
							back = &(graph->vexs[i]);
							visit(back);
							used[i] = 1;
							if (top + 1 == SIZE) return ERROR;
							stack[top++] = back;  // ��ջ, ��ջ��Ϊ back
							break;
						}
					}
					// i ���ߵ���ͷ
					if (i == NOT_FOUND) break;
				}
				// �ߵ��˾�ͷ����ջ����һ��
				if (top != 0) top--;
			} // while 
		}
	} // for
	return OK;
}

// �������������
status graph_BFS(mgraph *graph, status (*visit)(nametype *data))
{
	nametype *queue[SIZE];
	int rear = 0;
	int front = 0;
	int n, i;
	nametype *back;

	if (!graph) return ERROR;
	n = graph->vexnum;
	for (i=0; i<n; i++) used[i] = 0;	// ��ʼ���������

	// �����һ��������
	for (i=0; i<n; i++)
	{
		if (!used[i])   // �������û����ӵ�
		{
			if ((rear+1)%SIZE == front) return ERROR;   // ��������
			queue[rear] = &(graph->vexs[i]);
			rear = (rear + 1) % SIZE;
			used[i] = 1;		// �����ʹ��
			while (rear != front)
			{
				// ���ӷ���
				back = queue[front];
				front = (front + 1) % SIZE;
				visit(back);

				// �� back �й�����ȫ�����
				for (i = firstadjvex(graph, back);
					i != NOT_FOUND; 
					i = nextadjvex(graph, back, graph->vexs + i))
				{
					if (!used[i]) 
					{
						if ((rear+1) % SIZE == front) return ERROR;
						queue[rear] = graph->vexs + i;
						rear = (rear + 1) % 100;
						used[i] = 1;
					}
				} // for
			} // while
		} // if
	} // for
	return OK;
}
