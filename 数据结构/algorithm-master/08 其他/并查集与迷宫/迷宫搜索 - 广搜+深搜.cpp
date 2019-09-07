// �Թ�����, ���ѣ�����
// Ҫ�㣬���ڷ��ʹ��ĵ�Ҫ���б�ǣ���Ȼ���ظ����ʵ�
// �ļ��������ϸ���㷨����

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 21
#define USED 2		// ������·��
#define INF -1		// -1 û��ǰ�����

// �����
typedef struct
{
	short int x;
	short int y;
	short int quan;		// �õ��Ȩֵ
	short int used;		// ʹ�ñ��
}point;

// ·����¼ջ
typedef struct
{
	point base[200];
	int top;
}stack;

// �ĸ�������������         ��         ��        ��
point dir[4] = {-1,0,0,0,  0,1,0,0,  1,0,0,0,  0,-1,0,0};

// ����Թ�
void showmap(point map[MAXSIZE][MAXSIZE], int m, int n)
{
	int i, j;
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			if (map[i][j].quan == 1) printf("%3c", '.');
			else if (map[i][j].quan == 0) printf("%3c", '*');
			else printf("%3c", 'O');
		printf("\n");
	}
}

// ��ʼ�����ʱ��
void clear(point map[MAXSIZE][MAXSIZE], int m, int n)
{
	int i, j;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			map[i][j].used = 0;
}

// ��ʼ����ͼ��Ȩֵ
void init_quan(point map[MAXSIZE][MAXSIZE], int m, int n)
{
	int i, j;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			if (map[i][j].quan == USED) 
				map[i][j].quan = 1;
}

// �����Թ�
void input(point map[MAXSIZE][MAXSIZE], int m, int n)
{
	int i, j;
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			scanf("%1d", &map[i][j].quan);
		scanf("%c");	// ����һ���س���
	}
	// ��ʼ��ʹ�ñ��
	clear(map, m, n);
}

// ���Ϸ�
inline int check(int m, int n)
{
	if (m <= 0 
		|| m > MAXSIZE - 1 
		|| n <= 0 
		|| n > MAXSIZE - 1)
	{
		printf("�����Թ�����ܳ��� 20*20 !\n");
		return 0;
	}
	else return 1;
}

// �жϵ�ǰ��ɲ�������
int find(point map[MAXSIZE][MAXSIZE], 
		 int cur_x, int cur_y, int m, int n)
{
	if (cur_x >= 0 
		&& cur_y >= 0 
		&& cur_x< m 
		&& cur_y < n 
		&& map[cur_x][cur_y].quan
		&& !map[cur_x][cur_y].used) 
		return 1;
	return 0;
}


// --------------------�����㷨Ҫ��------------------------
// 1. ��һ����ά���飬��¼·������ǰ���Ǵ��ĸ��������
// 2. ���ڷ��ʹ��Ľ��Ҫ���б�ǣ���ֹ�ظ����ʣ�
// BFS(��ͼ��m��, n��, ��㣬�յ�);
int BFS(point map[MAXSIZE][MAXSIZE], 
		 int m, 
		 int n,
		 point *s, 
		 point *e,
		 point p[MAXSIZE][MAXSIZE])
{
	point queue[100];
	int rear = 0;
	int front = 0;
	int i;
	point back;		// �������ӵĵ�
	point in;		// ������ӵĵ�
	int flag = 0;

	// ��շ��ʱ��
	clear(map, m, n);
	// ������
	queue[rear] = *s;
	rear = (rear + 1) % 100;
	map[s->x][s->y].used = 1;	// ���ʹ����
	// ��¼���·��, INF ��ʾû��ǰ������
	p[s->x][s->y].x = INF;
	p[s->x][s->y].y = INF;

	while (rear != front)
	{
		back = queue[front];		// ����
		front = (front + 1) % 100;
		// �жϵ��յ�û��
		if (back.x == e->x && back.y == e->y)
		{
			flag = 1;
			break;
		}
		// ���û���������ڵĵ����,ͬʱ��¼·��
		// ���ĸ���������
		for (i=0; i<4; i++)
		{
			in.x = back.x + dir[i].x;
			in.y = back.y + dir[i].y;

			if (find(map, in.x, in.y, m, n))
			{
				queue[rear] = in;	// ���
				rear = (rear + 1) % 100;
				map[in.x][in.y].used = 1;	// ���ʹ���ˣ���ֹ�ظ�����
				// ��¼·������¼��һ���������
				// in ���� back ��
				p[in.x][in.y].x = back.x;
				p[in.x][in.y].y = back.y;
			}
		}
	}
	return flag;
}

// --------------------�����㷨Ҫ��------------------------
// ����㿪ʼ��ջ����ջ��Ҫ��Ƿ���
// ����˳ʱ�뷽�����ķ�����
// �ĸ������߲�ͨ��ʱ�򣬾ͳ�ջһ��������̽��
// ֱ��ջ�գ������ҵ�������
// DFS(map, m, n, &start, &end, &out))
int DFS(point map[MAXSIZE][MAXSIZE], 
		 int m, 
		 int n,
		 point *s, 
		 point *e,
		 stack *p)
{
	int flag = 0;
	int found, i;
	point back;
	point in;
	
	// ��ʼ�����ʱ��
	clear(map, m, n);
	p->top = 0;
	p->base[p->top++] = *s;	// �����ջ
	s->used = 1;			// ���ʹ��

	// ѭ���е�����break��һ�����ҵ������ˣ�һ����ջ����
	while (1)
	{
		// ��ջ��Ԫ��������
		back = p->base[p->top - 1];

		// ���ж��ǲ��ǳ��ڣ�������Ǽ�����ջ
		if (back.x == e->x && back.y == e->y)
		{
			flag = 1;
			break;
		}
		// ���ǳ��ڣ����ķ�����һ����ͨ��·��
		for (i=0; i<4; i++)
		{
			found = 0;	// ���û���ҵ�ͨ·
			in.x = back.x + dir[i].x;
			in.y = back.y + dir[i].y;
			// �������ͨ,
			if (find(map, in.x, in.y, m, n))
			{
				found = 1;
				p->base[p->top++] = in;	// ��ջ
				map[in.x][in.y].used = 1;
				// һ��Ҫ���ʹ���ˣ���ֹ�ظ�����
				break;
			}
		}
		// ��ջ�ͽ�������
		// ��������������ͳ�ջһ��
		if (!found) p->top--;
		if (p->top <= 0) break;
	}
	return flag;
}


// m * n �Թ����뷽��
// m n
// ����ȥ m �� n �е� 0 1
// 0 ��ͨ, 1 ͨ
// �Թ����ֵ 20 * 20

int main(void)
{
	point map[MAXSIZE][MAXSIZE];
	int n, m;
	point start;
	point end;
	point tmp;
	int x, y, i;
	
	printf("�Թ�����");
	do {
		printf("\n�������Թ�:");
		scanf("%d %d", &m, &n);
	} while (!check(m, n));

	input(map, m, n);
	system("cls");
	printf("�Թ����£�\n");
	showmap(map, m, n);
	printf("������㣺");
	scanf("%d %d", &start.x, &start.y);
	printf("�����յ㣺");
	scanf("%d %d", &end.x, &end.y);
	// �����д�����,�뱣֤����ȷ
	
	// �������, path ��¼·��
	point path[MAXSIZE][MAXSIZE];
	stack out;
	out.top = 0;

	// ��ʼ����...
	if (BFS(map, m, n, &start, &end, path))
	{
		printf("\n���ѣ��ҵ����ڣ�\n");
		init_quan(map, m, n);	// ��ʼ����ͼ��Ȩ
		tmp = end;
		// �� path ����ȡ·��, ���յ�������ѣ�������ջ����
		while (tmp.x != INF || tmp.y != INF)
		{
			out.base[out.top++] = tmp;	// ��ջ
			// ��ͼ��Ҳ���, USED �Ǳؾ�֮·
			map[tmp.x][tmp.y].quan = USED;
			// (x, y) ��ǰ�����
			x = path[tmp.x][tmp.y].x;
			y = path[tmp.x][tmp.y].y;
			tmp.x = x;     tmp.y = y;
		}
		printf("��ڣ�");
		while (out.top)
		{
			x = out.base[out.top - 1].x;
			y = out.base[out.top - 1].y;
			out.top--;
			printf(" -> (%d, %d)", x, y);
		}
		printf(" -> ����\n·������ͼ��\n");
		showmap(map, m, n);
	}
	else printf("���ѣ��Ҳ�������!\n");

	printf("\n���»س�������ʼ����...");
	getchar();   getchar();

	// ��ʼ����...
	if (DFS(map, m, n, &start, &end, &out))
	{
		printf("\n���ѣ��ҵ����ڣ�\n��ڣ�");
		init_quan(map, m, n);	// ��ʼ����ͼ��Ȩ
		// ��ջ����ȡ·��
		// ��ջ�׿�ʼ��ȡ��˵��ջ��������˵��˫�˶���
		for (i=0; i<out.top; i++)
		{
			x = out.base[i].x;
			y = out.base[i].y;
			printf(" -> (%d, %d)", x, y);
			map[x][y].quan = USED;
		}
		printf(" -> ����\n·������ͼ\n");
		showmap(map, m, n);
	}
	else printf("���ѣ��Ҳ�������!\n");

	return 0;
}

/*
���ѣ�
���������ӣ������ʹ��
������йص���û���ʹ���Ҳ��ӣ��ǵ�Ҫ���ʹ��
ֱ���ҵ����ڣ����߶��п��ˣ���������

���Ѽ�¼·����
��һ��point��Ķ�ά���飬����¼ǰ�����
���Ǽ�¼��ǰ���Ǵ��ĸ�����ʹ�����
Ȼ��Ϳ��Դ��յ㣬�ҵ���㣬�����

���ѣ�
�����ջ�������ʹ��
��һ����ջ������йصĽ��
����������û��ʹ�ù��ģ���ջ���ǵñ��ʹ��
����Ҳ����ʹ�ջ�ﵯ��һ������Ϊ�������·������
ֱ��ջ�գ������ҵ��յ���, ��������
ջ���Ԫ�ؾ���·���ˣ�

�Ƚϣ������ѳ�����·������̵ģ�
*/
