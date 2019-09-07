
// ����, ��һ��ͼ�Ĵ��ݱհ�
// ���ݱհ�: �������ٵı�, ʹ�ø�ͼ���д�����

#include <stdio.h>
#include <queue>

#define NUM 60

// ����
void BFS(int (*m)[NUM], int cur, int n)
{
	std::queue<int> q;
	int used[NUM];
	int i, tmp;

	for (i=0; i<n; i++) used[i] = 0;
	q.push(cur);
	// used[cur] = 1;	// �þ仰������, ��Ϊ�п��ܴ��ݵ��Լ� (�Է���)
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (i=0; i<n; i++)
		{
			if (!used[i] && m[tmp][i] == 1)
			{
				q.push(i);
				used[i] = 1;
				m[cur][i] = 1;		// �����·
			}
		}
	}
}

// ��ÿһ����, ����һ������, ��ͨ�����ѵ��ĵ�
// ��Ϊ�д����Բ��ܴﵽ�õ�, �����˸õ�, ˵������
void solve(int (*m)[NUM], int n)
{
	int i;
	for (i=0; i<n; i++) BFS(m, i, n);
}

int main(void)
{
	int m[NUM][NUM];		// �ڽӾ���
	int n;
	int a, b;
	int i, j;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		m[a][b] = 1;		// ����ͼ
	}
	// �󴫵ݱհ�, ����֮�� m[][] ���޸�
	solve(m, n);
	printf("\n���ݱհ�:\n");
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++) 
			printf("%3d ", m[i][j]);
		putchar('\n');
	}
	return 0;
}
/*
4
0 1
1 2
2 3
3 2
0 2
0 0
*/