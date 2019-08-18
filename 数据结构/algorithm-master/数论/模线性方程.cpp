
// ���ģ���Է��� ax �� b(mod n)
// ���� a, b, n, ������е� x ��

#include <stdio.h>

int stack[100];
int top;

int gcd(int a, int b)		// ���Լ��
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

// ��չ��ŷ������㷨
void extand_gcd(int a, int b, int &d, int &x, int &y)
{
	if (b == 0) {d = a;  x = 1;  y = 0; }
	else 
	{
		extand_gcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}

// ���� ax �� b(mod n), ������� stack ��
void calc(int a, int b, int n)
{
	int d = gcd(a, b);
	int i, x, y;

	top = 0;
	extand_gcd(a, n, d, x, y);
	if (b % d != 0) return ;

	x = x * (b / d) % n;
	for (i=1; i<d; i++)
		stack[top++] = x + i * (n / d);
}

int main(void)
{
	int a, b, n;

	while (1)
	{
		printf("���� a, b, n: ");
		scanf("%d %d %d", &a, &b, &n);
		calc(a, b, n);
		if (top)
		{
			printf("���: ");
			while (top) printf("%d, ", stack[--top]);
			printf("\n\n");
		}
		else printf("�����޽�!\n\n");
	}
	return 0;
}