
// ����ɸѡ
// ��� k ������, ��ô�� k Ϊ���ӵ�����������

#include <stdio.h>

#define NUM 20000		// �������ڵ�����
int map[NUM];			// ɸ��

void initialize()
{
	int i, j;

	for (i=0; i<NUM; i++) map[i] = 1;
	map[0] = map[1] = 1;

	for (i=2; i<NUM; i++)
	{
		if (map[i])		// i ������
		{
			for (j=i+i; j<NUM; j+=i) map[j] = 0;
		}
	}
}

int main(void)
{
	int i;

	initialize();		// ��ʼ��
	printf("����:\n");
	for (i=2; i<200; i++)
	{
		if (map[i]) printf("%d, ", i);
	}
	return 0;
}