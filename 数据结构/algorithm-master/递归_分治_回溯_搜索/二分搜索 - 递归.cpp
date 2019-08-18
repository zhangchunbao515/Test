#include <stdio.h>

// �ݹ�Ķ�������, �ٶ���ȻҪ�ȷǵݹ����
int bin_search_s(int *a, int left, int right, int data)
{
	int mid;

	if (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == data) return 1;
		else if (data < a[mid])
		{
			if (bin_search_s(a, left, mid-1, data)) 
				return 1;
		}
		else	// �ݹ�������������, �ѵ��ͷ��سɹ�
		{
			if (bin_search_s(a, mid+1, right, data))
				return 1;
		}
	}
	return 0;
}

int main(void)
{
	int n, i;
	int a[100];
	int data;

	printf("������һ����������: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		scanf("%d", a + i);

	while (1)
	{
		printf("\n������һ��Ҫ���ҵ���: ");
		scanf("%d", &data);
		if (bin_search_s(a, 0, n-1, data))
			printf("�ҵ�!\n");
		else printf("δ�ҵ�!\n");
	}
	return 0;
}