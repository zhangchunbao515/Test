
// ��������ͼ�ĸ��
// ���: ɾ���õ�, ��ͼ��Ϊ������ͨ��֧

// <���ݽṹ> �϶���, 
// 1. ���һ�������ܷ��ʵ�ȫ���Ľ��, ���ø��ж�ò��໥��ͨ������
// ��ô�Ѹø�ȥ��, ����ͨ��������Ϊ�����ͨ��֧
// 2. ���һ���� k, ����һ������, ���ܻص��ȸ�����Ľ��
// ��ô�ø���һ�����, ��Ϊȥ���õ�, ĳ��������Ϊ�����ķ�֧

// ��ԭͼ����һ������, ��¼ÿ����ķ���˳�� count[]
// ��Ȼ�������ȷ��ʵ�, ���Ը��� count[] ����С��
// ��Ȼ�Ӹ�������һ��Ҷ�ӵ�·����, count[] �ǵ�����
// ��������һ����� k �������� count[] ����� k С
// ���� low[] ����ʾÿ������ܹ��ص� count[] ��С���
// ��� k ����һ������ v , �����ܻص��� count[k] ��ҪС�ĵط�
// �� low[v] >= count[k], ��ô�� k �õ�, ���������Ϊ��������ͨ��֧
// �� k ��һ�����

#include <stdio.h>

#define NUM 60

int m[NUM][NUM];	// �ڽӾ���
int n;
int used[NUM];
int count[NUM];		// ���ѷ���˳��
int num;			// ���
int low[NUM];		// �ɴ����С����
int map[NUM];		// map �м�¼�Ѿ���õĸ��

void DFS(int cur)		// ����, ��ͨ������ͨ��֧
{
	int i;

	used[cur] = 1;
	low[cur] = count[cur] = num++;
	for (i=0; i<n; i++)
	{
		if (m[cur][i])
		{
			if (!used[i])
			{
				DFS(i);
				if (low[i] < low[cur])
					low[cur] = low[i];
				// i �� cur ������
				// i �ܻص�����С���, û��С�� cur
				// ��ʱ cur ����һ�����, ��¼�� map ��
				if (low[i] >= count[cur])
					map[cur] = 1;
			}
			else if (count[i] < low[cur])
				low[cur] = count[i];
			// ��ʱ i �Ѿ����ʹ�, 
			// ������ low[i] ��û�����
			// ���Կ��ܵ���� count ��С
		}
	}
}

void tarjan(void)		// tarjan ����
{
	int i;
	int root = 0;		// ���ѡһ�����������������ĸ�

	for (i=0; i<n; i++)		// ��ʼ��
	{
		map[i] = count[i] = used[i] = 0;
		low[i] = 0XFFFFFF;
	}
	num = 0;
	used[root] = 1;			// ��ʼ����
	low[root] = count[root] = num++;

	for (i=0; i<n; i++)		// ���� root ��һ������
	{
		if (m[root][i])
		{
			DFS(i);
			break;
		}
	}
	if (num < n)	// û�з�����ȫ���ĵ�, ��ʱ root �Ǹ��
	{
		map[root] = 1;
		for (i=0; i<n; i++)		// ��ʣ��ķ�����
		{
			if (!used[i] && m[root][i]) DFS(i);
		}
	}
}

int main(void)
{
	int i, j;
	int zero;

	printf("���붥�����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (!(i || j)) break;
		m[i][j] = 1;
		m[j][i] = 1;
	}
	tarjan();
	printf("\n��㼯: ");
	for (zero=i=0; i<n; i++)
	{
		if (map[i]) printf("%d, ", i);
		zero += map[i];		// zero ���� 0 ����
	}
	if (zero == 0) printf("�޸��");
	putchar('\n');

	return 0;
}