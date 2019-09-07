#include <stdio.h>

// �����������Ҫ����
// ������� data[������] < data[mid] < data[������]
// ͬʱ�������� left
int sort(int *data, int left, int right)
{
	int key;

	key = data[left];		// ѡ�� left ������
	while (left < right)
	{
		// ��Ϊ����ѡ�� left, �����ȴ��ұ߿�ʼ
		while (left < right && data[right] >= key) right--;
		data[left] = data[right];		// ��ʱ data[right] �ǿ��е�
		while (left < right && data[left] <= key) left++;
		data[right] = data[left];		// ��ʱ data[left] �ǿ��е�
	}
	// ��ʱ left == right, �����¾����� data[left] �� data[right] ��һ����
	data[left] = key;
	return left;		// ͬ��, ���� right Ҳ��
}

// ��������, �������� [left..right]
// ����ָ�, [left..mid-1] [mid] [mid + 1..right]
void quick_sort(int *data, int left, int right)
{
	int mid;		// ����
	if (left < right)
	{
		mid = sort(data, left, right);
		quick_sort(data, left, mid - 1);
		quick_sort(data, mid + 1, right);
	}
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	quick_sort(data, 0, n-1);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}