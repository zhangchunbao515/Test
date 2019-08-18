#include <stdio.h>
#include <malloc.h>

// �Ľ���Ͱ����, ֧�ָ���

#define SIZE 1000000	// ������ռ�

// �㷨: �ҵ�һ����С��, ����, �����ֵ, ����ʱ����
// ��ԭ��������ǰ��, ��С������ 0 λ��
// ���� ��С�� -1, �ǾͰ� -1 ���� 0 λ��,
void tong_sort(int *data, int n)
{
	int min = 0xFFFFFFF;
	int max = -0xFFFFFFF;
	int j, i, size;
	short int *map;		// ��ʱ�ռ�

	for (i=0; i<n; i++)		// ���ҳ���ֵ
	{
		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
	size = max-min;
	if (size > SIZE) return ;	// ��ֹ̫����
	map = (short int *)malloc((size+2) * sizeof(short int));

	for (i=0; i<=size; i++) map[i] = -1;		// ��ʼ
	for (i=0; i<n; i++) 
	{
		map[ data[i] - min ]++;		// ���
	}
	for (j=i=0; i<=size; i++)		// ����
	{
		while (map[i] != -1) 
		{
			data[j++] = i + min;	// �ӻز�ֵ min
			map[i]--;
		}
	}
	free(map);
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	tong_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}