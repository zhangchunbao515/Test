
// �ж�ŷ����·, �����, ���һ��ŷ����·
// ŷ��ͨ·: ���еı�ֻ�ܾ���һ��, �������б�
// ŷ����·: ���еı�ֻ�ܾ���һ��, �������б�, �һص�ԭ��
// ��ϸ����� <��ɢ��ѧ>

#include <stdio.h>

#define NUM 60

int type;		// ��־ͼ������
int n;
int m[NUM][NUM];
int degree[NUM];		// ����ͼ�Ķ���
int used[NUM];
int in[NUM], out[NUM];	// ����ͼ����ȳ���
int stack[100];			// ��¼·��
int top;
int e;			// ����

void DFS(int cur)
{
	int i;

	for (i=0; i<n; i++)
	{
		if (!used[i] && m[cur][i])
		{
			used[i] = 1;
			DFS(i);
		}
	}
}

// �ж��Ƿ����ŷ����·:
// ����ͼ��: ��ͨͼ�����ж������Ϊż��
// ����ͼ��: ��ͨͼ�����ж������ȵ��ڳ���
int judge(void)
{
	int i;

	// ���Ѽ����ͨ��
	for (i=0; i<n; i++) used[i] = 0;
	DFS(0);
	for (i=0; i<n; i++) 
		if (!used[i]) return 0;

	if (type)		// ����ͼ, ��ȵ��ڳ���
	{
		for (i=0; i<n; i++)
			if (in[i] != out[i]) return 0;
	}
	else		// ����ͼ, ����Ϊż��
	{
		for (i=0; i<n; i++)
			if (degree[i] % 2) return 0;
	}
	return 1;
}

// ����ͼ��ŷ����·, �� cur ��, �� pos �㿪ʼ��
void DFS1(int cur, int pos)
{
	int i, a, b;

	stack[top++] = cur;
	for (i=pos; i<n; i++)
	{
		if (m[cur][i] != 0)
		{
			m[cur][i] = 0;
			out[cur]--;
			in[i]--;
			DFS1(i, 0);
			break;
		}
	}
	// ��Ͷ��·, ���һ��бߵ�ʱ��, �˻�һ��
	if (i == n && top < e)
	{
		b = stack[--top];
		a = stack[--top];
		m[a][b] = 1;		// �ָ���
		out[a]++;
		in[b]++;
		DFS1(a, b + 1);		// ����һ����ʼ��
	}
}

// ����ͼ��ŷ����·, cur ��, �� pos �㿪ʼ��
void DFS2(int cur, int pos)
{
	int i, a, b;

	stack[top++] = cur;
	for (i=pos; i<n; i++)
	{
		if (m[cur][i] != 0)
		{
			m[i][cur] = 0;
			m[cur][i] = 0;
			degree[cur]--;
			degree[i]--;
			DFS2(i, 0);
			break;
		}
	}
	if (i == n && top < e)		// �˻�һ��
	{
		b = stack[--top];
		a = stack[--top];
		m[a][b] = 1;
		m[b][a] = 1;
		degree[a]++;
		degree[b]++;
		DFS2(a, b + 1);		// ����һ����ʼ��
	}
}

int main(void)
{
	int i;
	int a, b;

	printf("0, ����ͼ    1, ����ͼ : ");
	scanf("%d", &type);
	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		in[i] = out[i] = 0;
		degree[i] = 0;
	}
	e = top = 0;
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (!(a || b)) break;
		m[a][b] = 1;
		in[b]++;		// ˳��ͳ�ƶ���
		out[a]++;
		e++;
		if (!type)		// ���������ͼ
		{
			m[b][a] = 1;
			degree[a]++;
			degree[b]++;
		}
	}
	if (judge())
	{
		// ���һ��ŷ����·
		printf("\nһ��ŷ����·: ");
		if (type) 
			DFS1(0, 0);
		else 
			DFS2(0, 0);
		for (i=0; i<top; i++)
		{
			printf("%d", stack[i]);
			if (i + 1 != top) printf(" -> ");
		}
		putchar('\n');
	}
	else printf("\n������ŷ����·!\n");

	return 0;
}