#include <stdio.h>

// �ݹ鷨�� fibonacci ��
__int64 fib(__int64 n)
{
	if (n == 1 || n == 2) return 1;
	else return fib(n-1) + fib(n-2);
}

int main(void)
{
	int n;

	printf("��fibonacci��, ������һ�� n: ");
	scanf("%d", &n);
	if (n <= 0) printf("\n�������!\n");
	else printf("\n���: %ld\n", fib(n));

	return 0;
}