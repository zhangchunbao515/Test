#include <stdio.h>

// ð������, �����ϸ�, С���³�
void msort(int *data, int n)
{
	int tmp;
	int i, j;
	int last;		// ��¼��󽻻�����

	// n ��Ԫ��, ����� n-1 ��
	for (i=0; i<n-1; i++)
	{
		last = 0;
		for (j=last; j<n-1; j++)
		{
			if (data[j] > data[j+1])
			{
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				last = j;		// ��¼
			}
		}
		if (last == 0) break;
	}
}

int main(void)
{
	int i, n;
	int data[100];

	printf("������ n, �� n ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++) scanf("%d", data + i);

	msort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}