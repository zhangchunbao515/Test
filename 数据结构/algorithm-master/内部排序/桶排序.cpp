#include <stdio.h>

// Ͱ����, Ͱ����֧�ָ���, 

#define MAX_SIZE 1000	// �������

// ���Ƶ�ͼ��Ƿ�
void tong_sort(int *data, int n)
{
	unsigned short int map[MAX_SIZE];
	int i, j;

	// map[i] ��¼ i �����˶��ٴ�
	for (i=0; i<MAX_SIZE; i++) map[i] = 0;
	for (i=0; i<n; i++) map[ data[i] ]++;
	for (j=i=0; i<MAX_SIZE; i++)
	{
		while (map[i]--) data[j++] = i;
	}	// ����--, data[j] ��¼Ԫ��
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