
// ���������, ����·�㷨, Ford-Fulkerson �㷨

#include <stdio.h>
#include <string.h>
#include <queue>

#define NUM 30		// ��󶥵���

// �㷨����:
// �ڲ���������, ͨ�������ҵ�һ������·
// �ҳ�����·�ϵ���СȨֵ�ı�
// ���²�������
// ֱ���Ҳ�������·Ϊֹ
// ͳ�Ƶ�ǰ�����л�����
int maxflow(int (*m)[NUM], int n, const int s, const int e)
{
	int r[NUM][NUM];		// ��������
	int max_flow = 0;
	int i, j;
	int cur, min;
	std::queue<int> q;		// ���Ѷ���
	char used[NUM];
	int pre[NUM];

	for (i=0; i<n; i++)			// ��ʼ��
		for (j=0; j<n; j++)
			r[i][j] = m[i][j];		// r ��Ϊ�˲��ƻ�main�� m ������
	while (1)		// ���ϲ�������·
	{
		// ����һ������·, �Ҳ����� break
		memset(used, 0, sizeof(used));
		memset(pre, -1, sizeof(pre));
		q.push(s);
		used[s] = 1;
		cur = s;
		while (!q.empty())		// �� r �в���һ������·
		{
			cur = q.front();   q.pop();
			if (cur == e) break;
			for (i=0; i<n; i++)
			{
				if (!used[i] && r[cur][i] != 0)
				{
					used[i] = 1;
					q.push(i);
					pre[i] = cur;
					if (i == e) break;		// �ҵ���
				}
			}
		}
		if (pre[e] == -1) break;		// û������·��
		// ����ǰ����Ϣ pre �Ӻ���ǰ����СȨֵ
		cur = e;
		min = 0XFFFFFF;
		while (pre[cur] != -1)
		{
			if (r[ pre[cur] ][cur] < min)
				min = r[ pre[cur] ][cur];
			cur = pre[cur];
		}
		// ��������, ��ǰ�����м��� min, �����ǰ
		// ������� min, ָ����������, �п��ܱ�����������
		cur = e;
		while (pre[cur] != -1)
		{
			r[ pre[cur] ][cur] -= min;		// ��������
			r[cur][ pre[cur] ] += min;
			cur = pre[cur];
		}
	}
	// ���ݲ����������Ϣͳ������, ��� i->e ��·, ͳ�� e ����i������
	for (i=0; i<n; i++)
		if (m[i][e] != 0) max_flow += r[e][i];
	return max_flow;
}

int main(void)
{
	int n;
	int matrix[NUM][NUM];		// �ڽӾ���
	int a, b, c;

	memset(matrix, 0, sizeof(matrix));
	printf("������һ����Ȩ����ͼ: ");
	printf("�������: ");
	scanf("%d", &n);
	printf("�߼�: ");
	while (1)
	{
		scanf("%d %d %d", &a, &b, &c);
		if (!(a || b || c)) break;
		matrix[a][b] = c;
	}
	printf("����Դ��ͻ��: ");
	scanf("%d %d", &a, &b);
	printf("\n�����: %d\n", maxflow(matrix, n, a, b));
	return 0;
}
