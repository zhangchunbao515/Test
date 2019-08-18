
// �߾��ȸ����ͼӷ�
// input()		����
// show()		���
// add()		���

#include <stdio.h>
#include <string.h>

#define NUM 1000000		// 100 ��λ, Լռ 5.7MB �ڴ�

// n[] ����С����ǰ����, _n ����С��������
// �ӵ�ַ 0 ��ʼ����
typedef struct
{
	char n[NUM];
	int  len;
	char _n[NUM];
	int  _len;
}bignum;			// ������

bignum x, y, z;			// x + y = z

// ����ģ��
void input(bignum *str)
{
	char tmp;
	int point = 1;
	
	str->len = str->_len = 0;
	while (1)
	{
		tmp = getchar();
		if (tmp == '\n') break;
		if (point)
		{
			if (tmp == '.') point = 0;
			else str->n[str->len++] = tmp;
		}
		else str->_n[str->_len++] = tmp;
	}
	str->n[str->len] = '\0';
	str->_n[str->_len] = '\0';
}

// ���ģ��, num ��ʾ�����С��λ, num == -1 ��ʾȫ�����
void show(bignum *s, int num)
{
	char tmp;
	int i;

	printf("%s", s->n);
	if (s->_len != 0 && num != 0) putchar('.');
	if (num <= s->_len)
	{
		// Ƶ������ printf �ܷ�ʱ
		tmp = s->_n[num];
		s->_n[num] = '\0';
		printf("%s", s->_n);
		s->_n[num] = tmp;
	}
	else
	{
		printf("%s", s->_n);
		for (i=num - s->_len; i>=0; i--)
			putchar('0');
	}
	putchar('\n');
}

// ���ͼӷ�ģ��, xx + yy = zz
// ���ؽ�λ��־ cf, flag ��־�����������ֻ���С��
int int_add(char *xx, char *yy, char *zz, int cf, int flag)
{
	int len1 = strlen(xx);
	int len2 = strlen(yy);
	int min = len1 > len2 ? len2 : len1;
	int top = NUM;
	int tmp;
	int a, b, i;

	// Ƶ������ printf() ��ʱ��, �� z ������, һ�����
	zz[--top] = '\0';
	for (i=min-1; i>=0; i--)
	{
		a = xx[--len1] - '0';
		b = yy[--len2] - '0';
		tmp = (a + b + cf) % 10;
		cf = (a + b + cf) / 10;
		zz[--top] = tmp + '0';
	}
	if (len1) 
	{
		while (cf != 0)
		{
			if (len1 > 0)
				a = xx[--len1] - '0';
			else a = 0;
			tmp = (a + cf) % 10;
			zz[--top] = tmp + '0';
			cf = (a + cf) / 10;
		}
		while (len1) 
			zz[--top] = xx[--len1];
	}
	else if (len2)
	{
		while (cf != 0)
		{
			if (len2 > 0)
				a = yy[--len2] - '0';
			else a = 0;
			tmp = (a + cf) % 10;
			zz[--top] = tmp + '0';
			cf = (a + cf) / 10;
		}
		while (len2) 
			zz[--top] = yy[--len2];
	}
	i = 0;
	if (flag == 1 && cf == 1) zz[i++] = '1';
	while (1)		// �ƶ��� 0 ��ַ
	{
		zz[i++] = zz[top++];
		if (zz[top-1] == '\0') break;
	}
	return cf;
}

// ������������� x + y = z
// �Ȱ�С�����ֵ�λ������, �������ͼӷ�ģ�����, ���ؽ�λ��־
// ��������ֱ�ӵ������ͼӷ�ģ��������, ͬʱ����С���Ľ�λ
void add(void)
{
	int i;
	int cf = 0;		// ��λ��־

	// С�����ֲ��� 0
	if (x._len < y._len)
	{
		for (i=x._len; i<y._len; i++)
			x._n[i] = '0';
		x._n[i] = '\0';
		x._len = y._len;
	}
	else if (y._len < x._len)
	{
		for (i=y._len; i<x._len; i++)
			y._n[i] = '0';
		y._n[i] = '\0';
		y._len = x._len;
	}
	// С���������
	cf = int_add(x._n, y._n, z._n, cf, 0);
	z._len = x._len;
	while (z._n[z._len - 1] == '0') z._len--;	// ������ 0
	z._n[z._len] = '\0';
	// �����������
	cf = int_add(x.n, y.n, z.n, cf, 1);
}

int main(void)
{
	while (1)
	{
		// ������������, ������һ������, ����ת��Ϊ����
		// ֧�ָ���������������
		printf("\n����������:\n��һ��: ");
		input(&x);
		printf("�ڶ���: ");
		input(&y);
		add();
		printf("��� :  ");
		show(&z, -1);		// ���ȫ��С��
//		show(&z, 6);		// ��� 6 λС��
//		show(&z, 0);		// ȡ��
	}
	return 0;
}