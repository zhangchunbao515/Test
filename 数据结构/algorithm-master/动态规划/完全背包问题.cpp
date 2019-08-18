
// ��ȫ��������
// 0-1 ������, ÿ����Ʒֻ������һ��, ����ȫ������, ÿ����Ʒ���������޴�
// ��Ҫ����
// dp()				��ͨDP,   ʱ O(n^2), �� O(n^2+n)
// dp2()			�ռ��Ż�  ʱ O(n^2), �� O(n+n)
// dp3()			ʱ���Ż�  ʱ O(n^2), �� O(n)

#include <stdio.h>

#define SIZE 150
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// �ⷨһ: ת��Ϊ 0-1 ��������
// ÿ����Ʒ�õļ������ܳ������������� c
// ��ÿ����Ʒ���ֻ���� c / w[i] ��
// ����ÿ����Ʒ�����������, �ٰ��� 0-1 ��������

// ״̬����: sum[i][j] = MAX{sum[i-1][j], sum[i][ j- w[k] ] + v[k]}
// �� i ����Ʒ, ���� i ʱ, �� = sum[i-1][j]
// �� i ʱ, �� = sum[i][ j- w[k] ] + v[k]
int dp(int c, int n, int *w, int *v)
{
	// sum[a][b] = c �� a ����Ʒ, ������ b ʱ, ����ֵΪ c
	int sum[SIZE][SIZE];
	int count[SIZE];		// ͳ��ÿ����Ʒ���õĴ���
	int i, j, k, total = 0;

	for (i=0; i<=c; i++) sum[0][i] = 0;		// ��ʼ�� sum
	for (i=1; i<=n; i++)			// �����ÿ����Ʒ���õĴ���
	{
		count[i] = c / w[i];
		total += count[i];			// �ܼ���
	}
	for (i=1; i<=total; i++)		// �� i ������Ʒ
	{
		for (k=1; k<=n; k++)		// �õ� k ����Ʒ
		{ if (count[k]) { count[k]--;   break; }}
		for (j=0; j<=c; j++)		// ö������
		{	
			// �õ� k ��
			if (w[k] > j) sum[i][j] = sum[i-1][j];	// �Ų���
			else sum[i][j] = MAX(sum[i-1][j], sum[i][ j-w[k] ] + v[k]);
		}
	}
	return sum[total][c];		// �� total ����Ʒ
}


// dp2() �� dp() �Ļ�����, �ù��������Ż��ռ�
int dp2(int c, int n, int *w, int *v)
{
	// sum[a] = c, �� a ����Ʒ, ����ֵΪ c
	int sum[SIZE];			// sum[] �Ż�Ϊһά����
	int count[SIZE];
	int i, j, k, total = 0;

	for (i=0; i<=c; i++) sum[i] = 0;
	for (i=1; i<=n; i++)
	{
		count[i] = c / w[i];
		total += count[i];			// �ܼ���
	}
	for (i=0; i<total; i++)			// �� i ������Ʒ
	{
		for (k=1; k<=n; k++)		// �õ� k ����Ʒ
		{ if (count[k]) {count[k]--;   break;}}
		// ö������, ����Ӻ���ǰ��
		// ��Ϊ�õ� k ����Ʒ��ʱ����Ҫ, sum[k] �� sum[ j-w[k] ] ��ֵ
		// ��ǰ������, �Ḳ�ǵ� sum[j-w[k]]
		for (j=c; j>=0; j--)
		{
			if (w[k] <= j)		// װ����
				sum[j] = MAX(sum[j], sum[ j-w[k] ] + v[k]);
		}	// else װ���¾ͻ���ԭ���� sum[k]
	}
	return sum[c];		// �� total ����Ʒ
}


// ��ţ�ⷨ
// 0-1������, ö������֮��������Ҫ�� C -> 0 ����
// ����ΪҪ��֤ sum[c] �Ǵ� sum[c-w[k]] ���ƶ���
// ��Ҫ��֤ sum[c-w[k]] ��ǰ k ����Ʒ�����Ž�, û�б���Ʒ k �ƻ�
// ����ȫ������ÿ����Ʒ����������, ��ô sum[c-w[k]] ���԰�����ǰ��Ʒ k
// ������������� 0 -> C ö��, sum[c-w[k]] ���ܼ����˵�ǰ��Ʒ
int dp3(int c, int n, int *w, int *v)
{
	int sum[SIZE];
	int i, j;

	for (i=0; i<=c; i++) sum[i] = 0;
	for (i=0; i<n; i++)			// ���� n ����Ʒ 0 -> n
		for (j=0; j<=c; j++)		// ö������ 0 -> C
			if (w[i] <= j)  sum[j] = MAX(sum[j], sum[j-w[i]] + v[i]);
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
	sum = dp2(c, n, weight, value);
//	sum = dp3(c, n, weight, value);
	printf("\n����ֵ: %d\n", sum);
	return 0;
}
