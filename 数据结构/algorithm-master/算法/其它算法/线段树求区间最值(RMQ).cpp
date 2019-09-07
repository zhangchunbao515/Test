
#include <stdio.h>

#define NUM 500		// ��� 500 ����
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct 
{
	int left;
	int right;
	int max;
}tree[1000];		// �߶���

int num[NUM];		// ����
int n;

int create(int L, int R, int pos)		// ������
{
	int mid;
	int a, b;

	if (L == R)
	{
		tree[pos].left = L;
		tree[pos].right = R;
		tree[pos].max = num[L];
		return num[L];
	}
	mid = (L + R) / 2;
	a = create(L, mid, 2 * pos);
	b = create(mid + 1, R, 2 * pos + 1);
	tree[pos].left = L;
	tree[pos].right = R;
	tree[pos].max = MAX(a, b);		// ����ʱ������ֵ

	return tree[pos].max;
}

void DFS(int L, int R, int pos, int *m)
{
	int mid;

	if (tree[pos].left == L && tree[pos].right == R)
	{
		*m = MAX(*m, tree[pos].max);
		return ;
	}
	mid = (tree[pos].left + tree[pos].right) / 2;
	if (R <= mid)		// ������
	{
		DFS(L, R, 2 * pos, m);
	}
	else if (mid < L)		// ������
	{
		DFS(L, R, 2 * pos + 1, m);
	}
	else		// �����������
	{
		DFS(L, mid, 2 * pos, m);
		DFS(mid + 1, R, 2 * pos + 1, m);
	}
}

int query(int L, int R)		// ��ѯ��ֵ
{
	int max = -0xFFFFFF;

	if (L < R)
		DFS(L, R, 1, &max);		// �߶�������
	else
		DFS(R, L, 1, &max);
	return max;
}

int main(void)
{
	int i;
	int a, b;

	printf("���� n, �� n ����: ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)		// �±�� 1 ��ʼ
		scanf("%d", num + i);
	create(1, n, 1);
	// �����ѯ
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("���ֵ: %d\n", query(a, b));
	}
	return 0;
}
/*
10
3 2 4 5 6 8 1 2 9 7
*/