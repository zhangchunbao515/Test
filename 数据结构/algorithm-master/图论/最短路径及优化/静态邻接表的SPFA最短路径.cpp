
#include <stdio.h>
#include <queue>

#define NUM 60
#define INF 0xFFFFFF

typedef struct
{
	int i;		// �ɴ���
	int v;		// Ȩֵ
}node;

int n;
node m[NUM][NUM];		// ��̬�ڽӱ�
int top[NUM];
// m[k][0] 0 �ŵ�Ԫ��ʾ k ����ĳ�����
// m[a][..].i = c  ��ʾ a �� b ��Ȩֵ�� c
// m[a][..].v = c  ��ʾ a �� b ��Ȩֵ�� v

int SPFA(int s, int t, int *pre, int *value)
{
	std::queue<int> q;
	int used[NUM];
	int dis[NUM];		// ��̾���
	int i, tmp;
	int a, b, v;
	int count[NUM];		// ��Ӵ���
	// n ������, ����һ������ʣ�µ� n-1 ���������� n-1 ����
	// ����������� n-1 ��, ��������� n-1 ˵�����ڸ���
	// ÿ��һ�θ���, dis[] �͸�С, ���������ѭ��

	for (i=0; i<n; i++)
	{
		dis[i] = INF;
		used[i] = 0;
		count[i] = 0;
	}
	dis[s] = 0;
	q.push(s);
	used[s] = 1;
	count[s]++;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (i=0; i<top[tmp]; i++)
		{
			a = tmp;
			b = m[tmp][i].i;
			v = m[tmp][i].v;
			if (dis[a] + v < dis[b])
			{
				dis[b] = dis[a] + v;
				pre[b] = a;
				// ������ɳڵĽ�� b, û���ڶ�����
				// ���, ��Ϊ�� b ȥ�ɳ����ڽӵ�
				if (!used[b])
				{
					q.push(b);
					used[b] = 1;
					count[b]++;
					if (count[b] == n) return 0;
				}
			}
		}
		used[tmp] = 0;
	}
	*value = dis[t];
	return 1;
}

int main(void)
{
	int i;
	int a, b, c;		// (a, b) = c
	int pre[NUM];		// ��¼ǰ��

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		top[i] = 0;
		pre[i] = -1;
	}
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		m[a][top[a]].i = b;
		m[a][top[a]].v = c;
		top[a]++;
	}
	printf("�������, �յ�: ");
	scanf("%d %d", &a, &b);
	if (SPFA(a, b, pre, &c))
	{
		printf("\n���·����: %d\n·��: ", c);
		c = b;
		while (c != -1)
		{
			printf("%d <- ", c);
			c = pre[c];
		}
		printf("���\n");
	}
	else printf("\n���ڸ���!\n");

	return 0;
}
/*   �����������, һ���н�, һ���и���
5
0 1 6
0 2 7
1 2 8
1 3 5
3 1 -2
1 4 -4
2 3 -3
2 4 9
4 3 7
0 0 0
0 4

4
0 1 1
1 2 -2
2 3 -3
3 2 -4
2 4 1
0 0 0
0 2
*/