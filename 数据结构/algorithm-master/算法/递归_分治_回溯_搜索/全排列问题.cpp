#include <stdio.h>

int count = 1;

inline void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;   *b = tmp;
}

void show_p(int num[], int s, int all)
{
	int i;

	if (s == all-1) 
	{
		printf("�� %d ������: ", count++);
		for (i=0; i<all; i++)
			printf("%d, ", num[i]);
		printf("\n");
	}
	else 
	{
		for (i=s; i<all; i++)
		{
			swap(num + s, num + i);
			show_p(num, s+1, all);		// �� s + 1 ��������
			swap(num + s, num + i);		// ���ݸĻ�ԭ����
		}
	}
}

int main(void)
{
	int num[200];
	int n, i;

	printf("���� n, �� n  ��Ԫ��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		scanf("%d", num+i);
	show_p(num, 0, n);

	return 0;
}
