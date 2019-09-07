
// Bellman-ford �㷨, ������ڸ��ߵ�ͼ

#include <stdio.h>

#define NUM  50		// �������
#define NUM2 200	// ������
#define INF  0xFFFFFf

struct		// �߼�����, (s, t) = v;
{
	int s;
	int t;
	int v;
}node[NUM2];
int top = 0;

// �ѱ߼��еı�, ���� n-1 ���ɳ�, ��ôÿ�����ɳ��� n-1 ��
// n ������, ����һ���㵽����ĵ�, ������ n-1 ����
// ��������ɳ��Ǿ�˵�����ڸ�Ȩ�ı���
int bellman(int n, int start, int end, int *pre, int *r)
{							// pre ����ǰ����Ϣ, r ���ؽ��
	int dis[NUM];
	int i, j;
	int s, t, v;

	for (i=0; i<top; i++) dis[i] = INF;
	dis[start] = 0;
	
	for (i=1; i<n; i++)		// ÿ�����ɳ� n-1 ��
	{
		for (j=0; j<top; j++)	// �����߼�
		{
			s = node[j].s;
			t = node[j].t;
			v = node[j].v;
			if (dis[s] + v < dis[t])
			{
				dis[t] = dis[s] + v;
				pre[t] = s;			// ��¼ǰ��
			}
			// ��� dis[s] + cost[s..t] < dis[t] ����� dis[t]
		}
	}
	for (j=0; j<top; j++)
		if (dis[node[j].s] + node[j].v < dis[node[j].t])
			return 0;
	*r = dis[end];
	return 1;
}

int main(void)
{
	int n;
	int a, b, c;		// (a, b) = c
	int pre[NUM];

	printf("���붥�����: ");
	scanf("%d", &n);
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		pre[top] = -1;
		node[top].s = a;
		node[top].t = b;
		node[top++].v = c;
	}
	printf("�������, �յ�: ");
	scanf("%d %d", &a, &b);
	if (bellman(n, a, b, pre, &c))
	{
		printf("\n���·����: %d\n", c);
		printf("·��: ");
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