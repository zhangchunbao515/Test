
#include <stdio.h>

#define NUM 500		// ��� 500 ����

struct 
{
	int left;
	int right;
	int sum;
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
		tree[pos].sum = num[L];
		return num[L];
	}
	mid = (L + R) / 2;
	a = create(L, mid, 2 * pos);
	b = create(mid + 1, R, 2 * pos + 1);
	tree[pos].left = L;
	tree[pos].right = R;
	tree[pos].sum = a + b;		// ����ʱ��������

	return tree[pos].sum;
}

void DFS(int L, int R, int pos, int *s)
{
	int mid;

	if (tree[pos].left == L && tree[pos].right == R)
	{
		*s += tree[pos].sum;
		return ;
	}
	mid = (tree[pos].left + tree[pos].right) / 2;
	if (R <= mid)		// ������
	{
		DFS(L, R, 2 * pos, s);
	}
	else if (mid < L)		// ������
	{
		DFS(L, R, 2 * pos + 1, s);
	}
	else		// �����������
	{
		DFS(L, mid, 2 * pos, s);
		DFS(mid + 1, R, 2 * pos + 1, s);
	}
}

int query(int L, int R)		// ��ѯ��ֵ
{
	int sum = 0;

	if (L < R)
		DFS(L, R, 1, &sum);		// �߶�������
	else 
		DFS(R, L, 1, &sum);
	return sum;
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
	// �������, �±�� 1 ��ʼ
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("��: %d\n", query(a, b));
	}
	return 0;
}
/*
10
3 2 4 5 6 8 1 2 9 7
*/