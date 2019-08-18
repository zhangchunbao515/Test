
// ���������֮ dinic �㷨
// EK �㷨���ҹ�������·, ��������
// �� dinic �ȹ��Ѹ߶ȱ��, ��������������·
// ���ҵ������� height[a] == height[b] + 1
// ��ͱ�֤����ֻ��Ӹ������ƽ�

#include <stdio.h>
#include <queue>

#define NUM 60
#define INF 0xFFFFFF

int m[NUM][NUM];		// �ڽӾ���
int n;
int h[NUM];			// �߶Ⱥ���
int used[NUM];

void BFS(int s, int t)		// ���Ѽ�����߶�
{
	int i, tmp;
	std::queue<int> q;

	for (i=0; i<n; i++) used[i] = 0;
	h[t] = 0;		// ������
	used[t] = 1;
	q.push(t);
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (i=0; i<n; i++)
		{
			// �ӻ��������
			if (!used[i] && m[i][tmp] != 0)
			{
				h[i] = h[tmp] + 1;
				used[i] = 1;
				q.push(i);
			}
		}
	}
}

// �� cur ��ʼ��, �ѵ� t ֹͣ, �ƽ��� v
// ���ر��ε��ƽ��� min{v, cur->t}
// �Ҳ�������·���� 0
int DFS(int cur, int t, int v)
{
	int i;
	int f;		// ����ƽ���

	if (cur == t) return v;
	for (i=0; i<n; i++)
	{							// �˴� h[cur] > h[i] ���ص�
		if (!used[i] && m[cur][i] != 0 && h[cur] == h[i] + 1)
		{
			used[i] = 1;
			f = v > m[cur][i] ? m[cur][i] : v;
			f = DFS(i, t, f);		// �ƽ�
			if (f == 0) break;		// û����·��
			m[cur][i] -= f;			// ����ʱ, ��¼
			m[i][cur] += f;			// �����¼

			return f;
		}
	}
	return 0;
}

int dinic(int s, int t)
{
	int maxflow = 0;
	int tmp, i;

	while (1)
	{
		BFS(s, t);			// ���Ѹ߶ȱ��, ÿ�ζ�Ҫ���¼���߶�
		for (i=0; i<n; i++) used[i] = 0;
		tmp = DFS(s, t, INF);	// ���ѳ������� INF ������
		if (tmp) maxflow += tmp;
		else break;
	}
	return maxflow;
}

int main(void)
{
	int i, j, v;

	printf("���붥��������߼�: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	while (1)
	{
		scanf("%d %d %d", &i, &j, &v);
		if (!(i || j || v)) break;
		m[i][j] = v;
	}
	printf("����Դ����: ");
	scanf("%d %d", &i, &j);
	printf("\n�����: %d\n", dinic(i, j));

	return 0;
}