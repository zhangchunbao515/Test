
// ������ͼ�ĸ��
// ���: ȥ���ñ�, ��ͼ��Ϊ������ͨ��֧
// ������һ��, �õ� num[] ��¼����˳��
// low[] ��¼�ܹ��ص�����С���
// ����һ���� (a, b) ������� low[b] > num[a] (a, b) ���Ǹ��
// ���������, ������ low[b] >= num[a] ��˵�� a �Ǹ��
// ��Ϊ������������ b �ܻص� a �� a �õ�, b ��������͵���
// ��������, ��� b ���ܻص� a ��ô�� (a, b) �õ�. b ���б��� a ����
// ֻ�� b �ز��� a ��, �� low[b] > num[a] (a, b) ���Ǹ��

#include <stdio.h>

#define NUM 60
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int m[NUM][NUM];		// �ڽӾ���
int n;
int used[NUM];			// ���ʱ��
int num[NUM];			// ����˳��
int number;
int low[NUM];			// ��С�ص�
int count;

// ���ҵ�����֧�еĸ��, �������Ļ, Ҳ�ɱ��浽������
void DFS(int cur)
{
	int i;

	used[cur] = 1;
	num[cur] = low[cur] = number++;
	for (i=0; i<n; i++)
	{
		if (m[cur][i])
		{
			if (!used[i])
			{
				m[i][cur] = 0;			// �����ر�
				// ��ֹ�������ϵ���һ����� low ���µ� cur
				DFS(i);
				low[cur] = MIN(low[cur], low[i]);
				if (low[i] > num[cur])		// �ҵ�һ�����
				{
					count++;
					printf("(%d, %d), ", cur, i);
				}
			}
			else low[cur] = MIN(low[cur], num[i]);
		}
	}
}

int edge(void)		// ����
{
	int i;

	number = count = 0;
	for (i=0; i<n; i++) used[i] = 0;
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
		m[j][i] = 1;
	}
	printf("\n���: ");
	count = edge();
	printf("\n��߸���: %d\n", count);

	return 0;
}