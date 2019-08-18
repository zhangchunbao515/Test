
/*			������ ���� ���� 1175 ��
���������ж��顣ÿ�����ݵĵ�һ��������������n,m(0<n<=1000,0<m<1000)��
�ֱ��ʾ���̵��������������ڽ�������n���У�ÿ����m���Ǹ������������̵ķ���ֲ���
0��ʾ���λ��û�����ӣ���������ʾ���ӵ����͡���������һ����һ��������q(0<q<50)��
��ʾ������q��ѯ�ʡ��ڽ�������q���ÿ�����ĸ�������x1,y1,x2,y2,
��ʾѯ�ʵ�x1��y1�е��������x2��y2�е������ܲ�����ȥ��n=0,m=0ʱ�����������
ע�⣺ѯ��֮�����Ⱥ��ϵ��������Ե�ǰ״̬�ģ�

Sample Input
3 4
1 2 3 4
0 0 0 0
4 3 2 1
4
1 1 3 4
1 1 2 4
1 1 3 3
2 1 2 4
3 4
0 1 4 3
0 2 4 1
0 0 0 0
2
1 1 2 4
1 3 2 3
0 0

Sample Output
YES
NO
NO
NO
NO
YES
*/

#include <stdio.h>
#include <math.h>
#include <queue>

int n, m;
int map[1003][1003];
int used[1003][1003];

int dir[4][2] = {0, 1, 0, -1, -1, 0, 1, 0};

typedef struct		// ���ѽ��
{
	short int x, y;
	short int prex, prey;	// ��¼ǰ�����
	short int times;		// ��¼�������
}node;

inline int ok(node *cur)		// Խ����
{
	if (cur->x < 0 || cur->x >= n 
		|| cur->y < 0 || cur->y >= m) return 0;
	return 1;
}

// �������
inline double dist(int x1, int y1, int x2, int y2)
{
	return sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

int BFS(int x1, int y1, int x2, int y2)
{
	std::queue<node> q;
	int key1 = map[x1][y1];
	int i, j;
	node tmp, cur;
	double d;

	// ͼ����ͬ, ������ȥ
	if (key1 == 0 || key1 != map[x2][y2]) return 0;
	for (i=0; i<n; i++)			// ��ʼ�����ʱ��
		for (j=0; j<m; j++)
			used[i][j] = map[i][j];
	tmp.prex = tmp.x = x1;
	tmp.prey = tmp.y = y1;
	tmp.times = 0;
	q.push(tmp);
	used[x1][y1] = 1;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (i=0; i<4; i++)		// �ֱ�ɨ����0 ��1 ��2 ��3
		{
			cur.x = tmp.x + dir[i][0];
			cur.y = tmp.y + dir[i][1];
			if (ok(&cur))		// Խ����
			{
				// ����ǰ������뵱ǰ���ľ���
				d = dist(cur.x, cur.y, tmp.prex, tmp.prey);
				// �й���, ������ľ����Ǹ���2, �� 1.414
				if (d > 1.5 || d < 1.3)
					cur.times = tmp.times;
				else 
					cur.times = tmp.times + 1;
				// �����������������
				if (cur.times <= 2)
				{
					cur.prex = tmp.x;
					cur.prey = tmp.y;
					if (cur.x == x2 && cur.y == y2) return 1;
					// û�з��ʹ�, ���ܼ������
					if (!used[cur.x][cur.y])
					{
						q.push(cur);
						used[cur.x][cur.y] = 1;
					}
				}
			}
		}
	}
	return 0;
}

int main(void)
{
	int i, j;
	int q;
	int x1, y1, x2, y2;

	while (scanf("%d %d", &n, &m), n || m)
	{
		for (i=0; i<n; i++)
			for (j=0; j<m; j++)
				scanf("%d", &(map[i][j]));
		scanf("%d", &q);
		for (i=0; i<q; i++)
		{
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (BFS(x1-1, y1-1, x2-1, y2-1)) 
				printf("YES\n");
			else 
				printf("NO\n");
		}
	}
	return 0;
}