
// �߾������ͼӷ�����, ��֧��С��, ��������ת��Ϊ����

#include <stdio.h>
#include <string.h>

#define NUM 10000000		// ���� 10^10000000 ֮��
// �߾��Ȳ��������޸�, �ܵ��ڴ������

// -------------- z = x + y, �ַ�����洢 ------------------
char x[NUM];
char y[NUM];
char z[NUM];

void add(void)
{
	int len1 = strlen(x);
	int len2 = strlen(y);
	int min = len1 > len2 ? len2 : len1;
	int cf = 0;			// ��λ��־
	int top = NUM - 1;
	int tmp;
	int a, b, i;

	// Ƶ������ printf() ��ʱ��, �� z ������, һ�����
	z[top] = '\0';
	for (i=min-1; i>=0; i--)
	{
		a = x[--len1] - '0';
		b = y[--len2] - '0';
		tmp = (a + b + cf) % 10;
		cf = (a + b + cf) / 10;
		z[--top] = tmp + '0';
	}
	if (len1) 
	{
		// ���ܰѳ����Ĳ���ֱ�Ӹ��Ƶ� z
		// ����  99999000
		// ��        1000
		// ���� 100000000
		while (cf != 0)
		{
			if (len1 > 0)
				a = x[--len1] - '0';
			else a = 0;
			tmp = (a + cf) % 10;
			z[--top] = tmp + '0';
			cf = (a + cf) / 10;
		}
		while (len1) 
			z[--top] = x[--len1];
	}
	else if (len2)
	{
		while (cf != 0)
		{
			if (len2 > 0)
				a = y[--len2] - '0';
			else a = 0;
			tmp = (a + cf) % 10;
			z[--top] = tmp + '0';
			cf = (a + cf) / 10;
		}
		while (len2) 
			z[--top] = y[--len2];
	}
	if (cf) z[--top] = '1';
	printf("���� :  %s\n", z + top);
}

int main(void)
{
	while (1)
	{
		printf("\n����������:\n��һ��: ");
		scanf("%s", x);
		printf("�ڶ���: ");
		scanf("%s", y);

		add();
	}
	return 0;
}