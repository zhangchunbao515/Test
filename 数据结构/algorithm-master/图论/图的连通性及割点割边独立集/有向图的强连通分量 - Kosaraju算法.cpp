
// ��������ͼ��ǿ��ͨ���� Kosaraju �㷨
// ���ʽ���: (�ϸ���� <��ɢ��ѧ>)
// ǿ��ͨ���� : ����ͨ��������������֮�䶼�ǿɴ��
// ��ͼ: ��ԭͼ�ı�ȡ��, ���Ը�ͼ�ڽӾ���ת��

// �㷨����ԭ��: ��ԭͼ��, a, b��Ϊ�ɴ�, ���ҽ�����ͼ��, a, b��Ϊ�ɴ�
// ���ԭͼ�� a -> b �ɴ�, �ڷ�ͼ����� a -> b Ҳ�ɴ�
// ��ô a, b ����ͬһ��ǿ��ͨ������
// ����ԭͼ��ͼ�ж� DFS(a), ���ζ������ʵ��ĵ㼴��һ��ǿ��ͨ
// ���� a ��������˳����, ����������, ���ܻص� a, ��ô�����ĵ���ǿ��ͨ��
// a Ҫ��ĳ������������, ��Ȼ�ѵ���ֻ���� a Ϊ���ķ���, ������
// ����Ҫ�� stack[] ��¼��������
// ����ĳ��ͼ�ѵ����ĸ�����: a, b, c, d
// ��ԭͼ�� a -> b ����·��, ��Ϊ��·�Ļ�, a, b Ҳ���ᱻ�����������
// ���ǲ��ܱ�֤��ͼ�� b -> a ��·, ����ԭͼ�� b -> a ��·
// ��ô�ڷ�ͼ�� a -> b ����·, ������ a �Ļ�, ���ѵ� b ������, ����Ȼ����
// ����Ҫ�� stack[] ��¼ a, b, c, d, Ȼ������ d, c, b, a ������

// Kosaraju �㷨:
// ��ԭͼ����һ������, ��¼���������˳��
// ��������и�λ�����, ����������ĺ������
// �Ӻ���ǰѡ���Ӹ��Է�ͼ��������, ���ҵ��ĵ����һ��ǿ��ͨ����
// ������������ a, b, c, ��ô�Է�ͼ����ʱ, ���� c, b, a ��˳��

#include <stdio.h>
#include <string.h>

#define NUM 60

int m[NUM][NUM];		// �ڽӾ���, ԭͼ
int fm[NUM][NUM];		// �ڽӾ���, ��ͼ
int n;					// ������
int used[NUM];			// ���ʱ��
int father[NUM];		// ��¼������ͨ����
int stack[100];			// ��¼�����������
int top;

void DFS1(int cur)		// ԭͼ����, ��¼ stack[]
{
	int i;

	used[cur] = 1;
	for (i=0; i<n; i++)
	{
		if (!used[i] && m[cur][i] != 0)
			DFS1(i);
	}
	stack[top++] = cur;		// ��¼����, ����ʱ��¼ cur
}

void DFS2(int cur, int root)	// ��ͼ����, ��¼������ͨ����
{
	int i;

	used[cur] = 1;
	father[cur] = root;		// ��¼��������
	for (i=0; i<n; i++)
	{
		if (!used[i] && fm[cur][i] != 0)
			DFS2(i, root);
	}
}

// ���������ͨ��������, father[] �д�����������, �е㲢�鼯��ζ��
int kosaraju(void)
{
	int count = 0;	// ��¼��ͨ����
	int i;

	memset(used, 0, sizeof(used));
	memset(father, 0, sizeof(father));
	top = 0;
	for (i=0; i<n; i++)		// ��ԭͼ����, ��¼��������
	{
		if (!used[i]) DFS1(i);
	}
	memset(used, 0, sizeof(used));
	for (i=top-1; i>=0; i--)	// �Ӻ���ǰ�������ĸ�
	{
		if (!used[stack[i]])
		{
			DFS2(stack[i], count);
			count++;
		}
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
			fm[i][j] = m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (i == 0 && j == 0) break;
		m[i][j] = 1;		// ԭͼ
		fm[j][i] = 1;		// ��ͼ
	}
	count = kosaraju();
	printf("\nǿ��ͨ��������: %d\n", count);
	for (i=0; i<count; i++)
	{
		printf("{");
		for (j=0; j<n; j++)
			if (father[j] == i) printf("%d, ", j);
		printf("}\n");
	}
	return 0;
}