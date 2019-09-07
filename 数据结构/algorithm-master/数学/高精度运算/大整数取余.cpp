
// ��ʽ1: (a * b) mod m = ((a mod m) * (b mod m)) mod m
// ��ʽ2: (a + b) mod m = ((a mod m) + (b mod m)) mod m
// ��������� p, ���� m, �� p mod m

#include <stdio.h>

// p[0] ֻ����һ��ʮ����λ
short int p[1000000];		// 100 ��λ
int len;
int m;

int main(void)
{
	int i, c;
	char t;

	printf("���� p: ");
	while (scanf("%c", &t) != EOF)
	{
		if (t == '\n') break;
		p[len++] = t - '0';
	}
	printf("���� m: ");
	scanf("%d", &m);
	for (c=i=0; i<len; i++)
	{
		c = (c * 10 + p[i]) % m;	// ��ʽ 2
	}
	printf("����: %d\n", c);

	return 0;
}