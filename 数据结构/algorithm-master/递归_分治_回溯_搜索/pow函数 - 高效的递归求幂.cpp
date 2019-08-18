#include <stdio.h>

// �� x^n
// ��ͨ����: x �Գ� n-1 ��, ���Ӷ� O(n)
// ���ù�ʽ, ��� n ��ż�� x^n = x^(n/2) * x^(n/2) = (x * x)^(n / 2)
// ��� n ������ x^n = x^((n-1)/2) * x^((n-1)/2) * x = (x * x)^((n-1)/2) * x
// ���ӶȽ��� O(log n) �ݹ��������

// �� x^n ʱ�临�Ӷ� O(log n)
double pow(int x, int n)
{
	if (n == 0) return 1;
	else if (n == 1) return x;
	else if (n % 2 == 0) return pow(x * x, n/2);
	else return pow(x * x, n/2) * x;
}

int main(void)
{
	int x, n;

	printf("���������ָ��: ");
	scanf("%d %d", &x, &n);
	printf("\n���: %0.lf\n", pow(x, n));

	return 0;
}
