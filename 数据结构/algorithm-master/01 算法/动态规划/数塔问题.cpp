#include <stdio.h>
#include <string.h>

void copy(int (*d)[30], int (*s)[30], int n)
{
	int i, j;
	for (i=0; i<n; i++)
		for (j=0; j<=i; j++)
			d[i][j] = s[i][j];
}

void dp(int (*ta)[30], int n, int *stack, int *top, int *sum)
{
	int i, j;
	int tmp[30][30];		// �����������
	int pos;
	int max = -0xFFFFF;
	int max_pos[30];
	int a, b;

	copy(tmp, ta, n);
	*top = *sum = 0;
	for (i=n-2; i>=0; i--)		// i ���Ʋ���, �ݼ�
	{
		for (j=0; j<=i; j++)
		{
			if (tmp[i+1][j] > tmp[i+1][j+1])
				pos = 0;		// ��
			else pos = 1;		// ��
			tmp[i][j] += tmp[i + 1][j + pos];
			if (tmp[i][j] > max) 
			{
				max = tmp[i][j];
				max_pos[i] = j;
			}
		}
		// ��¼·��, �����Ӷκ�
		a = tmp[i+1][max_pos[i]];   b = tmp[i+1][max_pos[i] + 1];
		stack[(*top)++] = a > b ? 
			ta[i+1][max_pos[i]] : ta[i+1][max_pos[i] + 1];
	}
	stack[(*top)++] = ta[0][0];
	*sum = tmp[0][0];
}

int main(void)
{
	int ta[30][30];		// ����, ջ�ռ����ʵ�ʷ���
	int stack[50];		// ��¼·��
	int top = 0;
	int max = 0;		// ��¼����
	int n, i, j;

	printf("���� n, �� n ����������: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		for (j=0; j<=i; j++)
			scanf("%d", &(ta[i][j]));
	dp(ta, n, stack, &top, &max);
	printf("\n����: %d\n·��: ", max);
	while (top)
		printf(" -> %d", stack[--top]);
	printf("\n");
	return 0;
}
