
// �ǵݹ����������Թ�
// �㷨: �����ѵ�·����Ϊ�Թ���ͨ·

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CHANGE(n) (2 * (n) - 1)
#define A ' '
#define B 'X'
#define NO -1

// �����
typedef struct 
{
	int x, y;
}point;

// �Թ��ṹ
typedef struct
{
	char p[41][79];	// Ҳ�ɶ�̬���� point *base;
	int x, y;			// ��С (x * y)
//	int sx, sy;			// ��� (sx, sy)
//	int ex, ey;			// �յ� (ex, ey)
}map;

int used[41][79];	// ���ʱ������

inline int ok(map *m, int x, int y)
{
	if (x > 0 
		&& x <= m->x 
		&& y > 0 
		&& y <= m->y 
		&& !used[x][y])
		return 1;
	else return 0;
}

void show(map *m)		// ����Թ�
{
	int i, j;
	for (i=0; i<79; i++) putchar('_');
	putchar('\n');
	for (i=0; i<=m->x+1; i++)
	{
		putchar('|');
		for (j=0; j<=m->y+1; j++)
		{
			putchar(m->p[i][j]);
		}
		putchar('|'); putchar('\n');
	}
	for (i=0; i<79; i++) putchar('-');
}

void create(map *m)		// �����Թ��� m 
{
	int i, j;
	point tmp;
	point stack[10000];
	int top = 0;
	int dir[4][2] = {0,-1, 0,+1, -1,0, +1,0};
	point re[4];		// ��¼��������
	int flag, r;
	int tx, ty;

	// ���귭��
	m->x = CHANGE(m->x);   m->y = CHANGE(m->y);
	m->x++;   m->y++;
	for (i=0; i<=m->x; i++)		// ��ʼ����ͼ
	{
		for (j=0; j<=m->y; j++)
		{
			m->p[i][j] = B;
			used[i][j] = 0;
		}
	}
	m->x--;   m->y--;
	// �����ջ
	stack[top].x = 1;   stack[top].y = 1;
	top++;
	used[1][1] = 1;		// ��Ƿ���
	srand(time(NULL));
	while (top != 0)
	{
		tmp = stack[top-1];		// ���ջ��
		flag = 0;
		for (i=0; i<4; i++)		// ���������ܲ�����
		{
			tx = tmp.x+dir[i][0];
			ty = tmp.y+dir[i][1];
			if (ok(m, tx, ty)		// ��֦����
				&& (( !used[tx+1][ty] && !used[tx-1][ty] 
				&& (used[tx][ty+1]!=1 || used[tx][ty-1]!=1)) 
				|| (!used[tx][ty+1] && !used[tx][ty-1])) 
				&& (used[tx+1][ty]!=1 || used[tx-1][ty]!=1))
			{
				// ��¼�����ߵķ���
				re[i].x = tx;
				re[i].y = ty;
				flag = 1;
			}
			else re[i].x = re[i].y = NO;
		}
		if (!flag) top--;		// ���ܲ�������
		else 
		{
			while (1)		// �������һ������
			{
				r = rand() % 4;
				if (re[r].x != NO) break;
			}
			m->p[re[r].x][re[r].y] = A;		// ��ͨ, ��¼
			stack[top].x = re[r].x;   stack[top].y = re[r].y;
			top++;
			used[re[r].x][re[r].y] = 1;

//			show(m);			// ��δ���ɹ۲��Թ����ɹ���
//			system("cls");
		}
	}
	m->p[1][1] = '.';			// ������, �յ�
	m->p[m->x][m->y] = '.';
}


int main(void)
{
	map m;		// �Թ���ͼ

	printf("�������ͼ��С: ");		// �Թ���� (20 * 39)
	scanf("%d %d", &m.x, &m.y);
	if (m.x < 2 || m.y < 2 || m.x > 20 || m.y > 39) return 0;

	create(&m);		// �����Թ�
	show(&m);		// ���
	printf("\n");

	return 0;
}