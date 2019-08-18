
// ��С���õ������
// ÿ���߲���������, ���з���(Ȩ)
// �� s �� t �������, ͬʱ��Ҫ������С

// ��ͨ��������ù���, ����, dijskral �ȵȲ�������·
// ������Ҫ�������С, ÿ��Ҫ��һ��������С������·
// �� dijskral ���� SPFA ���ҷ�����С������·
// ���� n ��̰�ĺ�, ֱ���Ҳ�������·��
// ��ʱ��ǰ������, ������ͨ���ı߼�����, ������С������

#include <stdio.h>
#include <queue>

#define NUM 50		// ��󶥵���
#define INF 0xFFFFFF

typedef struct
{
	int v;		// ����
	int c;		// ���� cost
}matrix;	// �ڽӾ���

// SPFA ���ҷ�����С��·��, ���費���ڸ���
int SPFA(matrix (*e)[NUM], int n, int *pre, int s, int t)
{
	std::queue<int> q;
	int used[NUM];		// �ڲ��ڶ�����
	int dis[NUM];		// ��̾���
	int i, tmp;

	for (i=0; i<n; i++) {
		pre[i] = -1;
		used[i] = 0;
		dis[i] = INF;
	}
	dis[s] = 0;
	q.push(s);
	used[s] = 1;
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		for (i=0; i<n; i++)			// �ɳ��ڽӵ�
		{
			// SPFA �����޸�, ���� dis[tmp] + e[tmp][i] < dis[i]
			// ��Ҫ�������� e[tmp][i] �е�������Ϊ 0, ����·����
			// ��Ϊ��� tmp -> i ������ 0 ��
			// ���ɳ� tmp -> i �ö�, �Ѿ�û����
			// ����ֻ���������·����һ��·���� 0, ������Ϊ 0
			if (e[tmp][i].v != 0 
				&& dis[tmp] + e[tmp][i].c < dis[i])
			{
				dis[i] = dis[tmp] + e[tmp][i].c;
				pre[i] = tmp;
				if (!used[i])		// ���ɳڵĵ����һ��
				{
					q.push(i);
					used[i] = 1;
				}
			}
		}
	}
	if (pre[t] != -1) return 1;
	else return 0;
}

// ����С����, max_f ���������
// �㷨����:
// �� SPFA ����һ��������С������·
// ������·���²�������, ��ǰ����
// ֱ���Ҳ�������·Ϊֹ
// �ڵ�ǰ������ͳ����С����, �����
int min_cost(matrix (*m)[NUM], int n, int s, int t, int *max_f)
{
	matrix e[NUM][NUM];		// ��������
	matrix c[NUM][NUM];		// ��ǰ����
	int pre[NUM];
	int cur;
	int mincost = 0;
	int min;
	int i, j;

	for (i=0; i<n; i++) {		// ��ʼ��
		for (j=0; j<n; j++) {
			e[i][j] = m[i][j];		// ���ƻ� m ����
			c[i][j].c = m[i][j].c;
			c[i][j].v = 0;
		}
	}
	while (SPFA(e, n, pre, s, t))	// ������ҵ�����·
	{
		min = INF;
		cur = t;
		while (pre[cur] != -1)		// ����С������
		{
			if (e[pre[cur]][cur].v < min)
				min = e[pre[cur]][cur].v;
			cur = pre[cur];
		}
		cur = t;
		while (pre[cur] != -1)		// ��������
		{
			i = pre[cur];
			e[i][cur].v -= min;		// ���²�������
			e[cur][i].v += min;		// ��¼��������
			c[i][cur].v += min;		// ���µ�ǰ����
			c[cur][i].v -= min;
			cur = pre[cur];
		}
	}
	// �ڵ�ǰ������ͳ����С����, �����
	*max_f = 0;
	for (i=0; i<n; i++) 
	{
		if (c[i][t].v != 0) (*max_f) += c[i][t].v;
		for (j=0; j<n; j++)
		{
			if (c[i][j].v > 0) mincost += c[i][j].c;
		}
	}
	return mincost;
}

int main(void)
{
	int a, b, v, c;		// (a, b) ���� v, ���� c
	int n;
	int i, j;
	int max_f;
	matrix m[NUM][NUM];		// �ڽӾ���

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			m[i][j].v = 0;		// ��ʼ����Ϊ 0
			m[i][j].c = INF;	// �������޴�
		}
	}
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d %d %d", &a, &b, &v, &c);
		if (!(a || b || v || c)) break;
		m[a][b].v = v;
		m[a][b].c = c;
	}
	printf("����Դ��, ���: ");
	scanf("%d %d", &a, &b);
	printf("\n��С����: %d\n", min_cost(m, n, a, b, &max_f));
	printf("�����: %d\n", max_f);

	return 0;
}
