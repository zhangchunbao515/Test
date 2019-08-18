
// �� n �Ľ׳�, 

#include <stdio.h>

int num[1000000];		// ÿ��Ԫ�ر��� 5 λ����, ���Ծ���Ϊ 10^5000000
int top;

void calc(int n)
{
	int i, j;
	int tmp, cf = 0;

	top = 0;
	num[top++] = 1;
	if (n == 0 || n == 1) return ;
	for (i=1; i<=n; i++)
	{
		for (j=0; j<top; j++)
		{
			tmp = num[j] * i + cf;
			num[j] = tmp % 100000;
			cf = tmp / 100000;
		}
		// ����н�λ, ����һ�� num[] Ԫ��
		if (cf != 0)
		{
			num[top++] = cf;
			cf = 0;
		}
	}
}

void show(void)
{
	int i;

	printf("%d", num[--top]);
	for (i=top-1; i>=0; i--)
	{
		printf("%05d", num[i]);
	}
	printf("\n");
}

int main(void)
{
	int n;

	while (1)
	{
		printf("���� n: ");
		scanf("%d", &n);
		calc(n);
		show();
	}
	return 0;
}