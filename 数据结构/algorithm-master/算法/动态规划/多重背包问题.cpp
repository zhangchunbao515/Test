
// ���ر�������, ��ȫ������ÿ����Ʒ���������޼�
// ���ر�����, �� i ����Ʒ������ count[i] ��, ���޼�

#include <stdio.h>

#define NUM 50
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int dp(int c, int n, int *w, int *v, int *cnt)
{
	int sum[NUM][NUM];
	int i, j, k, h;

	for (k=0, i=0; i<=n; i++)
	{
		for (j=0; j<=c; j++) sum[i][j] = 0;
		k += cnt[i];		// ���� k ����Ʒ
	}
	for (i=1; i<=k; i++)
	{
		for (j=0; j<n; j++)			// �õ� j ����Ʒ
		{ if (cnt[j]) { cnt[j]--;  break; } }
		for (h=0; h<=c; h++)
		{
			if (w[j] <= h)			// ת��Ϊ 0-1 ����
				sum[i][h] = MAX(sum[i-1][h], sum[i-1][h-w[j]] + v[j]);
			else sum[i][h] = sum[i-1][h];
		}
	}
	return sum[k][c];
}

int main(void)
{
	int c, n;		// ������� c, ���� n
	int weight[NUM] = {0};
	int value[NUM] = {0};
	int count[NUM] = {0};
	int i, sum;

	printf("���뱳�������������Ʒ����: ");
	scanf("%d %d", &c, &n);
	printf("���� %d ����Ʒ: (���� ��ֵ)\n", n);
	for (i=1; i<=n; i++)		// 0 �ŵ�Ԫ����
		scanf("%d %d %d", weight + i, value + i, count + i);
	sum = dp(c, n, weight, value, count);
	printf("\n����ֵ: %d\n", sum);
	return 0;
}
