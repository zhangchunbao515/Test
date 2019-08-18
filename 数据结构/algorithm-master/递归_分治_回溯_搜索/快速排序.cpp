#include <stdio.h>

int move(int *num, int left, int right)
{
	int key = num[left];

	while (left < right)
	{
		while (left < right && num[right] >= key) right--;
		num[left] = num[right];
		while (left < right && num[left] <= key) left++;
		num[right] = num[left];
	}
	num[left] = key;
	return left;
}

void quick_sort(int *num, int left, int right)
{
	int mid;

	if (left < right)		// ���ƶ������������
	{
		mid = move(num, left, right);
		quick_sort(num, left, mid);
		quick_sort(num, mid+1, right);
	}
}

int main(void)
{
	int n, i;
	int num[100];

	printf("����һ�� n, �� n ������: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", num + i);
	quick_sort(num, 0, n - 1);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", num[i]);
	printf("\n");

	return 0;
}