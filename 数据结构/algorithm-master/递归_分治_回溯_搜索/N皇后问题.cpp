#include <stdio.h>
#include <string.h>

void show(char (*map)[20], int n)
{
	int i, j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
			printf("%3c", map[i][j]);
		printf("\n");
	}
}

int ok(char (*map)[20], int x, int y, int n)
{
	int i, y1, y2, x1;

	for (i=x-1; i>=0; i--)		// ��ͬ��
	{
		if (map[i][y] == '*') return 0;
	}
	for (y1=y-1, x1=x-1; y1>=0; y1--, x1--)	// ������Խ���
	{
		if (map[x1][y1] == '*') return 0;
	}
	for (y2=y+1, x1=x-1; y2<n; y2++, x1--)	// �����ҶԽ���
	{
		if (map[x1][y2] == '*') return 0;
	}
	return 1;
}

void DFS(char (*map)[20], int flood, int n, int *num)
{
	int i;

	if (flood == n)	// �ҵ���
	{
		show(map, n);
		printf("\n");
		(*num)++;
	}
	else 
	{		// ��ͬ��������ȥ
		for (i=0; i<n; i++)
		{
			if (ok(map, flood, i, n))
			{
				map[flood][i] = '*';
				DFS(map, flood + 1, n, num);	// ������һ��
				map[flood][i] = '-';		// ����ʱ, ����
			}
		}
	}
}

int nqueue(int n)
{
	char map[20][20];
	int num = 0;

	memset(map, '-', sizeof(map));
	DFS(map, 0, n, &num);
	return num;
}

int main(void)
{
	int n;

	printf("����ʺ�����: ");
	scanf("%d", &n);
	printf("�Ϸ������� %d\n", nqueue(n));

	return 0;
}