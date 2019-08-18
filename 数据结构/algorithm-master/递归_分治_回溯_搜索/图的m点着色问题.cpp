
// ͼ�� m ����ɫ����, ��ͼ�����ڵĹ��Ҳ�������ͬ����ɫ
// ����һ��ͼ, m ����ɫ, ���������ɫ����

#include <stdio.h>

#define NUM 50
#define NO -1		// ��ɫ

int n;		// n ����
int m;		// m ����ɫ
int k;		// ������
int c[NUM][NUM];
int used[NUM];
int color[NUM];		// ÿ�������ɫ

// �� i �Ž����ɫ, ��ɫ�ɹ����� 1, ʧ�ܷ��� 0
int ok(int cur)
{
	int i;
	int map[NUM];

	for (i=0; i<n; i++) map[i] = 0;
	// ���� i ���ڽӱ�, ��¼ʹ�õ���ɫ
	for (i=0; i<n; i++)
	{
		if (c[cur][i] != 0 && color[i] != NO)
			map[ color[i] ] = 1;
	}
	for (i=0; i<m; i++)
		if (map[i] == 0) break;		// �ҵ�һ����ɫ i �� break
	if (i == m) return 0;
	color[cur] = i;			// �� cur �� i ��ɫ

	return 1;
}

void DFS(int f)
{
	int i;

	if (f == n)
	{
		k++;
		printf("\n�� %d ���:\n", k);
		for (i=0; i<n; i++)
			printf("%d �� %d ��ɫ\n", i, color[i]);
		return ;
	}
	for (i=0; i<n; i++)
	{
		if (!used[i] && ok(i))
		{
			used[i] = 1;
			DFS(f+1);
			color[i] = NO;	// ���������ɫ
			used[i] = 0;
		}
	}
}

void initiaize(int a)	// ��ʼ������
{
	int i, j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++) c[i][j] = 0;
		used[i] = 0;
		color[i] = NO;
	}
	k = 0;
}

int main(void)
{
	int a, b;

	printf("���붥�����: ");
	scanf("%d", &n);
	initiaize(n);			// ��ʼ������
	printf("����߼�: ");
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0) break;
		c[a][b] = 1;
		c[b][a] = 1;
	}
	printf("������ɫ����: ");
	scanf("%d", &m);
	DFS(0);
	if (k == 0) printf("��ɫʧ��, ��ɫ����̫��\n");
	return 0;
}
/*		�����������
5
0 1
0 2
0 3
1 2
1 3
1 4
2 3
3 4
0 0
4

3
0 1
1 2
2 0
0 0
2
*/