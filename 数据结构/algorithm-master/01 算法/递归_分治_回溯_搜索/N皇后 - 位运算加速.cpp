
#include <stdio.h>

int all;		// ǰ n ��λ���� 1
int sum;

void DFS(int cur, int ld, int rd)
{
	int p, pos;

	if (cur == all)
	{
		sum++;
		return ;
	}
	pos = all & ~(cur | ld | rd);
	// ������в���ͻ��λ��
	while (pos)
	{
		p = pos & -pos;		// ������ұ߲���ͻλ��
		pos -= p;			// ȥ����λ��
		DFS(cur + p, (ld + p) << 1, (rd + p) >> 1);
	}
}

int main(void)
{
	int n;

	while (1)
	{
		// ���� n ��Ҫ���� 20, n ��ʾ n * n ������
		scanf("%d", &n);
		all = (1 << n) - 1;		// ǰ n λ��Ϊ 1
		sum = 0;
		DFS(0, 0, 0);
		printf("%d\n", sum);		// �����ĸ���
	}
	return 0;
}