
// ������ P(3, 5) = 5 * 4 * 3
// ����� C(3, 5) = p(3, 5) / p(3, 3)

#include <stdio.h>

int P(int a, int b)
{
	int ans = 1;

	while (a)
	{
		ans *= b;
		a--;
		b--;
	}
	return ans;
}

int C(int a, int b)
{
	return P(a, b) / P(a, a);
}

int main(void)
{
	int a, b;

	printf("����������: ");
	scanf("%d %d", &a, &b);
	printf("������ %d, �����%d\n", P(a, b), C(a, b));

	return 0;
}