
// �����ı���֮���м��㷨
// �� n ������, m ����ͬ����Դ
// ÿ������ռ�� m ����Դ�е�һ������

#include <stdio.h>
#include <string.h>

#define NUM 50

int n, m;
int xian[NUM];			// ������Դ
int you[NUM][NUM];		// ������Դ
int xu[NUM][NUM];		// ��Ȼ����
// xian[a] = b;      ��ʾ�� a ����Դ�Ŀ������� b
// you[a][b] = c;    ��ʾ�� a ������, ռ�� b ����Դ c ��
// xu[a][b] = c;     ��ʾ�� a ������, ���� b ����Դ c ��

// ��ȫ���� 1, ����ȫ���� 0
int juage()
{
	int i, j, k;
	int used[NUM];
	int flag;

	for (k=0; k<n; k++) used[k] = 0;

	// n ������, ��Ҫ���� n ��
	for (k=0; k<n; k++)
	{
		for (i=0; i<n; i++)		// ��һ�� i
		{
			if (used[i]) continue;
			flag = 1;
			for (j=0; j<m; j++)		// ƥ�����
			{
				if (xian[j] - xu[i][j] < 0)
				{
					flag = 0;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag) return 0;
		used[i] = 1;
		for (j=0; j<m; j++)		// �ͷ� i ����Դ
			xian[j] += you[i][j];
	}
	return 1;
}

int main(void)
{
	int i, j;

	memset(you, 0, sizeof(you));
	memset(xu, 0, sizeof(xu));
	memset(xian, 0, sizeof(xian));
	printf("�����������: ");
	scanf("%d", &n);
	printf("��������Դ�������: ");
	scanf("%d", &m);
	printf("����������Դ����: \n");
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			scanf("%d", you[i] + j);
	printf("������Ȼ�������: \n");
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			scanf("%d", xu[i] + j);
	printf("���������Դ����: ");
	while (1)
	{
		for (i=0; i<m; i++)
			scanf("%d", xian + i);
		if (juage()) printf("��ȫ״̬\n");
		else printf("����ȫ״̬\n");
	}
	return 0;
}
/*		�����������
5 4
3 0 1 1
0 1 0 0
1 1 1 0
1 1 0 1
0 0 0 0

1 1 0 0
0 1 1 2
3 1 0 0
0 0 1 0
2 1 1 0

0 0 1 0
1 0 0 0
*/