
// ��������ͼ��ǿ��ͨ���� Tarjan �㷨
// �� tarjan �㷨����һ��
// �� num[] ��¼����ʱ���ķ���˳��
// �� low[] ��¼ÿ������ܻص���������������С���
// ��� low[k] == count[k] ��˵�� k �ܻص� k
// ��ôջ�� k �ϵ�Ԫ�غ� k ��һ��ǿ��ͨ����

#include <stdio.h>
#include <string.h>

#define NUM 60
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int m[NUM][NUM];		// �ڽӾ���, ԭͼ
int n;					// ������
int num[NUM];			// ���ѷ���˳��
int number;				// ���
int low[NUM];			// �ܵ�����С�ĵ�
int used[NUM];			// ���ʱ��
int stack[NUM];			// ��¼���ʵĽ��
int top;
int in_the_stack[NUM];	// ��־�ڲ���ջ��
int count;				// ��¼ǿ��ͨ����


void DFS(int cur)
{
	int i;

	used[cur] = 1;
	low[cur] = num[cur] = number++;
	stack[top++] = cur;
	in_the_stack[cur] = 1;
	// ����ڲ���ջ��, ֻ����ջ�еĵ����ͬһ��������������

	for (i=0; i<n; i++)
	{
		if (m[cur][i])
		{
			if (!used[i])
			{
				DFS(i);		// ����ʱ���� low
				low[cur] = MIN(low[cur], low[i]);
			}
			else if (in_the_stack[i])
				low[cur] = MIN(low[cur], num[i]);
			// ��ʱ i �Ѿ����ʹ�, ���� low[i] ����û�����
			// ��Ϊ�ڻ��ݵ�ʱ����� low ��
			// ��ջ�е� i ���Ǻ� cur ��ͬһ�������������ϵ�
			// ���п�����ͬһ��ǿ��ͨ, ��ֹ�ѵ�������������
		}
	}
	// �����Ѿ������� cur ������������
	if (low[cur] == num[cur])		// �ҵ�һ����ͨ����
	{
		// ��� low[cur] < num[cur] ˵�����������滹�и������ͨ����
		// ֻ�� low[cur] == num[cur] ʱ, ˵�� cur �պ��ܻص��Լ�
		// low[cur] > num[cur] �������������� == �ų�����
		count++;
		printf("\n{");
		// �� cur �Լ� cur ֮�ϵĵ�ȫ����ջ
		do
		{
			top--;
			printf("%d, ", stack[top]);
			in_the_stack[stack[top]] = 0;
		}
		while (top >= 0 && stack[top] != cur);
		printf("}");
	}
}

int Tarjan(void)
{
	int i;

	number = count = top = 0;
	for (i=0; i<n; i++) 
		in_the_stack[i] = used[i] = 0;
	for (i=0; i<n; i++)		// ����
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
	count = Tarjan();
	printf("\nǿ��ͨ��������: %d\n", count);

	return 0;
}