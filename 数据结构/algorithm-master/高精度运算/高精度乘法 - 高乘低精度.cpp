
// �߾��ȳ��Ե;���
// �߾��ȷ�Χ 0 - 10^1000000
// �;��ȷ�Χ int ��֮��

#include <stdio.h>
#include <string.h>

#define NUM 1000000

char a[NUM];		// �߾��ȳ���
char z[NUM];		// ������
int top;

// ��ڲ��� a, b, ���ڲ��� r + top
void mul(int b)
{
	int i;
	int len = strlen(a);
	int cf = 0;
	int tmp = 0;

	top = NUM;
	z[--top] = '\0';
	for (i=len-1; i>=0; i--)
	{
		tmp = (a[i] - '0') * b + cf;
		z[--top] = tmp % 10 + '0';
		cf = tmp / 10;
	}
	while (cf)
	{
		z[--top] = cf % 10 + '0';
		cf /= 10;
	}
	while (z[top] == '0') top++;	// ����ǰ�� 0
	if (z[top] == '\0') z[--top] = '0';
}

int main(void)
{
	int b;

	while (1)
	{
		printf("����߾�������: ");
		scanf("%s", a);
		printf("����;�������: ");
		scanf("%d", &b);
		mul(b);		// a * b
		printf("���: %s\n\n", z + top);
	}
	return 0;
}