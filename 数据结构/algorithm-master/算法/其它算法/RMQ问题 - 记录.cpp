
// O(n^2) ����ÿ����ѯ��, �� RMQ[][] ������, O(1) �ش��ѯ

#include <stdio.h>

#define NUM 300

int RMQ[NUM][NUM];
int num[NUM];
int n;

void initialize(void)
{
	int i, j;
	int max;

	for (i=0; i<n; i++)
	{
		max = -0xFFFFFF;
		for (j=i; j<n; j++)
		{
			if (num[j] > max) max = num[j];
			RMQ[i][j] = max;
			RMQ[j][i] = max;
		}
	}
}

int main(void)
{
	int a, b;
	int i;

	printf("���� n, �� n ����: \n");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		scanf("%d", num + i);
	initialize();
	// �����ѯ����, �±�� 0 ��ʼ
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("���ֵ: %d\n", RMQ[a][b]);
	}
	return 0;
}
/*		һ���������
10
3 2 4 5 6 8 1 2 9 7
*/