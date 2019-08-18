
// ����ͼ���ƥ�� Hopcroft Karp�㷨
// ���㷨���������㷨������:
// �������㷨ÿ����һ������·���з�ת
// HK �㷨ÿ���Ҷ�������·���з�ת

// �㷨����:
// ��ͨ�������ҵ���������·
// ��������Ҳ�������·��, �ͱ�ʾ������
// ��ô��¼��������·��?
// �õ��߶Ⱥ��� h[] ֻ�� h[a] == h[b] + 1 ��ʾ a b ��һ��·�ϵ�

#include <stdio.h>
#include <queue>

#define NUM 80

int m[NUM][NUM];	// ��̬�ڽӱ�
int top[NUM];		// �ڽӱ�β��
int x, y;			// ����ͼ x, y ���ϵĸ���
int xlink[NUM];		// x ����Ӧ��ƥ���
int ylink[NUM];		// y ��ƥ���
int h[NUM];			// �߶Ⱥ���

// ����������·
int BFS(void)
{
	int i, tmp, j;
	std::queue<int> q;
	int flag = 0;

	for (i=0; i<NUM; i++) h[i] = 0;
	for (i=0; i<x; i++)
	{
		if (xlink[i] == -1) q.push(i);
	}	// δƥ��ı����
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (i=0; i<top[tmp]; i++)		// ���� tmp �ڽӵ�
		{
			j = m[tmp][i];
			if (h[j] == 0)
			{
				h[j] = h[tmp] + 1;
				if (ylink[j] == -1) flag = 1;	// �ҵ���һ������·
				else 
				{
					// ��� j [ƥ���, ���±�ƥ��ĵ�
					h[ylink[j]] = h[j] + 1;
					q.push(ylink[j]);
				}
			}
		}
	}
	return flag;
}

// ���Ѳ�������·, һ��·�ϵĵ�߶ȵ��� 1
int DFS(int cur)
{
	int i, j;

	for (i=0; i<top[cur]; i++)
	{
		j = m[cur][i];
		if (h[j] == h[cur] + 1)
		{
			h[j] = -1;		// ��Ƿ�����
			if (ylink[j] == -1 || DFS(ylink[j]))
			{
				ylink[j] = cur;
				xlink[cur] = j;
				return 1;
			}
		}
	}
	return 0;
}

int HK(void)
{
	int count = 0;
	int i;

	for (i=0; i<NUM; i++)
		xlink[i] = ylink[i] = -1;
	while (BFS())
	{
		for (i=0; i<x; i++)		// �� x ������
		{
			if (xlink[i] == -1 && DFS(i)) count++;
		}	// δƥ��ĵ㳢��ƥ��
	}
	return count;
}

int main(void)
{
	int i, j;

	printf("���� x, y ���ϵĶ������: ");
	scanf("%d %d", &x, &y);
	for (i=0; i<x; i++) top[i] = 0;
	// ����߼���ʱ��, Ĭ��������������������
	while (1)
	{
		scanf("%d %d", &i, &j);
		if (!(i || j)) break;
		m[i][top[i]++] = j;
	}
	printf("\n���ƥ����: %d\n", HK());
	printf("ƥ���: ");
	for (i=0; i<x; i++)
	{
		if (xlink[i] != -1)
			printf("(%d, %d), ", i, xlink[i]);
	}
	putchar('\n');
	return 0;
}
