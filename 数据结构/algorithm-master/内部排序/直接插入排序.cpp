#include <stdio.h>

// ˳���������, [0..k][k+1..n]
// [0..k] ����,  [k+1..n] ����
// ÿ�δ� k + 1 ѡһ���嵽 [0..k] �еĺ���λ��
void insert_sort(int *data, int n)
{
	int i, j, tmp;

	for (i=1; i<n; i++)		// i ���� [k+1..n]
	{
		if (data[i-1] > data[i])
		{
			tmp = data[i];		// �ڳ���λ, ���ٸ�ֵ
			for (j=i; j>0; j--)		// �Ҹ�����λ��
				if (data[j-1] > tmp)
					data[j] = data[j-1];
				else break;
			data[j] = tmp;		// ����
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

	insert_sort(data, n);
	printf("�����: ");
	for (i=0; i<n; i++) printf("%d, ", data[i]);
	printf("\n\n");
	return 0;
}
