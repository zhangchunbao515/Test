#include <stdio.h>

// ��Ҫ����
// dp()				��ͨDP,   ʱ O(n^2), �� O(n^2)
// dp2()			�ռ��Ż�  ʱ O(n^2), �� O(n)
// show_and_dp()	���������Щ��Ʒ

#define SIZE 300	// �����Ʒ��
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 0-1����, DP�ⷨ
// �㷨����, �ӵ�һ����Ʒ��ʼѡ��Ż򲻷�, ֱ�����
// �� sum[][] �����м�¼����ֵ
// sum[a][b] = c  ����:
// a �� a ����Ʒ,  b ���������Ϊ b ��ʱ��, c ���ż�ֵ
int dp(int c, int n, int *w, int *v)
{
	int sum[SIZE][SIZE];		// ��¼����ֵ
	int i, j;

	for (i=0; i<=n; i++)		// ��ʼ��
		for (j=0; j<=c; j++) sum[i][j] = 0;
	
	for (i=1; i<=n; i++)	// ��Ʒ
	{
		for (j=1; j<=c; j++)	// ��ǰ���� j
		{
			// �����ǰ��������С�ڵ� i ����Ʒ����, ���Ų���
			// ֱ����ǰ i - 1 ������ֵ
			// ����, ���ڵ�ǰ��Ʒ����ѡ��Ż򲻷�
			if (j < w[i]) sum[i][j] = sum[i-1][j];
			else sum[i][j] = MAX(sum[i-1][j], sum[i-1][ j - w[i] ] + v[i]);
			// ֱ����ǰһ����Ʒ(i-1)������ֵ sum[i-1][j], ���ǲ���
			// ���Ҫ�ŵ�ǰ��Ʒ i, �õ�ǰ���� j, ��ȥ�Լ����� w[i], �ڳ��ռ�
			// �ٴ�����Ϊ j-w[i] ������ֵ, �����Լ��� v[i], ѡ������
		}
	}
	return sum[n][c];		// n ����Ʒ����Ϊ c ʱ�Ľ�
}

// ͬʱ���ѡ��ʲô��Ʒ (����, ��ֵ)
int show_and_dp(int c, int n, int *w, int *v)
{
	int sum[SIZE][SIZE];
	int used[SIZE][SIZE];	// used[][] == 0 û��, == 1 ����
	int i, j;

	for (i=0; i<=n; i++)
		for (j=0; j<=c; j++)
			sum[i][j] = used[i][j] = 0;

	for (i=1; i<=n; i++)	// �� i ����Ʒ
	{
		for (j=1; j<=c; j++)	// ���� j
		{
			if (j < w[i]) sum[i][j] = sum[i-1][j];
			else 
			{	// �Ƚ��úͲ����ĸ���
				if (sum[i-1][j] >= sum[i-1][j - w[i]] + v[i])
					sum[i][j] = sum[i-1][j];
				else 
				{
					sum[i][j] = sum[i-1][j - w[i]] + v[i];
					used[i][j] = 1;		// ����
				}
			}
		}
	}
	printf("\nѡ��: ");
	i = n;   j = c;
	while (i >= 0)
	{
		if (used[i][j])
		{
			printf("(%d, %d), ", w[i], v[i]);
			j -= w[i];
		}
		i--;
	}
	return sum[n][c];
}

// ����2���, �Ż��ռ临�Ӷ� O(n)
// ���ڲ��ٱ��� i ����Ʒ, ������ j ��ʱ������ֵ�Ƕ���
// ֻ���浱ǰ��Ʒ i ������ֵ
// ���������Ӻ���ǰ��, for j=c to 1 do
int dp2(int c, int n, int *w, int *v)
{
	int sum[SIZE];
	int i, j;

	for (i=0; i<=c; i++) sum[i] = 0;

	for (i=1; i<=n; i++)	// �� i ����Ʒ
	{
		for (j=c; j>=1; j--)	// ���� j
		{
			if (j >= w[i])
				sum[j] = MAX(sum[j], sum[j - w[i]] + v[i]);
			// ֻ�е�ǰ���� j �����Լ� w[i] ���ܷŵ���
			// ���� sum[j] = sum[j] ��ֵ, �ޱ仯
		}
		for (j=1; j<=c; j++) printf("%d, ", sum[j]);
		printf("\n");
	}
	return sum[c];
}

int main(void)
{
	int c, n;		// ������� c, ���� n
	int weight[SIZE] = {0};
	int value[SIZE] = {0};
	int i, sum;

	printf("���뱳�������������Ʒ����: ");
	scanf("%d %d", &c, &n);
	printf("���� %d ����Ʒ: (���� ��ֵ)\n", n);
	for (i=1; i<=n; i++)		// 0 �ŵ�Ԫ����
		scanf("%d %d", weight + i, value + i);
//	sum = dp(c, n, weight, value);
//	sum = dp2(c, n, weight, value);
	sum = show_and_dp(c, n, weight, value);   // ͬʱ�����ѡ��Ʒ
	printf("\n����ֵ: %d\n", sum);
	return 0;
}
