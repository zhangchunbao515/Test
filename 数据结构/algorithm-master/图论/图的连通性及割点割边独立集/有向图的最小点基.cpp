
// �������: ��ʦҪ֪ͨ����ѧ��һ����Ϣ, ��ʦ��ȫ��ѧ���ĵ绰
// ���һ��һ��֪̫ͨ�鷳, �е�ѧ���ụ�ཻ���绰����
// ��֪ͨ�� A ѧ��, A ѧ���ֿ���֪ͨ����ʶ��ѧ��
// ����ʦ����Ҫ֪ͨ���ٸ�ѧ��, ����֪ͨ������ѧ��
// �������С�����
// �㷨: ��ͼ�еļ���ǿ��ͨ�� Tarjan ���ɵ�
// �������Ϊ 0 �������, ������С�����

#include <stdio.h>

#define NUM 70		// �������
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int m[NUM][NUM];		// �ڽӾ���
int n;
int stack[100];
int top;
int in_stack[NUM];		// ����ڲ���ջ��
int num[NUM];			// ���ѱ��
int index;				// ���
int low[NUM];			// ��С�ص�
int belong[NUM];		// ����ǿ��ͨ
int count;				// ǿ��ͨ����
int degree[NUM];		// ͳ���������

// Tarjan �㷨�����ѹ���
void DFS(int cur)
{
	int i;

	low[cur] = num[cur] = index++;
	stack[top++] = cur;
	in_stack[cur] = 1;
	for (i=0; i<n; i++)
	{
		if (m[cur][i] != 0)
		{
			if (num[i] == -1)
			{
				DFS(i);
				low[cur] = MIN(low[cur], low[i]);
			}
			else if (in_stack[i])
				low[cur] = MIN(low[cur], num[i]);
		}
	}
	// �ҵ�һ��ǿ��ͨ, ��ջ�� cur ���ϵ�ȫ������
	if (num[cur] == low[cur])
	{
		do 
		{
			i = stack[--top];
			in_stack[i] = 0;
			belong[i] = count;
		}
		while (stack[top] != cur);
		count++;
	}
}

// Tarjan �㷨����С���
// �㷨����:
// ���ÿ����������ǿ��ͨ
// ͳ��ÿ����������, ͳ�����Ϊ 0 ����
int Tarjan(void)
{
	int i, j;
	int a = 0;

	top = count = index = 0;
	for (i=0; i<n; i++)
	{
		belong[i] = num[i] = -1;
		in_stack[i] = degree[i] = 0;
	}
	for (i=0; i<n; i++)		// ͳ������ǿ��ͨ
	{
		if (num[i] == -1) DFS(i);
	}
	for (i=0; i<n; i++)		// ͳ���������
		for (j=0; j<n; j++)
			if (m[i][j] && belong[i] != belong[j]) 
				degree[ belong[j] ]++;
			// i, j Ҫ��������ͬ��ǿ��ͨ�������
	for (i=0; i<count; i++)
	{
		if (degree[i] == 0)		// ������
		{
			a++;
			printf("{");
			for (j=0; j<n; j++)
				if (belong[j] == i)
					printf("%d, ", j);
			printf("}\n");
		}
	}
	return a;
}

int main(void)
{
	int i, j;
	int a;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (i == 0 && j == 0) break;
		m[i][j] = 1;
	}
	printf("\n");
	a = Tarjan();
	printf("��С�����: %d\n", a);

	return 0;
}
/*
8
0 1
1 4
4 0
1 5
4 5
5 6
6 5
2 3
3 2
2 6
3 7
6 7
0 0
*/