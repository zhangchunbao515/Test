#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define INF INT_MAX

typedef struct		// ��̬��ά����
{
	int **m;
	int x;
	int y;
}suzhu;

typedef struct		// ά�� (x * y)
{
	int x;
	int y;
}matrix;

void create(suzhu *n, int x, int y)
{
	int i, j;

	n->x = x;   n->y = y;
	n->m = (int **)malloc(x * sizeof(int *));
	for (i=0; i<x; i++)
	{
		n->m[i] = (int *)malloc(y * sizeof(int));
		for (j=0; j<y; j++) n->m[i][j] = 0;		// ��ʼ��
	}
}

void destroy(suzhu *n)
{
	int i;

	if (n->m == NULL) return ;
	for (i=0; i<n->x; i++)
		free(n->m[i]);
	free(n->m);
	n->m = NULL;
}

void show(suzhu *n)
{
	int i, j;

	for (i=0; i<n->x; i++)
	{
		for (j=0; j<n->y; j++)
		{
			if (i > j) printf("%8c,", '-');
			else printf("%8d,", n->m[i][j]);
		}
		printf("\n");
	}
}

int ok(matrix *m, int n)		// ����ɳ˼��
{
	int i;

	for (i=1; i<n; i++)
		if (m[i-1].y != m[i].x) return 0;
	return 1;
}

// ��������, m ��¼����ά��, c ��¼��˴���, p ��¼λ��
void dp(matrix *m, int n, suzhu *c, suzhu *p)
{
	int i, j, k;
	int tmp;
	int end;

	// �Լ����Լ������ 0 ��
	for (i=0; i<n; i++) p->m[i][i] = c->m[i][i] = 0;
	for (i=1; i<n; i++)		// i ���ƴ���
	{
		for (j=0; j<n-i; j++)
		{
			end = j + i;			// ����ĩβ [j .. end]
			c->m[j][end] = INF;		// ���ű�ĳ�ʼ��
			p->m[j][end] = j + 1;
			for (k=j; k<end; k++)		// k �� j..end �����ж�
			{
				tmp = c->m[j][k] + c->m[k+1][end] 
					+ m[j].x * m[k+1].x * m[end].y;
				if (tmp < c->m[j][end])
				{
					c->m[j][end] = tmp;
					p->m[j][end] = k + 1;
				}
			}
		}
	}
}

int main(void)
{
	suzhu count, pos;
	int i, n;
	matrix m[50];		// ��� 50 ���������

	printf("���� n, �� n �������ά��: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		scanf("%d %d", &(m[i].x), &(m[i].y));

	create(&count, n, n);		// ��¼��˴���
	create(&pos, n, n);		// ��¼�����ŵ�λ��
	if (!ok(m, n)) { printf("���󲻿ɳ�!\n");  return 0;}

	dp(m, n, &count, &pos);		// DP

	printf("\n�������˴�����: \n");
	show(&count);
	printf("\n������λ��: \n");
	show(&pos);

	destroy(&count);
	destroy(&pos);
	return 0;
}
