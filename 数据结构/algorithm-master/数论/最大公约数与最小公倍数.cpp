
// ���Լ�� - ŷ������㷨
// gcd(a, b) = gcd(b, a mod b)
// lcm(a, b) = (a * b) / gcd(a, b)

#include <stdio.h>

long int gcd(long int a, long int b)
{
	long int c;

	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

long int lcm(long int a, long int b)
{
	return ((a * b) / gcd(a, b));
}

int main(void)
{
	long int a, b;

	printf("����������: ");
	scanf("%ld %ld", &a, &b);
	printf("\n���Լ��: %ld\n", gcd(a, b));
	printf("��С������: %ld\n", lcm(a, b));

	return 0;
}