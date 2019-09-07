
// ����ͼ��ǿ��ͨ���� Gabow �㷨
// Tarjan �㷨���� low[i] == num[i] ����ʾ�ҵ���һ������ǿ��ͨ
// �� Gabow �㷨��������ջ����ǿ��ͨ
// һ��ջ��¼���ѷ���˳��, һ��ջ��¼����˳���ͬʱ, ��Ҫ��������ͨͼ

#include <stdio.h>
#include <string.h>

#define NUM 60

int m[NUM][NUM];		// �ڽӾ���
int n;
int used[NUM];
int stack1[100];		// ����ջ
int stack2[100];		// ��������ͨջ
int top1, top2;
int map[NUM];			// ��¼����ǿ��ͨ
int num[NUM];			// ��¼���ѱ��
int index;				// ���
int count;				// ǿ��ͨ����

void DFS(int cur)
{
	int i;

	stack1[top1++] = cur;
	stack2[top2++] = cur;
	num[cur] = index++;
	used[cur] = 1;
	for (i=0; i<n; i++)
	{
		if (m[cur][i] != 0)
		{
			if (!used[i]) DFS(i);
			else if (map[i] == -1)
			{
				// map[i] == -1 ˵�� i ��û������������
				// ��ô i ������ĳ������ǿ��ͨ����ǿ��ͨ
				// ��ջ�� i ���ϵĵ�, ȫ���˵�
				while (num[stack2[top2 - 1]] > num[i]) top2--;
			}
		}
	}
	// ������ cur ���ڽӱ�, ���� stack2 ��ջ���ǲ��� cur
	// �����, ˵�� cur ��ĳ��ǿ��ͨ�ĸ�, ��Ϊ�����ڽӱߵ�����
	// �Բ��ܰ� cur �� stack2 ����ȥ
	if (stack2[top2 - 1] == cur)
	{
		top2--;			// ȥ�� cur ��
		do
		{
			i = stack1[--top1];
			map[i] = count;
		}while (stack1[top1] != cur);
		count++;
	}
}

// ����ǿ��ͨ����
int gabow()
{
	int i;

	index = count = top1 = top2 = 0;
	memset(used, 0, sizeof(used));
	memset(map, -1, sizeof(map));
	for (i=0; i<n; i++)
	{
		if (!used[i]) DFS(i);
	}
	return count;
}

int main(void)
{
	int i, j;
	int count;

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
	count = gabow();
	printf("\nǿ��ͨ��������: %d\n", count);
	for (i=0; i<count; i++)
	{
		putchar('{');
		for (j=0; j<n; j++)
			if (map[j] == i) printf("%d, ", j);
		printf("}\n");
	}
	return 0;
}
