
// �߾��������Ե;�����, ��֧�ָ���С��
// �㷨: ģ���˹��������
// ��Ҫ����:
// div()		�����̺�����
// div2()		������С������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 1000000
// �߾��ȷ�Χ 0 - 10^1000000
// �;��ȷ�Χ 0 - 99999999

// ���� a / b
char a[NUM];		// ������
int  b;				// ����
char c[NUM];		// ��
char r[NUM];		// ����, ��С������

int intlen(int n)		// �� int ��λ��
{
	int len = 0;

	while (n) 
	{
		len++;
		n /= 10;
	}
	return len;
}

// ���ǰ�� 0
void clear_zero(char *c, int topc)
{
	int i, j;

	for (i=0; i<topc; i++)		// ����ǰ�� 0
	{
		if (c[i] != '0') break;
	}
	if (i != 0)
	{
		for (j=0; i<topc; j++, i++)
			c[j] = c[i];
		c[j] = '\0';
	}
	else c[topc] = '\0';
	if (c[0] == '\0') { c[1] = c[0];   c[0] = '0'; }
}

// ��ڲ���, a, b, ���ڲ���: c, r
void div()
{
	int lena, lenb;
	int tmp, i;
	int cur;
	int topc = 0;

	// �Ƚ� a, b �Ĵ�С
	lena = strlen(a);
	lenb = intlen(b);
	// ��� lena <= lenb ˵���� int �ı�ʾ��Χ��
	if (lena <= lenb)
	{
		tmp = atoi(a);
		itoa(tmp / b, c, 10);
		itoa(tmp % b, r, 10);
		return ;
	}
	// ��ʱ lena > lenb, a �� b ��
	for (tmp=i=0, cur=NULL; i<lenb; i++)
		tmp = tmp * 10 + a[cur++] - '0';
	while (1)
	{
		c[topc++] = tmp / b + '0';
		tmp %= b;
		if (a[cur] == '\0') break;
		tmp = tmp * 10 + a[cur++] - '0';
	}
	itoa(tmp, r, 10);		// ����
	clear_zero(c, topc);	// ���ǰ�� 0
}

// ��ڲ���, a, b, n, ���ڲ���: c, r
// n ��ʾ���㵽�� n λС��
// �ڵ�������, �ٲ��ϵس� 10 ���
void div2(__int64 n)
{
	int lena, lenb;
	int topa, topc, topr;
	int i, tmp;

	c[0] = r[0] = '\0';
	lena = strlen(a);
	lenb = intlen(b);
	for (tmp=topa=i=0; i<lenb; i++)
	{
		if (topa < lena)
			tmp = tmp * 10 + a[topa++] - '0';
		else break;
	}
	topc = 0;
	while (1)
	{
		c[topc++] = tmp / b + '0';
		tmp %= b;
		if (a[topa] == '\0') break;
		tmp = tmp * 10 + a[topa++] - '0';
	}
	clear_zero(c, topc);		// ���ǰ�� 0
	for (topr=i=0; i<n; i++)	// ���� n λС��
	{
		tmp = tmp * 10;
		r[topr++] = tmp / b + '0';
		tmp %= b;
	}
	r[topr] = '\0';
	// ����� 0, ֻ����һ�� 0
	while (r[topr - 1] == '0' && topr != 1) topr--;
	r[topr] = '\0';
}

int main(void)
{
	while (1)
	{
		printf("����߾��ȱ�����: ");
		scanf("%s", a);
		printf("����;��ȳ���: ");
		scanf("%d", &b);
		if (b == 0) return 0;		// ���ܳ� 0
		div();
		printf("\n��: %s\n����: %s\n", c, r);
		div2(40);			// ���� 40 λС��
		printf("С����ʽ: %s.%s\n\n", c, r);
	}
	return 0;
}