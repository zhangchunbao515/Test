
// ������ x �� a[] (mod m[]), ���� m[] ��������
// ���� n, a[], m[] ���һ�� x, 

#include <stdio.h>

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
	if (b == 0) { d = a;  x = 1;  y = 0; }
	else 
	{
		extand_gcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}

// ��ģ���Է�����, 
int calc(int *a, int *m, int n, int &M)
{
	int i, w, d, x = 0, y;

	M = 1;
	for (i=0; i<n; i++) M *= m[i];
	for (i=0; i<n; i++)
	{
		w = M / m[i];
		extand_gcd(m[i], w, d, d, y);
		x = (x + y * w * a[i]) % M;
	}
	return (x + M) % M;
}

int main(void)
{
	int a[100];
	int m[100];
	int n, i, x, M;

	while (1)
	{
		printf("���뷽����ĸ��� n: ");
		scanf("%d", &n);
		printf("����a[] :");
		for (i=0; i<n; i++)
			scanf("%d", a + i);
		printf("����m[] :");
		for (i=0; i<n; i++)
			scanf("%d", m + i);
		x = calc(a, m, n, M);
		printf("���: %d + %dk\n\n", x, M);
	}
	return 0;
}