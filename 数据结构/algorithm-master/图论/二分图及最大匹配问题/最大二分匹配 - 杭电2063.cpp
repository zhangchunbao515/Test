
// ���� 2063 �� - ��ɽ��

#include <stdio.h>

int k, m, n;		// k ������, m ��Ů��, n ������
int map[510][510];	// �ڽӾ����¼��
int link[510];		// link[Ů��], ��ʾƥ�������
int used[510];		// �������ʱ��

// Ѱ������·
int find_path(int g)
{
	int i;

	for (i=0; i<=n; i++)	// ��������
	{
		// ���Ů�� g ������ i ��·
		if (!used[i] && map[g][i])
		{
			used[i] = 1;
			if (link[i] == -1 || find_path(link[i]))
			{
				link[i] = g;
				return 1;
			}
		}
	}
	return 0;
}

int main(void)
{
	int i, j;
	int g, b;
	int count;

	while (scanf("%d", &k) != EOF && k)
	{
		scanf("%d %d", &m, &n);
		for (i=0; i<=m; i++)
			for (j=0; j<=n; j++) map[i][j] = 0;
		while (k--)
		{
			scanf("%d %d", &g, &b);
			map[g][b] = 1;
			// ��Ů�����ϳ���, ƥ������
			// ���Բ��ü�¼ map[b][g] = 1 �ķ����
			// ������������Ҫ���÷�������
		}
		count = 0;
		for (j=0; j<=n; j++) link[j] = -1;
		for (i=1; i<=m; i++)	// ��Ů�����ϳ���
		{
			for (j=0; j<=n; j++) used[j] = 0;
			if (find_path(i)) count++;
		}
		printf("%d\n", count);
	}
	return 0;
}
