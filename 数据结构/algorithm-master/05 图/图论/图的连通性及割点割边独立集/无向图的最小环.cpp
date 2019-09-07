
// �������ͼ��С��

#include <stdio.h>

#define NUM 60
#define INF 0xFFFFFF

int m[NUM][NUM];		// �ڽӾ���
int n;
int dis[NUM][NUM];		// ��̾���
int pre[NUM][NUM];		// ��¼·��
int stack[NUM];			// ��¼��
int top;

// �����С��Ȩֵ��·��
// ���� flody ����ѡȡ�м�� k ���в���
// min{ dis[i][j] + m[i][k] + m[k][j] }
int min_h(void)
{
	int min = INF;
	int i, j, k;
	int tmp;

	for (i=0; i<n; i++)		// ��ʼ�� dis, pre
	{
		for (j=0; j<n; j++)
		{
			dis[i][j] = m[i][j];
			if (m[i][j] != INF)
				pre[i][j] = i;
			else pre[i][j] = -1;
		}
	}
	for (k=0; k<n; k++)
	{
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				// ����С��, ͬʱ��¼�û�
				if (dis[i][j] + m[i][k] + m[k][j] < min)
				{
					min = dis[i][j] + m[i][k] + m[k][j];
					// ��¼ i �� j ��·��, ���� k
					top = 0;
					tmp = j;
					while (tmp != -1)
					{
						stack[top++] = tmp;
						tmp = pre[i][tmp];
					}
					stack[top++] = k;
				}
				// flody ����, ��� i �� j �����·
				if (i != j && dis[i][k] + dis[k][j] < dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					pre[i][j] = pre[k][j];
					// �� i �� j ��ǰ������Ϊ k �� j ��ǰ��
				}
			}
		}
	}
	return min;
}

int main(void)
{
	int i, j, v;

	printf("���붥�������߼�: ");
	scanf("%d", &n);
	if (n <= 2) printf("\n�����㹹���ɻ�!\n");
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = INF;
	while (1)
	{
		scanf("%d %d %d", &i, &j, &v);
		if (!(i || j || v)) break;
		m[i][j] = v;
		m[j][i] = v;
	}
	printf("\n��С��Ȩֵ: %d\n�㼯: ", min_h());
	for (i=0; i<top; i++)
		printf("%d, ", stack[i]);
	printf("\n");

	return 0;
}
/*
6
0 1 9
0 2 1
2 3 1
3 4 1
4 1 1
0 3 6
3 1 5
5 0 1
5 1 1
0 0 0
*/