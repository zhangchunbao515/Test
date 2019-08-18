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

// ���ƿ��������㷨
int find_k(int *num, int left, int right, int k)
{
	int mid;

	if (left == right) return num[k];
	else
	{
		mid = move(num, left, right);
		if (k == mid) return num[k];
		else if (k < mid)
			return find_k(num, left, mid-1, k);
		else 
			return find_k(num, mid+1, right, k);
	}
	return 0;
}

int main(void)
{
	int num[100];
	int n, k;
	int i;

	printf("������ n, �� n ��Ԫ��");
	scanf("%d", &n);
	for (i=1; i<=n; i++)		// 0 �ŵ�Ԫ����
		scanf("%d", num + i);
	printf("���ҵ� k С����, ���� k: ");
	scanf("%d", &k);
	printf("�� %d С������: %d\n\n", k, find_k(num, 1, n, k));

	return 0;
}
