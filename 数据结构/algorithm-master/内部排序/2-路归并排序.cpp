#include <stdio.h>
#include <malloc.h>

// �鲢�������Ҫ����
// �ϲ� [left..mid] �� [mid+1, right]
// ����˳���ĺϲ�
void merge(int *tmp, int *data, int left, int mid, int right)
{
	int pos = 0;		// ָʾ��ʱ�ռ�λ��
	int rs = mid + 1;	// ���������
	int ls = left;		// ���������
	int i, j;

	// left, right �����޸�, ֻ�ܸı� ls, rs ָ��
	while (ls <= mid && rs <= right)
	{
		if (data[ls] < data[rs])
			tmp[pos++] = data[ls++];
		else tmp[pos++] = data[rs++];
	}
	// ʣ�µĲ���, ֱ������
	while (ls <= mid)   tmp[pos++] = data[ls++];
	while (rs <= right) tmp[pos++] = data[rs++];
	// �� left ��ʼ���ǵ�ԭ�����򲿷�
	for (j=left, i=0; i<pos; i++, j++) data[j] = tmp[i];
}

// 2-·�鲢����
// �������� [left..mid], [mid+1..right]
// ��Ҫ�ֳ� [left..mid-1], [mid..right] Ҳ�ǿ��Ե�
void merge_sort(int *data, int left, int right)
{
	int mid;
	int tmp[101];	// ��ʱ�ռ�

	if (left < right)	//���ƶ������ĺ������
	{
		mid = (left + right) / 2;
		merge_sort(data, left, mid);
		merge_sort(data, mid + 1, right);
		merge(tmp, data, left, mid, right);
		// �ϲ� [left..right]
	}
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	merge_sort(data, 0, n-1);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}