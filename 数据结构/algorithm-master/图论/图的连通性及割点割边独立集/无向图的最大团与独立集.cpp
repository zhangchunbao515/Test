
// ����ͼ��������������
// ���ʽ���: (�ϸ���� <��ɢ��ѧ>)
// ����ż�: �����ȫ��ͼ, ��ͼ������������ֱ�ӵ���ı�
// ��������: ��ͼ, ĳͼ�е�һ���㼯, �ü����еĵ�, �������㶼��û��ֱ��ߵ�

// ���Ѳ��������, ����ŵĵ㼯�洢�� stack[] ��
// ��֦: ֻ�е�ĳ��, ��ջ��ȫ���ĵ���ֱ���, �ſ�����ջ
// һ��ͼ���޳�������ŵĵ㼯, ʣ�µľ��Ƕ�������
// ��Ϊ����������л��е�������������, ��ô���ᱻ�ѵ�, ���ǳ�Ϊ�����

#include <stdio.h>

#define NUM 60

int m[NUM][NUM];	// �ڽӾ���
int n;
int used[NUM];
int max;			// max ��¼����ŵĶ�����
int stack[200];		// ��¼����ŵ��ӽṹ
int top;
int map[NUM];		// ��ʱ��

inline int ok(int cur)	// ��֦
{
	int i;

	for (i=0; i<top; i++)
	{
		if (m[stack[i]][cur] == 0) return 0;
	}
	return 1;
}

void DFS1(int cur)		// ������Ŷ�����
{
	int i;

	for (i=0; i<n; i++)
	{
		if (!used[i] && m[cur][i] && ok(i))
		{
			used[i] = i;
			stack[top++] = i;
			if (top > max) max = top;
			DFS1(i);		// �����ݹ�
			top--;
			used[i] = 0;
		}
	}
}

void max_graph(void)
{
	int i;

	for (i=0; i<n; i++) used[i] = 0;
	max = -1;
	top = 0;
	DFS1(0);
	printf("\n����Ŷ������: %d\n", max);
	printf("����һ������: \n");
	for (i=0; i<n; i++) map[i] = -1;
	printf("�����: {");
	for (i=0; i<max; i++)
	{
		printf("%d, ", stack[i]);
		map[stack[i]]++;
	}
	printf("}, ������: {");
	for (i=0; i<n; i++)
		if (map[i] == -1) printf("%d, ", i);
	printf("}\n");
}

int main(void)
{
	int i, j;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (!(i || j)) break;
		m[i][j] = 1;
		m[j][i] = 1;	// ����ͼ
	}
	max_graph();
	return 0;
}
/*
5
0 3
3 2
2 1
1 4
4 0
0 1
0 2
0 0
*/