#include <stdio.h>

int bin_search(int *a, int left, int right, int data)
{
	int mid;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == data) return 1;
		else if (a[mid] > data)
			right = mid - 1;
		else left = mid + 1;
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
		if (bin_search(a, 0, n-1, data))
			printf("�ҵ�!\n");
		else printf("δ�ҵ�!\n");
	}
	return 0;
}