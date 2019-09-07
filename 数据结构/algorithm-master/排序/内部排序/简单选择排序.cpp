#include <stdio.h>

// ��ѡ������, [0..n]
// ÿ�δ� ����ѡһ����С�ķŵ�ǰ����
void select_sort(int *data, int n)
{
	int i, j, tmp;
	int min, pos;

	for (i=0; i<n; i++)
	{
		min = 0x4FFFFFFF;
		tmp = data[i];   pos = i;
		for (j=i; j<n; j++)
		{
			if (data[j] < min)
			{
				min = data[j];
				pos = j;
			}
		}
		if (pos != i)	// ��������Լ�
		{
			data[i] = data[pos];
			data[pos] = tmp;
		}
	}
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	select_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}
