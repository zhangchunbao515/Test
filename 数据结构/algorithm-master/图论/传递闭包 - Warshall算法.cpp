
// warshall�㷨, ��һ��ͼ�Ĵ��ݱհ�
// ���ݱհ�: �������ٵı�, ʹ�ø�ͼ���д�����

#include <stdio.h>

#define NUM 60

void solve(int (*m)[NUM], int n)
{
	int i, j, k;

	// i, j ѭ���Ǳ��������
	// k ��ѭ��, �õ� k ���������̽, k ����Ϊ�м��, �� a -> k -> b
	// ��ô a -> b �д���
	// k ��ѭ������ dijskral ���ɳڲ���, ���� flody ��ȡ k �����ȫ���ɳ�
	for (k=0; k<n; k++)
		for (i=0; i<n; i++)
			for (j=0; j<n; j++)
				m[i][j] = m[i][j] | (m[i][k] & m[k][j]);
				// ��� i->j ������·, ���� i->k->j ��·
				// ��ô i->j ��·
}

int main(void)
{
	int m[NUM][NUM];		// �ڽӾ���
	int n;
	int a, b;
	int i, j;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		m[a][b] = 1;		// ����ͼ
	}
	// �󴫵ݱհ�, ����֮�� m[][] ���޸�
	solve(m, n);
	printf("\n���ݱհ�:\n");
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++) 
			printf("%3d ", m[i][j]);
		putchar('\n');
	}
	return 0;
}
/*
4
0 1
1 2
2 3
3 2
0 2
0 0
*/