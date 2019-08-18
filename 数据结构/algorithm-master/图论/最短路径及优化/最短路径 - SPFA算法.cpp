
// SPFA �㷨
// �� bellman-Ford �㷨�ϸĽ�, �ö����Ż�, �����˲���Ҫ���ɳ�
// SPFA �㷨�͹�������, �����ɳڵĽ���ڶ�����, �����㲻�ڶ�����
// ��һ���Ľ�, ʹ�� SPFA �㷨�ܹ�������, ��¼ÿ�������������
// ��������� n-1 ��, ��ô�ʹ��ڸ�����
// ��Ϊ n ������, ����һ���㵽����ĵ������� n-1 ����
// Ҳ�������ֻ���ɳ� n-1 ��, ������ n-1 ��

#include <stdio.h>
#include <queue>

#define NUM  50		// �������
#define INF  0xFFFFFf

// ��ʼ��, ������
// �Ӷ�����ȡ��һ�����, �ɳ��ڽӵ�, ���ɳ۵ĵ����
int SPFA(int(*m)[NUM], int n, int start, int end, int *pre, int *r)
{										// pre ����ǰ��, r �������·��
	int used[NUM];		// ��־�ڲ��ڶ�����
	int dis[NUM];		// ��̾���
	int count[NUM];		// ͳ�ƽ����Ӵ���, �жϸ���
	std::queue<int> q;
	int i, tmp;
	
	for (i=0; i<n; i++)
	{
		used[i] = 0;
		dis[i] = INF;
		count[i] = 0;
	}
	dis[start] = 0;
	q.push(start);
	count[start]++;
	used[start] = 1;
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		for (i=0; i<n; i++)		// ���� tmp �ڽӵ�
		{
			if (dis[tmp] + m[tmp][i] < dis[i])
			{
				dis[i] = dis[tmp] + m[tmp][i];
				pre[i] = tmp;
				if (!used[i])		// ������ڶ�����, �����
				{
					count[i]++;		// �жϸ���
					if (count[i] >= n) return 0;
					used[i] = 1;
					q.push(i);
				}
			}
		}
		used[tmp] = 0;		// ��ʾ���ڶ�������
	}
	*r = dis[end];
	return 1;
}

int main(void)
{
	int n;
	int a, b, c;		// (a, b) = c
	int m[NUM][NUM];
	int pre[NUM];		// ��¼ǰ��

	printf("���붥�����: ");
	scanf("%d", &n);
	for (a=0; a<n; a++) {
		for (b=0; b<n; b++) m[a][b] = INF;
		pre[a] = -1;
	}
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		m[a][b] = c;
	}
	printf("�������, �յ�: ");
	scanf("%d %d", &a, &b);
	if (SPFA(m, n, a, b, pre, &c))
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