
// ������Ӿ����
// ��������Ӷκ��ƹ�, ����ӶκͿɿ����� 1 * n �ľ���
// m * n �ľ����Ƚ���ѹ���� 1 * n �ľ���, �����Ӷκ͵ķ������
// ѹ���������ǰ� m �����
// ��         9   2   -6   2
//           -4   1   -4   1
// �������   5   3   -10  3     �Դ�������
// ö�� m * n ��, m �е�ѹ�����

#include <stdio.h>
#include <malloc.h>

#define MAX 200

// ������Ӷκ�
int max_sum(int *a, int n, int *s, int *e)
{
	int max = 0;
	int i;
	int sum = -0XFFFFF;

	*s = *e = 0;
	for (i=0; i<n; i++)
	{
		if (max > 0) max += a[i];
		else { max = a[i];   *s = i; }		// ͬʱ������� s
		if (max > sum) { sum = max;  *e = i; }
	}
	return sum;
}

// ������Ӿ����, (a, b) �� (c, d) ���Ӿ���
int dp(int (*m)[MAX], int x, int y, 
	   int *a, int *b, int *c, int *d)
{
	int i, j, k;
	int *buf;
	int sum = -0XFFFFF;
	int tmp;
	int s, e;	// �Ӷκ͵ķ�Χ [s..e]

	*a = *b = *c = *d = 0;
	buf = (int *)malloc(y * sizeof(int));
	for (i=0; i<x; i++)		// ö����ʼ��
	{
		for (j=0; j<y; j++) buf[j] = 0;
		for (j=i; j<x; j++)		// ����ʼ�����һ��
		{
			// �����ۼӵ� j ��
			for (k=0; k<y; k++) buf[k] += m[j][k];
			tmp = max_sum(buf, y, &s, &e);
			if (tmp > sum) 
			{
				sum = tmp;
				*a = i;   *c = j;	// ��¼ i �е� j ��
				*b = s;   *d = e;	// ��¼ s �е� e ��
			}
		}
	}
	free(buf);
	return sum;
}

int main(void)
{
	int m[MAX][MAX];
	int sum;
	int i, j;
	int x, y;		// �����С (x * y)
	int a, b, c, d;		// �Ӿ��� (a, b) �� (c, d)

	printf("����һ������: ");
	scanf("%d %d", &x, &y);
	for (i=0; i<x; i++)
		for (j=0; j<y; j++) scanf("%d", &(m[i][j]));
	sum = dp(m, x, y, &a, &b, &c, &d);
	printf("\n�Ӿ�������: %d\n�Ӿ���:\n", sum);
	for (i=a; i<=c; i++)
	{
		for (j=b; j<=d; j++) printf("%5d", m[i][j]);
		printf("\n");
	}
	printf("\n");
	return 0;
}
