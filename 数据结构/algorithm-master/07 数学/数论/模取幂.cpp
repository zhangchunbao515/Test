
// ģȡ��, �� a^n mod p ��ֵ

// �㷨1: ���ù�ʽ: (a * b) mod m = (a mod m) * (b mod m) mod m
// a^n = a^(n-1) * a
// ����: a^n mod p = ((a^(n-1) mod p) * a mod p) mod p
//       a^(n-1) mod p = ((a^(n-2) mod p) * a mod p) mod p
// ���� n �ε���, ʱ�临�Ӷ� O(n)

// �㷨2: �� n �ö����Ʊ�ʾ, ��Ȩչ��
// ���� a^6 mod p,  6 = (110)B = 1*2^2 + 1*2^1 + 0*2^0
// ���� a^(1*2^2 + 1*2^1 + 0*2^0) = (a^1*2^2) * (a^1*2^1) * (a^0*2^0)
// �����ù�ʽ: (a * b) mod p = ((a mod p) * b) mod p ���е���
// 6 �� 110 ������λ, ���� 3 ��
// n �� log n ��λ, ʱ�临�Ӷ� O(log n)

#include <stdio.h>
#include <time.h>

// �㷨1
int calc(int a, int n, int p)
{
	int r = 1;		// r = a^0 = 1
	int i;

	for (i=0; i<n; i++)
	{
		r = (r % p * a % p) % p;
	}
	return r;
}

// �㷨2
int calc2(int a, int n, int p)
{
	int r = 1;
	long int d = a % p;
	// d Ϊ a �� 2^i �η�ģ p �Ľ��
	// d2 = (d1 * d1) % p;

	while (n)
	{
		if (n & 1) r = (r * d) % p;
		d = (d * d) % p;
		n >>= 1;
	}
	return r;
}

int main(void)
{
	int a, n, p;
	int t, t1, t2;

	while (1)
	{
		printf("������� a: ");
		scanf("%d", &a);
		printf("����ָ�� n: ");
		scanf("%d", &n);
		printf("���� p: ");
		scanf("%d", &p);
		t1 = clock();
		t = calc(a, n, p);
		t2 = clock();
		printf("\n���: %d\nO(n) ����ʱ: %d ms\n", t, t2 - t1);
		t1 = clock();
		t = calc2(a, n, p);
		t2 = clock();
		printf("\n���: %d\nO(log n) ����ʱ: %d ms\n\n", t, t2 - t1);
	}
	return 0;
}