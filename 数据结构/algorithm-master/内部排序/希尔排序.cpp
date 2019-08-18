#include <stdio.h>

// ϣ��������ʵ���Ƕ�β�������
// ���������е�����Ϊ���� 1, ����Ϊ���� dk
void shell_sort(int *data, int n)
{
	// ���ʵ���������
	int dk[] = {101, 70, 40, 20, 10, 7, 5, 3, 1};
	int pos = 0;
	int d, i, j;
	int tmp;

	while (dk[pos++] >= n);		// ȷ���������

	for (d=pos-1; dk[d-1]!=1; d++)	// ��С����
	{
		for (i=dk[d]; i<n; i += dk[d])	// i ���� dk[k]
		{
			tmp = data[i];		// ��¼��������
			if (data[i - dk[d]] > data[i])
			{
				for (j=i; j>0; j -= dk[d])
				{
					if (data[j - dk[d]] > tmp)
						data[j] = data[j - dk[d]];
					else break;
				}
				data[j] = tmp;
				// ����Ĵ���, ������ i
			}
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

	shell_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}