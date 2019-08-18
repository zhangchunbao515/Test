
// ���鼯�����Թ�
// �㷨: 
// 1. �������յ㲻��һ������ʱ, ������Ĳ���
// 2. ���ѡ��һ�����ʵı�
// 3. �����һ����µ��������ǲ���һ�����ϵ�
// 4. ������ǾͲ�ǽ, �ϲ����ߵĵ㵽һ������, ֱ�� 1 ����

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CHANGE(n) (2 * (n) - 1)
#define DOUBLE(n) (2 * (n))
#define A ' '
#define B 'X'

// �����
typedef struct 
{
	int x, y;
}point;

// �Թ��ĵ�ṹ
typedef struct
{
	char pass;		// ��ǰͨ��ͨ
	point parent;	// ˫�׽��
}node;

// �Թ��ṹ
typedef struct
{
	node p[40][78];	// Ҳ�ɶ�̬���� point *base;
	int x, y;			// ��С (x * y)
	int sx, sy;			// ��� (sx, sy)
	int ex, ey;			// �յ� (ex, ey)
}map;


// Ѱ�� (x, y) �ĸ�, ��ѹ��·��
inline point find_r(map *m, int x, int y)
{
	point r;		// ��
	point tmp, tmp2;

	r.x = x;   r.y = y;		// ���Ҹ����
	while (m->p[r.x][r.y].parent.x != r.x 
		|| m->p[r.x][r.y].parent.y != r.y)
	{
		tmp.x = m->p[r.x][r.y].parent.x;
		tmp.y = m->p[r.x][r.y].parent.y;
		r = tmp;
	}
	// �ٴ�Ҷ���ߵ���, ѹ��·��, �����÷ǵݹ�ѹ��
	// ��Ϊ�Թ�̫��, �ݹ鹤��ջ�������
	tmp.x = x;   tmp.y = y;
	while (m->p[tmp.x][tmp.y].parent.x != r.x 
		|| m->p[tmp.x][tmp.y].parent.y != r.y)
	{
		// tmp2 ����˫����Ϣ
		tmp2.x = m->p[tmp.x][tmp.y].parent.x;
		tmp2.y = m->p[tmp.x][tmp.y].parent.y;
		m->p[tmp.x][tmp.y].parent.x = r.x;
		m->p[tmp.x][tmp.y].parent.y = r.y;
		tmp = tmp2;
	}
	return r;
}

// �ϲ� (a, b), (c, d) ���ڵļ���
void merge(map *m, int a, int b, int c, int d)
{
	point r1, r2;

	r1 = find_r(m, a, b);
	r2 = find_r(m, c, d);
	if (r1.x != r2.x || r1.y != r2.y)
	{
		m->p[c][d].parent.x = r1.x;
		m->p[c][d].parent.y = r1.y;
	}	// �ϲ��� (a, b) �ļ���
}

void create(map *m)		// �����Թ��� m 
{
	int i, j;
	int x, y;
	point start, end;
	point s2, e2;		// ��¼��(a,b) (c,d) �ĸ�
	int a, b, c, d;		// ��(a,b), ��(c,d)

	// ���귭��
	m->x = CHANGE(m->x);   m->y = CHANGE(m->y);
	m->sx = DOUBLE(m->sx - 1);  m->sy = DOUBLE(m->sy - 1);	
	m->ex = DOUBLE(m->ex - 1);  m->ey = DOUBLE(m->ey - 1);
	for (i=0; i<m->x; i++)
	{
		for (j=0; j<m->y; j++)
		{
			if (!(i % 2 || j % 2)) m->p[i][j].pass = A;
			else m->p[i][j].pass = B;
			m->p[i][j].parent.x = i;
			m->p[i][j].parent.y = j;
			// ��ʼû��˫��, ��ʼ�����鼯
		}
	}
	srand(time(NULL));
	while (1)			// ��ʼ����
	{
		start = find_r(m, m->sx, m->sy);
		end = find_r(m, m->ex, m->ey);
		if (start.x == end.x && start.y == end.y) 
			break;		// �ϲ���һ��������

		do {	// �� x + y Ϊ����ʱ, �ǿɲ�ı�
			x = rand() % m->x;
			y = rand() % m->y;
		} while ((x + y) % 2 == 0);
		// ��ʱ (x, y) �Ǵ����ǽ
		if (x % 2)		// �����½��
		{
			b = d = y;   a = x + 1;   c = x - 1;
		}
		else		// �����ҽ��
		{
			a = c = x;   b = y + 1;  d = y - 1;	
		}
		s2 = find_r(m, a, b);
		e2 = find_r(m, c, d);
		// �������ǲ�ͬ�ļ���
		if (s2.x != e2.x || s2.y != e2.y) 
		{
			merge(m, a, b, c, d);	// �ϲ� (a,b), (c,d)
			m->p[x][y].pass = A;	// ��ǽ
		}
	}
	// �Ѷ�����, �����ٶ����ǽ...
	m->p[m->sx][m->sy].pass = '.';
	m->p[m->ex][m->ey].pass = '.';
}

void show(map *m)		// ����Թ�
{
	int i, j;
	for (i=0; i<79; i++) putchar('_');
	putchar('\n');
	for (i=0; i<m->x; i++)
	{
		putchar('|');
		for (j=0; j<m->y; j++)
		{
			putchar(m->p[i][j].pass);
		}
		putchar('|'); putchar('\n');
	}
	for (i=0; i<79; i++) putchar('-');
}

int main(void)
{
	map m;		// �Թ���ͼ

	printf("�������ͼ��С: ");		// �Թ���� (20 * 39)
	scanf("%d %d", &m.x, &m.y);
	printf("�������: ");
	scanf("%d %d", &m.sx, &m.sy);
	printf("�����յ�: ");
	scanf("%d %d", &m.ex, &m.ey);
	if (m.x < 2 || m.y< 2 || m.x > 20 || m.y > 39) return 0;

	create(&m);		// �����Թ�
	show(&m);		// ���
	printf("\n");

	return 0;
}