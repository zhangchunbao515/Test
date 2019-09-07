
// Tarjan �㷨��һ�������㷨, ���������ȫ�������, �� LCA ���鱣��
// Ȼ����� O(1) �Ļش�ÿ�� LCA(a, b)

#include <stdio.h>

#define NUM 500

int tree[NUM];			// ������
int n;					// �����
int num[NUM];			// ����
int top;
int parent[NUM];		// ���鼯˫��
int check[NUM];			// ���Ʒ��ʱ��
int ancestor[NUM];		// ���ϵ��������
int LCA[NUM][NUM];		// ���� LCA ���

void create(int pos)		// ���� num[] ���� tree[]
{
	tree[pos] = num[top++];
	if (tree[pos] != -1)
	{
		n++;		// ��¼�����
		create(2 * pos);
		create(2 * pos + 1);
	}
}

void initialize(void)		// ���� n ��ʼ�����鼯
{
	int i;

	for (i=0; i<n; i++) 
	{
		parent[i] = i;
		check[i] = 0;
	}
}

// ���Ҽ���ʱ, ͬʱѹ��·��
int find_set(int cur)
{
	int stack[100];		// ע��ջ��С
	int t = 0;

	while (parent[cur] != cur)
	{
		stack[t++] = cur;
		cur = parent[cur];
	}
	while (t != 0)
	{
		parent[stack[--t]] = cur;
	}
	return cur;
}

// �ϲ�����: �� b �ϲ��� a ���ڵļ���
void union_set(int a, int b)
{
	int ra, rb;

	ra = find_set(a);
	rb = find_set(b);
	if (ra != rb)
	{
		parent[rb] = ra;
	}
}

// ���Ѵ���
void tarjan(int cur)
{
	int i;
	int child = 2 * cur;
	int set;

	set = find_set(tree[cur]);
	ancestor[set] = tree[cur];
	// ��������, �����������������
	for (i=child; i<child+2; i++)
	{
		if (tree[i] > 0)		// tree[i] ��㲻Ϊ��
		{
			tarjan(i);
			union_set(tree[cur], tree[i]);		// �ϲ�����
		}
	}
	// �� tree[cur] ���ڵļ��ϵ����ȱ��Ϊ tree[cur] 
	// Ȼ��ش����� LCA[ tree[cur] ][i] �Ĳ�ѯ
	set = find_set(tree[cur]);
	ancestor[set] = tree[cur];
	check[tree[cur]] = 1;		// ����ʱ, ��Ǽ�����
	for (i=0; i<n; i++)
	{
		if (check[i])		// i �������
		{
			set = ancestor[find_set(i)];
			LCA[tree[cur]][i] = set;
			LCA[i][tree[cur]] = set;
		}
	}
}

int main(void)
{
	int a, b;

	// �����������뷽ʽ, -1 ��ʾ����, -2 ��ʾ�������
	// ��������: 0 1 3 -1 -1 4 5 -1 -1 6 -1 -1 2 7 -1 -1 8 -1 -1 -2
	// ���Ҫ�����, �� 0 ��ʼ����
	printf("����һ����: ");
	top = 0;
	while (1)
	{
		scanf("%d", num + top);
		if (num[top] == -2) break;
		top++;
	}
	n = top = 0;
	create(1);			// ��ʼ����
	initialize();		// ��ʼ�����鼯, ���ʼ�¼
	tarjan(1);			// ����ȫ����ѯ, ��¼�� LCA[][]
	printf("LCA ��ѯ:\n");
	while (1)
	{
		scanf("%d %d", &a, &b);
		printf("�����������: %d\n", LCA[a][b]);
	}
	return 0;
}