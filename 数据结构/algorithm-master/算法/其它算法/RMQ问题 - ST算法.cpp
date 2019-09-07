
// RMQ ����, �ҳ�ĳ�������ֵ
// �� n ����, m �β�ѯ, ��ͨ����Ҫ O(n*m)
// ST �㷨�ܴﵽ O(m log n), �� O(1) ʱ�����ҳ���ֵ

// ����һ�� max(i, j) �����¼��ֵ
// max(i, j) ��ʾ i �� i+2^j �����ڵ���ֵ
// DP״̬ת�Ʒ���: max(i, j) = MAXIMUM{max(i, j-1), max(i+2^(j-1), j-1)}
// ������ 3 2 4 5 6 8 1 2 9 7 ����
// max(0, 2) = MAXIMUM(max(0, 1), max(1, 1))
// 3 2 4 5 6 =         3 2 4 5  , 2 4 5 6

// RMQ(i, j) ��ʾ��ѯ i �� j ����ֵ
// k = log2(���䳤��);
// RMQ(i, j) = MAXIMUM{max(i, k), max(j-2^k+1, k)}
// ���� RMQ(0, 4) = MAXIMUM(max(0, 2), max(1, 2))

#include <stdio.h>
#include <math.h>

#define NUM 400			// ��� 400 ������
#define MAXIMUM(a, b) ((a) > (b) ? (a) : (b))
// ���Ҫ��������Сֵ, ֻ����Ĵ˺�

int num[NUM];		// ����
int n;
int max[NUM][NUM];	// ��¼����ֵ

// DP ��������ֵ
void initialize()
{
	int i, j;
	int k = (int)(log(n) / log(2));

	for (i=1; i<=n; i++) max[i][0] = num[i];
	// ���� i �� i ����ֵ��Ȼ�� num[i]

	for (j=1; j<=n-(j<<1)+1; j++)	// j < n-2^j+1
	{
		for (i=1; i+(1<<j)-1<=n; i++)
		{
			max[i][j] = MAXIMUM(max[i][j-1], max[i+(1<<(j-1))][j-1]);
		}
	}
}

int RMQ(int a, int b)
{
	int k = (int)(log(b-a+1) / log(2));
	// log(����) / log(2) = log2(����)
	// ������û�� log2() ����, ��������һ�������Ļ��׹�ʽ

	return MAXIMUM(max[a][k], max[b-(1<<k)+1][k]);
}

int main(void)
{
	int a, b;
	int i;

	printf("���� n, �� n ����: \n");
	scanf("%d", &n);
	for (i=1; i<=n; i++)		// �±�� 1 ��ʼ
		scanf("%d", num + i);
	initialize();
	// �����ѯ����
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("���ֵ: %d\n", RMQ(a, b));
	}
	return 0;
}
/*		һ���������
10
3 2 4 5 6 8 1 2 9 7
*/