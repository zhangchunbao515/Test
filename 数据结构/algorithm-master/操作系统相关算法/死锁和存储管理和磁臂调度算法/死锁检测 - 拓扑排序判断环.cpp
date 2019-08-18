
// ���������⻷
// �㷨����:
// ���ÿ������� degree[]
// Ѱ�����Ϊ 0 �ĵ�, ������ȥ

#include <stdio.h>
#include <string.h>

#define NUM 50			// ��󶥵���

// �л����� 1, �޻����� 0
int juage(int (*m)[NUM], int n)
{
	int degree[NUM];
	int i, j, tmp;
	int stack[300];
	int top = 0;

	// ����ÿ��������
	memset(degree, 0, sizeof(degree));
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			if (m[i][j] != 0) degree[j]++;

	// �����Ϊ 0, ��ջ
	for (i=0; i<n; i++)
		if (degree[i] == 0)
			stack[top++] = i;

	// ջ�м�¼���Ϊ 0 �ĵ�
	while (top != 0)
	{
		tmp = stack[--top];
		for (i=0; i<n; i++)
		{
			if (m[tmp][i] != 0)
			{
				degree[i]--;
				if (degree[i] == 0)
					stack[top++] = i;
			}
		}
	}		// �������������ȵĵ�, ˵���л�
	for (i=0; i<n; i++)
		if (degree[i] != 0) return 1;
	return 0;
}

int main(void)
{
	int m[NUM][NUM];		// �ڽӾ���
	int n;
	int i, j;
	int a, b;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (!(a || b)) break;
		m[a][b] = 1;
	}
	if (juage(m, n)) printf("\n���ڻ�, ������\n");
	else printf("\n�޻�, ��������\n");

	return 0;
}