
// Ⱦɫ���ж϶���ͼ
// ѡһ����Ⱦ�ɰ�ɫ, �Ӹõ㷢��һ������
// �����ڽӵ�Ⱦ���෴�ĺ�ɫ
// �������ڽӵ��ǰ�ɫ, ���ʾ���Ƕ���ͼ
// ֱ�����ѽ���, ���Ƕ���ͼ

#include <stdio.h>
#include <queue>

#define NUM 50			// ��󶥵���
#define WRITE 0			// ��ɫ
#define BLACK 1			// ��ɫ
#define NO -1			// ��ûȾɫ

int color[NUM];			// �����ɫ

// ���ѡһ����, ���й���Ⱦɫ
// �˴ι��Ѳ���Ҫ used[] ���ʱ��, ��Ϊû��Ⱦ��ɫ�ľ���û���ʵ�
int BFS(short int (*m)[NUM], int n)
{
	int i;
	int result;
	int BFS_s(short int (*m)[NUM], int n, int i);	// ��ͨ������ͨ��֧

	for (i=0; i<n; i++) color[i] = NO;		// ûȾɫ
	for (i=0; i<n; i++)
	{
		if (color[i] == NO) result = BFS_s(m, n, i);
		if (result == 0) return 0;		// ����ʧ��
	}
	return 1;
}

// �жϵ�����ͨ��֧
int BFS_s(short int (*m)[NUM], int n, int i)
{
	std::queue<int> q;
	int tmp, j;
	int c;

	color[i] = WRITE;		// �״�Ⱦ��ɫ
	q.push(i);
	while (!q.empty())
	{
		tmp = q.front();   q.pop();
		c = color[tmp] == WRITE ? BLACK : WRITE;
		// c ȡ�෴����ɫ
		for (j=0; j<n; j++)
		{
			if (m[tmp][j] == 1)		// �����·
			{
				if (color[j] == NO)		// δȾ��
				{
					color[j] = c;
					q.push(j);
				}
				else if (color[j] == color[tmp]) 
					return 0;			// ��ɫ��ͻ
			}
		}
	}
	return 1;
}

int main(void)
{
	short int m[NUM][NUM];		// �ڽӾ���
	int n;
	int i, j;
	int a, b;

	printf("���붥����: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<n; j++) m[i][j] = 0;
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		m[a][b] = m[b][a] = 1;
	}
	if (BFS(m, n))
	{
		printf("\n���Ƕ���ͼ");
		printf("\n A ��: ");
		for (i=0; i<n; i++)
			if (color[i] == WRITE) 
				printf("%d, ", i);
		printf("\n B ��: ");
		for (i=0; i<n; i++)
			if (color[i] == BLACK) 
				printf("%d, ", i);
	}
	else printf("\n���Ƕ���ͼ");
	putchar('\n');

	return 0;
}
