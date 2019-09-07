
// �ж�ͼ�Ƿ���ڻ�, �㷨��� <����ϵͳ> 249 ҳ
// ��ÿ���㷢��һ������, ������ѻ��Լ�˵�����ڻ�
// ˳����һ��, ���ݿ�ϵͳ���ж��û��Ƿ�ѭ����Ȩ, Ҳ�Ǽ�⻷

#include <stdio.h>

#define NUM 60		// ��󶥵���

int m[NUM][NUM];		// �ڽӾ���
int used[NUM];			// ���ʱ��

void DFS(int n, int cur)	// һ������
{
	int i;

	for (i=0; i<n; i++)
	{
		if (!used[i] && m[cur][i] != 0)
		{
			used[i] = 1;
			DFS(n, i);
		}
	}
}

// �л����� 1, �޻����� 0
int juage(int n)
{
	int i, j;
	
	// ��ÿ���㷢������
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++) used[j] = 0;
		DFS(n, i);
		if (used[i] == 1) return 1;
		// ��� i �㱻������, ˵���� i �����ֻص��� i, ���ڻ�
	}
	return 0;
}

int main(void)
{
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
	if (juage(n)) printf("\n���ڻ�, ������\n");
	else printf("\n�޻�, ��������\n");

	return 0;
}