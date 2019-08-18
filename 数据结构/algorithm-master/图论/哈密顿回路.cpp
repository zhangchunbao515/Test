
// ���ܶٻ�·
// ŷ����·��ÿ����ֻ�ܾ���һ��, ���ܶٻ�·��ÿ����ֻ�ܾ���һ��
// ��ԭͼ����һ������, ���������ȫ����㼴��һ�����ܶٻ�·

#include <stdio.h>

#define NUM 60

int m[NUM][NUM];
int n;
int used[NUM];
int stack[100];
int top;

void DFS(int cur)		// ����
{
	int i;

	stack[top++] = cur;
	used[cur] = 1;
	for (i=0; i<n; i++)
	{
		if (!used[i] && m[cur][i])
		{
			DFS(i);
			break;
		}
	}
}

int judge()
{
	int i;

	top = 0;
	for (i=0; i<n; i++) used[i] = 0;
	DFS(0);
	// ���û�з�����ȫ���ĵ�, ����
	for (i=0; i<n; i++)
		if (!used[i]) return 0;
	// �������Ľ��, �ܲ����γɻ�·
	if (m[stack[top-1]][0] == 0) return 0;
	return 1;
}

int main(void)
{
	int i, j;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (!(i || j)) break;
		m[i][j] = 1;
		m[j][i] = 1;
	}
	if (judge())
	{
		printf("\n���ܶٻ�·: ");
		for (i=0; i<top; i++)
			printf("%d -> ", stack[i]);
		printf("%d\n", stack[0]);
	}
	else printf("\n���ǹ��ܶٻ�·!\n");

	return 0;
}
/*			�����������
5
0 1
1 2
2 3
3 0
0 4
1 4
2 4
3 4
0 0

5
0 1
1 2
2 0
2 3
3 4
4 2
0 0
*/