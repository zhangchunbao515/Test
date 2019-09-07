
// ���ù鲢�����������, O(n log n)

#include <stdio.h>
#include <malloc.h>

int *tmp;	// �鲢�ĸ����ռ�
int count;	// ���������

// �ϲ�, �������ܸ�
void merge(int *num, int ls, int le, int rs, int re)
{
	int lc = ls;	// ָ���趨�����
	int rc = rs;
	int top = 0;
	int i;

	// ָ��û�е�ͷ
	while (lc <= le && rc <= re)
	{
		if (num[lc] <= num[rc])
			tmp[top++] = num[lc++];
		else 
		{
			tmp[top++] = num[rc++];
			// ��ʱ������ĵ�����������ʣ�µĶ�Ҫ��
			// ��ô num[rc] ��ʣ�� num[lc..le] ���������
			// ���Խ�����ȫ�����, ����ֻͳ������
			count += le - lc + 1;
		}
	}
	while (lc <= le) tmp[top++] = num[lc++];
	while (rc <= re) tmp[top++] = num[rc++];
	// �� tmp �Ľ��д��ȥ
	for (i=ls, top=0; i<=re; i++)
		num[i] = tmp[top++];
}

void dfs(int *num, int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		dfs(num, left, mid);
		dfs(num, mid + 1, right);
		// �ϲ� [left, mid], [mid+1, right]
		merge(num, left, mid, mid+1, right);
	}
}

// �鲢�����������
void g_sort(int *num, int n)
{
	// �鲢�ĸ����ռ�
	tmp = (int *)malloc(1000 * sizeof(int));
	count = 0;
	dfs(num, 0, n-1);
	free(tmp);
}

int main(void)
{
	int n, i;
	int num[1000];

	while (1)
	{
		printf("���� n, �� n ������: ");
		scanf("%d", &n);
		if (n <= 0) break;
		for (i=0; i<n; i++)
			scanf("%d", num + i);
		g_sort(num, n);			// �鲢����
		for (i=0; i<n; i++)
			printf("%d, ", num[i]);
		printf("�����: %d\n\n", count);
	}
	return 0;
}