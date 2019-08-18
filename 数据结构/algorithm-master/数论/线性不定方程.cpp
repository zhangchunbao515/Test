
// ���Բ������� ax + by = c
// ���� a, b, c, ��� x, y

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

// ��չ��ŷ������㷨, ��ϸ֤�����㷨���� 528 ҳ
void extand_gcd(int a, int b, int &d, int &x, int &y)
{
	if (b == 0) {d = a;  x = 1;  y = 0; }
	else 
	{
		extand_gcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}

// ���� ax + by = c
int calc(int a, int b, int c, int &x, int &y)
{
	int d = gcd(a, b);

	// c Ҫ�� gcd(a, b) �ı���, �����޽�
	// ��, �� a, b ������������� c ����
	if (c % d != 0) return 0;

	// �� ax + by = c ת��Ϊ ax + by = d ����
	extand_gcd(a, b, d, x, y);
	c /= d;
	x *= c;   y *= c;
	return 1;
}

int main(void)
{
	int a, b, c, x, y;

	while (1)
	{
		printf("���� a, b, c: ");
		scanf("%d %d %d", &a, &b, &c);
		if (calc(a, b, c, x, y))
			printf("x = %d   y = %d\n\n", x, y);
		else 
			printf("�����޽�!\n\n");
	}
	return 0;
}